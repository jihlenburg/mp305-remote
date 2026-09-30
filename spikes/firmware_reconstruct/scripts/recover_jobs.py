#!/usr/bin/env python3
"""Recover offline analysis probes without changing the original workspace.

Prepare a private scripts directory, then run each probe in its own process.
Completion is distinct from a passing assertion. Logs and a job ledger retain
failures, timeouts, exact commands, dependency versions and input hashes.
"""
import argparse
import ast
import concurrent.futures
import difflib
import hashlib
import json
import os
from pathlib import Path
import re
import subprocess
import sys
import time


def digest(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def prepare(workspace, output, repo):
    scripts = output / "scripts"
    scripts.mkdir(parents=True, exist_ok=True)
    changes = []
    for original in sorted((workspace / "scripts").glob("*.py")):
        old = original.read_text()
        new = old
        # Imports must resolve to the repaired copy, even when a probe has an
        # old absolute sys.path insertion. Firmware inputs stay in workspace.
        new = "\n".join(
            "sys.path.insert(0, str(__import__('pathlib').Path(__file__).resolve().parent))"
            if line.startswith("sys.path.insert(0,") else line
            for line in new.splitlines()
        ) + "\n"
        new = re.sub(r"sys\.path\.insert\(0, os\.path\.expanduser\([\"']~/mp305b-fw-re/scripts[\"']\)\)",
                     "sys.path.insert(0, str(__import__('pathlib').Path(__file__).resolve().parent))", new)
        if original.name in {"emu_app.py", "ch58x_emu.py", "hostlink_emu_ch58x.py"}:
            if "import os" not in new:
                new = "import os\n" + new
            new = "\n".join(
                'RE = os.path.expanduser(os.environ.get("MP305_RE_WORKSPACE", "~/mp305b-fw-re")) + "/"'
                if line.startswith("RE = ") else line
                for line in new.splitlines()
            ) + "\n"
        if original.name == "emu_app.py":
            new = new.replace("(HC32F4A0, linked", "(HC32 family, linked")
            new = new.replace("        return mu.reg_read(UC_ARM_REG_R0)",
                '        if mu.reg_read(UC_ARM_REG_PC) != TRAP:\n'
                '            raise RuntimeError(f"ARM call {addr:#x} exhausted its budget at {mu.reg_read(UC_ARM_REG_PC):#x}")\n'
                '        return mu.reg_read(UC_ARM_REG_R0)')
        if original.name == "ch58x_emu.py":
            # AUIPC at 0x1C48 is PC-relative: 0x1C48 + 0x20000000 + 0x3B8.
            new = new.replace("UC_RISCV_REG_GP, 0x200023B8", "UC_RISCV_REG_GP, 0x20002000")
            for old_api in ("docs/research/firmware-v51/wch-sdk-api.tsv",
                            "docs/research/firmware/v51/canonical/wch-sdk-api.tsv"):
                new = new.replace(f'os.path.expanduser("~/mp305b/{old_api}")',
                    'os.path.join(os.environ.get("MP305_RE_REPO", os.path.expanduser("~/mp305b")), "docs/research/firmware/v51/canonical/wch-sdk-api.tsv")')
            new = new.replace("        return u.reg_read(A[0])",
                '        if u.reg_read(UC_RISCV_REG_PC) != RET:\n'
                '            raise RuntimeError(f"RV32 call {fn:#x} exhausted its budget at {u.reg_read(UC_RISCV_REG_PC):#x}")\n'
                '        return u.reg_read(A[0])')
        if original.name == "hostlink_emu_ch58x.py":
            new = new.replace("        return mu.reg_read(UC_RISCV_REG_A0)",
                '        if mu.reg_read(UC_RISCV_REG_PC) != TRAP:\n'
                '            raise RuntimeError(f"RV32 call {addr:#x} exhausted its budget at {mu.reg_read(UC_RISCV_REG_PC):#x}")\n'
                '        return mu.reg_read(UC_RISCV_REG_A0)')
        if original.name == "hostlink_ch58x_route_tests.py":
            new = new.replace("    c = CH(); usb = []; gatt = []", "    c = CH(); usb = []; gatt = []\n"
                "    # Binding success writes DataFlash. Model the external flash operation\n"
                "    # as successful, just as cmds() does; persistence is checked separately.\n"
                "    c.hooks[0x200028D6] = lambda ch: 0")
            new = new.replace("    print('USB OUT %-16s", "    assert uart == [frame], (label, uart, frame)\n    print('USB OUT %-16s")
            new = new.replace("    print('MCU->%s wire", "    if dst == 1:\n"
                "        assert all(u[0] == 2 and 0 < u[1] <= 62 for u in usb), usb\n"
                "        assert b''.join(u[2:2+u[1]] for u in usb) == w, (usb, w)\n"
                "    else:\n"
                "        expected = ('AF01', b'\\x31' + body[:-1]) if body[-1] == 0x31 else ('AF02', body[:-1])\n"
                "        assert gatt == [expected], (gatt, expected)\n"
                "    print('MCU->%s wire")
        if original.name == "hostlink_emu_tests.py":
            new = new.replace("    print('encoder: %d cases, %d mismatches' % (len(cases), bad))",
                "    assert bad == 0, f'{bad} encoder mismatches'\n"
                "    print('encoder: %d cases, %d mismatches' % (len(cases), bad))")
            new = new.replace("    print('decoder round trip: %d frames, %d failures' % (n, bad))",
                "    assert bad == 0, f'{bad} decoder mismatches'\n"
                "    print('decoder round trip: %d frames, %d failures' % (n, bad))")
        (scripts / original.name).write_text(new)
        if new != old:
            changes.extend(difflib.unified_diff(old.splitlines(True), new.splitlines(True),
                fromfile=f"original/{original.name}", tofile=f"recovered/{original.name}"))
    (output / "harness-repairs.patch").write_text("".join(changes))


def run(workspace, output, repo, python, only):
    scripts = output / "scripts"
    jobs = []
    for group in "c8 c6 reads misc e2 e8 ee prog pd chreads maint deferred".split():
        jobs.append((f"commands-{group}", [str(scripts / "commands_vectors.py"), group], "observation"))
    for i in range(1, 9):
        jobs.append((f"bridge-t{i}", ["-c", f"import ch58x_bridge_checks as p; p.check_t{i}()"], "observation"))
    tree = ast.parse((scripts / "hostlink_emu_tests.py").read_text())
    for node in tree.body:
        if isinstance(node, ast.FunctionDef) and node.name.startswith("test_"):
            kind = "comparison" if node.name in {"test_encoder", "test_decoder"} else "observation"
            jobs.append((f"hostlink-{node.name[5:]}", ["-c", f"import hostlink_emu_tests as p; p.{node.name}()"], kind))
    jobs.append(("bridge-routes", [str(scripts / "hostlink_ch58x_route_tests.py")], "observation"))
    if only:
        jobs = [job for job in jobs if job[0] in only]
        if set(only) != {job[0] for job in jobs}:
            raise ValueError("Unknown job selection")
    env = dict(os.environ, MP305_RE_WORKSPACE=str(workspace), MP305_RE_REPO=str(repo),
               PYTHONPATH=str(scripts), PYTHONUNBUFFERED="1")
    logs = output / "logs"
    logs.mkdir(exist_ok=True)
    def one(job):
        name, args, kind = job
        command = [str(python), *args]
        start = time.monotonic()
        log = logs / f"{name}.log"
        if log.exists():
            log.rename(log.with_name(f"{name}.{time.time_ns()}.previous.log"))
        with log.open("w") as stream:
            try:
                result = subprocess.run(command, cwd=scripts, env=env, stdout=stream,
                                        stderr=subprocess.STDOUT, timeout=180, check=False)
                rc = result.returncode
                status = "completed" if rc == 0 else "failed"
            except subprocess.TimeoutExpired:
                rc, status = None, "timeout"
        row = dict(job=name, kind=kind, status=status, returncode=rc,
                   seconds=round(time.monotonic()-start, 3), command=command,
                   log=str(log.relative_to(output)), sha256=digest(log))
        print(f"{name}: {status}", flush=True)
        return row
    path = output / "results/jobs.json"
    path.parent.mkdir(exist_ok=True)
    prior = json.loads(path.read_text()) if path.exists() else {}
    with concurrent.futures.ThreadPoolExecutor(max_workers=2) as pool:
        for row in pool.map(one, jobs):
            prior[row["job"]] = row
            path.write_text(json.dumps(prior, indent=2) + "\n")
    metadata = dict(workspace=str(workspace), python=str(python), cwd=str(scripts),
                    environment={k: env[k] for k in ["MP305_RE_WORKSPACE", "MP305_RE_REPO", "PYTHONPATH"]},
                    inputs={p.name:digest(p) for p in sorted((workspace/"bin").glob("*.bin"))},
                    scripts={p.name:digest(p) for p in sorted(scripts.glob("*.py"))})
    (output / "results/run-inputs.json").write_text(json.dumps(metadata, indent=2) + "\n")
    return all(row["status"] == "completed" for row in prior.values())


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("workspace", type=Path)
    parser.add_argument("output", type=Path)
    parser.add_argument("--repo", type=Path, default=Path(__file__).resolve().parents[3])
    parser.add_argument("--python", type=Path)
    parser.add_argument("--prepare", action="store_true")
    parser.add_argument("--only", nargs="*")
    args = parser.parse_args()
    workspace, output, repo = args.workspace.resolve(), args.output.resolve(), args.repo.resolve()
    if output == workspace:
        parser.error("Output must be a separate recovery directory")
    if args.prepare:
        prepare(workspace, output, repo)
    ok = run(workspace, output, repo, args.python or workspace/".venv/bin/python", args.only)
    sys.exit(0 if ok else 1)


if __name__ == "__main__":
    main()
