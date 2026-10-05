//! Implements: DD-STORE-001, DD-STORE-003.
//!
//! The two ways the store writes a file. `write_atomic` replaces a file in
//! one step, so that a crash leaves the old content or the new, never a
//! part. `write_if_absent` creates a file only if it does not exist yet, so
//! that two processes that start on an empty directory at once end with
//! one host ID. Both write the content to a temp file in the same directory
//! first; its name holds the process ID and a process-wide counter, so the
//! app and a script, or two scripts, never write into each other's temp
//! file.

use std::fs::{self, OpenOptions};
use std::io::{self, Write};
use std::path::{Path, PathBuf};
use std::sync::atomic::{AtomicU64, Ordering};

/// The process-wide counter that makes each temp name of this process
/// unique.
static TEMP_COUNTER: AtomicU64 = AtomicU64::new(0);

/// The temp name for a write to `path`: `<path>.<pid>-<n>.tmp`, in the same
/// directory as `path`, with `n` from a process-wide counter. Two calls in
/// one process never return the same name.
pub(crate) fn temp_path(path: &Path) -> PathBuf {
    // `fetch_add` wraps at `u64::MAX`; no process writes that many files.
    let n = TEMP_COUNTER.fetch_add(1, Ordering::Relaxed);
    let mut name = path.as_os_str().to_os_string();
    name.push(format!(".{}-{n}.tmp", std::process::id()));
    PathBuf::from(name)
}

/// Replaces the content of `path` with `bytes` in one step: the content goes
/// to a new temp file (DD-STORE-001), is synced to the disk, and the temp
/// file is renamed over `path`. The rename replaces the file atomically
/// (POSIX `rename`, Windows `MoveFileEx` with replace), and the sync before
/// it makes the rename meaningful after a power loss. The temp file is
/// removed when any step fails.
///
/// # Errors
///
/// The I/O error of the step that failed, for example a Windows sharing
/// violation when another process holds `path` open.
pub(crate) fn write_atomic(path: &Path, bytes: &[u8]) -> io::Result<()> {
    let temp = write_temp(path, bytes)?;
    fs::rename(&temp, path).inspect_err(|_| remove_temp(&temp))
}

/// Creates `path` with `bytes` only if it does not exist yet. Returns `true`
/// when this call created the file and `false` when the file existed; the
/// temp file is removed either way.
///
/// The content goes to a synced temp file first, which is then hard-linked
/// to `path`: the link creates `path` only if it does not exist, and
/// publishes content that is already complete. Where hard links are not
/// supported (FAT, exFAT, some network shares), the fallback opens `path`
/// with `create_new`, which is also create-if-absent, and writes there.
///
/// # Errors
///
/// The I/O error of the temp write, or of the fallback when the link failed
/// for a reason other than an existing `path`.
pub(crate) fn write_if_absent(path: &Path, bytes: &[u8]) -> io::Result<bool> {
    publish(path, bytes, |from, to| fs::hard_link(from, to))
}

/// The body of [`write_if_absent`], with the hard link passed in so that the
/// tests can exercise the fallback on a file system that supports links.
fn publish(
    path: &Path,
    bytes: &[u8],
    link: impl FnOnce(&Path, &Path) -> io::Result<()>,
) -> io::Result<bool> {
    let temp = write_temp(path, bytes)?;
    let linked = link(&temp, path);
    remove_temp(&temp);
    match linked {
        Ok(()) => Ok(true),
        Err(error) if error.kind() == io::ErrorKind::AlreadyExists => Ok(false),
        // No hard links here: `create_new` is the create-if-absent fallback.
        // A write that fails after the creation leaves a partial file, which
        // the next read treats as corrupt and replaces (DD-STORE-002).
        Err(_) => match create_synced(path, bytes) {
            Ok(()) => Ok(true),
            Err(error) if error.kind() == io::ErrorKind::AlreadyExists => Ok(false),
            Err(error) => Err(error),
        },
    }
}

/// Writes `bytes` to a new temp file for `path` and syncs it. Returns the
/// temp file's path. On failure the temp file is removed: its name belongs
/// to this call alone, so removing it never touches another writer's file.
///
/// # Errors
///
/// The I/O error of the creation, the write or the sync.
fn write_temp(path: &Path, bytes: &[u8]) -> io::Result<PathBuf> {
    let temp = temp_path(path);
    match create_synced(&temp, bytes) {
        Ok(()) => Ok(temp),
        Err(error) => {
            remove_temp(&temp);
            Err(error)
        }
    }
}

/// Creates `path`, which must not exist (`create_new`: `O_EXCL` on POSIX,
/// `CREATE_NEW` on Windows), writes `bytes` and syncs the file to the disk.
/// The file is closed on return, so that Windows can rename or remove it.
///
/// # Errors
///
/// `AlreadyExists` when `path` exists, or the I/O error of the write or the
/// sync.
fn create_synced(path: &Path, bytes: &[u8]) -> io::Result<()> {
    let mut file = OpenOptions::new().write(true).create_new(true).open(path)?;
    file.write_all(bytes)?;
    file.sync_all()
}

/// Removes a temp file. A failure is ignored: a leftover temp file is never
/// read, and this process never reuses its name.
fn remove_temp(temp: &Path) {
    let _ = fs::remove_file(temp);
}

#[cfg(test)]
mod tests {
    use super::*;
    use std::fs;

    /// The names of the entries in `dir`, sorted.
    fn entries(dir: &Path) -> Vec<String> {
        let mut names: Vec<String> = fs::read_dir(dir)
            .unwrap()
            .map(|e| e.unwrap().file_name().to_string_lossy().into_owned())
            .collect();
        names.sort();
        names
    }

    /// The `n` of a temp name `<path>.<pid>-<n>.tmp` for `path`, or `None`
    /// when the name has another form or another process ID.
    fn temp_number(path: &Path, temp: &Path) -> Option<u64> {
        let temp = temp.to_str()?;
        let rest = temp.strip_prefix(path.to_str()?)?.strip_prefix('.')?;
        let (pid, n) = rest.strip_suffix(".tmp")?.split_once('-')?;
        (pid.parse::<u32>().ok()? == std::process::id()).then_some(())?;
        n.parse().ok()
    }

    /// Test: UT-STORE-007
    ///
    /// The write is behind: `set` returns `Ok`, and the writer thread logs
    /// the failure at WARN with the error text the synchronous `set`
    /// returned (`marker set failed: store: <path>: <os error>`).
    #[test]
    fn set_fails_when_the_markers_directory_is_a_file() {
        use crate::session::Markers;
        use crate::store::{Store, LOG_TARGET};
        use crate::transport::test_log;

        let log = test_log::install();
        let dir = tempfile::tempdir().unwrap();
        let markers = dir.path().join("markers");
        fs::write(&markers, b"x").unwrap();
        let store = Store::new(dir.path());
        assert_eq!(store.set("a", std::time::UNIX_EPOCH), Ok(()));
        assert!(store.flush(std::time::Duration::from_secs(30)));
        let prefix = format!("marker set failed: store: {}: ", markers.display());
        let warned = log
            .lines(LOG_TARGET)
            .into_iter()
            .filter(|(level, text)| *level == log::Level::Warn && text.starts_with(&prefix))
            .count();
        assert_eq!(warned, 1);
        assert_eq!(fs::read(&markers).unwrap(), b"x");
    }

    /// Test: UT-STORE-007
    #[test]
    fn temp_names_differ_and_writes_leave_no_temp_file() {
        let dir = tempfile::tempdir().unwrap();
        let path = dir.path().join("host_id");

        let first = temp_path(&path);
        let second = temp_path(&path);
        assert_ne!(first, second);
        assert!(temp_number(&path, &first).is_some(), "{}", first.display());
        assert!(
            temp_number(&path, &second).is_some(),
            "{}",
            second.display()
        );
        assert_eq!(first.parent(), path.parent());

        write_atomic(&path, b"one\n").unwrap();
        write_atomic(&path, b"two\n").unwrap();
        assert_eq!(fs::read(&path).unwrap(), b"two\n");
        assert_eq!(entries(dir.path()), vec!["host_id".to_string()]);
    }

    /// Test: UT-STORE-010
    #[test]
    fn write_if_absent_creates_only_a_missing_file() {
        let dir = tempfile::tempdir().unwrap();
        let path = dir.path().join("host_id");

        fs::write(&path, b"old\n").unwrap();
        assert!(!write_if_absent(&path, b"new\n").unwrap());
        assert_eq!(fs::read(&path).unwrap(), b"old\n");
        assert_eq!(entries(dir.path()), vec!["host_id".to_string()]);

        let fresh = dir.path().join("fresh");
        assert!(write_if_absent(&fresh, b"new\n").unwrap());
        assert_eq!(fs::read(&fresh).unwrap(), b"new\n");
        assert_eq!(
            entries(dir.path()),
            vec!["fresh".to_string(), "host_id".to_string()]
        );
    }

    /// Test: UT-STORE-010
    #[test]
    fn write_if_absent_falls_back_to_create_new_without_hard_links() {
        let dir = tempfile::tempdir().unwrap();
        let no_links = |_: &Path, _: &Path| Err(io::Error::from(io::ErrorKind::Unsupported));

        let path = dir.path().join("host_id");
        assert!(publish(&path, b"new\n", no_links).unwrap());
        assert_eq!(fs::read(&path).unwrap(), b"new\n");
        assert_eq!(entries(dir.path()), vec!["host_id".to_string()]);

        assert!(!publish(&path, b"other\n", no_links).unwrap());
        assert_eq!(fs::read(&path).unwrap(), b"new\n");
        assert_eq!(entries(dir.path()), vec!["host_id".to_string()]);

        let missing = dir.path().join("missing").join("host_id");
        assert_eq!(
            write_if_absent(&missing, b"new\n").unwrap_err().kind(),
            io::ErrorKind::NotFound
        );
        assert_eq!(entries(dir.path()), vec!["host_id".to_string()]);
    }
}
