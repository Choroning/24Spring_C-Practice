/**
 * @file    A10303-1_C09Q3.c
 * @brief   Q3. 문자열 분리
 * @author  박철원 (Cheolwon Park)
 * @date    2024-05-27
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char str[100];

    printf("Input str: ");
    if (fgets(str, sizeof(str), stdin)) {
        str[strcspn(str, "\n")] = '\0';

        for (int i = 0; i < strlen(str); i++) {
            putchar(isspace((unsigned char)str[i]) ? '\n' : str[i]);
        }
        putchar('\n');
    }

    return 0;
}
