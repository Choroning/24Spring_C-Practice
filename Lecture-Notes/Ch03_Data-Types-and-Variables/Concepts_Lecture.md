# Chapter 3 — Data Types and Variables

[Repository Guide](../../README.md) | [English](Concepts_Lecture.md) | [한국어](Concepts_Lecture.ko.md)

> **Last Updated:** 2026-10-19
>
> Warming-Up C Programming, 천정아, Ch 3

> **Learning Objectives:**
> 1. Explain how a data type determines memory size and binary representation, and compare the sizes and ranges of integer, floating-point, and character types
> 2. Convert among decimal, binary, and hexadecimal and represent negative numbers in two's complement
> 3. Explain integer overflow and the precision, representation error, overflow, and underflow of floating-point types
> 4. Declare and initialize variables and name them according to the identifier rules
> 5. Distinguish and use literal constants, macro constants, and `const` variables
> 6. Use format specifiers, type conversion, and the `sizeof` operator

---

## Table of Contents

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
- [Self-Check Questions](#self-check-questions)

---

<br>

## 1. Data Types

A **data type** determines the memory size and binary representation needed to store a value. The way a computer system represents and stores values as binary data is called the binary representation of data types, and every value has a data type. The compiler uses the data type to decide how many bytes to allocate and how to interpret the stored bits.

```text
Data Types
├── Primitive Types          ← this chapter
│   ├── char (character)
│   ├── short, int, long, long long (integer)
│   └── float, double, long double (floating-point)
├── Derived Types            ← Chapters 7, 8
│   ├── Array
│   └── Pointer
└── User-Defined Types       ← Chapter 10
    ├── struct
    ├── union
    └── enum
```

*Figure 1. Classification of data types in C*

Every variable in C must have a type declared **before** it is used.

### 1.1 Integer Types

Integer types store whole numbers (no fractional part). C provides integer types of various sizes, and the sizes and ranges in the table below are for a 32-bit platform (64-bit Windows is the same).

| Type | Size | Range (signed) | Format |
|:-----|:----:|:---------------|:------:|
| `char` | 1 B | -128 to 127 | `%d` |
| `short` | 2 B | -32,768 to 32,767 | `%hd` |
| `int` | 4 B | -2,147,483,648 to 2,147,483,647 | `%d` |
| `long` | 4 B | -2,147,483,648 to 2,147,483,647 | `%ld` |
| `long long` | 8 B | -9,223,372,036,854,775,808 to 9,223,372,036,854,775,807 (about $\pm 9.2 \times 10^{18}$) | `%lld` |

*Table 1. Sizes, ranges, and format specifiers of signed integer types (32-bit platform)*

`long long` is a data type added in C99. On 64-bit Linux and macOS, `long` is 8 bytes and has the same range as `long long`. Whether `char` is signed or unsigned depends on the implementation (signed on x86 Windows, Linux, and macOS; unsigned on ARM Linux), and the table shows the range for signed `char`.

The C standard guarantees: `sizeof(short)` ≤ `sizeof(int)` ≤ `sizeof(long)`.

#### `signed` and `unsigned`

Integer types are divided into signed and unsigned integer types. If omitted, the type is `signed` (can hold negative values), so write `unsigned` for an unsigned integer type. Adding `unsigned` removes the negative range and roughly doubles the positive range. In the comments of the code below, 2B means about 2 billion.

```c
int a = -10;              // signed (default) → range: -2B ~ +2B
unsigned int b = 100;     // unsigned → range: 0 ~ 4,294,967,295
```

| Signed Type | Unsigned Type | Size | Unsigned Range |
|:------------|:-------------|:----:|:---------------|
| `char` | `unsigned char` | 1 B | 0-255 |
| `short` | `unsigned short` | 2 B | 0-65,535 |
| `int` | `unsigned int` | 4 B | 0-4,294,967,295 |
| `long` | `unsigned long` | 4 B | 0-4,294,967,295 |
| `long long` | `unsigned long long` | 8 B | 0-18,446,744,073,709,551,615 |

*Table 2. Sizes and ranges of unsigned integer types (32-bit platform)*

> **Key Point:** `signed int` and `int` are the same. `unsigned` and `unsigned int` are also the same. Likewise, `short` is the same as `short int`, `signed short`, and `signed short int`; `long` is the same as `long int`, `signed long`, and `signed long int`; `unsigned short` is the same as `unsigned short int`, and `unsigned long` as `unsigned long int`.

#### Overflow and Underflow

Every integer type has a **fixed range (valid range)**. Storing a value outside this range in an integer variable cuts off the remaining upper bits to fit the type's size, so only a value within the valid range is ever stored. This spilling over into a value within the valid range is called **overflow**, and the case of going below the minimum is sometimes called **underflow** separately. As a result, the value wraps around within the valid range.

```c
#include <limits.h>

int max = INT_MAX;       // 2,147,483,647
printf("%d\n", max + 1); // -2,147,483,648  (wraps around!)
```

```text
          Overflow
    ┌─── INT_MAX + 1 ───┐
    │                    ▼
... ─2 ─1  0  1  2 ... INT_MAX  INT_MIN ...
                         ▲                │
                         └── INT_MIN - 1 ─┘
                              Underflow
```

*Figure 2. Wraparound of `int` values on overflow and underflow*

```c
char n = 128;             // char range: -128~127 → overflow!
printf("%d\n", n);        // -128  (wraps around)

unsigned char red = 300;  // unsigned char range: 0~255 → overflow!
printf("%d\n", red);      // 44   (300 - 256 = 44)
```

`char n = 128;` stores only the low byte `0x80` (`10000000`) of the 4-byte integer 128 (`0x00000080`) in `n` and cuts off the upper 3 bytes. Because the most significant bit is the sign bit, this bit pattern is interpreted as -128. `unsigned char red = 300;` stores only the low byte `0x2C` (`00101100`) of 300 (`0x0000012C`), so it becomes 44.

```text
char n = 128;
  128 (int)  : 00000000 00000000 00000000 10000000
  n (char)   :                            10000000  = 0x80 → -128

unsigned char red = 300;
  300 (int)  : 00000000 00000000 00000001 00101100
  red        :                            00101100  = 0x2C → 44
```

*Figure 3. Cutting off the upper bytes to store a value in one byte*

> **Caution:** In the C standard, wraparound of unsigned integer types is defined behavior: the result is the remainder modulo $2^N$ ($N$ is the number of bits). In contrast, signed integer arithmetic that goes out of range, such as `INT_MAX + 1`, is undefined behavior, and the result of converting an out-of-range value to a signed integer type, as in `char n = 128;`, is implementation-defined. Most two's complement systems produce the wrapped results shown above, but compiler optimizations may not assume wraparound, so do not write code that relies on signed integer overflow.

> **Note:** **Tip on range constants.** Include `<limits.h>` to access constants like `INT_MAX`, `INT_MIN`, `SHRT_MAX`, etc.

### 1.2 Floating-Point Types

Floating-point types store real numbers using the **floating-point** method. A value is represented as $1.xxx \times 2^n$, where the mantissa (xxx) determines precision and the exponent ($n$) determines range.

| Type | Size | Precision | Format | Range |
|:-----|:----:|:----------|:------:|:------|
| `float` | 4 B | About 7 significant digits | `%f` | $\pm 1.17549 \times 10^{-38}$ to $\pm 3.40282 \times 10^{38}$ |
| `double` | 8 B | About 15 significant digits | `%lf` (input), `%f` (output) | $\pm 2.22507 \times 10^{-308}$ to $\pm 1.79769 \times 10^{308}$ |
| `long double` | 8+ B | ≥15 significant digits | `%Lf` | ≥ `double` |

*Table 3. Sizes, precision, format specifiers, and ranges of floating-point types*

The left value of each range is the smallest magnitude among nonzero normalized numbers, and the right value is the largest magnitude. The size of `long double` depends on the compiler; in Visual C++ it is 8 bytes, the same as `double`.

```c
float pi_f = 3.14f;       // 'f' suffix for float literal
double pi_d = 3.14159265; // decimal literals default to double
```

> **Caution:** `unsigned` **cannot** be applied to floating-point types. `unsigned float` and `unsigned double` are invalid.

#### Precision

**Precision** is the total number of **significant digits** a floating-point type can store accurately. It is not the number of decimal places.

```c
float  f = 123456789.123456789f;
double d = 123456789.123456789;

printf("float:  %.15f\n", f);  // 123456792.000000000000000 (wrong after ~7 digits)
printf("double: %.15f\n", d);  // 123456789.123456791043282 (wrong after ~15 digits)
```

`float` is accurate to about 7 significant digits; `double` to about 15. If the same value 9.876543210987654 is stored in a `float` and a `double` variable and printed with `%.15f`, the `float` gives `9.876543045043945`, correct only to 6 decimal places, while the `double` gives `9.876543210987654`, correct in every digit. For most calculations, prefer `double`.

#### Representation Error

Computers store numbers in **binary**. Some decimal fractions (like 0.1) have no exact binary representation, just as 1/3 has no exact decimal form. Converting 0.1 to binary gives $0.1_{10} = 0.000110011001100\ldots_2$, where `0011` repeats forever, so an approximation rounded to the number of mantissa bits is stored (0.1 as a `float` has the bit pattern `0x3DCCCCCD`).

```c
double x = 0.1 + 0.2;
printf("%.20f\n", x);  // 0.30000000000000004441  (not exactly 0.3!)

if (x == 0.3) { ... }  // ❌ may be false!
```

> **Caution:** Do not compare floating-point values with `==`; use a tolerance instead.
> ```c
> #include <math.h>
> if (fabs(x - 0.3) < 1e-9) { /* close enough */ }
> ```

#### Floating-Point Overflow and Underflow

- **Overflow:** Storing a value larger than the maximum representable value sets it to `INF` (infinity).
- **Underflow:** Storing a value whose magnitude is smaller than the smallest nonzero normalized value represents it as a **denormalized number** with fewer significant mantissa bits, reducing precision. If it is smaller still, it eventually becomes `0.0`.

```c
#include <float.h>

float num = 3.40282e38f;    // near FLT_MAX → OK
num = 3.40282e40f;          // overflow → inf
num = 1.17549e-42f;         // denormalized (reduced precision)
num = 1.17549e-46f;         // underflow → 0.0
```

The smallest denormalized `float` is about $1.4 \times 10^{-45}$, so `1.17549e-46f` becomes 0. Printing `1.17549e-42f` with `%e` gives `1.175689e-42`, which shows the loss of significant digits. The compiler warns about literals out of range (`3.40282e40f`, `1.17549e-46f`).

### 1.3 Character Type

Each character has a corresponding **character code**, such as ASCII, EBCDIC, or the Korean Wansung (precomposed) code. `char` usually stores a single character using **ASCII** encoding (1 byte). Internally, it stores the character's integer code, so storing `'A'` in a `char` variable actually stores the ASCII code 65 (`0x41`).

```c
char letter = 'A';       // stores 65 internally
printf("%c\n", letter);   // A  (as character)
printf("%d\n", letter);   // 65 (as integer)
```

| Char | ASCII | Description |
|:----:|:-----:|:------------|
| `'A'`-`'Z'` | 65-90 | uppercase letters |
| `'a'`-`'z'` | 97-122 | lowercase letters |
| `'0'`-`'9'` | 48-57 | digit characters |
| `' '` | 32 | space |

*Table 4. ASCII codes of common characters*

ASCII is a 7-bit code with 128 codes from 0 to 127, made up of 33 control characters and 95 printable characters. ASCII codes 0-31 and 127 are **control characters** (non-printable) for controlling devices, and codes 32-126 are **printable characters**.

EBCDIC is an 8-bit character code used on IBM mainframes. Korean Hangul is not in ASCII, so separate codes are used. The Korean Wansung code (KS X 1001) assigns a 2-byte code to each of 2,350 frequently used Hangul syllables, and Windows CP949 extends it to represent all 11,172 modern Hangul syllables. The UTF-8 encoding of Unicode, widely used today, stores one Hangul syllable in 3 bytes. In every scheme, one Hangul syllable does not fit in a single 1-byte `char`, so Korean text is handled as a string.

Since `char` is essentially a small 1-byte integer, arithmetic on characters is valid.

```c
char ch = 'M';
char prev = ch - 1;    // 'L' (76)
char next = ch + 1;    // 'N' (78)
char lower = ch + 32;  // 'm' (109)
```

Printing the same `char` value with `%c`, `%d`, and `%#x` gives the character, its decimal code, and its hexadecimal code with `0x`. For example, `'M'` prints as `M`, `77`, and `0x4d`. `char` is also useful as an integer type for storing small integers (with `char n = 97;`, `n + 1` is 98), and `unsigned char` is mainly used to store 1 byte of binary data, as in `unsigned char flags = 0x81;` (binary data `10000001`).

> **Note:** **Tip on case conversion.** In ASCII, the code difference between an uppercase letter and its lowercase letter is always 32 (`'a' - 'A' == 32`).

#### Escape Sequences

Escape sequences represent control characters that cannot be printed and characters that need special notation inside strings. They consist of a backslash (`\`) and a designated character.

| Escape | Name | ASCII | Description |
|:------:|:-----|:-----:|:------------|
| `\n` | newline | 10 | move to next line |
| `\t` | tab | 9 | horizontal tab |
| `\0` | null | 0 | null character (string terminator) |
| `\\` | backslash | 92 | literal `\` |
| `\"` | double quote | 34 | literal `"` inside strings |
| `\'` | single quote | 39 | literal `'` inside char literals |

*Table 5. Common escape sequences*

```c
printf("Hello\tWorld\n");   // Hello	World (tab + newline)
printf("She said \"Hi\"\n"); // She said "Hi"
printf("Path: C:\\Users\n"); // Path: C:\Users
```

You can also use `\x` followed by a hex ASCII code.

```c
char newline = '\xa';  // '\xa' == '\n' == ASCII 10
```

---

<br>

## 2. Binary Representation

### 2.1 Number Systems

Computers store all data in **binary (base 2)**. Understanding binary, decimal, and hexadecimal conversions is fundamental.

**Decimal (base 10) → each digit is a power of 10:**

```text
45,238 = 4×10⁴ + 5×10³ + 2×10² + 3×10¹ + 8×10⁰
```

**Binary (base 2) → each digit is a power of 2:**

```text
11011₂ = 1×2⁴ + 1×2³ + 0×2² + 1×2¹ + 1×2⁰
       = 16   + 8    + 0    + 2    + 1    = 27₁₀
```

**Decimal → binary:** Divide the decimal number by 2 repeatedly until the quotient is 0, and read the remainders in reverse, starting from the last one.

```text
27 ÷ 2 = 13 … 1   ↑
13 ÷ 2 =  6 … 1   │
 6 ÷ 2 =  3 … 0   │  read the remainders from bottom to top
 3 ÷ 2 =  1 … 1   │
 1 ÷ 2 =  0 … 1   │
27₁₀ = 11011₂
```

**Binary addition:** In each position, 0 + 0 = 0, 0 + 1 = 1, 1 + 0 = 1, and $1 + 1 = 10_2$ (0 in that position, carry 1 to the next).

```text
    100101₂   (37)
  + 110011₂   (51)
  ─────────
   1011000₂   (88)
```

**Hexadecimal (base 16) → digits 0-9 and letters A-F:**

| Dec | 0 | 1 | ... | 9 | 10 | 11 | 12 | 13 | 14 | 15 |
|:---:|:-:|:-:|:---:|:-:|:--:|:--:|:--:|:--:|:--:|:--:|
| Hex | 0 | 1 | ... | 9 | A  | B  | C  | D  | E  | F  |

*Table 6. Correspondence between decimal and hexadecimal digits*

```text
0x3A0B = 3×16³ + 10×16² + 0×16¹ + 11×16⁰
       = 12288 + 2560   + 0     + 11     = 14,859₁₀
```

One hexadecimal digit corresponds exactly to four binary digits (e.g., `0x2C` = `0010 1100`), so hexadecimal is used to write binary data compactly.

In C, use prefixes for literal notation.

```c
int dec = 27;      // decimal
int bin = 0b11011; // binary (standard since C23, compiler extension before)
int oct = 033;     // octal (prefix 0)
int hex = 0x1B;    // hexadecimal (prefix 0x)
```

### 2.2 Integer Representation (Two's Complement)

**How does the computer represent negative integers?**

Modern systems use **two's complement**. In signed integer types, the most significant bit (MSB) is the **sign bit**: `0` = positive, `1` = negative.

**To get -n:** write n in binary, flip all bits (0 to 1 and 1 to 0), and add 1 to the result.

```text
+7 in 8-bit:  0 0 0 0 0 1 1 1
flip all bits: 1 1 1 1 1 0 0 0
add 1:         1 1 1 1 1 0 0 1  → -7
```

Besides two's complement, negative numbers can be represented by **sign-magnitude**, which uses the most significant bit only as the sign, and **one's complement**, which uses the bitwise inversion as the negative. A 3-bit comparison is shown below.

| Bits | Sign-Magnitude | One's Complement | Two's Complement | Unsigned |
|:----:|:----:|:----:|:----:|:----:|
| `000` | 0 | 0 | 0 | 0 |
| `001` | +1 | +1 | +1 | 1 |
| `010` | +2 | +2 | +2 | 2 |
| `011` | +3 | +3 | +3 | 3 |
| `100` | -0 | -3 | -4 | 4 |
| `101` | -1 | -2 | -3 | 5 |
| `110` | -2 | -1 | -2 | 6 |
| `111` | -3 | -0 | -1 | 7 |

*Table 7. Interpretations of 3-bit patterns under each scheme*

In 3 bits, sign-magnitude and one's complement represent only the 7 values from -3 to +3 and have two representations of zero (+0 and -0), whereas two's complement represents the 8 values from -4 to +3 and has a single zero. An unsigned 3-bit integer represents 0-7.

**Why two's complement?**
- There is only one representation for zero (unlike sign-magnitude and one's complement).
- The adder works the same way for positive and negative numbers, so subtraction can be done as addition of a negative number.
- The hardware implementation is simple.

Unsigned integer types use the most significant bit to store value as well. In other words, the data type of a variable determines the meaning of the value stored in it.

> **Key Point:** The same bit pattern means different things depending on the type. `short a = -7` and `unsigned short b = 65529` have the **identical bits** (`0xFFF9`), but the type determines interpretation. In `b`, the most significant bit is treated as the value $2^{15}$.

Printing the two variables with `printf("%08x", ...)` (`%08x` prints in hexadecimal in a width of 8 characters, filling empty positions with 0) gives `fffffff9` for `a` and `0000fff9` for `b`. A `short` value is converted to a 4-byte `int` when printed, and `a` is sign-extended in the process, so only the low 2 bytes `fff9` of the two values should be compared.

### 2.3 Floating-Point Representation (IEEE 754)

Floating-point numbers are stored as: **sign bit + exponent + mantissa**.

```text
Value = (-1)^sign × 1.mantissa × 2^(exponent - bias)
```

| Type | Sign | Exponent | Mantissa | Total | Bias |
|:-----|:----:|:--------:|:--------:|:-----:|:-----:|
| `float` (single) | 1 bit | 8 bits | 23 bits | 32 bits | 127 |
| `double` (double) | 1 bit | 11 bits | 52 bits | 64 bits | 1023 |

*Table 8. Bit layout of single- and double-precision floating-point numbers*

- More **mantissa bits** give more precision (significant digits).
- More **exponent bits** give a wider range.

This explains why `float` has about 7 significant digits (23-bit mantissa) and `double` has about 15 (52-bit mantissa). A normalized number does not store its leading 1, so the actual significant bits are 24 and 53, and $\log_{10} 2^{24} \approx 7.2$ and $\log_{10} 2^{53} \approx 15.9$.

**Example: representing 23.625 as a `float`.** The integer part 23 is $10111_2$, and the fractional part 0.625 is 0.5 + 0.125, so it is $0.101_2$. Therefore $23.625 = 10111.101_2 = 1.0111101_2 \times 2^4$. The sign bit is 0, the exponent field is $4 + 127 = 131 = 10000011_2$, and the mantissa field is the 23 bits formed by 0111101 after the binary point followed by zeros.

```text
23.625 = 10111.101₂ = 1.0111101₂ × 2⁴
sign | exponent (131) | mantissa (23 bits)
  0  | 1000 0011      | 0111 1010 0000 0000 0000 000
= 0100 0001 1011 1101 0000 0000 0000 0000₂ = 0x41BD0000
```

> **Note:** **Details of IEEE 754.** There is no need to memorize every special exponent value used for zero, infinity, NaN, and denormalized numbers, but knowing the structure explains why precision and range differ between `float` and `double`.

---

<br>

## 3. Variables

The data used in a program consists of variables and constants. A **variable** is a named memory location that can change its value during program execution. A **constant** is a value that cannot change.

### 3.1 Declaration and Initialization

**Declaration** tells the compiler the variable's data type and name. To declare several variables of the same type, list the variable names separated by commas (`,`). **Initialization** gives a variable its starting value when it is allocated in memory, and **assignment** stores a value in a variable that already exists.

```c
int x;                // declaration — value is garbage (undefined)
int y = 10;           // declaration + initialization
x = 5;                // assignment

int a, b, c;          // multiple declarations
int m = 1, n = 2;    // multiple with initialization
```

> **Caution:** Uninitialized local variables contain **garbage values** (whatever was previously in that memory). Using them causes **undefined behavior**, and the compiler issues a warning (Visual Studio may even treat it as a compile error). Global variables declared outside functions are automatically initialized to 0.

When the initial value's type does not match the variable's type, the compiler automatically converts the value to the variable's type for initialization but may warn.

```c
float rate = 0.2;     // ⚠ 0.2 is double → converted to float (possible precision loss)
int weight = 50.5;    // ⚠ 50.5 is double → truncated to 50 (data loss)
```

### 3.2 Identifiers and Naming Rules

An **identifier** is a name created and used by the programmer, such as a variable name or a function name.

| Rule | Valid Examples | Invalid Examples |
|:-----|:-------------|:-----------------|
| Letters, digits, `_` only | `score1`, `tax_rate` | `annual-salary` (hyphen) |
| Must start with letter or `_` | `_amount`, `count` | `2019income` (starts with digit) |
| Case-sensitive | `length` ≠ `Length` | None |
| No keywords | None | `int`, `return`, `case` |
| No spaces | `taxRate` | `total amount` |

*Table 9. Identifier rules with examples*

No symbol other than the underscore (`_`) may be used. A **keyword** is a word such as `int` or `return` that is reserved for a special meaning in C. Variable names should have a clear meaning. Names beginning with an underscore are valid by the rules, but names beginning with `_` followed by an uppercase letter, or with `__`, are reserved for the standard library and should be avoided.

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

A **constant** is an element whose value does not change in a program. Constants include **literal constants**, values used directly in source code, and **symbolic constants**, values given a name. Symbolic constants are created with the macro constants of Section 4.2 and the `const` variables of Section 4.3. A value that is not stored in named memory like a variable and disappears after being used once is called a **temporary value**, and a literal constant written in an expression is used as a temporary value.

| Category | Type | Example | Data Type |
|:---------|:-----|:--------|:----------|
| Character | plain | `'x'`, `'A'` | `int` |
| Character | escape | `'\n'`, `'\t'`, `'\b'`, `'\xa'` | `int` |
| Integer | decimal | `-10`, `42` | `int` |
| Integer | hexadecimal | `0xa`, `0XA`, `0xFF` | `int` |
| Integer | octal | `012` | `int` |
| Integer | unsigned | `65536u`, `65536U` | `unsigned int` |
| Integer | long | `1234567l`, `1234567L` | `long` |
| Integer | unsigned long | `1234567ul`, `1234567UL` | `unsigned long` |
| Float | decimal | `56.78`, `.5` | `double` |
| Float | scientific | `5.678e1`, `.5e0` | `double` |
| Float | float suffix | `0.25f`, `0.25F` | `float` |
| String | string constant | `"hello"`, `"x"` | `char[]` |

*Table 10. Kinds of literal constants and their data types*

> **Key Point:** `'x'` is a **character** literal (type `int`, value 120). `"x"` is a **string** literal (type `char[2]`, stores `'x'` + `'\0'`). They are different.

### 4.2 `#define` Macro Constants

`#define` creates a **macro constant**, one kind of **symbolic constant**. A `#define` statement is a preprocessor statement, and the preprocessor replaces every occurrence of the name with the specified value before compilation.

```c
#define HOURLY_WAGE 8350
#define PI 3.141592

wage = HOURLY_WAGE * hours;  // preprocessor replaces → wage = 8350 * hours;
```

If `hours` is 5, `wage` becomes 8350 × 5 = 41750.

**Rules and pitfalls:** A `#define` statement needs no semicolon at the end, and the value of a macro constant cannot be changed.

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

`const` declares a variable whose value **cannot be changed** after initialization. Changing the value of a `const` variable causes a compile error.

```c
const int BUF_SIZE = 256;
const double PI = 3.141592;

BUF_SIZE = 128;  // ❌ compile error
```

> **Caution:** A `const` variable **must be initialized at declaration**. A declaration without initialization is not a syntax error in C (it is in C++), but because no value can be assigned later, a local one is left holding garbage and is useless.
> ```c
> const int size;     // ❌ useless — can never assign a value
> const int size = 10; // ✅ correct
> ```

| Feature | `#define` | `const` |
|:--------|:---------:|:-------:|
| Type checking | ❌ No | ✅ Yes |
| Scope | From the definition to the end of the file (until `#undef`) | Same as an ordinary variable (block or file) |
| Debugger visibility | ❌ No (replaced) | ✅ Yes |
| Semicolon | ❌ No semicolon | ✅ Normal statement |

*Table 11. Comparison of macro constants and `const` variables*

Symbolic constants make a program easier to modify, because only the one definition needs to change when the value changes, and easier to understand, because a meaningful name appears instead of a bare number.

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

*Table 12. Common format specifiers*

### 5.2 Width and Alignment

| Format | Meaning | Example (`42` or π) |
|:------:|:--------|:---------------|
| `%10d` | right-aligned, width 10 | `????????42` |
| `%-10d` | left-aligned, width 10 | `42????????` |
| `%010d` | zero-padded, width 10 | `0000000042` |
| `%+d` | show sign | `+42` |
| `%.2f` | 2 decimal places | `3.14` |
| `%.15f` | 15 decimal places | `3.141592653589793` |
| `%08x` | hex, zero-padded, width 8 | `0000002a` |

*Table 13. Specifying width, alignment, and precision*

(`?` = space)

```c
int no = 34, in = 124, out = 512;

printf("%5d", no);      //    34   (right-aligned, width 5)
printf("%-6d", in);     // 124    (left-aligned, width 6)
printf("%06d", out);    // 000512 (zero-padded, width 6)
```

Running the three statements in a row prints them joined with no line breaks: `   34124   000512`.

> **Note:** **Width and alignment at a glance.** `%Nd` right-aligns in N columns (default), `%-Nd` left-aligns, and `%0Nd` fills the empty positions with 0.

### 5.3 `scanf`

```c
int num;
scanf("%d", &num);  // & (address-of operator) is required
```

> **Caution:** `scanf` expects an **address** (`&num`), not the variable itself. Forgetting `&` causes undefined behavior.

---

<br>

## 6. Type Conversion

### 6.1 Implicit Conversion

When operands differ in type, C **promotes** the smaller type to the larger type.

```text
char → int → long → float → double → long double
```

*Figure 4. Order in which types are promoted in arithmetic*

This order is a simplification that omits `long long` and the `unsigned` types. Also, `char` and `short` are first promoted to `int` even when both operands have the same type (integer promotion). In an assignment, the value on the right is converted to the type of the variable on the left, so assigning a value of a larger type to a variable of a smaller type can lose data, and the compiler warns about it.

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

`sizeof` is an operator that computes the **byte size** of a data type, variable, or literal at compile time (for C99 variable-length arrays, it is computed at run time). The sizes of data types differ by platform.

```c
printf("char:   %d\n", sizeof(char));    // 1
printf("short:  %d\n", sizeof(short));   // 2
printf("int:    %d\n", sizeof(int));     // 4
printf("long:   %d\n", sizeof(long));    // 4
printf("float:  %d\n", sizeof(float));   // 4
printf("double: %d\n", sizeof(double));  // 8
```

The values in the comments are for a 32-bit platform and 64-bit Windows; on 64-bit Linux and macOS, `sizeof(long)` is 8.

`sizeof` also works on variables and literals.

```c
int a;
printf("%d\n", sizeof(a));      // 4
printf("%d\n", sizeof(3.14));   // 8  (double literal)
printf("%d\n", sizeof(0.25f));  // 4  (float literal)
printf("%d\n", sizeof('x'));    // 4  (char literal is int in C!)
printf("%d\n", sizeof("x"));   // 2  ('x' + '\0')
```

> **Caution:** The result type of `sizeof` is `size_t`, an unsigned integer type, so since C99 it is correct to print it with `%zu` (`printf("%zu\n", sizeof(int));`). Using `%d` as in the examples above makes gcc and clang warn about a format mismatch, and on 64-bit systems where `size_t` is 8 bytes it is, strictly speaking, undefined behavior.

> **Note:** In C, a character literal like `'x'` has type `int` (4 bytes), not `char` (1 byte). This is a C-specific quirk; in C++, `sizeof('x')` is 1.

---

<br>

## Summary

| Concept | Key Summary |
|:--------|:-------------|
| Data Types | A data type determines the memory size for a value and how its bits are interpreted. |
| Integer Types | On a 32-bit platform, `char` is 1B, `short` 2B, `int` 4B, `long` 4B, and `long long` 8B. |
| `signed`/`unsigned` | `unsigned` removes negatives and roughly doubles the positive range, and it cannot be applied to floating-point types. |
| Overflow | A value beyond an integer type's range has its upper bits cut off and wraps around, and overflow in signed arithmetic is undefined behavior. |
| Floating-Point | `float` is 4B with about 7 significant digits, and `double` is 8B with about 15 significant digits. |
| Precision | Precision is the total number of significant digits, not decimal places, and the binary representation causes representation error. |
| `char` / ASCII | `char` is a 1-byte integer, ASCII 0-31 and 127 are control characters, and 32-126 are printable characters. |
| Escape Sequences | A backslash denotes special characters, as in `\n` (newline), `\t` (tab), `\0` (null), `\\`, and `\"`. |
| Binary / Two's Complement | The MSB is the sign bit, and a negative number is formed by flipping the bits and adding 1. |
| IEEE 754 | A floating-point number is stored as sign, exponent, and mantissa, and this layout causes the differences in precision and range. |
| Variables | Variables must be declared before use and should always be initialized to avoid garbage values. |
| Identifiers | Identifiers use only letters, digits, and `_`, cannot start with a digit or be a keyword, and are case-sensitive. |
| Literals | Suffixes `f` (float), `L` (long), `u` (unsigned) and prefixes `0x` (hex), `0` (octal) set the type and base. |
| `#define` | It is a preprocessor macro, takes no semicolon at the end, and names inside strings are not replaced. |
| `const` | It is a type-checked constant and must be initialized at declaration. |
| Format Specifiers | Use `%d`, `%f`, `%c`, `%x`, `%e`, and others, and set the width with `%Nd`, `%-Nd`, and `%0Nd`. |
| Type Conversion | There is implicit conversion (promotion) and explicit conversion (casting) with `(type)`. |
| `sizeof` | It returns the byte size as `size_t`, and in C `'x'` is `int` (4B) and `"x"` is `char[2]` (2B). |

---

<br>

## Self-Check Questions

1. **Two's complement:** Write -20 as an 8-bit two's complement number, and also in hexadecimal. What is the same bit pattern when interpreted as an `unsigned char`?

   <details>
   <summary>Answer</summary>

   20 is `00010100`. Flipping every bit gives `11101011`, and adding 1 gives `11101100`, so -20 is `11101100` = `0xEC`. Interpreted as an `unsigned char`, the same bits are 128 + 64 + 32 + 8 + 4 = 236, which equals 256 - 20.

   </details>

2. **Base conversion:** Convert decimal 45 to binary and hexadecimal.

   <details>
   <summary>Answer</summary>

   Dividing 45 by 2 repeatedly gives the remainders 1, 0, 1, 1, 0, 1 in order, and reading them in reverse gives $101101_2$. Grouping the binary digits by four from the right gives `0010 1101`, so in hexadecimal it is `0x2D` (2 × 16 + 13 = 45).

   </details>

3. **Integer overflow:** What values are stored by `unsigned char c = 260;` and `char n = 200;` (on a system where `char` is signed)?

   <details>
   <summary>Answer</summary>

   Only the low byte of 260 is stored in `c`, so it is 260 - 256 = 4. 200 is `11001000`, and its most significant bit is 1, so a signed `char` interprets it as 200 - 256 = -56. The unsigned result is defined by the standard, and the result of converting to a signed type is implementation-defined, but on two's complement systems it is usually -56.

   </details>

4. **Integer division and casting:** With `int a = 9, b = 4;`, what are the values of `double r1 = a / b;` and `double r2 = (double)a / b;`?

   <details>
   <summary>Answer</summary>

   `r1` is 2.0, because `a / b` is computed first as integer division, giving 2, and that value is converted to `double` and assigned. `r2` is 2.25. Casting `a` to `double` promotes `b` to `double` as well, so floating-point division is performed.

   </details>

5. **Literals and `sizeof`:** In C, what are `sizeof('A')`, `sizeof("AB")`, and `sizeof(1.5f)`?

   <details>
   <summary>Answer</summary>

   They are 4, 3, and 4. In C, the character literal `'A'` has type `int`, so it is 4 bytes. The string literal `"AB"` is a `char[3]` storing `'A'`, `'B'`, and the terminating `'\0'`, so it is 3 bytes. `1.5f` is a `float` literal, so it is 4 bytes.

   </details>
