# HW7 Assignment Explanation — Arrays

[Repository Guide](../../README.md) | [English](Assignment-Explanation.md) | [한국어](Assignment-Explanation.ko.md)

> **Last Updated:** 2026-10-27

> **Learning Objectives:**
> 1. Store input real numbers in an array and compute their average and standard deviation
> 2. Initialize the maximum and minimum with the first element and update them by comparing with the remaining elements
> 3. Reverse the order of array elements using the correspondence between indices `i` and `n - 1 - i`
> 4. Explain the difference between the population standard deviation and the sample standard deviation
> 5. Find every position of a value in an array by sequential search and decide whether the value is present from the number of matches

**Problem Source:** Prof. Jonguk Lee, Computer Language and Training Ⅰ (DCCS103-03) / Cheolwon Park

---

## Table of Contents

- [1. Assignment Layout and How to Run](#1-assignment-layout-and-how-to-run)
- [2. Problem 1: Average and Standard Deviation](#2-problem-1-average-and-standard-deviation)
  - [2.1 Requirements](#21-requirements)
  - [2.2 Solution Approach](#22-solution-approach)
  - [2.3 Code and Output](#23-code-and-output)
  - [2.4 Edge Cases](#24-edge-cases)
- [3. Problem 2: Comparing Values in an Array](#3-problem-2-comparing-values-in-an-array)
  - [3.1 Requirements](#31-requirements)
  - [3.2 Solution Approach](#32-solution-approach)
  - [3.3 Code and Output](#33-code-and-output)
  - [3.4 Edge Cases](#34-edge-cases)
- [4. Problem 3: Reversing Array Elements](#4-problem-3-reversing-array-elements)
  - [4.1 Requirements](#41-requirements)
  - [4.2 Solution Approach](#42-solution-approach)
  - [4.3 Code and Output](#43-code-and-output)
  - [4.4 Edge Cases](#44-edge-cases)
- [5. Problem 4: Finding a Value in an Array](#5-problem-4-finding-a-value-in-an-array)
  - [5.1 Requirements](#51-requirements)
  - [5.2 Solution Approach](#52-solution-approach)
  - [5.3 Code and Output](#53-code-and-output)
  - [5.4 Edge Cases](#54-edge-cases)
- [Summary](#summary)
- [Self-Check Questions](#self-check-questions)

---

<br>

## 1. Assignment Layout and How to Run

This assignment consists of four problems that store values in a one-dimensional array and process them with loops ([Chapter 7](../../Lecture-Notes/Ch07_Arrays/Concepts_Lecture.md)). The assignment included free items in which students set and solved two of their own problems for understanding arrays, and Problems 3 and 4 are these free items.

```text
Coursework/HW07_Arrays/
└── Solution/
    ├── Q1.c    # Problem 1: average and standard deviation of 10 real numbers
    ├── Q2.c    # Problem 2: maximum and minimum of 7 integers
    ├── Q3.c    # Problem 3: copy a real-number array in reverse order
    └── Q4.c    # Problem 4: positions and count of an entered value in an integer array
```

*Figure 1. Directory layout of the HW7 assignment*

```bash
cd Coursework/HW07_Arrays/Solution
gcc -std=c99 -Wall -o Q1 Q1.c -lm && ./Q1
gcc -std=c99 -Wall -o Q2 Q2.c && ./Q2
gcc -std=c99 -Wall -o Q3 Q3.c && ./Q3
gcc -std=c99 -Wall -o Q4 Q4.c && ./Q4
```

`Q1.c` uses `sqrt()` from `<math.h>`, so with gcc on Linux it needs `-lm`, which links the math library; on macOS it can be omitted. The last line of the sample runs, `Program ended with exit code: 0`, is not program output but the exit message added by the Xcode console.

---

<br>

## 2. Problem 1: Average and Standard Deviation

### 2.1 Requirements

Read 10 arbitrary real numbers from the user and store them in a one-dimensional real-number array of size 10. Compute and print the average and standard deviation of the data stored in the array.

The standard deviation ($\sigma$) can be computed as follows. Square the difference between the first sample and the mean, compute the same for the second and third samples, ..., up to the last sample, and add them up. The positive square root of this sum divided by the number of samples is the standard deviation.

![Figure 2. Formulas for the standard deviation and the mean](../../images/HW07_Standard-Deviation-Formula.png)

*Figure 2. Formulas for the standard deviation and the mean*

$$\sigma = \sqrt{\frac{1}{N}\sum_{i=1}^{N}(x_i - \mu)^2}, \quad \mu = \frac{1}{N}\sum_{i=1}^{N} x_i$$

To take the square root of the computed value, include the `<math.h>` header and use the `sqrt()` function. Use the `double` type for real numbers, with the format specifier `%lf` for `scanf()` and `%f` for `printf()`.

**Sample Run:**

```text
>> Input data (1): 1.4
>> Input data (2): 2.3
>> Input data (3): 4.5
>> Input data (4): 0.4
>> Input data (5): -23.4
>> Input data (6): 14.5
>> Input data (7): 45.2
>> Input data (8): 10.0
>> Input data (9): 9.3
>> Input data (10): 3.4

배열의 내용: 1.4  2.3  4.5  0.4  -23.4  14.5  45.2  10.0  9.3  3.4
-> 평균: 6.76
-> 표준편차: 16.03

Program ended with exit code: 0
```

### 2.2 Solution Approach

The mean must be known before the deviation of each value can be computed, so the array is traversed twice.

1. **Input and sum:** The first loop prints the prompt `>> Input data (i + 1): `, stores the value read with `%lf` in `arr_num[i]`, and adds it to `sum` at the same time.
2. **Printing the array and the average:** It prints the stored values with `%.1f` and then computes the average with `ave = sum / 10`. Since `sum` is a `double`, this is floating-point division.
3. **Standard deviation:** The second loop adds the square of `(arr_num[i] - ave)` to `Dev`, and `sqrt(Dev / 10)` gives the standard deviation. `Dev / 10` is the variance.

Substituting the values of the sample run, the sum is 67.6, so the average is 6.76; the sum of squared deviations is 2569.584, so the variance is 256.9584 and the standard deviation is $\sqrt{256.9584} \approx 16.03$ ([Chapter 7, Section 5.2](../../Lecture-Notes/Ch07_Arrays/Concepts_Lecture.md#52-average-and-standard-deviation)).

### 2.3 Code and Output

**Code:** [Solution/Q1.c](Solution/Q1.c)

```c
/**
 * @file    A10303-1_C07Q1.c
 * @brief   Q1. 평균과 표준편차 구하기
 * @author  박철원 (Cheolwon Park)
 * @date    2024-05-10
 */

#include <stdio.h>
#include <math.h>

int main()
{
	double arr_num[10], sum = 0, ave, Dev = 0, stdDev;

	for (int i = 0; i < 10; i++) {
		printf(">> Input data (%d): ", i + 1);
		scanf(" %lf", &arr_num[i]);
		sum += arr_num[i];
	}
	printf("배열의 내용: ");

	for (int i = 0; i < 10; i++) {
		printf("%.1f ", arr_num[i]);
	}
	ave = sum / 10;
	printf("\n-> 평균: %.2f", ave);

	for (int i = 0; i < 10; i++) {
		Dev += (arr_num[i] - ave)*(arr_num[i] - ave);
	}
	stdDev = sqrt(Dev / 10);
	printf("\n-> 표준편차: %.2f", stdDev);
}
```

**Output:** Entering the values of the sample run gives the average 6.76 and the standard deviation 16.03. Unlike the sample run, there is no blank line between the input and `배열의 내용:`, and the values are separated by a single space, so the line ends with one trailing space. There is no newline after the last line.

```text
>> Input data (1): 1.4
>> Input data (2): 2.3
>> Input data (3): 4.5
>> Input data (4): 0.4
>> Input data (5): -23.4
>> Input data (6): 14.5
>> Input data (7): 45.2
>> Input data (8): 10.0
>> Input data (9): 9.3
>> Input data (10): 3.4
배열의 내용: 1.4 2.3 4.5 0.4 -23.4 14.5 45.2 10.0 9.3 3.4 
-> 평균: 6.76
-> 표준편차: 16.03
```

### 2.4 Edge Cases

- **All values equal:** All deviations are 0, so `Dev` is 0 and the standard deviation is 0.00.
- **Population and sample standard deviation:** The formula in the assignment is the population standard deviation, which divides the sum of squared deviations by $N$. The sample standard deviation, used to estimate a population from a sample, divides by $N - 1$, which for the values of the sample run gives $\sqrt{2569.584 / 9} \approx 16.90$.
- **Rounding in the output:** The array is printed with `%.1f`, so an input with digits beyond the first decimal place (for example, 1.25) is displayed rounded, but the calculation uses the value exactly as entered.

---

<br>

## 3. Problem 2: Comparing Values in an Array

### 3.1 Requirements

Write a program that reads 7 arbitrary integers from the user in turn, stores them in an array of size 7, and finds and prints the largest and smallest values in the array by comparison.

**Sample Run:**

```text
>> Input data (1): 97
>> Input data (2): 40
>> Input data (3): -35
>> Input data (4): 0
>> Input data (5): 14
>> Input data (6): -49
>> Input data (7): 100

배열에서 가장 큰 값: 100
배열에서 가장 작은 값: -49

Program ended with exit code: 0
```

### 3.2 Solution Approach

Both `min` and `max` are initialized with the first element `arr_num[0]`, and then each element from index 1 to 6 is compared with them to update them ([Chapter 7, Section 5.1](../../Lecture-Notes/Ch07_Arrays/Concepts_Lecture.md#51-finding-max--min)). The update is written with the conditional operator: `min = (arr_num[i] < min) ? arr_num[i] : min;` assigns the current element if it is smaller, and otherwise assigns the existing `min` again.

Because the initialization uses the first element, the result is correct even if all inputs are negative or all are very large. Initializing with 0 or an arbitrary large number can cause errors; for example, if all inputs are negative, `max` would remain 0.

### 3.3 Code and Output

**Code:** [Solution/Q2.c](Solution/Q2.c)

```c
/**
 * @file    A10303-1_C07Q2.c
 * @brief   Q2. 배열에서 대소 비교
 * @author  박철원 (Cheolwon Park)
 * @date    2024-05-10
 */

#include <stdio.h>

int main()
{
	int arr_num[7], min, max;

	for (int i = 0; i < 7; i++) {
		printf(">> Input data (%d): ", i + 1);
		scanf(" %d", &arr_num[i]);
	}
	min = arr_num[0];
	max = arr_num[0];

	for (int i = 1; i < 7; i++) {
		min = (arr_num[i] < min) ? arr_num[i] : min;
		max = (arr_num[i] > max) ? arr_num[i] : max;
	}

	printf("\n배열에서 가장 큰 값: %d\n", max);
	printf("배열에서 가장 작은 값 : %d\n", min);
}
```

**Output:** Entering the values of the sample run prints the largest value 100 and the smallest value -49. However, the second result line follows the string in the code and has a space before the colon, as in `가장 작은 값 : -49`, which differs by one space from the sample run.

```text
>> Input data (1): 97
>> Input data (2): 40
>> Input data (3): -35
>> Input data (4): 0
>> Input data (5): 14
>> Input data (6): -49
>> Input data (7): 100

배열에서 가장 큰 값: 100
배열에서 가장 작은 값 : -49
```

### 3.4 Edge Cases

- **Duplicate values:** Even if the maximum or minimum appears several times, only the value is printed, so the result is unaffected. If the position were printed as well, whether the first or the last position remains would depend on whether the comparison operator is `<` or `<=`.
- **All values equal:** No update ever happens, so `max` and `min` are both that value.
- **Number of comparisons:** For 7 elements, the maximum and minimum are each compared 6 times, 12 comparisons in total.

---

<br>

## 4. Problem 3: Reversing Array Elements

### 4.1 Requirements

Write a program that reverses the order of the elements of an array storing real-number data.

**Program Requirements:**

1. Set the array size to 10.
2. Initialize the array with the following values in order.
    - 1.2, 3.1, 4.3, 4.5, 6.7, 2.3, 8.7, 9.5, 2.3, 5.8

**Sample Run:**

```text
배열(원본): 1.2  3.1  4.3  4.5  6.7  2.3  8.7  9.5  2.3  5.8
배열(역순): 5.8  2.3  9.5  8.7  2.3  6.7  4.5  4.3  3.1  1.2

Program ended with exit code: 0
```

### 4.2 Solution Approach

A second array of the same size, `arrRev`, is declared, and `arrRev[i] = arr[9 - i]` copies the original from the back. In an array of size $n$, the element at index `i` goes to position `n - 1 - i` in reverse order, so for $n = 10$, `i` = 0 corresponds to 9, `i` = 1 to 8, ..., and `i` = 9 to 0. The two arrays are then printed in turn.

This method leaves the original untouched and builds a separate reversed array. If the original array itself must be reversed, swap `arr[i]` and `arr[9 - i]` `10 / 2` = 5 times while moving from both ends toward the center, as in [Chapter 7, Section 5.3](../../Lecture-Notes/Ch07_Arrays/Concepts_Lecture.md#53-reversing-an-array); no additional array is needed.

### 4.3 Code and Output

**Code:** [Solution/Q3.c](Solution/Q3.c)

```c
/**
 * @file    A10303-1_C07Q3.c
 * @brief   Q3. 배열 원소 뒤집기
 * @author  박철원 (Cheolwon Park)
 * @date    2024-05-10
 */

#include <stdio.h>

int main()
{
	double arr[10] = { 1.2, 3.1, 4.3, 4.5, 6.7, 2.3, 8.7, 9.5, 2.3, 5.8 };
	double arrRev[10];

	for (int i = 0; i < 10; i++) {
		arrRev[i] = arr[9 - i];
	}

	printf("\n배열(원본): ");
	for (int i = 0; i < 10; i++) {
		printf("%.1f  ", arr[i]);
	}
	printf("\n배열(역순): ");
	for (int i = 0; i < 10; i++) {
		printf("%.1f  ", arrRev[i]);
	}
}
```

**Output:** The original and reversed arrays are printed. Because the first `printf` begins with `\n`, there is one blank line at the very start of the output, and because two spaces are printed after each value, each line ends with two trailing spaces.

```text

배열(원본): 1.2  3.1  4.3  4.5  6.7  2.3  8.7  9.5  2.3  5.8  
배열(역순): 5.8  2.3  9.5  8.7  2.3  6.7  4.5  4.3  3.1  1.2  
```

### 4.4 Edge Cases

- **Hard-coded size:** The size 10 and the last index 9 are scattered across several places in the code. Defining `#define SIZE 10` and writing `arr[SIZE - 1 - i]` means only one place needs to change when the size changes.
- **Iterations of in-place reversal:** When switching to the swapping method, running the loop `SIZE` times swaps each pair twice and restores the original order, so the loop must run `SIZE / 2` times. If the size is odd, the middle element is not swapped.

---

<br>

## 5. Problem 4: Finding a Value in an Array

### 5.1 Requirements

Write a program that finds a value entered by the user in an array storing integer data and prints the positions where the value is stored and how many there are.

**Program Requirements:**

1. Set the array size to 10.
2. Initialize the array with the following values in order.
    - 7, 3, 9, 3, 12, 5, 3, 8, 1, 9
3. If the value to find is in the array, print every index where it is stored and then the count; otherwise, print a message that it is not there.

**Sample Runs:**

```text
배열의 내용: 7 3 9 3 12 5 3 8 1 9
>> 찾을 값: 3
-> 인덱스: 1 3 6
-> 개수: 3

Program ended with exit code: 0
```

```text
배열의 내용: 7 3 9 3 12 5 3 8 1 9
>> 찾을 값: 4
-> 찾는 값이 배열에 없습니다.

Program ended with exit code: 0
```

### 5.2 Solution Approach

The program uses sequential search, which compares each element from the start of the array to the end with the value to find, `key` ([Chapter 7, Section 5.5](../../Lecture-Notes/Ch07_Arrays/Concepts_Lecture.md#55-sequential-search)). The same value may be stored several times, so the loop does not stop at the first match but runs to the end.

1. **Printing the array and reading the input:** The size is fixed with `#define SIZE 10`, and after printing the contents of the array, the program prints the prompt `>> 찾을 값: ` and reads `key` with `%d`.
2. **Searching:** Each time it meets an element with `arr[i] == key`, it prints the index `i` and increases `count` by 1. The first match happens when `count` is 0, so only then does it print `-> 인덱스:` first.
3. **Deciding the result:** After the loop, if `count` is greater than 0, the program prints the count; if it is 0, there was no match at all, so it prints the not-found message. `count` counts the matches and at the same time tells whether the value is present.

Each value is printed with a leading space as `" %d"`, so no space remains at the end of a line. Indices start at 0, so index 1 in the sample run is the second element of the array.

### 5.3 Code and Output

**Code:** [Solution/Q4.c](Solution/Q4.c)

```c
/**
 * @file    Q4.c
 * @brief   Q4. 배열에서 값 찾기
 * @author  박철원 (Cheolwon Park)
 * @date    2026-10-19
 */

#include <stdio.h>
#define SIZE 10

int main()
{
	int arr[SIZE] = { 7, 3, 9, 3, 12, 5, 3, 8, 1, 9 };
	int key, count = 0;

	printf("배열의 내용:");
	for (int i = 0; i < SIZE; i++) {
		printf(" %d", arr[i]);
	}

	printf("\n>> 찾을 값: ");
	scanf(" %d", &key);

	for (int i = 0; i < SIZE; i++) {
		if (arr[i] == key) {
			if (count == 0)
				printf("-> 인덱스:");
			printf(" %d", i);
			count++;
		}
	}

	if (count > 0)
		printf("\n-> 개수: %d\n", count);
	else
		printf("-> 찾는 값이 배열에 없습니다.\n");
}
```

**Output:** 3 is at indices 1, 3, and 6, so the count is 3, and 4 is not in the array.

```text
배열의 내용: 7 3 9 3 12 5 3 8 1 9
>> 찾을 값: 3
-> 인덱스: 1 3 6
-> 개수: 3
```

```text
배열의 내용: 7 3 9 3 12 5 3 8 1 9
>> 찾을 값: 4
-> 찾는 값이 배열에 없습니다.
```

### 5.4 Edge Cases

- **First and last elements:** Entering 9 prints `-> 인덱스: 2 9` and `-> 개수: 2`, which shows that the comparison reaches the last index 9 without skipping any element. Entering 7 prints only index 0 of the first element.
- **Number of comparisons:** All occurrences must be found, so the program always makes `SIZE`, that is, 10 comparisons whether or not the value is present. If only the first position is needed, ending the loop with `break` at the moment of a match makes it 1 comparison when the value is in the first element and 10 when it is absent.
- **Non-integer input:** If a non-integer such as `abc` is entered, `scanf` cannot read a value, and the uninitialized `key` is used in the comparisons. Checking that the return value of `scanf` is 1 filters out such input.

---

<br>

## Summary

| Concept | Key Summary |
|:-----|:-----|
| Average and standard deviation | The first loop computes the sum for the average, and the second loop computes the sum of squared deviations, divides it by $N$, and applies `sqrt()`. |
| Population and sample standard deviation | The formula in the assignment is the population standard deviation, which divides by $N$, while the sample standard deviation divides by $N - 1$. |
| Maximum and minimum | `max` and `min` are initialized with the first element and updated by comparing with the remaining elements using the conditional operator. |
| Reverse copy | In an array of size $n$, `arrRev[i] = arr[n - 1 - i]` builds a reversed array while preserving the original. |
| In-place reversal | Swapping the elements at both ends `n / 2` times reverses the original array without an additional array. |
| Sequential search | Compare the elements of the array with the value to find from start to end; counting the matches lets the program decide after the loop whether the value is present by checking whether the count is 0. |
| Output format | The solutions print the same values as the sample runs, but some blank lines and spaces differ. |

---

<br>

## Self-Check Questions

1. **Computing the standard deviation:** For the values 2, 4, 4, 4, 5, 5, 7, 9, compute the average and standard deviation in the same way as the program of Problem 1.

   <details>
   <summary>Answer</summary>

   The sum is 40, so the average is 5. The deviations are -3, -1, -1, -1, 0, 0, 2, 4, and the sum of their squares is 9 + 1 + 1 + 1 + 0 + 0 + 4 + 16 = 32. The variance is 32 / 8 = 4, so the standard deviation is 2.

   </details>

2. **Initializing the maximum:** If Problem 2 is changed to initialize `max` with 0 and compare from index 0, what is printed for the inputs -5, -3, -8, -1, -9, -2, -7?

   <details>
   <summary>Answer</summary>

   All inputs are less than 0, so `max` is never updated and 0 is printed as the largest value. The actual maximum is -1. Initializing with the first element avoids this error.

   </details>

3. **Reverse index:** In an array of size 10, which index of the original goes into `arrRev[3]`? What is the value with the data of Problem 3?

   <details>
   <summary>Answer</summary>

   `arrRev[3] = arr[9 - 3] = arr[6]`, so the value at index 6 of the original goes there. The original `arr[6]` is 8.7, so `arrRev[3]` is 8.7, which matches the fourth value of the reversed array in the output.

   </details>

4. **In-place reversal:** If Problem 3 is changed to swap `arr[i]` and `arr[9 - i]` inside `for (int i = 0; i < 10; i++)` without an additional array, what is the result?

   <details>
   <summary>Answer</summary>

   For `i` from 0 to 4, five pairs are swapped and the array is reversed, but for `i` from 5 to 9 the same five pairs are swapped again and the original order is restored. Therefore the array does not change. The loop condition must be `i < 10 / 2`.

   </details>

5. **Sample standard deviation:** What is the sample standard deviation, dividing by $N - 1$, for the values of the sample run of Problem 1?

   <details>
   <summary>Answer</summary>

   The sum of squared deviations is 2569.584, so it is $\sqrt{2569.584 / 9} = \sqrt{285.509\ldots} \approx 16.90$. This is larger than the population standard deviation 16.03, which divides by $N$.

   </details>

6. **Finding only the first position:** How should the second loop of Problem 4 be changed so that it prints only the index where the value first appears? If the value to find is 3, after how many comparisons does the loop end?

   <details>
   <summary>Answer</summary>

   Right after printing the index of a matching element and increasing `count`, end the loop with `break;`. 3 first appears at index 1, so the loop ends after 2 comparisons, `arr[0]` and `arr[1]`, and `-> 인덱스: 1` is printed.

   </details>
