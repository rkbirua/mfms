
#include <stdio.h>
#include <stdlib.h>
#include "reports.h"
#include "employees.h"
#include "budget.h"
#include "suppliers.h"
#include "assets.h"

/* Reads a menu choice between min and max. Re-asks until valid. */
static int readMenuChoice(int min, int max)
{
    char line[100];
    char *end;
    long value;

    printf("Enter your choice: ");
    while (1)
    {
        if (fgets(line, sizeof(line), stdin) == NULL)
        {
            return max; /* input closed: leave the menu */
        }
        if (line[0] == '\n')
        {
            continue; /* ignore blank lines (e.g. left over from scanf) */
        }
        value = strtol(line, &end, 10);
        if (end == line || (*end != '\n' && *end != '\0'))
        {
            printf("Invalid input. Please enter a number.\nEnter your choice: ");
            continue;
        }
        if (value < min || value > max)
        {
            printf("Invalid choice. Enter a number from %d to %d.\nEnter your choice: ",
                   min, max);
            continue;
        }
        return (int)value;
    }
}

/* Total pay for one employee: basic salary + allowances. */
static double totalSalary(Employee e)
{
    return (double)e.basicSalary + (double)e.housingAllowance
           + (double)e.transportAllowance;
}

void employeeReport(Employee list[], int count)
{
    int i;
    double salary, total = 0.0, highest, lowest;

    printf("\n========== EMPLOYEE REPORT ==========\n");
    if (count == 0)
    {
        printf("No employees registered yet.\n");
        return;
    }

    highest = totalSalary(list[0]);
    lowest = highest;

    for (i = 0; i < count; i++)
    {
        salary = totalSalary(list[i]);
        total += salary;
        if (salary > highest)
        {
            highest = salary;
        }
        if (salary < lowest)
        {
            lowest = salary;
        }
    }

    printf("Total Employees: %d\n", count);
    printf("Average Salary:  N$%.2f\n", total / count);
    printf("Highest Salary:  N$%.2f\n", highest);
    printf("Lowest Salary:   N$%.2f\n", lowest);
}

void budgetReport(void)
{
    int i, exceededCount = 0;
    double totalAllocated = 0.0, totalSpent = 0.0;

    printf("\n=========== BUDGET REPORT ===========\n");
    if (budgetCount == 0)
    {
        printf("No departmental budgets entered yet.\n");
        return;
    }

    for (i = 0; i < budgetCount; i++)
    {
        totalAllocated += budgets[i].allocated;
        totalSpent += budgets[i].spent;
    }

    printf("Total Allocated Budget: N$%.2f\n", totalAllocated);
    printf("Total Expenditure:      N$%.2f\n", totalSpent);
    printf("Remaining Budget:       N$%.2f\n", totalAllocated - totalSpent);

    printf("\nDepartments exceeding budget:\n");
    for (i = 0; i < budgetCount; i++)
    {
        if (budgets[i].spent > budgets[i].allocated)
        {
            printf("  - %s (over by N$%.2f)\n", budgets[i].department,
                   budgets[i].spent - budgets[i].allocated);
            exceededCount++;
        }
    }
    if (exceededCount == 0)
    {
        printf("  None. All departments are within budget.\n");
    }
}

void supplierReport(Supplier list[], int count)
{
    printf("\n=========== SUPPLIER REPORT =========\n");
    if (count == 0)
    {
        printf("No suppliers registered yet.\n");
        return;
    }
    displaySuppliers(list, count);
}

void assetReport(Asset list[], int count)
{
    printf("\n============ ASSET REPORT ===========\n");
    if (count == 0)
    {
        printf("No assets registered yet.\n");
        return;
    }
    displayAssets(list, count);
}

void displayReports(Employee emps[], int empCount,
                    Supplier sups[], int supCount,
                    Asset assets[], int assetCount)
{
    int choice;

    do
    {
        printf("\n----------- REPORTS MENU -----------\n");
        printf("1. Employee Report\n");
        printf("2. Budget Report\n");
        printf("3. Supplier Report\n");
        printf("4. Asset Report\n");
        printf("5. Back to Main Menu\n");

        choice = readMenuChoice(1, 5);

        switch (choice)
        {
        case 1:
            employeeReport(emps, empCount);
            break;
        case 2:
            budgetReport();
            break;
        case 3:
            supplierReport(sups, supCount);
            break;
        case 4:
            assetReport(assets, assetCount);
            break;
        case 5:
            break;
        }
    } while (choice != 5);
}
