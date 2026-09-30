"""Copy the workspace scripts into the repository spike folder.

Rewrites absolute home paths to ~/mp305b-fw-re so the copies are portable.
Skips caches. Run again after the scripts change.
"""
import os
import re
import shutil

WS = os.path.expanduser("~/mp305b-fw-re/scripts")
DST = os.path.expanduser("~/mp305b/spikes/firmware_reconstruct/scripts")
os.makedirs(DST, exist_ok=True)
home = os.path.expanduser("~")
for name in sorted(os.listdir(WS)):
    src = os.path.join(WS, name)
    if not os.path.isfile(src) or not name.endswith((".py", ".java", ".sh")):
        continue
    text = open(src).read()
    if name.endswith(".py") and home + "/mp305b-fw-re/" in text:
        text = re.sub(r"(['\"])" + re.escape(home) + r"/mp305b-fw-re/([^'\"]*)\1",
                      lambda m: 'os.path.expanduser("~/mp305b-fw-re/' + m.group(2) + '")', text)
        if not re.search(r"^import os\b|^import .*\bos\b", text, re.M):
            lines = text.split("\n")
            i = next(k for k, l in enumerate(lines) if l.startswith("import ") or l.startswith("from "))
            lines.insert(i, "import os")
            text = "\n".join(lines)
    assert home not in text, name
    open(os.path.join(DST, name), "w").write(text)
    shutil.copymode(src, os.path.join(DST, name))
    print("synced", name)
