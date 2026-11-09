/**
 * @file    Example_SafeInput.c
 * @brief   Reads lines with fgets, parses them with sscanf, and builds bounded output with snprintf
 * @author  박철원 (Cheolwon Park)
 * @date    2026-11-09
 */

#include <stdio.h>
#include <string.h>

#define LINE_SIZE 32
#define NAME_SIZE 16

// Reads one line into buf and removes the newline.
// Returns 1 on success, 0 at end of input, and -1 when the line did not fit.
static int read_line(char *buf, int size)
{
    if (fgets(buf, size, stdin) == NULL) {
        return 0;
    }

    size_t len = strcspn(buf, "\n");
    if (buf[len] == '\n') {
        buf[len] = '\0';
        return 1;
    }
    if (feof(stdin)) {       // the last line of the input may have no newline
        return 1;
    }

    // No newline in the buffer: the rest of the line is still in the stream
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
    return -1;
}

// Formats into out and reports truncation through the return value.
static int format_line(char *out, size_t size, const char *name, int age)
{
    int n = snprintf(out, size, "%s is %d years old", name, age);
    return n >= 0 && (size_t)n < size;
}

int main(void)
{
    char line[LINE_SIZE];
    int status;

    while ((status = read_line(line, sizeof line)) != 0) {
        char name[NAME_SIZE];
        int age;

        if (status < 0) {
            printf("too long: the line was discarded\n");
            continue;
        }

        // sscanf returns the number of items it stored
        if (sscanf(line, "%15s %d", name, &age) != 2) {
            printf("bad format: \"%s\"\n", line);
            continue;
        }

        char out[24];
        int complete = format_line(out, sizeof out, name, age);
        printf("%s%s\n", out, complete ? "" : " (truncated)");
    }

    return 0;
}
