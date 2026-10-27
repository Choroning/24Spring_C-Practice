# Chapter 2 Solutions — C Program Basics

[Repository Guide](../../README.md) | [English](Solutions.md) | [한국어](Solutions.ko.md)

> **Last Updated:** 2026-10-27
>
> Warming-Up C Programming, 천정아, Ch 2

---

<br>

## Table of Contents

- [Exercise 1: Statements About Comments](#exercise-1-statements-about-comments)
- [Exercise 2: Statements About Functions](#exercise-2-statements-about-functions)
- [Exercise 3: The Function Called When a Program Starts](#exercise-3-the-function-called-when-a-program-starts)
- [Exercise 4: Statements About the `main` Function](#exercise-4-statements-about-the-main-function)
- [Exercise 5: Statements About Variables](#exercise-5-statements-about-variables)
- [Exercise 6: Format Specifiers of `printf` and Their Meanings](#exercise-6-format-specifiers-of-printf-and-their-meanings)
- [Exercise 7: The Format Specifier That Produces the Output](#exercise-7-the-format-specifier-that-produces-the-output)
- [Exercise 8: Two Things Needed to Declare a Variable](#exercise-8-two-things-needed-to-declare-a-variable)
- [Exercise 9: The Header for the I/O Library](#exercise-9-the-header-for-the-io-library)
- [Exercise 10: A Program That Reads and Prints a Character](#exercise-10-a-program-that-reads-and-prints-a-character)
- [Exercise 11: Printing Several Lines with One `printf`](#exercise-11-printing-several-lines-with-one-printf)
- [Exercise 12: Printing a Decimal Integer in Hexadecimal](#exercise-12-printing-a-decimal-integer-in-hexadecimal)
- [Exercise 13: Reading and Printing a Date](#exercise-13-reading-and-printing-a-date)
- [Exercise 14: Printing Hours, Minutes, and Seconds in Two Digits](#exercise-14-printing-hours-minutes-and-seconds-in-two-digits)
- [Exercise 15: Converting Dollars to Won](#exercise-15-converting-dollars-to-won)
- [Exercise 16: Choosing a Clothing Size](#exercise-16-choosing-a-clothing-size)
- [Exercise 17: The Sum and Difference of Two Real Numbers](#exercise-17-the-sum-and-difference-of-two-real-numbers)
- [Exercise 18: Printing Pi in Several Formats](#exercise-18-printing-pi-in-several-formats)
- [Exercise 19: Reading and Printing Octal, Decimal, and Hexadecimal Integers](#exercise-19-reading-and-printing-octal-decimal-and-hexadecimal-integers)

---

<br>

## Exercise 1: Statements About Comments

**Textbook Problem:** Chapter 2 exercise 1

**Problem:** Of seven statements about comments, choose all the incorrect ones. The options are in [Exercise 1](Exercises.md#exercise-1-statements-about-comments).

### Solution

**Answer:** ②, ⑦

**Explanation:** Comments provide information about the source code or keep part of the source code from being compiled; they are ignored by the compiler and exist for human readers ([Chapter 2, Section 1.2](Concepts_Lecture.md#12-comments)). Comments are therefore not compiled, and a program does not need them.

- **① (correct):** A comment is a description that records information about the source code, such as what the code does or why it was written, in a form people can read.
- **② (incorrect):** Comments are ignored by the compiler, so they are not compiled. In the preprocessing step before compilation, each comment is replaced by one space, so the contents of a comment leave nothing in the object file ([Chapter 1, Section 3.2](../Ch01_Programming-and-C-Language/Concepts_Lecture.md#32-build-process)).
- **③ (correct):** A block comment runs from `/*` to `*/` and can span several lines.
- **④ (correct):** A line comment runs from `//` to the end of that line. It was added in C99 and is now available in most C compilers.
- **⑤ (correct):** Wrapping code that has already been written in `/* */`, or putting `//` in front of its lines, keeps that code from being compiled without deleting it. This is called commenting out code.
- **⑥ (correct):** Block comments cannot be nested. In `/* outer /* inner */ rest */`, the first `*/` closes the comment, so `rest */` remains as code and causes a compile error.
- **⑦ (incorrect):** Comments do not affect the result of compilation, so a program with no comments at all compiles and runs normally. Comments are written for the people who read and modify the code.

---

<br>

## Exercise 2: Statements About Functions

**Textbook Problem:** Chapter 2 exercise 2

**Problem:** Of seven statements about the parts and the flow of execution of a function, choose all the incorrect ones. The options are in [Exercise 2](Exercises.md#exercise-2-statements-about-functions).

### Solution

**Answer:** ⑤, ⑥

**Explanation:** A function consists of a return type, a function name, and parameters. When a function is called, the statements inside `{ }` are executed in order from the top, and when the end of the function (`}`) or a `return` is reached, control goes back to where the function was called ([Chapter 2, Section 1.3](Concepts_Lecture.md#13-main-function)).

- **① (correct):** Defining a function requires three parts: a return type, a function name, and parameters. In `int main(void)` they are `int`, `main`, and `void`.
- **② (correct):** A function with no parameters is written with `void`, as in `int main(void)`, or with empty parentheses, as in `int main()`.
- **③ (correct):** The statements the function processes are written inside the braces `{ }`, which form the function body.
- **④ (correct):** The statements in a function are executed one at a time in order from top to bottom. What changes this flow are the conditional and loop statements of Chapter 5 ([Chapter 2, Section 3](Concepts_Lecture.md#3-c-statements)).
- **⑤ (incorrect):** When the end of the function (`}`) or a `return` is reached, control goes back not to the start of the function but to **where the function was called**. This is called returning, and the caller continues execution after the function call. If control went back to the start of the function, the function would never end and would repeat the same statements.
- **⑥ (incorrect):** A C statement ends with a semicolon (`;`), not a period. However, blocks enclosed in braces and control statements such as `if` and `for` take no semicolon at the end, and preprocessor directives such as `#include` are also written without a semicolon.
- **⑦ (correct):** A C program consists of a single `main` function, or of `main` and several other functions.

> **Note:** **Empty parentheses and `void`.** When a function is defined with empty parentheses (`int main() { ... }`), it is a function with no parameters, so in a definition the two ways in ② produce the same function. In C99, however, empty parentheses in a declaration that is not a definition, as in `int f();`, do not mean that there are no parameters but that no information about the parameters is given, so the compiler cannot check the number and types of the arguments in a function call. To state precisely that there are no parameters, write `void`. Since C23, empty parentheses also mean the same as `void`.

---

<br>

## Exercise 3: The Function Called When a Program Starts

**Textbook Problem:** Chapter 2 exercise 3

**Problem:** Write the name of a function like `main`, which is called when a C program first starts. The full problem is in [Exercise 3](Exercises.md#exercise-3-the-function-called-when-a-program-starts).

### Solution

**Answer:** Entry point function

**Explanation:** The entry point function is the function agreed to be called when a C program first starts, and in C the `main` function is the entry point of every program ([Chapter 2, Section 1.3](Concepts_Lecture.md#13-main-function)). When the operating system runs a compiled program, execution starts at the first statement of `main`, and when `main` returns, the program terminates. This is why every C program must have exactly one `main` function, and other functions run only when they are called from `main`, directly or through other functions.

---

<br>

## Exercise 4: Statements About the `main` Function

**Textbook Problem:** Chapter 2 exercise 4

**Problem:** Of six statements about the return type, number, name, and exit code of the `main` function, choose all the correct ones. The options are in [Exercise 4](Exercises.md#exercise-4-statements-about-the-main-function).

### Solution

**Answer:** ①, ④, ⑤, ⑥

**Explanation:** The `main` function is the single entry point of a program, and it returns an exit code of type `int` to the operating system ([Chapter 2, Section 1.3](Concepts_Lecture.md#13-main-function), [Section 1.4](Concepts_Lecture.md#14-exit-code)).

- **① (correct):** The return type of `main` is `int`, and the return value is the exit code that indicates the termination status of the program.
- **② (incorrect):** Every C program must have exactly one `main` function. Without `main`, the source still compiles, but the link step cannot find the entry point and no executable file is produced. macOS clang then reports the error "Undefined symbols for architecture arm64" along with the missing symbol `_main`. Conversely, with two or more `main` functions, a function with the same name is defined twice and an error occurs.
- **③ (incorrect):** C is case-sensitive, so `main`, `Main`, and `MAIN` are different identifiers. Only the lowercase `main` is recognized as the entry point, and a program that defines only `Main` produces the same link error as in ②.
- **④ (correct):** Since C99, reaching the end (`}`) of the `main` function without a `return` statement is the same as returning 0. This exception applies only to `main`, and writing `return 0;` is preferred for clarity.
- **⑤ (correct):** When the program starts, the operating system calls `main`, and execution begins (Exercise 3).
- **⑥ (correct):** Exit code 0 means normal termination and a nonzero value means abnormal termination, and the operating system or a calling script uses this value to decide whether the program succeeded.

> **Note:** **Who calls `main`, and the exit code.** The textbook says that the operating system calls `main`. More precisely, the operating system loads the program into memory and passes control to the startup code of the C runtime linked into the executable file, and this startup code finishes initialization and then calls `main`. When `main` returns, the startup code calls the `exit` function with the return value, which passes the exit code to the operating system. Also, the only exit codes whose meaning the C standard defines are 0 and `EXIT_SUCCESS`, which mean success, and `EXIT_FAILURE`, which means failure (both macros are in `<stdlib.h>`); what other nonzero values mean is decided by the operating system and the program.

---

<br>

## Exercise 5: Statements About Variables

**Textbook Problem:** Chapter 2 exercise 5

**Problem:** Of seven statements about the storage, assignment, declaration, and name of a variable, choose all the incorrect ones. The options are in [Exercise 5](Exercises.md#exercise-5-statements-about-variables).

### Solution

**Answer:** ④, ⑥

**Explanation:** A variable is a space for storing a value; it gives a name to a memory space so that the space can be accessed by name instead of by address. A variable must be declared with a data type and a name before it is used ([Chapter 2, Section 2.4](Concepts_Lecture.md#24-variables-in-io)).

- **① (correct):** A variable is a space for storing a value.
- **② (correct):** Declaring a variable allocates a memory space of the size of its data type and gives the variable name to that space. The program accesses the space by the variable name instead of the memory address.
- **③ (correct):** The assignment operator `=` stores the value on the right in the memory space of the variable written on the left (`count = 5;`). Unlike the equals sign in mathematics, it does not mean that two values are equal.
- **④ (incorrect):** The data type must be written when a variable is declared. The compiler needs the data type to decide the size of the memory to allocate and the meaning of the stored value (⑤).
- **⑤ (correct):** The data type determines the size of the memory space. `char` is 1 byte, `int` and `float` are usually 4 bytes, and `double` is 8 bytes ([Chapter 3, Section 1](../Ch03_Data-Types-and-Variables/Concepts_Lecture.md#1-data-types)).
- **⑥ (incorrect):** A variable must be declared before it is used. Assigning a value to an undeclared variable, as in `total = 5;`, leaves the compiler not knowing the name `total`, so clang reports the compile error "use of undeclared identifier 'total'".
- **⑦ (correct):** A variable name is an identifier, a name the programmer creates, and it follows the identifier rules: it is made of letters, digits, and underscores, and its first character must be a letter or an underscore ([Chapter 3, Section 3.2](../Ch03_Data-Types-and-Variables/Concepts_Lecture.md#32-identifiers-and-naming-rules)).

> **Note:** **Implicit `int`.** In C89, a declaration that has only a keyword such as `static` and no data type, as in `static count = 3;`, was treated as the declaration of an `int` variable (implicit int). C99 removed this rule, so the data type cannot be omitted. Compiling this declaration with macOS clang and `-std=c99` produces the error "type specifier missing, defaults to 'int'; ISO C99 and later do not support implicit int", while `-std=c89` produces only a warning with the same content.

---

<br>

## Exercise 6: Format Specifiers of `printf` and Their Meanings

**Textbook Problem:** Chapter 2 exercise 6

**Problem:** Match the `printf` format specifiers `%d`, `%f`, `%c`, `%x`, and `%e` with their meanings. The options are in [Exercise 6](Exercises.md#exercise-6-format-specifiers-of-printf-and-their-meanings).

### Solution

**Answer:** (1) ②, (2) ③, (3) ⑤, (4) ①, (5) ④

**Explanation:** A format specifier is a placeholder made of `%` and an agreed character, and `printf` converts the corresponding value to that format and prints it in place of the format specifier ([Chapter 2, Section 2.2](Concepts_Lecture.md#22-printf)).

| Format specifier | Meaning | Example | Output |
|:-----:|:-----|:-----|:-----|
| `%d` | ② Prints an integer in decimal | `printf("%d", 255);` | `255` |
| `%f` | ③ Prints a real number in floating-point notation | `printf("%f", 3.14);` | `3.140000` |
| `%c` | ⑤ Prints a character | `printf("%c", 'A');` | `A` |
| `%x` | ① Prints an integer in hexadecimal | `printf("%x", 255);` | `ff` |
| `%e` | ④ Prints a real number in exponential notation | `printf("%e", 3.14);` | `3.140000e+00` |

*Table 1. Meanings and sample outputs of `printf` format specifiers*

- **`%d` and `%x`:** Both print integers and differ only in the base. 255 is `255` in decimal and `ff` in hexadecimal. `%X` prints it in uppercase, as `FF`.
- **`%f` and `%e`:** Both print `float` and `double` values. `%f` is the notation without an exponent that writes 6 digits after the decimal point, as in `3.140000`, and `%e` is the notation with a mantissa and a power of 10, as in `3.140000e+00`. `e+00` means $\times 10^{0}$.
- **`%c`:** Prints the one character that corresponds to a character code. Printing the same `'A'` with `%d` prints its ASCII code `65` ([Chapter 3, Section 1.3](../Ch03_Data-Types-and-Variables/Concepts_Lecture.md#13-character-type)).

---

<br>

## Exercise 7: The Format Specifier That Produces the Output

**Textbook Problem:** Chapter 2 exercise 7

**Problem:** Fill in the blank of `printf` so that printing `float pi = 3.141592;` gives `pi = 3.14`. The full problem and source code are in [Exercise 7](Exercises.md#exercise-7-the-format-specifier-that-produces-the-output).

### Solution

**Answer:** `%.2f`

**Explanation:** The output `3.14` is the value of `pi` printed to 2 digits after the decimal point, so the answer is `%.2f`, which sets the precision to 2 ([Chapter 2, Section 2.2](Concepts_Lecture.md#22-printf)).

- **Conversion character `f`:** `pi` is a `float` variable. A `float` value is converted to `double` automatically when it is passed to `printf` as an argument, so both `float` and `double` are printed with `%f`.
- **Precision `.2`:** Writing `.2` between `%` and `f` rounds at the third digit after the decimal point and prints up to the second digit. 3.141592 becomes `3.14`. `%f` without a precision prints 6 digits after the decimal point, as in `3.141592`.
- **Field width:** Adding a field width, as in `%4.2f`, gives the same result because `3.14` is 4 characters long. With a larger width, `%6.2f` pads the front with spaces, as in `  3.14`.

The program with the blank filled in is as follows. It compiles with `gcc -std=c99 -Wall` without warnings, and running it prints the same output as the sample run. This code has no `return` statement, but since C99 `main` returns 0 when it reaches its end, so the program terminates normally (option ④ of Exercise 4).

**Code:**

```c
#include <stdio.h>

int main(void)
{
    float pi = 3.141592;
    printf("pi = %.2f\n", pi);
}
```

**Output:**

```text
pi = 3.14
```

---

<br>

## Exercise 8: Two Things Needed to Declare a Variable

**Textbook Problem:** Chapter 2 exercise 8

**Problem:** Write the two things needed to declare a variable. The full problem is in [Exercise 8](Exercises.md#exercise-8-two-things-needed-to-declare-a-variable).

### Solution

**Answer:** The data type and the variable name

**Explanation:** A declaration tells the compiler the data type and name of a variable ([Chapter 2, Section 2.4](Concepts_Lecture.md#24-variables-in-io)). In `int count;`, `int` is the data type and `count` is the variable name.

- **Data type:** The kind of data the variable stores, which determines the size of the memory space to allocate and the meaning of the stored value. `int` stores an integer, `double` a real number, and `char` a character.
- **Variable name:** The identifier that distinguishes the variable, by which the program accesses the variable's memory space.

An initial value is not required in a declaration; giving one with the declaration, as in `int count = 5;`, makes it an initialization. Several variables of the same data type can be declared at once by joining their names with commas, as in `int a, b, c;` ([Chapter 3, Section 3.1](../Ch03_Data-Types-and-Variables/Concepts_Lecture.md#31-declaration-and-initialization)).

---

<br>

## Exercise 9: The Header for the I/O Library

**Textbook Problem:** Chapter 2 exercise 9

**Problem:** Write the input/output library header needed to use `scanf` and `printf`. The full problem is in [Exercise 9](Exercises.md#exercise-9-the-header-for-the-io-library).

### Solution

**Answer:** `<stdio.h>`

**Explanation:** C has no built-in input/output keywords; instead, the input/output library provides input/output functions such as `printf` and `scanf`. The declarations of these functions are in `stdio.h`, the standard input/output header file, so it is included with `#include <stdio.h>` at the top of the source file ([Chapter 2, Section 2.1](Concepts_Lecture.md#21-console-io)).

- **Role of the header file:** A header file contains function declarations: the function name, return type, and parameters. When the preprocessor meets `#include`, it copies the contents of the header file into that place, and the compiler uses these declarations to check that the calls to `printf` and `scanf` are correct.
- **Definitions of the functions:** The header file has only declarations; the code that actually performs the functions is in the standard library and is connected to the executable file in the link step ([Chapter 1, Section 3.2](../Ch01_Programming-and-C-Language/Concepts_Lecture.md#32-build-process)).
- **Without the header:** If `#include <stdio.h>` is left out, the compiler does not know the declarations of `printf` and `scanf`, and an error or a warning occurs.

---

<br>

## Exercise 10: A Program That Reads and Prints a Character

**Textbook Problem:** Chapter 2 exercise 10

**Problem:** Fill in blanks ①, ②, and ③ of a program that reads one character with `scanf` and prints it with `printf`. The full problem and source code are in [Exercise 10](Exercises.md#exercise-10-a-program-that-reads-and-prints-a-character).

### Solution

**Answer:** ① `<stdio.h>`, ② `&ch`, ③ `%c`

**Explanation:** Using `scanf` and `printf` requires including the standard input/output header, `scanf` takes the address of a variable, and a `char` value is printed with `%c` ([Chapter 2, Section 2.3](Concepts_Lecture.md#23-scanf)).

- **① `<stdio.h>`:** The standard input/output header that contains the declarations of `scanf` and `printf` (Exercise 9). The `#define _CRT_SECURE_NO_WARNINGS` before it is a macro that prevents the error (C4996) Visual Studio reports when it treats `scanf` as an unsafe function, and it takes effect only when written before `#include`.
- **② `&ch`:** `scanf` needs the memory address at which to store the input value, so the address-of operator `&` is put before the variable name. Passing `ch` without `&` passes not an address but the value of `ch` (an uninitialized garbage value), which causes undefined behavior, and clang with `-Wall` warns "format specifies type 'char *' but the argument has type 'int'".
- **③ `%c`:** The format specifier that prints the one character stored in a `char` variable. Writing `%d` here prints the character's code (65 for `A`) instead of the character.

The program with the blanks filled in is as follows. It compiles with `gcc -std=c99 -Wall` without warnings, and entering `A` prints `ch = A`. This program prints no input prompt, so when it runs it waits for input on an empty line.

**Code:**

```c
// test.c
#define _CRT_SECURE_NO_WARNINGS     // needed to use scanf in Visual Studio 2022
#include <stdio.h>

int main(void)
{
    char ch;
    scanf("%c", &ch);
    printf("ch = %c\n", ch);
}
```

**Output:**

```text
A
ch = A
```

---

<br>

## Exercise 11: Printing Several Lines with One `printf`

**Textbook Problem:** Chapter 2 programming assignment 1

**Problem:** Using the `printf` statement only once, print the four lines `int main(void)`, `{`, `return 0;` (preceded by four spaces), and `}`. The full problem and sample run are in [Exercise 11](Exercises.md#exercise-11-printing-several-lines-with-one-printf).

### Solution

**Approach:** `printf` does not move to a new line automatically, so the four lines are put in one string, and the newline escape sequence `\n` is placed wherever a line ends ([Chapter 2, Section 2.2](Concepts_Lecture.md#22-printf)).

- **Newlines:** `"int main(void)\n{\n    return 0;\n}\n"` contains `\n` four times, so four lines are printed, and the last `\n` moves the cursor to the start of the next line.
- **Indentation:** The four spaces before `return 0;` are written in the string as they are. A tab character `\t` is usually displayed 8 columns wide in a console, which would differ from the sample run.
- **Characters to print and statements to execute:** The `return 0;` inside the double quotes is only characters to print, not a statement that is executed. What actually ends the program is the `return 0;` on the line after `printf`.

**Code:**

```c
#include <stdio.h>

int main(void)
{
    // One printf call prints all four lines; \n ends each line
    printf("int main(void)\n{\n    return 0;\n}\n");

    return 0;
}
```

**Output:** It compiles with `gcc -std=c99 -Wall` without warnings and prints the same four lines as the sample run.

```text
int main(void)
{
    return 0;
}
```

> **Note:** **Concatenation of string literals.** String literals that follow one another with only spaces or newlines between them are joined into one string at compile time. So splitting the string by output line, as below, is still a single call to `printf`, and the output is the same.

```c
printf("int main(void)\n"
       "{\n"
       "    return 0;\n"
       "}\n");
```

---

<br>

## Exercise 12: Printing a Decimal Integer in Hexadecimal

**Textbook Problem:** Chapter 2 programming assignment 2

**Problem:** Read a decimal integer and print it in hexadecimal. The full problem and sample run are in [Exercise 12](Exercises.md#exercise-12-printing-a-decimal-integer-in-hexadecimal).

### Solution

**Approach:** An integer is stored in memory in binary, and decimal and hexadecimal are only different ways of writing the same value as characters ([Chapter 3, Section 2.1](../Ch03_Data-Types-and-Variables/Concepts_Lecture.md#21-number-systems)). So the value is read once and stored in one variable, and the same variable is printed twice, with `%d` and with `%x` ([Chapter 2, Section 2.2](Concepts_Lecture.md#22-printf)).

- **Input:** `scanf("%d", &num);` interprets the typed characters `10` as a decimal number and stores the integer 10 in `num`.
- **Output:** `num` is matched to both `%d` and `%x` in the format string. 10 is the single hexadecimal digit `a`. To print hexadecimal digits in uppercase, use `%X`.

**Code:**

```c
#define _CRT_SECURE_NO_WARNINGS  // allows scanf in Visual Studio
#include <stdio.h>

int main(void)
{
    int num;

    printf("10진수 정수? ");
    scanf("%d", &num);                    // read a decimal integer

    // %d prints the value in decimal, %x prints the same value in hexadecimal
    printf("10진수 %d은 16진수 %x에 해당합니다.\n", num, num);

    return 0;
}
```

**Output:** It compiles with `gcc -std=c99 -Wall` without warnings and prints the same output as the sample run. Entering 171 prints the two-digit hexadecimal number `ab`, because 171 = 16 × 10 + 11.

```text
10진수 정수? 10
10진수 10은 16진수 a에 해당합니다.
```

```text
10진수 정수? 171
10진수 171은 16진수 ab에 해당합니다.
```

> **Caution:** **Negative input.** `%x` expects an `unsigned int` value, so for a negative input it prints the value obtained by reading the bit pattern as an unsigned integer. With a 32-bit `int`, -1 in two's complement has all bits set to 1, so `ffffffff` is printed ([Chapter 3, Section 2.2](../Ch03_Data-Types-and-Variables/Concepts_Lecture.md#22-integer-representation-twos-complement)).

```text
10진수 정수? -1
10진수 -1은 16진수 ffffffff에 해당합니다.
```

A similar problem that prints the input value in decimal, octal, and hexadecimal at once is [HW02 Problem 1](../../Coursework/HW02_Operators/Assignment-Explanation.md#2-problem-1-printing-a-value-in-different-bases).

---

<br>

## Exercise 13: Reading and Printing a Date

**Textbook Problem:** Chapter 2 programming assignment 3

**Problem:** Read the year, month, and day as integers and print the date. The full problem and sample run are in [Exercise 13](Exercises.md#exercise-13-reading-and-printing-a-date).

### Solution

**Approach:** Declare three `int` variables for the year, month, and day, and print a prompt such as `연? ` before reading each value. The prompt has no `\n`, so the cursor stays after the question mark and the value is typed there ([Chapter 2, Section 2.3](Concepts_Lecture.md#23-scanf)).

- **Input:** Pass the address of each variable with `&`, as in `scanf("%d", &year);`. The three values could be read with a single `scanf("%d %d %d", &year, &month, &day);`, but printing a prompt for each value, as in the sample run, requires splitting the input into three reads.
- **Output:** The three format specifiers correspond to the three variables in order. To match the sample run, one space is left after `일` before `입니다.` is printed.

**Code:**

```c
#define _CRT_SECURE_NO_WARNINGS  // allows scanf in Visual Studio
#include <stdio.h>

int main(void)
{
    int year, month, day;

    printf("연? ");
    scanf("%d", &year);
    printf("월? ");
    scanf("%d", &month);
    printf("일? ");
    scanf("%d", &day);

    printf("입력한 날짜는 %d년 %d월 %d일 입니다.\n", year, month, day);

    return 0;
}
```

**Output:** It compiles with `gcc -std=c99 -Wall` without warnings and prints the same output as the sample run.

```text
연? 2022
월? 10
일? 1
입력한 날짜는 2022년 10월 1일 입니다.
```

> **Caution:** **Checking the input values.** This program only reads integers and prints them; it does not check whether the values form a valid date. Entering -500, 15, and 55 for the year, month, and day prints "-500년 15월 55일" as it is. Checking that the month is 1-12 and that the day is within the number of days in that month requires the conditional statements of [Chapter 5, Section 2](../Ch05_Control-Statements/Concepts_Lecture.md#2-conditional-statements).

```text
연? -500
월? 15
일? 55
입력한 날짜는 -500년 15월 55일 입니다.
```

---

<br>

## Exercise 14: Printing Hours, Minutes, and Seconds in Two Digits

**Textbook Problem:** Chapter 2 programming assignment 4

**Problem:** Read the hours, minutes, and seconds and print each in two digits, so that 1 hour 1 minute 1 second is printed as "01:01:01". The full problem and sample run are in [Exercise 14](Exercises.md#exercise-14-printing-hours-minutes-and-seconds-in-two-digits).

### Solution

**Approach:** The input is read as in Exercise 13, and each value is printed in two digits. `%2d`, with a field width of 2, pads a one-digit number with a space in front, and `%02d`, with `0` before the width, pads it with 0 instead of a space ([Chapter 3, Section 5.2](../Ch03_Data-Types-and-Variables/Concepts_Lecture.md#52-width-and-alignment)).

| Value | `%d` | `%2d` | `%02d` |
|:---:|:---:|:---:|:---:|
| 1 | `1` | `␣1` | `01` |
| 13 | `13` | `13` | `13` |

*Table 2. Output with field width and zero padding (␣ is a space)*

- **`%02d`:** 1 is printed as `01`, and 13 is printed unchanged as `13`.
- **Separators:** The colons in the format string `"%02d:%02d:%02d"` are ordinary characters, so they are printed as they are.

**Code:**

```c
#define _CRT_SECURE_NO_WARNINGS  // allows scanf in Visual Studio
#include <stdio.h>

int main(void)
{
    int hour, minute, second;

    printf("시? ");
    scanf("%d", &hour);
    printf("분? ");
    scanf("%d", &minute);
    printf("초? ");
    scanf("%d", &second);

    // %02d: width 2, empty positions filled with 0
    printf("입력한 시간은 %02d:%02d:%02d입니다.\n", hour, minute, second);

    return 0;
}
```

**Output:** It compiles with `gcc -std=c99 -Wall` without warnings and prints the same output as the sample run. Entering 13, 5, and 9 pads only the one-digit minutes and seconds with 0.

```text
시? 1
분? 1
초? 1
입력한 시간은 01:01:01입니다.
```

```text
시? 13
분? 5
초? 9
입력한 시간은 13:05:09입니다.
```

> **Caution:** **The field width is a minimum width.** A value with more than two digits is printed in full without being cut, and the sign of a negative number takes one character. Entering 100, -5, and 7 prints "100:-5:07". This program also does not check that the hours are in the range 0-23 and the minutes and seconds in 0-59.

```text
시? 100
분? -5
초? 7
입력한 시간은 100:-5:07입니다.
```

A problem that practices field width, alignment, and zero padding together is [HW01 Q3](../../Coursework/HW01_Data-Types-and-Variables/Assignment-Explanation.md#33-q3-variable-practice-3).

---

<br>

## Exercise 15: Converting Dollars to Won

**Textbook Problem:** Chapter 2 programming assignment 5

**Problem:** Read an amount in dollars as a real number and print it converted to won at 1000 won per dollar, as an integer. The full problem and sample run are in [Exercise 15](Exercises.md#exercise-15-converting-dollars-to-won).

### Solution

**Approach:** The dollar amount is a real number with a decimal point, so it is read into a `double` variable with `%lf`, and the won amount is stored in an `int` variable and printed with `%d` ([Chapter 2, Section 2.3](Concepts_Lecture.md#23-scanf)).

- **Exchange rate constant:** The value of 1000 won per dollar is given a name with `#define WON_PER_DOLLAR 1000`. If the rate changes, only this line needs to be changed ([Chapter 3, Section 4.2](../Ch03_Data-Types-and-Variables/Concepts_Lecture.md#42-define-macro-constants)).
- **Input:** In `scanf`, a `double` is read with `%lf`, not `%f`.
- **Real to integer:** `dollars * WON_PER_DOLLAR` is a `double` value. Converting a real number to `int` discards the fractional part, so 0.5 is added before the `(int)` cast to round to the nearest integer ([Chapter 3, Section 6.2](../Ch03_Data-Types-and-Variables/Concepts_Lecture.md#62-explicit-conversion-casting)). This rounding holds when the amount is not negative, and the reason rounding is needed is in the caution box below.
- **Output:** The dollar amount is printed with `%.2f` so that the cents show, and the won amount with `%d`. The `$` in the format string is an ordinary character.

**Code:**

```c
#define _CRT_SECURE_NO_WARNINGS  // allows scanf in Visual Studio
#include <stdio.h>

#define WON_PER_DOLLAR 1000      // exchange rate: 1 dollar = 1000 won

int main(void)
{
    double dollars;
    int won;

    printf("달러? ");
    scanf("%lf", &dollars);              // %lf reads a double

    // add 0.5 before truncating to int so that 2009.9999... becomes 2010
    won = (int)(dollars * WON_PER_DOLLAR + 0.5);

    printf("$%.2f는 %d원입니다.\n", dollars, won);

    return 0;
}
```

**Output:** It compiles with `gcc -std=c99 -Wall` without warnings and, as in the sample run, prints 50.25 × 1000 = 50250 won. 2.01 dollars is also converted correctly to 2010 won.

```text
달러? 50.25
$50.25는 50250원입니다.
```

```text
달러? 2.01
$2.01는 2010원입니다.
```

> **Caution:** **Representation error of real numbers and discarding the fractional part.** Assigning without rounding, as in `won = dollars * WON_PER_DOLLAR;`, can give a result 1 won short. 2.01 cannot be represented exactly in binary, so it is stored in a `double` as 2.00999999999999978684..., and multiplying it by 1000 gives 2009.9999999999998, whose fractional part is discarded in the conversion to `int`, leaving 2009 ([Chapter 3, Section 1.2](../Ch03_Data-Types-and-Variables/Concepts_Lecture.md#12-floating-point-types)). The following is the result of entering 2.01 into a program that assigns without rounding.

```text
달러? 2.01
$2.01는 2009원입니다.
```

---

<br>

## Exercise 16: Choosing a Clothing Size

**Textbook Problem:** Chapter 2 programming assignment 6

**Problem:** Read a clothing size as one of the characters S, M, and L and print the chosen size. The full problem and sample run are in [Exercise 16](Exercises.md#exercise-16-choosing-a-clothing-size).

### Solution

**Approach:** A single character is stored in a `char` variable, and the format specifier `%c` is used for both input and output ([Chapter 2, Section 2.3](Concepts_Lecture.md#23-scanf)).

- **Input:** In `scanf(" %c", &size);`, the space before `%c` makes `scanf` skip all whitespace characters in the input, such as spaces, tabs, and newlines. Unlike the numeric format specifiers, `%c` does not skip whitespace, so without this space a space typed before `M` would be stored.
- **Output:** The character stored in `size` is printed in place of `%c`, followed by ` 사이즈를 선택했습니다.`.

**Code:**

```c
#define _CRT_SECURE_NO_WARNINGS  // allows scanf in Visual Studio
#include <stdio.h>

int main(void)
{
    char size;

    printf("옷 사이즈(S,M,L)? ");
    scanf(" %c", &size);                 // the space skips leading whitespace

    printf("%c 사이즈를 선택했습니다.\n", size);

    return 0;
}
```

**Output:** It compiles with `gcc -std=c99 -Wall` without warnings and prints the same output as the sample run.

```text
옷 사이즈(S,M,L)? M
M 사이즈를 선택했습니다.
```

> **Caution:** **Only one character is read.** `%c` reads only one character, so entering `XL` stores only `X` and leaves `L` in the input buffer. The program also does not check whether the input is one of S, M, and L, so a lowercase letter or any other character is printed as it is. Restricting the input to S, M, and L requires the conditional statements of [Chapter 5, Section 2](../Ch05_Control-Statements/Concepts_Lecture.md#2-conditional-statements).

```text
옷 사이즈(S,M,L)? XL
X 사이즈를 선택했습니다.
```

---

<br>

## Exercise 17: The Sum and Difference of Two Real Numbers

**Textbook Problem:** Chapter 2 programming assignment 7

**Problem:** Read two real numbers and print their sum and difference. The full problem and sample run are in [Exercise 17](Exercises.md#exercise-17-the-sum-and-difference-of-two-real-numbers).

### Solution

**Approach:** The two real numbers are read into `double` variables, and the sum and difference are computed directly in the argument positions of `printf` as `x + y` and `x - y` ([Chapter 2, Section 2.3](Concepts_Lecture.md#23-scanf)).

- **Input:** `scanf("%lf %lf", &x, &y);` reads two real numbers separated by whitespace in turn. They can be typed on one line with a space between them, as in `12.34 0.5`, or on two lines.
- **Output:** The `12.340000` in the sample run is the 6 digits after the decimal point that `%f` prints when no precision is given. Each line has three format specifiers, so `x`, `y`, and the result are passed in order.
- **`%lf` and `%f`:** A `double` is read with `%lf` in `scanf` and printed with `%f` in `printf`.

**Code:**

```c
#define _CRT_SECURE_NO_WARNINGS  // allows scanf in Visual Studio
#include <stdio.h>

int main(void)
{
    double x, y;

    printf("실수 2개? ");
    scanf("%lf %lf", &x, &y);            // %lf for double in scanf

    printf("%f + %f = %f\n", x, y, x + y);   // %f for double in printf
    printf("%f - %f = %f\n", x, y, x - y);

    return 0;
}
```

**Output:** It compiles with `gcc -std=c99 -Wall` without warnings and prints the same output as the sample run.

```text
실수 2개? 12.34 0.5
12.340000 + 0.500000 = 12.840000
12.340000 - 0.500000 = 11.840000
```

> **Caution:** **Reading a `double` with `%f` in `scanf`.** Writing `scanf("%f %f", &x, &y);` makes `scanf` store a value in `float` format in the memory of a `double` variable, which causes undefined behavior. Compiling with `-Wall`, clang warns "format specifies type 'float *' but the argument has type 'double *'", and running the program in this environment prints values unrelated to the input, as follows.

```text
실수 2개? 12.34 0.5
0.000000 + 0.000000 = 0.000000
0.000000 - 0.000000 = 0.000000
```

---

<br>

## Exercise 18: Printing Pi in Several Formats

**Textbook Problem:** Chapter 2 programming assignment 8

**Problem:** Print pi, 3.14159265, to 2, 4, 6, and 8 digits after the decimal point and in exponential notation, and compare storing it in a `float` variable with storing it in a `double` variable. The full problem and sample run are in [Exercise 18](Exercises.md#exercise-18-printing-pi-in-several-formats).

### Solution

**Approach:** The same value is printed five times with only the precision changed. The precision is written as `.` and an integer between `%` and `f`, and the value is rounded at the digit after the specified one ([Chapter 2, Section 2.2](Concepts_Lecture.md#22-printf)).

| Format specifier | Meaning | Output |
|:-----:|:-----|:-----|
| `%.2f` | 2 digits after the decimal point | `3.14` |
| `%.4f` | 4 digits after the decimal point | `3.1416` |
| `%f` | 6 digits after the decimal point (default) | `3.141593` |
| `%.8f` | 8 digits after the decimal point | `3.14159265` |
| `%e` | Exponential notation (6 digits after the decimal point of the mantissa) | `3.141593e+00` |

*Table 3. Format specifiers used to print pi*

- **Rounding:** Written to 4 digits after the decimal point, 3.14159265 is rounded up at the fifth digit, 9, to `3.1416`, and written to 6 digits, it is rounded up at the seventh digit, 6, to `3.141593`.
- **Exponential notation:** `3.141593e+00` is $3.141593 \times 10^{0}$.

**Code:**

```c
#include <stdio.h>

int main(void)
{
    double pi = 3.14159265;

    printf("pi = %.2f\n", pi);           // 2 digits after the decimal point
    printf("pi = %.4f\n", pi);           // 4 digits
    printf("pi = %f\n", pi);             // default precision: 6 digits
    printf("pi = %.8f\n", pi);           // 8 digits
    printf("pi = %e\n", pi);             // exponential notation

    return 0;
}
```

**Output:** It compiles with `gcc -std=c99 -Wall` without warnings and prints the same output as the sample run.

```text
pi = 3.14
pi = 3.1416
pi = 3.141593
pi = 3.14159265
pi = 3.141593e+00
```

**Comparing `float` and `double`:** Storing pi in a `float` variable changes the output with 8 digits after the decimal point. This is because a `float` has about 7 significant digits and a `double` about 15 ([Chapter 3, Section 1.2](../Ch03_Data-Types-and-Variables/Concepts_Lecture.md#12-floating-point-types)). The `float` value closest to 3.14159265 is 3.14159274101257324..., so `%.8f` prints `3.14159274`, whereas a `double` stores 3.14159265000000020862... and prints all 8 digits correctly. Up to 6 digits after the decimal point, the value fits within 7 significant digits, so the two outputs are the same. The following program prints a `float` variable with the same output statements.

```c
#include <stdio.h>

int main(void)
{
    float pi = 3.14159265f;              // f suffix: float literal

    printf("pi = %.2f\n", pi);           // a float argument is promoted to double
    printf("pi = %.4f\n", pi);
    printf("pi = %f\n", pi);
    printf("pi = %.8f\n", pi);
    printf("pi = %e\n", pi);

    return 0;
}
```

```text
pi = 3.14
pi = 3.1416
pi = 3.141593
pi = 3.14159274
pi = 3.141593e+00
```

- **`float` literal:** The suffix `f` in `3.14159265f` marks the literal as a `float`. Writing `float pi = 3.14159265;` without the suffix converts the `double` literal to `float` and stores the same value, and `-Wall` gives no warning for this conversion ([Chapter 3, Section 4.1](../Ch03_Data-Types-and-Variables/Concepts_Lecture.md#41-literal-constants)).
- **Output format specifiers:** A `float` argument is converted to `double` when it is passed to `printf`, so the two programs use the same format specifiers. This conversion does not restore precision that has already been lost.

---

<br>

## Exercise 19: Reading and Printing Octal, Decimal, and Hexadecimal Integers

**Textbook Problem:** Chapter 2 programming assignment 9

**Problem:** Read an integer in octal (`012`), decimal, or hexadecimal (`0x12`) and print it in octal, decimal, and hexadecimal. The full problem and sample run are in [Exercise 19](Exercises.md#exercise-19-reading-and-printing-octal-decimal-and-hexadecimal-integers).

### Solution

**Approach:** The input is read with `%i`, which decides the base from the prefix, and the output uses `%#o`, `%d`, and `%#x` ([Chapter 2, Section 2.3](Concepts_Lecture.md#23-scanf), [Chapter 3, Section 5.1](../Ch03_Data-Types-and-Variables/Concepts_Lecture.md#51-common-specifiers)).

- **`%i` input:** `%d` always interprets the input as decimal, but `%i`, like C integer constants, decides the base from the prefix. Input starting with `0x` or `0X` is read as hexadecimal, input starting with `0` as octal, and anything else as decimal. `0x12` is stored as 16 × 1 + 2 = 18.
- **`%#o` and `%#x` output:** `%o` prints in octal and `%x` in hexadecimal, and the `#` flag adds the same prefixes `0` and `0x` as in the input. Since 18 = 8 × 2 + 2, it is `022` in octal.
- **Alignment:** As in the sample run, one space is put before `8진수` so that its colon lines up with those of `10진수` and `16진수`.

**Code:**

```c
#define _CRT_SECURE_NO_WARNINGS  // allows scanf in Visual Studio
#include <stdio.h>

int main(void)
{
    int num;

    printf("8진수로 입력하려면 012, 16진수로 입력하려면 0x12처럼 입력하세요.\n");
    printf("정수? ");
    scanf("%i", &num);                   // %i accepts decimal, 012 (octal), 0x12 (hex)

    printf(" 8진수: %#o\n", num);        // # adds the prefix 0
    printf("10진수: %d\n", num);
    printf("16진수: %#x\n", num);        // # adds the prefix 0x

    return 0;
}
```

**Output:** It compiles with `gcc -std=c99 -Wall` without warnings, and entering `0x12` prints the same output as the sample run. The octal `012` is 8 × 1 + 2 = 10, and the decimal `18` is the same value as `0x12`.

```text
8진수로 입력하려면 012, 16진수로 입력하려면 0x12처럼 입력하세요.
정수? 0x12
 8진수: 022
10진수: 18
16진수: 0x12
```

```text
8진수로 입력하려면 012, 16진수로 입력하려면 0x12처럼 입력하세요.
정수? 012
 8진수: 012
10진수: 10
16진수: 0xa
```

```text
8진수로 입력하려면 012, 16진수로 입력하려면 0x12처럼 입력하세요.
정수? 18
 8진수: 022
10진수: 18
16진수: 0x12
```

> **Caution:** **Zero and digits that are not octal.** The `#` flag adds no prefix when the value is 0, so entering 0 prints `0` on all three lines. Also, `%i` reads input that starts with 0 as octal, so entering `09` stops reading before 9, which is not an octal digit, and the value becomes 0. A decimal number must be entered without a leading 0.

```text
8진수로 입력하려면 012, 16진수로 입력하려면 0x12처럼 입력하세요.
정수? 09
 8진수: 0
10진수: 0
16진수: 0
```

A similar problem that prints a value read in decimal with `%d`, `%#o`, and `%#x` is [HW02 Problem 1](../../Coursework/HW02_Operators/Assignment-Explanation.md#2-problem-1-printing-a-value-in-different-bases). That problem reads the input with `%d`, so an input such as `0x12` is read as 0.
