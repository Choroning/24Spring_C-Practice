# HW10 Assignment Explanation — Strings

[Repository Guide](../../README.md) | [English](Assignment-Explanation.md) | [한국어](Assignment-Explanation.ko.md)

> **Last Updated:** 2026-10-27
>
> 문제풀이 중심의 C언어 연습, 김용일과 강문설, Ch 8

> **Learning Objectives:**
> 1. Sort an array by selection sort and find its median according to whether the number of elements is odd or even
> 2. Count the uppercase and lowercase letters in a string by comparing character code ranges
> 3. Reverse a string in place by moving two pointers inward from both ends
> 4. Read a line containing spaces with `fgets` and remove the trailing newline
> 5. Identify whitespace characters with `isspace` and print a string split at whitespace

**Problem Source:** Prof. Jonguk Lee, Computer Language and Training Ⅰ (DCCS103-03) / Cheolwon Park

---

## Table of Contents

- [1. Finding the Median](#1-finding-the-median)
  - [1.1 Problem](#11-problem)
  - [1.2 Solution](#12-solution)
  - [1.3 Output](#13-output)
- [2. String Search](#2-string-search)
  - [2.1 Problem](#21-problem)
  - [2.2 Solution](#22-solution)
  - [2.3 Output](#23-output)
- [3. String Reversal](#3-string-reversal)
  - [3.1 Problem](#31-problem)
  - [3.2 Solution](#32-solution)
  - [3.3 Output](#33-output)
- [4. String Splitting](#4-string-splitting)
  - [4.1 Problem](#41-problem)
  - [4.2 Solution](#42-solution)
  - [4.3 Output](#43-output)
- [Summary](#summary)
- [Self-Check Questions](#self-check-questions)

---

<br>

## 1. Finding the Median

### 1.1 Problem

**Textbook Problem:** Chapter 8 exercise 9

There are two arrays as follows. Print the median of each array.

```c
int vOne[] = { 15, 18, 10, 4, 27 };
int vTwo[] = { 2, -4, 6, 9, 21, 44 };
```

The median is the value at the middle position when the data are first sorted by size. If the size of the array is $n$, the median is as follows.

- If $n$ is odd: the value at position $\frac{n+1}{2}$
- If $n$ is even: the sum of the value at position $\frac{n}{2}$ and the value at position $\frac{n}{2}+1$, divided by 2

### 1.2 Solution

**Approach:** The median is determined from sorted data, so the array is sorted in ascending order and then the position is computed. Sorting and computing the median are each written as a function so that the same code serves both arrays.

- **`sortArr()`:** It sorts the array in ascending order by selection sort ([Chapter 7, Section 5.6](../../Lecture-Notes/Ch07_Arrays/Concepts_Lecture.md#56-selection-sort)). For `i` from 0 to `n - 2`, it finds the index `minIdx` of the smallest value from position `i` to the end and swaps that element with element `i`. Passing an array as an argument passes its starting address, so the result sorted inside the function remains in the array of `main()` ([Chapter 8, Section 3.4](../../Lecture-Notes/Ch08_Pointers/Concepts_Lecture.md#34-passing-arrays-to-functions)).
- **`getMedian()`:** The positions in the problem count from 1, so 1 is subtracted to turn them into indices. If $n$ is odd, position $\frac{n+1}{2}$ is index $\frac{n+1}{2} - 1$, which equals `n / 2` in integer division. If $n$ is even, positions $\frac{n}{2}$ and $\frac{n}{2}+1$ are indices `n / 2 - 1` and `n / 2`. When $n$ is even, the average of the two values may not be an integer, so the function divides by `2.0` and returns a `double`.
- **`main()`:** It finds the number of elements by dividing the size of the whole array by the size of one element, as in `sizeof(vOne) / sizeof(vOne[0])`, and prints the original array, the sorted array, and the median in turn. `printArr()` prints the arrays.

| Array | Sorted result | $n$ | Position of the median | Median |
|:-----|:-----|:-----|:-----|:-----|
| `vOne` | 4, 10, 15, 18, 27 | 5 (odd) | 3rd (index 2) | 15 |
| `vTwo` | -4, 2, 6, 9, 21, 44 | 6 (even) | 3rd and 4th (indices 2, 3) | (6 + 9) / 2 = 7.5 |

*Table 1. Computing the medians of the two arrays*

**Code:** [Solution/Q1.c](Solution/Q1.c)

```c
/**
 * @file    Q1.c
 * @brief   Q1. 중위수 구하기
 * @author  박철원 (Cheolwon Park)
 * @date    2026-10-19
 */

#include <stdio.h>

void sortArr(int arr[], int n)
{
	for (int i = 0; i < n - 1; i++) {
		int minIdx = i;
		for (int j = i + 1; j < n; j++) {
			if (arr[j] < arr[minIdx])
				minIdx = j;
		}
		int tmp = arr[i];
		arr[i] = arr[minIdx];
		arr[minIdx] = tmp;
	}
}

double getMedian(int arr[], int n)
{
	if (n % 2 == 1)
		return arr[n / 2];
	else
		return (arr[n / 2 - 1] + arr[n / 2]) / 2.0;
}

void printArr(const char* name, int arr[], int n)
{
	printf("%s:", name);
	for (int i = 0; i < n; i++)
		printf(" %d", arr[i]);
	printf("\n");
}

int main()
{
	int vOne[] = { 15, 18, 10, 4, 27 };
	int vTwo[] = { 2, -4, 6, 9, 21, 44 };
	int nOne = sizeof(vOne) / sizeof(vOne[0]);
	int nTwo = sizeof(vTwo) / sizeof(vTwo[0]);

	printArr("vOne", vOne, nOne);
	sortArr(vOne, nOne);
	printArr("Sorted vOne", vOne, nOne);
	printf("Median of vOne: %.1f\n\n", getMedian(vOne, nOne));

	printArr("vTwo", vTwo, nTwo);
	sortArr(vTwo, nTwo);
	printArr("Sorted vTwo", vTwo, nTwo);
	printf("Median of vTwo: %.1f\n", getMedian(vTwo, nTwo));
}
```

### 1.3 Output

The output is as follows.

```text
vOne: 15 18 10 4 27
Sorted vOne: 4 10 15 18 27
Median of vOne: 15.0

vTwo: 2 -4 6 9 21 44
Sorted vTwo: -4 2 6 9 21 44
Median of vTwo: 7.5
```

As in Table 1, the median of `vOne` is 15 and the median of `vTwo` is 7.5. `getMedian()` returns a `double` that is printed with `%.1f`, so the integer median 15 is also printed as `15.0`.

> **Caution:** `sortArr()` sorts the arrays of `main()` directly, so the original order is gone after the median is found. If the original order must be kept, copy the array to another array before sorting. Also, `getMedian()` assumes that it receives a sorted array, and passing an array with no elements (`n` of 0) reads index -1, so it must be called only when `n` is at least 1.

---

<br>

## 2. String Search

### 2.1 Problem

Write a program that finds and prints the number of uppercase letters and the number of lowercase letters in a string entered by the user.

**Sample Run:**

```text
Input str: aB3 2# dfkW
Uppercase letters: 2
Lowercase letters: 4

Program ended with exit code: 0
```

### 2.2 Solution

**Approach:** A line containing spaces must be read, so `gets_s`, which reads a whole line, is used instead of `%s` ([Chapter 9, Section 4.2](../../Lecture-Notes/Ch09_Strings/Concepts_Lecture.md#42-fgets--gets_s)). Then each character is checked until the null character is reached.

- **Input:** `char str[50] = "";` initializes the whole array with null characters, and `gets_s(str, sizeof(str))` reads one line without the newline. `sizeof(str)` is the array size 50, so at most 49 characters are read.
- **Classification:** The loop condition `str[i]` is true while the current character is not the null character (0). If the character is between `'a'` and `'z'`, `countL` is incremented, and if it is between `'A'` and `'Z'`, `countU` is incremented. In ASCII, the uppercase and lowercase letters each have consecutive codes, so they can be identified by range comparison.
- **Output:** The number of uppercase letters and the number of lowercase letters are printed in turn.

In `aB3 2# dfkW`, the uppercase letters are `B` and `W` (2), and the lowercase letters are `a`, `d`, `f`, and `k` (4); digits, spaces, and `#` are not counted as either.

**Code:** [Solution/Q2.c](Solution/Q2.c)

```c
/**
 * @file    A10303-1_C09Q1.c
 * @brief   Q1. 문자열 검색
 * @author  박철원 (Cheolwon Park)
 * @date    2024-05-31
 * 
 * @note    소스 코드에 사용된 gets_s는 Visual Studio 이외의
 *          IDE에서 실행이 불가할 수 있음에 주의하시기 바랍니다.
 */

#include <stdio.h>

int main()
{
	char str[50] = "";
	int i, countU = 0, countL = 0;
	
	printf("Input str: ");
	gets_s(str, sizeof(str));

	for (i = 0; str[i]; i++) {
		if (str[i] >= 'a' && str[i] <= 'z')
			countL++;
		else if (str[i] >= 'A' && str[i] <= 'Z')
			countU++;
	}

	printf("Uppercase letters: %d\n", countU);
	printf("Lowercase letters: %d\n", countL);
}
```

### 2.3 Output

`gets_s` belongs to Annex K, which is optional in the C11 standard, so Visual Studio provides it but the standard libraries used by gcc and clang do not. To run the code with gcc or clang, include a header that defines a `gets_s` with the same behavior (read one line and discard the newline) with the `-include` option, as in the Chapter 9 exercise solution ([Chapter 9, Exercise 1 solution](../../Lecture-Notes/Ch09_Strings/Solutions.md#exercise-1-string-manipulation)). Entering the string of the sample run gives the following result.

```text
Input str: aB3 2# dfkW
Uppercase letters: 2
Lowercase letters: 4
```

The last line of the sample run, `Program ended with exit code: 0`, is not program output but the exit message added by the Xcode console, and the same holds for the other sample runs in this document.

> **Note:** Using `isupper()` and `islower()` from `<ctype.h>` instead of range comparisons shows the intent better and also works correctly for character sets other than ASCII ([Chapter 9, Section 3.1](../../Lecture-Notes/Ch09_Strings/Concepts_Lecture.md#31-classification)). For portability, read with `fgets` instead of `gets_s` and remove the newline (Section 4). The newline is not a letter, so even if it is not removed, the counts in this problem do not change.

---

<br>

## 3. String Reversal

### 3.1 Problem

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

### 3.2 Solution

**Approach:** Without creating a new array, two pointers that point to both ends of the string are moved inward while the two characters are exchanged. When the two pointers meet or cross, every character is in place.

- **`revStr()`:** It sets both `start` and `end` to the starting address of the string, moves `end` to the null character, and then steps it back one position so that it points to the last character. This step finds the end of the string without `strlen`. Then, while `start < end`, it exchanges `*start` and `*end` with a temporary variable and moves `start` forward and `end` backward by one position. The pointer comparison `start < end` compares two positions in the same array ([Chapter 8, Section 2.1](../../Lecture-Notes/Ch08_Pointers/Concepts_Lecture.md#21-pointer-arithmetic)).
- **`main()`:** It reads one line with `fgets(str, sizeof(str), stdin)`, and since `<string.h>` cannot be used, it finds the newline with a loop and replaces it with the null character. If the newline were not removed, it would come first in the reversed string. If `fgets` returns `NULL` (end of input), nothing is printed.

```text
Step 1:  [a][b][c][d][e]   start → a, end → e   : swap a and e
Step 2:  [e][b][c][d][a]   start → b, end → d   : swap b and d
Step 3:  [e][d][c][b][a]   start == end (c)     : loop ends
```

*Figure 1. `revStr()` reversing `"abcde"`*

**Code:** [Solution/Q3.c](Solution/Q3.c)

```c
/**
 * @file    A10303-1_C09Q2.c
 * @brief   Q2. 문자열 뒤집기
 * @author  박철원 (Cheolwon Park)
 * @date    2024-05-31
 */

#include <stdio.h>

void revStr(char* str) {
    char* start = str;
    char* end = str;

    while (*end) {
        end++;
    }
    end--;
	
    while (start < end) {
        char tmp = *start;
        *start = *end;
        *end = tmp;

        start++;
        end--;
    }
}

int main() {
    char str[100];

    printf("Input str: ");
    if (fgets(str, sizeof(str), stdin)) {
        for (int i = 0; str[i]; i++) {
            if (str[i] == '\n') {
                str[i] = '\0';
                break;
            }
        }

        revStr(str);
        printf("Reversed str: %s\n", str);
    }
}
```

### 3.3 Output

Entering the string of the sample run gives the following result.

```text
Input str: aB3 2# dfkW
Reversed str: Wkfd #2 3Ba
```

The string has length 11, so 5 swaps occur and the middle character `#` (index 5) stays in place.

> **Caution:** If an empty string is entered, `end` points to the null character from the start, so `end--` makes it point before the beginning of the array. Since `start < end` is false, no dereference occurs, but merely forming a pointer outside the array is undefined behavior in the C standard, so it is safer to check first, as in `if (*str == '\0') return;`. Also, this function reverses byte by byte, so a UTF-8 string in which one character takes several bytes, such as Hangul, has its byte order reversed and its characters broken.

---

<br>

## 4. String Splitting

### 4.1 Problem

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

### 4.2 Solution

**Approach:** The string is printed one character at a time, but a newline is printed in place of each whitespace character. Then the pieces separated by whitespace are printed one per line.

- **Input and newline removal:** `fgets` reads at most 99 characters, and `strcspn(str, "\n")` gives the position of the first newline (or the string length if there is no newline), which is replaced with the null character. If the newline were not removed, one more blank line would be printed at the end.
- **Split printing:** For each character, the conditional operator chooses `'\n'` if `isspace((unsigned char)str[i])` is true and the character itself otherwise, and `putchar()` prints it. The conversion to `unsigned char` is needed because on systems where `char` is signed, non-ASCII bytes such as those of Hangul become negative values that cannot be passed to `isspace()` ([Chapter 9, Section 3.1](../../Lecture-Notes/Ch09_Strings/Concepts_Lecture.md#31-classification)).
- **Finishing:** After the last piece, `putchar('\n')` ends the line.

**Code:** [Solution/Q4.c](Solution/Q4.c)

```c
/**
 * @file    A10303-1_C09Q3.c
 * @brief   Q3. 문자열 분리
 * @author  박철원 (Cheolwon Park)
 * @date    2024-05-27
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char str[100];

    printf("Input str: ");
    if (fgets(str, sizeof(str), stdin)) {
        str[strcspn(str, "\n")] = '\0';

        for (int i = 0; i < strlen(str); i++) {
            putchar(isspace((unsigned char)str[i]) ? '\n' : str[i]);
        }
        putchar('\n');
    }

    return 0;
}
```

### 4.3 Output

Entering the string of the sample run gives the following result.

```text
Input str: aB 3# ! D
aB
3#
!
D
```

The code does not print the second line of the sample run, `Output:`. To match the format, add `printf("Output:\n");` before the loop.

> **Caution:** Because each whitespace character is replaced with a newline, consecutive spaces as in `a  b` produce an empty line between the pieces (three lines: `a`, an empty line, and `b`). To treat consecutive whitespace as one, remember whether the last printed character was a newline and do not print newlines in a row. Also, the loop condition `i < strlen(str)` calls `strlen` again on every iteration, taking $O(n^2)$ time for a string of length $n$, and compares an `int` with a `size_t` (an unsigned integer). It is better to compute the length once before the loop with `size_t len = strlen(str);` or to use `str[i] != '\0'` as the condition.

---

<br>

## Summary

| Concept | Key Summary |
|:--------|:------------|
| Median | After sorting, the median is the value at index `n / 2` if the number of elements $n$ is odd, and the real number obtained by adding the values at indices `n / 2 - 1` and `n / 2` and dividing by `2.0` if $n$ is even. |
| Identifying letter case | In ASCII the letters have consecutive codes, so they can be identified by range, as in `'a' <= c && c <= 'z'`, while `isupper()` and `islower()` are more portable. |
| Reading a line | A line containing spaces is read with `gets_s` or `fgets`; `gets_s` discards the newline, and `fgets` stores it with the text. |
| Removing the newline | The newline stored by `fgets` is removed with `str[strcspn(str, "\n")] = '\0';` or with a loop that finds the newline and replaces it with the null character. |
| In-place reversal | Exchanging two pointers at both ends while `start < end` and moving them inward reverses a string of length $n$ with $\lfloor n/2 \rfloor$ swaps. |
| Handling an empty string | Checking for an empty string before stepping a pointer back to the last character avoids forming a pointer before the array. |
| `isspace()` | It treats space, `\t`, `\n`, `\v`, `\f`, and `\r` as whitespace, and its argument is converted to `unsigned char` before being passed. |
| Cost of the loop condition | `i < strlen(str)` recomputes the length on every iteration, so the length is computed once or the null character is used as the condition. |

---

<br>

## Self-Check Questions

1. **Indices of the median:** When an array of 7 elements and an array of 8 elements are sorted, the values at which indices does `getMedian()` of Section 1 use to find each median?

   <details>
   <summary>Answer</summary>

   7 is odd, so the median is the 4th value, that is, the value at index `7 / 2` = 3. 8 is even, so the median is the sum of the 4th and 5th values, that is, the values at indices `8 / 2 - 1` = 3 and `8 / 2` = 4, divided by `2.0`.

   </details>

2. **Counting letters:** If `Hello World 2024` is entered into the program of Section 2, how many uppercase and lowercase letters are there?

   <details>
   <summary>Answer</summary>

   There are 2 uppercase letters, `H` and `W`, and 8 lowercase letters, `e`, `l`, `l`, `o`, `o`, `r`, `l`, and `d`. Spaces and digits are not counted.

   </details>

3. **Swaps in reversal:** How many swaps occur when `revStr()` reverses `"abcd"` and `"abcde"`, and what are the results?

   <details>
   <summary>Answer</summary>

   `"abcd"` becomes `"dcba"` after 2 swaps, (a, d) and (b, c). `"abcde"` becomes `"edcba"` after 2 swaps, (a, e) and (b, d), after which the two pointers meet at the middle `c` and the loop ends. For length $n$, there are $\lfloor n/2 \rfloor$ swaps.

   </details>

4. **Without removing the newline:** If the loop that removes the newline is taken out of `main()` in Section 3 and `abc` is entered, what is printed?

   <details>
   <summary>Answer</summary>

   `str` holds `"abc\n"`, so reversing it gives `"\ncba"`. Therefore the line breaks right after `Reversed str: `, `cba` is printed on the next line, and the `\n` of `printf` breaks the line again.

   </details>

5. **Consecutive spaces:** If `a  b` (two spaces) is entered into the program of Section 4, how many lines are printed after the `Input str:` line?

   <details>
   <summary>Answer</summary>

   Three lines are printed. The first space breaks the line after `a`, the second space produces an empty line, then `b` is printed and the final `putchar('\n')` ends the line. That is, the order is `a`, an empty line, and `b`.

   </details>
