# ADR-0008: Quality standards, IEC 61508 functional safety and MISRA-aligned guidelines

- Status: Accepted
- Date: 2026-09-30
- Decided by: user
- Related: ADR-0001, ADR-0003, ADR-0005, ADR-0006, [AGENTS.md](../../AGENTS.md), [docs/v-model/1-user-requirements.md](../v-model/1-user-requirements.md)

## Context

The software controls the ISDT MP305B bench power supply (up to 30 V, 5 A,
150 W). Erroneous behavior (such as unintended output activation, setpoint
corruption, runaway voltage/current, or missed faults) can cause direct property
damage (destruction of devices under test, electrical fires, thermal runaway)
and indirectly human injury (burns, fire, or electric shock).

To systematically mitigate these hazards, this software is treated as an
electrical safety-related system under **IEC 61508**
(Functional Safety of Electrical/Electronic/Programmable Electronic
Safety-related Systems), adhering to **MISRA guidelines** (or equivalent
derivatives for Rust and Python).

## Decision

### 1. IEC 61508 Functional Safety Baseline

The project implements the systematic fault avoidance and architectural
principles of **IEC 61508-3** (Software requirements):

- **Strict V-Model Lifecycle:** Requirements, architecture, detailed design,
  and corresponding test specifications are formally documented and reviewed
  before implementation at each gate (ADR-0001).
- **Hazard Traceability:** Every identified hazard (`H-001` through `H-009` in
  `docs/v-model/1-user-requirements.md`) must have full bidirectional
  traceability to mitigating user requirements (`UR-`), system requirements
  (`SR-`), detailed designs (`DD-`), and test specifications (`AT-`, `ST-`,
  `UT-`).
- **Fail-Safe Defaults & Defensive Architecture:**
  - The power supply output must always default to OFF upon startup,
    disconnection, timeout, or fault.
  - Heartbeat / keep-alive mechanisms detect communication link loss and trigger
    safe shutdown.
    Editorial note (2026-09-30, TBD-022): the two bullets above describe the
    intent, not what this device allows. The supply keeps its output as it
    was when the link drops and only releases remote control, and after a
    link loss nothing can be sent (docs/research/device-model.md 4.4). The
    mitigations are SR-028 (report at once, send nothing), the USB keepalive
    (SR-051), the unclean-exit warning (UR-030) and the bench-safety note
    (UR-031).
  - Input parameters are validated and clamped against strict physical limits
    (0 to 30 V, 0 to 5 A) at all API boundaries.

### 2. MISRA-Aligned Coding Standards for Rust

Since the core logic and protocol implementation reside in Rust (`mp305-core`),
the project adheres to the safety-critical Rust principles established by the
Rust Foundation Safety-Critical Rust Consortium and Ferrocene safety
guidelines:

- **Elimination of Unsafe Code:**
  - `mp305-core` and `mp305-app` enforce `#![forbid(unsafe_code)]`.
  - In `mp305-py`, any unavoidable foreign function interface (FFI) code
    required by PyO3 must be strictly quarantined in a dedicated `ffi` module,
    surrounded by defensive assertions and safety invariants.
- **Zero Panic in Production Code:**
  - Crates enforce `#![deny(clippy::unwrap_used, clippy::expect_used, clippy::panic)]`.
  - All fallible operations must return explicit `Result` or `Option` types and
    handle failure paths deterministically.
- **Defensive Memory & Indexing:**
  - Crates enforce `#![deny(clippy::indexing_slicing)]`. Direct array or slice
    indexing (`slice[i]`) is forbidden; code must use `.get()` with explicit
    bounds checking or error handling.
- **Safe Arithmetic:**
  - Crates enforce `#![deny(clippy::arithmetic_side_effects)]`. All protocol
    arithmetic, setpoint scaling, and checksum calculations must use checked,
    saturating, or widening operations (`checked_add`, `saturating_sub`) to
    prevent arithmetic overflows.
- **Linting & Documentation:**
  - Clippy runs with `-D warnings` and pedantic safety rules.
  - Crates enforce `#![deny(missing_docs)]` and
    `#![warn(clippy::missing_docs_in_private_items)]`. Private items must be
    documented to explain invariants.

### 3. MISRA-Aligned Defensive Standards for Python

Python is used for automation and test scripting (`mp305`), binding to the Rust
core:

- **Strict Static Typing:**
  - `mypy` runs with `strict = true`. No untyped definitions, implicit `Any`,
    or missing return types.
- **Defensive Runtime Parameter Validation:**
  - Python API entry points must perform runtime type and range validation
    (e.g., asserting voltage in $[0.0, 30.0]$ V, current in $[0.0, 5.0]$ A)
    before invoking the native Rust core, providing defense-in-depth.
- **Static Analysis & Security:**
  - Ruff runs with rules `E`, `W`, `F`, `B` (flake8-bugbear for bug-prone code),
    `S` (flake8-bandit for security analysis), and `D` (pydocstyle, Google convention).

### 4. Test Coverage Standards

Line coverage is measured with `cargo llvm-cov` and `pytest-cov`:

| Component | Target |
|---|---|
| Protocol module of `mp305-core` | 95 % |
| Rest of `mp305-core` | 85 % |
| Non-rendering app logic | 80 % |
| Pure-Python code | 90 % |

- GUI drawing code is segregated into `ui/` modules and excluded with
  `cargo llvm-cov --ignore-filename-regex`.
- Every coverage exclusion and skipped/ignored test must carry an explanatory
  comment citing the covering test or TODO item.
- Lowering coverage below target requires an explicit reason in the commit
  message and in `LOGBOOK.md`.

### 5. Hardware-in-the-Loop (HIL) Safety Rules

- Rust HIL tests are named `hil_*`, carry
  `#[ignore = "HIL: needs a real MP305B"]`, and first call a shared
  `hil_device()` helper that panics before any I/O unless both `MP305_HIL=1`
  and `MP305_HIL_DEVICE` are set.
- Python HIL tests carry `@pytest.mark.hil` and are excluded by default in
  `pyproject.toml` (`addopts = "-m 'not hil' --strict-markers"`). A fixture
  skips them unless both environment variables are set.
- An agent never sets `MP305_HIL` unless the user explicitly requests it in
  the current session.
- Defaults stay at 5 V or less and 100 mA or less unless a test documents why
  more is needed.
- Every HIL test ensures the output is switched OFF in its teardown (including
  on panic or failure), and restores any modified settings.

## Alternatives considered

- Treating the project as a hobbyist-grade utility without formal safety
  standards: rejected. A power supply is a physical actuator
  capable of thermal damage, equipment destruction, and electrical fire.
- Relying solely on C/C++ MISRA C:2012: rejected because the project is
  implemented in Rust and Python. The project adopts equivalent safety
  principles adapted to Rust (Safety-Critical Rust / Ferrocene guidelines) and
  Python (strict typing and defensive runtime verification).

## Consequences

- Systematic errors are caught at compile time via strict Rust lints and
  type safety.
- No uncontrolled panics or indexing crashes can occur in the core protocol
  engine.
- CI and local pre-commit checks enforce zero Clippy warnings, 100% doc
  coverage, and strict mypy compliance.
