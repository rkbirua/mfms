/* Shared line-based validation for every module. */
#include "validation.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <float.h>

int readText(const char *prompt, char *output, size_t capacity)
{
    char line[512], *start, *end;
    int c;
    size_t length;
    if (capacity < 2) return 0;
    for (;;) {
        printf("%s", prompt);
        if (!fgets(line, sizeof line, stdin)) return 0;
        length = strlen(line);
        if (length && line[length - 1] != '\n' && !feof(stdin)) {
            c = getchar();
            if (c != '\n' && c != EOF) {
                while ((c = getchar()) != '\n' && c != EOF) { }
                printf("Input too long. Please try again.\n");
                continue;
            }
        }
        start = line;
        while (isspace((unsigned char)*start)) start++;
        end = start + strlen(start);
        while (end > start && isspace((unsigned char)end[-1])) end--;
        *end = '\0';
        length = (size_t)(end - start);
        if (!length) { printf("This field cannot be empty.\n"); continue; }
        if (length >= capacity) { printf("Input too long. Please try again.\n"); continue; }
        memcpy(output, start, length + 1);
        return 1;
    }
}

int readIntRange(const char *prompt, int min, int max, int *output)
{
    char line[512], *end;
    long value;
    while (readText(prompt, line, sizeof line)) {
        errno = 0;
        value = strtol(line, &end, 10);
        if (errno == ERANGE || end == line || *end || value < min || value > max) {
            printf("Invalid input. Enter a whole number from %d to %d.\n", min, max);
            continue;
        }
        *output = (int)value;
        return 1;
    }
    return 0;
}

static int readAmount(const char *prompt, double limit, double *output)
{
    char line[512], *end;
    double value;
    while (readText(prompt, line, sizeof line)) {
        errno = 0;
        value = strtod(line, &end);
        if (errno == ERANGE || end == line || *end || !isfinite(value) || value < 0 || value > limit) {
            printf("Invalid input. Enter a finite non-negative number in range.\n");
            continue;
        }
        *output = value;
        return 1;
    }
    return 0;
}
int readNonNegativeDouble(const char *prompt, double *output)
{
    return readAmount(prompt, DBL_MAX, output);
}
int readNonNegativeFloat(const char *prompt, float *output)
{
    double value;
    if (!readAmount(prompt, FLT_MAX, &value)) return 0;
    *output = (float)value;
    return 1;
}
int readMenuChoice(int min, int max)
{
    int choice;
    return readIntRange("Enter your choice: ", min, max, &choice) ? choice : max;
}
