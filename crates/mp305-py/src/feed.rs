//! Implements: DD-PY-007
//!
//! The feed: one per native session, the buffer between the core's
//! `SessionEvents` and every Python reader. The forwarder, a Tokio task, is
//! the only owner of the events; it numbers each event and pushes it into
//! two rings, readings and the other events. Readers keep their own cursors
//! over those numbers, so no lock is held while anyone waits.
//!
//! Three counters, all from 1: the sequence number orders every event of
//! the session, readings included; the reading number counts readings and
//! the event number the other events. The numbers a ring holds are
//! consecutive, so a gap between a cursor and the oldest number kept is
//! exactly what was dropped.

use core::future::Future;
use core::time::Duration;
use std::collections::VecDeque;
use std::sync::atomic::{AtomicBool, Ordering};
use std::sync::{Arc, Mutex, MutexGuard, PoisonError};

use futures::FutureExt;
use mp305_core::session::{SessionEvent, SessionEvents, TimedReading};
use tokio::sync::{mpsc, oneshot, watch};
use tokio::task::JoinHandle;

/// The readings a feed keeps; the oldest is dropped when full.
pub const READINGS_KEPT: usize = 1024;
/// The events other than readings a feed keeps; the oldest is dropped when
/// full.
pub const EVENTS_KEPT: usize = 1024;

/// Where the forwarder takes events from: the core's `SessionEvents`, or a
/// channel in the tests. `next` must be cancel-safe, since the forwarder
/// drops a pending `next` whenever it serves a flush (py DD, decision 5).
pub trait Source: Send + 'static {
    /// The next event, `None` once the source ended.
    fn next(&mut self) -> impl Future<Output = Option<SessionEvent>> + Send;
}

impl Source for SessionEvents {
    fn next(&mut self) -> impl Future<Output = Option<SessionEvent>> + Send {
        SessionEvents::next(self)
    }
}

/// Locks `mutex`, recovering the data of a poisoned lock (DD-SESS-052's
/// rule). A leaf lock: held only for a copy or a push.
pub fn lock<T>(mutex: &Mutex<T>) -> MutexGuard<'_, T> {
    mutex.lock().unwrap_or_else(PoisonError::into_inner)
}

/// What the feed's lock guards.
#[derive(Debug)]
struct FeedState {
    /// The sequence number of the next event.
    next_seq: u64,
    /// The reading number of the next reading.
    next_reading: u64,
    /// The event number of the next event other than a reading.
    next_event: u64,
    /// The readings kept, keyed by reading number.
    readings: VecDeque<(u64, TimedReading)>,
    /// The other events kept: event number, sequence number, event.
    events: VecDeque<(u64, u64, SessionEvent)>,
    /// The event number of the last event dispatched.
    dispatch_cursor: u64,
    /// The event number of the last event `events_take` returned.
    events_cursor: u64,
    /// Events dropped before `events_take` returned them.
    events_overwritten: u64,
    /// The loss text, while the link is lost.
    loss_text: Option<String>,
    /// Whether the source ended.
    ended: bool,
}

/// A flush request: answered once everything the source had ready is in
/// the feed.
type FlushRequest = oneshot::Sender<()>;

/// The feed of one native session, shared as `Arc<Feed>`.
#[derive(Debug)]
pub struct Feed {
    /// The rings and cursors.
    state: Mutex<FeedState>,
    /// The newest sequence number, sent on every push and at the end.
    seq: watch::Sender<u64>,
    /// Whether the source ended; read by waiters without the lock.
    ended: AtomicBool,
    /// Flush requests to the forwarder.
    flush: mpsc::UnboundedSender<FlushRequest>,
    /// The dispatch token (DD-PY-003): taken by the one thread that
    /// dispatches, never waited for.
    dispatching: AtomicBool,
}

/// Holds the dispatch token and releases it when dropped, on every return
/// path.
#[derive(Debug)]
pub struct DispatchToken<'a>(&'a AtomicBool);

impl Drop for DispatchToken<'_> {
    fn drop(&mut self) {
        self.0.store(false, Ordering::Release);
    }
}

/// What `readings_after` returns: the readings, the new cursor and the
/// number of readings skipped because they were dropped.
pub type ReadingsAfter = (Vec<TimedReading>, u64, u64);

impl Feed {
    /// A feed with its forwarder spawned on the current runtime, which owns
    /// `source` from now on. Needs the runtime entered.
    pub fn start<S: Source>(source: S) -> (Arc<Feed>, JoinHandle<()>) {
        let (feed, requests) = Feed::new();
        let handle = tokio::spawn(forward(Arc::clone(&feed), source, requests));
        (feed, handle)
    }

    /// An empty feed and the receiver of its flush requests.
    fn new() -> (Arc<Feed>, mpsc::UnboundedReceiver<FlushRequest>) {
        let (flush, requests) = mpsc::unbounded_channel();
        let (seq, _) = watch::channel(0);
        let feed = Arc::new(Feed {
            state: Mutex::new(FeedState {
                next_seq: 1,
                next_reading: 1,
                next_event: 1,
                readings: VecDeque::new(),
                events: VecDeque::new(),
                dispatch_cursor: 0,
                events_cursor: 0,
                events_overwritten: 0,
                loss_text: None,
                ended: false,
            }),
            seq,
            ended: AtomicBool::new(false),
            flush,
            dispatching: AtomicBool::new(false),
        });
        (feed, requests)
    }

    /// Numbers `event` and pushes it into its ring; keeps the loss text.
    fn push(&self, event: SessionEvent) {
        let seq = {
            let mut st = lock(&self.state);
            let seq = st.next_seq;
            st.next_seq = seq.saturating_add(1);
            match event {
                SessionEvent::Reading(reading) => {
                    let n = st.next_reading;
                    st.next_reading = n.saturating_add(1);
                    st.readings.push_back((n, reading));
                    if st.readings.len() > READINGS_KEPT {
                        st.readings.pop_front();
                    }
                }
                other => {
                    match &other {
                        SessionEvent::LinkLost { text } => st.loss_text = Some(text.clone()),
                        SessionEvent::ReconnectGaveUp { text } => {
                            st.loss_text = Some(match st.loss_text.take() {
                                Some(previous) => format!("{previous} {text}"),
                                None => text.clone(),
                            });
                        }
                        SessionEvent::Reconnected => st.loss_text = None,
                        _ => {}
                    }
                    let n = st.next_event;
                    st.next_event = n.saturating_add(1);
                    st.events.push_back((n, seq, other));
                    if st.events.len() > EVENTS_KEPT {
                        st.events.pop_front();
                    }
                }
            }
            seq
        };
        self.seq.send_replace(seq);
    }

    /// Marks the source ended and wakes every waiter.
    fn end(&self) {
        lock(&self.state).ended = true;
        self.ended.store(true, Ordering::SeqCst);
        self.seq.send_modify(|_| {});
    }

    /// The newest sequence number (0 before the first event).
    #[must_use]
    pub fn seq(&self) -> u64 {
        lock(&self.state).next_seq.saturating_sub(1)
    }

    /// The newest reading number (0 before the first reading).
    #[must_use]
    pub fn newest_reading(&self) -> u64 {
        lock(&self.state).next_reading.saturating_sub(1)
    }

    /// The newest event number (0 before the first event).
    #[must_use]
    pub fn newest_event(&self) -> u64 {
        lock(&self.state).next_event.saturating_sub(1)
    }

    /// Whether the source ended.
    #[must_use]
    pub fn ended(&self) -> bool {
        self.ended.load(Ordering::SeqCst)
    }

    /// At most `limit` readings with a reading number above `cursor`, the
    /// new cursor (the number of the last one returned), and how many
    /// readings after `cursor` were dropped before they could be returned.
    #[must_use]
    pub fn readings_after(&self, cursor: u64, limit: usize) -> ReadingsAfter {
        let st = lock(&self.state);
        let (skipped, start) = match st.readings.front() {
            Some(&(oldest, _)) => {
                let skipped = oldest.saturating_sub(cursor).saturating_sub(1);
                (skipped, cursor.max(oldest.saturating_sub(1)))
            }
            None => (0, cursor),
        };
        let items: Vec<(u64, TimedReading)> = st
            .readings
            .iter()
            .filter(|(n, _)| *n > start)
            .take(limit)
            .copied()
            .collect();
        let new_cursor = items.last().map_or(start, |(n, _)| *n);
        (
            items.into_iter().map(|(_, r)| r).collect(),
            new_cursor,
            skipped,
        )
    }

    /// At most `limit` events not yet returned by this call, in order, with
    /// their sequence numbers; advances the cursor in the same lock hold and
    /// counts events dropped before they were returned.
    pub fn events_take(&self, limit: usize) -> Vec<(u64, SessionEvent)> {
        let mut st = lock(&self.state);
        if let Some(&(oldest, _, _)) = st.events.front() {
            let gap = oldest.saturating_sub(st.events_cursor).saturating_sub(1);
            if gap > 0 {
                st.events_overwritten = st.events_overwritten.saturating_add(gap);
                st.events_cursor = oldest.saturating_sub(1);
            }
        }
        let cursor = st.events_cursor;
        let taken: Vec<(u64, u64, SessionEvent)> = st
            .events
            .iter()
            .filter(|(n, _, _)| *n > cursor)
            .take(limit)
            .cloned()
            .collect();
        if let Some((last, _, _)) = taken.last() {
            st.events_cursor = *last;
        }
        taken.into_iter().map(|(_, seq, e)| (seq, e)).collect()
    }

    /// Events dropped before `events_take` returned them.
    #[must_use]
    pub fn events_overwritten(&self) -> u64 {
        lock(&self.state).events_overwritten
    }

    /// The next undispatched event with an event number at most `upto`,
    /// with its sequence number; advances the dispatch cursor past it.
    /// Events dropped before they were dispatched are skipped.
    pub fn take_for_dispatch(&self, upto: u64) -> Option<(u64, SessionEvent)> {
        let mut st = lock(&self.state);
        let cursor = st.dispatch_cursor;
        let (n, seq, event) = st
            .events
            .iter()
            .find(|(n, _, _)| *n > cursor && *n <= upto)
            .cloned()?;
        st.dispatch_cursor = n;
        Some((seq, event))
    }

    /// Takes the dispatch token, or `None` when another dispatcher holds it.
    pub fn try_dispatch(&self) -> Option<DispatchToken<'_>> {
        self.dispatching
            .compare_exchange(false, true, Ordering::AcqRel, Ordering::Acquire)
            .ok()
            .map(|_| DispatchToken(&self.dispatching))
    }

    /// The loss text while the link is lost: the `LinkLost` text, followed
    /// by a space and the `ReconnectGaveUp` text once the reconnection gave
    /// up; cleared by `Reconnected`.
    #[must_use]
    pub fn loss_text(&self) -> Option<String> {
        lock(&self.state).loss_text.clone()
    }

    /// Waits until the newest sequence number is above `after`, the source
    /// ended or `wait` passed, and returns the newest sequence number. Any
    /// number of tasks can wait at once; no lock is held.
    pub async fn wait(&self, after: u64, wait: Duration) -> u64 {
        let mut rx = self.seq.subscribe();
        let ended = &self.ended;
        let woken = tokio::time::timeout(
            wait,
            rx.wait_for(|newest| *newest > after || ended.load(Ordering::SeqCst)),
        )
        .await;
        drop(woken);
        self.seq()
    }

    /// Returns once everything the source had ready when the request was
    /// served is in the feed; at once when the forwarder has ended.
    ///
    /// The end is watched as well as the answer: a request sent while the
    /// forwarder drops its receiver can stay queued unanswered, since the
    /// feed keeps the sender, and the end comes right after a session's
    /// close, which is when `close` flushes.
    pub async fn flush(&self) {
        let (tx, rx) = oneshot::channel();
        if self.flush.send(tx).is_err() {
            return;
        }
        let mut newest = self.seq.subscribe();
        let ended = &self.ended;
        tokio::select! {
            _ = rx => {}
            _ = newest.wait_for(|_| ended.load(Ordering::SeqCst)) => {}
        }
    }
}

/// The forwarder: the only owner of `source`. A biased select serves flush
/// requests first, taking every event the source has ready without waiting
/// before it answers; otherwise it waits for the next event. It holds no
/// core session and runs no Python.
async fn forward<S: Source>(
    feed: Arc<Feed>,
    mut source: S,
    mut requests: mpsc::UnboundedReceiver<FlushRequest>,
) {
    loop {
        tokio::select! {
            biased;
            Some(reply) = requests.recv() => {
                loop {
                    // Unconstrained: Tokio's cooperative budget would make a
                    // ready channel answer `Pending` after 128 polls, and the
                    // flush would stop short of what the source has ready.
                    match tokio::task::unconstrained(source.next()).now_or_never() {
                        Some(Some(event)) => feed.push(event),
                        Some(None) => {
                            feed.end();
                            let _ = reply.send(());
                            return;
                        }
                        None => break,
                    }
                }
                let _ = reply.send(());
            }
            event = source.next() => match event {
                Some(event) => feed.push(event),
                None => {
                    feed.end();
                    return;
                }
            },
        }
    }
}

/// A channel as a [`Source`], for tests.
#[cfg(test)]
pub(crate) struct ChannelSource(pub(crate) mpsc::UnboundedReceiver<SessionEvent>);

#[cfg(test)]
impl Source for ChannelSource {
    fn next(&mut self) -> impl Future<Output = Option<SessionEvent>> + Send {
        self.0.recv()
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use mp305_core::protocol::fixtures::C3_CAPTURE;
    use mp305_core::protocol::ops::telemetry::{self, Reading};
    use std::time::{SystemTime, UNIX_EPOCH};
    use tokio::time::Instant;

    /// A reading of the capture with the wall time `n` seconds after the
    /// epoch, so tests can tell readings apart.
    fn reading(n: u64) -> SessionEvent {
        let raw = telemetry::parse_payload(&C3_CAPTURE).unwrap();
        SessionEvent::Reading(TimedReading {
            at: Instant::now(),
            wall: UNIX_EPOCH + Duration::from_secs(n),
            reading: Reading::from_raw(&raw),
        })
    }

    /// A non-reading event carrying `n` in its text.
    fn event(n: u64) -> SessionEvent {
        SessionEvent::LinkLost {
            text: n.to_string(),
        }
    }

    /// A started feed over a channel.
    fn feed() -> (
        Arc<Feed>,
        mpsc::UnboundedSender<SessionEvent>,
        JoinHandle<()>,
    ) {
        let (tx, rx) = mpsc::unbounded_channel();
        let (feed, handle) = Feed::start(ChannelSource(rx));
        (feed, tx, handle)
    }

    /// The wall time of a reading in whole seconds.
    fn secs(r: &TimedReading) -> u64 {
        r.wall.duration_since(UNIX_EPOCH).unwrap().as_secs()
    }

    /// Test: UT-PY-022 (a)
    #[tokio::test]
    async fn the_reading_ring_keeps_1024_and_counts_the_skipped() {
        let (feed, tx, _h) = feed();
        for n in 1..=1100 {
            tx.send(reading(n)).unwrap();
        }
        feed.flush().await;
        let (items, cursor, skipped) = feed.readings_after(0, 2000);
        assert_eq!(items.len(), 1024);
        assert_eq!(secs(&items[0]), 77);
        assert_eq!(skipped, 76);
        assert_eq!(cursor, 1100);
        let (rest, _, skipped) = feed.readings_after(cursor, 10);
        assert!(rest.is_empty());
        assert_eq!(skipped, 0);
    }

    /// Test: UT-PY-022 (b)
    #[tokio::test]
    async fn the_event_ring_keeps_1024_and_counts_the_overwritten() {
        let (feed, tx, _h) = feed();
        for n in 1..=1100 {
            tx.send(event(n)).unwrap();
        }
        feed.flush().await;
        let first = feed.events_take(2000);
        assert_eq!(first.len(), 1024);
        assert_eq!(feed.events_overwritten(), 76);
        assert_eq!(
            first[0].1,
            SessionEvent::LinkLost {
                text: "77".to_string()
            }
        );
        assert!(feed.events_take(2000).is_empty());
    }

    /// Test: UT-PY-022 (c)
    #[tokio::test]
    async fn the_loss_text_follows_loss_reconnection_and_give_up() {
        let (feed, tx, _h) = feed();
        tx.send(SessionEvent::LinkLost {
            text: "a".to_string(),
        })
        .unwrap();
        feed.flush().await;
        assert_eq!(feed.loss_text(), Some("a".to_string()));
        tx.send(SessionEvent::Reconnected).unwrap();
        feed.flush().await;
        assert_eq!(feed.loss_text(), None);
        tx.send(SessionEvent::LinkLost {
            text: "b".to_string(),
        })
        .unwrap();
        tx.send(SessionEvent::ReconnectGaveUp {
            text: "g".to_string(),
        })
        .unwrap();
        feed.flush().await;
        assert_eq!(feed.loss_text(), Some("b g".to_string()));
    }

    /// Test: UT-PY-022 (d)
    #[tokio::test]
    async fn flush_makes_every_ready_event_readable() {
        let (feed, tx, _h) = feed();
        for n in 1..=5 {
            tx.send(event(n)).unwrap();
        }
        feed.flush().await;
        assert_eq!(feed.seq(), 5);
        assert_eq!(feed.events_take(10).len(), 5);
    }

    /// Test: UT-PY-022 (e)
    #[tokio::test(flavor = "multi_thread", worker_threads = 2)]
    async fn waiters_wake_at_the_end_of_the_source() {
        let (feed, tx, _h) = feed();
        tx.send(event(1)).unwrap();
        feed.flush().await;
        let seq = feed.seq();
        let waiters: Vec<_> = (0..2)
            .map(|_| {
                let feed = Arc::clone(&feed);
                tokio::spawn(async move {
                    let n = feed.wait(seq, Duration::from_secs(1)).await;
                    (n, SystemTime::now())
                })
            })
            .collect();
        tokio::time::sleep(Duration::from_millis(50)).await;
        drop(tx);
        let closed = SystemTime::now();
        for waiter in waiters {
            let (n, at) = waiter.await.unwrap();
            assert_eq!(n, 1);
            let after = at.duration_since(closed).unwrap_or(Duration::ZERO);
            assert!(after < Duration::from_millis(100), "{after:?}");
        }
        assert!(feed.ended());
        assert!(lock(&feed.state).ended);
        // After the end, a flush returns at once.
        feed.flush().await;
    }

    /// Test: UT-PY-022 (`flush` after the end, also with a request the
    /// forwarder never answered: a request sent while the forwarder drops
    /// its receiver can stay queued, since the feed keeps the sender)
    #[tokio::test]
    async fn flush_returns_once_the_forwarder_ended() {
        let (feed, requests) = Feed::new();
        let pending = {
            let feed = Arc::clone(&feed);
            tokio::spawn(async move { feed.flush().await })
        };
        tokio::time::sleep(Duration::from_millis(20)).await;
        assert!(!pending.is_finished());
        feed.end();
        let answered = tokio::time::timeout(Duration::from_secs(1), pending).await;
        assert!(
            answered.is_ok(),
            "a flush pending at the end did not return"
        );
        let late = tokio::time::timeout(Duration::from_secs(1), feed.flush()).await;
        assert!(late.is_ok(), "a flush after the end did not return");
        drop(requests);
    }

    /// Test: UT-PY-022 (f)
    #[tokio::test]
    async fn take_for_dispatch_returns_each_event_once() {
        let (feed, tx, _h) = feed();
        tx.send(event(1)).unwrap();
        tx.send(event(2)).unwrap();
        feed.flush().await;
        assert_eq!(feed.newest_event(), 2);
        assert_eq!(feed.take_for_dispatch(2), Some((1, event(1))));
        assert_eq!(feed.take_for_dispatch(2), Some((2, event(2))));
        assert_eq!(feed.take_for_dispatch(2), None);
        let token = feed.try_dispatch();
        assert!(token.is_some());
        assert!(feed.try_dispatch().is_none());
        drop(token);
        assert!(feed.try_dispatch().is_some());
    }

    /// Test: UT-PY-022 (g)
    #[tokio::test]
    async fn the_three_counters() {
        let (feed, tx, _h) = feed();
        tx.send(reading(1)).unwrap();
        tx.send(event(1)).unwrap();
        tx.send(reading(2)).unwrap();
        tx.send(reading(3)).unwrap();
        tx.send(event(2)).unwrap();
        feed.flush().await;
        assert_eq!(feed.seq(), 5);
        assert_eq!(feed.newest_reading(), 3);
        let (items, _, skipped) = feed.readings_after(0, 10);
        assert_eq!(items.iter().map(secs).collect::<Vec<_>>(), [1, 2, 3]);
        assert_eq!(skipped, 0);
        let events: Vec<u64> = feed.events_take(10).into_iter().map(|(s, _)| s).collect();
        assert_eq!(events, [2, 5]);
    }
}
