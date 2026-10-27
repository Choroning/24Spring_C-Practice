# Chapter 10 Lab — Structure Basics and Converting Strings to Integers

[Repository Guide](../../README.md) | [English](Concepts_Lab.md) | [한국어](Concepts_Lab.ko.md)

> **Last Updated:** 2026-10-27
>
> 문제풀이 중심의 C언어 연습, 김용일 외, Ch 9

> **Learning Objectives:**
> 1. Explain the limits of representing related information with separate variables and why a structure groups it
> 2. Define a structure, declare a structure variable, and access its members with the dot operator
> 3. Explain why a string cannot be assigned to a character array member and put a value in it with `strcpy`
> 4. Initialize a structure variable with an initializer list and explain the value of members without an initial value
> 5. Implement a function that converts a string of digits to an integer using the ASCII codes of digit characters

---

## Table of Contents

- [1. Structure Basics](#1-structure-basics)
  - [1.1 Information in Separate Variables](#11-information-in-separate-variables)
  - [1.2 Structure Definition and Variable Declaration](#12-structure-definition-and-variable-declaration)
  - [1.3 Member Access and Character Array Members](#13-member-access-and-character-array-members)
  - [1.4 Structure Initialization](#14-structure-initialization)
- [2. Converting a String to an Integer](#2-converting-a-string-to-an-integer)
  - [2.1 Problem](#21-problem)
  - [2.2 Digit Characters and ASCII Codes](#22-digit-characters-and-ascii-codes)
  - [2.3 Multiplying by Place Values and Adding](#23-multiplying-by-place-values-and-adding)
  - [2.4 Multiplying by 10 from the Front](#24-multiplying-by-10-from-the-front)
- [Summary](#summary)
- [Self-Check Questions](#self-check-questions)

---

<br>

## 1. Structure Basics

All code in this section compiles with `gcc -std=c99 -Wall` without warnings, and the outputs are from actual runs.

### 1.1 Information in Separate Variables

Consider a small program that manages a student's grades. The information needed is the name (`char name[]`), the Korean score (`int kor`), the English score (`int eng`), and the average (`double ave`). With what has been covered so far, each piece of information is declared as a separate variable.

```c
#include <stdio.h>

int main()
{
    char name[] = "hong gil dong";
    int kor, eng;
    double ave;

    kor = 80;
    eng = 91;
    ave = (kor + eng) / 2.0;

    printf("name: %s \n", name);
    printf("%d, %d \n", kor, eng);
    printf("%.1f \n", ave);
}
```

```text
name: hong gil dong 
80, 91 
85.5 
```

The output looks like the information of one student, but `name`, `kor`, `eng`, and `ave` are four separate variables with no relation to one another. They were only printed together when printing the same student's information; nothing in the code marks the four pieces as belonging to one student. With several students, the variables multiply into `name1`, `kor1`, `name2`, `kor2`, and which score belongs to which student can be told only by the number attached to the variable name.

Grouping related information into a single unit solves this problem. This way of making data into one structure is the **structure** ([Chapter 10, Section 1.1](Concepts_Lecture.md#11-structure-concept)).

### 1.2 Structure Definition and Variable Declaration

A structure is a way for the programmer to design a new data type by grouping variables related to a particular purpose. The keyword `struct` is followed by the name of the structure (the tag), and the variables to group are declared inside braces. The variables inside the braces are called **members**, and the definition ends with a semicolon ([Chapter 10, Section 1.2](Concepts_Lecture.md#12-structure-definition)).

```c
struct grade {
    char name[20];
    int kor, math;
    double ave;
};
```

This definition creates a data type `struct grade` that groups a name, a Korean score, a math score, and an average. A definition only describes the shape of the data type; the definition alone allocates no memory. Just as a variable is declared with `int`, memory is allocated only when a structure variable is declared with `struct grade hong;`, and then the four members `name`, `kor`, `math`, and `ave` are created together. These members are variables belonging to `hong` ([Chapter 10, Section 1.3](Concepts_Lecture.md#13-structure-variable-declaration)).

```text
 hong
 offset 0                   20       24       28       32                40
 ┌─────────────────────────┬────────┬────────┬────────┬─────────────────┐
 │ name[20]                │ kor    │ math   │ (pad)  │ ave             │
 └─────────────────────────┴────────┴────────┴────────┴─────────────────┘
```

*Figure 1. Memory layout of the structure variable hong (arm64 macOS, clang)*

Members are laid out in the order they are declared. The sum of the member sizes is 20 + 4 + 4 + 8 = 36 bytes, but `sizeof(hong)` is 40. The `double` member `ave` is aligned to start at an address that is a multiple of 8, so the compiler inserted 4 bytes of padding after `math`. The amount of padding can differ by compiler and system.

### 1.3 Member Access and Character Array Members

The members of a structure variable are accessed with the **dot operator** (`.`). `hong.kor` is the member `kor` of `hong`, and a value can be assigned to it and read from it like an ordinary `int` variable ([Chapter 10, Section 1.5](Concepts_Lecture.md#15-member-access)).

```c
#include <stdio.h>
#include <string.h>

struct grade {
    char name[20];
    int kor, math;
    double ave;
};

int main()
{
    struct grade hong;      // members name, kor, math, ave are created together

    // hong.name = "hong gil dong";     // compile error: an array cannot be assigned
    strcpy(hong.name, "hong gil dong");
    hong.kor = 90;
    hong.math = 79;
    hong.ave = (hong.kor + hong.math) / 2.0;

    printf("-> name: %s \n", hong.name);
    printf("-> %d, %d \n", hong.kor, hong.math);
    printf("-> %.1f \n", hong.ave);
    printf("-> size: %zu \n", sizeof(hong));
}
```

```text
-> name: hong gil dong 
-> 90, 79 
-> 84.5 
-> size: 40 
```

- **Character array member:** `hong.name = "hong gil dong";` is a compile error. `hong.name` is an array, and a value cannot be put into an array name with the assignment operator. clang reports the error `array type 'char[20]' is not assignable`. To put a string into a character array member, copy it with `strcpy`, as in `strcpy(hong.name, "hong gil dong");` ([Chapter 9 Lab, Section 1.3](../Ch09_Strings/Concepts_Lab.md#13-modifying-character-arrays)).
- **Integer and real members:** A value is put in with the assignment operator, as in `hong.kor = 90;`, and the members are used in calculations like ordinary variables, as in `(hong.kor + hong.math) / 2.0`.

> **Note:** Visual Studio issues warning C4996 for `strcpy`, so write `#pragma warning(disable:4996)` or `#define _CRT_SECURE_NO_WARNINGS` at the top of the file. In Visual Studio 2019 and later, warning C6031, issued when the return value of `scanf` is not used, can also be turned off with `#pragma warning(disable:6031)` ([Chapter 3 Lab, Section 5.1](../Ch03_Data-Types-and-Variables/Concepts_Lab.md#51-warning-c4996)).

### 1.4 Structure Initialization

A structure variable can also be initialized at its declaration with an **initializer list** `{ }`. The initial values correspond to the members in the order they were declared, and a character array member can be initialized with a string literal inside the initializer list ([Chapter 10, Section 1.4](Concepts_Lecture.md#14-structure-initialization)).

```c
#include <stdio.h>

struct grade {
    char name[20];
    int kor, math;
    double ave;
};

int main()
{
    struct grade hong = { "hong gil dong", 87, 88 };    // ave is not given

    printf("-> name: %s \n", hong.name);
    printf("-> %d, %d \n", hong.kor, hong.math);
    printf("-> %.1f \n", hong.ave);

    hong.ave = (hong.kor + hong.math) / 2.0;
    printf("============\n");
    printf("-> name: %s \n", hong.name);
    printf("-> %d, %d \n", hong.kor, hong.math);
    printf("-> %.1f \n", hong.ave);
}
```

```text
-> name: hong gil dong 
-> 87, 88 
-> 0.0 
============
-> name: hong gil dong 
-> 87, 88 
-> 87.5 
```

The three initial values of `{ "hong gil dong", 87, 88 }` go to `name`, `kor`, and `math` in order. When there are fewer initial values than members, the remaining members are initialized to 0, so `ave`, which has no initial value, is 0.0. This is why the first output shows an average of 0.0; after the average is computed and assigned to `hong.ave`, 87.5 is printed.

> **Key Point:** Putting a string into a character array member through an initializer list is possible only at the declaration. After the declaration, `strcpy` must be used, as in Section 1.3.

A problem that inputs, prints, and sorts a structure array with functions is covered in [Chapter 10 Exercise 1](Exercises.md#exercise-1-student-structure).

---

<br>

## 2. Converting a String to an Integer

### 2.1 Problem

**Problem:** Read a string of digits and implement the function `strToInt()`, which returns the value of that string converted to an integer. The `main` function multiplies the returned integer by 2 and prints it with `%6d` (textbook problem 9-14).

The string `"124"` is just a character array of the characters `'1'`, `'2'`, `'4'` followed by the null character, not the integer 124 on which arithmetic can be done. So each character must be turned into an integer, and the integer value must then be rebuilt according to the place of each digit.

### 2.2 Digit Characters and ASCII Codes

The ASCII codes of the digit characters `'0'`-`'9'` are consecutive, from 48 to 57.

| Character | `'0'` | `'1'` | `'2'` | `'3'` | `'4'` | `'5'` | `'6'` | `'7'` | `'8'` | `'9'` |
|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
| Decimal code | 48 | 49 | 50 | 51 | 52 | 53 | 54 | 55 | 56 | 57 |
| Hexadecimal code | 0x30 | 0x31 | 0x32 | 0x33 | 0x34 | 0x35 | 0x36 | 0x37 | 0x38 | 0x39 |

*Table 1. ASCII codes of the digit characters*

Because the codes are consecutive, subtracting the code of `'0'`, 48, from the code of a digit character gives the integer that the character represents. For example, `'1' - '0'` is 49 - 48 = 1, and `'4' - '0'` is 52 - 48 = 4. Writing `'0'` instead of 48 means the ASCII code value need not be memorized, and the intent of the code is clearer. Characters are promoted to integers in arithmetic, so the result of `pstr[i] - '0'` has type `int`.

### 2.3 Multiplying by Place Values and Adding

In `"124"`, `'1'` is the hundreds digit, `'2'` the tens digit, and `'4'` the ones digit. Turning each digit into an integer, multiplying it by its place value, and adding gives the integer 124.

1. Find the length (number of digits) len of the string. For `"124"` it is 3.
2. Compute the place value place of the first digit as 10 to the power (len - 1). If len is 3, it is 100.
3. From the front, for each digit add (digit character - `'0'`) × place to the result, and divide place by 10.

| i | `pstr[i]` | `pstr[i] - '0'` | place | Value added | result |
|:---:|:---:|:---:|:---:|:---:|:---:|
| 0 | `'1'` | 1 | 100 | 100 | 100 |
| 1 | `'2'` | 2 | 10 | 20 | 120 |
| 2 | `'4'` | 4 | 1 | 4 | 124 |

*Table 2. Converting "124" with place values*

```c
#include <stdio.h>
#include <string.h>

int strToInt(const char *pstr);

int main()
{
    char str[20];

    printf(">> input str: ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0';     // remove the newline that fgets keeps

    printf("-> output int: %6d \n", strToInt(str) * 2);
}

int strToInt(const char *pstr)
{
    int len = 0, place = 1, result = 0;

    while (pstr[len] != '\0')           // number of digits
        len++;
    for (int i = 1; i < len; i++)       // place value of the first digit
        place *= 10;

    for (int i = 0; i < len; i++) {
        result += (pstr[i] - '0') * place;      // '1' - '0' is the integer 1
        place /= 10;
    }
    return result;
}
```

```text
>> input str: 124
-> output int:    248 
```

```text
>> input str: 1352
-> output int:   2704 
```

- **String input:** `fgets` keeps the newline character it reads in the array, so `strcspn` finds it and replaces it with the null character. If the newline character remained, it would be counted in the length and the number of digits would grow by one ([Chapter 9 Lab, Section 1.6](../Ch09_Strings/Concepts_Lab.md#16-string-input-functions)).
- **Parameter:** `strToInt` only reads the string, so its parameter is declared as `const char *`.
- **Output:** Being able to multiply the returned integer by 2 shows that the string has become an integer. `%6d` right-aligns the value in 6 columns, so 248 is preceded by three spaces and 2704 by two.

### 2.4 Multiplying by 10 from the Front

The conversion can also be done without computing the number of digits first. Each time a digit is read from the front, the result so far is multiplied by 10, shifting it one place to the left, and the new digit is added.

```c
int strToInt(const char *pstr)
{
    int result = 0;

    for (int i = 0; pstr[i] != '\0'; i++)
        result = result * 10 + (pstr[i] - '0');
    return result;
}
```

For `"124"`, result changes as 0 → 0 × 10 + 1 = 1 → 1 × 10 + 2 = 12 → 12 × 10 + 4 = 124. Using this function instead of the `strToInt` of Section 2.3 gives the same results. It needs neither the loop that counts the length nor the loop that computes the place value, so it scans the string only once.

> **Caution:** Both functions assume that the input consists only of digits. With a sign, as in `-12`, or a non-digit character mixed in, as in `12a`, they return a wrong value, and a number beyond the range of `int` overflows. The standard library function `atoi` handles leading white space and a sign and stops converting at a non-digit character ([Chapter 9, Section 5.1](../Ch09_Strings/Concepts_Lecture.md#51-string-to-number)).

---

<br>

## Summary

| Concept | Key Summary |
|:-----|:-----|
| Structure | A data type designed by the programmer that groups variables related to a particular purpose. |
| Structure definition | It has the form `struct tag { member declarations };`, and the definition alone allocates no memory. |
| Structure variable | Declaring it, as in `struct grade hong;`, allocates all the members together. |
| Size of a structure | It can be larger than the sum of the member sizes because of padding for alignment. |
| Dot operator | Members are accessed through the structure variable, as in `hong.kor`. |
| Character array member | A string cannot be put in with the assignment operator, so it is copied with `strcpy`. |
| Structure initialization | Initial values correspond to members in declaration order, and members without an initial value become 0. |
| Converting a digit character | Subtracting `'0'` from a digit character gives the integer it represents. |
| Converting a string to an integer | Multiply each digit by its place value and add, or multiply the result by 10 and add each new digit. |

---

<br>

## Self-Check Questions

1. **Structure definition:** If `struct point { int x, y; };` is only defined and no variable is declared, is memory allocated?

   <details>
   <summary>Answer</summary>

   No. A structure definition only describes the shape of the data type; the memory for the members `x` and `y` is allocated only when a variable is declared, as in `struct point p;`.

   </details>

2. **Character array member:** After declaring `struct grade s;`, what happens with `s.name = "kim";`? How should it be fixed?

   <details>
   <summary>Answer</summary>

   `s.name` is an array and cannot be assigned, so it is a compile error. It must be copied with `strcpy(s.name, "kim");`.

   </details>

3. **Partial initialization:** With `struct grade s = { "lee", 70 };`, what are the values of `s.math` and `s.ave`?

   <details>
   <summary>Answer</summary>

   Members without an initial value are initialized to 0, so `s.math` is 0 and `s.ave` is 0.0.

   </details>

4. **Size of a structure:** In the `struct grade` of Section 1.2, the member sizes add up to 36 bytes. Why is `sizeof(struct grade)` 40?

   <details>
   <summary>Answer</summary>

   The compiler inserted 4 bytes of padding after `math` so that the `double` member `ave` starts at a position that is a multiple of 8.

   </details>

5. **Converting a string to an integer:** How does result change when the function of Section 2.4 converts `"305"`?

   <details>
   <summary>Answer</summary>

   It changes as 0 → 3 → 30 → 305. `'0' - '0'` is 0, so the middle digit 0 is handled correctly too.

   </details>
