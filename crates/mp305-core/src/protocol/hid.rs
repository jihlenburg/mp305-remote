//! The USB HID wire form: the framed stream with `AA` doubling, split into
//! report payloads, and the resynchronising stream decoder.
//!
//! Implements: DD-PROTO-010, DD-PROTO-011, DD-PROTO-012.

use crate::protocol::error::Reason;
use crate::protocol::frame::Frame;

/// The start-of-frame byte. It is never doubled at position 0 and doubled
/// everywhere else in the stream.
pub const START: u8 = 0xAA;
/// The address of every request: source 1 (the USB host), destination 2 (the
/// main MCU).
pub const REQUEST_ADDRESS: u8 = 0x12;
/// The address of every reply: the nibbles of the request swapped.
pub const REPLY_ADDRESS: u8 = 0x21;
/// The most stream bytes one output report carries after `01, n`.
pub const REPORT_PAYLOAD: usize = 62;

/// The 8-bit wrapping sum over the address, the length and the body
/// (opcode and payload), computed over the unstuffed bytes.
#[must_use]
pub fn checksum(address: u8, length: u8, body: &[u8]) -> u8 {
    body.iter().fold(address.wrapping_add(length), |sum, byte| {
        sum.wrapping_add(*byte)
    })
}

/// The stream of `frame` as a request (address `0x12`), split into the
/// payloads of consecutive output reports: each `Vec` holds the `n` stream
/// bytes that follow `01, n` in one report, at most 62 of them.
///
/// Every `AA` after the leading one is doubled: address, length, body and
/// checksum included (device-model.md 2.2).
#[must_use]
pub fn encode(frame: &Frame) -> Vec<Vec<u8>> {
    // The frame type bounds the payload at 254 bytes, so the length fits.
    let length = u8::try_from(frame.payload().len().saturating_add(1)).unwrap_or(u8::MAX);
    let mut body = Vec::with_capacity(frame.payload().len().saturating_add(1));
    body.push(frame.opcode());
    body.extend_from_slice(frame.payload());
    let sum = checksum(REQUEST_ADDRESS, length, &body);
    let mut stream = Vec::with_capacity(body.len().saturating_add(8));
    stream.push(START);
    for byte in [REQUEST_ADDRESS, length]
        .into_iter()
        .chain(body)
        .chain([sum])
    {
        stream.push(byte);
        if byte == START {
            stream.push(START);
        }
    }
    stream.chunks(REPORT_PAYLOAD).map(<[u8]>::to_vec).collect()
}

/// Where the decoder is inside a frame.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
enum State {
    /// Between frames.
    Idle,
    /// The next data byte is the length.
    Length,
    /// Collecting `remaining` body bytes.
    Body,
    /// The next data byte is the checksum.
    Checksum,
}

/// A resynchronising parser of the reply stream, fed with the stream bytes
/// of input reports in any split.
///
/// It follows the device's own parser (protocol.md 2.2, firmware.md "Frame
/// parser"): an `AA` toggles a pending flag; a non-`AA` byte with the flag
/// set starts a frame with that byte as the address, in every state; a
/// non-`AA` byte with the flag clear is consumed in the current state; an
/// `AA` with the flag set is the data byte `AA`. The address is judged when
/// the frame completes, so a foreign address never breaks resynchronisation.
///
/// | Position | Byte |
/// |---|---|
/// | 0 | `AA`, never doubled |
/// | 1 | address, `0x21` in replies |
/// | 2 | length: opcode through the last payload byte |
/// | 3 | opcode |
/// | 4 .. | payload |
/// | last | checksum over address, length, opcode and payload |
///
/// See docs/research/protocol.md, section 2.2.
#[derive(Debug)]
pub struct Decoder {
    /// The current state.
    state: State,
    /// An `AA` was seen and not yet resolved as a start or a data byte.
    aa_pending: bool,
    /// The address of the frame in progress.
    address: u8,
    /// The length byte of the frame in progress.
    length: u8,
    /// Body bytes still to collect.
    remaining: usize,
    /// The body collected so far.
    body: Vec<u8>,
    /// Bytes skipped in `Idle` since the last result.
    skipped: u64,
    /// Bytes skipped in `Idle` since the decoder was created.
    skipped_total: u64,
}

impl Default for Decoder {
    fn default() -> Self {
        Self::new()
    }
}

impl Decoder {
    /// A decoder between frames.
    #[must_use]
    pub fn new() -> Self {
        Self {
            state: State::Idle,
            aa_pending: false,
            address: 0,
            length: 0,
            remaining: 0,
            body: Vec::new(),
            skipped: 0,
            skipped_total: 0,
        }
    }

    /// Bytes skipped between frames since the decoder was created.
    #[must_use]
    pub fn skipped_total(&self) -> u64 {
        self.skipped_total
    }

    /// Feeds stream bytes and returns every frame or error they completed,
    /// in order. A [`Reason::Skipped`] precedes the first result after bytes
    /// were skipped between frames.
    pub fn push(&mut self, bytes: &[u8]) -> Vec<Result<Frame, Reason>> {
        let mut out = Vec::new();
        for &byte in bytes {
            if byte == START && !self.aa_pending {
                self.aa_pending = true;
                continue;
            }
            if byte != START && self.aa_pending {
                // A lone AA followed by this byte: a frame starts here.
                self.aa_pending = false;
                if self.state != State::Idle {
                    out.push(Err(Reason::Restarted));
                }
                self.start(byte);
                continue;
            }
            // Either a doubled AA (the data byte AA) or a plain data byte.
            self.aa_pending = false;
            self.consume(byte, &mut out);
        }
        out
    }

    /// Opens a frame whose address byte is `address`.
    fn start(&mut self, address: u8) {
        self.address = address;
        self.body.clear();
        self.state = State::Length;
    }

    /// Emits the pending skip count, if any, before `result`.
    fn emit(&mut self, result: Result<Frame, Reason>, out: &mut Vec<Result<Frame, Reason>>) {
        if self.skipped > 0 {
            out.push(Err(Reason::Skipped(self.skipped)));
            self.skipped = 0;
        }
        out.push(result);
        self.state = State::Idle;
    }

    /// Handles one data byte in the current state.
    fn consume(&mut self, byte: u8, out: &mut Vec<Result<Frame, Reason>>) {
        match self.state {
            State::Idle => {
                self.skipped = self.skipped.saturating_add(1);
                self.skipped_total = self.skipped_total.saturating_add(1);
            }
            State::Length => {
                if byte == 0 {
                    self.emit(
                        Err(Reason::BadLength {
                            expected: 1,
                            got: 0,
                        }),
                        out,
                    );
                    return;
                }
                self.length = byte;
                self.remaining = usize::from(byte);
                self.state = State::Body;
            }
            State::Body => {
                self.body.push(byte);
                self.remaining = self.remaining.saturating_sub(1);
                if self.remaining == 0 {
                    self.state = State::Checksum;
                }
            }
            State::Checksum => {
                let expected = checksum(self.address, self.length, &self.body);
                let result = if byte != expected {
                    Err(Reason::BadChecksum {
                        expected,
                        got: byte,
                    })
                } else if self.address != REPLY_ADDRESS {
                    Err(Reason::BadAddress(self.address))
                } else {
                    let (opcode, payload) = self.body.split_at(1);
                    match opcode.first() {
                        Some(&opcode) => Frame::new(opcode, payload.to_vec()),
                        None => Err(Reason::BadLength {
                            expected: 1,
                            got: 0,
                        }),
                    }
                };
                self.emit(result, out);
            }
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::protocol::error::Reason;
    use crate::protocol::frame::Frame;

    /// The payload of the first `0xC3` of `2026-09-29T193614-ble-readonly.jsonl`
    /// (t = 12.8857), without the AF01 tag and the opcode.
    const C3_PAYLOAD: [u8; 36] = [
        0x00, 0x00, 0x5A, 0x00, 0x00, 0x14, 0x05, 0x00, 0x00, 0xE8, 0x03, 0x01, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x01, 0x1A, 0x00,
        0x00, 0x01, 0x40, 0x06, 0x00, 0x00,
    ];

    /// A reply stream as the bridge sends it: address `0x21`, `AA` doubled.
    fn reply_stream(opcode: u8, payload: &[u8]) -> Vec<u8> {
        stream_with_address(REPLY_ADDRESS, opcode, payload)
    }

    fn stream_with_address(address: u8, opcode: u8, payload: &[u8]) -> Vec<u8> {
        let length = (payload.len() + 1) as u8;
        let mut body = vec![opcode];
        body.extend_from_slice(payload);
        let sum = checksum(address, length, &body);
        let mut out = vec![START];
        for byte in [address, length].into_iter().chain(body).chain([sum]) {
            out.push(byte);
            if byte == START {
                out.push(START);
            }
        }
        out
    }

    fn frame(opcode: u8, payload: &[u8]) -> Frame {
        Frame::new(opcode, payload.to_vec()).unwrap()
    }

    fn c8_170() -> Frame {
        frame(
            0xC8,
            &[
                0x01, 0xAA, 0x00, 0xE8, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00,
            ],
        )
    }

    /// Test: UT-PROTO-010
    #[test]
    fn encode_frames_doubles_aa_and_sums_unstuffed_bytes() {
        assert_eq!(
            encode(&frame(0xC4, &[])),
            vec![vec![0xAA, 0x12, 0x01, 0xC4, 0xD7]]
        );
        assert_eq!(
            encode(&c8_170()),
            vec![vec![
                0xAA, 0x12, 0x0C, 0xC8, 0x01, 0xAA, 0xAA, 0x00, 0xE8, 0x03, 0x03, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x7F
            ]]
        );
        assert_eq!(
            encode(&frame(0x97, &[])),
            vec![vec![0xAA, 0x12, 0x01, 0x97, 0xAA, 0xAA]]
        );
    }

    /// Test: UT-PROTO-011
    #[test]
    fn encode_splits_into_reports_of_at_most_62_bytes() {
        let reports = encode(&frame(0x01, &[0; 58]));
        assert_eq!(
            reports.iter().map(Vec::len).collect::<Vec<_>>(),
            vec![62, 1]
        );
        let reports = encode(&frame(0x01, &[0; 119]));
        assert_eq!(
            reports.iter().map(Vec::len).collect::<Vec<_>>(),
            vec![62, 62]
        );
    }

    /// Test: UT-PROTO-012
    #[test]
    fn decoder_yields_one_frame_for_every_split() {
        let stream = reply_stream(0xC3, &C3_PAYLOAD);
        assert_eq!(stream.len(), 41);
        for chunk in 1..=stream.len() {
            let mut decoder = Decoder::new();
            let results: Vec<_> = stream.chunks(chunk).flat_map(|c| decoder.push(c)).collect();
            assert_eq!(
                results,
                vec![Ok(frame(0xC3, &C3_PAYLOAD))],
                "chunk size {chunk}"
            );
        }
    }

    /// Test: UT-PROTO-013
    #[test]
    fn decoder_reports_a_bad_checksum_and_returns_to_idle() {
        let mut stream = reply_stream(0xC3, &C3_PAYLOAD);
        let expected = *stream.last().unwrap();
        *stream.last_mut().unwrap() = 0x00;
        let mut decoder = Decoder::new();
        assert_eq!(
            decoder.push(&stream),
            vec![Err(Reason::BadChecksum { expected, got: 0 })]
        );
        assert_eq!(
            decoder.push(&reply_stream(0xC4, &[])),
            vec![Ok(frame(0xC4, &[]))]
        );
    }

    /// Test: UT-PROTO-013
    #[test]
    fn decoder_rejects_length_zero_at_once() {
        let mut decoder = Decoder::new();
        assert_eq!(
            decoder.push(&[0xAA, 0x21, 0x00, 0x21]),
            vec![Err(Reason::BadLength {
                expected: 1,
                got: 0
            })]
        );
    }

    /// Test: UT-PROTO-013
    #[test]
    fn decoder_rejects_a_foreign_address_after_the_whole_frame() {
        let mut decoder = Decoder::new();
        let stream = stream_with_address(0x12, 0xC3, &C3_PAYLOAD);
        assert_eq!(decoder.push(&stream), vec![Err(Reason::BadAddress(0x12))]);
        assert_eq!(
            decoder.push(&reply_stream(0xC4, &[])),
            vec![Ok(frame(0xC4, &[]))]
        );
    }

    /// Test: UT-PROTO-013
    #[test]
    fn a_lone_aa_restarts_the_frame() {
        let mut stream = vec![0xAA, 0x21, 0x25, 0xC3];
        stream.extend_from_slice(&C3_PAYLOAD[..10]);
        stream.extend_from_slice(&[0xAA, 0x21, 0x01, 0xC4, 0xE6]);
        let mut decoder = Decoder::new();
        assert_eq!(
            decoder.push(&stream),
            vec![Err(Reason::Restarted), Ok(frame(0xC4, &[]))]
        );
    }

    /// Test: UT-PROTO-013
    #[test]
    fn garbage_before_a_frame_is_skipped_and_counted() {
        let mut stream = vec![0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07];
        stream.extend(reply_stream(0xC3, &C3_PAYLOAD));
        let mut decoder = Decoder::new();
        assert_eq!(
            decoder.push(&stream),
            vec![Err(Reason::Skipped(7)), Ok(frame(0xC3, &C3_PAYLOAD))]
        );
        assert_eq!(decoder.skipped_total(), 7);
    }

    /// Test: UT-PROTO-013
    #[test]
    fn a_doubled_aa_outside_a_frame_starts_nothing() {
        let mut stream = vec![0xAA, 0xAA];
        stream.extend(reply_stream(0xC4, &[])[1..].iter());
        let mut decoder = Decoder::new();
        assert_eq!(decoder.push(&stream), vec![]);
        assert_eq!(
            decoder.push(&reply_stream(0xC4, &[])),
            vec![Err(Reason::Skipped(5)), Ok(frame(0xC4, &[]))]
        );
    }

    /// Test: UT-PROTO-013
    #[test]
    fn doubled_aa_in_payload_and_checksum_decode_to_one_aa() {
        let mut decoder = Decoder::new();
        assert_eq!(
            decoder.push(&reply_stream(0xC5, &[0x01, 0xAA])),
            vec![Ok(frame(0xC5, &[0x01, 0xAA]))]
        );
        // 0x21 + 0x01 + 0x88 = 0xAA: the checksum itself is doubled.
        assert_eq!(
            reply_stream(0x88, &[]),
            vec![0xAA, 0x21, 0x01, 0x88, 0xAA, 0xAA]
        );
        assert_eq!(
            decoder.push(&reply_stream(0x88, &[])),
            vec![Ok(frame(0x88, &[]))]
        );
    }
}
