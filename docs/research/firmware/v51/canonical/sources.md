# Source provenance

Updated 2026-09-30. Firmware evidence, external reference implementations
and manufacturer claims have different scopes. None of the external
references establishes the exact bytes or components in the user's unit.

## Firmware and scratchpads

The original ISDT MP305B V51 update is identified in
[input-sha256.json](verification/input-sha256.json). It was already present
under `~/.local/share/mp305b/fw/` and in both prior scratchpads. The
[16 input comparisons](verification/input-verification.json) establish
agreement and image boundaries. Independent restoration preserves the
identity magic that WebLink's plain export replaced with four `FF` bytes.

| Workspace | Role |
|---|---|
| `/Users/jihlenburg/mp305b-firmware-scratch/2026-09-29` | Canonical restored images, refined Ghidra projects and independent rebuild |
| `/tmp/mp305_firmware_scratchpad` | Earlier report, scripts and decompilations, preserved as historical evidence |
| `/Users/jihlenburg/mp305b-firmware-scratch/2026-09-30-merge` | Merge baseline, copies of both source notes, new analyses and portable verification runs |
| `/Users/jihlenburg/mp305b-fw-re` | Independent Ghidra imports and host-interface analysis, original files preserved |
| `/Users/jihlenburg/mp305b-fw-re/recovery-2026-09-30` | Recovered jobs, named project copies, checked probes and completed comparison report; text artifacts in [firmware-recovery](../independent/README.md) |

These paths locate evidence on the research machine. The repository's
text exports and scripts do not require those paths for reading. Raw
firmware, restored images, downloaded binaries, compiled libraries and
Ghidra databases remain outside the repository.

The old report is not imported as current documentation because several
field meanings and load addresses were wrong. Its hash is retained in
[tmp-source-manifest.json](verification/tmp-source-manifest.json), alongside
the [persistent-note manifest](verification/persistent-source-manifest.json).
The [correction ledger](../../verification.md#scratchpad-claim-reconciliation)
explains the differences.

## WCH reference library and register definitions

The ISDT RV32 program names `CH58x_BLE_LIB_V1.8` and calls address
`0x40000`, outside the update. Official
[openwch/ch583](https://github.com/openwch/ch583) commit
`1e6af6a4299de36dfdd97e5791989a3a97981847` supplies a comparison:

- [V1.8 API header](https://github.com/openwch/ch583/blob/1e6af6a4299de36dfdd97e5791989a3a97981847/EVT/EXAM/BLE/LIB/CH58xBLE_ROM.h).
- [V1.8 Intel HEX library](https://github.com/openwch/ch583/blob/1e6af6a4299de36dfdd97e5791989a3a97981847/EVT/EXAM/BLE/LIB/CH58xBLE_ROMx.hex).

The HEX decoder checks record checksums and both address-extension forms.
The reference spans `0x40000..0x6C77F`; 138 API entries were extracted.
It is analyzed in its own project and exported under sdk-reference.
The physical unit's installed library was not dumped or matched.
Current-branch CH583SFR.h and startup code provide additional comparisons.
Exact download URLs and hashes are in
[reference-downloads.json](verification/reference-downloads.json) and
[reference-sha256.json](verification/reference-sha256.json).

## HDSC register comparisons

Device packs came from the official
[HDSC pack repository](https://github.com/hdscmcu/pack) and
[Keil index](https://www.keil.com/pack/index.pidx). F448, F451, F452,
F460, F472 and F4A0 headers/SVDs were compared. F467 material came from
the [vendor product page](https://www.xhsc.com.cn/product/1219.html) and
[IDE package](https://oss-nc-beijing-2.cecloudcs.com/doc-hc/HC32F467_IDE_Rev1.0.2.zip).
These comparisons leave the main MCU identity unresolved. The access
index preserves conflicting names instead of selecting a family globally.

## RTOS comparison

The official [FreeRTOS V10.3.1-kernel-only source](https://github.com/FreeRTOS/FreeRTOS-Kernel/tree/V10.3.1-kernel-only)
was used to compare task lists, queues, event groups, heap_4 and the
RVDS ARM_CM4F port. [Downloaded source hashes](verification/freertos-sources.json)
record the exact comparison. V10.3.1 is not claimed as the recovered
device version. Behavioral findings are tied to V51 instructions.

## Hardware and product references

| Reference | What it supports |
|---|---|
| [ISDT MP305 product page](https://www.isdt.co/mp305.html?lang=en) | Manufacturer specifications and model distinction |
| [ISDT manual](https://www.isdt.co/down/pdf/MP305.pdf) | Panel/connector labels and specifications; rendered English pages 15 and 23 inspected |
| [TI INA226 datasheet](https://www.ti.com/lit/ds/symlink/ina226.pdf) | Candidate current-monitor address, register map and byte order |
| [Southchip SC8815 datasheet](https://datasheet.lcsc.com/datasheet/pdf/166c1651342e6c0583cf5aa024478e9d.pdf) | Manufacturer-authored PDF served by LCSC; fixed address and voltage-reference packing |
| [Jadard JD9853 datasheet](https://files.waveshare.com/wiki/common/Jd9853_datasheet.pdf) | Manufacturer-authored PDF served by Waveshare; geometry and standard display commands |
| [JD9853 driver source](https://github.com/mydazy/esp_lcd_jd9853) | Original driver implementation with matching unlock sequence; supplementary, not board evidence |
| [Adafruit CST8XX definitions](https://adafruit.github.io/Adafruit_CST8XX_Library/html/_adafruit___c_s_t8_x_x_8h.html) | Original driver definitions used for the touch-interface candidate |

[additional-sources.json](verification/additional-sources.json) fingerprints
the newly downloaded PDFs. A failed Southchip website download returned
HTML; it is retained externally as SC8815-download.html and was not
treated as a datasheet. The valid replacement PDF was text-inspected.

Hardware candidates remain **inferred**. Manufacturer specifications remain
claims until observed on the unit. Only the existing captures supply
hardware confirmation in this pass.
