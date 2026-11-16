# HW7 Assignment Handout — Arrays

[Repository Guide](../../../README.md) | [English](Assignment.md) | [한국어](Assignment.ko.md)

> **Last Updated:** 2026-11-16

This is the seventh assignment of section 3 of Computer Language and Training Ⅰ. It consists of four problems on arrays. Problems 3 and 4 are free items in which students set and solve two problems of their own for understanding arrays.

- **Deadline:** 2024-05-13 (Mon) 14:00, before the class starts. After the deadline the assignment is hidden automatically.
- **Submission:** Write the answers in the assignment template (.hwp) distributed by the course and submit it only in the assignment area of Blackboard.
- **Contents:** For a coding problem, an analysis of the code must be written together with the code.
- **Sample Runs:** The line `Program ended with exit code: 0` at the end of a sample run is not output of the program but a termination message that the Xcode console appends.

---

<br>

## Problem 1. Average and Standard Deviation

Read 10 arbitrary real numbers from the user and store them in a one-dimensional real-number array of size 10. Compute and print the average and standard deviation of the data stored in the array.

The standard deviation ($\sigma$) can be computed as follows. Square the difference between the first sample and the mean, compute the same for the second and third samples, ..., up to the last sample, and add them up. The positive square root of this sum divided by the number of samples is the standard deviation.

```math
\sigma = \sqrt{\frac{1}{N}\sum_{i=1}^{N}(x_i - \mu)^2}, \quad \mu = \frac{1}{N}\sum_{i=1}^{N} x_i
```

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

---

<br>

## Problem 2. Comparing Values in an Array

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

---

<br>

## Problem 3. Reversing Array Elements

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

---

<br>

## Problem 4. Finding a Value in an Array

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

---

<br>

After solving the problems, see the [assignment explanation](../Assignment-Explanation.md) for the answers and solutions.
