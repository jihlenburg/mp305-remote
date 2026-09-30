# Reusable firmware analysis tools

Question: can the recovered Ghidra work be preserved without firmware bytes,
and can the same analysis process start from a future release?

These are offline research tools, outside any production workspace. They do
no device I/O. Read the [workflow](../../docs/research/workflow/README.md) for
the procedure, evidence rules and address-porting requirements.

## Tools

| Tool | Purpose |
|---|---|
| `stage_release.py` | Decode the documented FWD container into a fresh external workspace; verify checksum and reset vector; record candidate companion boundaries |
| `import_release.py` | Import fresh raw programs, verify staged hashes and export initial analysis |
| `ExportAnalysis.java` | Export standard XML without memory contents plus JSON for hashes, mappings, functions, variables, options and fingerprints |
| `ImportAnalysis.java` | Rebuild mappings from verified external inputs and restore XML plus explicit function metadata into a fresh project |
| `restore_analysis.py` | Require exact inputs, restore, re-export and compare; report importer losses separately |
| `audit_research.py` | Check current research links, firmware exclusions and artifact hashes; write or verify the manifest |
| `compare_analysis.py` | Suggest same-language function matches, retaining ambiguity and requiring review; apply no names |

Python 3.12 and its standard library suffice for these scripts. The recorded
run used Ghidra 12.1.3 and OpenJDK 21. Supply `--ghidra` when the installation
is not `/opt/homebrew/Cellar/ghidra/12.1.3/libexec`, and set `JAVA_HOME` as
required by that installation. Ghidra's XML behavior is version-sensitive.

## Export an existing program

Use a read-only headless session. Supply all external files needed to locate
initialized memory blocks, including separately reconstructed RAM:

```sh
/path/to/ghidra/support/analyzeHeadless /external/projects project-name \
  -process program-name -noanalysis -readOnly \
  -scriptPath "$PWD/spikes/firmware_workflow/scripts" \
  -postScript ExportAnalysis.java /external/metadata \
  /external/firmware.bin /external/initialized-ram.bin
```

Require `unresolved_blocks=0` and inspect the resulting XML and JSON. Export
stores memory hashes and input offsets, not the initialized memory contents.
Program comments, symbols, types, references, context and function definitions
remain in XML; JSON supplements metadata lost by the XML importer.

The restore runner uses `-noanalysis`, but XML import itself can infer extra
functions and thunks. The importer reconciles the saved entry set, body ranges
and thunk relationships explicitly. Its comparison records any remaining
symbol, stack-frame or variable changes. Original XML and JSON remain the
reference even when the importer cannot reproduce every property.

## Recorded checks

See [V51 snapshots](../../docs/research/firmware/v51/ghidra/README.md) for all
seven restore results and [workflow verification](../../docs/research/firmware/v51/ghidra/verification/workflow.json)
for container/import/comparison and rejection checks. Fresh imports are initial
auto-analysis only; later manual reconstruction is still required.

## Audit a published bundle

```sh
python3 spikes/firmware_workflow/scripts/audit_research.py
```

After deliberate research edits, review the changes and regenerate the current
manifest with `--write-manifest`. Historical manifests remain unchanged. The
script checks local file targets; the recorded cleanup also checked Markdown
heading anchors. It does not prove every semantic claim in the research.
