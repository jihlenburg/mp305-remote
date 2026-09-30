#!/usr/bin/env python3
"""Check research links, firmware exclusions and the current artifact manifest.

Historical manifests retain their original scope and paths. This command checks
current research files and writes or verifies docs/research/manifest.json.
"""

import argparse
import hashlib
import json
from pathlib import Path
import re
from urllib.parse import unquote
import xml.etree.ElementTree as ET


def audit(root):
    """Return current file hashes and concrete structural errors."""
    files = {}
    errors = []
    for path in sorted(root.rglob("*")):
        if not path.is_file() or path.name == "manifest.json" and path.parent == root:
            continue
        relative = str(path.relative_to(root))
        if path.suffix.lower() in {
            ".bin",
            ".fwd",
            ".hex",
            ".elf",
            ".gpr",
            ".bytes",
        } or any(p.endswith(".rep") for p in path.parts):
            errors.append(f"Firmware or project file in research: {relative}")
        files[relative] = dict(
            bytes=path.stat().st_size,
            sha256=hashlib.sha256(path.read_bytes()).hexdigest(),
        )
        if path.name == "analysis.xml":
            if ET.parse(path).findall(".//MEMORY_CONTENTS"):
                errors.append(f"Memory contents embedded in {relative}")
        if path.name == "program.json" and "ghidra" in path.parts:
            data = json.loads(path.read_text())
            if data.get("memory_contents_exported") is not False or any(
                b.get("unresolved") for b in data["memory_blocks"]
            ):
                errors.append(f"Unresolved memory or embedded contents in {relative}")
        if path.suffix != ".md" or "historical" in path.parts:
            continue
        content = re.sub(r"```.*?```", "", path.read_text(), flags=re.S)
        for match in re.finditer(r"(?<!!)\[[^\]]*\]\(([^)]+)\)", content):
            url = match[1].split(' "')[0].strip("<>")
            target = unquote(url.split("#")[0])
            if not target or re.match(r"^[a-z]+:", target):
                continue
            if not (path.parent / target).exists():
                errors.append(f"Broken link in {relative}: {url}")
    return files, errors


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--write-manifest", action="store_true")
    args = parser.parse_args()
    root = Path(__file__).resolve().parents[3] / "docs/research"
    manifest = root / "manifest.json"
    files, errors = audit(root)
    if args.write_manifest and not errors:
        manifest.write_text(
            json.dumps(
                dict(
                    schema=1,
                    scope="Current research files except this manifest; historical snapshots keep their own hashes",
                    files=files,
                ),
                indent=2,
            )
            + "\n"
        )
    elif not args.write_manifest:
        saved = json.loads(manifest.read_text())["files"]
        for path in sorted(saved.keys() | files.keys()):
            if saved.get(path) != files.get(path):
                errors.append(f"Manifest mismatch: {path}")
    print(
        json.dumps(
            dict(
                files=len(files),
                bytes=sum(x["bytes"] for x in files.values()),
                errors=errors,
                passed=not errors,
            ),
            indent=2,
        )
    )
    return 1 if errors else 0


if __name__ == "__main__":
    raise SystemExit(main())
