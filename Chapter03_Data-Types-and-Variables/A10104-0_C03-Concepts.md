# Chapter 03 — Data Types and Variables

> **Last Updated:** 2026-03-16

---

## 📑 Table of Contents

- [1. Data Types](#1-data-types)
  - [1.1 Integer Types](#11-integer-types)
  - [1.2 Floating-Point Types](#12-floating-point-types)
  - [1.3 Character Type](#13-character-type)
- [2. Binary Representation](#2-binary-representation)
  - [2.1 Number Systems](#21-number-systems)
  - [2.2 Integer Representation (Two's Complement)](#22-integer-representation-twos-complement)
  - [2.3 Floating-Point Representation (IEEE 754)](#23-floating-point-representation-ieee-754)
- [3. Variables](#3-variables)
  - [3.1 Declaration and Initialization](#31-declaration-and-initialization)
  - [3.2 Identifiers and Naming Rules](#32-identifiers-and-naming-rules)
- [4. Constants and Literals](#4-constants-and-literals)
  - [4.1 Literal Constants](#41-literal-constants)
  - [4.2 `#define` Macro Constants](#42-define-macro-constants)
  - [4.3 `const` Variables](#43-const-variables)
- [5. Format Specifiers](#5-format-specifiers)
  - [5.1 Common Specifiers](#51-common-specifiers)
  - [5.2 Width and Alignment](#52-width-and-alignment)
  - [5.3 `scanf`](#53-scanf)
- [6. Type Conversion](#6-type-conversion)
  - [6.1 Implicit Conversion](#61-implicit-conversion)
  - [6.2 Explicit Conversion (Casting)](#62-explicit-conversion-casting)
- [7. `sizeof` Operator](#7-sizeof-operator)
- [Summary](#summary)

---

<br>

## 1. Data Types

A **data type** determines the memory size and binary representation needed to store a value. The compiler uses the data type to decide how many bytes to allocate and how to interpret the stored bits.

```
Data Types
├── Primitive Types          ← this chapter
│   ├── char (character)
│   ├── short, int, long, long long (integer)
│   └── float, double, long double (floating-point)
├── Derived Types            ← later chapters
│   ├── Array
│   └── Pointer
└── User-Defined Types       ← later chapters
    ├── struct
    ├── union
    └── enum
```

Every variable in C must have a type declared **before** it is used.

### 1.1 Integer Types

Integer types store whole numbers (no fractional part).

| Type | Size | Range (signed) | Format |
|:-----|:----:|:---------------|:------:|
| `char` | 1 B | -128 ~ 127 | `%d` |
| `short` | 2 B | -32,768 ~ 32,767 | `%hd` |
| `int` | 4 B | -2,147,483,648 ~ 2,147,483,647 | `%d` |
| `long` | 4 B | -2,147,483,648 ~ 2,147,483,647 | `%ld` |
| `long long` | 8 B | ±9.2 × 10¹⁸ | `%lld` |

The C standard guarantees: `sizeof(short)` ≤ `sizeof(int)` ≤ `sizeof(long)`.

#### `signed` and `unsigned`

By default, integer types are `signed` (can hold negative values). Adding `unsigned` removes the negative range and doubles the positive range.

```c
int a = -10;              // signed (default) → range: -2B ~ +2B
unsigned int b = 100;     // unsigned → range: 0 ~ 4,294,967,295
```

| Signed Type | Unsigned Type | Size | Unsigned Range |
|:------------|:-------------|:----:|:---------------|
| `char` | `unsigned char` | 1 B | 0 ~ 255 |
| `short` | `unsigned short` | 2 B | 0 ~ 65,535 |
| `int` | `unsigned int` | 4 B | 0 ~ 4,294,967,295 |
| `long` | `unsigned long` | 4 B | 0 ~ 4,294,967,295 |
| `long long` | `unsigned long long` | 8 B | 0 ~ 18,446,744,073,709,551,615 |

> **Key Point:** `signed int` and `int` are the same. `unsigned` and `unsigned int` are also the same.

#### Overflow and Underflow

Every integer type has a **fixed range**. Storing a value outside this range causes **overflow** (exceeds max) or **underflow** (below min). The value wraps around to stay within the valid range.

```c
#include <limits.h>

int max = INT_MAX;       // 2,147,483,647
printf("%d\n", max + 1); // -2,147,483,648  (wraps around!)
```

```
          Overflow
    ┌─── INT_MAX + 1 ───┐
    │                    ▼
... ─2 ─1  0  1  2 ... INT_MAX  INT_MIN ...
                         ▲                │
                         └── INT_MIN - 1 ─┘
                              Underflow
```

```c
char n = 128;             // char range: -128~127 → overflow!
printf("%d\n", n);        // -128  (wraps around)

unsigned char red = 300;  // unsigned char range: 0~255 → overflow!
printf("%d\n", red);      // 44   (300 - 256 = 44)
```

> **Tip:** Include `<limits.h>` to access constants like `INT_MAX`, `INT_MIN`, `SHRT_MAX`, etc.

### 1.2 Floating-Point Types

Floating-point types store real numbers using the **floating-point** method: a value is represented as `1.xxx × 2^n`, where the mantissa (xxx) determines precision and the exponent (n) determines range.

| Type | Size | Precision | Format | Range |
|:-----|:----:|:----------|:------:|:------|
| `float` | 4 B | ~7 significant digits | `%f` | ±3.4 × 10³⁸ |
| `double` | 8 B | ~15 significant digits | `%lf` | ±1.8 × 10³⁰⁸ |
| `long double` | 8+ B | ≥15 significant digits | `%Lf` | ≥ `double` |

```c
float pi_f = 3.14f;       // 'f' suffix for float literal
double pi_d = 3.14159265; // decimal literals default to double
```

> **Warning:** `unsigned` **cannot** be applied to floating-point types. `unsigned float` and `unsigned double` are invalid.

#### Precision

**Precision** is the number of **significant digits** a type can store accurately — not "decimal places."

```c
float  f = 123456789.123456789f;
double d = 123456789.123456789;

printf("float:  %.15f\n", f);  // 123456792.000000000000000 (wrong after ~7 digits)
printf("double: %.15f\n", d);  // 123456789.123456791043282 (wrong after ~15 digits)
```

`float` is accurate to ~7 significant digits; `double` to ~15. For most calculations, prefer `double`.

#### Representation Error

Computers store numbers in **binary**. Some decimal fractions (like 0.1) have no exact binary representation, just as 1/3 has no exact decimal form.

```c
double x = 0.1 + 0.2;
printf("%.20f\n", x);  // 0.30000000000000004441  (not exactly 0.3!)

if (x == 0.3) { ... }  // ❌ may be false!
```

> **Warning:** Never compare floats with `==`. Use a tolerance:
> ```c
> #include <math.h>
> if (fabs(x - 0.3) < 1e-9) { /* close enough */ }
> ```

#### Floating-Point Overflow and Underflow

- **Overflow** — result exceeds max representable value → becomes `inf`.
- **Underflow** — result is too close to zero → becomes `0.0`.

```c
#include <float.h>

float num = 3.40282e38f;    // near FLT_MAX → OK
num = 3.40282e40f;          // overflow → inf
num = 1.17549e-42f;         // denormalized (reduced precision)
num = 1.17549e-46f;         // underflow → 0.0
```

### 1.3 Character Type

`char` stores a single character using **ASCII** encoding (1 byte). Internally, it stores the character's integer code.

```c
char letter = 'A';       // stores 65 internally
printf("%c\n", letter);   // A  (as character)
printf("%d\n", letter);   // 65 (as integer)
```

| Char | ASCII | Description |
|:----:|:-----:|:------------|
| `'A'`~`'Z'` | 65~90 | uppercase letters |
| `'a'`~`'z'` | 97~122 | lowercase letters |
| `'0'`~`'9'` | 48~57 | digit characters |
| `' '` | 32 | space |

ASCII codes 0~31 and 127 are **control characters** (non-printable). Codes 32~126 are **printable characters**.

Since `char` is a small integer, arithmetic on characters is valid:

```c
char ch = 'M';
char prev = ch - 1;    // 'L' (76)
char next = ch + 1;    // 'N' (78)
char lower = ch + 32;  // 'm' (109)
```

> **Tip:** The gap between uppercase and lowercase is always 32 (`'a' - 'A' == 32`).

#### Escape Sequences

Escape sequences represent control characters or special characters that cannot be typed directly in strings. They start with a backslash (`\`).

| Escape | Name | ASCII | Description |
|:------:|:-----|:-----:|:------------|
| `\n` | newline | 10 | move to next line |
| `\t` | tab | 9 | horizontal tab |
| `\0` | null | 0 | null character (string terminator) |
| `\\` | backslash | 92 | literal `\` |
| `\"` | double quote | 34 | literal `"` inside strings |
| `\'` | single quote | 39 | literal `'` inside char literals |

```c
printf("Hello\tWorld\n");   // Hello	World (tab + newline)
printf("She said \"Hi\"\n"); // She said "Hi"
printf("Path: C:\\Users\n"); // Path: C:\Users
```

You can also use `\x` followed by a hex ASCII code:

```c
char newline = '\xa';  // '\xa' == '\n' == ASCII 10
```

---

<br>

## 2. Binary Representation

### 2.1 Number Systems

Computers store all data in **binary (base 2)**. Understanding binary, decimal, and hexadecimal conversions is fundamental.

**Decimal (base 10) → each digit is a power of 10:**

```
45,238 = 4×10⁴ + 5×10³ + 2×10² + 3×10¹ + 8×10⁰
```

**Binary (base 2) → each digit is a power of 2:**

```
11011₂ = 1×2⁴ + 1×2³ + 0×2² + 1×2¹ + 1×2⁰
       = 16   + 8    + 0    + 2    + 1    = 27₁₀
```

**Hexadecimal (base 16) → digits 0~9 and A~F:**

| Dec | 0 | 1 | ... | 9 | 10 | 11 | 12 | 13 | 14 | 15 |
|:---:|:-:|:-:|:---:|:-:|:--:|:--:|:--:|:--:|:--:|:--:|
| Hex | 0 | 1 | ... | 9 | A  | B  | C  | D  | E  | F  |

```
0x3A0B = 3×16³ + 10×16² + 0×16¹ + 11×16⁰
       = 12288 + 2560   + 0     + 11     = 14,859₁₀
```

In C, use prefixes for literal notation:

```c
int dec = 27;      // decimal
int bin = 0b11011; // binary (C99, some compilers)
int oct = 033;     // octal (prefix 0)
int hex = 0x1B;    // hexadecimal (prefix 0x)
```

### 2.2 Integer Representation (Two's Complement)

**How does the computer represent negative integers?**

Modern systems use **two's complement**. The most significant bit (MSB) is the **sign bit**: `0` = positive, `1` = negative.

**To get -n:** write n in binary → flip all bits → add 1.

```
+7 in 8-bit:  0 0 0 0 0 1 1 1
flip all bits: 1 1 1 1 1 0 0 0
add 1:         1 1 1 1 1 0 0 1  → -7
```

**Why two's complement?**
- Only one representation for zero (unlike sign-magnitude)
- Addition works the same for positive and negative numbers
- Hardware implementation is simple

> **Key Point:** The same bit pattern means different things depending on the type. `short a = -7` and `unsigned short b = 65529` have the **identical bits** (`0xFFF9`), but the type determines interpretation.

### 2.3 Floating-Point Representation (IEEE 754)

Floating-point numbers are stored as: **sign bit + exponent + mantissa**.

```
Value = (-1)^sign × 1.mantissa × 2^(exponent - bias)
```

| Type | Sign | Exponent | Mantissa | Total |
|:-----|:----:|:--------:|:--------:|:-----:|
| `float` (single) | 1 bit | 8 bits | 23 bits | 32 bits |
| `double` (double) | 1 bit | 11 bits | 52 bits | 64 bits |

- More **mantissa bits** → more precision (significant digits).
- More **exponent bits** → wider range.

This explains why `float` has ~7 significant digits (23-bit mantissa) and `double` has ~15 (52-bit mantissa).

> **Note:** Understanding the full IEEE 754 encoding isn't required for this course, but knowing the structure explains why precision and range differ between `float` and `double`.

---

<br>

## 3. Variables

A **variable** is a named memory location that can change its value during program execution. A **constant** is a value that cannot change.

### 3.1 Declaration and Initialization

**Declaration** tells the compiler the variable's type and name. **Initialization** gives it a starting value.

```c
int x;                // declaration — value is garbage (undefined)
int y = 10;           // declaration + initialization
x = 5;                // assignment

int a, b, c;          // multiple declarations
int m = 1, n = 2;    // multiple with initialization
```

> **Warning:** Uninitialized variables contain **garbage values** (whatever was previously in that memory). Using them causes **undefined behavior** and the compiler will issue a warning.

When the initial value's type doesn't match the variable's type, the compiler converts it automatically but may warn:

```c
float rate = 0.2;     // ⚠ 0.2 is double → converted to float (possible precision loss)
int weight = 50.5;    // ⚠ 50.5 is double → truncated to 50 (data loss)
```

### 3.2 Identifiers and Naming Rules

An **identifier** is a name created by the programmer for variables, functions, etc.

| Rule | Valid Examples | Invalid Examples |
|:-----|:-------------|:-----------------|
| Letters, digits, `_` only | `score1`, `tax_rate` | `annual-salary` (hyphen) |
| Must start with letter or `_` | `_amount`, `count` | `2019income` (starts with digit) |
| Case-sensitive | `length` ≠ `Length` | — |
| No keywords | — | `int`, `return`, `case` |
| No spaces | `taxRate` | `total amount` |

**Naming conventions:**

```c
int usage2019;       // digits OK (just not at start)
double _amount;      // underscore start OK
double tax_rate;     // snake_case: words separated by _
double taxRate;      // camelCase: capitalize each new word
```

---

<br>

## 4. Constants and Literals

### 4.1 Literal Constants

A **literal constant** is a value used directly in source code.

| Category | Type | Example | Data Type |
|:---------|:-----|:--------|:----------|
| Character | plain | `'x'`, `'A'` | `int` |
| Character | escape | `'\n'`, `'\t'`, `'\xa'` | `int` |
| Integer | decimal | `-10`, `42` | `int` |
| Integer | hexadecimal | `0xa`, `0xFF` | `int` |
| Integer | octal | `012` | `int` |
| Integer | unsigned | `65536u`, `65536U` | `unsigned int` |
| Integer | long | `1234567L` | `long` |
| Float | decimal | `56.78`, `.5` | `double` |
| Float | scientific | `5.678e1`, `.5e0` | `double` |
| Float | float suffix | `0.25f`, `0.25F` | `float` |
| String | — | `"hello"`, `"x"` | `char[]` |

> **Key Point:** `'x'` is a **character** literal (type `int`, value 120). `"x"` is a **string** literal (type `char[2]`, stores `'x'` + `'\0'`). They are different!

### 4.2 `#define` Macro Constants

`#define` creates a **symbolic constant** — the preprocessor replaces every occurrence with the specified value before compilation.

```c
#define HOURLY_WAGE 8350
#define PI 3.141592

wage = HOURLY_WAGE * hours;  // preprocessor replaces → wage = 8350 * hours;
```

**Rules and pitfalls:**

```c
#define MAX_SIZE 100    // ✅ correct — no semicolon at end
#define MAX_SIZE 100;   // ❌ wrong — semicolon gets substituted too!

// After preprocessing with the wrong version:
int arr[MAX_SIZE];  →  int arr[100;];  // syntax error!
```

```c
#define HOURLY_WAGE 8350
HOURLY_WAGE = 9000;           // ❌ compile error — macro is not a variable
printf("HOURLY_WAGE\n");      // prints "HOURLY_WAGE" — strings are NOT replaced
printf("%d\n", HOURLY_WAGE);  // prints 8350 — identifier IS replaced
```

### 4.3 `const` Variables

`const` declares a variable whose value **cannot be changed** after initialization.

```c
const int BUF_SIZE = 256;
const double PI = 3.141592;

BUF_SIZE = 128;  // ❌ compile error
```

> **Warning:** A `const` variable **must be initialized at declaration**. Without initialization, it contains garbage and can never be assigned.
> ```c
> const int size;     // ❌ useless — can never assign a value
> const int size = 10; // ✅ correct
> ```

| Feature | `#define` | `const` |
|:--------|:---------:|:-------:|
| Type checking | ❌ No | ✅ Yes |
| Scope | Global (from definition) | Block scope |
| Debugger visibility | ❌ No (replaced) | ✅ Yes |
| Semicolon | ❌ No semicolon | ✅ Normal statement |

---

<br>

## 5. Format Specifiers

Format specifiers control how `printf` and `scanf` interpret data.

### 5.1 Common Specifiers

| Specifier | Type | Example Output |
|:---------:|:-----|:---------------|
| `%d` | `int` (decimal) | `42` |
| `%u` | `unsigned int` | `100` |
| `%f` | `float`/`double` | `3.140000` |
| `%e` | `float`/`double` (scientific) | `3.140000e+00` |
| `%c` | `char` | `A` |
| `%s` | string | `hello` |
| `%x` | `int` (hex, lowercase) | `2a` |
| `%X` | `int` (hex, uppercase) | `2A` |
| `%#x` | `int` (hex with `0x` prefix) | `0x2a` |
| `%o` | `int` (octal) | `52` |
| `%%` | literal `%` | `%` |

### 5.2 Width and Alignment

| Format | Meaning | Example (`42`) |
|:------:|:--------|:---------------|
| `%10d` | right-aligned, width 10 | `????????42` |
| `%-10d` | left-aligned, width 10 | `42????????` |
| `%010d` | zero-padded, width 10 | `0000000042` |
| `%+d` | show sign | `+42` |
| `%.2f` | 2 decimal places | `3.14` |
| `%.15f` | 15 decimal places | `3.141592653589793` |
| `%08x` | hex, zero-padded, width 8 | `0000002a` |

(`?` = space)

```c
int no = 34, in = 124, out = 512;

printf("%5d", no);      //    34   (right-aligned, width 5)
printf("%-6d", in);     // 124    (left-aligned, width 6)
printf("%06d", out);    // 000512 (zero-padded, width 6)
```

> **Tip:** `%Nd` right-aligns in N columns (default). `%-Nd` left-aligns. `%0Nd` zero-pads.

### 5.3 `scanf`

```c
int num;
scanf("%d", &num);  // & (address-of operator) is required
```

> **Warning:** `scanf` expects an **address** (`&num`), not the variable itself. Forgetting `&` causes undefined behavior.

---

<br>

## 6. Type Conversion

### 6.1 Implicit Conversion

When operands differ in type, C **promotes** the smaller type to the larger type.

```
char → int → long → float → double → long double
```

```c
int a = 5;
double b = 2.0;
double result = a + b;  // a promoted to double → 7.0

double weight;
weight = 50;  // 50 (int) → 50.0 (double)

int length;
length = 12.5; // ⚠ 12.5 (double) → 12 (int), data loss!
```

### 6.2 Explicit Conversion (Casting)

```c
int a = 7, b = 2;
double result;

result = a / b;          // int / int = int → 3 → 3.0
result = (double)a / b;  // double / int = double → 3.5
```

> **Key Point:** In `a / b`, both are `int`, so integer division happens **first** (result: 3), then 3 is assigned as 3.0 to `double`. Cast **at least one** operand to get floating-point division.

---

<br>

## 7. `sizeof` Operator

`sizeof` returns the **byte size** of a data type, variable, or literal at compile time.

```c
printf("char:   %d\n", sizeof(char));    // 1
printf("short:  %d\n", sizeof(short));   // 2
printf("int:    %d\n", sizeof(int));     // 4
printf("long:   %d\n", sizeof(long));    // 4
printf("float:  %d\n", sizeof(float));   // 4
printf("double: %d\n", sizeof(double));  // 8
```

`sizeof` also works on variables and literals:

```c
int a;
printf("%d\n", sizeof(a));      // 4
printf("%d\n", sizeof(3.14));   // 8  (double literal)
printf("%d\n", sizeof(0.25f));  // 4  (float literal)
printf("%d\n", sizeof('x'));    // 4  (char literal is int in C!)
printf("%d\n", sizeof("x"));   // 2  ('x' + '\0')
```

> **Note:** In C, a character literal like `'x'` has type `int` (4 bytes), not `char` (1 byte). This is a C-specific quirk — in C++, `sizeof('x')` is 1.

---

<br>

## Summary

| Concept | Key Takeaway |
|:--------|:-------------|
| Data Types | Determine memory size and how bits are interpreted |
| Integer Types | `char`(1B), `short`(2B), `int`(4B), `long`(4B), `long long`(8B) |
| `signed`/`unsigned` | `unsigned` doubles positive range, removes negatives; cannot apply to `float`/`double` |
| Overflow | Value wraps around when exceeding type range |
| Floating-Point | `float`(4B, ~7 digits), `double`(8B, ~15 digits) |
| Precision | Total significant digits, not decimal places; binary causes representation error |
| `char` / ASCII | 1-byte integer; 0~31 control chars, 32~126 printable |
| Escape Sequences | `\n`(newline), `\t`(tab), `\0`(null), `\\`, `\"` |
| Binary / Two's Complement | Sign bit (MSB); flip + add 1 for negation |
| IEEE 754 | sign + exponent + mantissa; explains precision limits |
| Variables | Declare before use; always initialize; garbage values are dangerous |
| Identifiers | Letters/digits/`_` only; no digit start; no keywords; case-sensitive |
| Literals | Suffixes: `f`(float), `L`(long), `u`(unsigned); prefixes: `0x`(hex), `0`(octal) |
| `#define` | Preprocessor macro; no semicolon; strings not replaced |
| `const` | Type-safe constant; must initialize at declaration |
| Format Specifiers | `%d`, `%f`, `%c`, `%x`, `%e`; width: `%Nd`, `%-Nd`, `%0Nd` |
| Type Conversion | Implicit (promotion) or explicit (`(type)` cast) |
| `sizeof` | Returns byte size; `'x'` is `int`(4B) in C, `"x"` is `char[2]`(2B) |

---
