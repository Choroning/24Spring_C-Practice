/**
 * @file    Example_SafeCopy.c
 * @brief   Copies a file in binary mode, checking every call and releasing resources through one cleanup label
 * @author  박철원 (Cheolwon Park)
 * @date    2026-11-09
 */

#define _CRT_SECURE_NO_WARNINGS  // allows fopen in Visual Studio
#include <stdio.h>
#include <stdlib.h>

// Returns 0 on success and -1 on failure. Every failure is reported on stderr.
static int copy_file(const char *src_path, const char *dst_path)
{
    int result = -1;
    FILE *src = NULL;
    FILE *dst = NULL;
    char buf[4096];
    size_t n;

    src = fopen(src_path, "rb");
    if (src == NULL) {
        perror(src_path);
        goto cleanup;
    }

    dst = fopen(dst_path, "wb");
    if (dst == NULL) {
        perror(dst_path);
        goto cleanup;
    }

    while ((n = fread(buf, 1, sizeof buf, src)) > 0) {
        if (fwrite(buf, 1, n, dst) != n) {
            perror(dst_path);
            goto cleanup;
        }
    }

    if (ferror(src)) {                  // fread returned 0: end of file, or an error?
        perror(src_path);
        goto cleanup;
    }

    result = 0;

cleanup:
    if (src != NULL) {
        fclose(src);
    }
    if (dst != NULL && fclose(dst) == EOF && result == 0) {
        perror(dst_path);               // Buffered data may fail to reach the file here
        result = -1;
    }
    return result;
}

int main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source> <destination>\n",
                argc > 0 ? argv[0] : "safecopy");
        return 2;
    }

    return copy_file(argv[1], argv[2]) == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
