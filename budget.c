#include <stdio.h>
#include <string.h>
#include "budget.h"

Budget budgets[MAX_DEPARTMENTS];
int budgetCount = 0;

/* ---------- helpers ---------- */

static void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

static double readNonNegativeDouble(const char *prompt) {
    double value;
    while (1) {
        printf("%s", prompt);
        if (scanf("%lf", &value) != 1) {
            printf("Invalid input. Please enter a number.\n");
            clearInputBuffer();
        } else if (value < 0) {
            printf("Value cannot be negative.\n");
            clearInputBuffer();
        } else {
            clearInputBuffer();
            return value;
        }
    }
}

static void readName(const char *prompt, char *dest, int size) {
    while (1) {
        printf("%s", prompt);
        if (fgets(dest, size, stdin) == NULL) {
            strcpy(dest, "Unknown");
            return;
        }
        dest[strcspn(dest, "\n")] = '\0';
        if (strlen(dest) == 0) {
            printf("Department name cannot be empty.\n");
        } else {
            return;
        }
    }
}

static void updateStatus(Budget *b) {
    b->remaining = b->allocated - b->spent;
    b->exceeded = (b->spent > b->allocated) ? 1 : 0;
}

/* ---------- main functions ---------- */

void addBudget(void) {
    if (budgetCount >= MAX_DEPARTMENTS) {
        printf("Budget list is full.\n");
        return;
    }

    Budget b;
    readName("Department name: ", b.department, MAX_NAME_LEN);

    for (int i = 0; i < budgetCount; i++) {
        if (strcmp(budgets[i].department, b.department) == 0) {
            printf("That department already exists.\n");
            return;
        }
    }

    b.allocated = readNonNegativeDouble("Allocated budget: ");
    b.spent = readNonNegativeDouble("Amount spent: ");
    updateStatus(&b);

    budgets[budgetCount++] = b;
    printf("Budget added. Status: %s\n",
           b.exceeded ? "EXCEEDED" : "WITHIN BUDGET");
}

void displayBudgets(void) {
    if (budgetCount == 0) {
        printf("No budgets recorded yet.\n");
        return;
    }
    printf("\n%-20s %12s %12s %12s  %s\n",
           "Department", "Allocated", "Spent", "Remaining", "Status");
    for (int i = 0; i < budgetCount; i++) {
        printf("%-20s %12.2f %12.2f %12.2f  %s\n",
               budgets[i].department, budgets[i].allocated,
               budgets[i].spent, budgets[i].remaining,
               budgets[i].exceeded ? "EXCEEDED" : "WITHIN BUDGET");
    }
}

void displayOverspent(void) {
    int found = 0;
    printf("\nDepartments over budget:\n");
    for (int i = 0; i < budgetCount; i++) {
        if (budgets[i].exceeded) {
            printf("- %s (over by %.2f)\n",
                   budgets[i].department, -budgets[i].remaining);
            found = 1;
        }
    }
    if (!found) printf("None. All departments are within budget.\n");
}

void budgetMenu(void) {
    int choice;
    do {
        printf("\n--- Budget Management ---\n");
        printf("1. Add department budget\n");
        printf("2. Display all budgets\n");
        printf("3. Show overspent departments\n");
        printf("4. Back\n");
        printf("Choice: ");

        if (scanf("%d", &choice) != 1) {
            clearInputBuffer();
            choice = 0;
        } else {
            clearInputBuffer();
        }

        switch (choice) {
            case 1: addBudget(); break;
            case 2: displayBudgets(); break;
            case 3: displayOverspent(); break;
            case 4: break;
            default: printf("Invalid choice. Enter 1-4.\n");
        }
    } while (choice != 4);
}