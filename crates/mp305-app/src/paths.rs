//! Implements: DD-APP-009.
//!
//! The directories the app uses: the state directory the store keeps the
//! host ID and the unclean-exit markers in (the one the Python library
//! uses too, DD-PY-005, so the app and a script share them), and the
//! directory and file name of a recording.

use std::path::{Path, PathBuf};
use std::time::{SystemTime, UNIX_EPOCH};

use directories::{ProjectDirs, UserDirs};
use mp305_core::civil;

use crate::texts;

/// The state directory from what `ProjectDirs` reports: its `state_dir()`
/// when the OS has one (Linux), else its `data_local_dir()`.
///
/// # Errors
///
/// [`texts::NO_HOME`] when the OS reports no home directory (`None`).
pub fn state_dir_from(dirs: Option<(Option<PathBuf>, PathBuf)>) -> Result<PathBuf, String> {
    match dirs {
        Some((Some(state), _)) => Ok(state),
        Some((None, data_local)) => Ok(data_local),
        None => Err(texts::NO_HOME.to_string()),
    }
}

/// The state directory of `ProjectDirs::from("", "", "mp305")`.
///
/// # Errors
///
/// [`texts::NO_HOME`] when the OS reports no home directory.
pub fn state_dir() -> Result<PathBuf, String> {
    state_dir_from(ProjectDirs::from("", "", "mp305").map(|dirs| {
        (
            dirs.state_dir().map(Path::to_path_buf),
            dirs.data_local_dir().to_path_buf(),
        )
    }))
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
    fn the_state_directory_prefers_the_state_dir() {
        assert_eq!(
            state_dir_from(Some((Some(PathBuf::from("/s")), PathBuf::from("/d")))),
            Ok(PathBuf::from("/s"))
        );
        assert_eq!(
            state_dir_from(Some((None, PathBuf::from("/d")))),
            Ok(PathBuf::from("/d"))
        );
        assert_eq!(
            state_dir_from(None),
            Err("the OS reports no home directory".to_string())
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
