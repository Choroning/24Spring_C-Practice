/**
 * @file    Example_DynamicArray.c
 * @brief   A growable int array that doubles its capacity, counting the elements copied by every growth
 * @author  박철원 (Cheolwon Park)
 * @date    2026-11-09
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    int *data;          // block holding the elements
    size_t size;        // number of elements in use
    size_t capacity;    // number of elements the block can hold
} IntArray;

void array_init(IntArray *v)
{
    v->data = NULL;
    v->size = 0;
    v->capacity = 0;
}

// Returns 1 on success and 0 on failure. On failure the array is unchanged.
int array_push(IntArray *v, int value, size_t *copies)
{
    if (v->size == v->capacity) {
        size_t new_capacity = (v->capacity == 0) ? 1 : v->capacity * 2;

        if (new_capacity > SIZE_MAX / sizeof *v->data) {
            return 0;
        }
        int *tmp = realloc(v->data, new_capacity * sizeof *tmp);
        if (tmp == NULL) {
            return 0;
        }
        *copies += v->size;
        v->data = tmp;
        v->capacity = new_capacity;
    }
    v->data[v->size] = value;
    v->size++;
    return 1;
}

void array_free(IntArray *v)
{
    free(v->data);
    array_init(v);
}

int main(void)
{
    IntArray v;
    size_t copies = 0;
    size_t last_capacity = 0;

    array_init(&v);
    for (int i = 0; i < 1000; i++) {
        if (!array_push(&v, i * i, &copies)) {
            printf("out of memory\n");
            array_free(&v);
            return 1;
        }
        if (v.capacity != last_capacity) {
            printf("size %4zu  capacity %4zu  copies so far %4zu\n",
                   v.size, v.capacity, copies);
            last_capacity = v.capacity;
        }
    }
    printf("%zu pushes copied %zu elements\n", v.size, copies);
    printf("v.data[999] = %d\n", v.data[999]);

    array_free(&v);
    return 0;
}
