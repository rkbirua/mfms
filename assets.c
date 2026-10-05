// assets.c
#include <stdio.h>
#include <string.h>
#include "validation.h"
#include "assets.h"

/* Validate a temporary record completely before updating shared storage.
 * EOF cancels the operation, so no partial record is inserted. */
void addAsset(Asset list[], int *count) {
    if (*count >= MAX_ASSETS) {
        printf("Asset list is full.\n");
        return;
    }

    Asset a;
    a.id = *count + 1;

    if (!readText("Enter asset name: ", a.name, sizeof(a.name))) return;

    if (!readText("Enter asset type (e.g. Vehicle, Building): ", a.type, sizeof(a.type))) return;

    if (!readNonNegativeFloat("Enter purchase value: ", &a.purchaseValue)) return;

    if (!readText("Enter department: ", a.department, sizeof(a.department))) return;

    if (!readText("Enter condition (e.g. Good, Fair, Poor): ", a.condition, sizeof(a.condition))) return;

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
    if (!readText("Enter asset name to search: ", query, sizeof(query))) return;

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