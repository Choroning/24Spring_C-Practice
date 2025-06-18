/**
 * @file    A10104-1_C7Q3.c
 * @brief   Q3. 빈도와 상대 빈도 계산
 * @author  박철원 (Cheolwon Park)
 * @date    2024-05-11
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int frequency[5] = { 0 }, data[40], i, j;
    double relative_freq[5];

    srand((unsigned)time(NULL));

    for (i = 0; i < 40; i++) {
        data[i] = rand() % 50 + 150;

        switch ((data[i] - 150) / 10) {    // data[i] 값에 해당하는 구간의 인덱스
        case 0:
            frequency[0] += 1;
            break;
        case 1:
            frequency[1] += 1;
            break;
        case 2:
            frequency[2] += 1;
            break;
        case 3:
            frequency[3] += 1;
            break;
        case 4:
            frequency[4] += 1;
            break;
        }
    }
    for (i = 0; i < 5; i++)
        relative_freq[i] = frequency[i] / 40.0;

    printf("배열 출력:\n");
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 10; j++) {
            printf("%d ", data[10 * i + j]);
        }
        printf("\n");
    }

    printf("\n\n\n-----------------------------\n");
    printf("구간 범위     도수    상대도수\n");
    printf("-----------------------------\n");

    for (i = 0; i < 5; i++) {
        printf("%d - %d     %2d     %.3f\n",
               150 + 10 * i, 150 + 10 * i + 9,
               frequency[i], relative_freq[i]);
    }

    return 0;
}
