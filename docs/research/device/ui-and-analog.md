# Display, touch and analog interfaces

Updated 2026-09-30. MP305B V51 main processor addresses are used throughout.
Numeric accesses and call sequences below are **confirmed in code**.
Physical component and signal names remain **inferred** where stated.

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
