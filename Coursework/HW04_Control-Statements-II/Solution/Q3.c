/**
 * @file    A10303-2_C05Q3.c
 * @brief   Q3. switch-if 변환 (1)
 * @author  박철원 (Cheolwon Park)
 * @date    2024-04-05
 */

#include <stdio.h>

int main()
{
    int score;
    printf(">> Input score(0~100): ");
    scanf(" %d", &score);

    switch ((score < 0 || score > 100) ? -1 : (score / 10)) {
    case 10:
    case 9:
        printf("%d is a/an A!", score);
        break;
    case 8:
        printf("%d is a/an B!", score);
        break;
    case 7:
        printf("%d is a/an C!", score);
        break;
    case 6:
        printf("%d is a/an D!", score);
        break;
    case 5: 
	case 4: 
	case 3: 
	case 2: 
	case 1: 
	case 0:
        printf("%d is a/an F!", score);
        break;
    default:
        printf("Input error!");
    }

    return 0;
}
