/*
 * main.c - Municipal Financial Management System (MFMS)
 * Menu loop that connects all the modules.
 *
 * main() owns the employee, supplier and asset arrays and passes them
 * to the functions written by the other group members.
 * Budget data lives inside budget.c, so budgetMenu() needs no arguments.
 */
#include <stdio.h>
#include "validation.h"
#include "employees.h"
#include "budget.h"
#include "suppliers.h"
#include "assets.h"
#include "reports.h"


static void displayMenu(void)
{
    printf("\n========================================\n");
    printf("MUNICIPAL FINANCIAL MANAGEMENT SYSTEM\n");
    printf("========================================\n");
    printf("1. Employee Management\n");
    printf("2. Budget Management\n");
    printf("3. Supplier Management\n");
    printf("4. Asset Management\n");
    printf("5. Reports\n");
    printf("6. Exit\n");
}

static void employeeMenu(Employee list[], int *count)
{
    int choice;

    do
    {
        printf("\n--- EMPLOYEE MANAGEMENT ---\n");
        printf("1. Add Employee\n");
        printf("2. Display Employees\n");
        printf("3. Search Employee\n");
        printf("4. Calculate Salary\n");
        printf("5. Back to Main Menu\n");

        choice = readMenuChoice(1, 5);

        switch (choice)
        {
        case 1:
            addEmployee(list, count);
            break;
        case 2:
            displayEmployees(list, *count);
            break;
        case 3:
            searchEmployee(list, *count);
            break;
        case 4:
            calculateSalary(list, *count);
            break;
        case 5:
            break;
        }
    } while (choice != 5);
}

static void supplierMenu(Supplier list[], int *count)
{
    int choice;

    do
    {
        printf("\n--- SUPPLIER MANAGEMENT ---\n");
        printf("1. Add Supplier\n");
        printf("2. Display Suppliers\n");
        printf("3. Search Supplier\n");
        printf("4. Back to Main Menu\n");

        choice = readMenuChoice(1, 4);

        switch (choice)
        {
        case 1:
            addSupplier(list, count);
            break;
        case 2:
            displaySuppliers(list, *count);
            break;
        case 3:
            searchSupplier(list, *count);
            break;
        case 4:
            break;
        }
    } while (choice != 4);
}

static void assetMenu(Asset list[], int *count)
{
    int choice;

    do
    {
        printf("\n--- ASSET MANAGEMENT ---\n");
        printf("1. Add Asset\n");
        printf("2. Display Assets\n");
        printf("3. Search Asset\n");
        printf("4. Back to Main Menu\n");

        choice = readMenuChoice(1, 4);

        switch (choice)
        {
        case 1:
            addAsset(list, count);
            break;
        case 2:
            displayAssets(list, *count);
            break;
        case 3:
            searchAsset(list, *count);
            break;
        case 4:
            break;
        }
    } while (choice != 4);
}

int main(void)
{
    Employee employees[MAX_EMPLOYEES];
    Supplier suppliers[MAX_SUPPLIERS];
    Asset assets[MAX_ASSETS];
    int employeeCount = 0;
    int supplierCount = 0;
    int assetCount = 0;
    int choice;

    do
    {
        displayMenu();
        choice = readMenuChoice(1, 6);

        switch (choice)
        {
        case 1:
            employeeMenu(employees, &employeeCount);
            break;
        case 2:
            budgetMenu();
            break;
        case 3:
            supplierMenu(suppliers, &supplierCount);
            break;
        case 4:
            assetMenu(assets, &assetCount);
            break;
        case 5:
            displayReports(employees, employeeCount,
                           suppliers, supplierCount,
                           assets, assetCount);
            break;
        case 6:
            printf("Goodbye!\n");
            break;
        }
    } while (choice != 6);

    return 0;
}
