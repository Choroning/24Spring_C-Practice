/**
 * @file    Example_BinaryRecords.c
 * @brief   Writes fixed-size structure records with fwrite, then reads and updates one of them in place with fseek
 * @author  박철원 (Cheolwon Park)
 * @date    2026-11-09
 */

#define _CRT_SECURE_NO_WARNINGS  // allows fopen in Visual Studio
#include <stdio.h>
#include <stdlib.h>

struct record {
    int id;
    char grade;
    double score;
};

static void die(const char *what)
{
    perror(what);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    const char *path = (argc > 1) ? argv[1] : "records.bin";
    struct record table[3] = {
        {101, 'A', 93.5}, {102, 'B', 81.0}, {103, 'C', 72.25}
    };

    printf("sizeof(struct record) = %zu\n", sizeof(struct record));

    // Write the whole array in one call.
    FILE *fp = fopen(path, "wb");
    if (fp == NULL)
        die(path);
    if (fwrite(table, sizeof table[0], 3, fp) != 3)
        die("fwrite");
    if (fclose(fp) == EOF)
        die("fclose");

    // Reopen for update: "r+b" neither truncates nor creates the file.
    fp = fopen(path, "r+b");
    if (fp == NULL)
        die(path);

    // Jump straight to record 1 (the second record).
    struct record r;
    long offset = 1L * (long)sizeof r;
    if (fseek(fp, offset, SEEK_SET) != 0)
        die("fseek");
    if (fread(&r, sizeof r, 1, fp) != 1)
        die("fread");
    printf("record 1 before: %d %c %.2f\n", r.id, r.grade, r.score);

    // The read moved the position, so go back before overwriting the record.
    r.score = 88.75;
    if (fseek(fp, offset, SEEK_SET) != 0)
        die("fseek");
    if (fwrite(&r, sizeof r, 1, fp) != 1)
        die("fwrite");

    // File size: a binary stream positioned at the end. See the note on SEEK_END.
    if (fseek(fp, 0L, SEEK_END) != 0)
        die("fseek");
    long size = ftell(fp);
    if (size == -1L)
        die("ftell");
    printf("file size: %ld bytes, %ld records\n", size, size / (long)sizeof r);

    // Read everything back from the start.
    rewind(fp);
    while (fread(&r, sizeof r, 1, fp) == 1) {
        printf("%d %c %.2f\n", r.id, r.grade, r.score);
    }
    if (ferror(fp))
        die("fread");

    if (fclose(fp) == EOF)
        die("fclose");
    return EXIT_SUCCESS;
}
