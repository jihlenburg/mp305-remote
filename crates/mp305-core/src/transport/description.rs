//! What a transport is: its kind and the identifier discovery reported.
//!
//! Implements: DD-TRANS-002.

use core::fmt;

/// The kind of link a transport uses.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum Kind {
    /// Bluetooth LE through the `AF00` service.
    Ble,
    /// USB HID reports.
    Hid,
}

/// A transport's kind and the identifier discovery reported for the supply:
/// the OS peripheral identifier over Bluetooth, the HID path over USB.
#[derive(Clone, Debug, PartialEq, Eq)]
pub struct Description {
    /// The kind of link.
    pub kind: Kind,
    /// The identifier of the supply on this link.
    pub identifier: String,
}

impl fmt::Display for Description {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        let kind = match self.kind {
            Kind::Ble => "ble",
            Kind::Hid => "hid",
        };
        write!(f, "{kind} {}", self.identifier)
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    /// Test: UT-TRANS-001
    #[test]
    fn display_is_kind_and_identifier() {
        let ble = Description {
            kind: Kind::Ble,
            identifier: "72DE66A3".to_string(),
        };
        let hid = Description {
            kind: Kind::Hid,
            identifier: "/dev/hidraw3".to_string(),
        };
        assert_eq!(ble.to_string(), "ble 72DE66A3");
        assert_eq!(hid.to_string(), "hid /dev/hidraw3");
    }
}
