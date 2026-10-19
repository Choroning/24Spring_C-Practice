/**
 * @file    A10104-1_C07Q2.c
 * @brief   Q2. 선택 정렬 변형
 * @author  박철원 (Cheolwon Park)
 * @date    2024-05-11
 */

#include <stdio.h>
#define SIZE 5

void print_array(int arr[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int data[SIZE] = { 52, 31, 28, 17, 46 };
    int i, j, temp;
    int index_max;

    for (i = SIZE - 1; i >= 0; i--) {
        index_max = i;

        for (j = i - 1; j >= 0; j--) {
            if (data[index_max] < data[j])
                index_max = j;
        }

        if (i != index_max) {
            temp = data[i];
            data[i] = data[index_max];
            data[index_max] = temp;
        }

        printf("i = %d회 반복 후 배열 : ", i);
        print_array(data, SIZE);
    }

    return 0;
}
