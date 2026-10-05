# Source code documentation

## Ownership and data flow

`main()` allocates Employee, Supplier and Asset arrays and their record counts.
Add functions receive a pointer to the count; display/search/report functions
receive the current count by value. Budget storage is defined once in `budget.c`
and exposed via `extern` in `budget.h`. Reports read records without changing them.

Each add function builds a local record, validates all required inputs, and only
then writes the record into its array and increments the count. Capacity is
checked first. Closing input during an entry cancels that entry.

## Shared validation API

| Function | Contract |
| --- | --- |
| `readText(prompt, output, capacity)` | Trim surrounding whitespace; reject blank or overlong text; return 1 on success, 0 on EOF |
| `readIntRange(prompt, min, max, output)` | Parse a complete integer with `strtol`; reject overflow, suffixes and out-of-range values |
| `readNonNegativeDouble(prompt, output)` | Parse a complete finite, non-negative double; reject conversion range errors |
| `readNonNegativeFloat(prompt, output)` | Apply numeric rules and check FLT_MAX before converting to float |
| `readMenuChoice(min, max)` | Use integer validation; return max on EOF, so max must mean Back/Exit |

Callers provide valid output pointers. Output values change only on successful
reads. All module input uses these helpers, avoiding mixed scanf/fgets newline
handling. `readText` drains overlong input so its remainder cannot become the next
field. A complete final input line without a newline is accepted.

## Module functions

- Employees: `addEmployee`, `displayEmployees`, `searchEmployee`,
  `calculateSalary`. Total pay = basic + housing + transport allowances.
- Budgets: `addBudget`, `displayBudgets`, `displayOverspent`, `budgetMenu`.
  Private `updateStatus` calculates allocated minus spent and the exceeded flag.
- Suppliers: `addSupplier`, `displaySuppliers`, `searchSupplier`.
- Assets: `addAsset`, `displayAssets`, `searchAsset`.
- Reports: `displayReports`, `employeeReport`, `budgetReport`, `supplierReport`,
  `assetReport`. Private `totalSalary` returns an employee's combined pay.

Employee statistics initialize highest and lowest from the first record, sum
pay in a loop and divide by the nonzero count. Budget reports total allocations
and spending and list each department whose spending exceeds allocation.
Supplier and asset reports reuse the corresponding display functions. All four
reports handle empty arrays. Searches use `strcmp` for exact matches.

## Integration changes

Shared validation replaces duplicate menu parsers and module-local input readers.
Module data structures, menu numbering and public module function signatures are
preserved. Salary display uses a double accumulator to avoid float addition
overflow for individually valid float components. No claim is made that report
aggregation is overflow-proof for arbitrarily large collections of amounts.
