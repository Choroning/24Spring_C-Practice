# Chapter 9 Exercises — Strings

[Repository Guide](../../README.md) | [English](Exercises.md) | [한국어](Exercises.ko.md)

> **Last Updated:** 2026-10-27

**Problem Source:** Prof. Younghee Im, Computer Language Ⅰ (DCCS101-04)

---

<br>

## Table of Contents

- [Exercise 1: String Manipulation](#exercise-1-string-manipulation)

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
