# HW8 Assignment Handout — Pointers I

[Repository Guide](../../../README.md) | [English](Assignment.md) | [한국어](Assignment.ko.md)

> **Last Updated:** 2026-11-16

This is the eighth assignment of section 3 of Computer Language and Training Ⅰ. It consists of three problems on pointers. Problem 3 is a free item in which students set and solve a problem of their own related to pointers.

- **Deadline:** 2024-05-20 (Mon) 14:00, before the class starts. After the deadline the assignment is hidden automatically.
- **Submission:** Write the answers in the assignment template (.hwp) distributed by the course and submit it only in the assignment area of Blackboard.
- **Contents:** For a coding problem, an analysis of the code must be written together with the code.
- **Sample Runs:** The line `Program ended with exit code: 0` at the end of a sample run is not output of the program but a termination message that the Xcode console appends.

---

<br>

## Problem 1. Swapping

Referring to the sample run, write a program that swaps the data stored in two variables. `main()` has the variables `int a = 3, b = 5;`, and a `swap()` function that exchanges the two values using pointers is defined and used.

**Sample Run:**

```text
초기상태: a = 3, b = 5
맞바꾸기: a = 5, b = 3

Program ended with exit code: 0
```

---

<br>

## Problem 2. Array Operation

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

---

<br>

## Problem 3. Sorting Three Numbers

Write a program that reads three integers from the user into three variables and then sorts the values of the three variables in ascending order using pointers and prints them.

**Program Requirements:**

1. Define and use the `swap()` function that exchanges the values of two variables (Problem 1) and the function `void sort3(int* pa, int* pb, int* pc)`, which receives the addresses of three variables and sorts their values in ascending order.
2. The sorted result must be reflected directly in the variables `x`, `y`, and `z` of `main()`.

**Sample Run:**

```text
정수 3개 입력: 9 -2 5
정렬 전: x = 9, y = -2, z = 5
정렬 후: x = -2, y = 5, z = 9

Program ended with exit code: 0
```

---

<br>

After solving the problems, see the [assignment explanation](../Assignment-Explanation.md) for the answers and solutions.
