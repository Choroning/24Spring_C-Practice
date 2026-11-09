/**
 * @file    Example_FixedWidth.c
 * @brief   Fixed-width integer types with their format macros, plus size_t, ptrdiff_t, offsetof, limits, and bool
 * @author  박철원 (Cheolwon Park)
 * @date    2026-11-09
 */

#include <inttypes.h>
#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

struct record {
    char   tag;
    int    count;
    double score;
};

int main(void)
{
    // Exact-width, minimum-width, and fastest types
    printf("int8_t  %zu, int32_t  %zu, int64_t  %zu\n",
           sizeof(int8_t), sizeof(int32_t), sizeof(int64_t));
    printf("int_least16_t %zu, int_fast16_t %zu\n",
           sizeof(int_least16_t), sizeof(int_fast16_t));

    // Format macros from <inttypes.h> expand to string literals
    int32_t  celsius = -40;
    uint64_t bytes   = UINT64_C(1099511627776);
    printf("celsius = %" PRId32 ", bytes = %" PRIu64 "\n", celsius, bytes);
    printf("PRId32 is \"%s\", PRIu64 is \"%s\"\n", PRId32, PRIu64);

    // size_t and ptrdiff_t
    int data[5] = {10, 20, 30, 40, 50};
    size_t count = sizeof data / sizeof data[0];
    ptrdiff_t distance = &data[4] - &data[1];
    printf("count = %zu, distance = %td\n", count, distance);

    // Counting down with an unsigned index: the test i > 0 stops the loop safely
    for (size_t i = count; i > 0; i--) {
        printf("%d ", data[i - 1]);
    }
    printf("\n");

    // offsetof shows the padding the compiler inserted
    printf("sizeof(struct record) = %zu\n", sizeof(struct record));
    printf("offsets: tag %zu, count %zu, score %zu\n",
           offsetof(struct record, tag),
           offsetof(struct record, count),
           offsetof(struct record, score));

    // Limits of the integer types on this implementation
    printf("CHAR_BIT = %d, INT_MIN = %d, INT_MAX = %d\n", CHAR_BIT, INT_MIN, INT_MAX);
    printf("LLONG_MAX = %lld, SIZE_MAX = %zu\n", LLONG_MAX, SIZE_MAX);

    // Conversion to bool produces 0 or 1, unlike conversion to a narrow integer type
    int big = 256;
    bool as_bool = big;
    unsigned char as_char = (unsigned char)big;
    printf("(bool)256 = %d, (unsigned char)256 = %d\n", as_bool, as_char);

    return 0;
}
