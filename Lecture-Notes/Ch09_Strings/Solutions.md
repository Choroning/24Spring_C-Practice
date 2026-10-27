# Chapter 9 Solutions — Strings

[Repository Guide](../../README.md) | [English](Solutions.md) | [한국어](Solutions.ko.md)

> **Last Updated:** 2026-10-27

**Problem Source:** Prof. Younghee Im, Computer Language Ⅰ (DCCS101-04)

---

<br>

## Table of Contents

- [Exercise 1: String Manipulation](#exercise-1-string-manipulation)

---

<br>

## Exercise 1: String Manipulation

**Problem:** Define `my_strlen()`, `my_strcpy()`, `my_strcmp()`, `makeUpper()`, `makeReverse()`, `strSwap()`, and `swap()` yourself without using string library functions. Implement `makeUpper()` with the pointer increment operation and `strSwap()` with pointer arithmetic, and make `makeReverse()` and `strSwap()` exchange characters with `swap()` without a temporary array. The full problem and sample run are in [Exercise 1](Exercises.md#exercise-1-string-manipulation).

### Solution

**Approach:** Every function treats the null character `'\0'` as the end of a string ([Chapter 9, Section 1.1](Concepts_Lecture.md#11-characters-vs-strings)). Parameters that only read a string are received as `const char*`, and parameters whose contents change are received as `char*` ([Chapter 9, Section 6.3](Concepts_Lecture.md#63-guidelines)).

- **`my_strlen()`:** It increases the index `len` from 0 and counts until `p[len]` is the null character. The null character is not counted, so `len` at the end of the loop is the length.
- **`my_strcpy()`:** While `p2[i]` is not the null character, it copies one character at a time into `p1[i]`, and at the end it appends the null character with `p1[i] = '\0'` to terminate the copied string.
- **`my_strcmp()`:** It computes the lengths of both strings and compares the characters at the same positions for the length of the longer one. At the first differing character, it returns 1 if the character of `p1` is greater and -1 if it is smaller; if all characters match, it returns 0. At the end of the shorter string, the null character (0) is compared with the other character, so `"abc"` and `"abcd"` give `'\0' < 'd'` at index 3 and return -1, and `"C++"` and `"C"` give `'+' > '\0'` at index 1 and return 1. Because it returns immediately at the position of the difference, it never reads past the null character of the shorter string.
- **`makeUpper()`:** It increments the parameter `p` and subtracts 32 from `*p` when it is between `'a'` and `'z'`. This works because in ASCII the code difference between lowercase and uppercase letters is `'a' - 'A' = 32`.
- **`makeReverse()`:** For a string of length `size`, it exchanges `p[i]` and `p[size - i - 1]` with `swap()` for `i = 0` through `size / 2 - 1`. Because it swaps only up to the middle, the middle character of an odd-length string stays in place.
- **`strSwap()`:** It finds the length `j` of the longer string and exchanges the characters at the same positions with `swap()` for indices 0 through `j` (including the null character of the longer string). Because the null character of the longer string is also exchanged, the strings in both arrays are swapped completely.
- **`swap()`:** It receives the addresses of two characters and exchanges them with a temporary variable.

**Code:** [Lab_Q1.c](../../Coursework/Lab09_Strings/Lab_Q1.c)

```c
/**
 * @file    A10104-1_C09Q1.c
 * @brief   Q1. 문자열 조작
 * @author  박철원 (Cheolwon Park)
 * @date    2024-05-28
 * 
 * @note    소스 코드에 사용된 gets_s는 Visual Studio 이외의
 *          IDE에서 실행이 불가할 수 있음에 주의하시기 바랍니다.
 */

 #include <stdio.h>
#define SIZE 64

int my_strlen(const char* p);
void my_strcpy(char* p1, const char* p2);
int my_strcmp(const char* p1, const char* p2);
void makeUpper(char p[]);
void makeReverse(char p[]);
void strSwap(char* p1, char* p2);
void swap(char* a, char* b);

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
    printf("\nstr2를 대문자로 변환 = %s\n", str2);

    makeReverse(str2);
    printf("\nstr2를 역순으로 변환 = %s\n", str2);

    my_strcpy(str3, str1);
    if (!my_strcmp(str1, str3))
        printf("\n%s == %s\n", str1, str3);
    if (result = my_strcmp("abc", "abcd"))
        printf("\nstrcmp(\"abc\", \"abcd\") = %d\n", result);
    if (result = my_strcmp("C++", "C"))
        printf("\nstrcmp(\"C++\", \"C\") = %d\n\n", result);

    my_strcpy(str3, "C is powerful");

    printf("------ strSwap() 함수 호출 전 ------\n");
    printf("str1 = %s\nstr3 = %s\n", str1, str3);

    strSwap(str1, str3);
    printf("------ 첫 번째 strSwap() 함수 호출 후 ------\n");
    printf("str1 = %s\nstr3 = %s\n", str1, str3);

    strSwap(str1, str3);
    printf("------ 두 번째 strSwap() 함수 호출 후 ------\n");
    printf("str1 = %s\nstr3 = %s\n", str1, str3);

    return 0;
}

int my_strlen(const char* p)
{
    int len = 0;
    while (p[len])
        len++;
    return len;
}

void my_strcpy(char* p1, const char* p2)
{
    int i = 0;
    while (p2[i]) {
        p1[i] = p2[i];
        i++;
    }
    p1[i] = '\0';
}

int my_strcmp(const char* p1, const char* p2)
{
    int i, j, len1 = 0, len2 = 0;
    while (p1[len1]) len1++;
    while (p2[len2]) len2++;
    j = (len1 >= len2) ? len1 : len2;

    for (i = 0; i < j; i++) {
        if (p1[i] > p2[i]) return 1;
        else if (p1[i] < p2[i]) return -1;
    }
    return 0;
}

void makeUpper(char p[])
{
    while (*p) {
        if (*p >= 'a' && *p <= 'z')
            *p -= 32;
        p++;
    }
}

void makeReverse(char p[])
{
    int i, size = my_strlen(p);
    for (i = 0; i < size / 2; i++) {
        swap(&p[i], &p[size - i - 1]);
    }
}

void strSwap(char* p1, char* p2)
{
    int i, j, len1 = my_strlen(p1), len2 = my_strlen(p2);
    j = len1 > len2 ? len1 : len2;
    for (i = 0; i <= j; i++) {
        swap(&p1[i], &p2[i]);
    }
}

void swap(char* a, char* b)
{
    char temp = *a;
    *a = *b;
    *b = temp;
}
```

**Output:** `gets_s` belongs to Annex K, which is optional in the C11 standard, so Visual Studio provides it but the standard libraries used by gcc and clang do not ([Chapter 9, Section 4.2](Concepts_Lecture.md#42-fgets--gets_s)). To run the code with gcc or clang, define a function with the same behavior (read one line and discard the newline) in a header (for example, `gets_s_compat.h`) and include it with the `-include` option, as in `gcc -std=c99 -Wall -include gets_s_compat.h Lab_Q1.c`.

```c
#include <stdio.h>
#include <string.h>

static char *gets_s(char *s, size_t n) {
    if (!fgets(s, (int)n, stdin)) return NULL;
    s[strcspn(s, "\n")] = '\0';   // discard the newline
    return s;
}
```

Compiling this way produces two warnings (`-Wparentheses`) that ask for parentheses to make the assignment inside the conditions `if (result = my_strcmp(...))` explicit. Entering the string of the sample run gives the following result.

```text
문자열(str1) 입력: c is fun!!

str1의 길이: 10

str2 = c is fun!!

str2를 대문자로 변환 = C IS FUN!!

str2를 역순으로 변환 = !!NUF SI C

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
```

Two prompt lines differ from the sample run: the uppercase result is labeled `str2를 대문자로 변환` instead of `str1을 대문자로 변환`, and the reversed result `str2를 역순으로 변환` instead of `str2의 역순`. Since the string converted to uppercase is `str2`, the code's label matches the actual behavior better. The last line of the sample run, `Program ended with exit code: 0`, is the exit message added by the Xcode console.

> **Note:** **Differences from the requirements.** The requirements ask for `strSwap()` to be implemented with pointer arithmetic, but this code obtains the addresses with subscript notation, as in `&p1[i]` and `&p2[i]`. `&p1[i]` is the same address as `p1 + i`, so the behavior is identical; to follow the notation of the requirement, write `swap(p1 + i, p2 + i);` ([Chapter 8, Section 2.2](../Ch08_Pointers/Concepts_Lecture.md#22-pointer-as-array)). Also, writing the assignment in the condition as `if ((result = my_strcmp("abc", "abcd")) != 0)` makes the intent clear and removes the warning.

> **Caution:** `my_strcmp()` compares `char` values as they are. On systems where `char` is signed, bytes of 0x80 or above, such as those of Hangul in UTF-8, become negative, so when such characters are present the sign of the result may differ from that of the standard `strcmp()`, which compares bytes as `unsigned char`. `strSwap()` accesses positions past the null character in the array of the shorter string, so both arrays must be at least the longer string's length + 1 in size (in this program both arrays are `SIZE` = 64 bytes). If the input exceeds 63 characters, `gets_s` handles it as an error without writing past the array (in Visual Studio the invalid parameter handler is called and terminates the program by default), but when switching to another input function, it must be checked separately that the input does not exceed the array size.
