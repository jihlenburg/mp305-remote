#!/usr/bin/env python3
"""Suggest cross-release function matches without applying any names.

Unique exact instruction hashes are the strongest suggestions. Mnemonic-only
matches ignore operands and require manual review. Ambiguities remain explicit.
"""

import argparse
from collections import defaultdict
import json
from pathlib import Path


def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument("baseline", type=Path)
    p.add_argument("candidate", type=Path)
    p.add_argument("output", type=Path)
    a = p.parse_args()
    old = json.loads(a.baseline.read_text())
    new = json.loads(a.candidate.read_text())
    if old["language"] != new["language"]:
        p.error("Compare programs using the same processor language")
    for spec in [old, new]:
        if any(
            "instruction_bytes_sha256" not in row or "mnemonics_sha256" not in row
            for row in spec["functions"]
        ):
            p.error("Export both programs with the current ExportAnalysis.java")
    indices = {
        key: defaultdict(list)
        for key in ["instruction_bytes_sha256", "mnemonics_sha256"]
    }
    for row in new["functions"]:
        if row.get("instruction_count", 0):
            for key, index in indices.items():
                index[(row.get(key), row.get("instruction_count"))].append(row)
    records = []
    for row in old["functions"]:
        exact = indices["instruction_bytes_sha256"][
            (row.get("instruction_bytes_sha256"), row.get("instruction_count"))
        ]
        weak = indices["mnemonics_sha256"][
            (row.get("mnemonics_sha256"), row.get("instruction_count"))
        ]
        kind = (
            "unique_instruction_hash"
            if len(exact) == 1
            else "ambiguous_instruction_hash"
            if exact
            else "mnemonic_candidates"
            if weak
            else "unmatched"
        )
        if row.get("instruction_count", 0) <= 3 and kind != "unmatched":
            kind = "short_function_candidates"
        candidates = exact or weak
        records.append(
            dict(
                old_entry=row["entry"],
                old_name=row["name"],
                kind=kind,
                candidates=[dict(entry=x["entry"], name=x["name"]) for x in candidates],
                review_required=True,
            )
        )
    result = dict(
        baseline_sha256=old["executable_sha256"],
        candidate_sha256=new["executable_sha256"],
        mappings_applied=False,
        results=records,
    )
    a.output.write_text(json.dumps(result, indent=2) + "\n")
    print(
        json.dumps(
            {
                kind: sum(x["kind"] == kind for x in records)
                for kind in sorted({x["kind"] for x in records})
            }
        )
    )


if __name__ == "__main__":
    main()
