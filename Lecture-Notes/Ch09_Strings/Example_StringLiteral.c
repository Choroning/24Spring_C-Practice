/**
 * @file    Example_StringLiteral.c
 * @brief   A char pointer to a string literal can read the string, but changing a character of the literal is a run-time error
 * @author  박철원 (Cheolwon Park)
 * @date    2024-06-03
 */

#include <stdio.h>

int main()
{
    char* pc = "AbCde";

    printf("%p \n", pc);
    printf("%s \n", pc);

    pc[1] = 'B';        // attempt to change a string literal through a pointer -> run-time error
    puts(pc);
}
