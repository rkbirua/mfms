#ifndef BUDGET_H
#define BUDGET_H

#define MAX_DEPARTMENTS 20
#define MAX_NAME_LEN 50

typedef struct {
    char department[MAX_NAME_LEN];
    double allocated;
    double spent;
    double remaining;
    int exceeded;   /* 1 = EXCEEDED, 0 = WITHIN BUDGET */
} Budget;

/* Shared so the Reports module (Role 4) can read them */
extern Budget budgets[MAX_DEPARTMENTS];
extern int budgetCount;

void addBudget(void);
void displayBudgets(void);
void displayOverspent(void);
void budgetMenu(void);   /* main.c calls this for option 2 */

#endif
