//! Implements: DD-APP-009.
//!
//! The directories the app uses: the state directory the store keeps the
//! host ID and the unclean-exit markers in (the one the Python library
//! uses too, DD-PY-005, so the app and a script share them), and the
//! directory and file name of a recording.

use std::path::{Path, PathBuf};
use std::time::{SystemTime, UNIX_EPOCH};

use directories::UserDirs;
use mp305_core::civil;

use crate::texts;

/// The state directory: the core's rule (`mp305_core::store::default_dir`,
/// DD-STORE-007), which the Python library uses too.
///
/// # Errors
///
/// [`texts::NO_HOME`] when the OS reports no home directory.
pub fn state_dir() -> Result<PathBuf, String> {
    mp305_core::store::default_dir().ok_or_else(|| texts::NO_HOME.to_string())
}

/// Where recordings go by default: the documents directory, else the home
/// directory, else `.`.
#[must_use]
pub fn recording_dir() -> PathBuf {
    UserDirs::new().map_or_else(
        || PathBuf::from("."),
        |dirs| dirs.document_dir().unwrap_or(dirs.home_dir()).to_path_buf(),
    )
}

/// `dir` joined with `mp305-YYYYMMDD-HHMMSS.csv` for `at` in UTC.
#[must_use]
pub fn default_recording_path(dir: &Path, at: SystemTime) -> PathBuf {
    let seconds = at
        .duration_since(UNIX_EPOCH)
        .map_or(0, |since| since.as_secs());
    let c = civil::from_unix(seconds);
    dir.join(format!(
        "mp305-{:04}{:02}{:02}-{:02}{:02}{:02}.csv",
        c.year, c.month, c.day, c.hour, c.minute, c.second
    ))
}

#[cfg(test)]
mod tests {
    use super::*;
    use core::time::Duration;
    use std::time::UNIX_EPOCH;

    /// Test: UT-APP-022
    #[test]
    fn the_state_directory_is_the_one_of_the_core() {
        assert_eq!(
            state_dir().ok(),
            mp305_core::store::default_dir(),
            "the app and the library share one state directory"
        );
    }

    /// Test: UT-APP-022
    #[test]
    fn the_default_recording_name_is_the_utc_time() {
        let at = |secs: u64| UNIX_EPOCH + Duration::from_secs(secs);
        assert_eq!(
            default_recording_path(Path::new("/rec"), at(1_790_848_800)),
            PathBuf::from("/rec/mp305-20261001-100000.csv")
        );
        assert_eq!(
            default_recording_path(Path::new("/rec"), at(1_798_761_599)),
            PathBuf::from("/rec/mp305-20261231-235959.csv")
        );
    }
}
