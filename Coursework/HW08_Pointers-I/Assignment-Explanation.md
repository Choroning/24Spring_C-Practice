# HW8 Assignment Explanation — Pointers I

[Repository Guide](../../README.md) | [English](Assignment-Explanation.md) | [한국어](Assignment-Explanation.ko.md)

> **Last Updated:** 2026-10-19

> **Learning Objectives:**
> 1. Write a function that swaps two of the caller's variables through pointer parameters
> 2. Pass the addresses of array elements to a function and store element-wise results in another array
> 3. Decide what a function should handle when its prototype is fixed and explain the reason
> 4. Pass an address received through a pointer parameter on to another function as it is to sort three of the caller's variables

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
- [3. Sorting Three Numbers](#3-sorting-three-numbers)
  - [3.1 Problem](#31-problem)
  - [3.2 Solution](#32-solution)
  - [3.3 Output](#33-output)
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

## 3. Sorting Three Numbers

### 3.1 Problem

The third item of the assignment is a free item in which students set and solve their own problem on pointers, and the problem in this section is a new problem set in that format.

Write a program that reads three integers from the user into three variables and then sorts the values of the three variables in ascending order using pointers and prints them.

**Program Requirements:**

1. Define and use the `swap()` function that exchanges the values of two variables (Section 1) and the function `void sort3(int* pa, int* pb, int* pc)`, which receives the addresses of three variables and sorts their values in ascending order.
2. The sorted result must be reflected directly in the variables `x`, `y`, and `z` of `main()`.

**Sample Run:**

```text
정수 3개 입력: 9 -2 5
정렬 전: x = 9, y = -2, z = 5
정렬 후: x = -2, y = 5, z = 9

Program ended with exit code: 0
```

### 3.2 Solution

**Approach:** The program goes through three steps, each of which compares two neighboring values and swaps them if the first is larger. The swaps reuse the `swap()` of Section 1 as it is.

- **Steps 1 and 2:** If `*pa > *pb`, swap `*pa` and `*pb`; then, if `*pb > *pc`, swap `*pb` and `*pc`. After these two steps, the largest of the three values has moved to `*pc`.
- **Step 3:** Comparing the remaining two values `*pa` and `*pb` once more and swapping them puts the three values in ascending order.
- **Passing the addresses on:** The parameters `pa`, `pb`, and `pc` of `sort3()` already hold the addresses of `x`, `y`, and `z` of `main()`, so they are passed to `swap()` as they are, as in `swap(pa, pb)`. `swap()` dereferences the addresses it receives to change the values, so even through two levels of function calls the variables of `main()` change directly ([Chapter 8, Section 3.2](../../Lecture-Notes/Ch08_Pointers/Concepts_Lecture.md#32-modifying-a-variable-through-a-pointer)).

For the input `9 -2 5`, `x`, `y`, and `z` start as 9, -2, and 5, and the values after each step are as follows.

| Step | Comparison | Swap | `x` | `y` | `z` |
|:-----|:-----|:-----|:-----|:-----|:-----|
| Step 1 | `*pa > *pb`, that is, 9 > -2 is true | `swap(pa, pb)` | -2 | 9 | 5 |
| Step 2 | `*pb > *pc`, that is, 9 > 5 is true | `swap(pb, pc)` | -2 | 5 | 9 |
| Step 3 | `*pa > *pb`, that is, -2 > 5 is false | None | -2 | 5 | 9 |

*Table 1. Variable values after each step of `sort3()` for the input `9 -2 5`*

**Code:** [Solution/Q3.c](Solution/Q3.c)

```c
/**
 * @file    Q3.c
 * @brief   Q3. 세 수 정렬
 * @author  박철원 (Cheolwon Park)
 * @date    2026-10-19
 */

#include <stdio.h>

void swap(int* a, int* b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void sort3(int* pa, int* pb, int* pc)
{
	if (*pa > *pb)
		swap(pa, pb);
	if (*pb > *pc)
		swap(pb, pc);
	if (*pa > *pb)
		swap(pa, pb);
}

int main()
{
	int x, y, z;

	printf("정수 3개 입력: ");
	scanf(" %d %d %d", &x, &y, &z);

	printf("정렬 전: x = %d, y = %d, z = %d\n", x, y, z);
	sort3(&x, &y, &z);
	printf("정렬 후: x = %d, y = %d, z = %d\n", x, y, z);
}
```

### 3.3 Output

It compiles without warnings with `gcc -std=c99 -Wall`, and entering the same values as in the sample run gives the following output.

```text
정수 3개 입력: 9 -2 5
정렬 전: x = 9, y = -2, z = 5
정렬 후: x = -2, y = 5, z = 9
```

It matches the sample run. Entering 1, 2, and 3 in all six orders always gives `x = 1, y = 2, z = 3`, and `5 5 1`, which contains equal values, gives `x = 1, y = 5, z = 5`. The program always makes three comparisons regardless of the input, and the input with the most swaps is the descending `3 2 1`, which swaps in all three steps.

```text
정수 3개 입력: 3 2 1
정렬 전: x = 3, y = 2, z = 1
정렬 후: x = 1, y = 2, z = 3
```

> **Caution:** Adding `&` inside `sort3()`, as in `swap(&pa, &pb);`, passes the address of the pointer variable `pa` itself, a value of type `int**`, instead of the value of `pa` (the address of `x`). It does not match the parameter type `int*`, so clang gives the warning `-Wincompatible-pointer-types`, and gcc 16 stops compiling with an error of the same name. If the warning is ignored and `9 -2 5` is entered into the executable built with clang, the result is not sorted, as in `x = 5, y = -2, z = 9`.

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
| Passing addresses on | A pointer parameter already holds an address, so it is passed to another function as it is, as in `swap(pa, pb)`, while `&pa` is the address of the pointer variable itself, a value of type `int**`. |
| Sorting three values | Going through three steps that compare two neighboring values and swap them puts the three values in ascending order. |

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

4. **Tracing the swaps:** If `3 2 1` is entered into the program of Section 3, what are the values of `x`, `y`, and `z` after each step of `sort3()`?

   <details>
   <summary>Answer</summary>

   In step 1, 3 > 2 is true, so a swap gives (2, 3, 1); in step 2, 3 > 1 is true, so a swap gives (2, 1, 3); and in step 3, 2 > 1 is true, so a swap gives (1, 2, 3). A swap happens in all three steps, and this input is the case with the most swaps.

   </details>

5. **Descending order:** What must change for `sort3()` to sort the three values in descending order?

   <details>
   <summary>Answer</summary>

   Change `>` to `<` in all three comparisons. Then the smallest value moves to `*pc` through steps 1 and 2, and step 3 places the remaining two values with the larger one first. For example, entering `9 -2 5` gives `x = 9, y = 5, z = -2`.

   </details>
