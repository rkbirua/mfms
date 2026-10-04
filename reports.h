#ifndef REPORTS_H
#define REPORTS_H

#include "employees.h"
#include "suppliers.h"
#include "assets.h"

/* Shows the reports sub-menu. main.c passes in the data to report on.
   Budget data is read from the shared budgets[] array in budget.h. */
void displayReports(Employee emps[], int empCount,
                    Supplier sups[], int supCount,
                    Asset assets[], int assetCount);

/* Individual reports */
void employeeReport(Employee list[], int count);
void budgetReport(void);
void supplierReport(Supplier list[], int count);
void assetReport(Asset list[], int count);

#endif
