// suppliers.c
#include <stdio.h>
#include <string.h>
#include "validation.h"
#include "suppliers.h"

/* Validate a temporary record completely before updating shared storage.
 * EOF cancels the operation, so no partial record is inserted. */
void addSupplier(Supplier list[], int *count) {
    if (*count >= MAX_SUPPLIERS) {
        printf("Supplier list is full.\n");
        return;
    }

    Supplier s;
    s.id = *count + 1;

    if (!readText("Enter supplier name: ", s.name, sizeof(s.name))) return;

    if (!readText("Enter email: ", s.email, sizeof(s.email))) return;

    if (!readText("Enter phone: ", s.phone, sizeof(s.phone))) return;

    if (!readText("Enter town: ", s.town, sizeof(s.town))) return;

    list[*count] = s;
    (*count)++;

    printf("Supplier added with ID %d.\n", s.id);
}

void displaySuppliers(Supplier list[], int count) {
    if (count == 0) {
        printf("No suppliers to display.\n");
        return;
    }
    for (int i = 0; i < count; i++) {
        printf("ID: %d | Name: %s | Email: %s | Phone: %s | Town: %s\n",
               list[i].id, list[i].name, list[i].email, list[i].phone, list[i].town);
    }
}

void searchSupplier(Supplier list[], int count) {
    char query[50];
    if (!readText("Enter supplier name to search: ", query, sizeof(query))) return;

    for (int i = 0; i < count; i++) {
        if (strcmp(list[i].name, query) == 0) {
            printf("Found: ID %d | %s | %s | %s\n",
                   list[i].id, list[i].email, list[i].phone, list[i].town);
            return;
        }
    }
    printf("Supplier not found.\n");
}