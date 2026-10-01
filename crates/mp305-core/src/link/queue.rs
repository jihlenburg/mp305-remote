//! The two-level queue: urgent entries first, each level in order. Nothing
//! else reorders entries.
//!
//! Implements: DD-LINK-011.

use std::collections::VecDeque;

use tokio::sync::oneshot;

use crate::error::Error;
use crate::link::class::Class;
use crate::link::Outcome;
use crate::protocol::frame::Frame;

/// The requests the link issues on its own.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub(crate) enum Internal {
    /// The poll's `0xC2` (DD-LINK-030).
    Poll,
    /// The `0xC2` that clears the `0xC8` block (DD-LINK-023).
    Block,
    /// The USB keepalive `0xE0` (DD-LINK-031).
    Keepalive,
}

/// Who is told how a request ended.
#[derive(Debug)]
pub(crate) enum Responder {
    /// A caller of `Link::request`; cancelled when its future is dropped
    /// before the write.
    Caller(oneshot::Sender<Result<Outcome, Error>>),
    /// A caller of `Link::output_off`; written even when its future was
    /// dropped.
    OutputOff(oneshot::Sender<Result<Outcome, Error>>),
    /// The link itself; nobody is told.
    Internal(Internal),
}

impl Responder {
    /// Tells the caller, if there is one, how the request ended. A caller
    /// that stopped waiting is not an error.
    pub(crate) fn resolve(self, result: Result<Outcome, Error>) {
        match self {
            Responder::Caller(tx) | Responder::OutputOff(tx) => {
                // The caller may have dropped its future; nothing to do then.
                let _ = tx.send(result);
            }
            Responder::Internal(_) => {}
        }
    }

    /// Whether this is a request whose future was dropped, so that it must
    /// not be written (DD-LINK-022). An `output_off` is never cancelled.
    pub(crate) fn is_cancelled(&self) -> bool {
        matches!(self, Responder::Caller(tx) if tx.is_closed())
    }

    /// The word the `sent` log line uses for this request.
    pub(crate) fn word(&self, class: &Class) -> &'static str {
        match (self, class) {
            (Responder::OutputOff(_), _) => "output-off",
            (_, Class::Deferred { .. }) => "deferred",
            (_, Class::Immediate { .. }) => "immediate",
        }
    }
}

/// One queued request.
#[derive(Debug)]
pub(crate) struct Queued {
    /// The frame to write.
    pub(crate) frame: Frame,
    /// Its class, fixed when it was queued.
    pub(crate) class: Class,
    /// Who is told how it ended.
    pub(crate) responder: Responder,
}

/// Two queues: urgent (`output_off`) and normal.
#[derive(Debug, Default)]
pub(crate) struct Queue {
    /// `output_off` requests, in order.
    urgent: VecDeque<Queued>,
    /// Every other request, in order.
    normal: VecDeque<Queued>,
}

impl Queue {
    /// Appends an urgent entry.
    pub(crate) fn push_urgent(&mut self, entry: Queued) {
        self.urgent.push_back(entry);
    }

    /// Appends a normal entry.
    pub(crate) fn push_normal(&mut self, entry: Queued) {
        self.normal.push_back(entry);
    }

    /// The urgent head if any, else the normal head.
    pub(crate) fn peek(&self) -> Option<&Queued> {
        self.urgent.front().or_else(|| self.normal.front())
    }

    /// Removes the urgent head if any, else the normal head.
    // Part of the queue's interface (DD-LINK-011) and tested by UT-LINK-002;
    // the send step weighs each head on its own and does not call it.
    #[cfg_attr(not(test), allow(dead_code))]
    pub(crate) fn pop_front(&mut self) -> Option<Queued> {
        self.urgent.pop_front().or_else(|| self.normal.pop_front())
    }

    /// The head of the urgent queue, for the send step, which weighs each
    /// head on its own (DD-LINK-022).
    pub(crate) fn urgent_head(&self) -> Option<&Queued> {
        self.urgent.front()
    }

    /// The head of the normal queue.
    pub(crate) fn normal_head(&self) -> Option<&Queued> {
        self.normal.front()
    }

    /// Removes the head of the urgent queue.
    pub(crate) fn pop_urgent(&mut self) -> Option<Queued> {
        self.urgent.pop_front()
    }

    /// Removes the head of the normal queue.
    pub(crate) fn pop_normal(&mut self) -> Option<Queued> {
        self.normal.pop_front()
    }

    /// Removes every entry and resolves each responder with a clone of
    /// `error`.
    pub(crate) fn drain(&mut self, error: &Error) {
        for entry in self.urgent.drain(..).chain(self.normal.drain(..)) {
            entry.responder.resolve(Err(error.clone()));
        }
    }

    /// The number of queued entries.
    // Part of the queue's interface (DD-LINK-011) and tested by UT-LINK-002;
    // the send step weighs each head on its own and does not call it.
    #[cfg_attr(not(test), allow(dead_code))]
    pub(crate) fn len(&self) -> usize {
        self.urgent.len().saturating_add(self.normal.len())
    }

    /// Whether nothing is queued.
    // Part of the queue's interface (DD-LINK-011) and tested by UT-LINK-002;
    // the send step weighs each head on its own and does not call it.
    #[cfg_attr(not(test), allow(dead_code))]
    pub(crate) fn is_empty(&self) -> bool {
        self.urgent.is_empty() && self.normal.is_empty()
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::error::Error;
    use crate::link::class::Class;
    use crate::protocol::ops::{info, telemetry};
    use tokio::sync::oneshot;

    fn entry(opcode: u8) -> (Queued, oneshot::Receiver<Result<Outcome, Error>>) {
        let (tx, rx) = oneshot::channel();
        let frame = if opcode == 0xE0 {
            info::request()
        } else {
            telemetry::request()
        };
        let class = Class::Immediate {
            reply: opcode + 1,
            timeout: crate::protocol::timing::REPLY,
        };
        (
            Queued {
                frame,
                class,
                responder: Responder::Caller(tx),
            },
            rx,
        )
    }

    /// Test: UT-LINK-002
    #[test]
    fn urgent_first_then_in_order_and_drain_resolves_all() {
        let mut q = Queue::default();
        let (a, _ra) = entry(0xE0);
        let (b, _rb) = entry(0xC2);
        let (mut c, _rc) = entry(0xE0);
        c.frame = crate::protocol::frame::Frame::new(0xC8, vec![1; 11]).unwrap();
        q.push_normal(a);
        q.push_normal(b);
        q.push_urgent(c);
        assert_eq!(q.len(), 3);
        assert_eq!(q.peek().map(|e| e.frame.opcode()), Some(0xC8));
        let order: Vec<u8> =
            std::iter::from_fn(|| q.pop_front().map(|e| e.frame.opcode())).collect();
        assert_eq!(order, vec![0xC8, 0xE0, 0xC2]);
        assert!(q.is_empty());

        let (a, mut ra) = entry(0xE0);
        let (b, mut rb) = entry(0xC2);
        q.push_normal(a);
        q.push_urgent(b);
        let lost = Error::LinkLost {
            text: "x".to_string(),
        };
        q.drain(&lost);
        assert!(q.is_empty());
        assert_eq!(ra.try_recv().unwrap().unwrap_err(), lost);
        assert_eq!(rb.try_recv().unwrap().unwrap_err(), lost);
    }
}
