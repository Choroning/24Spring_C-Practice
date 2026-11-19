# Chapter 9 Solutions — Strings

[Repository Guide](../../README.md) | [English](Solutions.md) | [한국어](Solutions.ko.md)

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

---

<br>

## Exercise 2: Values of String Pointer Expressions

**Textbook Problem:** Chapter 9 exercise 4

**Problem:** Write the values printed by five expressions formed with `const char *p`, which points to `"summer"` at address `0x8000`. The expressions are in [Exercise 2](Exercises.md#exercise-2-values-of-string-pointer-expressions).

### Solution

**Answer:** (1) `0x8000` (2) `0x8002` (3) `s` (4) `u` (5) `ummer`

**Explanation:** `p` holds the address of the first character `'s'`, so (1) is that address. The form in which `%p` prints an address is decided by the implementation, and this environment prints it as hexadecimal with `0x`. `char` is 1 byte, so (2) `p + 2` is 0x8000 + 2 = 0x8002, the address of the third character `'m'`. (3) `*p` is the first character `s`, and (4) `p[1]` is `*(p + 1)`, the second character `u`. (5) `%s` prints from the given address up to the null character, so `ummer`, from the second character on, is printed ([Chapter 9, Section 6.1](Concepts_Lecture.md#61-char-string-pointer)).

---

<br>

## Exercise 3: Values of String Array Expressions

**Textbook Problem:** Chapter 9 exercise 10

**Problem:** Write the values of eight expressions on the two-dimensional character array `movies[][20]`. The expressions are in [Exercise 3](Exercises.md#exercise-3-values-of-string-array-expressions).

### Solution

**Answer:** (1) `"avengers"` (2) 4 (3) `'v'` (4) `'i'` (5) `"thor"` (6) 20 (7) 80 (8) `'c'`

**Explanation:** There are 4 initial values, so the number of rows is fixed at 4, making `movies` an array of 4 rows and 20 columns with a total size of 4 × 20 = 80 bytes ([Chapter 9, Section 7.1](Concepts_Lecture.md#71-2d-char-array)). `movies[i]` in (1) and (5) is row i, that is, the i-th string. (2) is the number of rows 4, the total size 80 divided by the size of one row 20; (6) is the number of columns 20, the size of one row 20 divided by the size of one `char` 1; and (7) is the total number of elements 80. (3) is the second character of `"avengers"`, and (4) the first character of `"iron man"`. (8) `*movies[3]` binds `[]` first, giving `*(movies[3])`, the first character `'c'` of `"captain america"`. The following is the actual output of the same expressions.

```text
avengers 4 v i thor
20 80 c
```

---

<br>

## Exercise 4: Misuse of `strcpy`

**Textbook Problem:** Chapter 9 exercise 2

**Problem:** Select the wrong ones among five pieces of code that use `strcpy` and state the problem with each. The choices are in [Exercise 4](Exercises.md#exercise-4-misuse-of-strcpy).

### Solution

**Answer:** ②, ③, ⑤

**Explanation:** `strcpy(dest, src)` copies `src` up to its null character into the modifiable array `dest` points to, so `dest` must be a character array of at least the length of `src` plus 1 byte ([Chapter 9, Section 2.2](Concepts_Lecture.md#22-strcpy--strncpy)).

- ① `s1` is 10 bytes and `"abc"` is 4 bytes including the null character, so it is correct.
- ② The destination is a string literal. In C the type of a literal is a `char` array without `const`, so there may be no compile warning, but changing a literal is undefined behavior, and the program usually terminates abnormally.
- ③ `"good job"` is 9 bytes including the null character, but `s3` is 3 bytes, so a buffer overrun occurs. Clang issues the warning `'strcpy' will always overflow; destination buffer has size 3, but the source string has length 9 (including NUL byte)`.
- ④ `s4` is a 4-byte array initialized with `"xyz"`, and `s5` is also 4 bytes, so the copy fits exactly, including the null character, and is correct.
- ⑤ As in ②, the destination is a literal, so it is wrong.

---

<br>

## Exercise 5: Printing Initials

**Textbook Problem:** Chapter 9 programming assignment 2

**Problem:** From an English name read on one line, collect the first letter of each word in uppercase and print it, working correctly even with several spaces. The sample run is in [Exercise 5](Exercises.md#exercise-5-printing-initials).

### Solution

**Approach:** Keep a variable `at_start` that indicates "this is where a word may start." On a space, set `at_start` to 1; on a non-space character, if `at_start` is 1, that character is the first letter of a word, so add it to the initials and set `at_start` to 0.

```c
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    char name[64], initials[16];
    int i, n = 0, at_start = 1;

    printf("name? ");
    if (fgets(name, sizeof(name), stdin) == NULL)
        return 1;
    name[strcspn(name, "\n")] = '\0';

    for (i = 0; name[i] != '\0'; i++) {
        if (name[i] == ' ') {
            at_start = 1;
        } else if (at_start) {
            initials[n++] = (char)toupper((unsigned char)name[i]);
            at_start = 0;
        }
    }
    initials[n] = '\0';
    printf("initials: %s\n", initials);
    return 0;
}
```

- `fgets` stores the newline character in the array as well, so `strcspn(name, "\n")` finds the position of the first `'\n'`, and a null character is put there. If there is no newline, `strcspn` returns the length of the string, so a null character is simply put back where the original one was.
- The initial value of `at_start` is 1, so the first letter of the first word also becomes an initial. Several spaces before or between words only set `at_start` to 1 several times, and the result is the same.
- The value passed to `toupper` is converted to `unsigned char` because the functions of `<ctype.h>` accept only `EOF` and values representable as `unsigned char`.
- After the initials are collected, the string must be terminated with `initials[n] = '\0'` so that it can be printed with `%s`.

**Output:**

```text
name? Son Heung Min
initials: SHM
name?   ada   lovelace
initials: AL
```

---

<br>

## Exercise 6: Case-Insensitive String Comparison

**Textbook Problem:** Chapter 9 programming assignment 6

**Problem:** Write `strcmp_ic`, which follows the sign rule of `strcmp` but ignores case, by comparing one character at a time. The test code is in [Exercise 6](Exercises.md#exercise-6-case-insensitive-string-comparison).

### Solution

**Approach:** Convert both characters to lowercase before comparing, and return their difference if they differ. If one string ends first, the difference between the `'\0'` (0) of the ended string and the other character decides the sign.

```c
#include <stdio.h>
#include <ctype.h>

int strcmp_ic(const char *lhs, const char *rhs)
{
    int a, b;

    while (*lhs != '\0' && *rhs != '\0') {
        a = tolower((unsigned char)*lhs);
        b = tolower((unsigned char)*rhs);
        if (a != b)
            return a - b;
        lhs++;
        rhs++;
    }
    return tolower((unsigned char)*lhs) - tolower((unsigned char)*rhs);
}

int main(void)
{
    printf("%d\n", strcmp_ic("Avengers", "avengers") == 0);
    printf("%d\n", strcmp_ic("Thor", "thanos") > 0);
    printf("%d\n", strcmp_ic("iron", "Iron Man") < 0);
    return 0;
}
```

- For `"Avengers"` and `"avengers"`, every character is equal after conversion to lowercase and the two strings end together, so the difference after the loop is 0 - 0 = 0.
- `"Thor"` and `"thanos"` differ at the third character, `'o'` (111) and `'a'` (97), so 111 - 97 = 14, a positive value, is returned.
- When `"iron"` ends after 4 characters, the loop exits and returns the difference -32 between `'\0'` (0) and `' '` (32), a negative value.

**Output:**

```text
1
1
1
```

---

<br>

## Exercise 7: Counting Words

**Problem:** Write `count_words`, which returns the number of words separated by whitespace, counting exactly even when whitespace repeats or appears at the ends. The sample run is in [Exercise 7](Exercises.md#exercise-7-counting-words).

### Solution

**Approach:** Counting spaces and adding 1 fails when spaces repeat or appear at the ends. Instead, keep a variable `in_word` that indicates "currently inside a word," and increase the count only when a non-whitespace character is met while `in_word` is 0, that is, when a new word starts.

```c
#include <stdio.h>

int count_words(const char *s)
{
    int count = 0, in_word = 0;

    while (*s != '\0') {
        if (*s == ' ' || *s == '\t' || *s == '\n') {
            in_word = 0;
        } else if (!in_word) {
            in_word = 1;
            count++;
        }
        s++;
    }
    return count;
}

int main(void)
{
    printf("%d\n", count_words("to be or not to be"));
    printf("%d\n", count_words("   leading and   double  spaces  "));
    printf("%d\n", count_words(""));
    return 0;
}
```

In the second string, `in_word` stays 0 through the 3 leading spaces and becomes 1 when a word starts at `l`. It becomes 0 at the space after `leading`, the count becomes 2 at `and`, 3 at `double` after the 3 spaces, and 4 at `spaces`, and the trailing spaces do not change the count. For the empty string, the loop never runs, and 0 is returned. This approach processes the input in one pass with a single state variable, so it counts words exactly regardless of the number or position of the spaces.

**Output:**

```text
6
4
0
```
