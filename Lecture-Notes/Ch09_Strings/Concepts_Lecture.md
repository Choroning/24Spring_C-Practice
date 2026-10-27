# Chapter 9 — Strings

[Repository Guide](../../README.md) | [English](Concepts_Lecture.md) | [한국어](Concepts_Lecture.ko.md)

> **Last Updated:** 2026-10-27
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
- [2. Standard String Functions (`<string.h>`)](#2-standard-string-functions-stringh)
  - [2.1 `strlen`](#21-strlen)
  - [2.2 `strcpy` / `strncpy`](#22-strcpy--strncpy)
  - [2.3 `strcmp` / `strncmp`](#23-strcmp--strncmp)
  - [2.4 `strcat` / `strncat`](#24-strcat--strncat)
  - [2.5 `strchr` / `strstr`](#25-strchr--strstr)
  - [2.6 `strtok`](#26-strtok)
- [3. Character Functions (`<ctype.h>`)](#3-character-functions-ctypeh)
  - [3.1 Classification](#31-classification)
  - [3.2 Conversion](#32-conversion)
- [4. String I/O](#4-string-io)
  - [4.1 `scanf` / `printf` with `%s`](#41-scanf--printf-with-s)
  - [4.2 `fgets` / `gets_s`](#42-fgets--gets_s)
  - [4.3 `puts`](#43-puts)
- [5. Data Conversion Functions (`<stdlib.h>`, `<stdio.h>`)](#5-data-conversion-functions-stdlibh-stdioh)
  - [5.1 String to Number](#51-string-to-number)
  - [5.2 `sscanf` / `sprintf`](#52-sscanf--sprintf)
- [6. String Pointers](#6-string-pointers)
  - [6.1 `char*` String Pointer](#61-char-string-pointer)
  - [6.2 `const char*`](#62-const-char)
  - [6.3 Guidelines](#63-guidelines)
- [7. String Arrays](#7-string-arrays)
  - [7.1 2D `char` Array](#71-2d-char-array)
  - [7.2 Array of String Pointers](#72-array-of-string-pointers)
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

> **Note:** **Tip.** You can modify individual characters (`str[0] = 'X'`), but you cannot replace the entire string with `=`. Always use `strcpy()` for whole-string assignment after declaration.

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

> **Caution:** Never use `==` to compare strings! `s1 == s2` compares **pointer addresses**, not string contents. Always use `strcmp`.

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

> **Caution:** `strtok` modifies the original string! If you need to preserve it, make a copy first with `strcpy`. For the same reason, a string literal, which cannot be modified, must not be passed to `strtok`.

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

*Table 4. Character classification functions of `<ctype.h>`*

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

*Table 5. Case conversion functions of `<ctype.h>`*

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

> **Note:** **Tip.** `toupper` and `tolower` return the character unchanged if it is not a letter. Therefore they can be called without first checking whether the character is a letter.

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

*Table 6. Values stored by `scanf("%s", name)` for each input*

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

*Table 7. Comparison of string input functions*

> **Note:** **Tip.** Use `fgets` for reading full lines. It is safe and available on all systems. Strip the trailing `'\n'` if it is not needed.

### 4.3 `puts`

**`puts(str)`** prints one line of string and **automatically appends a newline**.

```c
char str[] = "Hello, World!";
puts(str);    // prints: Hello, World!\n
// equivalent to: printf("%s\n", str);
```

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

*Table 8. Functions that convert strings to numbers*

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

> **Note:** **Tip.** `sscanf` and `sprintf` are the string equivalents of `scanf` and `printf` and are useful for parsing and formatting data within strings. They are often used together with line I/O: a line is read with `gets_s` or `fgets` and values are extracted with `sscanf`, or a string is built with `sprintf` and printed with `puts`. `sprintf` also does not check the size of the destination array, so `snprintf` (C99), which takes the size, is safer.

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

| Use Case | Declaration | Mutable? |
|:---------|:------------|:---------|
| Need to modify the string | `char str[] = "Hello";` | Yes |
| Read-only string reference | `const char *str = "Hello";` | No |
| Function parameter (read-only) | `void print(const char *s);` | No |
| Function parameter (modifiable) | `void modify(char *s);` | Yes |

*Table 9. String declarations by use case*

```c
// Mutable string (array: copies the literal)
char greeting[] = "Hello";
greeting[0] = 'h';             // OK

// Immutable reference (pointer: points to literal)
const char *message = "Hello";
// message[0] = 'h';           // compile error
```

> **Note:** **Tip.** As a rule of thumb, use `char[]` when you need to change the string contents, and `const char*` when you only need to read or pass the string around. Store strings that are entered by the user or can change in character arrays, and represent strings that do not change during execution as string literals. Use a `char*` pointer only to point to a modifiable string (a character array), and use a `const char*` pointer to point to a string literal or to access a character array read-only.

When defining a function that takes a string as a parameter, follow these rules. If the string is an output parameter, use a `char*` parameter and also receive the size of the character array, so that changes to the string inside the function do not exceed the array size. If the string is an input parameter, use a `const char*` parameter; the end of the string can be found by its null character, so there is no need to receive the array size. Inside the function, the pointer can be indexed and handled like a character array.

When calling such a function, a `char*` parameter accepts only character arrays and `char*` pointers as arguments, and the contents of the string may change after the call. A `const char*` parameter accepts character arrays, string literals, `char*` pointers, and `const char*` pointers, and the contents of the string do not change after the call.

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

*Figure 4. Memory layout of `char names[3][20]`*

Each string is accessed with only the row index, as in `names[i]`, and the `j`-th character of the `i`-th string is accessed with both the row and column indices, as in `names[i][j]`.

```c
// Access and print each name
for (int i = 0; i < 3; i++) {
    printf("%s\n", names[i]);
}

// Modify a name
strcpy(names[1], "Bobby");   // OK: each row is a mutable char array
```

> **Key Point:** The column size (20) must be large enough for the **longest string + 1**. Shorter strings waste the remaining space. Every string must fit within the fixed column size.

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

*Figure 5. Pointer array names pointing to string literals*

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

*Table 10. Comparison of a 2D character array and an array of string pointers*

> **Note:** **Tip.** If you need to both **read and modify** strings, use a 2D `char` array. If you only need a **read-only list** of string constants, use an array of `const char*` pointers for efficiency.

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
