/**
 * @file    Example_Macros.c
 * @brief   Function-like macros with and without parentheses, the # and ## operators, conditional compilation, and predefined macros
 * @author  박철원 (Cheolwon Park)
 * @date    2026-11-09
 */

#include <stdio.h>

#define BAD_SQUARE(x)   x * x           // Deliberately wrong: no parentheses
#define SQUARE(x)       ((x) * (x))

#define PRINT_INT(x)    printf(#x " = %d\n", (x))
#define MAKE_NAME(a, b) a##b

#define STR(x)          #x              // Stringizes the argument as written
#define XSTR(x)         STR(x)          // Expands the argument first, then stringizes it
#define VERSION         12

// Build with -DDEBUG to enable the trace messages.
#ifdef DEBUG
#define TRACE(msg)      fprintf(stderr, "[%s:%d] %s\n", __FILE__, __LINE__, (msg))
#else
#define TRACE(msg)      do { } while (0)
#endif

static void show_function_name(void)
{
    printf("__func__ = %s\n", __func__);
}

int main(void)
{
    int a = 2, b = 3;
    int value12 = 99;

    printf("BAD_SQUARE(a + b) = %d\n", BAD_SQUARE(a + b));
    printf("SQUARE(a + b)     = %d\n", SQUARE(a + b));

    PRINT_INT(a + b);
    printf("MAKE_NAME(value, 12) = %d\n", MAKE_NAME(value, 12));

    printf("STR(VERSION)  = %s\n", STR(VERSION));
    printf("XSTR(VERSION) = %s\n", XSTR(VERSION));

    TRACE("about to print the predefined macros");

    printf("__LINE__ = %d\n", __LINE__);
    printf("__STDC_VERSION__ = %ldL\n", (long)__STDC_VERSION__);
    show_function_name();

    return 0;
}
