# Chapter 9 Lab — Strings and String Pointers

[Repository Guide](../../README.md) | [English](Concepts_Lab.md) | [한국어](Concepts_Lab.ko.md)

> **Last Updated:** 2026-10-27
>
> 문제풀이 중심의 C언어 연습, 김용일 외, Ch 8, 9

> **Learning Objectives:**
> 1. Distinguish string constants from string variables (character arrays) and explain how the null character marks the end of a string
> 2. Initialize character arrays with string literals and character constants, and modify them element by element or copy into them with `strcpy`
> 3. Explain the difference between `scanf("%s")` and line input functions, and the characters left in the input buffer
> 4. Implement string length, uppercase conversion, reversal, and comparison without library functions
> 5. Explain the difference between a pointer to a string literal and a pointer to a character array

---

## Table of Contents

- [1. Strings](#1-strings)
  - [1.1 String Constants and String Variables](#11-string-constants-and-string-variables)
  - [1.2 Printing Strings and %s](#12-printing-strings-and-s)
  - [1.3 Modifying Character Arrays](#13-modifying-character-arrays)
  - [1.4 Initialization and the Null Character](#14-initialization-and-the-null-character)
  - [1.5 Arrays of Strings](#15-arrays-of-strings)
  - [1.6 String Input Functions](#16-string-input-functions)
- [2. String Practice](#2-string-practice)
  - [2.1 Length of a String](#21-length-of-a-string)
  - [2.2 Converting Lowercase to Uppercase](#22-converting-lowercase-to-uppercase)
- [3. String Pointers](#3-string-pointers)
  - [3.1 A Pointer to a String Literal](#31-a-pointer-to-a-string-literal)
  - [3.2 A String Literal Cannot Be Modified](#32-a-string-literal-cannot-be-modified)
  - [3.3 A Pointer to a Character Array](#33-a-pointer-to-a-character-array)
- [4. String Pointer Practice](#4-string-pointer-practice)
  - [4.1 Reversing a String](#41-reversing-a-string)
  - [4.2 Breaking Lines at Spaces](#42-breaking-lines-at-spaces)
  - [4.3 Comparing Two Strings](#43-comparing-two-strings)
- [Summary](#summary)
- [Self-Check Questions](#self-check-questions)

---

<br>

## 1. Strings

### 1.1 String Constants and String Variables

A sequence of characters written inside double quotes is a **string constant** or **string literal**. `"Hello World!"` in `printf("Hello World!");` is an example. A string literal is a string with the properties of a constant, so it cannot be modified, and the program stores string literals in a memory area kept separately for them ([Chapter 9, Section 1.1](Concepts_Lecture.md#11-characters-vs-strings)).

A **string variable** is a string stored and used in a character array. A string usually means a string variable, and the values kept in a character array can be changed. A string has the **null character** `'\0'` (code value 0) at its end to mark the end ([Chapter 9, Section 1.2](Concepts_Lecture.md#12-declaration-and-initialization)).

```c
char str1[5] = "Good";                      // a string literal adds '\0' automatically
char str2[] = {'a', 'b', 'c', '\0'};        // with character constants, '\0' must be written
```

```text
        [0]    [1]    [2]    [3]    [4]
 str1 │ 'G' │ 'o' │ 'o' │ 'd' │ '\0' │
 str2 │ 'a' │ 'b' │ 'c' │ '\0' │
```

*Figure 1. Elements of the character arrays str1 and str2*

Initializing with a string literal adds the null character at the end automatically, so storing `"Good"` needs 5 elements. When initializing with a sequence of character constants, the null character must be written explicitly.

### 1.2 Printing Strings and %s

A string is printed with the format specifier `%s`.

```c
#include <stdio.h>

int main(void)
{
    char str1[5] = "Good";                      // a string literal adds '\0' automatically
    char str2[] = {'a', 'b', 'c', '\0'};        // with character constants, '\0' must be written

    printf("%s \n", str1);      // %s prints characters until it meets '\0'
    printf("%s \n", str2);

    return 0;
}
```

```text
Good 
abc 
```

In `printf("%s", str1);`, the name of the character array `str1` is the starting memory address of the string. `printf` goes to this address, prints the elements one at a time, and stops when it meets the null character ([Chapter 9, Section 4.1](Concepts_Lecture.md#41-scanf--printf-with-s)).

### 1.3 Modifying Character Arrays

There are two ways to put a string into a character array declared without an initial value. The code is [Example_CharArray.c](Example_CharArray.c).

- **Assign character constants element by element:** A string is a sequence of character constants, so each element is changed with a character constant, as in `str[0] = 'H';`. The null character `'\0'` that marks the end of the string must also be put in the last position explicitly. The first comment of the code shows this method.
- **Copy with `strcpy`:** The string copy function `strcpy(str, "Hello");` copies everything up to and including the null character at once. Using `strcpy` requires including `<string.h>` ([Chapter 9, Section 2.2](Concepts_Lecture.md#22-strcpy--strncpy)).

```c
#define _CRT_SECURE_NO_WARNINGS  // allows strcpy in Visual Studio
#include <stdio.h>
#include <string.h>

/*int main()
{
    char str[7];
    printf("1. %s \n", str);

    // assign values with character literals
    str[0] = 'H';
    str[1] = 'e';
    str[2] = 'l';
    str[3] = 'l';
    str[4] = 'o';
    str[5] = '\0';
    printf("2. %s \n", str);
}*/

int main()
{
    char str[7];
    printf("1. %s \n", str);  // str is not initialized yet, so this prints whatever is in memory

    // update the string with strcpy()
    strcpy(str, "Hello");
    printf("2. %s \n", str);
}
```

```text
2. Hello 
```

The first `printf` prints an uninitialized array, so unknown bytes left in that memory are printed, or the function may read past the array until it finds a null character. This is undefined behavior and the result differs from run to run, so the output above shows only the second line, after `strcpy`.

> **Note:** Visual Studio issues warning C4996 for `strcpy` because it does not check the size of the destination array, and it is turned off with `#define _CRT_SECURE_NO_WARNINGS` or `#pragma warning(disable:4996)` ([Chapter 3 Lab, Section 5.1](../Ch03_Data-Types-and-Variables/Concepts_Lab.md#51-warning-c4996)). The compiler does not check that the destination array is large enough to hold the string and the null character, so the programmer must guarantee it.

A character array initialized with a string literal at its declaration can also be changed element by element.

```c
#include <stdio.h>

int main(void)
{
    char str[6] = "hello";
    printf("1. %s \n", str);

    str[0] = 'H';               // an element of a char array can be changed
    printf("2. %s \n", str);

    return 0;
}
```

```text
1. hello 
2. Hello 
```

### 1.4 Initialization and the Null Character

Initializing with a string literal adds the null character at the end automatically, but initializing with character constants requires writing the null character explicitly.

```c
#include <stdio.h>

int main(void)
{
    char arr1[] = "abc";                        // 4 elements: 'a', 'b', 'c', '\0'
    char arr2[] = {'a', 'b', 'c'};              // 3 elements: no '\0', so not a string
    char arr3[] = {'a', 'b', 'c', '\0'};        // 4 elements: the same as arr1

    printf("%zu %zu %zu\n", sizeof(arr1), sizeof(arr2), sizeof(arr3));

    return 0;
}
```

```text
4 3 4
```

`arr2` is a three-element character array without a null character, so it is not a string. Using it as a string, as in `printf("%s", arr2);`, reads past the end of the array looking for a null character, which is undefined behavior.

The null character tells where a string ends. Printing a string outputs characters one at a time from the start and stops at the null character, and computing the length of a string also counts until the null character.

```c
#include <stdio.h>

int main(void)
{
    char str[10] = "Ab # 31";   // str[7] to str[9] are filled with '\0'
    int i;

    printf("%s \n", str);       // printing stops at the first '\0'
    for (i = 0; i < 10; i++)
        printf("%d ", str[i]);  // the character codes of all 10 elements
    printf("\n");

    return 0;
}
```

```text
Ab # 31 
65 98 32 35 32 51 49 0 0 0 
```

`"Ab # 31"` has seven characters including spaces, so it is stored in `str[0]`-`str[6]`, and the remaining `str[7]`-`str[9]` are filled with 0 (the null character). The space character (code 32) is not the null character, so printing does not stop at a space.

### 1.5 Arrays of Strings

To use several strings, a two-dimensional character array is used. `char str[3][6]` stores three strings of up to 5 characters (6 elements including the null character); `str[i]` is the i-th string and `str[i][j]` the j-th character of that string ([Chapter 9, Section 7.1](Concepts_Lecture.md#71-2d-char-array)). The code is [Example_StringArray.c](Example_StringArray.c).

```c
#include <stdio.h>

int main()
{
    char str[3][6] = { {"ABC"}, {"defg"}, {"1Q$"} };
    int i;

    for (i = 0; i < 3; i++) {
        printf("%s \n", str[i]);
    }
    printf("------------ \n");
    str[0][0] = 'a';
    str[0][2] = 'c';
    printf("%c \n", str[0][0]);
    printf("%s \n", str[0]);
}
```

```text
ABC 
defg 
1Q$ 
------------ 
a 
aBc 
```

|  | [0] | [1] | [2] | [3] | [4] | [5] |
|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
| `str[0]` | `'a'` | `'B'` | `'c'` | `'\0'` | `'\0'` | `'\0'` |
| `str[1]` | `'d'` | `'e'` | `'f'` | `'g'` | `'\0'` | `'\0'` |
| `str[2]` | `'1'` | `'@'` | `'$'` | `'\0'` | `'\0'` | `'\0'` |

*Table 1. The array of strings after changing str[0][0] and str[0][2]*

`str[0][0] = 'a';` and `str[0][2] = 'c';` change only the first and third characters of the first string `"ABC"`, so `str[0]` becomes `"aBc"`. Printing `str[0][0]` with `%c` prints the single character `a`, and printing `str[0]` with `%s` prints the string `aBc`.

### 1.6 String Input Functions

`scanf("%s", ...)` stops reading at a white-space character (space, tab, newline), so it reads only one word. To read a line that contains spaces, a line input function is used. The code is [Example_InputBuffer.c](Example_InputBuffer.c).

```c
#define _CRT_SECURE_NO_WARNINGS  // allows scanf in Visual Studio
#include <stdio.h>
#include <string.h>
int main()
{
    char nOne[20] = "";
    char nTwo[20] = "";

    printf(">> 1. input name: ");
    scanf(" %s", nOne);     // enter a name such as hong gil dong

    // also note how the program behaves when the while loop below (which empties the buffer) is commented out
    while (getchar() != '\n');      // " gil dong" and Enter remain in the buffer after hong is read; this discards them

    printf(">> 2. input name: ");
    fgets(nTwo, sizeof(nTwo), stdin);   // enter a name such as hong gil dong
    nTwo[strcspn(nTwo, "\n")] = '\0';   // remove the newline that fgets keeps

    printf("-> nOne: %s \n", nOne);     // prints only hong (scanf stops at the space)
    printf("-> nTwo: %s \n", nTwo);     // prints all of hong gil dong
}
```

```text
>> 1. input name: hong gil dong
>> 2. input name: hong gil dong
-> nOne: hong 
-> nTwo: hong gil dong 
```

- **First input:** `scanf(" %s", nOne);` reads only `hong` and stores it in `nOne`, and the rest, ` gil dong` and the newline character, stays in the input buffer. The array name `nOne` is already an address, so no `&` is written.
- **Emptying the buffer:** `while (getchar() != '\n');` reads and discards the characters left in the buffer up to the newline character. Without this line, the second input function would not wait for the user but would immediately read the ` gil dong` left in the buffer.
- **Second input:** The line input function reads the whole line including spaces, `hong gil dong`.

> **Note:** **`gets`, `gets_s`, and `fgets`.** `gets`, which does not receive the size of the array and can cause buffer overflows, was removed from the standard in C11. Visual Studio provides `gets_s(str, sizeof(str));` instead, but this function belongs to the optional Annex K of C11 and is usually absent from the standard libraries of gcc and clang. The examples of this repository use the standard function `fgets(str, sizeof(str), stdin);` so that they compile with any compiler. Unlike `gets_s`, `fgets` keeps the newline character it reads in the array, so `str[strcspn(str, "\n")] = '\0';` replaces the newline with the null character ([Chapter 9, Section 4.2](Concepts_Lecture.md#42-fgets--gets_s)). For the same reason, reading a string with `scanf_s` requires passing the size of the array as well, as in `scanf_s("%s", nOne, 20);`.

---

<br>

## 2. String Practice

The following problems practice processing strings by the null character without library functions such as `strlen` and `isupper`. The solution code is the example files in this unit folder; each file compiles with `gcc -std=c99 -Wall` without warnings, and the outputs are from actual runs.

### 2.1 Length of a String

**Problem:** Declare the character array `char str[15] = "";`, read a string (14 characters or fewer) from the screen, and compute and print its length without using the `strlen` function.

**Solution:** Increase the index `len` from 0 and count while `str[len]` is not the null character. When the loop ends, `len` is the index of the null character, and that value is the length of the string. Spaces are characters too, so they are counted.

**Code:** [Example_StringLength.c](Example_StringLength.c)

```c
#include <stdio.h>
#include <string.h>

int main()
{
    char str[15] = "";
    int len = 0;

    printf(">> input str: ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0';     // remove the newline that fgets keeps

    while (str[len] != '\0')
        len++;

    printf("-> len: %d \n", len);       // strlen(str) also gives the length
}
```

```text
>> input str: Hello World
-> len: 11 
```

### 2.2 Converting Lowercase to Uppercase

**Problem:** Read a string into `char str[15] = "";`, convert all lowercase letters to uppercase in place, and print it. Do not use character functions such as `isupper` or `strlen`.

**Solution:** The lowercase letters `'a'`-`'z'` and the uppercase letters `'A'`-`'Z'` are consecutive at the same spacing in ASCII, and the lowercase and uppercase forms of the same letter differ by `'a' - 'A'` = 32. So a lowercase letter is turned into uppercase by subtracting 32. The loop condition can be written as just `str[i]` instead of `str[i] != '\0'` because the code of the null character is 0, which is false in a condition, so the length of the string need not be computed first. Characters that are not lowercase letters (uppercase letters, digits, spaces) are left as they are.

**Code:** [Example_ToUpper.c](Example_ToUpper.c)

```c
#include <stdio.h>
#include <string.h>

int main()
{
    char str[15] = "";
    int i;

    printf(">> input str: ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0';     // remove the newline that fgets keeps

    /*int len = 0;

    while (str[len] != '\0')
        len++;

    for (i = 0; i < len; i++) {
        if (str[i] >= 'a' && str[i] <= 'z')
            str[i] -= 'a' - 'A';
    }*/

    for (i = 0; str[i]; i++) {      // the loop range can be set without computing the length as above (str[i] != '\0')
                                    // str[i] alone works instead of str[i] != '\0' because the ASCII value of \0 is 0
        if (str[i] >= 'a' && str[i] <= 'z')
            str[i] -= 'a' - 'A';
    }

    printf("-> str: %s", str);
}
```

```text
>> input str: Hello C 2024
-> str: HELLO C 2024
```

Counting the uppercase and lowercase letters of an input string is covered in [HW10 Problem 2](../../Coursework/HW10_Strings/Assignment-Explanation.md#2-string-search).

---

<br>

## 3. String Pointers

### 3.1 A Pointer to a String Literal

`char *pc = "AbCde";` does not copy the string literal `"AbCde"` into a character array but stores in the pointer `pc` the starting address of that string in the storage reserved for string literals ([Chapter 9, Section 6.1](Concepts_Lecture.md#61-char-string-pointer)). The string can be read and printed through `pc`.

```text
 [Storage for string literals]
   0x102ab44e4
  ┌─────┬─────┬─────┬─────┬─────┬──────┐
  │ 'A' │ 'b' │ 'C' │ 'd' │ 'e' │ '\0' │
  └─────┴─────┴─────┴─────┴─────┴──────┘
     ▲
 pc ─┘  (pc = 0x102ab44e4)
```

*Figure 2. Pointer pc pointing to a string literal*

### 3.2 A String Literal Cannot Be Modified

A string literal cannot be modified, so trying to change a character of a literal through a pointer is undefined behavior. The code is [Example_StringLiteral.c](Example_StringLiteral.c).

```c
#include <stdio.h>

int main()
{
    char* pc = "AbCde";

    printf("%p \n", pc);
    printf("%s \n", pc);

    pc[1] = 'B';        // attempt to change a string literal through a pointer -> run-time error
    puts(pc);
}
```

```text
0x102ab44e4 
AbCde 
```

`pc[1] = 'B';` compiles without a compile error, but at run time the program terminates abnormally at that line, and the last `puts(pc);` is not executed. Most operating systems place string literals in read-only memory, so an attempt to write causes a memory access violation. The result above was run on macOS, where the program ended with a bus error (SIGBUS); in Visual Studio the debugger reports a write access violation exception.

> **Caution:** A pointer that points to a string literal should be declared with `const`, as in `const char *pc = "AbCde";`. Then the compiler catches a write such as `pc[1] = 'B';` as an error ([Chapter 9, Section 6.2](Concepts_Lecture.md#62-const-char)).

### 3.3 A Pointer to a Character Array

If a string literal is stored in a character array and the array is then pointed to by a pointer, the contents of the string can be changed through the pointer. This is because `char str[] = "AbCde";` copies the contents of the literal into a modifiable array.

```c
#include <stdio.h>

int main(void)
{
    char str[] = "AbCde";       // a char array initialized with a copy of the literal
    char *ps = str;             // ps points to the first element of the array

    ps[1] = 'B';                // changes str[1]: the array is modifiable
    printf("%s \n", str);

    return 0;
}
```

```text
ABCde 
```

`ps` points to `str[0]`, so `ps[1]` is `str[1]`, and `ps[1] = 'B';` changes the second character of the array from `'b'` to `'B'`.

---

<br>

## 4. String Pointer Practice

The solution code is the example files in this unit folder; each file compiles with `gcc -std=c99 -Wall` without warnings, and the outputs are from actual runs. In programs whose messages end without `\n`, the next prompt follows the message directly in a real terminal.

### 4.1 Reversing a String

**Problem:** Store a string entered on the screen in an array, call the function `revStr`, which stores the contents of the array in reverse, and print the changed string.

**Solution:** The function parameter `char *arr` is a pointer to the array, and when a pointer points to an array, an index can be used, as in `arr[i]`. To reverse a string of length len, swap the i-th character with the (len - 1 - i)-th character.

```text
 len = 6:  [0] [1] [2] [3] [4] [5]     [0]↔[5], [1]↔[4], [2]↔[3]
            A   b   c   ' ' 3   B      i = 0, 1, 2 (i < 3)

 len = 5:  [0] [1] [2] [3] [4]         [0]↔[4], [1]↔[3], [2] unchanged
            A   b   c   ' ' 3          i = 0, 1 (i < 2.5)
```

*Figure 3. Positions swapped when reversing a string*

Swapping needs to go only halfway through the string. Going to the end would swap the pairs back and restore the original string. The condition `i < (len / 2.0)` in the code is a real division, so when len is odd the loop also runs at the middle index len / 2, but that character is swapped with itself, so the result is the same. The integer division `i < len / 2` also works.

**Code:** [Example_ReverseString.c](Example_ReverseString.c)

```c
#include <stdio.h>
#include <string.h>
#define SIZE 10

void revStr(char* arr);
void swap(char* a, char* b);

int main()
{
    char str[SIZE] = "";

    printf(">> input str: ");
    fgets(str, SIZE, stdin);
    str[strcspn(str, "\n")] = '\0';     // remove the newline that fgets keeps

    revStr(str);
    printf("-> A reverse str: %s", str);
}

void revStr(char* arr)
{
    int i, len = strlen(arr);

    for (i = 0; i < (len / 2.0); i++) {
        swap(&arr[i], &arr[len - i - 1]);
    }
}

void swap(char* a, char* b)
{
    int temp;

    temp = *a;
    *a = *b;
    *b = temp;
}
```

```text
>> input str: Abc 3B
-> A reverse str: B3 cbA
```

```text
>> input str: Abc 3
-> A reverse str: 3 cbA
```

`swap` receives the addresses of two characters, `&arr[i]` and `&arr[len - i - 1]`, and swaps the values at those places ([Chapter 8 Lab, Section 4.3](../Ch08_Pointers/Concepts_Lab.md#43-swapping-two-variables-with-a-function)). The array size `SIZE` is 10, so for input longer than 9 characters `fgets` reads only 9. A solution that moves two pointers inward from both ends is in [HW10 Problem 3](../../Coursework/HW10_Strings/Assignment-Explanation.md#3-string-reversal).

### 4.2 Breaking Lines at Spaces

**Problem:** Print the string the user entered, continuing on the next line whenever a white-space character appears. Whether a character is white space is checked with the `isspace` function of `<ctype.h>`.

**Solution:** Examine the string one character at a time from the beginning, printing a newline character for white space and the character itself otherwise. `isspace` returns a nonzero value for a white-space character (space, tab, newline, and so on) and 0 otherwise, so it can be used directly in a condition ([Chapter 9, Section 3.1](Concepts_Lecture.md#31-classification)).

**Code:** [Example_WordSplit.c](Example_WordSplit.c)

```c
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main()
{
    char str[15] = "";
    int i;

    printf(">> input str: ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0';     // remove the newline that fgets keeps

    printf("word: \n");
    for (i = 0; i < strlen(str); i++) {
        if (isspace(str[i]))        // isspace() returns 0 for a non-space character and a nonzero value for a space character
            printf("\n");
        else
            printf("%c", str[i]);
    }
}
```

```text
>> input str: I love C
word: 
I
love
C
```

> **Note:** The `strlen(str)` in the loop condition is called on every iteration and counts the length of the string again. This is no problem for short strings, but computing the length once before the loop, or using `str[i]` as the condition as in Section 2.2, avoids unnecessary computation. Also, the argument of `isspace` must be a value representable as `unsigned char`, so if bytes with codes of 128 or more, such as Korean text, can occur, write `isspace((unsigned char)str[i])`. Code that solves the same problem with `fgets` and `putchar` is in [HW10 Problem 4](../../Coursework/HW10_Strings/Assignment-Explanation.md#4-string-splitting).

### 4.3 Comparing Two Strings

**Problem:** Implement the function `StrComp`, which returns 1 if two strings are equal and 0 if they are not.

**Solution:** First compare the lengths of the two strings; if they differ, the strings cannot be equal, so return 0 at once. If the lengths are equal, compare the characters at the same index one by one, returning 0 if any differ and 1 if all are equal to the end.

**Code:** [Example_StringCompare.c](Example_StringCompare.c)

```c
#include <stdio.h>
#include <string.h>

int StrComp(char* pOne, char* pTwo);

int main()
{
    char sOne[10] = "ab c";
    char sTwo[10] = "ab d";

    printf("1. result: %d \n", StrComp(sOne, sTwo));
    printf("2. result: %d \n", StrComp("hi", "hi"));
    printf("3. result: %d \n", StrComp("hi", "hi#"));
}

int StrComp(char* pOne, char* pTwo)
{
    int i, lenOne = strlen(pOne), lenTwo = strlen(pTwo);

    if (lenOne != lenTwo)       // strings of different lengths are treated as different
        return 0;

    for (i = 0; i < lenOne; i++) {
        if (pOne[i] != pTwo[i])
            return 0;
    }
    return 1;
}
```

```text
1. result: 0 
2. result: 1 
3. result: 0 
```

- `"ab c"` and `"ab d"` both have length 4, but their fourth characters `'c'` and `'d'` differ, so 0.
- `"hi"` and `"hi"` have all characters equal, so 1.
- `"hi"` and `"hi#"` have lengths 2 and 3, so 0.

> **Note:** The standard function `strcmp` returns 0 if the strings are equal, a negative value if the first string comes first in dictionary order, and a positive value if it comes later, so the meaning of its return value is the opposite of `StrComp` ([Chapter 9, Section 2.3](Concepts_Lecture.md#23-strcmp--strncmp)). Also, the parameters of `StrComp` only read the strings, so they are better declared as `const char *`.

---

<br>

## Summary

| Concept | Key Summary |
|:-----|:-----|
| String literal | A string constant written in double quotes, stored in a separate memory area and not modifiable. |
| String variable | A string stored in a character array, whose elements can be changed. |
| Null character | `'\0'`, with code value 0, marks the end of a string and is added automatically when initializing with a literal. |
| `%s` | Prints characters from the starting address of the string until it meets the null character. |
| `strcpy` | Copies a string up to the null character; the destination array must be large enough. |
| Array of strings | Several strings are stored in a two-dimensional character array, and `str[i]` is the i-th string. |
| String input | `scanf("%s")` stops at white space, and a line input function reads a whole line including spaces. |
| String pointers | Characters cannot be changed through a pointer to a literal, but can be through a pointer to a character array. |
| Reversing a string | Swap the i-th and (len - 1 - i)-th characters only up to the middle of the string. |
| Comparing strings | Strings of different lengths differ; with equal lengths, compare the characters one by one. |

---

<br>

## Self-Check Questions

1. **Array size:** What is `sizeof(s)` for `char s[] = "C language";`?

   <details>
   <summary>Answer</summary>

   It stores 10 characters including the space and 1 automatically added null character, so it is 11.

   </details>

2. **Null character:** What does `printf("%s", t);` print for `char t[8] = "AB\0CD";`?

   <details>
   <summary>Answer</summary>

   `%s` stops at the first null character, so only `AB` is printed. `'C'` and `'D'` are also stored in the array.

   </details>

3. **Input functions:** When the user enters `New York` and it is read with `scanf("%s", city);`, what is stored in `city`, and what remains in the input buffer?

   <details>
   <summary>Answer</summary>

   `New` is stored in `city`, and ` York` and the newline character remain in the buffer. To read the whole line including spaces, a line input function such as `fgets` is used.

   </details>

4. **String pointers:** With `char a[] = "dog"; char *p = "cat";`, which of `a[0] = 'f';` and `p[0] = 'b';` causes a problem?

   <details>
   <summary>Answer</summary>

   `p[0] = 'b';`. `p` points to a string literal, which cannot be modified, so the write is undefined behavior. `a` is a character array that copies the contents of the literal, so `a[0] = 'f';` is fine.

   </details>

5. **Reversing:** If the loop condition of `revStr` in Section 4.1 is changed to `i < len`, what is the result for `"abc"`?

   <details>
   <summary>Answer</summary>

   At i = 0, a and c are swapped, giving `cba`; at i = 1, the middle b is swapped with itself; and at i = 2, the first and third characters are swapped again, giving back `abc`. So the string appears unchanged.

   </details>
