# Hardware buses and likely attached parts

Updated 2026-09-30, MP305B V51. Addresses are processor addresses. Register
accesses, arguments and byte order are **confirmed in code** where stated.
Component names and physical signal assignments are **inferred** unless
explicitly confirmed on hardware. No new hardware observations were made.
See the [hardware map](hardware.md), [register index](registers.md)
and [RTOS resource map](../firmware/rtos.md).

## Main processor UARTs

Three distinct register blocks and receive paths are present. Logical
protocol routes carried by one UART must not be counted as separate buses.

| Register base | Initialization | Configured baud | Receive path | GPIO port index and bit, mux code | Inferred endpoint |
|---|---|---:|---|---|---|
| `0x4001CC00` | `0x644A4` | 115200 | `0x1EF0C`, decoder channel 0, parser `0x11900` | 3.9 / `0x20`, 3.8 / `0x21` | PD companion, from the downstream state parser |
| `0x4001D400` | `0x1787C` | 115200 | `0x1EF5C`, decoder channel 1 | 2.0 / `0x20`, 2.1 / `0x21` | BLE/USB bridge; framing and route behavior agree across the two images |
| `0x40021000` | `0x27D24` | 1000000 at application startup | `0x1F048`, text-line buffer | 0.9 / `0x26`, 0.10 / `0x27` | Text/debug connection; connector and external use unresolved |

The first two use DMA base `0x40053400`, channels 0 and 1 respectively,
with UART data addresses `0x4001CC04` and `0x4001D404`. Their interrupt
registration includes receive, error and transmit callbacks at priority
argument 15. The first UART registers selectors `0x12C/12D/12F`; the
second registers `0x14C/14D/14F`. These selector values and the NVIC
channel numbers are different namespaces.

The second UART demultiplexes sources 6, 1, 5 and 3 into four mailboxes
starting at `0x1FFF9660`, stride 260 bytes. Source 3 opcode `0x55` has
a handshake path and opcode `0x11` reaches `0x13C88`. These four routes
share one physical UART. The BLE firmware adds an internal route byte
for AF01 versus AF02 and removes it before the appropriate notification.

The third UART treats CR as a line terminator and ignores LF. Its buffer
at `0x1FFF8A8C` is 512 bytes; status, length and cursor are at
`0x1FFE0148/14A/14C`. This strongly suggests a console or factory interface,
but its command consumers and physical accessibility need further tracing.

GPIO indices above are firmware arguments, not package pin numbers or
verified board labels. TX/RX direction must be assigned using the exact
MCU mux table once its identity is established.

## Hardware I²C

`0x161C0` initializes the controller at **`0x4004E400`** with a target
rate of **380000 Hz**. The observed pin selections are port 3 bit 2,
mux `0x33`, and port 2 bit 12, mux `0x32`. Which is SCL and SDA depends
on the unresolved MCU mux table. The address helper `0x16360` writes
`(address7 << 1) | read_bit` to `0x4004E424`, establishing seven-bit
address interpretation independently of peripheral naming.

`0x163A4` writes a buffer. `0x16468` writes a register/address prefix and
reads a response with a repeated start. Both take the same mutex and wait
for an interrupt-generated completion event, with 100-tick timeouts.
IRQ callbacks are `0x160CC`, `0x16538`, `0x165A8` and `0x16650`.
See [resource and callback details](../firmware/rtos.md).

### Address 0x40: INA226-compatible monitor

Confirmed in code:

| Function or register | Behavior |
|---|---|
| `0x16C9A` | Write register address followed by a 16-bit value, most significant byte first |
| `0x16C6A` | Write one register address, read two bytes, convert big-endian value |
| Initialization `0x1DF40` | Write configuration register 0, calibration register 5 with `0x0800`, set bit `0x0400` in register 6 |
| Register 2 | Read by `0x15FBC` and `0x15FE0`; voltage scaling includes `raw * 125 / 10` |
| Register 4 | Signed current read in `0x16024`; scale state includes float bits `0x43505556` (approximately 208.33334) |
| Register 6 | Read by `0x19F4C` as status/control information |

**Strong inference:** this is an INA226-compatible current/power monitor.
The seven-bit address, big-endian words, bus-voltage register, signed
current register, calibration register and mask register match TI's
[INA226 datasheet](https://www.ti.com/lit/ds/symlink/ina226.pdf).
Those combined matches are stronger than the address alone. A compatible
part or clone remains possible. The precise shunt resistance, board
connection, calibration accuracy and installed part marking are unknown.
Do not infer a resistor value from the calibration word without resolving
the complete current scaling and units.

### Address 0x74: SC8815-compatible power controller

`0x1BCBA(reg,value)` sends two bytes through the hardware I²C writer to
address `0x74`. `0x12C98` reads an eight-bit register. `0x12CB0` selects
this path when its first argument is nonzero.

`0x19116(selector,target)` computes, with unsigned arithmetic:

```text
code = (target * 5 + 5) / 10 - 1
if code > 1023: code = 1023
write register 3 = code >> 2
write register 4 = (code & 3) << 6
```

**Strong inference:** the endpoint implements the SC8815 register
interface. Southchip specifies address `0x74`, external voltage-reference
registers 3 and 4, and the same 8-plus-2-bit packing. Its reference formula
is `(code + 1) * 2 mV`. This explains the firmware's conversion, subject
to the external feedback network and the input variable's scaling.
Source: Southchip's [SC8815 datasheet, register tables 4 and 5](https://datasheet.lcsc.com/datasheet/pdf/166c1651342e6c0583cf5aa024478e9d.pdf),
manufacturer-authored document served by LCSC. The downloaded PDF is
hashed in the source manifest; no board identification is claimed.

The subtraction is unsigned: input zero underflows and is clamped to
1023. Preserve that behavior in reconstruction. Whether real callers
can pass zero while the converter is enabled needs a separate call-path
check; this arithmetic observation is not an observed output fault.

## Software I²C: a second endpoint at 0x74

`0x16694` initializes a bit-banged bus context at `0x1FFF8F64`:

| Context offset | Value | Meaning from usage |
|---|---|---|
| 0 | `0x74` | Seven-bit slave address |
| 1 | 2 | SDA GPIO port index |
| 2 | 2 | SCL GPIO port index |
| 4, 16-bit | `0x0400` | SDA mask, bit 10 |
| 6, 16-bit | `0x0800` | SCL mask, bit 11 |

START is `0x38EE2`, STOP is `0x38F22`, transmit-byte is `0x38E9E`,
read-byte is `0x38DF6` and ACK sampling is `0x38F48`. GPIO transitions
and eight-bit loops establish I²C behavior directly. Delay helper
`0x144FC(5)` is used repeatedly; its argument does not by itself establish
a measured bus rate.

`0x16C0E` writes address, register and value, sampling but discarding ACK
results, then returns zero. `0x16A6E` performs register selection followed
by a repeated-start read and final NACK. `0x12CB0` and `0x12C98` choose
this bus when selector is zero.

**Strong inference:** there are two separately addressed SC8815-compatible
control domains, one on each bus. Both receive the same register protocol.
Separate pins explain why both may use fixed address `0x74`. Firmware
alone does not prove two physical packages, their board locations, or
which belongs to battery charging, MR30 regulation or USB-C power.
Trace both selector values through complete power-state paths before
assigning those physical roles.

## SPI nonvolatile storage

`0x1BE28` initializes register block `0x4001C800`. Mux selections are
port 1 bits 0, 1 and 2 with function codes `0x2E`, `0x2F` and `0x30`.
Transactions drive port 2 bit 5 low before transfer and high afterwards.
`0x12D10` transmits and `0x12CEC` receives. SPI mode, clock rate and
package pin numbers still need exact register-field decoding.

The command set, 24-bit addresses and status-bit polling strongly imply
SPI NOR storage. The [storage operation and offset tables](hardware.md#serial-nonvolatile-storage)
record reads, writes, erases and update areas. The original-instruction
[storage checks](../firmware/v51/canonical/verification/storage-emulation.json) confirm
command formatting with the byte-transfer functions substituted. They
do not establish the installed flash manufacturer, capacity or timing.

## Mapping the three images

| Hardware or interface | Main ARM | PD 8051 | BLE RV32 | Remaining inference |
|---|---|---|---|---|
| BLE radio and GATT | Receives bridged commands | No reviewed role | GATT table, AF01/AF02 handlers, WCH library calls | Exact CH58x variant and RF implementation |
| USB HID | Same bridged command handling | No reviewed role | Descriptors, endpoint handlers, 62-byte queued chunks | Physical USB data connector on MP305B |
| Main-to-bridge serial | `0x4001D400`, framed decoder channel 1 | No reviewed role | Queue, framing and route translation | Exact board pins at bridge end |
| Main-to-PD serial | `0x4001CC00`, parser `0x11900` | Serial and PD state-machine code | No reviewed role | Full byte-level endpoint equivalence and wiring |
| USB-C negotiation | Main consumes companion status | PD/PPS/EPR/AVS message and state-machine evidence | No reviewed negotiation role | Which connector and CC PHY each state machine controls |
| Current monitor | I²C address `0x40` | No reviewed role | No reviewed role | INA226-compatible part and sensing point |
| Power converter controls | Two buses, address `0x74` on each | Power-path interaction not fully traced | No reviewed role | SC8815-compatible domains and physical topology |
| Serial nonvolatile store | SPI commands and persistent tables | Update image staged by main | Separate host-ID storage API | Separate flash chips versus shared implementation |
| Display, touch, controls | LVGL and GPIO/control workers | No reviewed UI role | No reviewed UI role | Controller parts, pinout and complete access paths |
| Battery protection, fan, buzzer | Status/control candidates | Possible power-state role | No reviewed role | Exact analog circuitry and signal assignments |

“No reviewed role” leaves indirect and unreviewed paths open. It must not
be treated as a proof that an image never interacts with that hardware.
