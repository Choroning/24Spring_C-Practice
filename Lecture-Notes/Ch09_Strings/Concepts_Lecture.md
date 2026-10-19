# Chapter 09 — Strings

> **Last Updated:** 2026-03-16

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

---

<br>

## 1. Character Arrays

### 1.1 Characters vs Strings

In C, a **character** and a **string** are fundamentally different.

| Item | Example | Size | Stored As |
|:-----|:--------|:-----|:----------|
| Character literal | `'A'` | 1 byte (treated as `int` in expressions) | ASCII value `65` |
| String literal | `"A"` | 2 bytes | `'A'` + `'\0'` |

A **string** in C is a **null-terminated character array** — a sequence of `char` values ending with the special character `'\0'` (ASCII 0).

```
Character:  'A'      →  [ 65 ]                           (1 byte)
String:     "A"      →  [ 65 ][ 0 ]                      (2 bytes)
String:     "Hello"  →  [ H ][ e ][ l ][ l ][ o ][ \0 ]  (6 bytes)
```

**String constant vs string variable:**

- A **string constant** (literal) like `"Hello"` is stored in **read-only memory** by the compiler. You cannot modify it.
- A **string variable** is a `char` array that holds a copy of the string. You can modify its contents.

> **Key Point:** The null terminator `'\0'` is what tells all string functions where the string ends. Without it, functions like `printf("%s", ...)` will read past the array boundary — **undefined behavior**.

### 1.2 Declaration and Initialization

A character array must be large enough to hold the string **plus one extra byte** for `'\0'`.

```c
// Explicit size — remaining positions filled with '\0'
char str1[10] = "abc";    // stores: 'a','b','c','\0','\0',...,'\0' (size 10)

// Auto-sized — compiler determines size from initializer
char str2[] = "abc";      // stores: 'a','b','c','\0' (size 4)

// Initialized with character list (must include '\0' manually)
char str3[] = {'a', 'b', 'c', '\0'};  // same as str2

// Initialized with character list WITHOUT '\0' — NOT a valid string!
char str4[] = {'a', 'b', 'c'};        // size 3, no null terminator
```

**Memory layout of `char str[10] = "abc";`:**

```
Index:   [0]  [1]  [2]   [3]  [4]  [5]  [6]  [7]  [8]  [9]
Value:   'a'  'b'  'c'  '\0' '\0' '\0' '\0' '\0' '\0' '\0'
```

> **Warning:** If the string length equals or exceeds the array size, no `'\0'` is stored. This creates a char array that is **not** a valid string and will cause bugs with all string functions.

```c
char danger[3] = "abc";  // stores: 'a','b','c' — NO '\0'!
printf("%s", danger);     // undefined behavior: reads past array boundary
```

### 1.3 Usage

**Accessing individual characters:**

```c
char str[] = "Hello";
printf("%c\n", str[0]);   // H
printf("%c\n", str[4]);   // o
str[0] = 'h';             // OK: modify individual character
printf("%s\n", str);      // hello
```

**Printing strings:**

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

The array name `str` acts as a **constant pointer** to the first element. You cannot change where it points. Use `strcpy()` instead:

```c
char str[10];
strcpy(str, "Hello");  // correct way to copy a string into an array
```

> **Tip:** You can modify individual characters (`str[0] = 'X'`), but you cannot replace the entire string with `=`. Always use `strcpy()` for whole-string assignment after declaration.

---

<br>

## 2. Standard String Functions (`<string.h>`)

All functions below require `#include <string.h>`.

### 2.1 `strlen`

Returns the **length** of a string, **excluding** the null terminator.

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

```c
char str[20] = "Hello";
printf("strlen: %zu\n", strlen(str));   // 5  (string length)
printf("sizeof: %zu\n", sizeof(str));   // 20 (array size in bytes)
```

> **Key Point:** `strlen` scans for `'\0'` at runtime (O(n)), while `sizeof` is determined at compile time (O(1)). The return type of `strlen` is `size_t` (unsigned integer).

### 2.2 `strcpy` / `strncpy`

**`strcpy(dest, src)`** copies the entire source string (including `'\0'`) into the destination.

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

> **Warning:** `strcpy` performs **no bounds checking**. If `dest` is too small, it causes a **buffer overflow** — one of the most dangerous bugs in C. Always ensure `dest` is large enough.

### 2.3 `strcmp` / `strncmp`

**`strcmp(s1, s2)`** compares two strings character by character using ASCII values.

| Return Value | Meaning |
|:-------------|:--------|
| `0` | Strings are equal |
| `> 0` | First differing char in `s1` is greater than in `s2` |
| `< 0` | First differing char in `s1` is less than in `s2` |

```c
strcmp("abc", "abc");   // returns 0  (equal)
strcmp("abd", "abc");   // returns > 0  ('d' > 'c')
strcmp("abc", "abd");   // returns < 0  ('c' < 'd')
strcmp("abc", "abcd");  // returns < 0  ('\0' < 'd')
```

**`strncmp(s1, s2, n)`** compares only the first `n` characters:

```c
strncmp("Hello", "Help", 3);   // returns 0  (first 3 chars are equal)
strncmp("Hello", "Help", 4);   // returns < 0  ('l' < 'p')
```

> **Warning:** Never use `==` to compare strings! `s1 == s2` compares **pointer addresses**, not string contents. Always use `strcmp`.

### 2.4 `strcat` / `strncat`

**`strcat(dest, src)`** appends `src` to the end of `dest`.

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

> **Warning:** `dest` must have **enough space** for the existing string + appended string + `'\0'`. No bounds checking is performed by `strcat`.

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

**`strstr(str, substr)`** finds the **first occurrence** of substring `substr` in `str`. Returns a pointer to the beginning of the match, or `NULL`.

```c
char str[] = "Hello, World!";
char *p = strstr(str, "World");
if (p != NULL) {
    printf("Found at index %ld\n", p - str);   // 7
    printf("Substring: %s\n", p);               // World!
}
```

### 2.6 `strtok`

**`strtok(str, delim)`** splits a string into **tokens** using the specified delimiter characters.

- **First call:** pass the string to tokenize.
- **Subsequent calls:** pass `NULL` to continue tokenizing the same string.
- **Modifies** the original string by replacing delimiters with `'\0'`.

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

> **Warning:** `strtok` modifies the original string! If you need to preserve it, make a copy first with `strcpy`.

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

```c
#include <ctype.h>

char c = 'A';
if (isalpha(c))  printf("Letter\n");     // Letter
if (isupper(c))  printf("Uppercase\n");  // Uppercase
if (isdigit(c))  printf("Digit\n");      // (not printed)
```

### 3.2 Conversion

| Function | Action |
|:---------|:-------|
| `toupper(c)` | Returns uppercase version of `c` (if `c` is a lowercase letter) |
| `tolower(c)` | Returns lowercase version of `c` (if `c` is an uppercase letter) |

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

> **Tip:** `toupper` and `tolower` return the character unchanged if it is not a letter. They are safe to call on any character.

---

<br>

## 4. String I/O

### 4.1 `scanf` / `printf` with `%s`

**`scanf("%s", str)`** reads characters until **whitespace** (space, tab, newline). No `&` is needed because the array name is already a pointer.

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

> **Warning:** `scanf("%s", ...)` has no length limit by default — it can overflow the buffer. Use a width specifier: `scanf("%19s", name)` to read at most 19 characters (leaving room for `'\0'`).

### 4.2 `fgets` / `gets_s`

**`fgets(str, count, stdin)`** reads up to `count - 1` characters or until a newline, whichever comes first. It **includes the newline** `'\n'` in the stored string.

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

**`gets_s(str, count)`** (C11) reads until a newline but **excludes** `'\n'` from the stored string.

```c
char line[100];
gets_s(line, 100);   // reads line without '\n'
```

| Function | Reads Until | Includes `'\n'` | Buffer Overflow Protection |
|:---------|:------------|:-----------------|:---------------------------|
| `scanf("%s", ...)` | Whitespace | No | No (use width specifier) |
| `fgets(str, n, stdin)` | Newline or `n-1` chars | Yes | Yes |
| `gets_s(str, n)` | Newline | No | Yes |

> **Tip:** Prefer `fgets` for reading full lines. It is safe and available on all systems. Remember to strip the trailing `'\n'` if you don't want it.

### 4.3 `puts`

**`puts(str)`** prints the string and **automatically appends a newline**.

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

> **Tip:** `sscanf` and `sprintf` are the string equivalents of `scanf` and `printf`. They are very useful for parsing and formatting data within strings.

---

<br>

## 6. String Pointers

### 6.1 `char*` String Pointer

A `char*` pointer can point to a string literal stored in **read-only memory**.

```c
char *p = "Hello";   // p points to a string literal
printf("%s\n", p);   // Hello
```

**Memory layout:**

```
Read-only memory:  [ H ][ e ][ l ][ l ][ o ][ \0 ]
                     ▲
                     │
            p ───────┘
```

> **Warning:** Modifying a string literal through a pointer is **undefined behavior** and typically causes a crash:

```c
char *p = "Hello";
p[0] = 'h';      // UNDEFINED BEHAVIOR! String literals are read-only.
```

Compare with a `char` array, which creates a **mutable copy**:

```c
char arr[] = "Hello";
arr[0] = 'h';     // OK: arr is a modifiable copy
```

### 6.2 `const char*`

Use `const char*` to explicitly declare that the string should not be modified. This makes intent clear and lets the compiler catch accidental modifications.

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

```c
// Mutable string (array — copies the literal)
char greeting[] = "Hello";
greeting[0] = 'h';             // OK

// Immutable reference (pointer — points to literal)
const char *message = "Hello";
// message[0] = 'h';           // compile error
```

> **Tip:** As a rule of thumb, use `char[]` when you need to change the string contents, and `const char*` when you only need to read or pass the string around.

---

<br>

## 7. String Arrays

### 7.1 2D `char` Array

A 2D character array stores multiple strings with a **fixed column size**.

```c
char names[3][20] = {
    "Alice",
    "Bob",
    "Charlie"
};
```

**Memory layout (each row is 20 bytes):**

```
names[0]: [ A ][ l ][ i ][ c ][ e ][ \0 ][ \0 ]...[ \0 ]  (20 bytes)
names[1]: [ B ][ o ][ b ][ \0 ][ \0 ][ \0 ][ \0 ]...[ \0 ]  (20 bytes)
names[2]: [ C ][ h ][ a ][ r ][ l ][ i ][ e ][ \0 ]...[ \0 ]  (20 bytes)
```

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

An array of `char*` pointers stores the **addresses** of string literals.

```c
const char *names[] = {
    "Alice",
    "Bob",
    "Charlie"
};
```

**Memory layout (pointers to read-only literals):**

```
names[0] ──► "Alice\0"    (6 bytes in read-only memory)
names[1] ──► "Bob\0"      (4 bytes in read-only memory)
names[2] ──► "Charlie\0"  (8 bytes in read-only memory)
```

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

> **Tip:** If you need to both **read and modify** strings, use a 2D `char` array. If you only need a **read-only list** of string constants, use an array of `const char*` pointers for efficiency.

---

<br>

## Summary

| Concept | Key Takeaway |
|:--------|:-------------|
| Character vs String | `'A'` is 1 byte; `"A"` is 2 bytes (`'A'` + `'\0'`). Strings are null-terminated. |
| `char` Array Init | `char s[10] = "abc"` pads with `'\0'`; `char s[] = "abc"` auto-sizes to 4. |
| Array Assignment | `str = "xyz"` is illegal after declaration; use `strcpy()`. |
| `strlen` | Returns length excluding `'\0'`; `size_t` return type; differs from `sizeof`. |
| `strcpy` / `strncpy` | Copy strings; no bounds check in `strcpy` — risk of buffer overflow. |
| `strcmp` / `strncmp` | Returns 0 (equal), >0, or <0; never use `==` to compare strings. |
| `strcat` / `strncat` | Append strings; destination must have enough space. |
| `strchr` / `strstr` | Search for character or substring; return pointer or `NULL`. |
| `strtok` | Tokenize string by delimiters; modifies original string; pass `NULL` after first call. |
| `isalpha`, `isdigit`, ... | `<ctype.h>` classification functions; return non-zero for true. |
| `toupper` / `tolower` | Convert character case; non-letters returned unchanged. |
| `scanf("%s", ...)` | Reads one word (stops at whitespace); no `&` needed for arrays. |
| `fgets` | Reads full line including `'\n'`; safe with size limit. |
| `puts` | Prints string + automatic newline. |
| `atoi` / `atof` / `atol` | Convert string to `int` / `double` / `long`. |
| `sscanf` / `sprintf` | Read from / write to strings using format specifiers. |
| `char*` Pointer | Points to string literal (read-only memory); do not modify. |
| `const char*` | Explicitly marks string as read-only; prevents accidental modification. |
| 2D `char` Array | Fixed-size rows; mutable; wastes space for short strings. |
| Array of `char*` | Flexible; no wasted space; strings are read-only if pointing to literals. |

---
