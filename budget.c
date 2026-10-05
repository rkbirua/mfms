#include <stdio.h>
#include <string.h>
#include "budget.h"
#include "validation.h"

Budget budgets[MAX_DEPARTMENTS];
int budgetCount = 0;

/* ---------- helpers ---------- */

static void updateStatus(Budget *b) {
    b->remaining = b->allocated - b->spent;
    b->exceeded = (b->spent > b->allocated) ? 1 : 0;
}

/* ---------- main functions ---------- */

/* Validate a temporary record completely before updating shared storage.
 * EOF cancels the operation, so no partial record is inserted. */
void addBudget(void) {
    if (budgetCount >= MAX_DEPARTMENTS) {
        printf("Budget list is full.\n");
        return;
    }

    Budget b;
    if (!readText("Department name: ", b.department, MAX_NAME_LEN)) return;

    for (int i = 0; i < budgetCount; i++) {
        if (strcmp(budgets[i].department, b.department) == 0) {
            printf("That department already exists.\n");
            return;
        }
    }

    if (!readNonNegativeDouble("Allocated budget: ", &b.allocated)) return;
    if (!readNonNegativeDouble("Amount spent: ", &b.spent)) return;
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
        choice = readMenuChoice(1, 4);

        switch (choice) {
            case 1: addBudget(); break;
            case 2: displayBudgets(); break;
            case 3: displayOverspent(); break;
            case 4: break;
            default: printf("Invalid choice. Enter 1-4.\n");
        }
    } while (choice != 4);
}