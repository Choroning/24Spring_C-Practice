# Chapter 3 Solutions — Data Types and Variables

[Repository Guide](../../README.md) | [English](Solutions.md) | [한국어](Solutions.ko.md)

> **Last Updated:** 2026-10-27
>
> Warming-Up C Programming, 천정아, Ch 3

---

<br>

## Table of Contents

- [Exercise 1: Statements About Data Types](#exercise-1-statements-about-data-types)
- [Exercise 2: Meanings of Escape Sequences](#exercise-2-meanings-of-escape-sequences)
- [Exercise 3: Statements About Variables](#exercise-3-statements-about-variables)
- [Exercise 4: Valid Variable Declarations](#exercise-4-valid-variable-declarations)
- [Exercise 5: Statements About Constants](#exercise-5-statements-about-constants)
- [Exercise 6: Advantages of Symbolic Constants](#exercise-6-advantages-of-symbolic-constants)
- [Exercise 7: Lines That Cause Compile Errors](#exercise-7-lines-that-cause-compile-errors)
- [Exercise 8: Printing Out-of-Range Values](#exercise-8-printing-out-of-range-values)
- [Exercise 9: Area and Perimeter of a Square](#exercise-9-area-and-perimeter-of-a-square)
- [Exercise 10: Area and Perimeter of a Rectangle](#exercise-10-area-and-perimeter-of-a-rectangle)
- [Exercise 11: Computing Potential Energy](#exercise-11-computing-potential-energy)
- [Exercise 12: Area of a Right Triangle](#exercise-12-area-of-a-right-triangle)
- [Exercise 13: Converting Dollars to Won](#exercise-13-converting-dollars-to-won)
- [Exercise 14: Converting Won to Dollars](#exercise-14-converting-won-to-dollars)
- [Exercise 15: Converting Yards to Meters](#exercise-15-converting-yards-to-meters)
- [Exercise 16: Converting Inches to Centimeters](#exercise-16-converting-inches-to-centimeters)
- [Exercise 17: Converting Square Meters to Pyeong](#exercise-17-converting-square-meters-to-pyeong)
- [Exercise 18: Square and Cube of a Real Number](#exercise-18-square-and-cube-of-a-real-number)

---

<br>

## Exercise 1: Statements About Data Types

**Textbook Problem:** Chapter 3 exercise 1

**Problem:** Of ten statements about the size, valid range, and precision of data types, choose all the incorrect ones. The options are in [Exercise 1](Exercises.md#exercise-1-statements-about-data-types).

### Solution

**Answer:** ①, ②, ③, ⑥, ⑧, ⑨, ⑩

**Explanation:** A data type determines the memory size for storing a value and how the stored bits are interpreted ([Chapter 3, Section 1](Concepts_Lecture.md#1-data-types)). Integer types have a fixed size, so an out-of-range value wraps around into the valid range, while for floating-point types the mantissa determines the precision and the exponent the range, and most values are stored as approximations.

- **① (incorrect):** The size of a data type depends on the platform. For example, `long` is 4 bytes on 32-bit platforms and 64-bit Windows but 8 bytes on 64-bit Linux and macOS. The C standard guarantees only an order of sizes such as `sizeof(short)` ≤ `sizeof(int)` ≤ `sizeof(long)`, so the actual size is checked with the `sizeof` operator ([Chapter 3, Section 1.1](Concepts_Lecture.md#11-integer-types), [Section 7](Concepts_Lecture.md#7-sizeof-operator)).
- **② (incorrect):** The size of the `char` type is 1 byte. The C standard defines `sizeof(char)` as 1 on every platform.
- **③ (incorrect):** `unsigned` can be applied only to integer types, and `unsigned float` and `unsigned double` are invalid. Floating-point types have only one form, which has a sign bit ([Chapter 3, Section 1.2](Concepts_Lecture.md#12-floating-point-types)).
- **④ (correct):** A larger integer type has more bits for the value, so its valid range is wider. The 2-byte `short` represents -32,768 to 32,767, and the 4-byte `int` represents -2,147,483,648 to 2,147,483,647.
- **⑤ (correct):** A `char` variable stores the integer code of a character, so `char` is an integer type 1 byte in size. That is why arithmetic such as `'M' + 1` is possible and why it is also used to store small integers ([Chapter 3, Section 1.3](Concepts_Lecture.md#13-character-type)).
- **⑥ (incorrect):** The size of a variable is set by its data type and does not grow with the stored value. Storing a value larger than the maximum cuts off the upper bits and sets the variable to a value within the valid range (overflow). For example, with `char n = 128;`, `n` becomes -128 ([Overflow and Underflow in Chapter 3, Section 1.1](Concepts_Lecture.md#overflow-and-underflow)).
- **⑦ (correct):** Storing a value smaller than the minimum also cuts off the upper bits, so the value wraps around within the valid range (underflow). In `short b = SHRT_MIN - 1;` of Exercise 8, `b` becomes 32767, the maximum of `short`.
- **⑧ (incorrect):** Storing a value larger than the largest representable value in a floating-point variable sets it to infinity (`INF`), not 0. The value becomes 0 in the case of underflow, when a value whose magnitude is smaller than the smallest nonzero value is stored ([Floating-Point Overflow and Underflow in Chapter 3, Section 1.2](Concepts_Lecture.md#floating-point-overflow-and-underflow)).
- **⑨ (incorrect):** The precision of a real number, that is, the number of significant digits, is set by the number of mantissa bits, and the exponent part sets the representable range. `float` has a 23-bit mantissa and about 7 significant digits, and `double` has 52 bits and about 15 digits ([Chapter 3, Section 2.3](Concepts_Lecture.md#23-floating-point-representation-ieee-754)).
- **⑩ (incorrect):** A fraction such as 0.1 that repeats forever in binary is stored as an approximation rounded to the number of mantissa bits, so a representation error occurs. Only values such as 0.5 and 23.625, which are finite sums of powers of 2 and fit in the mantissa bits, are represented exactly ([Representation Error in Chapter 3, Section 1.2](Concepts_Lecture.md#representation-error)).

> **Note:** **Storing out-of-range integers.** The statement in ⑥ and ⑦ that the value wraps around into the valid range describes the behavior of the usual systems that use two's complement. The C standard defines the result of converting an out-of-range value to an unsigned integer type as the remainder modulo $2^N$ ($N$ is the number of bits), but leaves the result of converting it to a signed integer type as implementation-defined behavior. gcc, clang, and Visual C++ cut off the upper bits in this case too, so the value wraps around as described. On the other hand, a signed integer arithmetic result that goes out of range, such as `INT_MAX + 1`, is undefined behavior, so do not write code that assumes wraparound.

---

<br>

## Exercise 2: Meanings of Escape Sequences

**Textbook Problem:** Chapter 3 exercise 2

**Problem:** Match the escape sequences `'\0'`, `'\a'`, `'\b'`, `'\t'`, `'\n'`, and `'\\'` with their meanings. The options are in [Exercise 2](Exercises.md#exercise-2-meanings-of-escape-sequences).

### Solution

**Answer:** (1) ②, (2) ④, (3) ⑥, (4) ③, (5) ①, (6) ⑤

**Explanation:** An escape sequence is a backslash (`\`) followed by a designated character, and it represents a control character that cannot be printed or a character that needs special notation inside a string ([Escape Sequences in Chapter 3, Section 1.3](Concepts_Lecture.md#escape-sequences)). Each is written with two characters but is a single character.

- **(1) `'\0'` → ② Null character:** The character with ASCII code 0, used to mark the end of a string.
- **(2) `'\a'` → ④ Bell:** The control character with ASCII code 7 (alert). Printing it shows no character on the screen, and the terminal sounds a bell depending on its settings.
- **(3) `'\b'` → ⑥ Backspace:** The control character with ASCII code 8, which moves the output position one column to the left. A character printed after it overwrites the previous character.
- **(4) `'\t'` → ③ Horizontal tab:** The control character with ASCII code 9, which moves the output position to the next tab stop.
- **(5) `'\n'` → ① Newline:** The control character with ASCII code 10, which moves the output position to the beginning of the next line.
- **(6) `'\\'` → ⑤ Backslash:** A backslash starts an escape sequence, so it is written twice to represent the backslash character itself (ASCII code 92).

---

<br>

## Exercise 3: Statements About Variables

**Textbook Problem:** Chapter 3 exercise 3

**Problem:** Of seven statements about the declaration, memory allocation, and initialization of variables, choose all the correct ones. The options are in [Exercise 3](Exercises.md#exercise-3-statements-about-variables).

### Solution

**Answer:** ②, ③

**Explanation:** A variable is a named memory location whose value can change during program execution ([Chapter 3, Section 3](Concepts_Lecture.md#3-variables)). To use a variable, its data type and name must be declared first, and the declaration allocates memory of the data type's size.

- **① (incorrect):** In C, every variable must be declared with a data type before use. The compiler uses the data type to decide how many bytes to allocate and how to interpret the stored bits.
- **② (correct):** The value stored in a variable can be read and used at any time, as in `printf("%d", x)` or `y = x + 1`.
- **③ (correct):** A variable is a named memory location, so declaring it allocates memory of the data type's size. An `int` variable usually occupies 4 bytes.
- **④ (incorrect):** A variable declaration consists of a data type and a name, and the name must follow the identifier rules. The program accesses the variable's memory location through this name.
- **⑤ (incorrect):** The value of a variable can be changed any number of times during execution with assignment statements. What cannot be changed is a constant, and among variables only a variable declared with `const` is the exception whose value cannot be changed.
- **⑥ (incorrect):** Initialization gives a variable its starting value when it is allocated in memory, that is, at declaration (`int y = 10;`). Storing a value in a variable that already exists (`x = 5;`) is assignment ([Chapter 3, Section 3.1](Concepts_Lecture.md#31-declaration-and-initialization)).
- **⑦ (incorrect):** An uninitialized local variable holds a garbage value, whatever was in that memory before, and reading it is undefined behavior. A global variable declared outside functions is automatically initialized to 0, but this is not a rule for variables in general.

---

<br>

## Exercise 4: Valid Variable Declarations

**Textbook Problem:** Chapter 3 exercise 4

**Problem:** Of six variable declarations, choose all the valid ones. The options are in [Exercise 4](Exercises.md#exercise-4-valid-variable-declarations).

### Solution

**Answer:** ③, ⑤

**Explanation:** A variable declaration writes the variable name after the data type and ends with a semicolon, and the variable name must follow the identifier rules. An identifier uses only letters, digits, and the underscore (`_`), cannot start with a digit, cannot be a keyword, and cannot contain spaces ([Chapter 3, Section 3.2](Concepts_Lecture.md#32-identifiers-and-naming-rules)). Compiling the six options with `gcc -std=c99` shows that only ③ and ⑤ compile without errors.

- **① (incorrect):** `default` is a keyword used in the `switch` statement, so it cannot be used as a variable name.
- **② (incorrect):** No symbol other than the underscore can be used in an identifier, so `%_of_market`, which contains `%`, cannot be a variable name. It must be changed to something like `percent_of_market`.
- **③ (correct):** `unsigned short` is an unsigned 2-byte integer type, and `maxCount` is a camelCase name in which the first letter of each joined word is uppercase.
- **④ (incorrect):** A variable with the same name cannot be declared twice in the same block. This holds even if the data types differ, and the compiler reports an error that `num` is redefined with a different type.
- **⑤ (correct):** Variables of the same type can be declared at once by listing them with commas, and only some of them may be initialized. `x` is initialized to 100, `z` to 200, and `y` is only declared.
- **⑥ (incorrect):** A variable name cannot contain a space. `elapsed sec` is parsed as two words and causes a syntax error, so it must be written as `elapsed_sec` or `elapsedSec`.

---

<br>

## Exercise 5: Statements About Constants

**Textbook Problem:** Chapter 3 exercise 5

**Problem:** Of eight statements about literal constants, macro constants, and `const` variables, choose all the incorrect ones. The options are in [Exercise 5](Exercises.md#exercise-5-statements-about-constants).

### Solution

**Answer:** ③, ④, ⑤, ⑦

**Explanation:** A constant is an element whose value does not change, and constants are divided into literal constants, whose values are written directly in source code, and symbolic constants, which give a value a name. Symbolic constants are created as macro constants with `#define` and as `const` variables ([Chapter 3, Section 4](Concepts_Lecture.md#4-constants-and-literals)).

- **① (correct):** A constant cannot be changed, so it cannot appear on the left side of the assignment operator `=`. `10 = x;` and a statement that assigns a value to a `const` variable are compile errors (Exercise 7).
- **② (correct):** This describes a property of literal constants. A literal constant written in an expression is not stored in named memory like a variable but is used as a temporary value that disappears after being used once ([Chapter 3, Section 4.1](Concepts_Lecture.md#41-literal-constants)). Among constants, a `const` variable is allocated in memory (⑦), so this statement holds for literal constants.
- **③ (incorrect):** A constant with a name is a symbolic constant. A literal constant is a constant whose value is written directly in source code, such as `10`, `3.14`, or `'A'`, and it has no name.
- **④ (incorrect):** What makes code easy to read and easy to modify is symbolic constants, not literal constants (Exercise 6). If the same literal is written in many places, every place must be found and fixed when the value changes, and a bare number does not show what the value means.
- **⑤ (incorrect):** A `#define` statement is a preprocessor statement, not a C statement, and it gives only the name and the replacement value, as in `#define PI 3.141592`, with no data type. The type after replacement is determined by the literal itself, and `3.141592` is a `double` ([Chapter 3, Section 4.2](Concepts_Lecture.md#42-define-macro-constants)).
- **⑥ (correct):** The preprocessor replaces only macro names used as identifiers and does not replace characters inside a string. `printf("HOURLY_WAGE\n");` prints `HOURLY_WAGE` as it is.
- **⑦ (incorrect):** A `const` variable only cannot be changed; it is still a variable, so it is allocated in memory, and its address can be taken with `&` ([Chapter 3, Section 4.3](Concepts_Lecture.md#43-const-variables)).
- **⑧ (correct):** Assigning a value to a `const` variable makes the compiler report an error (line 12 of Exercise 7).

> **Note:** **Where literal values are placed.** "Not stored in memory" in ② means that no named memory space is allocated for a literal constant. The value itself is placed by the compiler directly in a machine instruction or in a read-only data area. In particular, a string literal such as `"hello"` is stored in memory as a `char` array that lasts for the whole execution of the program.

---

<br>

## Exercise 6: Advantages of Symbolic Constants

**Textbook Problem:** Chapter 3 exercise 6

**Problem:** Write two advantages of using symbolic constants instead of literal constants. The full problem is in [Exercise 6](Exercises.md#exercise-6-advantages-of-symbolic-constants).

### Solution

**Answer:** (1) The program is easier to modify. (2) The program is easier to understand.

**Explanation:** A symbolic constant is a constant that gives a value a name, and there are macro constants and `const` variables ([Chapter 3, Section 4.3](Concepts_Lecture.md#43-const-variables)).

- **(1) Easier to modify:** When the value changes, only the one place where the symbolic constant is defined needs to be fixed. With literal constants, every place where the same value is used must be found and fixed, and missing even one makes the program behave incorrectly.
- **(2) Easier to understand:** A meaningful name appears instead of a bare number. `wage = HOURLY_WAGE * hours;` shows more clearly than `wage = 8350 * hours;` that 8350 is the hourly wage.

---

<br>

## Exercise 7: Lines That Cause Compile Errors

**Textbook Problem:** Chapter 3 exercise 7

**Problem:** In a 14-line source code that uses the macro constants `MAX` and `MIN` and the `const` variable `y`, find all the lines that cause a compile error. The source code is in [Exercise 7](Exercises.md#exercise-7-lines-that-cause-compile-errors).

### Solution

**Answer:** Lines 10, 12, and 13

**Explanation:** Macro constants and `const` variables cannot be changed, and a semicolon at the end of a `#define` statement is substituted along with the value ([Chapter 3, Section 4.2](Concepts_Lecture.md#42-define-macro-constants), [Section 4.3](Concepts_Lecture.md#43-const-variables)). Compiling this code with `gcc -std=c99 -Wall` reports errors on these three lines only.

- **Line 10 (error):** The preprocessor replaces `MAX` with `1000`, so this statement becomes `1000 = 2000;`. A value cannot be assigned to a literal constant.
- **Line 11 (valid):** It becomes `x = 1000 - 1;`, which assigns 999 to the ordinary variable `x`.
- **Line 12 (error):** `y` is a `const` variable, so its value cannot be changed after it is initialized on line 8.
- **Line 13 (error):** `#define MIN 0;` on line 3 defines `MIN` as `0;`, so after preprocessing the statement becomes `printf("range: %d ~ %d\n", 0;, 1000);`. A semicolon inside the argument list of a function call is a syntax error. Line 3 itself is not an error; the error is reported on line 13, where the macro is used.
- **Other lines (valid):** The macro definition on line 2 and the declarations and initializations on lines 7 and 8 are correct. `main` ends on line 14 without a `return` statement, but since C99 reaching the end of `main` returns 0, so this is not an error.

---

<br>

## Exercise 8: Printing Out-of-Range Values

**Textbook Problem:** Chapter 3 exercise 8

**Problem:** Write the output of the program that prints `char a = CHAR_MIN - 1;`, `short b = SHRT_MIN - 1;`, and `char ch = '\t';` with `printf("%d, %d, %x\n", a, b, ch);`. The source code is in [Exercise 8](Exercises.md#exercise-8-printing-out-of-range-values).

### Solution

**Answer:** `127, 32767, 9`

**Explanation:** `a` and `b` receive a value 1 less than the minimum of their data types, so underflow occurs, and `ch` receives 9, the ASCII code of the tab character ([Overflow and Underflow in Chapter 3, Section 1.1](Concepts_Lecture.md#overflow-and-underflow)).

- **`a`:** `CHAR_MIN - 1` is computed as an `int` and becomes -129. In 32-bit two's complement, -129 is `0xFFFFFF7F`, and storing it in a `char` cuts off the upper 3 bytes and keeps only the low byte `0x7F`, so `a` becomes 127, the maximum of `char`.
- **`b`:** `SHRT_MIN - 1` is also computed as an `int` and becomes -32769 (`0xFFFF7FFF`), and only the low 2 bytes `0x7FFF` remain, so `b` becomes 32767, the maximum of `short`.
- **`ch`:** The ASCII code of `'\t'` is 9, and `%x` prints it in hexadecimal. 9 is also the single digit `9` in hexadecimal.
- **Output:** `char` and `short` values passed to `printf` are converted to `int`, so `%d` prints 127 and 32767.

**Output:** Compiling this code with `gcc -std=c99 -Wall` gives warnings (`-Wconstant-conversion`) on the two lines that initialize `a` and `b`, saying that the value changes from -129 to 127 and from -32769 to 32767, and running it prints the following.

```text
127, 32767, 9
```

> **Note:** **Conversion rules for out-of-range values.** `CHAR_MIN` and `SHRT_MIN` from `<limits.h>` are `int` constants, so `CHAR_MIN - 1` and `SHRT_MIN - 1` are first computed as `int`, and since -129 and -32769 are within the range of `int`, no overflow occurs in the subtraction itself. The value goes out of range in the conversion step that stores the result in a `char` and a `short`, and the result of converting an out-of-range value to a signed integer type is implementation-defined in the C standard. gcc, clang, and Visual C++ cut off the upper bits, which gives 127 and 32767. In contrast, signed integer arithmetic overflow, where the result of an operation on `int` values exceeds the range of `int`, is undefined behavior. Also, `CHAR_MIN` is -128 only on systems where `char` is signed; on ARM Linux, where `char` is unsigned, `CHAR_MIN` is 0, so `a` becomes 255, the result of converting -1 to an unsigned `char`.

---

<br>

## Exercise 9: Area and Perimeter of a Square

**Textbook Problem:** Chapter 3 programming assignment 1

**Problem:** Read the length of one side as an integer and print the area and perimeter of the square. The full problem and sample run are in [Exercise 9](Exercises.md#exercise-9-area-and-perimeter-of-a-square).

### Solution

**Approach:** If the length of one side is a, the area of the square is a × a and the perimeter is 4 × a. The input and output in the sample run are all integers, so the three variables are declared as `int` ([Chapter 3, Section 1.1](Concepts_Lecture.md#11-integer-types)).

- **Input:** `scanf("%d", &side);` reads one integer. `scanf` must receive the address of the variable, so `&` is placed before the variable name ([Chapter 3, Section 5.3](Concepts_Lecture.md#53-scanf)).
- **Computation:** `side * side` and `4 * side` are multiplications of `int` values, so the results are also `int`.
- **Output:** `%d` prints the two values as decimal integers. The prompt `"한 변의 길이 ? "` has a space before the question mark, as in the sample run.
- **`_CRT_SECURE_NO_WARNINGS`:** Visual Studio issues the security warning C4996 for `scanf` and treats it as an error in the default settings of a new project, so this macro is defined on the first line to allow `scanf`. It has no effect on other compilers. The other programs in this chapter start with the same line.

**Code:**

```c
#define _CRT_SECURE_NO_WARNINGS  // allows scanf in Visual Studio
#include <stdio.h>

int main(void)
{
    int side;          // length of one side
    int area;          // area of the square
    int perimeter;     // perimeter of the square

    printf("한 변의 길이 ? ");
    scanf("%d", &side);

    area = side * side;
    perimeter = 4 * side;

    printf("정사각형의 넓이: %d\n", area);
    printf("정사각형의 둘레: %d\n", perimeter);

    return 0;
}
```

**Output:** It compiles with `gcc -std=c99 -Wall square.c -o square` without warnings and prints the same results as the sample run.

```text
한 변의 길이 ? 5
정사각형의 넓이: 25
정사각형의 둘레: 20
```

> **Caution:** `side * side` is computed as an `int`, so if the length of a side is 46341 or more, the area exceeds 2,147,483,647, the maximum of `int` ($46341^2 = 2{,}147{,}488{,}281$). This is signed integer arithmetic overflow and therefore undefined behavior. To handle larger values, compute in `long long`, as in `long long area = (long long)side * side;`, and print with `%lld`. Also, the program does not check its input, so entering a negative number prints a positive area and a negative perimeter.

---

<br>

## Exercise 10: Area and Perimeter of a Rectangle

**Textbook Problem:** Chapter 3 programming assignment 2

**Problem:** Read the width and the height as integers and print the area and perimeter of the rectangle. The full problem and sample run are in [Exercise 10](Exercises.md#exercise-10-area-and-perimeter-of-a-rectangle).

### Solution

**Approach:** If the width is w and the height is h, the area of the rectangle is w × h and the perimeter is 2 × (w + h). As in Exercise 9, integer variables are used, and printing a prompt and reading with `scanf` is done once for the width and once for the height.

- **Declaration:** Variables of the same type can be declared at once by listing them with commas, as in `int width, height;` ([Chapter 3, Section 3.1](Concepts_Lecture.md#31-declaration-and-initialization)).
- **Area:** `width * height` is 10 × 20 = 200.
- **Perimeter:** `2 * (width + height)` computes the addition in the parentheses first and gives 2 × 30 = 60. Written without parentheses as `2 * width + height`, the multiplication is computed first and gives 2 × 10 + 20 = 40.

**Code:**

```c
#define _CRT_SECURE_NO_WARNINGS  // allows scanf in Visual Studio
#include <stdio.h>

int main(void)
{
    int width, height;     // lengths of the two sides
    int area, perimeter;

    printf("가로의 길이? ");
    scanf("%d", &width);
    printf("세로의 길이? ");
    scanf("%d", &height);

    area = width * height;
    perimeter = 2 * (width + height);

    printf("직사각형의 넓이: %d\n", area);
    printf("직사각형의 둘레: %d\n", perimeter);

    return 0;
}
```

**Output:** It compiles with `gcc -std=c99 -Wall rectangle.c -o rectangle` without warnings and prints the same results as the sample run.

```text
가로의 길이? 10
세로의 길이? 20
직사각형의 넓이: 200
직사각형의 둘레: 60
```

> **Caution:** As in Exercise 9, if `width * height` exceeds the maximum of `int` (for example, 50000 × 50000), the behavior is undefined, so compute in `long long` to handle large values.

---

<br>

## Exercise 11: Computing Potential Energy

**Textbook Problem:** Chapter 3 programming assignment 3

**Problem:** Read a mass in kg and a height in m and print the potential energy 9.8 × mass × height. The full problem and sample run are in [Exercise 11](Exercises.md#exercise-11-computing-potential-energy).

### Solution

**Approach:** The mass and the height may be real numbers, and the potential energy is a real number multiplied by 9.8, so all three variables are declared as `double` ([Chapter 3, Section 1.2](Concepts_Lecture.md#12-floating-point-types)).

- **Input:** To read a `double` variable with `scanf`, use `%lf`. An input without a decimal point, such as `10`, is read as 10.0.
- **Computation:** In `9.8 * mass * height`, `9.8` is a `double` literal. 9.8 × 10 × 5 = 490.
- **Output:** `printf` prints a `double` value with `%f`, and `%.2f` prints it to 2 decimal places, giving `490.00`.

**Code:**

```c
#define _CRT_SECURE_NO_WARNINGS  // allows scanf in Visual Studio
#include <stdio.h>

int main(void)
{
    double mass;       // mass in kg
    double height;     // height in m
    double energy;     // potential energy in J

    printf("질량(kg)? ");
    scanf("%lf", &mass);
    printf("높이(m)? ");
    scanf("%lf", &height);

    energy = 9.8 * mass * height;

    printf("위치에너지: %.2f J\n", energy);

    return 0;
}
```

**Output:** It compiles with `gcc -std=c99 -Wall energy.c -o energy` without warnings, and the first run matches the sample run. The second run enters the mass and the height as real numbers, and 9.8 × 2.5 × 1.2 = 29.4.

```text
질량(kg)? 10
높이(m)? 5
위치에너지: 490.00 J
```

```text
질량(kg)? 2.5
높이(m)? 1.2
위치에너지: 29.40 J
```

> **Caution:** Unlike `printf`, `scanf` requires `%f` and `%lf` to be distinguished. Reading a `double` variable with `%f` writes the bit pattern of a 4-byte `float` into part of the 8-byte variable, so the value is stored incorrectly, and this is undefined behavior. gcc and clang warn about such format mismatches with `-Wall`.

---

<br>

## Exercise 12: Area of a Right Triangle

**Textbook Problem:** Chapter 3 programming assignment 4

**Problem:** Read the base and the height and print the area of the right triangle to 2 decimal places. The full problem and sample run are in [Exercise 12](Exercises.md#exercise-12-area-of-a-right-triangle).

### Solution

**Approach:** The area of a right triangle is base × height ÷ 2. Even when the base and the height are integers, the area can be a fraction, as in 3 × 7 ÷ 2 = 10.5, so the key to this problem is to store the area in a floating-point type and make the division a floating-point division ([Chapter 3, Section 6](Concepts_Lecture.md#6-type-conversion)).

- **Data types:** The base and the height are declared as `double` so that they can also be entered as real numbers, and they are read with `%lf`. Writing `%lf %lf` in one `scanf` reads two values separated by a space from one line.
- **Computation:** `base * height` is a `double`, so the integer `2` in `/ 2` is converted to `double`, and the division is a floating-point division. 21.0 ÷ 2 = 10.5.
- **Output:** `%.2f` prints `10.50`.

**Code:**

```c
#define _CRT_SECURE_NO_WARNINGS  // allows scanf in Visual Studio
#include <stdio.h>

int main(void)
{
    double base, height;   // base and height of the right triangle
    double area;

    printf("밑변과 높이? ");
    scanf("%lf %lf", &base, &height);

    area = base * height / 2;

    printf("직각삼각형의 면적: %.2f\n", area);

    return 0;
}
```

**Output:** It compiles with `gcc -std=c99 -Wall triangle.c -o triangle` without warnings and prints the same result as the sample run.

```text
밑변과 높이? 3 7
직각삼각형의 면적: 10.50
```

> **Caution:** **Integer division.** If the base and the height are declared as `int`, read with `%d %d`, and the same expression `area = base * height / 2;` is used, everything on the right is `int`, so 21 / 2 is computed first as an integer division and gives 10, and that value is converted to `double` and stored in `area`. The program changed this way prints `10.00`, as shown below. To read integers, make the division a floating-point division with `base * height / 2.0` or `(double)base * height / 2` ([Chapter 3, Section 6.2](Concepts_Lecture.md#62-explicit-conversion-casting)).

```text
밑변과 높이? 3 7
직각삼각형의 면적: 10.00
```

---

<br>

## Exercise 13: Converting Dollars to Won

**Textbook Problem:** Chapter 3 programming assignment 5

**Problem:** Read an amount in dollars and the won/dollar exchange rate and print how many won it is. The full problem and sample run are in [Exercise 13](Exercises.md#exercise-13-converting-dollars-to-won).

### Solution

**Approach:** The amount in won is dollars × exchange rate. In the sample run, the dollars are printed as an integer, as in `USD 150`, and the won to 2 decimal places, as in `181500.00`, so the dollars are declared as `int` and the exchange rate and the won as `double`. An exchange rate can be a fraction such as 1210.5.

- **Input:** The dollars are read with `%d` and the exchange rate with `%lf`. The dollars are asked first, in the order of the sample run.
- **Computation:** `usd * rate` is a product of an `int` and a `double`, so `usd` is converted to `double` and the multiplication is a floating-point multiplication ([Chapter 3, Section 6.1](Concepts_Lecture.md#61-implicit-conversion)). 150 × 1210 = 181500.
- **Output:** `%d` and `%.2f` are used together in one `printf` to print `USD 150 = KRW 181500.00`. The format specifiers and the arguments must match in order and type.

**Code:**

```c
#define _CRT_SECURE_NO_WARNINGS  // allows scanf in Visual Studio
#include <stdio.h>

int main(void)
{
    int usd;           // amount in US dollars
    double rate;       // won per dollar
    double krw;        // amount in won

    printf("USD? ");
    scanf("%d", &usd);
    printf("원/달러 환율? ");
    scanf("%lf", &rate);

    krw = usd * rate;

    printf("USD %d = KRW %.2f\n", usd, krw);

    return 0;
}
```

**Output:** It compiles with `gcc -std=c99 -Wall usd2krw.c -o usd2krw` without warnings and prints the same result as the sample run.

```text
USD? 150
원/달러 환율? 1210
USD 150 = KRW 181500.00
```

> **Caution:** **Entering a fraction for an integer variable.** The dollars are read with `%d`, so for an input with a fraction such as `150.5`, `scanf` reads only `150` and leaves `.5` in the input buffer. The next `scanf("%lf", &rate)` then does not wait for the user and reads the remaining `.5` as an exchange rate of 0.5, which gives a wrong result, as in the following run. To handle cents, declare the dollars as `double` as well and read them with `%lf`.

```text
USD? 150.5
원/달러 환율? USD 150 = KRW 75.00
```

---

<br>

## Exercise 14: Converting Won to Dollars

**Textbook Problem:** Chapter 3 programming assignment 6

**Problem:** Read an amount in won and the won/dollar exchange rate and print how many dollars it is. The full problem and sample run are in [Exercise 14](Exercises.md#exercise-14-converting-won-to-dollars).

### Solution

**Approach:** The amount in dollars is won ÷ exchange rate. As in Exercise 13, the won is declared as `int` and the exchange rate and the dollars as `double`. Because this problem involves division, it is important that the division is not an integer division.

- **Computation:** In `krw / rate`, `rate` is a `double`, so `krw` is converted to `double` and the division is a floating-point division. 500000 ÷ 1210 is approximately 413.2231. If the exchange rate were also declared as `int`, the integer division would give 413, and `413.00` would be printed.
- **Output:** `%.2f` rounds at the third decimal place, so it prints `413.22`.

**Code:**

```c
#define _CRT_SECURE_NO_WARNINGS  // allows scanf in Visual Studio
#include <stdio.h>

int main(void)
{
    int krw;           // amount in won
    double rate;       // won per dollar
    double usd;        // amount in US dollars

    printf("KRW? ");
    scanf("%d", &krw);
    printf("원/달러 환율? ");
    scanf("%lf", &rate);

    usd = krw / rate;

    printf("KRW %d = USD %.2f\n", krw, usd);

    return 0;
}
```

**Output:** It compiles with `gcc -std=c99 -Wall krw2usd.c -o krw2usd` without warnings and prints the same result as the sample run.

```text
KRW? 500000
원/달러 환율? 1210
KRW 500000 = USD 413.22
```

> **Caution:** Entering 0 for the exchange rate divides by zero. Since `rate` is a `double`, this expression is a floating-point division, and in gcc and clang environments that follow IEEE 754 the result is infinity, so `inf` is printed, as shown below. Dividing an integer by zero is undefined behavior, and invalid input such as 0 can be checked with the `if` statement of [Chapter 5, Section 2.1](../Ch05_Control-Statements/Concepts_Lecture.md#21-if).

```text
KRW? 500000
원/달러 환율? 0
KRW 500000 = USD inf
```

---

<br>

## Exercise 15: Converting Yards to Meters

**Textbook Problem:** Chapter 3 programming assignment 7

**Problem:** Read a length in yards, convert it to meters, and print it. 1 yd is 0.9144 m. The full problem and sample run are in [Exercise 15](Exercises.md#exercise-15-converting-yards-to-meters).

### Solution

**Approach:** The length in meters is yards × 0.9144. In keeping with the topic of this problem, the conversion factor 0.9144 is written directly in the expression as a literal constant ([Chapter 3, Section 4.1](Concepts_Lecture.md#41-literal-constants)).

- **Data types:** In the sample run, the yards are printed as an integer, as in `100`, so they are declared as `int`, and the meters are a fraction, so they are declared as `double`.
- **Computation:** The type of the literal `0.9144` is `double`, so `yard * 0.9144` is a floating-point multiplication. 100 × 0.9144 = 91.44.
- **Output:** `%f` prints 6 decimal places, so the result is `91.440000`.

**Code:**

```c
#define _CRT_SECURE_NO_WARNINGS  // allows scanf in Visual Studio
#include <stdio.h>

int main(void)
{
    int yard;          // length in yards
    double meter;      // length in meters

    printf("길이(yd)? ");
    scanf("%d", &yard);

    meter = yard * 0.9144;     // 1 yd = 0.9144 m

    printf("%d yd = %f m\n", yard, meter);

    return 0;
}
```

**Output:** It compiles with `gcc -std=c99 -Wall yard.c -o yard` without warnings and prints the same result as the sample run.

```text
길이(yd)? 100
100 yd = 91.440000 m
```

> **Note:** Writing a literal constant directly keeps the code short, but when the same value is used in several places or its meaning should be visible, a symbolic constant, such as the macro constant of Exercise 16 or the `const` variable of Exercise 17, makes the program easier to modify and to understand (Exercise 6).

---

<br>

## Exercise 16: Converting Inches to Centimeters

**Textbook Problem:** Chapter 3 programming assignment 8

**Problem:** Read a length in inches, convert it to centimeters, and print it. 1 in is 2.54 cm, and the conversion factor is defined as a macro constant. The full problem and sample run are in [Exercise 16](Exercises.md#exercise-16-converting-inches-to-centimeters).

### Solution

**Approach:** `#define CM_PER_INCH 2.54` gives the conversion factor a name, and the length in centimeters is computed as inches × `CM_PER_INCH` ([Chapter 3, Section 4.2](Concepts_Lecture.md#42-define-macro-constants)). The sample run prints the inches to 2 decimal places, as in `10.00`, so both the inches and the centimeters are declared as `double`.

- **Macro definition:** A `#define` statement is a preprocessor statement, so no semicolon is written at its end. Written as `#define CM_PER_INCH 2.54;`, it would turn this program's statement into `cm = inch * 2.54;;`, which only adds an empty statement, but used in the middle of an expression, as on line 13 of Exercise 7, it causes a syntax error.
- **Replacement:** The preprocessor turns `inch * CM_PER_INCH` into `inch * 2.54` before compilation, so at run time the program behaves the same as if the literal were written directly.
- **Output:** `%.2f in = %.2f cm` prints 10.00 and 25.40.

**Code:**

```c
#define _CRT_SECURE_NO_WARNINGS  // allows scanf in Visual Studio
#include <stdio.h>

#define CM_PER_INCH 2.54       // 1 in = 2.54 cm

int main(void)
{
    double inch;       // length in inches
    double cm;         // length in centimeters

    printf("길이(in)? ");
    scanf("%lf", &inch);

    cm = inch * CM_PER_INCH;

    printf("%.2f in = %.2f cm\n", inch, cm);

    return 0;
}
```

**Output:** It compiles with `gcc -std=c99 -Wall inch.c -o inch` without warnings and prints the same result as the sample run.

```text
길이(in)? 10
10.00 in = 25.40 cm
```

---

<br>

## Exercise 17: Converting Square Meters to Pyeong

**Textbook Problem:** Chapter 3 programming assignment 9

**Problem:** Read the area of an apartment in square meters and print how many pyeong it is. 1 m² is 0.3025 pyeong, and the conversion factor is defined as a symbolic constant. The full problem and sample run are in [Exercise 17](Exercises.md#exercise-17-converting-square-meters-to-pyeong).

### Solution

**Approach:** Symbolic constants include macro constants and `const` variables. Exercise 16 used a macro constant, so this program uses a `const` variable, `const double PYEONG_PER_SQM = 0.3025;`, and computes the area in pyeong as square meters × `PYEONG_PER_SQM` ([Chapter 3, Section 4.3](Concepts_Lecture.md#43-const-variables)).

- **`const` variable:** It must be initialized at declaration, and any later attempt to change its value causes a compile error. Unlike a macro constant, it has a data type (`double`) and is type-checked by the compiler.
- **Name:** The name of a symbolic constant is written in uppercase letters and underscores to distinguish it from ordinary variables.
- **Computation and output:** 113 × 0.3025 = 34.1825, and `%.2f` rounds at the third decimal place and prints `34.18`.

**Code:**

```c
#define _CRT_SECURE_NO_WARNINGS  // allows scanf in Visual Studio
#include <stdio.h>

int main(void)
{
    const double PYEONG_PER_SQM = 0.3025;  // 1 square meter = 0.3025 pyeong
    double sqm;        // area in square meters
    double pyeong;     // area in pyeong

    printf("아파트의 면적(제곱미터)? ");
    scanf("%lf", &sqm);

    pyeong = sqm * PYEONG_PER_SQM;

    printf("%.2f 제곱미터 = %.2f 평\n", sqm, pyeong);

    return 0;
}
```

**Output:** It compiles with `gcc -std=c99 -Wall pyeong.c -o pyeong` without warnings and prints the same result as the sample run.

```text
아파트의 면적(제곱미터)? 113
113.00 제곱미터 = 34.18 평
```

> **Note:** Defining a macro constant with `#define PYEONG_PER_SQM 0.3025` instead of the `const` variable gives the same output. The two approaches differ in whether they are type-checked, whether the name is visible in a debugger, and whether the name can be used from the definition to the end of the file or only inside its block ([Chapter 3, Section 4.3](Concepts_Lecture.md#43-const-variables)).

---

<br>

## Exercise 18: Square and Cube of a Real Number

**Textbook Problem:** Chapter 3 programming assignment 10

**Problem:** Read a real number in decimal or exponent notation and print its square and cube in exponent notation. The full problem and sample run are in [Exercise 18](Exercises.md#exercise-18-square-and-cube-of-a-real-number).

### Solution

**Approach:** The real number is read into a `double` variable with `%lf`, and the results are printed with the exponent notation format specifier `%e` ([Chapter 3, Section 5.1](Concepts_Lecture.md#51-common-specifiers)).

- **Input:** `%lf` in `scanf` reads both decimal notation such as `12.34` and exponent notation such as `1.234e2` as real numbers, so the two notations need no separate handling. `1.234e2` means $1.234 \times 10^{2}$, that is, 123.4, the same notation as floating-point literals in source code (`5.678e1`) ([Chapter 3, Section 4.1](Concepts_Lecture.md#41-literal-constants)).
- **Computation:** `x * x` and `x * x * x` give the square and the cube. For an input of 0.3, the square is 0.09 and the cube is 0.027.
- **Output:** `%e` prints a value in the form `d.dddddde±dd`, that is, one digit before the decimal point, 6 decimal places, and an exponent of at least two digits. 0.09 is $9 \times 10^{-2}$, so it is printed as `9.000000e-02`. With `%E`, an uppercase `E` is printed, as in `9.000000E-02`.

**Code:**

```c
#define _CRT_SECURE_NO_WARNINGS  // allows scanf in Visual Studio
#include <stdio.h>

int main(void)
{
    double x;          // input value
    double square, cube;

    printf("실수? ");
    scanf("%lf", &x);  // accepts both 12.34 and 1.234e2

    square = x * x;
    cube = x * x * x;

    printf("제곱: %e\n", square);
    printf("세제곱: %e\n", cube);

    return 0;
}
```

**Output:** It compiles with `gcc -std=c99 -Wall power.c -o power` without warnings, and the first run matches the sample run. The second and third runs enter the decimal notation 12.34 and the exponent notation 1.234e2 given in the problem, and $12.34^2 = 152.2756$, $12.34^3 = 1879.080904$ and $123.4^2 = 15227.56$, $123.4^3 = 1879080.904$ are printed rounded to 6 decimal places.

```text
실수? 3.0e-1
제곱: 9.000000e-02
세제곱: 2.700000e-02
```

```text
실수? 12.34
제곱: 1.522756e+02
세제곱: 1.879081e+03
```

```text
실수? 1.234e2
제곱: 1.522756e+04
세제곱: 1.879081e+06
```

> **Caution:** If a result exceeds the maximum of `double` (about $1.8 \times 10^{308}$), floating-point overflow occurs and the result becomes infinity. Entering `1e200` makes the square $10^{400}$, so both values are printed as `inf` ([Floating-Point Overflow and Underflow in Chapter 3, Section 1.2](Concepts_Lecture.md#floating-point-overflow-and-underflow)).

```text
실수? 1e200
제곱: inf
세제곱: inf
```
