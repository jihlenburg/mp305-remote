//! Does `hidapi` on macOS survive being used from a thread after the thread
//! that used it first has ended? See the README.
//!
//! fresh:   every round on a new thread that ends afterwards.
//! owner:   one thread that lives for the whole run does every round.
//! alive:   the first thread stays alive, the later rounds use new threads.
//! library: every round is a USB scan through `mp305-core`, on a new thread
//!          with its own Tokio runtime; both end after the round.
use std::sync::mpsc;
use std::thread;
use std::time::Duration;

use mp305_core::discovery::{Discovery, ScanOptions};

const ROUNDS: usize = 6;

fn list(tag: &str) {
    let api = hidapi::HidApi::new().expect("hidapi");
    println!("{tag}: {} devices", api.device_list().count());
}

fn library_scan(round: usize) {
    let runtime = tokio::runtime::Builder::new_current_thread()
        .enable_all()
        .build()
        .expect("runtime");
    let found = runtime.block_on(async {
        let mut options = ScanOptions::default();
        options.bluetooth = false;
        options.usb = true;
        Discovery::new().await.expect("discovery").scan(options).await.expect("scan")
    });
    println!("library {round}: {} supplies over USB", found.len());
}

fn main() {
    let mode = std::env::args().nth(1).unwrap_or_else(|| "fresh".into());
    match mode.as_str() {
        "fresh" => {
            for round in 0..ROUNDS {
                thread::spawn(move || list(&format!("fresh {round}"))).join().expect("join");
                thread::sleep(Duration::from_millis(200));
            }
        }
        "owner" => {
            let (tx, rx) = mpsc::channel::<(usize, mpsc::Sender<()>)>();
            thread::spawn(move || {
                for (round, done) in rx {
                    list(&format!("owner {round}"));
                    let _ = done.send(());
                }
            });
            for round in 0..ROUNDS {
                // The requests come from new threads, as they would from a pool.
                let tx = tx.clone();
                thread::spawn(move || {
                    let (done, wait) = mpsc::channel();
                    tx.send((round, done)).expect("send");
                    wait.recv().expect("reply");
                })
                .join()
                .expect("join");
                thread::sleep(Duration::from_millis(200));
            }
        }
        "alive" => {
            let (ready, wait) = mpsc::channel();
            thread::spawn(move || {
                list("alive 0");
                ready.send(()).expect("send");
                loop {
                    thread::park();
                }
            });
            wait.recv().expect("first");
            for round in 1..ROUNDS {
                thread::spawn(move || list(&format!("alive {round}"))).join().expect("join");
                thread::sleep(Duration::from_millis(200));
            }
        }
        "library" => {
            for round in 0..ROUNDS {
                thread::spawn(move || library_scan(round)).join().expect("join");
                thread::sleep(Duration::from_millis(200));
            }
        }
        other => panic!("unknown mode {other}"),
    }
    println!("{mode}: finished without a crash");
}
