#!/usr/bin/env python3
"""Apply recovered names and finish exports on private Ghidra project copies.

The source workspace is never changed. A fresh output directory is required.
Firmware bytes and project databases remain outside the repository.
"""
import argparse
from collections import defaultdict
import hashlib
import json
import os
from pathlib import Path
import re
import shutil
import subprocess


def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument("workspace", type=Path)
    p.add_argument("output", type=Path)
    p.add_argument("--repo", type=Path, default=Path(__file__).resolve().parents[3])
    p.add_argument("--ghidra", type=Path, default=Path("/opt/homebrew/Cellar/ghidra/12.1.3/libexec"))
    a = p.parse_args()
    w,o,r = a.workspace.resolve(),a.output.resolve(),a.repo.resolve()
    if o.exists() or o.is_relative_to(r) or o == w:
        p.error("Choose a fresh output directory outside the repository")
    o.mkdir(parents=True)
    for name in ["scripts","ghidra"]:shutil.copytree(w/name,o/name)
    for name in ["exports","logs","names-merged","results"]:(o/name).mkdir()
    shutil.copy2(Path(__file__).with_name("RecoveryFixups.java"),o/"scripts/RecoveryFixups.java")
    for name in ["Export.java","ExportRefs.java"]:
        s=(o/"scripts"/name).read_text()
        s=s.replace('System.getProperty("user.home") + "/mp305b-fw-re/out/"','getScriptArgs()[1] + "/"')
        (o/"scripts"/name).write_text(s)
    path=o/"scripts/ApplyNames.java";s=path.read_text()
    s=s.replace('System.getProperty("user.home") + "/mp305b-fw-re/names"','getScriptArgs()[1]')
    s=s.replace('for (File f : dir.listFiles()) {','File[] files = dir.listFiles(); java.util.Arrays.sort(files); for (File f : files) {')
    path.write_text(s)
    names=defaultdict(list)
    for path in sorted((w/"names").glob("*.tsv")):
        for line in path.read_text().splitlines():
            if not line or line.startswith("#"):continue
            addr,name,*comment=line.split("\t")
            names[(path.name.split("_")[0],int(addr,16))].append(dict(source=path.name,name=name,comment=" ".join(comment)))
    for tag in ["app","ch58x"]:
        lines=[f'{addr:x}\t{items[-1]["name"]}\t'+" | ".join(x["name"]+": "+x["comment"] for x in items)
               for (t,addr),items in sorted(names.items()) if t==tag]
        (o/f"names-merged/{tag}_recovered.tsv").write_text("\n".join(lines)+"\n")
    ledger=[dict(image=t,address=hex(addr),primary=items[-1]["name"],aliases=items) for (t,addr),items in sorted(names.items())]
    (o/"results/names.json").write_text(json.dumps(ledger,indent=2)+"\n")
    lib=[]
    for row in (r/"docs/research/firmware/v51/canonical/wch-sdk-api.tsv").read_text().splitlines()[1:]:
        slot,_,name=row.split("\t");lib.append(slot+"\t"+name)
    (o/"names-merged/wch-library.tsv").write_text("\n".join(lib)+"\n")
    records=[]
    for tag in ["app","ch58x","pd8051"]:
        cmd=[str(a.ghidra/"support/analyzeHeadless"),"ghidra",f"mp305b_{tag}","-process",f"{tag}.bin","-noanalysis","-scriptPath","scripts","-max-cpu","2"]
        if tag=="app":cmd += ["-postScript","power_Fix.java","exports"]
        if tag=="ch58x":cmd += ["-postScript","ch58x_BridgeFix.java","names-merged/wch-library.tsv","exports/ch58x_decomp_fixed.c"]
        if tag!="pd8051":cmd += ["-postScript","ApplyNames.java",tag,"names-merged"]
        if tag=="app":cmd += ["-postScript","RecoveryFixups.java"]
        cmd += ["-postScript","Export.java",tag,"exports","-postScript","ExportRefs.java",tag,"exports"]
        log=o/f"logs/ghidra-{tag}.log"
        with log.open("w") as f:
            result=subprocess.run(cmd,cwd=o,stdout=f,stderr=subprocess.STDOUT,timeout=1200,check=False)
        text=log.read_text();export=re.findall(r"EXPORT functions=(\d+) failed=(\d+)",text)
        # Ghidra can return zero after a script exception; require its success
        # marker as well as nonempty files and absence of script errors.
        files=[o/f"exports/{tag}_{suffix}" for suffix in ["decomp.c","functions.tsv","refs.tsv","strings.tsv"]]
        ok=result.returncode==0 and len(export)==1 and export[0][1]=="0" and "ERROR" not in text and all(x.is_file() and x.stat().st_size for x in files)
        records.append(dict(image=tag,command=cmd,cwd=str(o),returncode=result.returncode,
            passed=bool(ok),export=export,java_home=os.environ.get("JAVA_HOME"),
            files={x.name:hashlib.sha256(x.read_bytes()).hexdigest() for x in files if x.exists()}))
        (o/"results/export-jobs.json").write_text(json.dumps(records,indent=2)+"\n")
        print(tag,"passed" if ok else "failed",flush=True)
        if not ok:raise RuntimeError(f"See {log}")


if __name__=="__main__":main()
