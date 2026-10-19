# HW8 Assignment Explanation — Pointers I

[Repository Guide](../../README.md) | [English](Assignment-Explanation.md) | [한국어](Assignment-Explanation.ko.md)

> **Last Updated:** 2026-10-19

> **Learning Objectives:**
> 1. Write a function that swaps two of the caller's variables through pointer parameters
> 2. Pass the addresses of array elements to a function and store element-wise results in another array
> 3. Decide what a function should handle when its prototype is fixed and explain the reason

**Problem Source:** Prof. Jonguk Lee, Computer Language and Training Ⅰ (DCCS103-03) / Cheolwon Park

---

## Table of Contents

- [1. Swapping](#1-swapping)
  - [1.1 Problem](#11-problem)
  - [1.2 Solution](#12-solution)
  - [1.3 Output](#13-output)
- [2. Array Operation](#2-array-operation)
  - [2.1 Problem](#21-problem)
  - [2.2 Solution](#22-solution)
  - [2.3 Output](#23-output)
- [Summary](#summary)
- [Self-Check Questions](#self-check-questions)

---

<br>

## 1. Swapping

### 1.1 Problem

Referring to the sample run, write a program that swaps the data stored in two variables. `main()` has the variables `int a = 3, b = 5;`, and a `swap()` function that exchanges the two values using pointers is defined and used.

**Sample Run:**

```text
초기상태: a = 3, b = 5
맞바꾸기: a = 5, b = 3

Program ended with exit code: 0
```

### 1.2 Solution

**Approach:** With pass by value, changing the parameters inside `swap()` does not change `a` and `b` of `main()`. So the parameters of `swap()` are declared as `int*` to receive the addresses of the two variables, and the originals are exchanged through dereferencing ([Chapter 8, Section 3.2](../../Lecture-Notes/Ch08_Pointers/Concepts_Lecture.md#32-modifying-a-variable-through-a-pointer)).

- **`swap(int* a, int* b)`:** It stores the value of `*a` in the temporary variable `tmp`, copies the value pointed to by `b` to where `a` points with `*a = *b;`, and then moves the original value with `*b = tmp;`. Without the temporary variable, the original value of `*a` would be lost the moment `*a = *b;` runs.
- **`main()`:** It prints the values before the swap, passes the addresses of the two variables with `swap(&a, &b);`, and prints the values after the swap.

**Code:** [Solution/Q1.c](Solution/Q1.c)

```c
/**
 * @file    A10303-1_C08Q1.c
 * @brief   Q1. 맞바꾸기
 * @author  박철원 (Cheolwon Park)
 * @date    2024-05-18
 */

#include <stdio.h>

void swap(int* a, int* b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

int main()
{
	int a = 3, b = 5;
	printf("초기상태: a = %d, b = %d\n", a, b);
	swap(&a, &b);
	printf("맞바꾸기: a = %d, b = %d\n", a, b);
}
```

### 1.3 Output

It compiles without warnings with `gcc -std=c99 -Wall`, and the output is as follows.

```text
초기상태: a = 3, b = 5
맞바꾸기: a = 5, b = 3
```

It matches the sample run. The last line of the sample run, `Program ended with exit code: 0`, is not program output but the exit message added by the Xcode console, and the same holds for the other sample runs in this document. `main()` has no `return 0;`, but since C99 reaching the end of `main()` is treated as returning 0, so the exit code is 0.

> **Caution:** If `swap()` exchanges the pointers themselves, as in `int *tmp = a; a = b; b = tmp;`, the variables of `main()` do not change. The pointer parameters `a` and `b` are also local variables that received copies of the addresses, so to change the originals, the pointed-to values must be changed through dereferencing, as in `*a` and `*b`.

---

<br>

## 2. Array Operation

### 2.1 Problem

There are three arrays `arrX`, `arrY`, and `arrZ` declared as follows.

```c
int arrX[4] = { -2, 4, 6, -32 };
int arrY[4] = { 4, 3, -5, 6 };
int arrZ[4] = { 0 };
```

Using the function declared below without changing it, add the elements of `arrX` and `arrY` pairwise, store the results in the `arrZ` array, and print the contents of the array.

```c
void arrSum(int* pX, int* pY, int* pZ);
```

**Sample Run:**

```text
arrZ:  2   7   1  -26

Program ended with exit code: 0
```

### 2.2 Solution

**Approach:** The given prototype has no parameter for the array size. So `arrSum()` handles the addition of one element, and `main()` passes the address of each element in a loop. Making the function process the whole array would require fixing the size at 4 inside the function, which would make it unusable for arrays of other sizes.

- **`arrSum()`:** It computes `*pZ = *pX + *pY;` for the elements the three pointers point to. The element of `arrZ` pointed to by `pZ` is changed to the result, so `pZ` is an output parameter ([Chapter 8, Section 3.3](../../Lecture-Notes/Ch08_Pointers/Concepts_Lecture.md#33-returning-multiple-values)).
- **`main()`:** It calls `arrSum(&arrX[i], &arrY[i], &arrZ[i]);` for `i = 0` through 3. `&arrX[i]` is the same address as `arrX + i`. After the computation, it prints the elements of `arrZ` with `%3d` followed by two spaces.

The element-wise results are -2 + 4 = 2, 4 + 3 = 7, 6 + (-5) = 1, and -32 + 6 = -26.

**Code:** [Solution/Q2.c](Solution/Q2.c)

```c
/**
 * @file    A10303-1_C08Q2.c
 * @brief   Q2. 배열 연산
 * @author  박철원 (Cheolwon Park)
 * @date    2024-05-18
 */

#include <stdio.h>

void arrSum(int* pX, int* pY, int* pZ)
{
	*pZ = *pX + *pY;
}

int main()
{
	int arrX[4] = { -2, 4, 6, -32 };
	int arrY[4] = { 4, 3, -5, 6 };
	int arrZ[4] = { 0 };

	for (int i = 0; i < 4; i++)
		arrSum(&arrX[i], &arrY[i], &arrZ[i]);

	printf("\narrZ: ");
	for (int i = 0; i < 4; i++)
		printf("%3d  ", arrZ[i]);
}
```

### 2.3 Output

It compiles without warnings with `gcc -std=c99 -Wall`, and the output is as follows.

```text

arrZ:   2    7    1  -26  
```

The four sums match the sample run. The output format differs. Because `printf("\narrZ: ")` starts with a newline, a blank line appears before the result, and because each element is printed with `%3d` followed by two spaces, the spacing is wider than in the sample run and the line ends with trailing spaces. Also, no newline is printed at the end, so when run in a terminal, the next shell prompt appears on the same line.

> **Note:** If the size could be passed as well, the input arrays could be received as `const`, as in `void arrSumN(const int *pX, const int *pY, int *pZ, int n)`, and the function could repeat `*(pZ + i) = *(pX + i) + *(pY + i);` `n` times to process the whole array in one call ([Chapter 8, Section 3.4](../../Lecture-Notes/Ch08_Pointers/Concepts_Lecture.md#34-passing-arrays-to-functions)).

---

<br>

## Summary

| Concept | Key Summary |
|:--------|:------------|
| Swapping with pointers | When `swap(int* a, int* b)` receives the addresses of two variables and exchanges `*a` and `*b` with a temporary variable, the caller's variables change. |
| Need for a temporary variable | Running `*a = *b;` first loses the original value of `*a`, so one value must be saved in a temporary variable before the swap. |
| Passing element addresses | `&arrX[i]` is the same address as `arrX + i`, and passing the address of an element lets the function read or change that element. |
| Output parameter | A pointer parameter through which the function writes its result, like `pZ` of `arrSum()`, is called an output parameter. |
| Fixed prototype and division of work | With a prototype that has no size parameter, letting the function process one element and the caller repeat avoids tying the function to an array size. |
| Output format differences | Even with the same results, newlines and the widths of format specifiers can make blank lines, spacing, and trailing spaces differ from the sample run. |

---

<br>

## Self-Check Questions

1. **Swapping the pointers themselves:** If `void swap2(int *a, int *b) { int *t = a; a = b; b = t; }` is called as `swap2(&x, &y);`, do the values of `x` and `y` change? Explain why.

   <details>
   <summary>Answer</summary>

   They do not change. `a` and `b` are local variables of `swap2()` that received copies of `&x` and `&y`, so exchanging the values (addresses) of the two pointers does not affect `x` and `y` in `main()`. To change the originals, `*a` and `*b`, the pointed-to values, must be exchanged.

   </details>

2. **Per-element calls:** With the arrays of Section 2, if only `arrSum(&arrX[3], &arrY[3], &arrZ[3]);` is called and the other elements are not, what does `arrZ` contain?

   <details>
   <summary>Answer</summary>

   `arrZ` was initialized with `{ 0 }`, so all its elements are 0, and after the call only `arrZ[3]` changes to -32 + 6 = -26, giving `{0, 0, 0, -26}`.

   </details>

3. **Processing the whole array:** What is the problem with making one call of `void arrSum(int* pX, int* pY, int* pZ)` process the whole array without changing the prototype?

   <details>
   <summary>Answer</summary>

   Inside the function, the number of array elements cannot be known from the pointers alone (`sizeof(pX)` is the pointer size), so the size would have to be fixed inside the function, for example at 4. Then the function cannot be used for arrays of other lengths, and passing a shorter array would access memory beyond the array. So when the prototype cannot change, it is safer to process one element per call and repeat in the caller.

   </details>
