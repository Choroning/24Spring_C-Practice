/**
 * @file    A10303-2_C05Q5.c
 * @brief   Q5. switch 분기 연습
 * @author  박철원 (Cheolwon Park)
 * @date    2024-04-05
 */

#include <stdio.h>

int main()
{
    char ch;

    printf(">> Input the character: ");
    scanf(" %c", &ch);

    switch (ch) {
    case 'c': 
	case 'C':
        printf("-> C Language\n");
        break;
    case 'p': 
	case 'P':
        printf("-> Python\n");
        break;
    case 'j': 
	case 'J':
        printf("-> JAVA\n");
        break;
    case 'l': 
	case 'L':
        printf("-> LISP\n");
        break;
    default:
        printf("-> Input Error!\n");
    }
}
