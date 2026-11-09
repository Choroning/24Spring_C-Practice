/**
 * @file    Example_QsortBsearch.c
 * @brief   Sorting int values, strings, and structures with qsort, and searching the sorted arrays with bsearch
 * @author  박철원 (Cheolwon Park)
 * @date    2026-11-09
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[16];
    int score;
} Student;

int compare_int(const void *a, const void *b)
{
    int x = *(const int *)a;
    int y = *(const int *)b;

    return (x > y) - (x < y);
}

// The elements are char *, so each argument is a pointer to a char *.
int compare_string(const void *a, const void *b)
{
    const char *const *x = a;
    const char *const *y = b;

    return strcmp(*x, *y);
}

// Higher score first; equal scores are ordered by name.
int compare_student(const void *a, const void *b)
{
    const Student *x = a;
    const Student *y = b;

    if (x->score != y->score) {
        return (x->score < y->score) - (x->score > y->score);
    }
    return strcmp(x->name, y->name);
}

// bsearch passes the key first: here the key is a plain name.
int compare_name_key(const void *key, const void *element)
{
    const char *name = key;
    const Student *s = element;

    return strcmp(name, s->name);
}

int compare_student_name(const void *a, const void *b)
{
    const Student *x = a;
    const Student *y = b;

    return strcmp(x->name, y->name);
}

int main(void)
{
    int values[] = {42, -7, 19, 0, 42, 3};
    size_t count = sizeof values / sizeof values[0];

    qsort(values, count, sizeof values[0], compare_int);
    for (size_t i = 0; i < count; i++) {
        printf("%d ", values[i]);
    }
    printf("\n");

    int key = 19;
    int *hit = bsearch(&key, values, count, sizeof values[0], compare_int);
    if (hit != NULL) {
        printf("19 found at index %td\n", hit - values);
    }

    const char *words[] = {"pear", "apple", "fig"};
    qsort(words, 3, sizeof words[0], compare_string);
    printf("%s %s %s\n", words[0], words[1], words[2]);

    Student students[] = {
        {"Mina", 90}, {"Jisoo", 85}, {"Hana", 90}, {"Bora", 70}, {"Yuna", 85},
    };
    size_t n = sizeof students / sizeof students[0];

    qsort(students, n, sizeof students[0], compare_student);
    for (size_t i = 0; i < n; i++) {
        printf("%-6s %d\n", students[i].name, students[i].score);
    }

    qsort(students, n, sizeof students[0], compare_student_name);
    Student *found = bsearch("Hana", students, n, sizeof students[0], compare_name_key);
    printf("Hana: %d\n", found != NULL ? found->score : -1);

    return 0;
}
