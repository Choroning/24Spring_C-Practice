/**
 * @file    Example_C99Features.c
 * @brief   Tour of C99: designated initializers, compound literals, flexible array members, VLAs, inline, restrict
 * @author  박철원 (Cheolwon Park)
 * @date    2026-11-09
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct point {
    int x;
    int y;
};

struct student {
    char   name[20];
    int    id;
    double gpa;
};

enum month { JAN, FEB, MAR, MONTH_COUNT };

// Designated initializers can name array elements in any order
static const char *const month_name[MONTH_COUNT] = {
    [MAR] = "March",
    [JAN] = "January",
    [FEB] = "February",
};

static int squared_length(struct point p)
{
    return p.x * p.x + p.y * p.y;
}

static inline int square(int n)
{
    return n * n;
}

// A flexible array member: the text is allocated together with the structure
struct message {
    size_t length;
    char   text[];
};

static struct message *message_new(const char *s)
{
    size_t size = strlen(s) + 1;
    struct message *m = malloc(sizeof *m + size);

    if (m != NULL) {
        m->length = size - 1;
        memcpy(m->text, s, size);
    }
    return m;
}

// restrict promises that dst and src do not overlap
static void add_arrays(size_t n, int *restrict dst, const int *restrict src)
{
    for (size_t i = 0; i < n; i++) {
        dst[i] += src[i];
    }
}

#ifndef __STDC_NO_VLA__
// A VLA parameter passes the dimensions of a 2D array at run time
static long sum_grid(size_t rows, size_t cols, int grid[rows][cols])
{
    long total = 0;

    for (size_t r = 0; r < rows; r++) {
        for (size_t c = 0; c < cols; c++) {
            total += grid[r][c];
        }
    }
    return total;
}
#endif

// A variadic macro forwards its extra arguments with __VA_ARGS__
#define DEBUG_PRINT(format, ...) printf("[%s] " format "\n", __func__, __VA_ARGS__)

int main(void)
{
    // Designated initializers for a structure; the unnamed member becomes zero
    struct student s = { .id = 2024001, .name = "Kim" };
    printf("%s %d %.1f\n", s.name, s.id, s.gpa);

    // A designator also resets the position: 6 goes to arr[5]
    int arr[6] = { [0] = 1, [4] = 5, 6 };
    for (int i = 0; i < 6; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n%s, %s\n", month_name[JAN], month_name[MAR]);

    // Compound literals create unnamed objects
    printf("squared_length = %d\n", squared_length((struct point){3, 4}));
    int *p = (int[]){10, 20, 30};
    printf("p[2] = %d\n", p[2]);

    struct message *m = message_new("hello");
    if (m != NULL) {
        printf("length = %zu, text = %s, sizeof = %zu\n", m->length, m->text, sizeof *m);
        free(m);
    }

#ifndef __STDC_NO_VLA__
    size_t n = 4;
    int vla[n];                       // the size comes from a variable
    for (size_t i = 0; i < n; i++) {
        vla[i] = (int)(i * i);
    }
    printf("sizeof vla = %zu, vla[3] = %d\n", sizeof vla, vla[3]);

    int grid[2][3] = {{1, 2, 3}, {4, 5, 6}};
    printf("sum_grid = %ld\n", sum_grid(2, 3, grid));
#endif

    int d[3] = {1, 2, 3};
    const int e[3] = {10, 20, 30};
    add_arrays(3, d, e);
    printf("%d %d %d\n", d[0], d[1], d[2]);

    bool done = square(7) == 49;
    DEBUG_PRINT("done=%d square=%d", done, square(7));
    printf("hex float: %a, 0x1.8p1 = %.1f\n", 0.75, 0x1.8p1);

    return 0;
}
