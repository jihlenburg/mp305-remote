#!/usr/bin/env python3
"""Restore a byte-free Ghidra snapshot using separately supplied firmware.

Exact hashes are mandatory. New releases must be analyzed in a fresh project;
do not apply V51's address-specific annotations to a different image.
"""

import argparse
import hashlib
import json
import os
from pathlib import Path
import subprocess
import xml.etree.ElementTree as ET


def compare_exports(snap, reexport):
    """Compare required core metadata, retaining optional importer differences."""
    spec = json.loads((snap / "program.json").read_text())
    record = {}
    ok = True
    after = json.loads((reexport / "program.json").read_text())
    for key in ["memory_blocks", "functions"]:
        # Block sources can be found in a different input order. The actual
        # ranges, permissions, byte hashes and function metadata must agree.
        def comparable(rows):
            return [
                {
                    k: v
                    for k, v in row.items()
                    if k
                    not in {
                        "source_name",
                        "source_sha256",
                        "source_offset",
                        "variables",
                    }
                }
                for row in rows
            ]

        same = comparable(spec[key]) == comparable(after[key])
        record[key + "_equal"] = same
        ok &= same
    before_tree = ET.parse(snap / "analysis.xml")
    after_tree = ET.parse(reexport / "analysis.xml")
    for section in [
        "DATATYPES",
        "DATA",
        "CODE",
        "MARKUP",
        "PROGRAM_ENTRY_POINTS",
        "REGISTER_VALUES",
        "COMMENTS",
        "BOOKMARKS",
        "SYMBOL_TABLE",
        "EQUATES",
        "FUNCTIONS",
    ]:

        def normalize(tree):
            node = tree.find(section)
            if node is None:
                raise ValueError(f"Missing Ghidra XML section: {section}")

            def canonical(el):
                return (
                    el.tag,
                    tuple(sorted(el.attrib.items())),
                    (el.text or "").strip(),
                    tuple(sorted(canonical(child) for child in el)),
                )

            return canonical(node)

        same = normalize(before_tree) == normalize(after_tree)
        record[section.lower() + "_xml_equal"] = same
        if section not in {"FUNCTIONS", "SYMBOL_TABLE"}:
            ok &= same
    record["variable_metadata_equal"] = all(
        x.get("variables") == y.get("variables")
        for x, y in zip(spec["functions"], after["functions"])
    )
    record["meaning"] = (
        "passed checks core function metadata, mapped bytes, types, comments, bookmarks, equates and context; XML function/storage and symbol differences are reported separately, not treated as lossless restoration"
    )
    record["core_comparison_passed"] = bool(ok)
    return record


def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument("--snapshot", type=Path, required=True)
    p.add_argument("--scratch", type=Path, required=True)
    p.add_argument("--input", type=Path, action="append", required=True)
    p.add_argument(
        "--ghidra",
        type=Path,
        default=Path("/opt/homebrew/Cellar/ghidra/12.1.3/libexec"),
    )
    a = p.parse_args()
    snap = a.snapshot.resolve()
    out = a.scratch.resolve()
    repo = Path(__file__).resolve().parents[3]
    if out.exists() or out.is_relative_to(repo):
        p.error("Choose a fresh scratch directory outside the repository")
    spec = json.loads((snap / "program.json").read_text())
    xml = ET.parse(snap / "analysis.xml")
    if spec["memory_contents_exported"] or xml.findall(".//MEMORY_CONTENTS"):
        p.error("Snapshot contains memory contents")
    inputs = {
        hashlib.sha256(x.read_bytes()).hexdigest(): str(x.resolve()) for x in a.input
    }
    needed = {
        b["source_sha256"] for b in spec["memory_blocks"] if b.get("source_sha256")
    }
    if any(b.get("unresolved") for b in spec["memory_blocks"]):
        p.error("Snapshot has unresolved initialized blocks")
    if needed - inputs.keys():
        p.error("Missing input hashes: " + ", ".join(sorted(needed - inputs.keys())))
    image = inputs.get(spec["executable_sha256"])
    if image is None:
        p.error("The original import image is required by hash")
    out.mkdir(parents=True)
    (out / "projects").mkdir()
    (out / "input-map.json").write_text(json.dumps(inputs, indent=2) + "\n")
    scripts = Path(__file__).resolve().parent
    cmd = [
        str(a.ghidra / "support/analyzeHeadless"),
        str(out / "projects"),
        "restored",
        "-import",
        image,
        "-processor",
        spec["language"],
        "-cspec",
        spec["compiler_spec"],
        "-loader",
        "BinaryLoader",
        "-loader-baseAddr",
        "0x0",
        "-noanalysis",
        "-scriptPath",
        str(scripts),
        "-postScript",
        "ImportAnalysis.java",
        str(snap),
        str(out / "input-map.json"),
        "-postScript",
        "ExportAnalysis.java",
        str(out / "reexport"),
        *[str(x.resolve()) for x in a.input],
    ]
    log = out / "restore.log"
    with log.open("w") as f:
        result = subprocess.run(
            cmd, stdout=f, stderr=subprocess.STDOUT, timeout=1200, check=False
        )
    text = log.read_text()
    errors = [line for line in text.splitlines() if line.startswith("ERROR")]
    known = [
        line
        for line in errors
        if "Unsupported operation for language" in line
        and "FunctionPurgeAnalysisCmd" in line
        or "Failed to create function at" in line
        and "FunctionsXmlMgr" in line
    ]
    ok = (
        result.returncode == 0
        and "ANALYSIS_RESTORED" in text
        and "ANALYSIS_EXPORTED" in text
        and errors == known
    )
    record = dict(
        command=cmd,
        java_home=os.environ.get("JAVA_HOME"),
        returncode=result.returncode,
        importer_diagnostics=errors,
        importer_null_function_diagnostics=text.count(
            "java.lang.NullPointerException:"
        ),
        passed=ok,
    )
    if ok:
        comparison = compare_exports(snap, out / "reexport")
        record.update(comparison)
        ok = comparison["core_comparison_passed"]
    record["passed"] = bool(ok)
    (out / "result.json").write_text(json.dumps(record, indent=2) + "\n")
    print(json.dumps(record, indent=2))
    return 0 if ok else 1


if __name__ == "__main__":
    raise SystemExit(main())
