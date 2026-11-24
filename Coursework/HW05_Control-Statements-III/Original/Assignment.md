# HW5 Assignment Handout — Control Statements III

[Repository Guide](../../../README.md) | [English](Assignment.md) | [한국어](Assignment.ko.md)

> **Last Updated:** 2026-11-24

This is the fifth assignment of section 3 of Computer Language and Training Ⅰ. It consists of four problems on loops.

- **Contents:** For a coding problem, an analysis of the code must be written together with the code.
- **Sample Runs:** The line `Program ended with exit code: 0` at the end of a sample run is not output of the program but a termination message that the Xcode console appends.

---

<br>

## Problem 1. Loop Practice (1)

Write a program that continuously reads integers (no) between 1 and 100 from the user and prints the maximum and minimum.

**Program Requirements:**

1. Use a `while` statement.
2. When `0` is entered, stop reading input and print the maximum and minimum.
3. Referring to the sample run, handle inputs that are not within 0-100 as exceptions.

**Sample Run:**

```text
Input value(no): 3
Input value(no): 9
Input value(no): 54
Input value(no): 87
Input value(no): 5
Input value(no): 234
-- Error --
Input value(no): 3
Input value(no): 0
MAX: 87, MIN: 3

Program ended with exit code: 0
```

---

<br>

## Problem 2. Loop Practice (2)

Assume that only positive numbers including 0 (numbers 0 or greater) are entered. Compute and print the sum and average of the entered positive numbers. If 0 is entered first, the program prints `0만 입력되었습니다!` ("Only 0 was entered!").

**Sample Runs:**

```text
>> Input value: 1
>> Input value: 2
>> Input value: 2
>> Input value: 0
=====================
-> SUM: 5, AVE: 1.7

Program ended with exit code: 0
```

```text
>> Input value: 0
=====================
-> 0만 입력되었습니다!

Program ended with exit code: 0
```

---

<br>

## Problem 3. Loop Practice (3)

Write a program that prints the result of `1-2+3- ... +9-10` using a `for` statement.

**Sample Run:**

```text
1 - 2 + 3 - 4 + 5 - 6 + 7 - 8 + 9 - 10 = -5

Program ended with exit code: 0
```

---

<br>

## Problem 4. Loop Practice (4)

Write code that prints the output shown in the sample run using nested `for` statements.

**Sample Run:**

```text
0
0 1
0 1 2
0 1 2 3
0 1 2 3 4
0 1 2 3
0 1 2
0 1
0

Program ended with exit code: 0
```

---

<br>

After solving the problems, see the [assignment explanation](../Assignment-Explanation.md) for the answers and solutions.
