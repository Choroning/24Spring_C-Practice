/**
 * @file    A10303-1_C09Q2.c
 * @brief   Q2. 문자열 뒤집기
 * @author  박철원 (Cheolwon Park)
 * @date    2024-05-31
 */

#include <stdio.h>

void revStr(char* str) {
    char* start = str;
    char* end = str;

    while (*end) {
        end++;
    }
    end--;
	
    while (start < end) {
        char tmp = *start;
        *start = *end;
        *end = tmp;

        start++;
        end--;
    }
}

int main() {
    char str[100];

    printf("Input str: ");
    if (fgets(str, sizeof(str), stdin)) {
        for (int i = 0; str[i]; i++) {
            if (str[i] == '\n') {
                str[i] = '\0';
                break;
            }
        }

        revStr(str);
        printf("Reversed str: %s\n", str);
    }
}
