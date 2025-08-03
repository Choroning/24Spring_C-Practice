/**
 * @file    A10303-2_C08Q3.c
 * @brief   Q3. 항목별 평균 구하기
 * @author  박철원 (Cheolwon Park)
 * @date    2024-05-24
 */

#include <stdio.h>

int main()
{
	int score[6][5] = { {28, 28, 26, 9}, {30, 27, 30, 10}, {25, 26, 24, 8},
		{18, 22, 22, 5}, {24, 25, 30, 10}, {0} };
	int i, j;

	// 총점 score[i][4] = score[i][0] + score[i][1] + score[i][2] + score[i][3]
	for (i = 0; i < 6; i++) { 
		for (j = 0; j < 4; j++) {
			score[i][4] += score[i][j];
		}
	}
	// 평균 score[5][i] = score[0][i] + score[1][i] + score[2][i] + score[3][i] + score[4][i]
	for (i = 0; i < 5; i++) { 
		for (j = 0; j < 5; j++) {
			score[5][i] += score[j][i];
		}
	}

	printf(    "               중간  기말  팀플  출석  총점\n");
	for (i = 0; i < 5; i++) {
		printf("학생    %d번:", i + 1);
		for (j = 0; j < 5; j++) {
			printf("    %2d", score[i][j]);
		}
		printf("\n");
	}
	printf("항목별 평균:  ");
	for (j = 0; j < 5; j++) {
		printf("  %4.1f", score[5][j] / 5.0);
	}
}