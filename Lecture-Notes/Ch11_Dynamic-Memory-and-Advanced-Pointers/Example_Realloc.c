/**
 * @file    Example_Realloc.c
 * @brief   Grows a malloc block with realloc through a temporary pointer and reports whether each call moved the block
 * @author  박철원 (Cheolwon Park)
 * @date    2026-11-09
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(void)
{
    size_t count = 5;
    int *arr = malloc(count * sizeof *arr);

    if (arr == NULL) {
        printf("allocation failed\n");
        return 1;
    }
    for (size_t i = 0; i < count; i++) {
        arr[i] = (int)(i + 1) * 10;
    }

    size_t sizes[] = {6, 8, 16, 1000};
    for (size_t k = 0; k < sizeof sizes / sizeof sizes[0]; k++) {
        uintptr_t old_address = (uintptr_t)arr;       // an integer copy can be compared after the call
        int *tmp = realloc(arr, sizes[k] * sizeof *tmp);

        if (tmp == NULL) {                            // the old block is still valid
            printf("reallocation failed\n");
            free(arr);
            return 1;
        }
        arr = tmp;
        printf("%4zu elements: %-5s arr[4] = %d\n", sizes[k],
               (uintptr_t)arr == old_address ? "same" : "moved", arr[4]);
    }

    free(arr);
    arr = NULL;
    return 0;
}
