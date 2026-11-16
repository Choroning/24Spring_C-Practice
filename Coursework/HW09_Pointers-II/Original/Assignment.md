# HW9 Assignment Handout — Pointers II

[Repository Guide](../../../README.md) | [English](Assignment.md) | [한국어](Assignment.ko.md)

> **Last Updated:** 2026-11-16

This is the ninth assignment of section 3 of Computer Language and Training Ⅰ. It consists of three problems on arrays and two-dimensional arrays. Problem 3 is a free item in which students set and solve a problem of their own related to two-dimensional arrays.

- **Deadline:** 2024-05-27 (Mon) 14:00, before the class starts. After the deadline the assignment is hidden automatically.
- **Submission:** Write the answers in the assignment template (.hwp) distributed by the course and submit it only in the assignment area of Blackboard.
- **Contents:** For a coding problem, an analysis of the code must be written together with the code.
- **Sample Runs:** The line `Program ended with exit code: 0` at the end of a sample run is not output of the program but a termination message that the Xcode console appends.

---

<br>

## Problem 1. Selection Sort

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

---

<br>

## Problem 2. Printing a 2D Array

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

---

<br>

## Problem 3. Averages by Item

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

---

<br>

After solving the problems, see the [assignment explanation](../Assignment-Explanation.md) for the answers and solutions.
