# HW4 Assignment Handout — Control Statements II

[Repository Guide](../../../README.md) | [English](Assignment.md) | [한국어](Assignment.ko.md)

> **Last Updated:** 2026-11-24

This is the fourth assignment of section 3 of Computer Language and Training Ⅰ. It consists of five exercises from Chapter 5 of the textbook, and Problems 3 and 4 rewrite example code solved in class with another control statement.

- **Contents:** For a coding problem, an analysis of the code must be written together with the code.
- **Sample Runs:** The line `Program ended with exit code: 0` at the end of a sample run is not output of the program but a termination message that the Xcode console appends.

---

<br>

## Problem 1. Letter Conversion

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

---

<br>

## Problem 2. Odd or Even

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

---

<br>

## Problem 3. switch-if Conversion (1)

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

---

<br>

## Problem 4. switch-if Conversion (2)

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

---

<br>

## Problem 5. switch Branching Practice

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

---

<br>

After solving the problems, see the [assignment explanation](../Assignment-Explanation.md) for the answers and solutions.
