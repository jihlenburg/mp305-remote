#!/usr/bin/env python3
"""Import a staged release with no inherited address-specific annotations."""

import argparse
import hashlib
import json
from pathlib import Path
import subprocess


def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument("workspace", type=Path)
    p.add_argument(
        "--image",
        action="append",
        choices=["main-arm.bin", "ble-riscv.bin", "pd-8051.bin"],
    )
    p.add_argument(
        "--ghidra",
        type=Path,
        default=Path("/opt/homebrew/Cellar/ghidra/12.1.3/libexec"),
    )
    a = p.parse_args()
    root = a.workspace.resolve()
    repo = Path(__file__).resolve().parents[3]
    if root.is_relative_to(repo):
        p.error("Analysis workspace must be outside the repository")
    spec = json.loads((root / "release.json").read_text())
    records = []
    selected = a.image or [
        name for name, row in spec["images"].items() if row.get("processor")
    ]
    for name in selected:
        row = spec["images"][name]
        source = root / row["file"]
        project = name.removesuffix(".bin")
        if (root / f"projects/{project}.gpr").exists():
            p.error("Project exists; preserve it and choose a new workspace")
        if hashlib.sha256(source.read_bytes()).hexdigest() != row["sha256"]:
            p.error("Input hash changed")
        cmd = [
            str(a.ghidra / "support/analyzeHeadless"),
            str(root / "projects"),
            project,
            "-import",
            str(source),
            "-processor",
            row["processor"],
            "-loader",
            "BinaryLoader",
            "-loader-baseAddr",
            row["load_address"],
            "-max-cpu",
            "2",
            "-scriptPath",
            str(Path(__file__).resolve().parent),
            "-postScript",
            "ExportAnalysis.java",
            str(root / "exports" / project),
            str(source),
        ]
        log = root / "logs" / f"import-{project}.log"
        with log.open("w") as f:
            run = subprocess.run(
                cmd, stdout=f, stderr=subprocess.STDOUT, timeout=1200, check=False
            )
        text = log.read_text()
        ok = run.returncode == 0 and "ANALYSIS_EXPORTED" in text and "ERROR" not in text
        records.append(dict(image=name, command=cmd, passed=ok))
        (root / "exports/import-results.json").write_text(
            json.dumps(records, indent=2) + "\n"
        )
        if not ok:
            raise RuntimeError(f"Import failed: {log}")
        print(project, "imported", flush=True)


if __name__ == "__main__":
    main()
