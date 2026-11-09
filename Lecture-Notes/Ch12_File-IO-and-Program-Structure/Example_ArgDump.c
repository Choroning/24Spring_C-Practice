/**
 * @file    Example_ArgDump.c
 * @brief   Prints argc and every command-line argument, then walks argv again until the null pointer argv[argc]
 * @author  박철원 (Cheolwon Park)
 * @date    2026-11-09
 */

#include <stdio.h>

int main(int argc, char *argv[])
{
    printf("argc = %d\n", argc);

    // Index loop: argv[0] through argv[argc - 1] point to the strings.
    for (int i = 0; i < argc; i++) {
        printf("argv[%d] = \"%s\"\n", i, argv[i]);
    }

    // Pointer loop: argv[argc] is a null pointer, so it ends the walk.
    int count = 0;
    for (char **p = argv; *p != NULL; p++) {
        count++;
    }
    printf("strings before the null pointer: %d\n", count);

    return 0;
}
