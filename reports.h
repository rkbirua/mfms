#ifndef REPORTS_H
#define REPORTS_H

/*
 * PAP521S - Programming in Practice
 * Project A: Municipal Financial Management System
 * Student 5 - Reports Module
 *
 * This header defines the data structures used by the reports module and
 * exposes the report functions that can be called from main.c.
 *
 * If your group already has Employee/Budget/Supplier/Asset structures in
 * other header files, keep only the function declarations here and replace
 * these structure definitions with #include statements for your group files.
 */

typedef struct {
    int employeeId;
    char name[60];
    char department[50];
    double basicSalary;
    double housingAllowance;
    double transportAllowance;
} Employee;

typedef struct {
    char department[50];
    double allocatedBudget;
    double expenditure;
} DepartmentBudget;

typedef struct {
    int supplierId;
    char name[80];
    char email[100];
    char telephone[30];
    char town[50];
} Supplier;

typedef struct {
    int assetId;
    char name[80];
    char type[50];
    double purchaseValue;
    char department[50];
    char condition[30];
} Asset;

/* Displays the Reports submenu and allows the user to select a report. */
void displayReportsMenu(const Employee employees[], int employeeCount,
                        const DepartmentBudget budgets[], int budgetCount,
                        const Supplier suppliers[], int supplierCount,
                        const Asset assets[], int assetCount);

/* Individual report functions. */
void displayEmployeeReport(const Employee employees[], int employeeCount);
void displayBudgetReport(const DepartmentBudget budgets[], int budgetCount);
void displaySupplierReport(const Supplier suppliers[], int supplierCount);
void displayAssetReport(const Asset assets[], int assetCount);

#endif
