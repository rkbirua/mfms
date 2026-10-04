// employees.h
#ifndef EMPLOYEES_H
#define EMPLOYEES_H

#define MAX_EMPLOYEES 100

typedef struct {
    int id;
    char name[50];
    char department[30];
    float basicSalary;
    float housingAllowance;
    float transportAllowance;
} Employee;

void addEmployee(Employee list[], int *count);
void displayEmployees(Employee list[], int count);
void searchEmployee(Employee list[], int count);
void calculateSalary(Employee list[], int count);

#endif