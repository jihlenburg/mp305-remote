//! Implements: DD-DISC-002, DD-DISC-003, DD-DISC-006.
//!
//! The pure part of discovery: the Bluetooth and USB classifiers, the
//! choice of the advertised name, the sighting accumulator that decides
//! which events count as "advertising now", the identifier shape test, the
//! connect plan and the choice of the USB device a connect opens. No
//! function here touches an OS stack; the glue files feed them what the OS
//! reported.

use std::collections::{BTreeSet, HashMap};

use crate::discovery::{Found, LOG_TARGET};
use crate::transport::description::Kind;

/// The company identifier under which the supply sends its manufacturer
/// data (device-model.md 1).
const COMPANY: u16 = 0xABBA;
/// The first two bytes of the supply's manufacturer data.
const DATA_PREFIX: [u8; 2] = [0xAF, 0xFA];
/// The length of the full advertised name, the only one that carries the
/// flag and the unit characters.
const FULL_NAME_LEN: usize = 29;
/// The index of the remote-control flag in the full name.
const FLAG_INDEX: usize = 12;
/// The index of the first of the three unit characters in the full name.
const UNIT_START: usize = 26;
/// The flag character that marks remote control as enabled.
const FLAG_ENABLED: char = 'S';
/// The USB vendor identifier of the supply (device-model.md 1).
const HID_VENDOR: u16 = 0x28E9;
/// The USB product identifier of the supply.
const HID_PRODUCT: u16 = 0x028A;
/// The text the supply's USB product string contains.
const HID_PRODUCT_TEXT: &str = "MP305";
/// The length of a hyphenated UUID (a macOS peripheral identifier).
const UUID_LEN: usize = 36;
/// The positions of the hyphens in a hyphenated UUID.
const UUID_HYPHENS: [usize; 4] = [8, 13, 18, 23];
/// The length of six hex pairs joined by a separator (a Bluetooth
/// address).
const ADDRESS_LEN: usize = 17;

/// Chooses the advertised name: the advertisement name when the OS reported
/// one, else the local name (BlueZ's local name is the user-settable alias,
/// Windows's the cached GAP name).
#[must_use]
pub fn advertised_name(
    advertisement_name: Option<&str>,
    local_name: Option<&str>,
) -> Option<String> {
    advertisement_name.or(local_name).map(str::to_string)
}

/// Whether `name` has the supply's layout: at least 8 characters,
/// characters 0, 1 and 3 are `0`, character 2 is `0` or `3`, characters 4
/// to 7 are `MP30`, byte-exact.
#[must_use]
pub fn name_matches(name: &str) -> bool {
    matches!(
        name.as_bytes().get(..8),
        Some([b'0', b'0', b'0' | b'3', b'0', b'M', b'P', b'3', b'0'])
    )
}

/// The unit characters and the remote-control flag of `name`: the last
/// three characters and whether character 12 is `S` for a 29-character
/// name, nothing for any other length.
fn full_name_parts(name: &str) -> (String, Option<bool>) {
    let chars: Vec<char> = name.chars().collect();
    if chars.len() != FULL_NAME_LEN {
        return (String::new(), None);
    }
    let unit_id = chars
        .get(UNIT_START..)
        .map(|unit| unit.iter().collect())
        .unwrap_or_default();
    let remote_flag = chars.get(FLAG_INDEX).map(|c| *c == FLAG_ENABLED);
    (unit_id, remote_flag)
}

/// Classifies one Bluetooth sighting.
///
/// `name` is the advertised name as [`advertised_name`] chose it. A sighting
/// matches when the name has the supply's layout ([`name_matches`]), or when
/// no name is present and `manufacturer_data` has the company `0xABBA` with
/// a value starting `AF FA`. A present name without the layout vetoes the
/// data match. Rejected sightings are logged at DEBUG.
#[must_use]
pub fn advertisement(
    id: &str,
    name: Option<&str>,
    manufacturer_data: &HashMap<u16, Vec<u8>>,
    rssi: Option<i16>,
) -> Option<Found> {
    let by_name = name.is_some_and(name_matches);
    let by_data = name.is_none()
        && manufacturer_data
            .get(&COMPANY)
            .is_some_and(|value| value.starts_with(&DATA_PREFIX));
    if !by_name && !by_data {
        log::debug!(target: LOG_TARGET, "rejected ble {id} name {name:?}");
        return None;
    }
    let name = name.unwrap_or_default();
    let (unit_id, remote_flag) = full_name_parts(name);
    Some(Found {
        transport: Kind::Ble,
        identifier: id.to_string(),
        unit_id,
        name: name.to_string(),
        rssi,
        remote_flag,
    })
}

/// Whether a USB HID device is a supply: vendor `0x28E9`, product `0x028A`
/// and a product string containing `MP305`.
fn is_supply(vendor_id: u16, product_id: u16, product: Option<&str>) -> bool {
    vendor_id == HID_VENDOR
        && product_id == HID_PRODUCT
        && product.is_some_and(|p| p.contains(HID_PRODUCT_TEXT))
}

/// Classifies one USB HID device: vendor `0x28E9`, product `0x028A` and a
/// product string containing `MP305`. The path is both the identifier and
/// the unit identifier. Rejected devices are logged at DEBUG.
#[must_use]
pub fn hid(vendor_id: u16, product_id: u16, product: Option<&str>, path: &str) -> Option<Found> {
    let name = product.filter(|_| is_supply(vendor_id, product_id, product));
    let Some(name) = name else {
        log::debug!(
            target: LOG_TARGET,
            "rejected hid {path} {vendor_id:04x}:{product_id:04x} product {product:?}"
        );
        return None;
    };
    Some(Found {
        transport: Kind::Hid,
        identifier: path.to_string(),
        unit_id: path.to_string(),
        name: name.to_string(),
        rssi: None,
        remote_flag: None,
    })
}

/// What the OS reported about a peripheral during a scan, as the
/// accumulator sees it.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum SightingEvent {
    /// The peripheral was discovered.
    Discovered,
    /// The peripheral's properties were updated.
    Updated,
    /// A new RSSI value arrived.
    Rssi,
    /// Manufacturer data arrived.
    ManufacturerData,
    /// Any other event about the peripheral.
    Other,
}

/// The accumulator the Bluetooth scan feeds: which peripherals count as
/// advertising now.
///
/// A peripheral the adapter did not hold before the scan counts on
/// `Discovered`, `Updated`, `Rssi` or `ManufacturerData`. A peripheral it
/// already held counts only on `Rssi` or `ManufacturerData`, since BlueZ
/// replays its cache as `Discovered` and a cached device seen again often
/// produces only RSSI or manufacturer-data changes. `Other` never counts.
#[derive(Clone, Debug, Default)]
pub struct Sightings {
    /// The ids the adapter held before the scan started.
    known: BTreeSet<String>,
    /// The ids counted so far, for the membership test.
    counted: BTreeSet<String>,
    /// The ids counted so far, in order of first counting.
    seen: Vec<String>,
}

impl Sightings {
    /// An accumulator with the ids the adapter held before the scan.
    #[must_use]
    pub fn new(known: BTreeSet<String>) -> Self {
        Self {
            known,
            counted: BTreeSet::new(),
            seen: Vec::new(),
        }
    }

    /// Notes `event` for `id` and returns whether `id` is now counted as
    /// advertising. An id already counted stays counted. Events that do not
    /// count are logged at DEBUG.
    pub fn note(&mut self, id: &str, event: SightingEvent) -> bool {
        if self.counted.contains(id) {
            return true;
        }
        let counts = match event {
            SightingEvent::Rssi | SightingEvent::ManufacturerData => true,
            SightingEvent::Discovered | SightingEvent::Updated => !self.known.contains(id),
            SightingEvent::Other => false,
        };
        if counts {
            self.counted.insert(id.to_string());
            self.seen.push(id.to_string());
        } else {
            log::debug!(target: LOG_TARGET, "event {event:?} from {id} not counted");
        }
        counts
    }

    /// The counted ids in order of first counting, each once.
    #[must_use]
    pub fn seen(&self) -> Vec<String> {
        self.seen.clone()
    }
}

/// Whether `s` has the shape of a Bluetooth peripheral identifier: a
/// hyphenated UUID (macOS), `AA:BB:CC:DD:EE:FF` (Windows) or
/// `hci<n>/dev_AA_BB_CC_DD_EE_FF` (Linux), hex digits of either case. A HID
/// path never has these shapes.
#[must_use]
pub fn looks_like_ble_id(s: &str) -> bool {
    is_uuid(s) || is_address(s, b':') || is_bluez_path(s)
}

/// Whether `s` is a hyphenated UUID: 36 characters, `-` at positions 8,
/// 13, 18 and 23, hex digits elsewhere.
fn is_uuid(s: &str) -> bool {
    s.len() == UUID_LEN
        && s.bytes().enumerate().all(|(i, b)| {
            if UUID_HYPHENS.contains(&i) {
                b == b'-'
            } else {
                b.is_ascii_hexdigit()
            }
        })
}

/// Whether `s` is six hex pairs joined by `separator`: 17 characters with
/// the separator at every third position.
fn is_address(s: &str, separator: u8) -> bool {
    s.len() == ADDRESS_LEN
        && s.bytes().enumerate().all(|(i, b)| {
            if i.checked_rem(3) == Some(2) {
                b == separator
            } else {
                b.is_ascii_hexdigit()
            }
        })
}

/// Whether `s` is a BlueZ device path as the Linux backend writes it (the
/// `/org/bluez/` prefix stripped): `hci<n>/dev_` and six hex pairs joined
/// by `_`.
fn is_bluez_path(s: &str) -> bool {
    let Some((adapter, address)) = s
        .strip_prefix("hci")
        .and_then(|rest| rest.split_once("/dev_"))
    else {
        return false;
    };
    !adapter.is_empty() && adapter.bytes().all(|b| b.is_ascii_digit()) && is_address(address, b'_')
}

/// How `connect` reaches an identifier.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum Plan {
    /// The adapter knows the identifier: find it advertising, then connect.
    BleKnown,
    /// A HID path the enumeration returned: open it.
    HidPath,
    /// A Bluetooth identifier the adapter does not know yet: find it
    /// advertising, then connect.
    BleFind,
    /// Neither: report "no supply found".
    NotFound,
}

/// Decides how to reach `identifier`: [`Plan::BleKnown`] when `ble_known`
/// contains it, else [`Plan::HidPath`] when `hid_paths` contains it, else
/// [`Plan::BleFind`] when it has a Bluetooth shape ([`looks_like_ble_id`]),
/// else [`Plan::NotFound`].
#[must_use]
pub fn connect_plan(identifier: &str, ble_known: &[String], hid_paths: &[String]) -> Plan {
    let listed = |list: &[String]| list.iter().any(|entry| entry == identifier);
    if listed(ble_known) {
        Plan::BleKnown
    } else if listed(hid_paths) {
        Plan::HidPath
    } else if looks_like_ble_id(identifier) {
        Plan::BleFind
    } else {
        Plan::NotFound
    }
}

/// One enumerated USB HID device, as the OS reported it.
#[derive(Clone, Debug, PartialEq, Eq)]
pub struct HidEntry {
    /// The device path as text, the identifier over USB.
    pub path: String,
    /// The USB vendor identifier.
    pub vendor_id: u16,
    /// The USB product identifier.
    pub product_id: u16,
    /// The product string, when the device reported one.
    pub product: Option<String>,
}

/// Why a connect runs.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum Purpose {
    /// The caller's connect: only the exact identifier is reached
    /// (SR-004).
    First,
    /// The session's automatic reconnection after a link loss: over USB a
    /// supply whose path changed is reached as well, see [`hid_target`].
    Again,
}

/// The USB device a connect opens.
#[derive(Clone, Debug, PartialEq, Eq)]
pub enum HidTarget {
    /// The device at the identifier's path.
    Exact,
    /// On a reconnect, the one supply listed, at a path other than the
    /// identifier.
    Moved {
        /// The supply's path now.
        path: String,
    },
    /// No device to open: report "no supply found".
    NotFound,
}

/// Decides which enumerated USB device a connect to `identifier` opens.
///
/// On [`Purpose::First`]: [`HidTarget::Exact`] when a device has the path
/// `identifier`, whatever it reports, as a first connect always did; else
/// [`HidTarget::NotFound`].
///
/// On [`Purpose::Again`]: [`HidTarget::Exact`] when a device that classifies
/// as a supply (the rule of [`hid`]) has the path `identifier`. A path that
/// now belongs to another device counts as gone, since Linux reuses
/// `hidraw` numbers. Else [`HidTarget::Moved`] when exactly one listed
/// device classifies as a supply, logged at WARN with the old and the new
/// path: the path changes when the cable is replugged or the supply
/// restarts, and the supply has no USB serial number. Else
/// [`HidTarget::NotFound`], with no supply or more than one listed.
pub fn hid_target<'a>(
    identifier: &str,
    devices: impl IntoIterator<Item = &'a HidEntry>,
    purpose: Purpose,
) -> HidTarget {
    let mut supplies = Vec::new();
    for device in devices {
        let supply = is_supply(
            device.vendor_id,
            device.product_id,
            device.product.as_deref(),
        );
        if device.path == identifier && (supply || purpose == Purpose::First) {
            return HidTarget::Exact;
        }
        if supply {
            supplies.push(device.path.as_str());
        }
    }
    match (purpose, supplies.as_slice()) {
        (Purpose::Again, [path]) => {
            log::warn!(
                target: LOG_TARGET,
                "the USB path of the supply changed from {identifier} to {path}"
            );
            HidTarget::Moved {
                path: (*path).to_string(),
            }
        }
        _ => HidTarget::NotFound,
    }
}

#[cfg(test)]
pub(crate) mod tests {
    use super::*;

    /// The advertised name of the capture: 29 characters, `S` at index 12,
    /// unit characters `E!K` (LOGBOOK 2026-09-29).
    pub(crate) const CAPTURE_NAME: &str = "0000MP305B  S             E!K";

    /// The manufacturer data of the capture: company `0xABBA`, then
    /// `AF FA 01 35 02 00` and 14 zero bytes (LOGBOOK 2026-09-29).
    pub(crate) fn capture_data() -> HashMap<u16, Vec<u8>> {
        let mut value = vec![0xAF, 0xFA, 0x01, 0x35, 0x02, 0x00];
        value.extend([0u8; 14]);
        HashMap::from([(0xABBA, value)])
    }

    /// Manufacturer data with one company and one value.
    fn data(company: u16, value: &[u8]) -> HashMap<u16, Vec<u8>> {
        HashMap::from([(company, value.to_vec())])
    }

    /// A Bluetooth `Found` with the given fields.
    fn ble(
        id: &str,
        unit_id: &str,
        name: &str,
        rssi: Option<i16>,
        remote_flag: Option<bool>,
    ) -> Found {
        Found {
            transport: Kind::Ble,
            identifier: id.to_string(),
            unit_id: unit_id.to_string(),
            name: name.to_string(),
            rssi,
            remote_flag,
        }
    }

    /// Test: UT-DISC-001
    #[test]
    fn advertisement_matches_by_name_layout_or_by_data_without_a_name() {
        assert_eq!(CAPTURE_NAME.chars().count(), 29);
        assert_eq!(capture_data().get(&0xABBA).map(Vec::len), Some(20));
        let empty = HashMap::new();
        assert_eq!(
            advertisement("id1", Some(CAPTURE_NAME), &capture_data(), Some(-61)),
            Some(ble("id1", "E!K", CAPTURE_NAME, Some(-61), Some(true)))
        );
        assert_eq!(
            advertisement("id2", Some(CAPTURE_NAME), &empty, None),
            Some(ble("id2", "E!K", CAPTURE_NAME, None, Some(true)))
        );
        assert_eq!(
            advertisement("id3", None, &capture_data(), Some(-70)),
            Some(ble("id3", "", "", Some(-70), None))
        );
        assert_eq!(
            advertisement("id4", None, &data(0xABBA, &[0xAF, 0xFA]), None),
            Some(ble("id4", "", "", None, None))
        );
        assert_eq!(
            advertisement("id5", Some("0000MP30"), &empty, None),
            Some(ble("id5", "", "0000MP30", None, None))
        );
        assert_eq!(advertisement("id6", Some("0000MP3"), &empty, None), None);
        assert_eq!(
            advertisement("id7", Some("0000mp305B  S             E!K"), &empty, None),
            None
        );
        assert_eq!(
            advertisement("id8", Some("Nordic"), &data(0x0059, &[0xAF, 0xFA]), None),
            None
        );
        assert_eq!(
            advertisement("id9", Some("Other"), &capture_data(), None),
            None
        );
        assert_eq!(
            advertisement("id10", None, &data(0xABBA, &[0xAF, 0xFB, 0x01]), None),
            None
        );
        assert_eq!(
            advertisement("id11", None, &data(0xABBA, &[0xAF]), None),
            None
        );
    }

    /// Test: UT-DISC-002
    #[test]
    fn flag_unit_layout_rule_and_name_choice() {
        // The capture name with a space at index 12.
        let no_flag = CAPTURE_NAME.replacen('S', " ", 1);
        assert_eq!(no_flag.chars().count(), 29);
        assert_eq!(no_flag.chars().nth(12), Some(' '));
        assert_eq!(
            advertisement("a", Some(&no_flag), &capture_data(), None),
            Some(ble("a", "E!K", &no_flag, None, Some(false)))
        );
        // The capture name with character 2 set to `3`.
        let chip_flag = CAPTURE_NAME.replacen("0000", "0030", 1);
        assert!(chip_flag.starts_with("0030MP305B"));
        assert_eq!(chip_flag.chars().count(), 29);
        assert_eq!(
            advertisement("b", Some(&chip_flag), &capture_data(), None),
            Some(ble("b", "E!K", &chip_flag, None, Some(true)))
        );
        assert!(name_matches("0000MP30"));
        assert!(!name_matches("0030MP3"));
        let short = "0000MP305B  X";
        assert_eq!(short.chars().count(), 13);
        assert_eq!(
            advertisement("c", Some(short), &HashMap::new(), None),
            Some(ble("c", "", short, None, None))
        );
        assert_eq!(
            advertised_name(Some("adv"), Some("alias")),
            Some("adv".to_string())
        );
        assert_eq!(
            advertised_name(None, Some("alias")),
            Some("alias".to_string())
        );
        assert_eq!(advertised_name(None, None), None);
    }

    /// Test: UT-DISC-003
    #[test]
    fn hid_matches_vendor_product_and_product_string() {
        let path = "/dev/hidraw3";
        let usb = |name: &str| Found {
            transport: Kind::Hid,
            identifier: path.to_string(),
            unit_id: path.to_string(),
            name: name.to_string(),
            rssi: None,
            remote_flag: None,
        };
        assert_eq!(
            hid(0x28E9, 0x028A, Some("MP305B"), path),
            Some(usb("MP305B"))
        );
        assert_eq!(hid(0x28E9, 0x1234, Some("MP305B"), path), None);
        assert_eq!(hid(0x28E9, 0x028A, None, path), None);
        assert_eq!(
            hid(0x28E9, 0x028A, Some("MP305A  "), path),
            Some(usb("MP305A  "))
        );
        assert_eq!(hid(0x1234, 0x028A, Some("MP305B"), path), None);
    }

    /// Test: UT-DISC-007
    #[test]
    fn sightings_count_cached_ids_only_on_evidence_of_advertising() {
        use SightingEvent::{Discovered, ManufacturerData, Other, Rssi, Updated};
        let mut sightings = Sightings::new(BTreeSet::from(["k1".to_string()]));
        let notes = [
            sightings.note("k1", Discovered),
            sightings.note("n1", Discovered),
            sightings.note("k1", Rssi),
            sightings.note("n2", Updated),
            sightings.note("n1", ManufacturerData),
            sightings.note("n3", Other),
            sightings.note("k2", ManufacturerData),
        ];
        assert_eq!(notes, [false, true, true, true, true, false, true]);
        assert_eq!(sightings.seen(), ["n1", "k1", "n2", "k2"]);
    }

    /// Test: UT-DISC-008
    #[test]
    fn identifier_shapes_and_the_connect_plan() {
        let shapes = [
            "72de66a3-1b2c-4d5e-8f90-abcdef123456",
            "AA:BB:CC:DD:EE:FF",
            "hci0/dev_AA_BB_CC_DD_EE_FF",
            "/dev/hidraw3",
            r"\\?\hid#vid_28e9&pid_028a#7&2a3b4c5d&0&0000#{4d1e55b2-f16f-11cf-88cb-001111000030}",
            "72DE66A3-1B2C-4D5E-8F90-ABCDEF123456",
            "72DE66A3-1B2C-4D5E-8F90-ABCDEF12345",
            "",
        ];
        assert_eq!(shapes[5].len(), 36);
        assert_eq!(shapes[6].len(), 35);
        assert_eq!(
            shapes.map(looks_like_ble_id),
            [true, true, true, false, false, true, false, false]
        );
        let ids = |list: &[&str]| list.iter().map(|s| s.to_string()).collect::<Vec<_>>();
        assert_eq!(connect_plan("x", &ids(&["x"]), &[]), Plan::BleKnown);
        assert_eq!(connect_plan("p", &[], &ids(&["p"])), Plan::HidPath);
        assert_eq!(
            connect_plan("72de66a3-1b2c-4d5e-8f90-abcdef123456", &[], &[]),
            Plan::BleFind
        );
        assert_eq!(
            connect_plan("/dev/hidraw9", &[], &ids(&["/dev/hidraw3"])),
            Plan::NotFound
        );
    }

    /// An enumerated USB device: a supply when `supply` is set, a keyboard
    /// of another vendor otherwise.
    fn entry(path: &str, supply: bool) -> HidEntry {
        if supply {
            HidEntry {
                path: path.to_string(),
                vendor_id: 0x28E9,
                product_id: 0x028A,
                product: Some("MP305B".to_string()),
            }
        } else {
            HidEntry {
                path: path.to_string(),
                vendor_id: 0x05AC,
                product_id: 0x024F,
                product: Some("Keyboard".to_string()),
            }
        }
    }

    /// Test: UT-DISC-015
    #[test]
    fn hid_target_takes_the_exact_path_in_both_purposes() {
        let listed = [entry("DevSrvsID:1", false), entry("DevSrvsID:2", true)];
        for purpose in [Purpose::First, Purpose::Again] {
            assert_eq!(
                hid_target("DevSrvsID:2", &listed, purpose),
                HidTarget::Exact
            );
        }
        // A first connect opens the exact path whatever the device reports.
        assert_eq!(
            hid_target("DevSrvsID:1", &listed, Purpose::First),
            HidTarget::Exact
        );
    }

    /// Test: UT-DISC-015
    #[test]
    fn hid_target_on_a_reconnect_never_opens_another_device_at_the_old_path() {
        // The old path now names a keyboard and the supply moved.
        let moved = [entry("/dev/hidraw3", false), entry("/dev/hidraw5", true)];
        assert_eq!(
            hid_target("/dev/hidraw3", &moved, Purpose::Again),
            HidTarget::Moved {
                path: "/dev/hidraw5".to_string()
            }
        );
        // The old path names a keyboard and no supply is listed.
        let gone = [entry("/dev/hidraw3", false)];
        assert_eq!(
            hid_target("/dev/hidraw3", &gone, Purpose::Again),
            HidTarget::NotFound
        );
    }

    /// Test: UT-DISC-015
    #[test]
    fn hid_target_takes_the_one_moved_supply_only_on_a_reconnect() {
        let log = crate::transport::test_log::install();
        let listed = [entry("/dev/hidraw0", false), entry("/dev/hidraw4", true)];
        assert_eq!(
            hid_target("/dev/hidraw3", &listed, Purpose::First),
            HidTarget::NotFound
        );
        assert_eq!(
            hid_target("/dev/hidraw3", &listed, Purpose::Again),
            HidTarget::Moved {
                path: "/dev/hidraw4".to_string()
            }
        );
        assert!(log.lines_here(LOG_TARGET).iter().any(|(l, m)| {
            *l == log::Level::Warn
                && m == "the USB path of the supply changed from /dev/hidraw3 to /dev/hidraw4"
        }));
    }

    /// Test: UT-DISC-015
    #[test]
    fn hid_target_finds_nothing_with_no_supply_or_two() {
        let two = [entry("DevSrvsID:7", true), entry("DevSrvsID:8", true)];
        let none = [entry("DevSrvsID:7", false)];
        let other_product = [HidEntry {
            product: Some("Other".to_string()),
            ..entry("DevSrvsID:9", true)
        }];
        let no_product = [HidEntry {
            product: None,
            ..entry("DevSrvsID:9", true)
        }];
        for purpose in [Purpose::First, Purpose::Again] {
            for listed in [&two[..], &none, &other_product, &no_product, &[]] {
                assert_eq!(
                    hid_target("DevSrvsID:1", listed, purpose),
                    HidTarget::NotFound
                );
            }
        }
    }
}
