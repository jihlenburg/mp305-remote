#!/usr/bin/env python3
"""Build the reviewed report with Pandoc and LaTeX in an external directory."""

import argparse
from pathlib import Path
import re
import shutil
import subprocess


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--build", type=Path, required=True)
    args = parser.parse_args()
    repo = Path(__file__).resolve().parents[3]
    source = repo / "docs/research/firmware/v51/independent"
    build = args.build.resolve()
    if build.exists() or build.is_relative_to(repo):
        parser.error("Choose a fresh build directory outside the repository")
    build.mkdir(parents=True)
    markdown = (source / "report.md").read_text().split("\n", 1)[1]
    result = subprocess.run(
        ["pandoc", "-f", "markdown", "-t", "latex", "--shift-heading-level-by=-1"],
        input=markdown,
        text=True,
        capture_output=True,
        check=True,
    )
    body = result.stdout
    body = re.sub(r"(\\(?:sub)*section\{)", r"\\Needspace{10\\baselineskip}\n\1", body)
    # Permit wrapping the long opcode list in a narrow comparison-table cell.
    body = re.sub(
        r"\\texttt\{([^{}]+)\}",
        lambda m: "\\texttt{" + m[1].replace("/", "/\\allowbreak{}") + "}",
        body,
    )
    # Keep the last row with the table footer instead of repeating an empty header.
    body = body.replace("\\\\\n\\end{longtable}", "\\\\*\n\\end{longtable}")
    (build / "body.tex").write_text(body)
    shutil.copy2(source / "report-source/preamble.tex", build / "preamble.tex")
    (build / "report.tex").write_text(r"""\input{preamble.tex}
\begin{document}
\title{MP305B firmware recovery and independent comparison}
\author{}
\date{30 September 2026}
\maketitle
\tableofcontents
\clearpage
\input{body.tex}
\end{document}
""")
    for number in (1, 2, 3):
        with (build / f"build-{number}.log").open("w") as log:
            subprocess.run(
                [
                    "pdflatex",
                    "-interaction=nonstopmode",
                    "-halt-on-error",
                    "report.tex",
                ],
                cwd=build,
                stdout=log,
                stderr=subprocess.STDOUT,
                check=True,
            )
    print(build / "report.pdf")


if __name__ == "__main__":
    main()
