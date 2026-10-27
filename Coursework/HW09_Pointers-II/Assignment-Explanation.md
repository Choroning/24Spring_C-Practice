# HW9 Assignment Explanation — Pointers II

[Repository Guide](../../README.md) | [English](Assignment-Explanation.md) | [한국어](Assignment-Explanation.ko.md)

> **Last Updated:** 2026-10-27

> **Learning Objectives:**
> 1. Sort an integer array in ascending order with selection sort and trace the array state at each step
> 2. Explain why the column size must be written in the parameter when a 2D array is passed to a function
> 3. Find the value of each element of a partially initialized 2D array
> 4. Traverse the rows and columns of a 2D array to compute row totals and column averages

**Problem Source:** Prof. Jonguk Lee, Computer Language and Training Ⅰ (DCCS103-03) / Cheolwon Park

---

## Table of Contents

- [1. Selection Sort](#1-selection-sort)
  - [1.1 Problem](#11-problem)
  - [1.2 Solution](#12-solution)
  - [1.3 Output](#13-output)
- [2. Printing a 2D Array](#2-printing-a-2d-array)
  - [2.1 Problem](#21-problem)
  - [2.2 Solution](#22-solution)
  - [2.3 Output](#23-output)
- [3. Averages by Item](#3-averages-by-item)
  - [3.1 Problem](#31-problem)
  - [3.2 Solution](#32-solution)
  - [3.3 Output](#33-output)
- [Summary](#summary)
- [Self-Check Questions](#self-check-questions)

---

<br>

## 1. Selection Sort

### 1.1 Problem

There is an array `data` declared as follows.

```c
int data[5] = { 52, 31, 28, 17, 46 };
```

Write a program that sorts the elements of the given array in ascending order and prints them.

**Sample Run:**

```text
> 정렬 전:  52  31  28  17  46
> 정렬 후:  17  28  31  46  52

Program ended with exit code: 0
```

### 1.2 Solution

**Approach:** Selection sort repeatedly finds the smallest element in the unsorted part and exchanges it with the first element of that part. With 5 elements, fixing the first four positions in turn (`i = 0` through 3) leaves the largest value in the last position automatically.

- **Finding the minimum:** Set `idx_min` to `i`, and for `j = i + 1` to the end, change `idx_min` to `j` whenever `data[idx_min] > data[j]`.
- **Swapping:** If `idx_min` differs from `i`, exchange `data[i]` and `data[idx_min]` with the temporary variable `tmp`. If they are the same, the element is already in place, so no swap is done.
- **Printing:** Before and after sorting, each element is printed with `%4d` to keep the width.

The array state at each step is as follows.

| Step | Minimum of the Unsorted Part | Swap | Array State |
|:-----|:-----|:-----|:-----|
| Start | | | 52, 31, 28, 17, 46 |
| `i = 0` | 17 (index 3) | `data[0]` and `data[3]` | 17, 31, 28, 52, 46 |
| `i = 1` | 28 (index 2) | `data[1]` and `data[2]` | 17, 28, 31, 52, 46 |
| `i = 2` | 31 (index 2) | None | 17, 28, 31, 52, 46 |
| `i = 3` | 46 (index 4) | `data[3]` and `data[4]` | 17, 28, 31, 46, 52 |

*Table 1. Array state at each step of selection-sorting `data`*

**Code:** [Solution/Q1.c](Solution/Q1.c)

```c
/**
 * @file    A10303-2_C08Q1.c
 * @brief   Q1. 선택 정렬
 * @author  박철원 (Cheolwon Park)
 * @date    2024-05-22
 */

#include <stdio.h>

int main()
{
	int data[5] = { 52, 31, 28, 17, 46 };
	int i, j, idx_min, tmp;

	printf("> 정렬 전:");
	for (i = 0; i < 5; i++)
	{
		printf("%4d", data[i]);
	}

	for (i = 0; i < 4; i++)
	{
		idx_min = i;
		for (j = i + 1; j < 5; j++)
		{
			if (data[idx_min] > data[j])
				idx_min = j;
		}
		if (idx_min != i)
		{
			tmp = data[i];
			data[i] = data[idx_min];
			data[idx_min] = tmp;
		}
	}
	printf("\n> 정렬 후:");
	for (i = 0; i < 5; i++)
	{
		printf("%4d", data[i]);
	}
}
```

### 1.3 Output

The output is as follows.

```text
> 정렬 전:  52  31  28  17  46
> 정렬 후:  17  28  31  46  52
```

No newline is printed after the last line, so in a terminal the next shell prompt appears on the same line. `Program ended with exit code: 0` in the sample run is the exit message added by the Xcode console, and the same holds for the other sample runs in this document.

> **Note:** Selection sort always makes $n(n-1)/2$ comparisons regardless of the input (10 for 5 elements), so its time complexity is $O(n^2)$, and it makes at most $n - 1$ swaps. In this array the minimum is already in place at `i = 2`, so 3 swaps occur.

---

<br>

## 2. Printing a 2D Array

### 2.1 Problem

Define a `printMat()` function that receives a `3 x 4` 2D integer array as a parameter and prints it, and write a program that prints the contents of the array by referring to the sample run.

**Program Requirements:**

1. The `3 x 4` 2D integer array is declared as follows.

   ```c
   int data[3][4] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
   ```

2. The parameters of `printMat()` are, in order, the address of the array, the number of rows, and the number of columns.

**Sample Run:**

```text
  1  2  3  4
  5  6  7  8
  9 10  0  0

Program ended with exit code: 0
```

### 2.2 Solution

**Approach:** A 2D array is stored contiguously in row-major order, so the 10 initial values listed without inner braces fill the array from `data[0][0]` in order, and the remaining two elements are initialized to 0.

```text
          [0]  [1]  [2]  [3]
data[0]     1    2    3    4
data[1]     5    6    7    8
data[2]     9   10    0    0
```

*Figure 1. Element values of the partially initialized `data[3][4]`*

- **Prototype of `printMat()`:** For a 2D array parameter such as `int arr[][4]`, the row size can be omitted but the column size must be written. The parameter `int arr[][4]` is `int (*arr)[4]`, a pointer to a row of 4 elements, and the compiler must know the column size 4 to compute the position of `arr[i][j]` as the `i * 4 + j`-th element from the start address.
- **Printing:** The outer loop goes over the rows and the inner loop over the columns, printing each element with `%3d` and starting a new line at the end of each row.
- **`main()`:** `printMat(data, 3, 4);` passes the array name (the address of the first row), the number of rows 3, and the number of columns 4.

**Code:** [Solution/Q2.c](Solution/Q2.c)

```c
/**
 * @file    A10303-2_C08Q2.c
 * @brief   Q2. 2차원 배열 출력
 * @author  박철원 (Cheolwon Park)
 * @date    2024-05-22
 */

#include <stdio.h>

void printMat(int data[][4], int cols, int rows);

int main()
{
	int data[3][4] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	printMat(data, 3, 4);
}

void printMat(int arr[][4], int cols, int rows)
{
	for (int i = 0; i < cols; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			printf("%3d", arr[i][j]);
		}
		printf("\n");
	}
}
```

### 2.3 Output

Compiling with `gcc -std=c99 -Wall` (as of Apple clang on macOS) produces three `-Wmissing-braces` warnings asking for braces around each row in the initializer list of `data`. The result of filling in row-major order is the same, so behavior is not affected, and writing `{ {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10} }` removes the warnings. The output is as follows.

```text
  1  2  3  4
  5  6  7  8
  9 10  0  0
```

> **Caution:** The second and third parameters of `printMat()` are named `cols` and `rows`, which is reversed. `main()` passes the number of rows 3 to `cols` and the number of columns 4 to `rows`, and the loops are written accordingly, so the result is correct, but renaming them `int rows, int cols` as in the requirements avoids confusing readers. Also, because the column size is fixed as `[4]`, passing a value other than 4 as the third argument would compute the row boundaries incorrectly.

---

<br>

## 3. Averages by Item

### 3.1 Problem

A semester grade is computed from the midterm (30 points), final exam (30 points), team project (30 points), and attendance (10 points). For a total of 5 students, write a program that computes each student's total and prints the averages of the midterm, final exam, team project, attendance, and total. Initialize the 2D array that stores the grades with the scores in the sample run below.

**Sample Run:**

```text
           중간   기말   팀플   출석   총점
학생   1번:  28    28    26     9    91
학생   2번:  30    27    30    10    97
학생   3번:  25    26    24     8    83
학생   4번:  18    22    22     5    67
학생   5번:  24    25    30    10    89
항목별 평균:  25.0  25.6  26.4   8.4  85.4

Program ended with exit code: 0
```

### 3.2 Solution

**Approach:** Use an `int score[6][5]` array with one extra row below the 5 student rows to collect sums and one extra total column to the right of the four item columns. If the initializer list gives only the scores of the four items, the remaining elements (the total column and the last row) are initialized to 0, so sums can be accumulated there.

- **Row totals:** For each row `i`, `score[i][4] += score[i][j];` is repeated for `j = 0` through 3. The loop also runs over the last row (`i = 5`), but that row is still all zeros, so the result is not affected.
- **Column sums:** For each column `i` (0-4, including the total column), `score[5][i] += score[j][i];` is repeated for `j = 0` through 4. Unlike the previous loop, the loop variable `i` is the column and `j` is the row.
- **Printing:** For each student the five values are printed with `%2d`, and the last line prints the averages, the column sums divided by `5.0`, with `%4.1f`. Dividing by `5.0` instead of `5` makes it floating-point division.

The column sums and averages are midterm 125 / 5 = 25.0, final 128 / 5 = 25.6, team project 132 / 5 = 26.4, attendance 42 / 5 = 8.4, and total 427 / 5 = 85.4.

**Code:** [Solution/Q3.c](Solution/Q3.c)

```c
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
```

### 3.3 Output

The output is as follows.

```text
               중간  기말  팀플  출석  총점
학생    1번:    28    28    26     9    91
학생    2번:    30    27    30    10    97
학생    3번:    25    26    24     8    83
학생    4번:    18    22    22     5    67
학생    5번:    24    25    30    10    89
항목별 평균:    25.0  25.6  26.4   8.4  85.4
```

Because four or two spaces are printed before each value, the column spacing differs slightly from the sample run, and no newline is printed after the last line.

> **Note:** Storing the sums in the extra row and column of the same array lets one array handle the whole table, but remember that the average row holds sums, not averages, and must be divided when printed. To store the averages exactly, a separate `double` array is clearer.

---

<br>

## Summary

| Concept | Key Summary |
|:--------|:------------|
| Selection sort | It repeats $n - 1$ times the step of finding the minimum of the unsorted part and exchanging it with the front of that part, always making $n(n-1)/2$ comparisons. |
| Skipping needless swaps | If the index of the minimum equals the current position, no swap is needed. |
| Partial initialization of 2D arrays | Initial values listed without inner braces fill the array in row-major order, and the remaining elements become 0. |
| 2D array parameters | As in `int arr[][4]`, the row size can be omitted, but the column size must be written to compute element positions. |
| Parameter names | A name that does not match its meaning makes the code hard to read even when it works, so the row count should be named `rows` and the column count `cols`. |
| Extra row and column for sums | Accumulating row totals and column sums in an extra column and row initialized to 0 lets one array compute the whole table. |
| Floating-point division | An integer sum must be divided by a floating-point value such as `5.0` to keep the fractional part. |

---

<br>

## Self-Check Questions

1. **Tracing selection sort:** When `{5, 1, 4, 2}` is sorted in ascending order by the method of Section 1, write the array state after each step and the number of swaps.

   <details>
   <summary>Answer</summary>

   At `i = 0`, the minimum 1 (index 1) is swapped with 5, giving `{1, 5, 4, 2}`, and at `i = 1`, the minimum 2 (index 3) is swapped with 5, giving `{1, 2, 4, 5}`. At `i = 2`, the minimum 4 is already in place, so no swap is done. There are 2 swaps in total.

   </details>

2. **Partial initialization:** For `int data[3][4] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };`, find the values of `data[1][3]`, `data[2][1]`, and `data[2][3]`.

   <details>
   <summary>Answer</summary>

   The array is filled in row-major order, so `data[1][3]` is the 8th value, 8, and `data[2][1]` is the 10th value, 10. There are only 10 initial values, so `data[2][3]` is 0.

   </details>

3. **Column size:** Explain why a parameter that omits the column size, as in `void printMat(int arr[][], int r, int c)`, is not allowed.

   <details>
   <summary>Answer</summary>

   A 2D array is stored contiguously in row-major order, so the position of `arr[i][j]` is the `i × (column size) + j`-th element from the start address. Without the column size, the compiler cannot compute this position, so only the first dimension (the row size) of a 2D array parameter can be omitted.

   </details>

4. **Sum row:** In the program of Section 3, what is the value of `score[5][4]` just before printing, and what does it mean?

   <details>
   <summary>Answer</summary>

   It is 427, the sum of the five students' totals 91 + 97 + 83 + 67 + 89; dividing it by 5.0 when printing gives the average total 85.4.

   </details>
