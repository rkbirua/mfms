// suppliers.c
#include <stdio.h>
#include <string.h>
#include "suppliers.h"

void addSupplier(Supplier list[], int *count) {
    if (*count >= MAX_SUPPLIERS) {
        printf("Supplier list is full.\n");
        return;
    }

    Supplier s;
    s.id = *count + 1;

    printf("Enter supplier name: ");
    fgets(s.name, sizeof(s.name), stdin);
    s.name[strcspn(s.name, "\n")] = '\0';

    printf("Enter email: ");
    fgets(s.email, sizeof(s.email), stdin);
    s.email[strcspn(s.email, "\n")] = '\0';

    printf("Enter phone: ");
    fgets(s.phone, sizeof(s.phone), stdin);
    s.phone[strcspn(s.phone, "\n")] = '\0';

    printf("Enter town: ");
    fgets(s.town, sizeof(s.town), stdin);
    s.town[strcspn(s.town, "\n")] = '\0';

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
    printf("Enter supplier name to search: ");
    fgets(query, sizeof(query), stdin);
    query[strcspn(query, "\n")] = '\0';

    for (int i = 0; i < count; i++) {
        if (strcmp(list[i].name, query) == 0) {
            printf("Found: ID %d | %s | %s | %s\n",
                   list[i].id, list[i].email, list[i].phone, list[i].town);
            return;
        }
    }
    printf("Supplier not found.\n");
}