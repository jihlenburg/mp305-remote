# Comparison report source

`report.md` in the parent directory is the editable source. `preamble.tex`
controls presentation. `body.tex` and `report.tex` preserve the final rendered
LaTeX source. The PDF is in the parent directory.

Rebuild with Python, Pandoc and pdfLaTeX installed:

```sh
python3 spikes/firmware_reconstruct/scripts/build_report.py \
  --build /path/to/fresh/external/report-build
```

The builder runs from the repository root and writes all intermediate files
outside it. Render the PDF with `pdftoppm`, inspect every page, and review the
LaTeX log before copying the PDF and generated sources back here. Local links
in the report refer to the parent research bundle; the Markdown edition is the
main way to navigate those sources.
