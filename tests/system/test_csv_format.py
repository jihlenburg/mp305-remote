"""ST-037: the library and the app write CSV in one format (SR-037).

The files come from HIL runs: the one ST-034 writes (its path is in the
run's record) and one the app recorded. Name them in `MP305_CSV_FILES`,
separated by the OS path separator (`:` on macOS and Linux, `;` on Windows).
The test reads files only; it uses no supply.
"""

from __future__ import annotations

from typing import TYPE_CHECKING

import pytest

from tests.system.support import CSV_HEADER, csv_problems

if TYPE_CHECKING:
    from tests.system.conftest import OptIns


@pytest.mark.spec("ST-037")
def test_st037_library_and_app_files_have_one_header_and_format(opt_ins: OptIns) -> None:
    """Parse a file from ST-034 and one from the app."""
    files = opt_ins.csv_files
    if len(files) < 2:
        pytest.skip(
            "needs a CSV file from ST-034 and one from the app; set MP305_CSV_FILES to both, "
            "separated by the OS path separator"
        )
    headers = set()
    for path in files:
        data = path.read_bytes()
        assert csv_problems(data) == [], path
        headers.add(data.decode("utf-8").splitlines(keepends=True)[0])
    assert headers == {CSV_HEADER}
