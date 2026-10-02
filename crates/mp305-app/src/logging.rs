//! Implements: DD-APP-033.
//!
//! The logger set-up: `RUST_LOG` picks the filter (`info` when unset or
//! empty), `MP305_LOG_FILE` a file to append to instead of stderr, and
//! every line carries a millisecond timestamp (SR-039, ST-038). The file
//! works also for the macOS bundle started from a terminal and for the
//! Windows build without a console.

use std::fs::OpenOptions;
use std::path::PathBuf;

/// The filter when `RUST_LOG` is unset or empty.
const DEFAULT_FILTER: &str = "info";

/// What [`init`] sets up.
#[derive(Clone, Debug, PartialEq, Eq)]
pub struct LogConfig {
    /// The `env_logger` filter.
    pub filter: String,
    /// The file to append to; `None` for stderr.
    pub file: Option<PathBuf>,
}

/// The configuration from the values of `RUST_LOG` and `MP305_LOG_FILE`.
#[must_use]
pub fn config(rust_log: Option<String>, log_file: Option<String>) -> LogConfig {
    LogConfig {
        filter: rust_log
            .filter(|f| !f.is_empty())
            .unwrap_or_else(|| DEFAULT_FILTER.to_string()),
        file: log_file.filter(|f| !f.is_empty()).map(PathBuf::from),
    }
}

/// Installs the logger from the environment. A file that does not open is
/// reported on stderr, which is then used; an installed logger is not an
/// error.
pub fn init() {
    let config = config(
        std::env::var("RUST_LOG").ok(),
        std::env::var("MP305_LOG_FILE").ok(),
    );
    let mut builder = env_logger::Builder::new();
    builder.parse_filters(&config.filter);
    builder.format_timestamp_millis();
    if let Some(path) = &config.file {
        match OpenOptions::new().append(true).create(true).open(path) {
            Ok(file) => {
                builder.target(env_logger::Target::Pipe(Box::new(file)));
            }
            Err(e) => {
                eprintln!(
                    "mp305-app: the log file {} does not open ({e}); logging to stderr",
                    path.display()
                );
            }
        }
    }
    let _ = builder.try_init();
}

/// Logs at ERROR that the window could not run, for `ui::launch`
/// (DD-APP-030), so that `ui/` names no logging crate (DD-APP-050).
pub fn launch_failed(error: &dyn core::fmt::Display) {
    log::error!(target: LOG_TARGET, "the app could not run: {error}");
}

/// The log target of the app's start and end.
pub const LOG_TARGET: &str = "mp305_app::launch";

#[cfg(test)]
mod tests {
    use super::*;

    /// Test: UT-APP-022
    #[test]
    fn the_configuration_from_the_environment() {
        let info = LogConfig {
            filter: "info".to_string(),
            file: None,
        };
        assert_eq!(config(None, None), info);
        assert_eq!(config(Some(String::new()), Some(String::new())), info);
        assert_eq!(
            config(
                Some("mp305_app::frames=trace".to_string()),
                Some("/tmp/l.log".to_string())
            ),
            LogConfig {
                filter: "mp305_app::frames=trace".to_string(),
                file: Some(PathBuf::from("/tmp/l.log")),
            }
        );
    }
}
