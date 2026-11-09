/**
 * @file    Example_RepeatWords.c
 * @brief   Complete command-line program: option loop, checked number conversion, usage message, and exit status
 * @author  박철원 (Cheolwon Park)
 * @date    2026-11-09
 */

#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STATUS_USAGE 2  // Usage errors get their own exit status, separate from run-time failures

static int usage(const char *prog)
{
    fprintf(stderr, "Usage: %s [-u] [-n count] [--] word...\n", prog);
    return STATUS_USAGE;
}

// Converts all of s to an int. Returns 1 on success and 0 on failure.
static int parse_int(const char *s, int *out)
{
    char *end;

    errno = 0;                                      // strtol never clears errno itself
    long value = strtol(s, &end, 10);

    if (end == s || *end != '\0' || errno == ERANGE) // No digits, trailing text, or out of range
        return 0;
    if (value < INT_MIN || value > INT_MAX)         // Fits in a long but not in an int
        return 0;

    *out = (int)value;
    return 1;
}

int main(int argc, char *argv[])
{
    const char *prog = (argc > 0 && argv[0][0] != '\0') ? argv[0] : "repeat";
    int count = 1, upper = 0, i = 1;

    // Option loop: stops at the first argument that is not an option.
    while (i < argc && argv[i][0] == '-' && argv[i][1] != '\0') {
        if (strcmp(argv[i], "--") == 0) {           // End of the options
            i++;
            break;
        } else if (strcmp(argv[i], "-u") == 0) {
            upper = 1;
            i++;
        } else if (strcmp(argv[i], "-n") == 0) {
            if (i + 1 >= argc || !parse_int(argv[i + 1], &count) || count < 0) {
                fprintf(stderr, "%s: -n needs a non-negative count\n", prog);
                return STATUS_USAGE;
            }
            i += 2;                                 // Skip -n and its value
        } else {
            fprintf(stderr, "%s: unknown option: %s\n", prog, argv[i]);
            return usage(prog);
        }
    }
    if (i >= argc)                                  // At least one word is required
        return usage(prog);

    for (; i < argc; i++) {
        for (int k = 0; k < count; k++) {
            for (const char *p = argv[i]; *p != '\0'; p++) {
                int c = (unsigned char)*p;          // <ctype.h> needs an unsigned char value
                putchar(upper ? toupper(c) : c);
            }
            putchar('\n');
        }
    }
    return EXIT_SUCCESS;
}
