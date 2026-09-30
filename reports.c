#include <stdio.h>
#include "reports.h"

/* Calculate an employee's total salary using the salary fields required by
 * the Project A specification. */
static double calculateTotalSalary(const Employee *employee)
{
    return employee->basicSalary
         + employee->housingAllowance
         + employee->transportAllowance;
}

void displayEmployeeReport(const Employee employees[], int employeeCount)
{
    int i;
    double totalSalary = 0.0;
    double highestSalary;
    double lowestSalary;
    double salary;

    printf("\n========================================\n");
    printf("             EMPLOYEE REPORT\n");
    printf("========================================\n");

    if (employeeCount <= 0) {
        printf("No employees are currently registered.\n");
        return;
    }

    highestSalary = calculateTotalSalary(&employees[0]);
    lowestSalary = highestSalary;

    for (i = 0; i < employeeCount; i++) {
        salary = calculateTotalSalary(&employees[i]);
        totalSalary += salary;

        if (salary > highestSalary) {
            highestSalary = salary;
        }

        if (salary < lowestSalary) {
            lowestSalary = salary;
        }
    }

    printf("Total Employees : %d\n", employeeCount);
    printf("Average Salary  : N$%.2f\n", totalSalary / employeeCount);
    printf("Highest Salary  : N$%.2f\n", highestSalary);
    printf("Lowest Salary   : N$%.2f\n", lowestSalary);
}

void displayBudgetReport(const DepartmentBudget budgets[], int budgetCount)
{
    int i;
    int exceededCount = 0;
    double totalAllocated = 0.0;
    double totalExpenditure = 0.0;
    double totalRemaining;

    printf("\n========================================\n");
    printf("              BUDGET REPORT\n");
    printf("========================================\n");

    if (budgetCount <= 0) {
        printf("No departmental budgets are currently registered.\n");
        return;
    }

    for (i = 0; i < budgetCount; i++) {
        totalAllocated += budgets[i].allocatedBudget;
        totalExpenditure += budgets[i].expenditure;
    }

    totalRemaining = totalAllocated - totalExpenditure;

    printf("Total Allocated Budget : N$%.2f\n", totalAllocated);
    printf("Total Expenditure      : N$%.2f\n", totalExpenditure);
    printf("Remaining Budget       : N$%.2f\n", totalRemaining);

    printf("\nDepartments Exceeding Budget:\n");
    printf("----------------------------------------\n");

    for (i = 0; i < budgetCount; i++) {
        if (budgets[i].expenditure > budgets[i].allocatedBudget) {
            printf("%-20s  Over by N$%.2f\n",
                   budgets[i].department,
                   budgets[i].expenditure - budgets[i].allocatedBudget);
            exceededCount++;
        }
    }

    if (exceededCount == 0) {
        printf("None. All departments are within budget.\n");
    }
}

void displaySupplierReport(const Supplier suppliers[], int supplierCount)
{
    int i;

    printf("\n===============================================================================================\n");
    printf("                                      SUPPLIER REPORT\n");
    printf("===============================================================================================\n");

    if (supplierCount <= 0) {
        printf("No suppliers are currently registered.\n");
        return;
    }

    printf("%-6s %-24s %-30s %-16s %-15s\n",
           "ID", "Supplier Name", "Email", "Telephone", "Town");
    printf("-----------------------------------------------------------------------------------------------\n");

    for (i = 0; i < supplierCount; i++) {
        printf("%-6d %-24.24s %-30.30s %-16.16s %-15.15s\n",
               suppliers[i].supplierId,
               suppliers[i].name,
               suppliers[i].email,
               suppliers[i].telephone,
               suppliers[i].town);
    }

    printf("\nTotal Suppliers: %d\n", supplierCount);
}

void displayAssetReport(const Asset assets[], int assetCount)
{
    int i;
    double totalAssetValue = 0.0;

    printf("\n============================================================================================================\n");
    printf("                                             ASSET REPORT\n");
    printf("============================================================================================================\n");

    if (assetCount <= 0) {
        printf("No municipal assets are currently registered.\n");
        return;
    }

    printf("%-6s %-22s %-16s %-16s %-20s %-15s\n",
           "ID", "Asset Name", "Type", "Value", "Department", "Condition");
    printf("------------------------------------------------------------------------------------------------------------\n");

    for (i = 0; i < assetCount; i++) {
        printf("%-6d %-22.22s %-16.16s N$%-13.2f %-20.20s %-15.15s\n",
               assets[i].assetId,
               assets[i].name,
               assets[i].type,
               assets[i].purchaseValue,
               assets[i].department,
               assets[i].condition);

        totalAssetValue += assets[i].purchaseValue;
    }

    printf("\nTotal Registered Assets: %d\n", assetCount);
    printf("Total Purchase Value   : N$%.2f\n", totalAssetValue);
}

void displayReportsMenu(const Employee employees[], int employeeCount,
                        const DepartmentBudget budgets[], int budgetCount,
                        const Supplier suppliers[], int supplierCount,
                        const Asset assets[], int assetCount)
{
    int choice;
    int inputStatus;

    do {
        printf("\n========================================\n");
        printf("                 REPORTS\n");
        printf("========================================\n");
        printf("1. Employee Report\n");
        printf("2. Budget Report\n");
        printf("3. Supplier Report\n");
        printf("4. Asset Report\n");
        printf("5. Return to Main Menu\n");
        printf("Enter your choice: ");

        inputStatus = scanf("%d", &choice);

        if (inputStatus != 1) {
            int ch;
            printf("Invalid input. Please enter a number from 1 to 5.\n");
            while ((ch = getchar()) != '\n' && ch != EOF) {
                /* Clear invalid input from the keyboard buffer. */
            }
            continue;
        }

        switch (choice) {
            case 1:
                displayEmployeeReport(employees, employeeCount);
                break;
            case 2:
                displayBudgetReport(budgets, budgetCount);
                break;
            case 3:
                displaySupplierReport(suppliers, supplierCount);
                break;
            case 4:
                displayAssetReport(assets, assetCount);
                break;
            case 5:
                printf("Returning to the main menu...\n");
                break;
            default:
                printf("Invalid choice. Please select an option from 1 to 5.\n");
        }
    } while (choice != 5);
}
