// assets.c
#include <stdio.h>
#include <string.h>
#include "assets.h"

void addAsset(Asset list[], int *count) {
    if (*count >= MAX_ASSETS) {
        printf("Asset list is full.\n");
        return;
    }

    Asset a;
    a.id = *count + 1;

    printf("Enter asset name: ");
    fgets(a.name, sizeof(a.name), stdin);
    a.name[strcspn(a.name, "\n")] = '\0';

    printf("Enter asset type (e.g. Vehicle, Building): ");
    fgets(a.type, sizeof(a.type), stdin);
    a.type[strcspn(a.type, "\n")] = '\0';

    printf("Enter purchase value: ");
    scanf("%f", &a.purchaseValue);
    getchar(); // clear leftover newline

    printf("Enter department: ");
    fgets(a.department, sizeof(a.department), stdin);
    a.department[strcspn(a.department, "\n")] = '\0';

    printf("Enter condition (e.g. Good, Fair, Poor): ");
    fgets(a.condition, sizeof(a.condition), stdin);
    a.condition[strcspn(a.condition, "\n")] = '\0';

    list[*count] = a;
    (*count)++;

    printf("Asset added with ID %d.\n", a.id);
}

void displayAssets(Asset list[], int count) {
    if (count == 0) {
        printf("No assets to display.\n");
        return;
    }
    for (int i = 0; i < count; i++) {
        printf("ID: %d | Name: %s | Type: %s | Value: N$%.2f | Dept: %s | Condition: %s\n",
               list[i].id, list[i].name, list[i].type, list[i].purchaseValue,
               list[i].department, list[i].condition);
    }
}

void searchAsset(Asset list[], int count) {
    char query[50];
    printf("Enter asset name to search: ");
    fgets(query, sizeof(query), stdin);
    query[strcspn(query, "\n")] = '\0';

    for (int i = 0; i < count; i++) {
        if (strcmp(list[i].name, query) == 0) {
            printf("Found: ID %d | Type: %s | Value: N$%.2f | Dept: %s | Condition: %s\n",
                   list[i].id, list[i].type, list[i].purchaseValue,
                   list[i].department, list[i].condition);
            return;
        }
    }
    printf("Asset not found.\n");
}