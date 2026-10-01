//! Implements: DD-STORE-004 (`storable`), DD-STORE-005.
//!
//! The mapping from a supply identifier to the file name of its marker, and
//! the rule for which identifiers a marker can hold. A Bluetooth identifier
//! is a UUID, but a HID path on Windows can be 200 characters long and hold
//! characters no file system accepts, so the name is a short readable prefix
//! plus a hash of the whole identifier. The hash constants are part of the
//! on-disk format: changing them would orphan the markers already written.

/// The FNV-1a 64 offset basis, pinned as part of the on-disk format.
const FNV_OFFSET: u64 = 0xcbf2_9ce4_8422_2325;
/// The FNV-1a 64 prime, pinned as part of the on-disk format.
const FNV_PRIME: u64 = 0x0000_0100_0000_01b3;
/// How many characters (Unicode scalar values) of the identifier the name
/// keeps as its readable prefix.
const PREFIX_CHARS: usize = 32;

/// The file name (without extension) of the marker for `identifier`: the
/// first 32 characters of the identifier with every character outside
/// `[A-Za-z0-9._-]` replaced by `_`, then `-`, then the 64-bit FNV-1a hash
/// of the identifier's UTF-8 bytes as 16 lowercase hex characters. The name
/// is at most 49 characters long. A Windows reserved name such as `CON`
/// cannot occur, since the name always continues with `-<hash>`.
///
/// ```
/// use mp305_core::store::names::marker_name;
///
/// assert_eq!(marker_name("a"), "a-af63dc4c8601ec8c");
/// ```
#[must_use]
pub fn marker_name(identifier: &str) -> String {
    let mut name: String = identifier
        .chars()
        .take(PREFIX_CHARS)
        .map(|c| {
            if c.is_ascii_alphanumeric() || matches!(c, '.' | '_' | '-') {
                c
            } else {
                '_'
            }
        })
        .collect();
    name.push('-');
    name.push_str(&format!("{:016x}", fnv1a(identifier.as_bytes())));
    name
}

/// Whether a marker file can give `identifier` back unchanged (DD-STORE-004).
/// The file holds the identifier as one line and is read back after
/// `trim_ascii`, so an identifier that is empty, holds a line break or has
/// ASCII whitespace at its start or end cannot be stored. Whitespace inside
/// the identifier is kept.
///
/// ```
/// use mp305_core::store::names::storable;
///
/// assert_eq!(storable("/dev/hidraw3"), Ok(()));
/// assert_eq!(storable("a\r"), Err("line break"));
/// ```
///
/// # Errors
///
/// The reason, checked in this order: `empty`, `line break` (`\n` or
/// `\r`, so a trailing one is reported as a line break), `surrounding
/// whitespace`.
pub fn storable(identifier: &str) -> Result<(), &'static str> {
    if identifier.is_empty() {
        return Err("empty");
    }
    if identifier.contains(['\n', '\r']) {
        return Err("line break");
    }
    if identifier.trim_ascii() != identifier {
        return Err("surrounding whitespace");
    }
    Ok(())
}

/// The 64-bit FNV-1a hash of `bytes`. `^` and `wrapping_mul` are the
/// algorithm's own arithmetic: the multiplication is defined modulo 2^64.
fn fnv1a(bytes: &[u8]) -> u64 {
    bytes.iter().fold(FNV_OFFSET, |hash, &byte| {
        (hash ^ u64::from(byte)).wrapping_mul(FNV_PRIME)
    })
}

#[cfg(test)]
mod tests {
    use super::*;

    /// Whether `text` is `n` lowercase hex characters.
    fn is_lower_hex(text: &str, n: usize) -> bool {
        text.len() == n
            && text
                .bytes()
                .all(|b| b.is_ascii_digit() || (b'a'..=b'f').contains(&b))
    }

    /// Splits a name at its last `-` into the readable prefix and the hash.
    fn split(name: &str) -> (&str, &str) {
        name.rsplit_once('-').unwrap()
    }

    /// Test: UT-STORE-006
    #[test]
    fn marker_names_follow_the_pinned_format() {
        assert_eq!(marker_name("a"), "a-af63dc4c8601ec8c");
        assert_eq!(marker_name("b"), "b-af63df4c8601f1a5");

        let uuid = "72de66a3-1b2c-4d5e-8f90-abcdef123456";
        let name = marker_name(uuid);
        let (prefix, hash) = split(&name);
        assert_eq!(prefix, &uuid[..32]);
        assert!(is_lower_hex(hash, 16), "{name}");

        let hid =
            r"\\?\hid#vid_28e9&pid_028a#7&2a3b4c5d&0&0000#{4d1e55b2-f16f-11cf-88cb-001111000030}";
        let name = marker_name(hid);
        let (prefix, hash) = split(&name);
        assert_eq!(prefix, "____hid_vid_28e9_pid_028a_7_2a3b");
        assert!(is_lower_hex(hash, 16), "{name}");

        let long = "x".repeat(300);
        let name = marker_name(&long);
        assert!(name.chars().count() <= 49, "{name}");
        let (prefix, hash) = split(&name);
        assert_eq!(prefix, "x".repeat(32));
        assert!(is_lower_hex(hash, 16), "{name}");

        let name = marker_name("é!");
        let (prefix, hash) = split(&name);
        assert_eq!(prefix, "__");
        assert!(is_lower_hex(hash, 16), "{name}");

        for id in ["a", "b", uuid, hid, long.as_str(), "é!"] {
            assert_eq!(marker_name(id), marker_name(id));
        }
    }

    /// Test: UT-STORE-011
    #[test]
    fn storable_accepts_what_a_marker_gives_back_and_names_the_reason_otherwise() {
        assert_eq!(storable("72de66a3-1b2c-4d5e-8f90-abcdef123456"), Ok(()));
        assert_eq!(storable("/dev/hidraw3"), Ok(()));
        assert_eq!(storable(""), Err("empty"));
        assert_eq!(storable(" a"), Err("surrounding whitespace"));
        assert_eq!(storable("a "), Err("surrounding whitespace"));
        assert_eq!(storable("a\tb"), Ok(()));
        assert_eq!(storable("a\nb"), Err("line break"));
        assert_eq!(storable("a\r"), Err("line break"));
        assert_eq!(storable("\n"), Err("line break"));
    }
}
