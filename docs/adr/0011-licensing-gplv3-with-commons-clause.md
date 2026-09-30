# ADR-0011: License under GNU GPLv3 with Commons Clause

- Status: Accepted
- Date: 2026-09-30
- Decided by: user, on the agent's recommendation
- Related: [AGENTS.md](../../AGENTS.md), [LICENSE](../../LICENSE)

## Context

The repository contains `mp305-core` (Rust library), `mp305-app` (egui desktop
application), `mp305` (Python library), and protocol specifications derived
from firmware reverse engineering. The project needs an explicit license.

The user's requirements for the license:
1. Companies and engineers must be allowed to use the software *for* their
   business (e.g. running the app or libraries in internal labs to power and
   test devices under test (DUTs)).
2. Selling the library, desktop app, or any derivative works must be strictly
   illegal.

## Decision

The project is licensed under the **GNU General Public License version 3.0
combined with the Commons Clause License Condition v1.0** (GPLv3 + Commons
Clause).

Under this license:
- Any individual or organization may freely use, run, inspect, and modify the
  software for personal, educational, research, and internal business
  operations (such as bench testing and automation).
- Anyone redistributing the software or derivative works must share source code
  under the terms of the GPLv3.
- Selling the software or any derivative works, charging fees for distribution,
  or offering it as a paid commercial product or service is strictly
  prohibited by the Commons Clause condition.

## Alternatives considered

- Permissive licenses (MIT, Apache 2.0): rejected. They permit third parties
  to sell the software and proprietary derivatives.
- Pure GNU GPLv3 or AGPLv3: rejected. While GPL/AGPL copyleft imposes strong
  source-disclosure requirements, the FSF definition allows charging for
  copies/distribution, so it does not make commercial sale strictly illegal.
- PolyForm Noncommercial 1.0.0: rejected. Its ban on all commercial use would
  cast legal doubt on legitimate internal business use (e.g. testing DUTs in
  a corporate lab).
- PolyForm Internal Use 1.0.0: considered. While it permits internal business
  use and forbids selling, it also prohibits all third-party redistribution,
  preventing community package maintenance (AUR, Homebrew, Debian) and public
  forks.
- PolyForm Perimeter 1.0.0: considered. It bans competitive products, but
  leaves a loophole where non-competing commercial derivatives could be sold.

## Consequences

- The `LICENSE` file in the repository root contains the Commons Clause
  condition followed by the GNU GPLv3 text.
- Crates and Python package metadata will indicate GPLv3 with Commons Clause
  restrictions.
- The project is classified as source-available / copyleft with a no-sale
  commercial restriction.
