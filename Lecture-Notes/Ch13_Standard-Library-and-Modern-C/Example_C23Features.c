/**
 * @file    Example_C23Features.c
 * @brief   Requires C23 (-std=c23): nullptr, constexpr, auto, typeof, attributes, checked arithmetic, _BitInt, #embed
 * @author  박철원 (Cheolwon Park)
 * @date    2026-11-09
 */

#include <stdckdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// constexpr: a named constant usable in constant expressions
constexpr int BUFFER_SIZE = 16;

// An enumeration with a fixed underlying type
enum color : unsigned char { RED, GREEN, BLUE };

[[nodiscard]] static int compute(int x)
{
    return x * 2;
}

[[deprecated("use compute instead")]] int old_compute(int x);

// In C23, empty parentheses declare a function with no parameters
static int forty_two()
{
    return 42;
}

static int classify(int n)
{
    int score = 0;

    switch (n) {
    case 1:
        score += 10;
        [[fallthrough]];
    case 2:
        score += 1;
        break;
    default:
        score = -1;
    }
    return score;
}

// An unnamed parameter is allowed in a function definition
static void on_event(int, [[maybe_unused]] void *context)
{
}

int main(void)
{
    // nullptr has its own type, nullptr_t
    int *p = nullptr;
    printf("p is null: %d, sizeof(nullptr_t) = %zu\n", p == nullptr, sizeof(nullptr_t));

    // bool, true, and false are keywords, so no header is needed
    bool ok = true;

    // auto infers the type from the initializer
    auto n = 10;
    auto ratio = 2.5;
    printf("ok = %d, n = %d, ratio = %.1f\n", ok, n, ratio);

    // typeof yields the type of an expression; typeof_unqual drops qualifiers
    typeof(n) m = 3;
    typeof_unqual(const int) w = 4;
    w = w + 1;
    printf("m = %d, w = %d, sizeof(typeof(ratio)) = %zu\n", m, w, sizeof(typeof(ratio)));

    // static_assert needs no message, and {} zero-initializes
    static_assert(BUFFER_SIZE == 16);
    char buffer[BUFFER_SIZE] = {};
    printf("sizeof buffer = %zu, buffer[0] = %d\n", sizeof buffer, buffer[0]);

    // Binary literals and digit separators
    unsigned mask = 0b1010'1010u;
    long million = 1'000'000;
    printf("mask = %u, million = %ld\n", mask, million);

    enum color c = BLUE;
    printf("sizeof(enum color) = %zu, BLUE = %d\n", sizeof c, c);

    printf("compute = %d, classify: %d %d %d, forty_two = %d\n",
           compute(4), classify(1), classify(2), classify(3), forty_two());

    // Checked arithmetic reports overflow and still stores the wrapped result
    int sum;
    if (ckd_add(&sum, 2147483647, 1)) {
        printf("overflow detected, wrapped result = %d\n", sum);
    }

    // Bit-precise integers
    unsigned _BitInt(4) nibble = 15uwb;
    nibble = nibble + 1uwb;
    printf("nibble after increment = %u\n", (unsigned)nibble);

    // strdup joined the standard in C23
    char *copy = strdup("copied");
    if (copy != nullptr) {
        printf("%s\n", copy);
        free(copy);
    }

    // #embed places the first bytes of this very file into the array
    static const unsigned char self[] = {
#embed __FILE__ limit(3)
    };
    printf("embedded %zu bytes: %c%c%c\n", sizeof self, self[0], self[1], self[2]);

    on_event(0, nullptr);
    return 0;
}
