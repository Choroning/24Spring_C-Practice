/**
 * @file    Example_Variadic.c
 * @brief   Variadic functions: a count-driven sum, a null-terminated join, and a printf-style wrapper over vsnprintf
 * @author  박철원 (Cheolwon Park)
 * @date    2026-11-09
 */

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

// The first parameter tells the function how many int values follow.
static int sum_ints(int count, ...)
{
    va_list ap;
    int total = 0;

    va_start(ap, count);
    for (int i = 0; i < count; i++) {
        total += va_arg(ap, int);
    }
    va_end(ap);

    return total;
}

// A float passed through "..." arrives as a double, so va_arg must name double.
static double average(int count, ...)
{
    va_list ap;
    double total = 0.0;

    va_start(ap, count);
    for (int i = 0; i < count; i++) {
        total += va_arg(ap, double);
    }
    va_end(ap);

    return count > 0 ? total / count : 0.0;
}

// The argument list ends with a null pointer of type const char *.
static void join(char *out, size_t size, const char *first, ...)
{
    va_list ap;
    size_t used = 0;

    out[0] = '\0';
    va_start(ap, first);
    for (const char *s = first; s != NULL; s = va_arg(ap, const char *)) {
        int n = snprintf(out + used, size - used, "%s", s);
        if (n < 0 || (size_t)n >= size - used) {
            break;
        }
        used += (size_t)n;
    }
    va_end(ap);
}

// A printf-style wrapper that forwards its arguments through a va_list.
static void log_line(const char *level, const char *format, ...)
{
    char text[40];
    va_list ap;

    va_start(ap, format);
    int n = vsnprintf(text, sizeof text, format, ap);
    va_end(ap);

    printf("[%s] %s%s\n", level, text,
           (n < 0 || (size_t)n >= sizeof text) ? " (cut)" : "");
}

int main(void)
{
    char c = 'A';    // promoted to int when passed through "..."
    short s = 7;     // promoted to int when passed through "..."
    float f = 2.5f;  // promoted to double when passed through "..."
    char joined[32];

    printf("sum = %d\n", sum_ints(4, 10, 20, c, s));
    printf("average = %.2f\n", average(3, 1.0, f, 4.5));

    join(joined, sizeof joined, "alpha", "-", "beta", (const char *)NULL);
    printf("joined = %s\n", joined);

    log_line("INFO", "score=%d, name=%s", 95, "Kim");
    log_line("WARN", "%s", "this message is longer than the local buffer of forty bytes");

    return 0;
}
