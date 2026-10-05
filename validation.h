#ifndef VALIDATION_H
#define VALIDATION_H
#include <stddef.h>
/* Return 1 on success, 0 when input closes. Never change output on failure.
 * Text is trimmed; overlong lines are consumed and rejected in full. */
int readText(const char *prompt, char *output, size_t capacity);
int readIntRange(const char *prompt, int min, int max, int *output);
int readNonNegativeDouble(const char *prompt, double *output);
int readNonNegativeFloat(const char *prompt, float *output);
/* EOF chooses max, which must be the menu's Back/Exit option. */
int readMenuChoice(int min, int max);
#endif
