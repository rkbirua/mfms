// employees.c
#include <stdio.h>
#include <string.h>
#include "employees.h"

static float readNonNegativeFloat(const char *prompt) {
    float value;
    while (1) {
        printf("%s", prompt);
        if (scanf("%f", &value) == 1 && value >= 0) {
            getchar();
            return value;
        }
        printf("Invalid input. Enter a number that is 0 or more.\n");
        while (getchar() != '\n');
    }
}

static void readNonEmptyString(const char *prompt, char *dest, int size) {
    while (1) {
        printf("%s", prompt);
        fgets(dest, size, stdin);
        dest[strcspn(dest, "\n")] = '\0';
        if (strlen(dest) > 0) {
            return;
        }
        printf("This field cannot be empty.\n");
    }
}

void addEmployee(Employee list[], int *count) {
    if (*count >= MAX_EMPLOYEES) {
        printf("Employee list is full.\n");
        return;
    }

    Employee e;
    e.id = *count + 1;

    readNonEmptyString("Enter employee name: ", e.name, sizeof(e.name));
    readNonEmptyString("Enter department: ", e.department, sizeof(e.department));
    e.basicSalary = readNonNegativeFloat("Enter basic salary: ");
    e.housingAllowance = readNonNegativeFloat("Enter housing allowance: ");
    e.transportAllowance = readNonNegativeFloat("Enter transport allowance: ");

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
    printf("Enter employee name to search: ");
    fgets(query, sizeof(query), stdin);
    query[strcspn(query, "\n")] = '\0';

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
    printf("Enter employee ID: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid ID.\n");
        while (getchar() != '\n');
        return;
    }
    getchar();

    for (int i = 0; i < count; i++) {
        if (list[i].id == id) {
            float total = list[i].basicSalary + list[i].housingAllowance + list[i].transportAllowance;
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