/**
 * @file    Example_DynamicMatrix.c
 * @brief   Three ways to allocate a two-dimensional array at run time: an array of row pointers, one contiguous block, and a pointer to an array
 * @author  박철원 (Cheolwon Park)
 * @date    2026-11-09
 */

#include <stdio.h>
#include <stdlib.h>

#define COLS 3

void matrix_free(int **m, size_t rows)
{
    if (m == NULL) {
        return;
    }
    for (size_t r = 0; r < rows; r++) {
        free(m[r]);
    }
    free(m);
}

int **matrix_alloc(size_t rows, size_t cols)
{
    int **m = malloc(rows * sizeof *m);

    if (m == NULL) {
        return NULL;
    }
    for (size_t r = 0; r < rows; r++) {
        m[r] = malloc(cols * sizeof *m[r]);
        if (m[r] == NULL) {
            matrix_free(m, r);      // frees only the rows already allocated
            return NULL;
        }
    }
    return m;
}

int main(void)
{
    size_t rows = 2;
    size_t cols = COLS;

    // 1. Array of row pointers
    int **a = matrix_alloc(rows, cols);
    if (a == NULL) {
        return 1;
    }
    a[1][2] = 12;
    printf("row pointers : a[1][2] = %d\n", a[1][2]);
    matrix_free(a, rows);

    // 2. One contiguous block with computed indices
    int *b = malloc(rows * cols * sizeof *b);
    if (b == NULL) {
        return 1;
    }
    b[1 * cols + 2] = 12;
    printf("single block : b[1 * cols + 2] = %d\n", b[1 * cols + 2]);
    free(b);

    // 3. Pointer to an array: the column count is fixed at compile time
    int (*c)[COLS] = malloc(rows * sizeof *c);
    if (c == NULL) {
        return 1;
    }
    c[1][2] = 12;
    printf("array pointer: c[1][2] = %d, sizeof *c = %zu\n", c[1][2], sizeof *c);
    free(c);

    return 0;
}
