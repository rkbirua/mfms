// employees.c
#include <stdio.h>
#include <string.h>
#include "employees.h"
#include "validation.h"
#include <limits.h>

/* Validate a temporary record completely before updating shared storage.
 * EOF cancels the operation, so no partial record is inserted. */
void addEmployee(Employee list[], int *count) {
    if (*count >= MAX_EMPLOYEES) {
        printf("Employee list is full.\n");
        return;
    }

    Employee e;
    e.id = *count + 1;

    if (!readText("Enter employee name: ", e.name, sizeof(e.name))) return;
    if (!readText("Enter department: ", e.department, sizeof(e.department))) return;
    if (!readNonNegativeFloat("Enter basic salary: ", &e.basicSalary)) return;
    if (!readNonNegativeFloat("Enter housing allowance: ", &e.housingAllowance)) return;
    if (!readNonNegativeFloat("Enter transport allowance: ", &e.transportAllowance)) return;

    list[*count] = e;
    (*count)++;

    printf("Employee added with ID %d.\n", e.id);
}

void displayEmployees(Employee list[], int count) {
    if (count == 0) {
        printf("No employees to display.\n");
        return;
    }
    for (int i = 0; i < count; i++) {
        printf("ID: %d | Name: %s | Dept: %s | Basic: N$%.2f | Housing: N$%.2f | Transport: N$%.2f\n",
               list[i].id, list[i].name, list[i].department,
               list[i].basicSalary, list[i].housingAllowance, list[i].transportAllowance);
    }
}

void searchEmployee(Employee list[], int count) {
    char query[50];
    if (!readText("Enter employee name to search: ", query, sizeof query)) return;

    for (int i = 0; i < count; i++) {
        if (strcmp(list[i].name, query) == 0) {
            printf("Found: ID %d | Dept: %s | Basic: N$%.2f | Housing: N$%.2f | Transport: N$%.2f\n",
                   list[i].id, list[i].department, list[i].basicSalary,
                   list[i].housingAllowance, list[i].transportAllowance);
            return;
        }
    }
    printf("Employee not found.\n");
}

void calculateSalary(Employee list[], int count) {
    int id;
    if (!readIntRange("Enter employee ID: ", 1, INT_MAX, &id)) return;

    for (int i = 0; i < count; i++) {
        if (list[i].id == id) {
            double total = (double)list[i].basicSalary + list[i].housingAllowance + list[i].transportAllowance;
            printf("Employee: %s\n", list[i].name);
            printf("Basic Salary: N$%.2f\n", list[i].basicSalary);
            printf("Housing Allowance: N$%.2f\n", list[i].housingAllowance);
            printf("Transport Allowance: N$%.2f\n", list[i].transportAllowance);
            printf("Total Salary: N$%.2f\n", total);
            return;
        }
    }
    printf("Employee ID not found.\n");
}