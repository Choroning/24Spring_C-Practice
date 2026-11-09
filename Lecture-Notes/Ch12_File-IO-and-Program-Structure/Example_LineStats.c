/**
 * @file    Example_LineStats.c
 * @brief   Counts the lines and characters of a text file with fgets, including lines longer than the buffer
 * @author  박철원 (Cheolwon Park)
 * @date    2026-11-09
 */

#define _CRT_SECURE_NO_WARNINGS  // allows fopen in Visual Studio
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file>\n", argc > 0 ? argv[0] : "linestats");
        return 2;
    }

    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        perror(argv[1]);
        return 1;
    }

    char buf[16];       // Deliberately small: one line may take several fgets calls
    long lines = 0, chars = 0, longest = 0, current = 0;

    while (fgets(buf, sizeof buf, fp) != NULL) {
        size_t len = strlen(buf);
        chars += (long)len;
        current += (long)len;

        if (len > 0 && buf[len - 1] == '\n') {  // This fgets call reached the end of a line
            lines++;
            if (current - 1 > longest) {        // The newline is not counted in the length
                longest = current - 1;
            }
            current = 0;
        }
    }

    if (current > 0) {                          // The last line had no newline
        lines++;
        if (current > longest) {
            longest = current;
        }
    }

    if (ferror(fp)) {                           // The loop may also end on a read error
        perror(argv[1]);
        fclose(fp);
        return 1;
    }
    fclose(fp);

    printf("lines: %ld, characters: %ld, longest line: %ld\n", lines, chars, longest);
    return 0;
}
