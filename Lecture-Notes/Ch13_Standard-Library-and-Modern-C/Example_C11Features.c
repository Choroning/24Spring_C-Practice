/**
 * @file    Example_C11Features.c
 * @brief   Tour of C11: _Generic, static assertions, noreturn, anonymous members, alignment, Unicode string literals
 * @author  박철원 (Cheolwon Park)
 * @date    2026-11-09
 */

#include <assert.h>
#include <stdalign.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdnoreturn.h>

// _Generic selects an expression by the type of its controlling expression
#define TYPE_NAME(x) _Generic((x),       \
    int:          "int",                 \
    long:         "long",                \
    double:       "double",              \
    char *:       "char *",              \
    const char *: "const char *",        \
    default:      "other")

// A type-generic absolute value: the selection picks the function to call
#define ABS_VALUE(x) _Generic((x),       \
    long:    labs,                       \
    default: abs)(x)

static_assert(sizeof(int32_t) == 4, "int32_t must occupy exactly 4 bytes");

noreturn static void fail(const char *reason)
{
    fprintf(stderr, "fatal: %s\n", reason);
    exit(EXIT_FAILURE);
}

// Anonymous union: its members are accessed as if they belonged to the outer struct
struct value {
    int kind;                // 0 = integer, 1 = real
    union {
        long   integer;
        double real;
    };
};

// Anonymous struct inside a union: the same storage under two sets of names
struct vec2 {
    union {
        struct { double x, y; };
        double v[2];
    };
};

int main(void)
{
    char text[] = "abc";
    printf("%s, %s, %s, %s, %s\n", TYPE_NAME(1), TYPE_NAME(1L), TYPE_NAME(1.0),
           TYPE_NAME(text), TYPE_NAME(1.0f));
    printf("ABS_VALUE: %d, %ld\n", ABS_VALUE(-3), ABS_VALUE(-4L));

    struct value v = { .kind = 1, .real = 2.5 };
    printf("kind = %d, real = %.1f\n", v.kind, v.real);

    struct vec2 u = { .x = 1.5, .y = 2.5 };
    printf("v[0] = %.1f, v[1] = %.1f\n", u.v[0], u.v[1]);

    alignas(32) char blob[64];
    printf("alignof(double) = %zu, blob mod 32 = %zu\n",
           alignof(double), (size_t)blob % 32);

    // UTF-16 and UTF-32 literals: char16_t and char32_t of <uchar.h> are these same types
    const uint_least16_t utf16[] = u"한글";
    const uint_least32_t utf32[] = U"한글";
    const char utf8[] = u8"한글";
    printf("UTF-16: %zu code units, first 0x%04X\n",
           sizeof utf16 / sizeof utf16[0] - 1, (unsigned)utf16[0]);
    printf("UTF-32: %zu code units, first 0x%04X\n",
           sizeof utf32 / sizeof utf32[0] - 1, (unsigned)utf32[0]);
    printf("UTF-8:  %zu bytes\n", sizeof utf8 - 1);

    if ((size_t)blob % 32 != 0) {
        fail("blob is not aligned");
    }

    return 0;
}
