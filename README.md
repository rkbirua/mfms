# Municipal Financial Management System (MFMS)

PAP521S - Programming in Practice | Project A | C99

Repository: https://github.com/rkbirua/mfms

MFMS is a console application for municipal employees, departmental budgets,
suppliers, assets and reports. Records are held in fixed-size arrays for the
current session; closing the program discards the data.

## Group members

| Student name | Student number |
| --- | --- |
| Joyce Kambonde | 224068520 |
| Japhet Nekwiyu | 225001187 |
| Condolleeza Da Cruz | 224072773 |
| Michael George | 225076462 |
| Maharero Joy | 223113964 |

## Features

- Add, display and search employees; calculate basic salary plus allowances.
- Add departmental budgets and expenditure; show balances and overspending.
- Add, display and search suppliers and assets.
- Generate employee statistics, budget summaries, supplier and asset listings.
- Validate menu choices, non-negative finite amounts and required text fields.
- Return safely from menus and cancel incomplete entries when input closes.

## Build and run

Install GCC and use a terminal in this repository. VS Code is an editor; GCC
must also be installed and available on PATH.

```sh
gcc -std=c99 -Wall -Wextra -pedantic main.c employees.c budget.c suppliers.c assets.c reports.c validation.c -o mfms
./mfms
```

Windows PowerShell:

```powershell
gcc -std=c99 -Wall -Wextra -pedantic main.c employees.c budget.c suppliers.c assets.c reports.c validation.c -o mfms.exe
.\mfms.exe
```

Select options 1-5 for a module or 6 to exit. Each submenu includes Back. Enter
records before generating populated reports. Searches match complete names
case-sensitively after trimming input. IDs are generated sequentially from 1.

## Source code guide

| Files | Purpose |
| --- | --- |
| `main.c` | Owns employee/supplier/asset arrays and counts; dispatches menus |
| `employees.c`, `employees.h` | Employee structure, add/display/search and salary calculation |
| `budget.c`, `budget.h` | Shared budget array/count, derived balance/status and budget menu |
| `suppliers.c`, `suppliers.h` | Supplier structure and add/display/search functions |
| `assets.c`, `assets.h` | Asset structure and add/display/search functions |
| `reports.c`, `reports.h` | Four reports and report menu; reads existing module data |
| `validation.c`, `validation.h` | Shared full-line text, numeric and menu validation |
| `tests/test_system.py` | Compiles the full program and exercises it through standard input |

The public declarations in headers connect modules without duplicating their
structures. See [source design](docs/SOURCE_CODE.md) for data flow and contracts.

## Testing

Requires Python 3 and GCC:

```sh
python3 tests/test_system.py
```

On Windows use `py tests/test_system.py` if `python3` is unavailable. The runner
builds in a temporary directory with `-Wall -Wextra -Werror -pedantic`, then runs
12 black-box tests with timeouts. [Recorded results](docs/test-results.txt) are
from the integrated application on 5 October 2026, on Linux; Windows execution has
not been tested in this environment.

## Documentation and Git workflow

- [Short technical report](docs/TECHNICAL_REPORT.md)
- [Validation and test coverage](docs/TESTING.md)
- [Branch and review workflow](docs/GIT_WORKFLOW.md)

## Limits

Capacity: 100 employees, 20 budgets, 100 suppliers and 100 assets. No file or
database persistence, authentication, editing or deletion. Email and telephone
fields are required text, without format verification. Employee, supplier and
asset names may repeat; department budget duplicates are rejected by exact name.
Money uses float/double rather than fixed-point accounting. Extreme combined
amounts can overflow report totals; ordinary municipal example values are the
tested use case. This is a foundation coursework application, not a production
financial system.
