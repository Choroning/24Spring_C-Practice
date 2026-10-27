# Chapter 7 Exercises — Arrays

[Repository Guide](../../README.md) | [English](Exercises.md) | [한국어](Exercises.ko.md)

> **Last Updated:** 2026-10-27
>
> Warming-Up C Programming, 천정아, Ch 7

**Problem Source:** Prof. Younghee Im, Computer Language Ⅰ (DCCS101-04)

**Common Requirement:** In every problem, specify the array size with a macro constant.

---

<br>

## Table of Contents

- [Exercise 1: Computing the Check Digit of a UPC Barcode](#exercise-1-computing-the-check-digit-of-a-upc-barcode)
- [Exercise 2: Selection Sort Variant](#exercise-2-selection-sort-variant)
- [Exercise 3: Computing Frequency and Relative Frequency](#exercise-3-computing-frequency-and-relative-frequency)

---

<br>

## Exercise 1: Computing the Check Digit of a UPC Barcode

**Problem:** A UPC barcode consists of 12 digits in total, and the last, 12th digit is an error-checking digit (check digit) generated from the previous 11 digits. For example, in the barcode 0 36000 29145 2, the last digit 2 is the check digit computed from the first 11 digits 03600029145. Given the example code below, which generates the 12th digit, rewrite it to use an array.

**Example Code:**

```c
#include <stdio.h>
int main() {
    int dig1, dig2, dig3, dig4, dig5, dig6, dig7, dig8, dig9, dig10, dig11, dig12, sum;

    printf("Please enter the first eleven UPC digits, separated by white space: \n");

    scanf("%d%d%d%d%d%d%d%d%d%d%d", &dig1, &dig2, &dig3, &dig4, &dig5, &dig6, &dig7, &dig8, &dig9, &dig10, &dig11);

    printf("입력된 숫자: %d%d%d%d%d%d%d%d%d%d%d\n", dig1, dig2, dig3, dig4, dig5, dig6, dig7, dig8, dig9, dig10, dig11);

    sum = 3 * (dig1 + dig3 + dig5 + dig7 + dig9 + dig11);
    sum = sum + (dig2 + dig4 + dig6 + dig8 + dig10);
    dig12 = (10 - sum % 10) % 10;

    printf("The check digit is %d \n", dig12);

    return 0;
}
```

**Skeleton of the Program to Write:**

```c
#include <stdio.h>
#define SIZE 12
int main()
{
    int dig[SIZE];
    int sum, i;
    // ...
    return 0;
}
```

**Program Requirements:**

1. Rewrite the example code to use an array.
2. Specify the array size with a macro constant.

**Sample Run:**

```text
Please enter the first eleven UPC digits, separated by white space:
0 3 6 0 0 0 2 9 1 4 5
입력된 숫자: 03600029145
The check digit is 2

Program ended with exit code: 0
```

**[Solution](Solutions.md#exercise-1-computing-the-check-digit-of-a-upc-barcode)**

---

<br>

## Exercise 2: Selection Sort Variant

**Textbook Problem:** A variant of Chapter 7, Example 7-11 (ascending selection sort)

**Problem:** The selection sort of Example 7-11 on page 262 of the textbook picks the minimum among the elements not yet sorted and fills the positions from the front. Rewrite it so that it still sorts in ascending order but selects the maximum and finds its final position from the back.

![Figure 1. Ascending selection sort code of textbook Example 7-11](../../images/Ch07_Selection-Sort-Code.png)

*Figure 1. Ascending selection sort code of textbook Example 7-11*

**Code of Example 7-11:**

```c
#include <stdio.h>
#define SIZE 5

void print_array(int arr[], int size)   // 배열의 원소를 출력하는 함수
{
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main(void)
{
    int data[SIZE] = { 52, 31, 28, 17, 46 };
    int i, j, temp;
    int index_min;      // 아직 정렬되지 않은 원소 중 가장 작은 원소의 인덱스

    for (i = 0; i < SIZE - 1; i++) {            // 0~(i-1)까지는 정렬된 상태이다.
        index_min = i;
        for (j = i + 1; j < SIZE; j++) {
            // data[i]~data[SIZE-1] 중에서 가장 작은 원소의 인덱스를 찾는다.
            if (data[index_min] > data[j])      // 오름차순 정렬
                index_min = j;
        }
        if (i != index_min) {                   // data[i]를 data[index_min]과 맞바꾼다.
            temp = data[i];
            data[i] = data[index_min];
            data[index_min] = temp;
        }                                       // data[i]가 i번째로 작은 값이 된다.

        printf("i = %d 일 때 정렬 결과 : ", i);
        print_array(data, SIZE);                // i번째 작은 값을 찾은 후의 정렬 결과 출력
    }
}
```

**Output of Example 7-11:**

```text
i = 0 일 때 정렬 결과 : 17 31 28 52 46 
i = 1 일 때 정렬 결과 : 17 28 31 52 46 
i = 2 일 때 정렬 결과 : 17 28 31 52 46 
i = 3 일 때 정렬 결과 : 17 28 31 46 52 
```

**[Solution](Solutions.md#exercise-2-selection-sort-variant)**

---

<br>

## Exercise 3: Computing Frequency and Relative Frequency

**Problem:** Fill a one-dimensional integer array of 40 elements with random values between 150 and 199, and write a program that computes and prints the frequency and relative frequency of each interval.

- Input: none
- Output: the frequency and relative frequency of each interval (see the sample run)

**Program Requirements:**

1. Declare the arrays that store the frequency and relative frequency of each interval as follows.

   ```c
   int frequency[5] = { 0 };
   double relative_freq[5];
   ```

2. Assign values between 150 and 199 to the array elements using the `rand()` function.
3. Call the `srand()` function to change the seed value of the `rand()` function.

   ```c
   srand((unsigned)time(NULL));
   ```

4. Use a `switch` statement when computing the frequencies.

**Sample Run:**

```text
배열 내용:
165  183  186  171  165  190  174  151  152  198
193  172  196  165  199  181  181  167  155  160
191  191  175  184  187  197  160  164  198  155
155  152  157  165  170  169  153  196  151  169

------------------------------
값의 범위        도수      상대도수
------------------------------
150 - 159       9       0.225
160 - 169      10       0.250
170 - 179       5       0.125
180 - 189       6       0.150
190 - 199      10       0.250

Program ended with exit code: 0
```

**[Solution](Solutions.md#exercise-3-computing-frequency-and-relative-frequency)**
