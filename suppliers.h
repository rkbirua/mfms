// suppliers.h
#ifndef SUPPLIERS_H
#define SUPPLIERS_H

#define MAX_SUPPLIERS 100

typedef struct {
    int id;
    char name[50];
    char email[50];
    char phone[20];
    char town[30];
} Supplier;

void addSupplier(Supplier list[], int *count);
void displaySuppliers(Supplier list[], int count);
void searchSupplier(Supplier list[], int count);

#endif