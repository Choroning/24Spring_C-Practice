/**
 * @file    Example_DynamicString.c
 * @brief   Duplicates and concatenates strings in exactly sized heap blocks and reads a line of unknown length from standard input
 * @author  박철원 (Cheolwon Park)
 * @date    2026-11-09
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *string_duplicate(const char *s)
{
    size_t bytes = strlen(s) + 1;       // +1 for the null character
    char *copy = malloc(bytes);

    if (copy != NULL) {
        memcpy(copy, s, bytes);
    }
    return copy;
}

char *string_concat(const char *a, const char *b)
{
    size_t len_a = strlen(a);
    size_t len_b = strlen(b);
    char *out = malloc(len_a + len_b + 1);

    if (out != NULL) {
        memcpy(out, a, len_a);
        memcpy(out + len_a, b, len_b + 1);   // copies b's null character too
    }
    return out;
}

// Returns a heap string without the newline, or NULL at end of input or on failure.
char *read_line(void)
{
    size_t capacity = 16;
    size_t length = 0;
    char *line = malloc(capacity);

    if (line == NULL) {
        return NULL;
    }
    while (fgets(line + length, (int)(capacity - length), stdin) != NULL) {
        length += strlen(line + length);
        if (length > 0 && line[length - 1] == '\n') {
            line[length - 1] = '\0';
            return line;
        }
        if (length + 1 == capacity) {           // the buffer was filled: grow it
            char *tmp = realloc(line, capacity * 2);
            if (tmp == NULL) {
                free(line);
                return NULL;
            }
            line = tmp;
            capacity *= 2;
        }
    }
    if (length > 0) {                           // last line without a newline
        return line;
    }
    free(line);
    return NULL;
}

int main(void)
{
    char *copy = string_duplicate("Hello");
    char *joined = string_concat("Hello, ", "World");

    if (copy == NULL || joined == NULL) {
        free(copy);
        free(joined);
        printf("allocation failed\n");
        return 1;
    }
    copy[0] = 'J';
    printf("%s (%zu)\n", copy, strlen(copy));
    printf("%s (%zu)\n", joined, strlen(joined));
    free(copy);
    free(joined);

    char *line;
    while ((line = read_line()) != NULL) {
        printf("line of %zu characters: %s\n", strlen(line), line);
        free(line);
    }
    return 0;
}
