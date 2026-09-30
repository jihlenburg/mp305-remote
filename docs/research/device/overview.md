# Device facts and identification gaps

Updated 2026-09-30. This page distinguishes the user's observed unit,
manufacturer specifications and firmware-derived component candidates.

## Observed unit

**Confirmed on hardware:** the existing Bluetooth captures report model
MP305B, System Version **1.6.0.40**, and the four bytes `02 00 02 00`
that WebLink labels Firmware Version. See LOGBOOK 2026-09-29,
“Corrections, second round”, and [protocol identity details](../protocol.md).
The interpretation of which chip owns each version remains separate
from the bytes observed. No new hardware session occurred in this pass.

**Confirmed in code:** the analyzed update contains main application
version **1.6.0.51**, an 8051 PD program and an RV32 BLE/USB program.
The update must not be treated as a dump of the running V1.6.0.40 unit.

## Manufacturer specifications

These are **inferred for the user's unit**, based on manufacturer claims;
they are not measured performance or board inspection.

| Item | Published specification |
|---|---|
| MR30 output | 0..30 V, 0..5 A, 150 W; 10 mV and 1 mA adjustment |
| Battery | 14.4 V, 4900 mAh, 70.56 Wh; four series 21700 cells |
| Controls | 2.8-inch touch display, rotary control, function/power and output buttons |
| Front USB-C | Output up to 140 W; fixed 5/9/12/15 V at 3 A, 20/28 V at 5 A; PPS 5..21 V at 5 A |
| Rear USB-C on MP305B | Power input, up to 140 W |
| Modes/storage | DC supply, program, USB-C PD and charger; ten presets/profiles and 100 program points |
| Cooling/feedback | Fan and buzzer |
| Size/mass | 138 x 86.5 x 70 mm; 828 g, tolerance 10% |

Sources: [ISDT product page](https://www.isdt.co/mp305.html?lang=en) and
[ISDT manual](https://www.isdt.co/down/pdf/MP305.pdf), English panel diagram
on PDF page 15 and specification table on PDF page 23, one-based page
numbers. The downloaded manual has 72 pages and was inspected as rendered
images because it contains no usable extracted text.

The manual gives voltage/current accuracy below ±0.5%, noise below
2 mV RMS/3 mA RMS, response below 90 microseconds and operation at
0..40 °C. Those are manufacturer specifications, not verified limits.
Its mounting description mixes “1/4 inch” with “M6, 1.27 pitch”; the
actual thread standard remains unresolved. [Manual](https://www.isdt.co/down/pdf/MP305.pdf).

## USB port distinction

The manual labels the rear connector as wired communication for MP305A
and power input for MP305B. V51's companion code nevertheless contains
USB HID descriptors and handlers. Code presence does not prove that a
user-accessible MP305B connector exposes those data lines. USB enumeration,
board routing and model-specific population remain open, including TBD-013.
[Manual](https://www.isdt.co/down/pdf/MP305.pdf),
[firmware USB evidence](../firmware/architecture.md#usb-and-gatt-tables).

## Parts inferred from firmware

| Function | Candidate | Confidence and discriminator |
|---|---|---|
| Main MCU | HDSC HC32 family | Family resemblance; conflicting peripheral/RAM maps prevent exact identification |
| BLE/USB MCU | WCH CH58x family | Strong SDK, instruction-set and register evidence; exact variant unknown |
| PD MCU | Unidentified 8051 controller | Architecture and PD role supported; `P829` is a firmware string |
| Current monitor | INA226-compatible | Strong register/address/word-order match; read device ID or inspect marking |
| Two power-control domains | SC8815-compatible | Strong fixed-address/reference-register match on separate buses; inspect topology |
| Display controller | JD9853-compatible | Initialization signature and geometry match; panel identification remains open |
| Touch controller | CST8xx-compatible | Address and coordinate format match; chip ID needed |
| Nonvolatile storage | SPI NOR-compatible | Command protocol established; JEDEC ID/capacity unresolved |
| RGB indicators | 24-bit serial LED family | Waveform generation supports inference; package and color order unknown |

The detailed evidence and alternatives are in [hardware.md](hardware.md),
[the bus map](buses.md) and [UI/analog interfaces](ui-and-analog.md).
This table is not a bill of materials. MOSFETs, inductors, shunts, op-amps,
protection ICs, passive values and board revisions cannot yet be assigned.
