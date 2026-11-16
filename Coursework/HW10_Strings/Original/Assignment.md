# HW10 Assignment Handout — Strings

[Repository Guide](../../../README.md) | [English](Assignment.md) | [한국어](Assignment.ko.md)

> **Last Updated:** 2026-11-16

This is the tenth assignment of section 3 of Computer Language and Training Ⅰ. It consists of the two problems set by the course (Problems 1 and 2) and two problems added for more practice with strings (Problems 3 and 4).

- **Deadline:** 2024-06-03 (Mon) 14:00, before the class starts. After the deadline the assignment is hidden automatically.
- **Submission:** Write the answers in the assignment template (.hwp) distributed by the course and submit it only in the assignment area of Blackboard.
- **Contents:** For a coding problem, an analysis of the code must be written together with the code.
- **Sample Runs:** The line `Program ended with exit code: 0` at the end of a sample run is not output of the program but a termination message that the Xcode console appends.

---

<br>

## Problem 1. Finding the Median

**Textbook Problem:** Chapter 8 exercise 9

There are two arrays as follows. Print the median of each array.

```c
int vOne[] = { 15, 18, 10, 4, 27 };
int vTwo[] = { 2, -4, 6, 9, 21, 44 };
```

The median is the value at the middle position when the data are first sorted by size. If the size of the array is $n$, the median is as follows.

- If $n$ is odd: the value at position $\frac{n+1}{2}$
- If $n$ is even: the sum of the value at position $\frac{n}{2}$ and the value at position $\frac{n}{2}+1$, divided by 2

---

<br>

## Problem 2. String Search

Write a program that finds and prints the number of uppercase letters and the number of lowercase letters in a string entered by the user.

**Sample Run:**

```text
Input str: aB3 2# dfkW
Uppercase letters: 2
Lowercase letters: 4

Program ended with exit code: 0
```

---

<br>

## Problem 3. String Reversal

Write a program that reverses a string entered by the user and prints it.

**Program Requirements:**

1. Define and use a `revStr()` function that reverses the string entered by the user and stores the result.
2. Write it without using the `<string.h>` library.

**Sample Run:**

```text
Input str: aB3 2# dfkW
Reversed str: Wkfd #2 3Ba

Program ended with exit code: 0
```

---

<br>

## Problem 4. String Splitting

Referring to the sample run, write a program that, when the string entered by the user contains whitespace, breaks the line at that point and continues printing.

**Program Requirements:**

1. Use the `isspace()` library function of `<ctype.h>` to check whether an array element is a whitespace character (a space, a tab, and so on). `isspace()` works as follows.
   - It is declared in `<ctype.h>` in the form `int isspace(int c);`, and a `char` argument is automatically converted to `int`.
   - It returns a nonzero value (true) if the argument is a whitespace character and 0 (false) otherwise.
   - It treats the six characters `' '`, `'\t'`, `'\n'`, `'\v'`, `'\f'`, and `'\r'` (the ordinary space and the whitespace control characters) as whitespace.

2. Use the `fgets()` function to handle user input. The newline (Enter, `\n`) typed to finish the input is stored together with the entered text. This newline can be removed by adding the following statement.

   ```c
   str[strcspn(str, "\n")] = '\0';
   ```

   Note that `<string.h>` must be included to use the `strcspn()` library function.

**Sample Run:**

```text
Input str: aB 3# ! D
Output:
aB
3#
!
D

Program ended with exit code: 0
```

---

<br>

After solving the problems, see the [assignment explanation](../Assignment-Explanation.md) for the answers and solutions.
