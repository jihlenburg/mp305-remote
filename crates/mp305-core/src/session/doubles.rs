//! Implements: DD-SESS-001 (the doubles).
//!
//! Test doubles for what the session takes from outside: a connector over
//! the scripted mock transport and an in-memory marker store. Compiled for
//! tests and the `mock` feature, so the integration tests reach them too.

use std::collections::BTreeMap;
use std::sync::Mutex;
use std::time::SystemTime;

use futures::future::BoxFuture;

use crate::error::Error;
use crate::session::{lock, Connector, Markers};
use crate::transport::guarded::Guarded;
use crate::transport::mock::{Mock, MockHandle};
use crate::transport::AnyTransport;

/// What one connection attempt yields.
type Attempts = Box<dyn FnMut() -> Result<Mock, Error> + Send>;

/// A [`Connector`] that calls a closure per `connect` and wraps the mock it
/// returns in a guard; a returned `Err` is the connector's error. The
/// handle of every mock is kept for the test.
pub struct MockConnector {
    /// The closure called per attempt.
    attempts: Mutex<Attempts>,
    /// The handles of the mocks handed out, in order.
    handles: Mutex<Vec<MockHandle>>,
}

impl MockConnector {
    /// A connector that calls `attempts` once per `connect`.
    pub fn new(attempts: impl FnMut() -> Result<Mock, Error> + Send + 'static) -> Self {
        Self {
            attempts: Mutex::new(Box::new(attempts)),
            handles: Mutex::new(Vec::new()),
        }
    }

    /// The handles of the mocks handed out so far, in order.
    #[must_use]
    pub fn handles(&self) -> Vec<MockHandle> {
        lock(&self.handles).clone()
    }
}

impl Connector for MockConnector {
    fn connect<'a>(
        &'a self,
        _identifier: &'a str,
    ) -> BoxFuture<'a, Result<Guarded<AnyTransport>, Error>> {
        let attempt = (lock(&self.attempts))();
        let result = attempt.map(|mock| {
            lock(&self.handles).push(mock.handle());
            Guarded::new(AnyTransport::from(mock))
        });
        Box::pin(async move { result })
    }
}

/// One call of the [`Markers`] trait, as [`MemoryMarkers`] records it.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum MarkerCall {
    /// `present`.
    Present,
    /// `set` with its time.
    Set(SystemTime),
    /// `clear`.
    Clear,
}

/// A [`Markers`] store in memory with a call log and a failure switch.
#[derive(Debug, Default)]
pub struct MemoryMarkers {
    /// The markers by identifier.
    markers: Mutex<BTreeMap<String, SystemTime>>,
    /// Every call, in order.
    calls: Mutex<Vec<(String, MarkerCall)>>,
    /// The error the next call fails with.
    fail_next: Mutex<Option<Error>>,
}

impl MemoryMarkers {
    /// An empty store.
    #[must_use]
    pub fn new() -> Self {
        Self::default()
    }

    /// A store that holds a marker for `identifier` written at `at`, as a
    /// previous session that ended uncleanly would have left it.
    #[must_use]
    pub fn holding(identifier: &str, at: SystemTime) -> Self {
        let store = Self::default();
        lock(&store.markers).insert(identifier.to_string(), at);
        store
    }

    /// Every call so far, in order, failed ones included.
    #[must_use]
    pub fn calls(&self) -> Vec<(String, MarkerCall)> {
        lock(&self.calls).clone()
    }

    /// Makes the next call fail with `error`.
    pub fn fail_next(&self, error: Error) {
        *lock(&self.fail_next) = Some(error);
    }

    /// Records a call and returns the error it must fail with, if any.
    fn record(&self, identifier: &str, call: MarkerCall) -> Result<(), Error> {
        lock(&self.calls).push((identifier.to_string(), call));
        match lock(&self.fail_next).take() {
            Some(error) => Err(error),
            None => Ok(()),
        }
    }
}

impl Markers for MemoryMarkers {
    fn present(&self, identifier: &str) -> Result<Option<SystemTime>, Error> {
        self.record(identifier, MarkerCall::Present)?;
        Ok(lock(&self.markers).get(identifier).copied())
    }

    fn set(&self, identifier: &str, at: SystemTime) -> Result<(), Error> {
        self.record(identifier, MarkerCall::Set(at))?;
        lock(&self.markers).insert(identifier.to_string(), at);
        Ok(())
    }

    fn clear(&self, identifier: &str) -> Result<(), Error> {
        self.record(identifier, MarkerCall::Clear)?;
        lock(&self.markers).remove(identifier);
        Ok(())
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::protocol::ble::{BleRoute, Route};
    use crate::protocol::ops::telemetry;
    use crate::transport::description::Kind;
    use crate::transport::mock::Script;
    use std::time::UNIX_EPOCH;

    /// Test: UT-SESS-047
    #[tokio::test(start_paused = true)]
    async fn the_doubles_hand_out_mocks_errors_and_markers() {
        let mut n = 0;
        let connector = MockConnector::new(move || {
            n += 1;
            if n == 2 {
                Err(Error::Transport {
                    message: "no adapter".to_string(),
                })
            } else {
                Ok(Mock::new(Kind::Ble, "m", Script::default()))
            }
        });
        let first = connector.connect("m").await.unwrap();
        assert_eq!(first.description().kind, Kind::Ble);
        assert_eq!(
            connector.connect("m").await.err(),
            Some(Error::Transport {
                message: "no adapter".to_string()
            })
        );
        let second = connector.connect("m").await.unwrap();
        let handles = connector.handles();
        assert_eq!(handles.len(), 2);
        second
            .send(&telemetry::request(), Route::Ble(BleRoute::Af01))
            .await
            .unwrap();
        assert!(handles[0].sent().is_empty());
        assert_eq!(handles[1].sent().len(), 1);
        drop(first);

        let markers = MemoryMarkers::new();
        let at = UNIX_EPOCH;
        markers.fail_next(Error::Store {
            message: "disk full".to_string(),
        });
        assert_eq!(
            markers.set("m", at),
            Err(Error::Store {
                message: "disk full".to_string()
            })
        );
        assert_eq!(markers.set("m", at), Ok(()));
        assert_eq!(markers.present("m"), Ok(Some(at)));
        assert_eq!(
            markers.calls(),
            vec![
                ("m".to_string(), MarkerCall::Set(at)),
                ("m".to_string(), MarkerCall::Set(at)),
                ("m".to_string(), MarkerCall::Present),
            ]
        );
    }
}
