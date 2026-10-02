//! Implements: DD-APP-007.
//!
//! The shell owns the Tokio runtime and the worker's life cycle. The
//! runtime has to outlive the worker's last close, or a release is cut
//! half way; the bound on the shutdown keeps a dead link from hanging the
//! exit. The runtime is never dropped plainly, since that waits without
//! bound for blocking work.

use core::time::Duration;

use futures::future::BoxFuture;
use tokio::runtime::Runtime;
use tokio::sync::mpsc;
use tokio::task::JoinHandle;

use crate::worker::{self, AppEvent, Command, Deps, UiReading, UiSender, Wake};

/// The log target of the shell.
pub const LOG_TARGET: &str = "mp305_app::shell";

/// The runtime's worker threads.
const WORKER_THREADS: usize = 2;

/// The runtime's thread name.
const THREAD_NAME: &str = "mp305-worker";

/// How long the runtime's shutdown waits after the worker's bound.
const RUNTIME_GRACE: Duration = Duration::from_millis(500);

/// The UI's ends of the three channels.
#[derive(Debug)]
pub struct Port {
    /// Commands to the worker.
    pub commands: mpsc::UnboundedSender<Command>,
    /// Events from the worker.
    pub events: mpsc::UnboundedReceiver<AppEvent>,
    /// Readings from the worker.
    pub readings: mpsc::Receiver<UiReading>,
}

/// How the shutdown ended.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum ShutdownReport {
    /// The worker returned within the bound.
    Finished,
    /// The bound passed first; the runtime was shut down with the worker
    /// still running.
    TimedOut,
}

/// The runtime and the worker task.
#[derive(Debug)]
pub struct Shell {
    /// The runtime.
    runtime: Runtime,
    /// The worker task.
    join: JoinHandle<()>,
}

impl Shell {
    /// Builds the runtime, creates the channels and spawns the worker over
    /// `build`.
    ///
    /// # Errors
    ///
    /// The text of a runtime build error.
    pub fn start(
        build: BoxFuture<'static, Result<Deps, String>>,
        wake: Wake,
    ) -> Result<(Shell, Port), String> {
        let runtime = tokio::runtime::Builder::new_multi_thread()
            .worker_threads(WORKER_THREADS)
            .enable_all()
            .thread_name(THREAD_NAME)
            .build()
            .map_err(|e| e.to_string())?;
        let (commands, command_rx) = mpsc::unbounded_channel();
        let (event_tx, events) = mpsc::unbounded_channel();
        let (reading_tx, readings) = mpsc::channel(worker::READING_CAPACITY);
        let ui = UiSender::new(event_tx, reading_tx);
        let join = runtime.spawn(worker::start(build, command_rx, ui, wake));
        Ok((
            Shell { runtime, join },
            Port {
                commands,
                events,
                readings,
            },
        ))
    }

    /// Waits for the worker within `bound`, then shuts the runtime down
    /// within another 500 ms. Called after the UI dropped its command
    /// sender.
    #[must_use]
    pub fn shutdown(self, bound: Duration) -> ShutdownReport {
        let Shell { runtime, join } = self;
        // The timer is made inside the runtime, which drives it.
        let waited = runtime.block_on(async move { tokio::time::timeout(bound, join).await });
        let report = match waited {
            Ok(Ok(())) => ShutdownReport::Finished,
            Ok(Err(e)) => {
                log::error!(target: LOG_TARGET, "the worker ended abnormally: {e}");
                ShutdownReport::Finished
            }
            Err(_) => ShutdownReport::TimedOut,
        };
        runtime.shutdown_timeout(RUNTIME_GRACE);
        report
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::model::{Kind, Limits};
    use crate::worker::worker_tests::{counting_wake, deps, fast_script, limits, scanner_f, shape};
    use crate::worker::{ErrorText, What};
    use mp305_core::discovery::ScanOptions;
    use mp305_core::protocol::fixtures;
    use mp305_core::session::doubles::{MarkerCall, MemoryMarkers, MockConnector};
    use mp305_core::transport::mock::{Mock, Reply};
    use std::sync::atomic::Ordering;
    use std::sync::Arc;
    use std::time::Instant as StdInstant;

    /// The next event, waiting at most `bound`.
    fn next(port: &mut Port, bound: Duration) -> AppEvent {
        let deadline = StdInstant::now().checked_add(bound).unwrap();
        loop {
            match port.events.try_recv() {
                Ok(event) => return event,
                Err(_) if StdInstant::now() < deadline => {
                    std::thread::sleep(Duration::from_millis(1));
                }
                Err(e) => panic!("no event in time: {e:?}"),
            }
        }
    }

    /// Events until one that `stop` accepts, waiting at most 10 s each.
    fn until(port: &mut Port, stop: impl Fn(&AppEvent) -> bool) -> Vec<AppEvent> {
        let mut out = Vec::new();
        loop {
            let event = next(port, Duration::from_secs(10));
            let done = stop(&event);
            out.push(event);
            if done {
                return out;
            }
        }
    }

    /// A connector whose attempts follow the 5 ms script with `overrides`.
    fn fast_connector(identifier: &str, overrides: Vec<Reply>) -> Arc<MockConnector> {
        let id = identifier.to_string();
        Arc::new(MockConnector::new(move || {
            Ok(Mock::new(Kind::Ble, &id, fast_script(overrides.clone())))
        }))
    }

    /// A build future over the mock dependencies.
    fn mock_build(
        connector: &Arc<MockConnector>,
        markers: &Arc<MemoryMarkers>,
    ) -> BoxFuture<'static, Result<Deps, String>> {
        let deps = deps(connector, markers, scanner_f());
        Box::pin(async move { Ok(deps) })
    }

    /// Connects, requests remote control and waits for both.
    fn connect_and_grant(port: &mut Port, identifier: &str) {
        port.commands
            .send(Command::Connect {
                id: 1,
                identifier: identifier.into(),
                reconnect: false,
                limits: limits(),
            })
            .unwrap();
        until(port, |e| matches!(e, AppEvent::Ready { .. }));
        port.commands
            .send(Command::RequestRemoteControl { id: 2 })
            .unwrap();
        let done = until(port, |e| matches!(e, AppEvent::Done { id: 2, .. }));
        assert!(matches!(
            done.last(),
            Some(AppEvent::Done { result: Ok(()), .. })
        ));
        // Let a reading after the grant arrive.
        std::thread::sleep(Duration::from_millis(150));
    }

    /// Test: UT-APP-017
    #[test]
    fn a_failed_build_answers_every_command_and_shuts_down() {
        let (wake, wakes) = counting_wake();
        let build: BoxFuture<'static, Result<Deps, String>> =
            Box::pin(async { Err("the OS reports no home directory".to_string()) });
        let (shell, mut port) = Shell::start(build, wake).unwrap();
        let text = "the OS reports no home directory";
        assert_eq!(
            next(&mut port, Duration::from_secs(5)),
            AppEvent::Fatal(text.into())
        );
        port.commands
            .send(Command::Scan {
                id: 1,
                options: ScanOptions::default(),
            })
            .unwrap();
        port.commands
            .send(Command::Connect {
                id: 2,
                identifier: "x".into(),
                reconnect: false,
                limits: Limits::none(),
            })
            .unwrap();
        port.commands
            .send(Command::Disconnect {
                id: 3,
                output_off: false,
            })
            .unwrap();
        let bound = Duration::from_secs(5);
        assert_eq!(
            next(&mut port, bound),
            AppEvent::ScanResult {
                id: 1,
                found: vec![],
                message: Some(text.into())
            }
        );
        assert_eq!(
            next(&mut port, bound),
            AppEvent::Done {
                id: 2,
                what: What::Connect,
                result: Err(ErrorText::app(text))
            }
        );
        assert_eq!(
            next(&mut port, bound),
            AppEvent::Disconnected {
                sid: None,
                text: None,
                off_requested: false,
                output_on: None
            }
        );
        assert!(wakes.load(Ordering::SeqCst) >= 4);
        drop(port.commands);
        let started = StdInstant::now();
        assert_eq!(
            shell.shutdown(Duration::from_secs(3)),
            ShutdownReport::Finished
        );
        assert!(started.elapsed() < Duration::from_millis(100));
    }

    /// Test: UT-APP-017
    #[test]
    fn a_disconnected_worker_shuts_down_at_once() {
        let connector = fast_connector("UT-APP-017b", vec![]);
        let markers = Arc::new(MemoryMarkers::new());
        let (wake, wakes) = counting_wake();
        let (shell, mut port) = Shell::start(mock_build(&connector, &markers), wake).unwrap();
        port.commands
            .send(Command::Connect {
                id: 1,
                identifier: "UT-APP-017b".into(),
                reconnect: false,
                limits: limits(),
            })
            .unwrap();
        let mut events = until(&mut port, |e| matches!(e, AppEvent::Ready { .. }));
        port.commands
            .send(Command::Disconnect {
                id: 2,
                output_off: false,
            })
            .unwrap();
        events.extend(until(&mut port, |e| {
            matches!(e, AppEvent::Disconnected { .. })
        }));
        assert!(wakes.load(Ordering::SeqCst) >= events.len());
        drop(port.commands);
        let started = StdInstant::now();
        assert_eq!(
            shell.shutdown(Duration::from_secs(3)),
            ShutdownReport::Finished
        );
        assert!(started.elapsed() < Duration::from_millis(100));
    }

    /// Test: UT-APP-017
    #[test]
    fn an_exit_with_the_output_off_releases_before_the_runtime_ends() {
        let connector = fast_connector("UT-APP-017c", vec![]);
        let markers = Arc::new(MemoryMarkers::new());
        let (wake, _) = counting_wake();
        let (shell, mut port) = Shell::start(mock_build(&connector, &markers), wake).unwrap();
        connect_and_grant(&mut port, "UT-APP-017c");
        let sent_before = connector.handles()[0].sent().len();
        drop(port.commands);
        assert_eq!(
            shell.shutdown(Duration::from_secs(3)),
            ShutdownReport::Finished
        );
        let after: Vec<(u8, u8)> = connector.handles()[0].sent()[sent_before..]
            .iter()
            .filter(|s| s.frame.opcode() == 0xC8)
            .map(|s| shape(s.frame.payload()))
            .collect();
        assert!(after.iter().any(|s| s.0 == 0), "{after:?}");
        assert!(markers.calls().iter().any(|(_, c)| *c == MarkerCall::Clear));
    }

    /// Test: UT-APP-017
    #[test]
    fn an_exit_with_the_output_on_leaves_it_and_the_marker() {
        let on = fixtures::c3_with(1, 0, 0, 1300, 1000);
        let c2 = crate::worker::worker_tests::reply(0xC2, Duration::from_millis(5), &on);
        let connector = fast_connector("UT-APP-017d", vec![c2]);
        let markers = Arc::new(MemoryMarkers::new());
        let (wake, _) = counting_wake();
        let (shell, mut port) = Shell::start(mock_build(&connector, &markers), wake).unwrap();
        connect_and_grant(&mut port, "UT-APP-017d");
        let sent_before = connector.handles()[0].sent().len();
        drop(port.commands);
        assert_eq!(
            shell.shutdown(Duration::from_secs(3)),
            ShutdownReport::Finished
        );
        let c8_after = connector.handles()[0].sent()[sent_before..]
            .iter()
            .filter(|s| s.frame.opcode() == 0xC8)
            .count();
        assert_eq!(c8_after, 0);
        assert!(!markers.calls().iter().any(|(_, c)| *c == MarkerCall::Clear));
    }

    /// Test: UT-APP-017
    #[test]
    fn a_worker_that_never_starts_times_out() {
        let (wake, _) = counting_wake();
        let build: BoxFuture<'static, Result<Deps, String>> = Box::pin(futures::future::pending());
        let (shell, port) = Shell::start(build, wake).unwrap();
        drop(port.commands);
        let started = StdInstant::now();
        assert_eq!(
            shell.shutdown(Duration::from_millis(200)),
            ShutdownReport::TimedOut
        );
        assert!(started.elapsed() < Duration::from_millis(700));
    }
}
