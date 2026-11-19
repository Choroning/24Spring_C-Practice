# Chapter 9 Exercises — Strings

[Repository Guide](../../README.md) | [English](Exercises.md) | [한국어](Exercises.ko.md)

> **Last Updated:** 2026-11-19
>
> Warming-Up C Programming, 천정아, Ch 9

**Problem Source:** Exercise 1 is from Prof. Younghee Im, Computer Language Ⅰ (DCCS101-04)

---

<br>

## Table of Contents

- [Exercise 1: String Manipulation](#exercise-1-string-manipulation)
- [Exercise 2: Values of String Pointer Expressions](#exercise-2-values-of-string-pointer-expressions)
- [Exercise 3: Values of String Array Expressions](#exercise-3-values-of-string-array-expressions)
- [Exercise 4: Misuse of `strcpy`](#exercise-4-misuse-of-strcpy)
- [Exercise 5: Printing Initials](#exercise-5-printing-initials)
- [Exercise 6: Case-Insensitive String Comparison](#exercise-6-case-insensitive-string-comparison)
- [Exercise 7: Counting Words](#exercise-7-counting-words)

---

<br>

## Exercise 1: String Manipulation

**Problem:** Write string functions yourself to learn the relationship between strings and pointers. Define the functions below and complete the example code.

**Program Requirements:**

1. The function prototypes given below cannot be changed, and no library function that handles strings may be used except I/O functions.
   Every string function operates based on the null character.

2. `int my_strlen(const char *p);`
   A function that receives a character array or a string constant (hereafter, a string) and returns the length of the string.
   The null character is not counted in the length.

3. `void my_strcpy(char *p1, const char *p2);`
   A function that receives two strings and copies the second string into the first.

4. `int my_strcmp(const char *p1, const char *p2);`
   A function that compares the two received strings and returns 0 if they are equal; otherwise it returns the result of comparing their ASCII values.
   It returns -1 if the left string has the smaller ASCII value and 1 if it has the larger one, and it must work the same way as `strcmp()`.

5. `void makeUpper(char p[]);`
   A function that receives a character array and converts lowercase letters to uppercase.
   Characters other than lowercase letters must not be converted, and it must be implemented with the pointer increment operation.

6. `void makeReverse(char p[]);`
   A function that receives a character array and reverses it.
   A temporary array cannot be declared and used inside the function.

7. `void strSwap(char *p1, char *p2);`
   A function that exchanges the contents of the two received strings.
   A temporary array cannot be declared and used inside the function, and it must be implemented with pointer arithmetic.

8. `void swap(char *a, char *b);`
   A function that exchanges the contents of two characters; it is called by the `makeReverse()` and `strSwap()` functions.

**Example Code:** Complete it by adding the function declarations and definitions.

```c
#include <stdio.h>
#define SIZE 64

int main()
{
   char str1[SIZE], str2[SIZE], str3[SIZE];
   int result;

   printf("문자열(str1) 입력: ");
   gets_s(str1, SIZE);

   printf("\nstr1의 길이: %d\n", my_strlen(str1));

   my_strcpy(str2, str1);
   printf("\nstr2 = %s\n", str2);

   makeUpper(str2);
   printf("\nstr1을 대문자로 변환 = %s\n", str2);

   makeReverse(str2);
   printf("\nstr2의 역순 = %s\n", str2);

   my_strcpy(str3, str1);

   if (!my_strcmp(str1, str3))
      printf("\n%s == %s\n", str1, str3);
   if (result = my_strcmp("abc", "abcd"))
      printf("\nstrcmp(\"abc\", \"abcd\") = %d\n", result);
   if (result = my_strcmp("C++", "C"))
      printf("\nstrcmp(\"C++\", \"C\") = %d\n\n", result);
   
   my_strcpy(str3, "C is powerful");
   printf("------ strSwap() 함수 호출 전 ------ \n");
   printf("str1 = %s\nstr3 = %s\n", str1, str3);
   strSwap(str1, str3);
   printf("------ 첫 번째 strSwap() 함수 호출 후 ------\n");
   printf("str1 = %s\nstr3 = %s\n", str1, str3);
   strSwap(str1, str3);
   printf("------ 두 번째 strSwap() 함수 호출 후 ------\n");
   printf("str1 = %s\nstr3 = %s\n", str1, str3);

   return 0;
}
```

**Sample Run:**

```text
문자열(str1) 입력: c is fun!!

str1의 길이: 10

str2 = c is fun!!

str1을 대문자로 변환 = C IS FUN!!

str2의 역순 = !!NUF SI C

c is fun!! == c is fun!!

strcmp("abc", "abcd") = -1

strcmp("C++", "C") = 1

------ strSwap() 함수 호출 전 ------
str1 = c is fun!!
str3 = C is powerful
------ 첫 번째 strSwap() 함수 호출 후 ------
str1 = C is powerful
str3 = c is fun!!
------ 두 번째 strSwap() 함수 호출 후 ------
str1 = c is fun!!
str3 = C is powerful

Program ended with exit code: 0
```

**[Solution](Solutions.md#exercise-1-string-manipulation)**

---

<br>

## Exercise 2: Values of String Pointer Expressions

**Textbook Problem:** Chapter 9 exercise 4

**Problem:** Assume `const char *p = "summer";` and that the string `"summer"` is at address `0x8000`. Write the value printed by each statement.

- (1) `printf("%p", p);`
- (2) `printf("%p", p + 2);`
- (3) `printf("%c", *p);`
- (4) `printf("%c", p[1]);`
- (5) `printf("%s", p + 1);`

**[Solution](Solutions.md#exercise-2-values-of-string-pointer-expressions)**

---

<br>

## Exercise 3: Values of String Array Expressions

**Textbook Problem:** Chapter 9 exercise 10

**Problem:** For `char movies[][20] = { "avengers", "iron man", "thor", "captain america" };`, write the value of each expression.

- (1) `movies[0]`
- (2) `sizeof(movies) / sizeof(movies[0])`
- (3) `movies[0][1]`
- (4) `movies[1][0]`
- (5) `movies[2]`
- (6) `sizeof(movies[0]) / sizeof(movies[0][0])`
- (7) `sizeof(movies) / sizeof(movies[0][0])`
- (8) `*movies[3]`

**[Solution](Solutions.md#exercise-3-values-of-string-array-expressions)**

---

<br>

## Exercise 4: Misuse of `strcpy`

**Textbook Problem:** Chapter 9 exercise 2

**Problem:** Select every piece of code below that misuses `strcpy`, and state what problem each causes.

- ① `char s1[10]; strcpy(s1, "abc");`
- ② `char s2[10] = "x"; strcpy("apple", s2);`
- ③ `char s3[3]; strcpy(s3, "good job");`
- ④ `char s4[] = "xyz", s5[4]; strcpy(s5, s4);`
- ⑤ `strcpy("hello", "bye");`

**[Solution](Solutions.md#exercise-4-misuse-of-strcpy)**

---

<br>

## Exercise 5: Printing Initials

**Textbook Problem:** Chapter 9 programming assignment 2

**Problem:** Write a program that reads an English name on one line and prints the initials, collecting the first letter of each word in uppercase. Words are separated by spaces, and the program must work correctly even with several spaces before, after, or between words. Read the input with `fgets`.

**Sample Run:**

```text
name? Son Heung Min
initials: SHM
name?   ada   lovelace
initials: AL
```

**[Solution](Solutions.md#exercise-5-printing-initials)**

---

<br>

## Exercise 6: Case-Insensitive String Comparison

**Textbook Problem:** Chapter 9 programming assignment 6

**Problem:** Write a function `int strcmp_ic(const char *lhs, const char *rhs)` that compares two strings without distinguishing case. The sign of the return value is the same as for `strcmp`: negative if `lhs` comes first, 0 if equal, and positive if it comes later. The two strings must be compared directly, one character at a time, without using `strcmp`. The results of the following three comparisons must all print as 1 (true).

```c
printf("%d\n", strcmp_ic("Avengers", "avengers") == 0);
printf("%d\n", strcmp_ic("Thor", "thanos") > 0);
printf("%d\n", strcmp_ic("iron", "Iron Man") < 0);
```

**[Solution](Solutions.md#exercise-6-case-insensitive-string-comparison)**

---

<br>

## Exercise 7: Counting Words

**Problem:** Write a function `int count_words(const char *s)` that returns the number of words in a string. A word is a run of characters other than spaces, tabs, and newlines, and words must be counted exactly even when whitespace characters repeat or appear at the start or end of the string.

**Sample Run:** These are the results for the three strings `"to be or not to be"`, `"   leading and   double  spaces  "`, and `""`.

```text
6
4
0
```

**[Solution](Solutions.md#exercise-7-counting-words)**
