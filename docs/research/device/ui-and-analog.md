# Display, touch and analog interfaces

Updated 2026-10-04. MP305B V51 main processor addresses are used throughout.
Numeric accesses and call sequences below are **confirmed in code**.
Physical component and signal names remain **inferred** where stated.

## Front-panel controls while remote control is granted

**Confirmed in code, reviewed 2026-10-04:** the UI blocks ordinary
front-panel actions while `remote_granted` is set and offers a dialog to
give control back to the front panel. The relevant V51 paths are:

- [UI construction at 0x2E158](../firmware/v51/canonical/main/functions/0002e158_FUN_0002e158.c)
  creates the full-screen object `DAT_1ffe03c4` and makes it active when
  `remote_granted == 1`.
- [Input dispatch at 0x14B14](../firmware/v51/canonical/main/functions/00014b14_FUN_00014b14.c)
  routes the main-screen action to that object while remote control is
  granted. [Event registration at 0x21A50](../firmware/v51/canonical/main/functions/00021a50_FUN_00021a50.c)
  connects its event to `0x5EEAC` and the dialog's action to `0x5B034`.
- [The active-control dialog at 0x5EEAC](../firmware/v51/canonical/main/functions/0005eeac_FUN_0005eeac.c)
  selects string index `0x27`, hides the allow button, configures the
  other button and sets `DAT_1fffab10 = 1`.
- [The action at 0x5B034](../firmware/v51/canonical/main/functions/0005b034_FUN_0005b034.c)
  clears `remote_granted` and `remote_request` and sets bit 2 of the
  reply-work mask when the active-control dialog is confirmed with
  `DAT_1fffab0f == 0`. [The generic dialog-close path at 0x1BA58](../firmware/v51/canonical/main/functions/0001ba58_FUN_0001ba58.c)
  sets `DAT_1fffab0f = 1` first, so dismissing this active-control dialog
  through that path preserves the grant.
- [The C8 handler at 0x1B7F4](../firmware/v51/canonical/main/functions/0001b7f4_cmd_c8_dc_control.c)
  returns `C9 01` for `remoteCon = 1` without a grant and does not apply
  the requested setpoints. A new `remoteCon = 2` request is needed to
  regain control over Bluetooth, with the Allow prompt again.

**Confirmed on hardware, 2026-10-04:** during ST-019 the user reported
that settings could not be changed while remote control was active and
that the screen asked whether to disable remote control. The stored log
contains two unsolicited `C9 01` replies, then a reading with a front-panel
voltage change to 4.00 V. The library copied that value into its 0.080 A
command, which received another `C9 01` and raised `RemoteControlLostError`.
All 308 readings in that test's kept log show the output off. The log
alone does not establish which physical action produced each unsolicited
reply. See the [run record](../../v-model/records/2026-10-04-system-macos-ble-person.md)
for the exact timings, firmware version and the teardown limitation.

**Inference for testing:** ST-019 cannot assume that the user can edit
the setpoint while the host retains its grant. Its procedure needs to
account for the permission change and a subsequent explicit request for
remote control. The approved test specification has not been changed.
ST-023 step 2 already covers a command after front-panel revocation.

## Unanswered remote-control request

**Confirmed in code, reviewed 2026-10-04:**
[the pending dialog at 0x5F434](../firmware/v51/canonical/main/functions/0005f434_FUN_0005f434.c)
sets `DAT_1fffab10 = 0` and exposes the Allow button.
[The idle timer at 0x1E7B4](../firmware/v51/canonical/main/functions/0001e7b4_FUN_0001e7b4.c)
calls the generic dialog-close path after its 60000 ms threshold.
For the remote dialog, `0x1BA58` targets the Deny button. With the
pending-state flag zero, `0x5B034` clears the grant and request and
queues a denied reply. In contrast,
[the Allow callback at 0x5AF88](../firmware/v51/canonical/main/functions/0005af88_FUN_0005af88.c)
sets the grant and queues its reply. The registration at `0x21A50`
binds these callbacks to the two buttons.

**Observed on hardware, 2026-10-04:** the standalone ST-048 timeout
attempt at 02:53 received `C9 00` 9.537 s after the request. The
subsequent active command also received `C9 00`. Output stayed off.
The user initially reported pressing nothing, but later said that they
were unsure about that attempt and requested repetition with clear
instructions. The attempt is inconclusive for unanswered-prompt
behavior and establishes no automatic-grant rule. A later timeout
attempt at 03:01 was allowed by the user and likewise cannot verify
the timeout. The expected ST-048 result remains unchanged.
See the [run record](../../v-model/records/2026-10-04-system-macos-ble-person.md#st-048-timeout-retry-acceptance-without-a-reported-button-press).

**Confirmed on hardware, 2026-10-04:** in the coordinated repetition
at 03:08 the user explicitly confirmed touching nothing. The device
sent `C9 01` after 61.827 s and the prompt disappeared. The library
raised `RemoteControlDeniedError` on that reply, before its 70 s
fallback. Output remained off and the setpoints remained 12.00 V and
0.500 A. See [ST-048 case 2](../../v-model/records/2026-10-04-system-macos-ble-person.md#case-2-unanswered-prompt).

## Display controller and SPI

`0x3C36C` initializes SPI register block `0x4001C000`, resets the panel
through port index 1 bit 3, and calls `0x60258` for its command sequence.
The reset remains low for 100 RTOS ticks and then high for 50 ticks.
Command helper `0x3C132` clears port 1 bit 4; data helper `0x3C150` sets
it. This identifies the latter as the display D/C signal from its use.

Pin configuration at `0x3C068` selects port 1 bit 10, mux `0x2F`; bit 5,
mux `0x28`; and bit 7, mux `0x29`. Assigning SCK, MOSI and other SPI roles
to those pins still needs the exact MCU mux table. DMA setup `0x3C170`
uses base `0x40053000`, channel 0, destination `0x4001C000`, interrupt
selector `0x20`, NVIC channel 5 and callback `0x3C354`.

Confirmed display parameters:

- Logical dimensions are 240 by 320, swapped for alternate orientations.
- Window commands are `2A`, `2B` and `2C`.
- Rotation writes command `36` with `00`, `60`, `C0` or `A0`.
- Initialization starts `DF 98 53`, switches command pages with `DE`,
  writes gamma/power parameters, then sends `3A 05`, `11`, waits 120
  ticks and sends `29`, `2C`.

The complete [command/data/delay sequence](../firmware/v51/canonical/verification/display-initialization.json)
was collected by executing original function `0x60258`, substituting only
the transfer and delay helpers. The sequence can therefore be compared
with a future logic-analyzer capture byte for byte.

**Inference:** a JD9853-compatible display controller is a strong candidate.
The `DF 98 53` unlock sequence matches a published
[JD9853 driver implementation](https://github.com/mydazy/esp_lcd_jd9853).
The manufacturer-authored [JD9853 datasheet](https://files.waveshare.com/wiki/common/Jd9853_datasheet.pdf)
supports the 240-by-320 geometry and standard command meanings. This
does not establish the panel module, exact silicon revision, glass,
backlight supply or physical SPI wiring. `3A 05` is consistent with
16-bit pixel data; the complete LVGL-to-DMA buffer format still needs
independent review.

## Touch controller on a separate I²C bus

Touch uses **`0x4004E000`**, distinct from the power-device I²C controller
at `0x4004E400`. Initialization `0x63370` sets a **200000 Hz target**.
Address helper `0x1854C` writes `(address << 1) | direction` to
`0x4004E024`; the transaction callback supplies address **`0x15`**.

| Signal | Evidence |
|---|---|
| Bus pins | `0x634FC`: port 1 bit 12, mux `0x33`; port 1 bit 13, mux `0x32` |
| Reset | `0x63334`: port 1 bit 14 low ten ticks, high 50 ticks |
| Interrupt input | Port 1 bit 15; callback `0x14A70` starts a one-byte register-selection transaction |
| Receive storage | Seven bytes at `0x1FFF8E96` |
| Completion processing | `0x169F0` receives bytes and reaches coordinate helper `0x277F0` |

The coordinate helper combines low nibbles and following bytes into
12-bit coordinates, rejects values beyond 240/320, and transforms the
coordinates for four display orientations. It also handles an alternate
byte alignment in the received data. The exact meaning of every status
and gesture byte remains open.

**Inference:** a CST8xx-compatible touch controller is plausible. The
address and touch-coordinate format agree with
[Adafruit's original CST8XX driver definitions](https://adafruit.github.io/Adafruit_CST8XX_Library/html/_adafruit___c_s_t8_x_x_8h.html).
These identify a compatible register family, not the fitted chip.
CST816 versus CST826, another compatible controller, and module-specific
firmware cannot be distinguished without ID reads or markings.

## ADC inputs

Initialization `0x12518` reaches ADC-like block `0x40040000`, enables
channels 3 and 6, and configures port 0 bits 3 and 6 as analog inputs.
`0x125C0` starts a conversion, polls completion with a bounded loop and
reads both channels. It computes:

```text
channel 3 software value = raw * 3.3 / 4096 * 1000
channel 6 software value = raw * 3.3 / 4096 * 1000 * 10
```

The resulting values are stored at `0x1FFFA9C8` and `0x1FFFA9C4`.
This establishes a nominal 3.3 V reference assumption and an extra
factor of ten on channel 6. It does not prove actual reference voltage,
resistor-divider values or the nodes being sensed. A 10:1 voltage divider
is a reasonable candidate for the second channel, subject to calibration
and further caller tracing.

## DAC and fine control outputs

`0x14184` configures two analog outputs on port 0 bits 4 and 5 and
register block `0x40041000`. `0x14258` clamps two values to `0xFFF` and
writes them into low and high halfwords. `0x1CE80` writes the low channel;
`0x1CE68` writes the high channel. These operations strongly support a
dual 12-bit DAC interpretation, consistent with the F467/F4A0 reference
maps. The F460 reference calls this address TRNG, another reason that
an F460 identification is insufficient.

The voltage/current control paths also split computed values between
these DAC writes and timer compares at `0x4003A000`:

- `0x1F548` scales a bounded input using `0xFFFFF`, writes the low DAC
  channel and a nine-bit remainder through timer channel 0.
- `0x19DD4` and correction worker `0x14080` transform current-related
  state, write the high DAC channel and use timer channel 3.
- Timer remainder writers are `0x1CEA8` and `0x1CE98`; they special-case
  zero and full scale through output-control bits.

**Inference:** DAC plus filtered PWM may provide coarse and fine analog
setpoint control. The arithmetic has a 20-bit intermediate, but this is
not evidence of 20-bit physical accuracy or effective resolution. Op-amp
topology, filter constants, calibration and channel polarity remain unknown.

## Timer-driven outputs

| Register block and channel | GPIO/configuration evidence | Inferred purpose and confidence |
|---|---|---|
| `0x4003A400`, channel 3 | `0x12E10`, port 1 bit 11, mux 4; sequencer `0x12D54` clamps frequency-like values to 100..5000 and uses duration/repetition tables | Buzzer/tone generation, strong functional match |
| `0x40026C00`, channel 2 | `0x184D4`, port 2 bit 2; DMA at `0x40053000` channel 1; 200-count timer period | Addressable RGB LED signal, strong waveform match; exact LED model unknown |
| `0x4003AC00`, channel 2 | `0x12C24`, port 1 bit 8, mux 4; period argument 24000; duty helper `0x1CD54` | PWM-controlled load; fan is a candidate, full consumer chain unresolved |
| `0x40026000`, channel 0 | `0x15214`, port 0 bit 0, mux 6; period argument 1200; stop helper `0x19FC0` | Another PWM-controlled load; exact fan/backlight assignment unresolved |
| `0x40024000`, channel 0 | `0x12108`, compare `0x753`, callback `0x1DDA0` | Periodic internal service interrupt; physical output not established |

The RGB inference comes from `0x1C5EC`: it expands each 24-bit value,
most significant bit first, into pulse widths `0x24` for zero and `0x6C`
for one. `0x181F8` builds two such values from mode and fault state, then
starts a 50-item DMA transfer. That supports a two-element RGB chain or
two 24-bit control units. The color order, LED package and actual waveform
frequency require further verification.

The tone and RGB interpretations are based on firmware behavior. They
are not identification of the soldered transducer or LED part number.
Rotary encoder, push buttons, fan tachometer, temperature sensing,
battery protection and output-switch signal assignments remain explicit
gaps in the [hardware map](hardware.md).
