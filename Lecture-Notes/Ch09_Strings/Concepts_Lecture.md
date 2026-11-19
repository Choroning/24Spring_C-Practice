# Chapter 9 — Strings

[Repository Guide](../../README.md) | [English](Concepts_Lecture.md) | [한국어](Concepts_Lecture.ko.md)

> **Last Updated:** 2026-11-19
>
> Warming-Up C Programming, 천정아, Ch 9

> **Learning Objectives:**
> 1. Explain the difference between characters and strings and how null-terminated strings are stored
> 2. Declare and initialize character arrays and explain the relationship between array size and string length
> 3. Use the length, copy, comparison, concatenation, search, and tokenizing functions of `<string.h>` and explain the risk of buffer overflow
> 4. Use the character functions of `<ctype.h>`, the string I/O functions, and the data conversion functions
> 5. Explain the differences among character arrays, `char*`, and `const char*` and choose the right type for each use
> 6. Compare 2D character arrays with arrays of string pointers and choose the one that fits the situation

---

## Table of Contents

- [1. Character Arrays](#1-character-arrays)
  - [1.1 Characters vs Strings](#11-characters-vs-strings)
  - [1.2 Declaration and Initialization](#12-declaration-and-initialization)
  - [1.3 Usage](#13-usage)
  - [1.4 Processing Strings with the Null Character](#14-processing-strings-with-the-null-character)
- [2. Standard String Functions (`<string.h>`)](#2-standard-string-functions-stringh)
  - [2.1 `strlen`](#21-strlen)
  - [2.2 `strcpy` / `strncpy`](#22-strcpy--strncpy)
  - [2.3 `strcmp` / `strncmp`](#23-strcmp--strncmp)
  - [2.4 `strcat` / `strncat`](#24-strcat--strncat)
  - [2.5 `strchr` / `strstr`](#25-strchr--strstr)
  - [2.6 `strtok`](#26-strtok)
  - [2.7 Comparing and Swapping Strings](#27-comparing-and-swapping-strings)
  - [2.8 Implementing String Functions Directly](#28-implementing-string-functions-directly)
- [3. Character Functions (`<ctype.h>`)](#3-character-functions-ctypeh)
  - [3.1 Classification](#31-classification)
  - [3.2 Conversion](#32-conversion)
- [4. String I/O](#4-string-io)
  - [4.1 `scanf` / `printf` with `%s`](#41-scanf--printf-with-s)
  - [4.2 `fgets` / `gets_s`](#42-fgets--gets_s)
  - [4.3 `puts`](#43-puts)
  - [4.4 Common Problems in String Input](#44-common-problems-in-string-input)
- [5. Data Conversion Functions (`<stdlib.h>`, `<stdio.h>`)](#5-data-conversion-functions-stdlibh-stdioh)
  - [5.1 String to Number](#51-string-to-number)
  - [5.2 `sscanf` / `sprintf`](#52-sscanf--sprintf)
- [6. String Pointers](#6-string-pointers)
  - [6.1 `char*` String Pointer](#61-char-string-pointer)
  - [6.2 `const char*`](#62-const-char)
  - [6.3 Guidelines](#63-guidelines)
  - [6.4 Writing Functions That Take String Parameters](#64-writing-functions-that-take-string-parameters)
  - [6.5 Storage of `char[]` Versus `char*`](#65-storage-of-char-versus-char)
- [7. String Arrays](#7-string-arrays)
  - [7.1 2D `char` Array](#71-2d-char-array)
  - [7.2 Array of String Pointers](#72-array-of-string-pointers)
  - [7.3 Memory Comparison of the Two Kinds of String Arrays](#73-memory-comparison-of-the-two-kinds-of-string-arrays)
- [Concept Applications](#concept-applications)
- [Summary](#summary)
- [Self-Check Questions](#self-check-questions)

---

<br>

## 1. Character Arrays

### 1.1 Characters vs Strings

A **string** is a sequence of consecutive characters, and a **character** is a single character. In C, a **character** and a **string** are fundamentally different.

| Item | Example | Size | Stored As |
|:-----|:--------|:-----|:----------|
| Character literal | `'A'` | 1 byte when stored in a `char` variable (in C a character constant itself has type `int`, so `sizeof('A')` is `sizeof(int)`) | ASCII value `65` |
| String literal | `"A"` | 2 bytes | `'A'` + `'\0'` |

*Table 1. Comparison of a character literal and a string literal*

A **string** in C is a **null-terminated character array**, a sequence of `char` values ending with the special character `'\0'` (ASCII 0). It is called a null-terminated string because the null character that marks its end is stored with it.

```text
Character:  'A'      →  [ 65 ]                           (1 byte)
String:     "A"      →  [ 65 ][ 0 ]                      (2 bytes)
String:     "Hello"  →  [ H ][ e ][ l ][ l ][ o ][ \0 ]  (6 bytes)
```

*Figure 1. Storage of the character `'A'` and the strings `"A"` and `"Hello"`*

**String constant vs string variable:**

- A **string constant** (literal) like `"Hello"` is a string whose value does not change, and the compiler typically stores it in **read-only memory**. You cannot modify it.
- A **string variable** is a `char` array that holds a copy of the string. Its contents can be modified, so a string entered by the user at run time or a string whose contents change must be stored in a character array.

> **Key Point:** The null terminator `'\0'` is what tells all string functions where the string ends. Without it, functions like `printf("%s", ...)` will read past the array boundary, which is **undefined behavior**.

### 1.2 Declaration and Initialization

A character array must be large enough to hold the string **plus one extra byte** for `'\0'`. That is, the array size must be at least the length of the string to store + 1.

```c
// Explicit size: remaining positions filled with '\0'
char str1[10] = "abc";    // stores: 'a','b','c','\0','\0',...,'\0' (size 10)

// Auto-sized: compiler determines size from initializer
char str2[] = "abc";      // stores: 'a','b','c','\0' (size 4)

// Initialized with character list (must include '\0' manually)
char str3[] = {'a', 'b', 'c', '\0'};  // same as str2

// Initialized with character list WITHOUT '\0': NOT a valid string!
char str4[] = {'a', 'b', 'c'};        // size 3, no null terminator
```

When an initializer is given, the array size can be omitted, and the array is allocated with the string length + 1. To initialize an entire character array with null characters, initialize it with the **null string** (`""`), a string consisting of a single null character.

```c
char str5[10] = "";   // all 10 bytes are '\0'
```

**Memory layout of `char str[10] = "abc";`:**

```text
Index:   [0]  [1]  [2]   [3]  [4]  [5]  [6]  [7]  [8]  [9]
Value:   'a'  'b'  'c'  '\0' '\0' '\0' '\0' '\0' '\0' '\0'
```

*Figure 2. Memory layout of `char str[10] = "abc";`*

> **Caution:** If the string length equals or exceeds the array size, no `'\0'` is stored. This creates a char array that is **not** a valid string and will cause bugs with all string functions. When the string length equals the array size, C initializes the array without a null character; when it exceeds the array size, the compiler issues a warning or an error.

```c
char danger[3] = "abc";  // stores: 'a','b','c', NO '\0'!
printf("%s", danger);     // undefined behavior: reads past array boundary
```

### 1.3 Usage

**Accessing individual characters:** Array elements can be accessed by index.

```c
char str[] = "Hello";
printf("%c\n", str[0]);   // H
printf("%c\n", str[4]);   // o
str[0] = 'h';             // OK: modify individual character
printf("%s\n", str);      // hello
```

**Printing strings:** A string can be printed one character at a time with `%c`, or all at once with the `%s` format specifier, which prints until it meets the null character.

```c
char str[] = "Hello";
printf("%s\n", str);      // prints until '\0': Hello
printf("%c\n", str[1]);   // prints one character: e
```

**Cannot assign a string after declaration:**

```c
char str[10];
str = "Hello";   // ERROR: array name is a constant pointer, cannot reassign
```

The array name `str` is the starting address of the array and acts as a **constant pointer** that cannot be changed. Because you cannot change where it points, use `strcpy()` instead.

```c
char str[10];
strcpy(str, "Hello");  // correct way to copy a string into an array
```

Individual characters can be modified (`str[0] = 'X'`), but the entire string cannot be replaced with `=`. After declaration, `strcpy()` must be used to assign a whole string.

### 1.4 Processing Strings with the Null Character

The end of a string is marked not by a length but by the null character, so a loop that processes a string proceeds until it meets `'\0'` rather than counting elements. The following code counts the length directly and converts lowercase letters to uppercase while counting the characters that were uppercase originally.

```c
char s[20] = "Hello, C";
int n = 0, i, upper = 0;

while (s[n] != '\0')                    // until the null character
    n++;
printf("length = %d\n", n);

for (i = 0; s[i] != '\0'; i++) {
    if (s[i] >= 'a' && s[i] <= 'z')
        s[i] = s[i] - 'a' + 'A';        // lowercase to uppercase
    else if (s[i] >= 'A' && s[i] <= 'Z')
        upper++;
}
printf("%s, originally uppercase = %d\n", s, upper);
```

```text
length = 8
HELLO, C, originally uppercase = 2
```

`"Hello, C"` consists of the 8 characters `H`, `e`, `l`, `l`, `o`, `,`, a space, and `C`, and `s[8]` is `'\0'`, so the first loop stops when `n` is 8. The array size 20 plays no part in deciding where the loop ends. In the second loop, `s[i] - 'a' + 'A'` uses the property that lowercase and uppercase letters differ by the same code in ASCII (Chapter 3, Section 1.3), and the comma and space match neither condition and remain as they are. The original uppercase letters are `H` and `C`, 2 in all. This approach assumes that `'\0'` is present, so if it is used on a character array without `'\0'`, as cautioned in Section 1.2, the loop continues past the array and the behavior is undefined. The standard functions that do the same jobs are `strlen` of Section 2 and `toupper` of Section 3.

---

<br>

## 2. Standard String Functions (`<string.h>`)

All functions below require `#include <string.h>`. String functions let you handle strings simply without knowing the details of the processing.

### 2.1 `strlen`

Returns the **length** of a string, **excluding** the null terminator. A character array or a string literal can be passed.

```c
#include <string.h>

char str[] = "Hello";
size_t len = strlen(str);   // 5
```

**`strlen` vs `sizeof`:**

| Expression | Value | Meaning |
|:-----------|:------|:--------|
| `strlen("Hello")` | `5` | Number of characters before `'\0'` |
| `sizeof("Hello")` | `6` | Total bytes allocated (including `'\0'`) |

*Table 2. Comparison of `strlen` and `sizeof`*

```c
char str[20] = "Hello";
printf("strlen: %zu\n", strlen(str));   // 5  (string length)
printf("sizeof: %zu\n", sizeof(str));   // 20 (array size in bytes)
```

> **Key Point:** `strlen` scans for `'\0'` at run time (O(n)), while `sizeof` is determined at compile time (O(1)). The return type of `strlen` is `size_t` (unsigned integer).

### 2.2 `strcpy` / `strncpy`

**`strcpy(dest, src)`** copies the entire source string (including `'\0'`) into the destination and returns `dest`.

```c
char src[] = "Hello";
char dest[20];
strcpy(dest, src);         // dest is now "Hello"
```

**`strncpy(dest, src, n)`** copies at most `n` characters. If `src` is shorter than `n`, the rest is padded with `'\0'`. If `src` is longer, **no `'\0'` is appended**.

```c
char dest[10];
strncpy(dest, "Hello, World!", 9);
dest[9] = '\0';   // always manually null-terminate after strncpy!
```

> **Caution:** `strcpy` performs **no bounds checking**. If `dest` is too small, it stores values beyond the allocated memory and corrupts memory, a **buffer overflow** (buffer overrun), which is one of the most dangerous bugs in C. Always ensure `dest` is large enough.

> **Note:** **Safe string functions in Visual Studio.** In the default project settings of Visual Studio 2019 and later, using a function with a buffer overrun risk such as `strcpy` turns the security warning (C4996) into an error, so the code does not compile. Instead, use `errno_t strcpy_s(char *dest, rsize_t destsz, const char *src);`, which also takes the size of the destination array, or turn off the warning by defining `#define _CRT_SECURE_NO_WARNINGS` **before** the statements that include the library headers. `strcat` has a counterpart of the same form, `strcat_s(dest, destsz, src)`. These functions belong to Annex K, which is optional in the C11 standard, so the standard libraries used by gcc and clang do not provide them.

### 2.3 `strcmp` / `strncmp`

**`strcmp(s1, s2)`** compares two strings character by character using character codes (ASCII values). That is, it compares the two strings in lexicographic (dictionary) order and returns a negative value if `s1` comes first, a positive value if it comes later, and 0 if they are equal.

| Return Value | Meaning |
|:-------------|:--------|
| `0` | Strings are equal |
| `> 0` | First differing char in `s1` is greater than in `s2` |
| `< 0` | First differing char in `s1` is less than in `s2` |

*Table 3. Return values of `strcmp`*

```c
strcmp("abc", "abc");   // returns 0  (equal)
strcmp("abd", "abc");   // returns > 0  ('d' > 'c')
strcmp("abc", "abd");   // returns < 0  ('c' < 'd')
strcmp("abc", "abcd");  // returns < 0  ('\0' < 'd')
```

The standard specifies only the sign of the return value, so a nonzero return value is not necessarily -1 or 1. Judge the result by its sign, as in `strcmp(...) < 0`.

**`strncmp(s1, s2, n)`** compares only the first `n` characters.

```c
strncmp("Hello", "Help", 3);   // returns 0  (first 3 chars are equal)
strncmp("Hello", "Help", 4);   // returns < 0  ('l' < 'p')
```

> **Caution:** Never use `==` to compare strings. `s1 == s2` compares **pointer addresses**, not string contents. Always use `strcmp`.

### 2.4 `strcat` / `strncat`

**`strcat(dest, src)`** copies `src` to the end of the string stored in `dest`, appending it.

```c
char dest[20] = "Hello";
strcat(dest, ", ");       // "Hello, "
strcat(dest, "World!");   // "Hello, World!"
```

**`strncat(dest, src, n)`** appends at most `n` characters from `src`, then adds `'\0'`.

```c
char dest[20] = "Hello";
strncat(dest, ", World!!!!!", 7);  // "Hello, World" (appends 7 chars + '\0')
```

> **Caution:** `dest` must have **enough space** for the existing string + appended string + `'\0'`. `strcat` performs no bounds checking, so there is a risk of buffer overrun.

### 2.5 `strchr` / `strstr`

**`strchr(str, ch)`** finds the **first occurrence** of character `ch` in `str`. Returns a pointer to the found character, or `NULL` if not found.

```c
char str[] = "Hello, World!";
char *p = strchr(str, 'o');
if (p != NULL) {
    printf("Found 'o' at index %ld\n", p - str);   // 4
    printf("From 'o' onward: %s\n", p);             // o, World!
}
```

**`strstr(str, substr)`** finds the **first occurrence** of substring `substr` in `str`. Returns a pointer to the beginning of the match, or `NULL`. For example, it can find `".txt"` in a file name to decide whether the file is a text file.

```c
char str[] = "Hello, World!";
char *p = strstr(str, "World");
if (p != NULL) {
    printf("Found at index %ld\n", p - str);   // 7
    printf("Substring: %s\n", p);               // World!
}
```

### 2.6 `strtok`

**`strtok(str, delim)`** splits a string into **tokens** using the delimiter characters in `delim`. A token is the smallest unit of a sentence that cannot be divided further, and every character written in `delim` is a delimiter.

- **First call:** pass the string to tokenize.
- **Subsequent calls:** pass `NULL` to continue tokenizing the same string.
- **Modifies** the original string by replacing delimiters with `'\0'`. It returns the address of the token, or `NULL` when there are no more tokens.

```c
char str[] = "Alice,Bob,Charlie,David";
char *token = strtok(str, ",");

while (token != NULL) {
    printf("%s\n", token);
    token = strtok(NULL, ",");
}
// Output:
// Alice
// Bob
// Charlie
// David
```

> **Caution:** `strtok` modifies the original string. If you need to preserve it, make a copy first with `strcpy`. For the same reason, a string literal, which cannot be modified, must not be passed to `strtok`.

### 2.7 Comparing and Swapping Strings

`strcmp(s1, s2)` compares two strings one character at a time from the front, and at the first differing characters it decides the result by comparing their codes. It returns a negative value if `s1` comes first, 0 if they are equal, and a positive value if `s1` comes later; the magnitude of the return value differs between implementations, so only its sign is tested. The following checks the result of each comparison by its sign.

```c
printf("%d\n", strcmp("apple", "apricot") < 0);
printf("%d\n", strcmp("apple", "app") > 0);
printf("%d\n", strcmp("Zebra", "apple") < 0);
printf("%d\n", strcmp("abc", "abc") == 0);
printf("%d\n", strncmp("apple", "apricot", 2) == 0);
```

```text
1
1
1
1
1
```

| Comparison | First Differing Position | Sign of the Result and Reason |
|:-----|:-----|:-----|
| `"apple"` and `"apricot"` | Index 2 (`'p'` and `'r'`) | Negative, `'p'` (112) < `'r'` (114) |
| `"apple"` and `"app"` | Index 3 (`'l'` and `'\0'`) | Positive, the shorter one ends first and `'\0'` (0) is smaller |
| `"Zebra"` and `"apple"` | Index 0 (`'Z'` and `'a'`) | Negative, uppercase `'Z'` (90) < lowercase `'a'` (97) |
| `"abc"` and `"abc"` | None | 0, all characters and the null character are equal |
| `"apple"` and `"apricot"`, first 2 characters only | None | 0, `strncmp` compares only up to n characters |

*Table 4. How `strcmp` compares*

The order of `strcmp` resembles dictionary order, but it follows character codes, so in ASCII every uppercase letter comes before every lowercase letter. To compare while ignoring case, compare copies of the two strings converted with `tolower` of Section 3.

When two strings are swapped, a temporary array is used with three calls to `strcpy`, because an array cannot be assigned with `=` (Section 1.3). The following code swaps two words if they are not in dictionary order.

```c
char a[20] = "banana", b[20] = "apple", temp[20];

if (strcmp(a, b) > 0) {         // if a comes after b
    strcpy(temp, a);
    strcpy(a, b);
    strcpy(b, temp);
}
printf("%s %s\n", a, b);
```

```text
apple banana
```

Since `'b'` is greater than `'a'`, `strcmp(a, b)` is positive, and the three copies exchange the two contents. All three arrays must then be large enough to hold the other string. If the two arrays differ in size, copying the longer string into the shorter array can cause the buffer overrun of Section 2.2.

### 2.8 Implementing String Functions Directly

The behavior of the standard string functions becomes clear when they are implemented directly with only pointers and the null character. The following functions do the same jobs as `strlen`, `strcpy`, and `strcat`.

```c
size_t my_strlen(const char *s)
{
    const char *p = s;

    while (*p != '\0')          // move p up to the null character
        p++;
    return (size_t)(p - s);     // the number of slots moved is the length
}

char *my_strcpy(char *dest, const char *src)
{
    char *d = dest;

    while ((*d++ = *src++) != '\0')     // copy one character at a time, through the null
        ;
    return dest;
}

char *my_strcat(char *dest, const char *src)
{
    my_strcpy(dest + my_strlen(dest), src);     // copy from the position of dest's null
    return dest;
}

int main(void)
{
    char buf[20];

    my_strcpy(buf, "data");
    printf("%s %zu\n", buf, my_strlen(buf));
    my_strcat(buf, "base");
    printf("%s %zu\n", buf, my_strlen(buf));
    return 0;
}
```

```text
data 4
database 8
```

- **`my_strlen`:** It moves `p` until it reaches the null character, then obtains the number of characters as the difference `p - s` of two pointers into the same array (Chapter 8, Section 2.1). For `"data"`, `p` moves 4 slots, and 4 is returned.
- **`my_strcpy`:** The condition `(*d++ = *src++) != '\0'` does three things at once: it assigns `*src` to `*d`, moves both pointers to the next slot, and tests whether the character just assigned is the null character. The loop ends after the null character has also been copied, so the copy always ends with a null character. The loop body is the null statement of Chapter 5, Section 3.7. Copying `"data"` performs 5 assignments: `'d'`, `'a'`, `'t'`, `'a'`, and `'\0'`.
- **`my_strcat`:** `dest + my_strlen(dest)` is the position of the null character of `dest`. Copying `src` from that position overwrites the null character and appends `src`. When `buf` is `"data"`, `"base"` is copied from offset 4, giving `"database"`.

This implementation also shows the same weakness as the standard functions. None of the functions knows the size of `dest`, so if the string to be copied is longer than the array, the buffer overrun of Section 2.2 occurs. This is why functions that also take the size should be used.

---

<br>

## 3. Character Functions (`<ctype.h>`)

All functions below require `#include <ctype.h>`. They take an `int` (character) and return non-zero for true, 0 for false.

### 3.1 Classification

| Function | Returns True If |
|:---------|:----------------|
| `isalpha(c)` | `c` is a letter (`A-Z`, `a-z`) |
| `isdigit(c)` | `c` is a digit (`0-9`) |
| `isalnum(c)` | `c` is a letter or digit |
| `isupper(c)` | `c` is an uppercase letter (`A-Z`) |
| `islower(c)` | `c` is a lowercase letter (`a-z`) |
| `isspace(c)` | `c` is whitespace (space, `\t`, `\n`, etc.) |
| `isxdigit(c)` | `c` is a hexadecimal digit (`0-9`, `A-F`, `a-f`) |

*Table 5. Character classification functions of `<ctype.h>`*

```c
#include <ctype.h>

char c = 'A';
if (isalpha(c))  printf("Letter\n");     // Letter
if (isupper(c))  printf("Uppercase\n");  // Uppercase
if (isdigit(c))  printf("Digit\n");      // (not printed)
```

> **Caution:** The argument of these functions must be a value representable as `unsigned char` or `EOF`. On systems where `char` is signed, non-ASCII bytes such as those of Hangul become negative, so convert them to `unsigned char` before passing them, as in `isspace((unsigned char)str[i])`.

### 3.2 Conversion

| Function | Action |
|:---------|:-------|
| `toupper(c)` | Returns uppercase version of `c` (if `c` is a lowercase letter) |
| `tolower(c)` | Returns lowercase version of `c` (if `c` is an uppercase letter) |

*Table 6. Case conversion functions of `<ctype.h>`*

```c
printf("%c\n", toupper('a'));   // A
printf("%c\n", tolower('Z'));   // z
printf("%c\n", toupper('1'));   // 1 (non-letter unchanged)
```

**Convert entire string to uppercase:**

```c
char str[] = "Hello, World!";
for (int i = 0; str[i] != '\0'; i++) {
    str[i] = toupper(str[i]);
}
printf("%s\n", str);   // HELLO, WORLD!
```

`toupper` and `tolower` return the character unchanged if it is not a letter. Therefore they can be called without first checking whether the character is a letter.

---

<br>

## 4. String I/O

The string I/O functions require `<stdio.h>`.

### 4.1 `scanf` / `printf` with `%s`

**`scanf("%s", str)`** reads characters from the input buffer until **whitespace** (space, tab, newline). No `&` is needed because the array name converts to the starting address of the array.

```c
char name[20];
printf("Enter name: ");
scanf("%s", name);          // reads one word only
printf("Hello, %s!\n", name);
```

**`printf("%s", str)`** prints characters until `'\0'`.

| Input | `scanf("%s", name)` stores |
|:------|:---------------------------|
| `Alice` | `"Alice"` |
| `Alice Bob` | `"Alice"` (stops at space; `"Bob"` remains in buffer) |

*Table 7. Values stored by `scanf("%s", name)` for each input*

> **Caution:** `scanf("%s", ...)` has no length limit by default, so it can overflow the buffer. With a width specifier such as `scanf("%19s", name)`, at most 19 characters are read, leaving room for `'\0'`. When reading a string with Visual Studio's `scanf_s`, pass the array size as well, as in `scanf_s("%s", name, (unsigned)sizeof(name))`; if a string longer than the array is entered, the first element is set to the null character and the result is an empty string.

### 4.2 `fgets` / `gets_s`

To read a line of string that contains spaces, use `fgets` or `gets_s`. **`fgets(str, count, stdin)`** reads up to `count - 1` characters or until a newline, whichever comes first. It **includes the newline** `'\n'` in the stored string.

```c
char line[100];
printf("Enter a line: ");
fgets(line, 100, stdin);
// If user types "Hello World\n", line contains "Hello World\n\0"
```

**Removing the trailing newline:**

```c
char line[100];
fgets(line, 100, stdin);
size_t len = strlen(line);
if (len > 0 && line[len - 1] == '\n') {
    line[len - 1] = '\0';
}
```

**`gets_s(str, count)`** (C11) reads until a newline but **excludes** `'\n'` from the stored string. `gets_s` belongs to Annex K, which is optional in C11, so Visual Studio provides it but the standard libraries used by gcc and clang do not.

```c
char line[100];
gets_s(line, 100);   // reads line without '\n'
```

| Function | Reads Until | Includes `'\n'` | Buffer Overflow Protection |
|:---------|:------------|:-----------------|:---------------------------|
| `scanf("%s", ...)` | Whitespace | No | No (use width specifier) |
| `fgets(str, n, stdin)` | Newline or `n-1` chars | Yes | Yes |
| `gets_s(str, n)` | Newline | No | Yes |

*Table 8. Comparison of string input functions*

`fgets` is used for reading full lines because it is safe and available on all systems. The trailing `'\n'` must be stripped if it is not needed.

When the entered line is longer than the array, `fgets` reads only one character fewer than the array size, appends the null character, and stops; the rest remains in the buffer, and the next `fgets` continues reading it. Reading `programming` twice with a `buf` of size 8, the first call obtains `program` (7 characters) and the second the remaining `ming` and the newline (5 characters). Hence if the string read does not end with `'\n'`, it can be concluded that the line has not been read completely.

### 4.3 `puts`

**`puts(str)`** prints one line of string and **automatically appends a newline**.

```c
char str[] = "Hello, World!";
puts(str);    // prints: Hello, World!\n
// equivalent to: printf("%s\n", str);
```

### 4.4 Common Problems in String Input

Two problems that often arise in string input are explained by the input buffer (Chapter 5, Section 3.8). The following program shows the two problems in turn.

```c
char word[20], rest[40], line[40];
int age = 0;

scanf("%19s", word);
fgets(rest, sizeof(rest), stdin);
printf("word = [%s], rest = [%s]\n", word, rest);

scanf("%d", &age);
fgets(line, sizeof(line), stdin);
printf("age = %d, line = [%s], len = %zu\n", age, line, strlen(line));
```

```text
Kim Minsu
21
Seoul
```

Entering the three lines above prints the following.

```text
word = [Kim], rest = [ Minsu
]
age = 21, line = [
], len = 1
```

First, `%s` stops reading when it meets a whitespace character. From `"Kim Minsu"`, only `Kim` goes into `word`, and `" Minsu\n"`, from the space on, remains in the buffer and is taken by the next `fgets`. To read a whole line containing spaces, use `fgets`, not `scanf("%s")`. Second, because of the `'\n'` that `scanf("%d")` leaves after reading 21, the `fgets` that follows does not wait for the user's input but reads just the newline, producing a string of length 1. `Seoul` is never read.

The second problem is solved by discarding the characters left in the buffer after `scanf`, up to the newline. In the following code, `getchar()` is a function that reads one character from the buffer and returns it, and the loop discards the remaining characters until it reads `'\n'`. Then the `'\n'` at the end of the line read by `fgets` is found with `strcspn` and removed.

```c
scanf("%d", &age);
while ((c = getchar()) != '\n' && c != EOF)     // discard the rest of the line
    ;
fgets(line, sizeof(line), stdin);
line[strcspn(line, "\n")] = '\0';               // remove the '\n' at the end of the line
```

```text
age? 21
address? Seoul Mapo
[21] [Seoul Mapo] len = 10
```

`c` must be declared `int` so that it can distinguish `EOF` (a negative value) returned by `getchar` from every character code. A program that reads integers and strings together also often reads all input line by line with `fgets` from the start and extracts numbers with the `sscanf` of Section 5.

---

<br>

## 5. Data Conversion Functions (`<stdlib.h>`, `<stdio.h>`)

### 5.1 String to Number

These functions are declared in `<stdlib.h>`.

| Function | Converts String To | Example |
|:---------|:-------------------|:--------|
| `atoi(str)` | `int` | `atoi("42")` returns `42` |
| `atof(str)` | `double` | `atof("3.14")` returns `3.14` |
| `atol(str)` | `long` | `atol("1000000")` returns `1000000L` |

*Table 9. Functions that convert strings to numbers*

```c
#include <stdlib.h>

char s1[] = "123";
char s2[] = "3.14";
char s3[] = "99abc";

int n = atoi(s1);       // 123
double d = atof(s2);    // 3.14
int m = atoi(s3);       // 99 (stops at first non-numeric character)
int z = atoi("abc");    // 0  (no valid number found)
```

> **Key Point:** `atoi`, `atof`, and `atol` skip leading whitespace, read as many valid characters as possible, and stop at the first invalid character. If no valid conversion can be performed, they return `0`.

### 5.2 `sscanf` / `sprintf`

**`sscanf(str, format, ...)`** reads formatted data **from a string** (instead of standard input).

```c
char data[] = "Alice 25 3.85";
char name[20];
int age;
double gpa;

sscanf(data, "%s %d %lf", name, &age, &gpa);
printf("Name: %s, Age: %d, GPA: %.2f\n", name, age, gpa);
// Name: Alice, Age: 25, GPA: 3.85
```

**`sprintf(str, format, ...)`** writes formatted data **into a string** (instead of standard output).

```c
char result[50];
int x = 42;
double pi = 3.14159;

sprintf(result, "x = %d, pi = %.2f", x, pi);
printf("%s\n", result);   // x = 42, pi = 3.14
```

`sscanf` and `sprintf` are the string equivalents of `scanf` and `printf` and are useful for parsing and formatting data within strings. They are often used together with line I/O: a line is read with `gets_s` or `fgets` and values are extracted with `sscanf`, or a string is built with `sprintf` and printed with `puts`. `sprintf` also does not check the size of the destination array, so `snprintf` (C99), which takes the size, is safer.

---

<br>

## 6. String Pointers

### 6.1 `char*` String Pointer

A **string pointer** is a pointer of type `char*` and can point to a `char` variable or an element of a `char` array. A `char*` pointer can also point to a string literal stored in **read-only memory**. String literals are kept in an unmodifiable memory area called the text segment (string table), and the value of a string literal in an expression is its address.

```c
char *p = "Hello";   // p points to a string literal
printf("%s\n", p);   // Hello
```

**Memory layout:**

```text
Read-only memory:  [ H ][ e ][ l ][ l ][ o ][ \0 ]
                     ▲
                     │
            p ───────┘
```

*Figure 3. `char*` pointer p pointing to a string literal*

> **Caution:** Modifying a string literal through a pointer is **undefined behavior** and typically causes a crash.

```c
char *p = "Hello";
p[0] = 'h';      // UNDEFINED BEHAVIOR! String literals are read-only.
```

Compare with a `char` array, which creates a **mutable copy**.

```c
char arr[] = "Hello";
arr[0] = 'h';     // OK: arr is a modifiable copy
```

Assigning another string literal to a string pointer changes only what the pointer points to. A `char*` pointer is mainly used to point to a character array, and the contents of the array it points to can then be changed. The reason for using a pointer instead of the array directly is that the string can be processed while the pointer is moved to particular positions in the array.

```c
char str[] = "hello world";
char *p = strchr(str, ' ');   // address of the space character
if (p != NULL) {
    p++;                      // point to the character after the space
    printf("%s\n", p);        // world
}
```

### 6.2 `const char*`

Use `const char*` to explicitly declare that the string should not be modified. This makes intent clear and lets the compiler catch accidental modifications. `const char*` is mainly used to point to string literals, and when it points to a character array, it allows the array contents to be read but not changed.

```c
const char *msg = "Hello";
msg[0] = 'h';    // COMPILE ERROR: cannot modify const data
msg = "World";   // OK: can change what the pointer points to
```

### 6.3 Guidelines

| Use Case | Declaration | Mutable |
|:---------|:------------|:---------|
| Need to modify the string | `char str[] = "Hello";` | Yes |
| Read-only string reference | `const char *str = "Hello";` | No |
| Function parameter (read-only) | `void print(const char *s);` | No |
| Function parameter (modifiable) | `void modify(char *s);` | Yes |

*Table 10. String declarations by use case*

```c
// Mutable string (array: copies the literal)
char greeting[] = "Hello";
greeting[0] = 'h';             // OK

// Immutable reference (pointer: points to literal)
const char *message = "Hello";
// message[0] = 'h';           // compile error
```

As a rule of thumb, `char[]` is used when the string contents must change, and `const char*` when the string is only read or passed around. Strings that are entered by the user or can change are stored in character arrays, and strings that do not change during execution are represented as string literals. A `char*` pointer is used only to point to a modifiable string (a character array), and a `const char*` pointer is used to point to a string literal or to access a character array read-only.

When defining a function that takes a string as a parameter, follow these rules. If the string is an output parameter, use a `char*` parameter and also receive the size of the character array, so that changes to the string inside the function do not exceed the array size. If the string is an input parameter, use a `const char*` parameter; the end of the string can be found by its null character, so there is no need to receive the array size. Inside the function, the pointer can be indexed and handled like a character array.

When calling such a function, a `char*` parameter accepts only character arrays and `char*` pointers as arguments, and the contents of the string may change after the call. A `const char*` parameter accepts character arrays, string literals, `char*` pointers, and `const char*` pointers, and the contents of the string do not change after the call.

### 6.4 Writing Functions That Take String Parameters

Following the guidelines of Section 6.3, a function that only reads a string is written with a `const char*` parameter, and a function that changes a string with a `char*` parameter. The following `count_space` counts spaces, and `reverse` reverses a string in place.

```c
int count_space(const char *s)
{
    int count = 0;

    while (*s != '\0') {        // while the character s points to is not null
        if (*s == ' ')
            count++;
        s++;                    // move to the next character
    }
    return count;
}

void reverse(char *s)
{
    int i = 0, j = 0;
    char t;

    while (s[j] != '\0')        // move j to the position of the null character
        j++;
    j--;                        // position of the last character
    while (i < j) {
        t = s[i];
        s[i] = s[j];
        s[j] = t;
        i++;
        j--;
    }
}

int main(void)
{
    char text[] = "to be or not";

    printf("spaces = %d\n", count_space(text));
    printf("spaces = %d\n", count_space("a b c d"));
    reverse(text);
    printf("%s\n", text);
    return 0;
}
```

```text
spaces = 3
spaces = 3
ton ro eb ot
```

The `s++` in `count_space` only moves the parameter `s`, a copy of the address received as the argument, to the next character, so the caller's array or pointer does not change. Both character arrays and string literals can be passed to a `const char*` parameter. `reverse` exchanges characters while narrowing the end indices `i` and `j` toward the middle; it differs from the array reversal of Chapter 7, Section 5.3 only in finding the end by the position of the null character instead of the element count. For the 12-character `"to be or not"`, it stops after 6 exchanges, when `i` is 6 and `j` is 5.

Passing from a `const` side to a non-`const` side is not allowed. Passing `const char *p` to a `char*` parameter makes Clang issue the warning `passing 'const char *' to parameter of type 'char *' discards qualifiers`. On the other hand, in C the type of a string literal is a `char` array without `const`, so passing a literal to a `char*` parameter, as in `reverse("abc")`, compiles without a warning. However, if the function tries to change the literal, the behavior is undefined as in Section 6.1, and a program that ran `char *p = "abc"; p[0] = 'X';` on arm64 macOS terminated abnormally with a bus error (SIGBUS). A string to be changed must always be passed as a character array. Declaring the parameters of functions that only read strings as `const char *` lets the compiler catch such mistakes.

### 6.5 Storage of `char[]` Versus `char*`

`char arr[] = "hello";` and `const char *ptr = "hello";` seem to handle the same string, but they are placed in memory differently.

```c
char arr[] = "hello";
const char *ptr = "hello";
const char *ptr2 = "hello";

printf("arr: %p, sizeof %zu\n", (void *)arr, sizeof arr);
printf("ptr: %p, sizeof %zu, &ptr %p\n", (void *)ptr, sizeof ptr, (void *)&ptr);
printf("ptr == ptr2: %d, arr == ptr: %d\n", ptr == ptr2, arr == ptr);
arr[0] = 'j';
ptr = "world";
printf("%s %s\n", arr, ptr);
```

```text
arr: 0x16fd1eb04, sizeof 6
ptr: 0x1000e0590, sizeof 8, &ptr 0x16fd1eaf8
ptr == ptr2: 1, arr == ptr: 0
jello world
```

```text
local variable area (0x16f...)             string constant area (0x100...)
┌────────────────────────────┐           ┌────────────────────────────┐
│ arr: h  e  l  l  o  \0     │           │ "hello\0"  @0x1000e0590    │
├────────────────────────────┤           └────────────────────────────┘
│ ptr: 0x1000e0590 ──────────┼─────────────────▲
└────────────────────────────┘
arr: 6-byte array, modifiable              constant: used as read-only
ptr: 8-byte address
```

*Figure 4. Memory areas where a char array and a char pointer are placed*

For `arr`, an array holding 6 characters (including the null character) is created in the local variable area, and the contents of the string constant are copied into that array. That is why `sizeof arr` is 6 and the contents can be changed with `arr[0] = 'j'`. `ptr` is one 8-byte pointer holding the address of `"hello"` in the program's string constant area. In the output, the different address ranges of `arr` (0x16f...) and `ptr` (0x100...) indicate that the two areas differ. That `ptr` and `ptr2` point to the same address is because the compiler merged string constants with the same contents into one; this is behavior the compiler may choose, so it is not relied on. `ptr = "world";` only makes the pointer point to another constant and copies no characters, whereas `arr = "world";` is a compile error because an array cannot be assigned.

The string constant area remains for as long as the program runs, so a function returning the address of a string constant, as in `return "hello";`, is safe, unlike the address of a local variable in Chapter 8, Section 3.5. In contrast, `char arr[] = "hello";` inside a function is a local array, so returning its address creates a dangling pointer.

Two mistakes that confuse character arrays with string constants are reported by Clang as warnings. First, initializing with a string longer than the array, as in `char s[5] = "hello!";`, gives the warning `initializer-string for char array is too long`, and only the first 5 characters go into the array, making a character array without a null character. Second, `if (t == "abc")` compares not the contents of the two strings but the address of the array `t` with the address of the string constant, so Clang issues the warning `result of comparison against a string literal is unspecified (use an explicit string comparison function instead)`. Like `arr == ptr` in Section 6.5, this comparison can be false even when the contents are equal, so content comparison must always use `strcmp(t, "abc") == 0`. Both cases compile, so if the warnings are not read, the problem is noticed only from the results.

---

<br>

## 7. String Arrays

### 7.1 2D `char` Array

To store several strings that are entered or change during execution, use a 2D character array. A 2D character array stores multiple strings with a **fixed column size**; the length of the string including the null character is specified as the column size, and the number of strings as the row size.

```c
char names[3][20] = {
    "Alice",
    "Bob",
    "Charlie"
};
```

**Memory layout (each row is 20 bytes):**

```text
names[0]: [ A ][ l ][ i ][ c ][ e ][ \0 ][ \0 ]...[ \0 ]  (20 bytes)
names[1]: [ B ][ o ][ b ][ \0 ][ \0 ][ \0 ][ \0 ]...[ \0 ]  (20 bytes)
names[2]: [ C ][ h ][ a ][ r ][ l ][ i ][ e ][ \0 ]...[ \0 ]  (20 bytes)
```

*Figure 5. Memory layout of `char names[3][20]`*

Each string is accessed with only the row index, as in `names[i]`, and the `j`-th character of the `i`-th string is accessed with both the row and column indices, as in `names[i][j]`.

```c
// Access and print each name
for (int i = 0; i < 3; i++) {
    printf("%s\n", names[i]);
}

// Modify a name
strcpy(names[1], "Bobby");   // OK: each row is a mutable char array
```

The column size (20) must be large enough for the **longest string + 1**, and every string must fit within this fixed column size. Shorter strings waste the remaining space.

### 7.2 Array of String Pointers

To store several strings that do not change, use an array of string pointers. An array of `char*` pointers stores only the **addresses** of string literals.

```c
const char *names[] = {
    "Alice",
    "Bob",
    "Charlie"
};
```

**Memory layout (pointers to read-only literals):**

```text
names[0] ──► "Alice\0"    (6 bytes in read-only memory)
names[1] ──► "Bob\0"      (4 bytes in read-only memory)
names[2] ──► "Charlie\0"  (8 bytes in read-only memory)
```

*Figure 6. Pointer array names pointing to string literals*

```c
// Access and print
for (int i = 0; i < 3; i++) {
    printf("%s\n", names[i]);
}

// Can change which string a pointer refers to
names[1] = "Bobby";   // OK: changes the pointer, not the string

// CANNOT modify the characters of the string literal
// names[1][0] = 'b';  // UNDEFINED BEHAVIOR: literals are read-only
```

**2D Array vs Array of Pointers:**

| Feature | `char names[3][20]` | `const char *names[3]` |
|:--------|:---------------------|:-----------------------|
| Memory | Fixed 60 bytes (3 x 20) | Pointers + literal storage (no waste) |
| Modifiable strings | Yes (`strcpy`, `names[i][j] = ...`) | No (literals are read-only) |
| Reassign to different string | No (array name is constant) | Yes (`names[i] = "New"`) |
| Wasted space | Yes (padding with `'\0'`) | No |
| Typical use | Mutable string table | Read-only lookup table |

*Table 11. Comparison of a 2D character array and an array of string pointers*

If strings must be both **read and modified**, a 2D `char` array is used. If only a **read-only list** of string constants is needed, an array of `const char*` pointers is more efficient.

### 7.3 Memory Comparison of the Two Kinds of String Arrays

Storing the same four strings in the two-dimensional character array of Section 7.1 and the array of string pointers of Section 7.2 and measuring their sizes gives the following.

```c
char a[4][20] = { "avengers", "iron man", "thor", "captain america" };
const char *p[4] = { "avengers", "iron man", "thor", "captain america" };
size_t lit = sizeof("avengers") + sizeof("iron man") + sizeof("thor") + sizeof("captain america");

printf("2D array: %zu bytes, row %zu\n", sizeof a, sizeof a[0]);
printf("pointer array: %zu bytes + literals %zu bytes\n", sizeof p, lit);
printf("%p %p\n", (void *)a[0], (void *)a[1]);
a[2][0] = 'T';
printf("%s %s\n", a[2], p[2]);
```

```text
2D array: 80 bytes, row 20
pointer array: 32 bytes + literals 39 bytes
0x16f4eaab8 0x16f4eaacc
Thor thor
```

```text
a (4 rows, 20 columns, 80 bytes)     p (4 pointers, 32 bytes)
a[0] avengers\0.......... (20)       p[0] ──► "avengers\0"         (9)
a[1] iron man\0.......... (20)       p[1] ──► "iron man\0"         (9)
a[2] thor\0.............. (20)       p[2] ──► "thor\0"             (5)
a[3] captain america\0... (20)       p[3] ──► "captain america\0"  (16)
```

*Figure 7. Memory of a 2D character array and an array of string pointers*

In the two-dimensional array, every row is 20 bytes, sized for the longest string, so 15 bytes are empty in the short `"thor"` row (the `.` in the figure). The address difference between `a[0]` and `a[1]` is 0xacc - 0xab8 = 0x14 = 20, the size of one row. The pointer array is smaller: 32 bytes for 4 pointers plus 39 bytes for the actual length + 1 of each string constant, 71 bytes in all. In exchange, the two-dimensional array gives each row its own character array, so contents can be changed, as in `a[2][0] = 'T'`, while the string constants pointed to by a `const char *` array cannot be changed. Use a two-dimensional character array when strings are read in or modified, and an array of string pointers when they are only read, as with a fixed list of names.

---

<br>

## Concept Applications

**True/False Check:**

| Statement | Judgment and Reason |
|:-----|:-----|
| A `char` array of size 3 is enough to store `"abc"`. | **F.** 4 bytes are needed, including the null character. |
| `strlen` returns the length including the null character. | **F.** `strlen` returns the number of characters before the null character. |
| After declaring `char s[10];`, a string can be assigned with `s = "hi";`. | **F.** Arrays cannot be assigned, so `strcpy(s, "hi");` is used. |
| If `strcmp` returns 0, the two strings have the same contents. | **T.** It is 0 if equal, and negative or positive by the first differing character otherwise. |
| In ASCII, `strcmp("Zoo", "apple")` is negative. | **T.** The uppercase `'Z'` (90) is less than the lowercase `'a'` (97). |
| `strncpy(dest, src, n)` always produces a null-terminated string. | **F.** If `src` has n or more characters, no null character is appended, so it must be added manually. |
| Executing `p[0] = 'X';` through a `char *p` pointing to a string literal is undefined behavior. | **T.** A literal may reside in unmodifiable memory, and the program may terminate abnormally depending on the environment. |
| `fgets` also stores the newline character of the line it reads, if there is room. | **T.** So when the newline is not wanted, it is found with `strcspn` or a similar method and replaced with a null character. |
| `sizeof` gives the same value for `char arr[] = "hello";` and `const char *p = "hello";`. | **F.** `sizeof arr` is 6, the whole array, and `sizeof p` is 8 (64-bit), the size of a pointer. |
| `scanf("%s", s)` can read a whole line containing spaces. | **F.** `%s` stops at whitespace, so a whole line is read with `fgets`. |
| `if (s == "abc")` tests whether the contents of `s` are `"abc"`. | **F.** It compares two addresses, so content comparison uses `strcmp`. |
| In a two-dimensional character array, every row occupies the same size. | **T.** Even a row with a short string is allocated memory of the declared column size. |

---

<br>

## Summary

| Concept | Key Summary |
|:--------|:------------|
| Character vs String | `'A'` takes 1 byte when stored in a `char`, while `"A"` takes 2 bytes (`'A'` and `'\0'`), and strings are null-terminated. |
| `char` Array Init | `char s[10] = "abc"` pads the rest with `'\0'`, and `char s[] = "abc"` sets the size to 4 automatically. |
| Array Assignment | `str = "xyz"` is not allowed after declaration, so `strcpy()` is used instead. |
| `strlen` | It returns the length excluding `'\0'` as a `size_t` and differs from `sizeof`, which gives the array size. |
| `strcpy` / `strncpy` | They copy strings, and `strcpy` performs no bounds check, so it risks buffer overflow. |
| `strcmp` / `strncmp` | They return 0 if equal, a positive value if `s1` comes later in dictionary order, and a negative value if it comes first; strings must not be compared with `==`. |
| `strcat` / `strncat` | They append strings, and the destination array must have enough space. |
| `strchr` / `strstr` | They search for a character or substring and return a pointer to the found position or `NULL`. |
| `strtok` | It splits a string by delimiter characters, modifies the original, and takes `NULL` after the first call. |
| `isalpha`, `isdigit`, ... | They are the classification functions of `<ctype.h>` and return non-zero for true. |
| `toupper` / `tolower` | They convert character case and return non-letters unchanged. |
| `scanf("%s", ...)` | It reads one word, stopping at whitespace, and needs no `&` for arrays. |
| `fgets` | It reads a full line including `'\n'` and is safe because of its size limit. |
| `puts` | It prints a string and appends a newline automatically. |
| `atoi` / `atof` / `atol` | They convert a string to `int`, `double`, and `long`, respectively. |
| `sscanf` / `sprintf` | They read from or write to strings using format specifiers. |
| `char*` Pointer | It can point to a string literal (read-only memory) whose contents must not be modified, and it is mainly used to point to character arrays. |
| `const char*` | It marks a string as read-only explicitly and prevents accidental modification. |
| 2D `char` Array | Its rows have a fixed size and are mutable, but short strings waste space. |
| Array of `char*` | It is flexible with no wasted space, but the strings are read-only if the pointers point to literals. |
| Processing with the null character | String loops run while `s[i] != '\0'`, and the null character, not the array size, decides the end. |
| Comparison by `strcmp` | The sign is set by the codes of the first differing characters; a shorter string comes first because of `'\0'`, and in ASCII uppercase precedes lowercase. |
| Swapping strings | Arrays cannot be assigned with `=`, so strings are swapped with a temporary array and three `strcpy` calls, and all three arrays must be large enough. |
| String parameters | A string only read is received as `const char*` and one changed as `char*`, and moving the pointer inside the function does not change the caller. |
| Implementing string functions | `strlen` counts slots up to the null, `strcpy` copies through the null, and `strcat` copies from the null's position, and none of them knows the destination size. |
| Problems in string input | `%s` stops at whitespace, and the `'\n'` left after `scanf` is read by the next `fgets`, so the rest of the line is discarded before reading. |
| `char[]` versus `char*` | An array makes a modifiable copy in the local area, while a pointer holds only an address in the string constant area. |
| Memory of the two string arrays | A 2D character array gives every row the same size and can be modified, while a pointer array, made of pointers and constants of actual length, is smaller but cannot change its contents. |

---

<br>

## Self-Check Questions

1. **Array size and length:** For `char s[10] = "abc";` and `char t[] = "abc";`, find the values of `strlen(s)`, `sizeof(s)`, and `sizeof(t)`.

   <details>
   <summary>Answer</summary>

   `strlen(s)` is the number of characters before the null character, so it is 3, and `sizeof(s)` is the declared array size, 10. Because the size of `t` is omitted, `t` becomes a 4-byte array (string length + 1), so `sizeof(t)` is 4.

   </details>

2. **String comparison:** Find the sign of the value returned by `strcmp("apple", "apricot")` and explain why.

   <details>
   <summary>Answer</summary>

   It is negative. The two strings share the first two characters `a` and `p`, and they first differ at the third character, `'p'` (112) versus `'r'` (114). Since `'p'` is less than `'r'`, `"apple"` comes first in dictionary order. The standard specifies only the sign, so the value cannot be assumed to be -1.

   </details>

3. **Newline from `fgets`:** For `char line[10];`, `Hi` is entered with `fgets(line, 10, stdin)` and Enter is pressed. What is `strlen(line)`, and how is the newline removed?

   <details>
   <summary>Answer</summary>

   `line` holds `"Hi\n"`, so `strlen(line)` is 3, because `fgets` stores the newline as well. Compute the length with `size_t len = strlen(line);`, and if `len > 0` and `line[len - 1] == '\n'`, remove it with `line[len - 1] = '\0';`. `line[strcspn(line, "\n")] = '\0';` does the same.

   </details>

4. **Pointer vs array:** Explain the difference between `char *p = "Hello"; p[0] = 'h';` and `char a[] = "Hello"; a[0] = 'h';`.

   <details>
   <summary>Answer</summary>

   `p` points to a string literal in read-only memory, so `p[0] = 'h'` is undefined behavior and usually terminates the program abnormally at run time. `a` is a modifiable character array that holds a copy of the literal's contents, so `a[0] = 'h'` works and `a` becomes `"hello"`. Declaring the pointer as `const char *p` when it points to a literal prevents this mistake at compile time.

   </details>

5. **`strtok` and the original:** If `strtok(d, "-")` and then `strtok(NULL, "-")` are called repeatedly on `char d[] = "2024-05-28";`, which tokens are returned, and what does `printf("%s", d)` print after all tokens are obtained?

   <details>
   <summary>Answer</summary>

   The tokens are returned in the order `"2024"`, `"05"`, and `"28"`, and the next call returns `NULL`. Because `strtok` replaces the delimiter `'-'` with `'\0'`, the first string in `d` ends at `"2024"`, and `printf("%s", d)` prints `2024`.

   </details>

6. **Sign of `strcmp`:** Write the sign of each of `strcmp("cat", "car")`, `strcmp("car", "cart")`, and `strcmp("Car", "car")`, and explain why.

   <details>
   <summary>Answer</summary>

   The first is positive because at index 2, `'t'` (116) > `'r'` (114). The second is negative because `"car"` ends first, and at index 3, `'\0'` (0) < `'t'` (116). The third is negative because at index 0, `'C'` (67) < `'c'` (99).

   </details>

7. **Null-character loop:** For `char w[10] = "level";`, how many times does the body of `for (i = 0; w[i] != '\0'; i++)` run? Describe how this loop can be used to decide whether `w` reads the same forward and backward (a palindrome).

   <details>
   <summary>Answer</summary>

   `"level"` has 5 characters, so the body runs 5 times, and `i` is 5 after the loop. After obtaining the length n with this loop, move `k` from 0 to n / 2 - 1 and compare `w[k]` with `w[n - 1 - k]`; if all pairs are equal, it is a palindrome. `"level"` is a palindrome because (`l`, `l`) and (`e`, `e`) are equal.

   </details>

8. **String parameters:** `void shout(char *s)` changes every lowercase letter of a string to uppercase. Explain the difference between `shout(name)` (with `char name[] = "kim";`) and `shout("kim")`.

   <details>
   <summary>Answer</summary>

   `name` is a character array, so the function can change its elements, and after the call `name` is `"KIM"`. `"kim"` is a string literal, so in C it compiles without a warning, but if the function tries to change its contents, the behavior is undefined, and the program usually terminates abnormally.

   </details>
