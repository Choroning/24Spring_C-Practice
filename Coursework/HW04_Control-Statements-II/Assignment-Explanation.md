# HW4 Assignment Explanation — Control Statements II

[Repository Guide](../../README.md) | [English](Assignment-Explanation.md) | [한국어](Assignment-Explanation.ko.md)

> **Last Updated:** 2026-10-27
>
> 문제풀이 중심의 C언어 연습, 김용일과 강문설, Ch 5

> **Learning Objectives:**
> 1. Determine and convert the case of an English letter by comparing ranges of ASCII codes
> 2. Determine whether an integer, including a negative one, is odd or even with the remainder operator
> 3. Turn range conditions into integer cases of a `switch` statement and handle out-of-range values separately
> 4. Rewrite a `switch` statement with grouped cases as an `if-else` statement using `||`
> 5. Handle uppercase and lowercase input with the same statements by placing case labels one after another

**Problem Source:** Prof. Jonguk Lee, Computer Language and Training Ⅰ (DCCS103-03)

---

## Table of Contents

- [1. Assignment Layout and How to Run](#1-assignment-layout-and-how-to-run)
- [2. Problem 1: Letter Conversion](#2-problem-1-letter-conversion)
  - [2.1 Problem](#21-problem)
  - [2.2 Solution](#22-solution)
  - [2.3 Output and Edge Cases](#23-output-and-edge-cases)
- [3. Problem 2: Odd or Even](#3-problem-2-odd-or-even)
  - [3.1 Problem](#31-problem)
  - [3.2 Solution](#32-solution)
  - [3.3 Output and Edge Cases](#33-output-and-edge-cases)
- [4. Problem 3: switch-if Conversion (1)](#4-problem-3-switch-if-conversion-1)
  - [4.1 Problem](#41-problem)
  - [4.2 Solution](#42-solution)
  - [4.3 Output and Edge Cases](#43-output-and-edge-cases)
- [5. Problem 4: switch-if Conversion (2)](#5-problem-4-switch-if-conversion-2)
  - [5.1 Problem](#51-problem)
  - [5.2 Solution](#52-solution)
  - [5.3 Output and Edge Cases](#53-output-and-edge-cases)
- [6. Problem 5: switch Branching Practice](#6-problem-5-switch-branching-practice)
  - [6.1 Problem](#61-problem)
  - [6.2 Solution](#62-solution)
  - [6.3 Output and Edge Cases](#63-output-and-edge-cases)
- [Summary](#summary)
- [Self-Check Questions](#self-check-questions)

---

<br>

## 1. Assignment Layout and How to Run

This assignment practices `if` and `switch` statements with exercises from Chapter 5 (conditional statements) of the textbook. Problems 1 and 2 classify characters and integers with `if-else`, Problems 3 and 4 rewrite `if` and `switch` statements with the same behavior into each other, and Problem 5 branches on a character input with a `switch` statement.

```text
Coursework/HW04_Control-Statements-II/
├── Assignment-Explanation.ko.md   # this document (Korean)
├── Assignment-Explanation.md      # this document (English)
└── Solution/
    ├── Q1.c                       # Problem 1: letter conversion
    ├── Q2.c                       # Problem 2: odd or even
    ├── Q3.c                       # Problem 3: if statement to switch statement
    ├── Q4.c                       # Problem 4: switch statement to if statement
    └── Q5.c                       # Problem 5: switch branching practice
```

*Figure 1. Directory layout of HW4*

All five programs use the standard `scanf`, so they compile as they are with any C compiler. Each program is compiled and run as follows.

```bash
cd Coursework/HW04_Control-Statements-II/Solution
gcc -std=c99 -Wall -o Q1 Q1.c
./Q1
```

The line `Program ended with exit code: 0` at the end of the sample runs in the assignment is not program output but the exit message added by the Xcode console.

---

<br>

## 2. Problem 1: Letter Conversion

### 2.1 Problem

**Textbook Problem:** Chapter 5 exercise 9

Referring to the sample runs, write a program that reads an arbitrary lowercase English letter from the user, converts it to uppercase, and prints it.

**Sample Runs:**

```text
>> Input char: q
-> Changed lower case q to upper case Q!

Program ended with exit code: 0
```

```text
>> Input char: G
-> Input error!

Program ended with exit code: 0
```

### 2.2 Solution

**Approach:** Characters in C are stored as integer codes, so their ranges can be compared with relational operators and they can be converted with arithmetic. In ASCII, the lowercase letters `'a'`-`'z'` are the consecutive codes 97-122 and the uppercase letters `'A'`-`'Z'` are 65-90, and the lowercase and uppercase forms of the same letter differ by `'a' - 'A'` = 32.

- **Input:** The space in `scanf(" %c", &ch)` skips leading whitespace and then reads one character.
- **Detecting and converting lowercase:** If `ch >= 'a' && ch <= 'z'`, the character is lowercase, and `ch - 32` is the corresponding uppercase letter.
- **Handling uppercase:** The code also handles the case `ch >= 'A' && ch <= 'Z'` separately and prints `ch + 32`, the lowercase letter. This goes beyond the behavior the problem requires.
- **Other characters:** For a character that is not an English letter, such as a digit or a symbol, it prints `-> Input error!`.

**Code:** [Solution/Q1.c](Solution/Q1.c)

```c
/**
 * @file    A10303-2_C05Q1.c
 * @brief   Q1. 영문자 변환
 * @author  박철원 (Cheolwon Park)
 * @date    2024-04-05
 */

#include <stdio.h>

int main()
{
	char ch;

	printf(">> Input char: ");
	scanf(" %c", &ch);

	if (ch >= 'a' && ch <= 'z') {
		printf("-> Changed lower case %c to upper case %c!\n", ch, ch - 32);
	} else if (ch >= 'A' && ch <= 'Z') {
		printf("-> Changed upper case %c to lower case %c!\n", ch, ch + 32);
	} else {
		printf("-> Input error!\n");
	}

	return 0;
}
```

### 2.3 Output and Edge Cases

**Output:** For the uppercase `G`, the sample run shows `-> Input error!`, but the code has a branch that converts uppercase to lowercase, so it prints `-> Changed upper case G to lower case g!`. For `5`, which is not a letter, the error message is printed.

```text
>> Input char: q
-> Changed lower case q to upper case Q!
>> Input char: G
-> Changed upper case G to lower case g!
>> Input char: 5
-> Input error!
```

> **Note:** Writing 32 directly relies on the ASCII codes, so writing it as a difference of character constants, as in `ch - 'a' + 'A'`, shows the intent more clearly. With `islower()` and `toupper()` from the standard library `<ctype.h>`, the test and the conversion each take a single function.

---

<br>

## 3. Problem 2: Odd or Even

### 3.1 Problem

**Textbook Problem:** Chapter 5 exercise 11

Referring to the sample runs, write a program that reads an arbitrary integer from the user and determines and prints whether it is odd or even.

**Sample Runs:**

```text
>> Input value: 3
-> 3 is an odd number!

Program ended with exit code: 0
```

```text
>> Input value: 6
-> 6 is an even number!

Program ended with exit code: 0
```

### 3.2 Solution

**Approach:** A number is even if its remainder after division by 2 is 0 and odd otherwise. In C, a non-zero value is true, so `num % 2` is used directly as the condition of `if`.

- **Condition:** `if (num % 2)` is the same as `if (num % 2 != 0)`. If the remainder is non-zero (odd), the first block executes, and if it is 0 (even), the `else` block executes.
- **Negative numbers:** Since C99, the sign of the remainder follows the dividend, so `-3 % 2` is -1. -1 is also non-zero, so negative odd numbers are correctly classified as odd. Comparing with `num % 2 == 1` would have misclassified negative odd numbers as even.

**Code:** [Solution/Q2.c](Solution/Q2.c)

```c
/**
 * @file    A10303-2_C05Q2.c
 * @brief   Q2. 홀짝 판별
 * @author  박철원 (Cheolwon Park)
 * @date    2024-04-05
 */

#include <stdio.h>

int main()
{
	int num;

	printf(">> Input value: ");
	scanf(" %d", &num);

	if (num % 2) {
		printf("-> %d is an odd number.\n", num);
	} else {
		printf("-> %d is an even number.\n", num);
	}

	return 0;
}
```

### 3.3 Output and Edge Cases

**Output:** Each sentence ends with `.` instead of the `!` in the sample runs. The last run enters the negative odd number -3.

```text
>> Input value: 3
-> 3 is an odd number.
>> Input value: 6
-> 6 is an even number.
>> Input value: -3
-> -3 is an odd number.
```

---

<br>

## 4. Problem 3: switch-if Conversion (1)

### 4.1 Problem

**Textbook Problem:** Chapter 5 exercise 14

Referring to the example code, rewrite the code that uses an if statement so that it uses a switch statement.

**Example Code:**

```c
#include <stdio.h>

int main()
{
	int score;
	printf(">> Input score(0~100): ");
	scanf(" %d", &score);

	if (score >= 90 && score <= 100)
		printf("%d is a/an A!", score);
	else if (score >= 80 && score <= 89)
		printf("%d is a/an B!", score);
	else if (score >= 70 && score <= 79)
		printf("%d is a/an C!", score);
	else if (score >= 60 && score <= 69)
		printf("%d is a/an D!", score);
	else if (score < 60 && score >= 0)
		printf("%d is a/an F!", score);
	else
		printf("Input error!");
}
```

### 4.2 Solution

**Approach:** A `switch` statement cannot compare ranges directly, so the score is turned into its quotient by 10, which represents each 10-point interval with a single integer ([Chapter 5, Section 2.7](../../Lecture-Notes/Ch05_Control-Statements/Concepts_Lecture.md#27-switch)). Scores 90-100 give a quotient of 9 or 10, scores 80-89 give 8, and so on.

- **Out-of-range values:** Using the quotient alone misclassifies out-of-range values. Since C99, integer division truncates toward zero, so -5 / 10 is 0 and is graded F, and 105 / 10 is 10 and is graded A. The expression of the `switch` is therefore `(score < 0 || score > 100) ? -1 : (score / 10)`, which produces -1, a value that matches no case, for out-of-range scores and sends them to `default`.
- **Grouping cases:** `case 10:` and `case 9:` are placed one after the other so that both print A, and `case 5:` through `case 0:` are grouped to print F. Each group ends with `break` so that execution does not continue into the next case.

**Code:** [Solution/Q3.c](Solution/Q3.c)

```c
/**
 * @file    A10303-2_C05Q3.c
 * @brief   Q3. switch-if 변환 (1)
 * @author  박철원 (Cheolwon Park)
 * @date    2024-04-05
 */

#include <stdio.h>

int main()
{
    int score;
    printf(">> Input score(0~100): ");
    scanf(" %d", &score);

    switch ((score < 0 || score > 100) ? -1 : (score / 10)) {
    case 10:
    case 9:
        printf("%d is a/an A!", score);
        break;
    case 8:
        printf("%d is a/an B!", score);
        break;
    case 7:
        printf("%d is a/an C!", score);
        break;
    case 6:
        printf("%d is a/an D!", score);
        break;
    case 5: 
	case 4: 
	case 3: 
	case 2: 
	case 1: 
	case 0:
        printf("%d is a/an F!", score);
        break;
    default:
        printf("Input error!");
    }

    return 0;
}
```

### 4.3 Output and Edge Cases

**Output:** For representative and boundary values of each grade interval, the program prints the same grades as the `if` statement of the example code. The program prints no newline at the end of the output.

```text
>> Input score(0~100): 100
100 is a/an A!
>> Input score(0~100): 95
95 is a/an A!
>> Input score(0~100): 85
85 is a/an B!
>> Input score(0~100): 72
72 is a/an C!
>> Input score(0~100): 61
61 is a/an D!
>> Input score(0~100): 59
59 is a/an F!
>> Input score(0~100): 0
0 is a/an F!
>> Input score(0~100): -5
Input error!
>> Input score(0~100): 101
Input error!
```

---

<br>

## 5. Problem 4: switch-if Conversion (2)

### 5.1 Problem

**Textbook Problem:** Chapter 5 exercise 15

Referring to the example code, rewrite the code that uses a switch statement so that it uses an if statement.

**Example Code:**

```c
#include <stdio.h>

int main()
{
	int grade;

	printf(">> Input grade(1~7): ");
	scanf(" %d", &grade);

	switch (grade) {
	case 1:
		printf("Very good!");
		break;
	case 2:
	case 3:
		printf("Good!");
		break;
	case 4:
	case 5:
		printf("So So!");
		break;
	case 6:
	case 7:
		printf("Cheer up!");
		break;
	default:
		printf("Input error!");
	}
}
```

### 5.2 Solution

**Approach:** One case of a `switch` is the equality comparison `grade == value`, and cases placed one after another to share statements form the logical OR of those comparisons. Each group is therefore turned into a condition joined by `||`, and the conditions are checked in order with an `else if` ladder.

- **Case 1:** `grade == 1`.
- **Cases 2 and 3:** `grade == 2 || grade == 3`. 4 and 5, and 6 and 7, work the same way.
- **default:** Corresponds to the final `else`, which executes when no condition matches.

**Code:** [Solution/Q4.c](Solution/Q4.c)

```c
/**
 * @file    A10303-2_C05Q4.c
 * @brief   Q4. switch-if 변환 (2)
 * @author  박철원 (Cheolwon Park)
 * @date    2024-04-05
 */

#include <stdio.h>

int main()
{
	int grade;

	printf(">> Input grade(1~7): ");
	scanf(" %d", &grade);

	if (grade == 1)
		printf("Very good!");
	else if (grade == 2 || grade == 3)
		printf("Good!");
	else if (grade == 4 || grade == 5)
		printf("So So!");
	else if (grade == 6 || grade == 7)
		printf("Cheer up!");
	else
		printf("Input error!");
}
```

### 5.3 Output and Edge Cases

**Output:** For a value from each group and an out-of-range value, the program prints the same messages as the `switch` statement of the example code. The program prints no newline at the end of the output.

```text
>> Input grade(1~7): 1
Very good!
>> Input grade(1~7): 3
Good!
>> Input grade(1~7): 5
So So!
>> Input grade(1~7): 7
Cheer up!
>> Input grade(1~7): 8
Input error!
```

> **Note:** A group of consecutive values such as 2 and 3 can also be written as a range, `grade >= 2 && grade <= 3`. A `switch` only needs the cases listed even when the values are scattered, while an `if` statement can be written more briefly with a range condition when the values form a consecutive interval.

---

<br>

## 6. Problem 5: switch Branching Practice

### 6.1 Problem

**Textbook Problem:** Chapter 5 exercise 16

Write a program that reads an arbitrary English letter from the user and prints the name of a programming language that starts with that letter.

**Program Requirements:**

1. Use a `switch` statement.
2. Map each letter as follows.
    - For `c` or `C`, print `C Language`.
    - For `p` or `P`, print `Python`.
    - For `j` or `J`, print `JAVA`.
    - For `l` or `L`, print `LISP`.
    - For any other letter, print `Input Error!`.

**Sample Runs:**

```text
>> Input the character: p
-> Python

Program ended with exit code: 0
```

```text
>> Input the character: C
-> C Language

Program ended with exit code: 0
```

```text
>> Input the character: m
-> Input Error!

Program ended with exit code: 0
```

### 6.2 Solution

**Approach:** Use the input character as the expression of the `switch`, and place the lowercase and uppercase cases one after the other so that they print the same language name. The first case has no statements, so execution continues directly into the statements of the next case; this is intentional fall-through ([Chapter 5, Section 2.7](../../Lecture-Notes/Ch05_Control-Statements/Concepts_Lecture.md#27-switch)).

- **Case groups:** There are four groups, `'c'` and `'C'`, `'p'` and `'P'`, `'j'` and `'J'`, and `'l'` and `'L'`, each ending with `break`.
- **default:** Prints `-> Input Error!` for every character outside the four groups.

**Code:** [Solution/Q5.c](Solution/Q5.c)

```c
/**
 * @file    A10303-2_C05Q5.c
 * @brief   Q5. switch 분기 연습
 * @author  박철원 (Cheolwon Park)
 * @date    2024-04-05
 */

#include <stdio.h>

int main()
{
    char ch;

    printf(">> Input the character: ");
    scanf(" %c", &ch);

    switch (ch) {
    case 'c': 
	case 'C':
        printf("-> C Language\n");
        break;
    case 'p': 
	case 'P':
        printf("-> Python\n");
        break;
    case 'j': 
	case 'J':
        printf("-> JAVA\n");
        break;
    case 'l': 
	case 'L':
        printf("-> LISP\n");
        break;
    default:
        printf("-> Input Error!\n");
    }
}
```

### 6.3 Output and Edge Cases

**Output:** The inputs of the three sample runs plus inputs for the other two languages (`j`, `L`).

```text
>> Input the character: p
-> Python
>> Input the character: C
-> C Language
>> Input the character: m
-> Input Error!
>> Input the character: j
-> JAVA
>> Input the character: L
-> LISP
```

> **Caution:** If the `break` at the end of a group is omitted, the statements of the next group also execute. For example, without the `break` after `Python`, entering `p` prints both `-> Python` and `-> JAVA`.

---

<br>

## Summary

| Concept | Key Summary |
|:--------|:------------|
| Comparing character ranges | Characters are integer codes, so relational operators such as `ch >= 'a' && ch <= 'z'` test whether a character is lowercase. |
| Case conversion | In ASCII, lowercase and uppercase letters differ by 32, so `ch - 32` or `ch - 'a' + 'A'` converts them. |
| Odd or even | A number is odd if `num % 2` is non-zero, and because the remainder of a negative odd number is -1, the test must be `!= 0`, not `== 1`. |
| Ranges in a `switch` | The quotient of the score by 10 serves as the case, and out-of-range values become -1 through the conditional operator and go to `default`. |
| Converting `switch` to `if` | Consecutive cases become equality comparisons joined by `\|\|`, and `default` becomes the final `else`. |
| Intentional fall-through | Lowercase and uppercase cases placed one after another share the same statements, and the `break` at the end of each group separates it from the next. |

---

<br>

## Self-Check Questions

1. **Case conversion:** Given `char ch = 'g';`, write the integer value of `ch - 32` and the character it represents.

   <details>
   <summary>Answer</summary>

   The ASCII code of `'g'` is 103, so `ch - 32` is 71, which is `'G'`.

   </details>

2. **Odd or even for negatives:** What is the value of `num % 2` when `num` is -7? What goes wrong if the odd test is written as `num % 2 == 1`?

   <details>
   <summary>Answer</summary>

   Since C99, the sign of the remainder follows the dividend, so -7 % 2 is -1. `num % 2 == 1` is false, so -7 is misclassified as even. The test must be written as `num % 2 != 0` or `if (num % 2)` to classify negative odd numbers correctly.

   </details>

3. **Out-of-range scores:** In the code of Problem 3, if the expression of the `switch` were just `score / 10` without the range check, what results would 105 and -5 produce?

   <details>
   <summary>Answer</summary>

   105 / 10 is 10, so `105 is a/an A!` is printed, and -5 / 10 truncates toward zero to 0, so `-5 is a/an F!` is printed. Both values should produce `Input error!`, so the conditional operator that turns out-of-range values into -1 is needed.

   </details>

4. **From `switch` to `if`:** Rewrite the following `switch` statement as an `if-else` statement with the same behavior.

   ```c
   switch (n) {
   case 1: case 3: printf("odd"); break;
   case 2: case 4: printf("even"); break;
   default: printf("other");
   }
   ```

   <details>
   <summary>Answer</summary>

   `if (n == 1 || n == 3) printf("odd"); else if (n == 2 || n == 4) printf("even"); else printf("other");`. Consecutive cases become equality comparisons joined by `||`, and `default` becomes the final `else`.

   </details>
