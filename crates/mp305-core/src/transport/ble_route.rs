//! The characteristic UUIDs of the `AF00` service and their routes.
//!
//! Implements: DD-TRANS-011 (the pure part).

use uuid::{uuid, Uuid};

use crate::protocol::ble::BleRoute;

/// The `AF00` service.
pub const AF00: Uuid = uuid!("0000af00-0000-1000-8000-00805f9b34fb");
/// The command and reply characteristic.
pub const AF01: Uuid = uuid!("0000af01-0000-1000-8000-00805f9b34fb");
/// The bind characteristic.
pub const AF02: Uuid = uuid!("0000af02-0000-1000-8000-00805f9b34fb");

/// The route of a characteristic, `None` for any other UUID.
#[must_use]
pub fn route_of(uuid: &Uuid) -> Option<BleRoute> {
    if *uuid == AF01 {
        Some(BleRoute::Af01)
    } else if *uuid == AF02 {
        Some(BleRoute::Af02)
    } else {
        None
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::protocol::ble::BleRoute;

    /// Test: UT-TRANS-010
    #[test]
    fn route_of_maps_the_two_characteristics() {
        assert_eq!(route_of(&AF01), Some(BleRoute::Af01));
        assert_eq!(route_of(&AF02), Some(BleRoute::Af02));
        assert_eq!(
            route_of(&uuid::uuid!("00002a23-0000-1000-8000-00805f9b34fb")),
            None
        );
    }
}
