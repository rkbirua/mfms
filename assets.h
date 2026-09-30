// assets.h
#ifndef ASSETS_H
#define ASSETS_H

#define MAX_ASSETS 100

typedef struct {
    int id;
    char name[50];
    char type[30];
    float purchaseValue;
    char department[30];
    char condition[20];
} Asset;

void addAsset(Asset list[], int *count);
void displayAssets(Asset list[], int count);
void searchAsset(Asset list[], int count);

#endif