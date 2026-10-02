//! Integration test IT-032 (AR-032): the pure parts of discovery fed with
//! the captured advertisement, USB descriptors and sighting events: the
//! Bluetooth and USB classifiers and the sighting accumulator.
#![allow(
    clippy::unwrap_used,
    clippy::expect_used,
    clippy::indexing_slicing,
    clippy::arithmetic_side_effects,
    clippy::panic,
    missing_docs
)]

use std::collections::{BTreeSet, HashMap};

use mp305_core::discovery::classify::{self, SightingEvent, Sightings};
use mp305_core::discovery::Found;
use mp305_core::transport::description::Kind;

/// The advertised name of the supply in
/// `docs/research/captures/2026-09-29T193614-ble-readonly.jsonl` (the meta
/// line's `name`): 29 characters, the remote-control flag `S` at index 12,
/// the unit characters `E!K`.
const CAPTURE_NAME: &str = "0000MP305B  S             E!K";

/// The manufacturer data of the same advertisement (LOGBOOK 2026-09-29):
/// company `0xABBA`, `AF FA 01 35 02 00` and 14 zero bytes.
fn capture_data() -> HashMap<u16, Vec<u8>> {
    let mut value = vec![0xAF, 0xFA, 0x01, 0x35, 0x02, 0x00];
    value.extend([0u8; 14]);
    HashMap::from([(0xABBA, value)])
}

/// Test: IT-032
#[test]
fn the_bluetooth_classifier_matches_by_name_or_by_data_without_a_name() {
    assert_eq!(CAPTURE_NAME.chars().count(), 29);
    let none = HashMap::new();
    let found = |id: &str, name: &str, rssi: Option<i16>, flag: Option<bool>, unit: &str| Found {
        transport: Kind::Ble,
        identifier: id.to_string(),
        unit_id: unit.to_string(),
        name: name.to_string(),
        rssi,
        remote_flag: flag,
    };
    // The name with the data, and the name alone.
    assert_eq!(
        classify::advertisement("p1", Some(CAPTURE_NAME), &capture_data(), Some(-61)),
        Some(found("p1", CAPTURE_NAME, Some(-61), Some(true), "E!K"))
    );
    assert_eq!(
        classify::advertisement("p2", Some(CAPTURE_NAME), &none, None),
        Some(found("p2", CAPTURE_NAME, None, Some(true), "E!K"))
    );
    // The data alone: no name, no unit characters, no flag.
    assert_eq!(
        classify::advertisement("p3", None, &capture_data(), None),
        Some(found("p3", "", None, None, ""))
    );
    // An unrelated name, with the data and alone.
    assert_eq!(
        classify::advertisement("p4", Some("Nordic_UART"), &capture_data(), Some(-50)),
        None
    );
    assert_eq!(
        classify::advertisement("p5", Some("Nordic_UART"), &none, None),
        None
    );
}

/// Test: IT-032
#[test]
fn the_usb_classifier_matches_the_vendor_and_product() {
    let path = "/dev/hidraw3";
    assert_eq!(
        classify::hid(0x28E9, 0x028A, Some("MP305B"), path),
        Some(Found {
            transport: Kind::Hid,
            identifier: path.to_string(),
            unit_id: path.to_string(),
            name: "MP305B".to_string(),
            rssi: None,
            remote_flag: None,
        })
    );
    assert_eq!(classify::hid(0x28E9, 0x1234, Some("MP305B"), path), None);
}

/// Test: IT-032
#[test]
fn the_accumulator_counts_a_known_id_only_on_evidence_of_advertising() {
    let mut sightings = Sightings::new(BTreeSet::from(["known".to_string()]));
    assert!(!sightings.note("known", SightingEvent::Discovered));
    assert!(sightings.note("known", SightingEvent::ManufacturerData));
    assert!(sightings.note("new", SightingEvent::Discovered));
    assert_eq!(
        sightings.seen(),
        vec!["known".to_string(), "new".to_string()]
    );
}
