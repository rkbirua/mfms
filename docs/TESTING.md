# Validation and integration testing

Date: 5 October 2026. Base: `17e9f24` on main. Tooling: GCC, Python 3, Linux.
Run `python3 tests/test_system.py` from the repository. The recorded output is in
`test-results.txt`. Tests compile the integrated application with warnings treated
as errors, then launch independent processes using scripted console input.

| Test | Verified result |
| --- | --- |
| Empty reports | Four empty-data messages; return to main |
| Menu validation | Blank, letters, invalid range, suffix and integer overflow rejected |
| Employees | Add/display/search; 1300 and 2500 salaries give average 1900, min 1300, max 2500 |
| Budgets | 3000 allocated, 1700 spent, 1300 remaining; IT overspent by 200; duplicate rejected |
| Suppliers/assets | Add/display/search, missing-name searches and both reports |
| Asset numeric validation | Negative, text, suffix, NaN, infinity and overflow rejected |
| Employee/budget amounts | Invalid salary, allowance, allocation and spending rejected |
| Text validation | Whitespace-only and overlong names rejected without field contamination |
| Menu EOF | Input closure exits each of the six menus without hanging |
| Partial-record EOF | No incomplete employee, budget, supplier or asset inserted |
| Capacity | 100 suppliers accepted; entry 101 rejected |
| Equal budget | Spending equal to allocation remains within budget |

All 12 test methods passed. Capacity is exercised for suppliers; the other
capacity guards were reviewed in source but not individually boundary-tested.
This is automated integration testing, not proof that every possible input is
correct. Windows runtime, email/phone semantics and extreme aggregate monetary
values are outside the recorded verification.

Before demonstration, each member should run the program locally, explain their
own module, show an invalid-input example and locate their own commits.
