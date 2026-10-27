# Chapter 4 Solutions — Operators

[Repository Guide](../../README.md) | [English](Solutions.md) | [한국어](Solutions.ko.md)

> **Last Updated:** 2026-10-27
>
> Warming-Up C Programming, 천정아, Ch 4

**Problem Source:** Prof. Younghee Im, Computer Language Ⅰ (DCCS101-04)

---

<br>

## Table of Contents

- [Exercise 1: Volume and Surface Area of a Helmet](#exercise-1-volume-and-surface-area-of-a-helmet)
- [Exercise 2: Converting Between Time and Seconds](#exercise-2-converting-between-time-and-seconds)
- [Exercise 3: Convert Red, Green, and Blue Values to a Hexadecimal RGB Value](#exercise-3-convert-red-green-and-blue-values-to-a-hexadecimal-rgb-value)
- [Exercise 4: Convert a Hexadecimal RGB Value to Red, Green, and Blue Values](#exercise-4-convert-a-hexadecimal-rgb-value-to-red-green-and-blue-values)
- [Exercise 5: Statements About Operators](#exercise-5-statements-about-operators)
- [Exercise 6: Unary Operators](#exercise-6-unary-operators)
- [Exercise 7: Statements About Arithmetic Operators](#exercise-7-statements-about-arithmetic-operators)
- [Exercise 8: Result Types of Expressions](#exercise-8-result-types-of-expressions)
- [Exercise 9: Values of Expressions and Variables After Operations](#exercise-9-values-of-expressions-and-variables-after-operations)
- [Exercise 10: Statements About Relational and Logical Operators](#exercise-10-statements-about-relational-and-logical-operators)
- [Exercise 11: Data for Manipulating Specific Bits](#exercise-11-data-for-manipulating-specific-bits)
- [Exercise 12: Parenthesizing Expressions in Evaluation Order](#exercise-12-parenthesizing-expressions-in-evaluation-order)
- [Exercise 13: Computing an Entrance Fee with the Conditional Operator](#exercise-13-computing-an-entrance-fee-with-the-conditional-operator)
- [Exercise 14: Output of a Bitwise Operation Program](#exercise-14-output-of-a-bitwise-operation-program)
- [Exercise 15: Computing Density](#exercise-15-computing-density)
- [Exercise 16: Computing an Electricity Bill](#exercise-16-computing-an-electricity-bill)
- [Exercise 17: Computing an Electricity Bill with a Basic Charge](#exercise-17-computing-an-electricity-bill-with-a-basic-charge)
- [Exercise 18: Checking Whether a Month Value Is Valid](#exercise-18-checking-whether-a-month-value-is-valid)
- [Exercise 19: Converting Fahrenheit to Celsius](#exercise-19-converting-fahrenheit-to-celsius)
- [Exercise 20: Computing Kinetic Energy](#exercise-20-computing-kinetic-energy)
- [Exercise 21: Computing Percent Concentration](#exercise-21-computing-percent-concentration)
- [Exercise 22: Converting a Playback Time to Hours, Minutes, and Seconds](#exercise-22-converting-a-playback-time-to-hours-minutes-and-seconds)
- [Exercise 23: Computing a Discounted Price and the Discount Amount](#exercise-23-computing-a-discounted-price-and-the-discount-amount)
- [Exercise 24: Printing Each Byte in Hexadecimal](#exercise-24-printing-each-byte-in-hexadecimal)
- [Exercise 25: Building an RGB Color with Overflow Handling](#exercise-25-building-an-rgb-color-with-overflow-handling)

---

<br>

## Exercise 1: Volume and Surface Area of a Helmet

**Problem:** From the helmet height h and base radius a, read as integers, compute the volume $V = \frac{\pi}{6} h (3a^2 + h^2)$ and the surface area $S = 2\pi \left(\frac{h}{3} + \frac{V}{\pi h^2}\right) h$. Use 3.14159265, defined with `#define`, for π, and make sure no integer division occurs. The full problem and sample runs are in [Exercise 1](Exercises.md#exercise-1-volume-and-surface-area-of-a-helmet).

### Solution

**Approach:** The inputs are `int`, but the results have fractional parts, so every division must have at least one floating-point operand ([Chapter 4, Section 2.2](Concepts_Lecture.md#22-integer-division-vs-float-division)).

- **Macro constant:** `#define PI 3.14159265` defines π. The preprocessor replaces `PI` with the floating-point literal `3.14159265`, so any expression containing `PI` is computed in `double`.
- **Volume:** `(PI / 6.0 * height)` is a `double`, and the second parenthesized part `(3 * base_radius * base_radius + height * height)` is computed in `int` and then converted to `double` in the multiplication. The only division is `PI / 6.0`, and both of its operands are floating-point.
- **Surface area:** Writing the denominator as a floating-point literal, as in `height / 3.0`, avoids integer division. With `height / 3`, the term would be 0 for a height of 1 and the result would be wrong. In `volume / (PI * height * height)`, both the numerator and the denominator are `double`.
- **Output:** Since C99, `%lf` in `printf` means the same as `%f` and prints six digits after the decimal point.

Simplifying the formula gives $\frac{V}{\pi h^2} = \frac{3a^2 + h^2}{6h}$, so $S = 2\pi h \cdot \frac{a^2 + h^2}{2h} = \pi (a^2 + h^2)$, the curved surface area of a spherical cap. With the macro value 3.14159265 used as π, h = 1 and a = 1 give $2 \times 3.14159265 \approx 6.283185$, and h = 12 and a = 20 give $544 \times 3.14159265 \approx 1709.026402$, matching the sample runs.

**Code:** [Lab_Q1.c](../../Coursework/Lab04_Operators/Lab_Q1.c)

```c
/**
 * @file    A10104-1_C04Q1.c
 * @brief   Q1. 헬멧의 체적과 표면적 계산
 * @author  박철원 (Cheolwon Park)
 * @date    2024-03-26
 * 
 * @note    소스 코드에 사용된 scanf_s는 Visual Studio 이외의
 * 	    IDE에서 실행이 불가할 수 있음에 주의하시기 바랍니다.
 */

#include <stdio.h>
#define PI 3.14159265

int main()
{
	int height, base_radius;
	double volume, surface_area;

	printf("헬멧의 높이: ");
	scanf_s(" %d", &height);

	printf("base 반지름 입력: ");
	scanf_s(" %d", &base_radius);

	volume = (PI / 6.0 * height) * (3 * base_radius * base_radius + height * height);
	surface_area = 2.0 * PI * ((height / 3.0) + (volume / (PI * height * height))) * height;

	printf("헬멧의 체적: %lf \n", volume);
	printf("헬멧의 표면적: %lf \n", surface_area);
}
```

**Output:** Entering the same values as in the two sample runs prints the same volume and surface area. Because of the `" \n"` at the end of the format strings, the code leaves one trailing space at the end of each line. The last line of the sample runs, `Program ended with exit code: 0`, is not program output but the exit message added by the Xcode console.

```text
헬멧의 높이: 1
base 반지름 입력: 1
헬멧의 체적: 2.094395 
헬멧의 표면적: 6.283185 
```

```text
헬멧의 높이: 12
base 반지름 입력: 20
헬멧의 체적: 8444.601043 
헬멧의 표면적: 1709.026402 
```

> **Note:** **`scanf_s` and the build environment.** The `scanf_s` used by the code in this chapter is a function provided by Visual Studio (MSVC). The optional Annex K of C11 also defines a function with this name, but most standard libraries used with gcc and clang do not provide it, so compiling the code as is fails with an undeclared function error. With gcc and clang, the code compiles without changes as `gcc -std=c99 -Wall -Dscanf_s=scanf`, which replaces `scanf_s` with `scanf`. For conversions that read numbers, such as `%d` and `%x`, the two functions behave the same.

> **Caution:** If the height is 0, `volume / (PI * height * height)` divides 0 by 0, so the surface area is printed as `nan` (Not a Number). Floating-point division by zero does not stop the program but yields infinity or `nan`. Also, `3 * base_radius * base_radius` is computed in `int`, so it exceeds the range of `int` when a is greater than 26754.

```text
헬멧의 높이: 0
base 반지름 입력: 5
헬멧의 체적: 0.000000 
헬멧의 표면적: nan 
```

---

<br>

## Exercise 2: Converting Between Time and Seconds

**Textbook Problem:** Adapted from Chapter 4 programming assignment 8

**Problem:** Read hours, minutes, and seconds and convert them to total seconds, then read a total number of seconds and convert it to hours, minutes, and seconds. Use the symbolic constants `SEC_PER_HOUR` (3600) and `SEC_PER_MIN` (60). The full problem and sample runs are in [Exercise 2](Exercises.md#exercise-2-converting-between-time-and-seconds).

### Solution

**Approach:** The first conversion uses multiplication and addition, and the second uses the quotient and remainder of integer division ([Chapter 4, Section 2.3](Concepts_Lecture.md#23-modulo-operator)). Here, integer division, which discards the fractional part, is exactly the operation needed.

- **Hours, minutes, seconds to seconds:** `hour * SEC_PER_HOUR + min * SEC_PER_MIN + sec`. For 2 hours 10 minutes 47 seconds, this is 7200 + 600 + 47 = 7847 seconds.
- **Seconds to hours:** `second_sum2 / SEC_PER_HOUR` is the quotient in units of 3600 seconds. For 3989 seconds, it is 1 hour.
- **Seconds to minutes:** The seconds left after removing the hours, `second_sum2 % SEC_PER_HOUR`, divided by 60. 3989 % 3600 = 389, and 389 / 60 = 6 minutes.
- **Seconds to seconds:** `second_sum2 % SEC_PER_MIN`. Because 3600 is a multiple of 60, the remainder modulo 60 equals the remainder after removing the hours. 3989 % 60 = 29 seconds.

**Code:** [Lab_Q2.c](../../Coursework/Lab04_Operators/Lab_Q2.c)

```c
/**
 * @file    A10104-1_C04Q2.c
 * @brief   Q2. 시간 - 초 환산
 * @author  박철원 (Cheolwon Park)
 * @date    2024-03-27
 *  
 * @note    소스 코드에 사용된 scanf_s는 Visual Studio 이외의
 * 	    IDE에서 실행이 불가할 수 있음에 주의하시기 바랍니다.
 */

#define SEC_PER_HOUR 3600
#define SEC_PER_MIN 60
#include <stdio.h>

int main()
{
	int hour, min, sec;
	int hour_cal, min_cal, sec_cal;
	int second_sum1, second_sum2;

	printf("시간을 차례로 입력하세요(시,분,초): ");
	scanf_s(" %d %d %d", &hour, &min, &sec);

	second_sum1 = hour * SEC_PER_HOUR + min * SEC_PER_MIN + sec;

	printf("%d시간 %d분 %d초는 총 %d초입니다. \n", hour, min, sec, second_sum1);
	printf("\n---------------------------------\n");

	printf("환산할 초를 입력하세요: ");
	scanf_s(" %d", &second_sum2);

	hour_cal = (second_sum2 / SEC_PER_HOUR);
	min_cal = (second_sum2 % SEC_PER_HOUR) / SEC_PER_MIN;
	sec_cal = (second_sum2 % SEC_PER_MIN);

	printf("%d초는 %d시간 %d분 %d초입니다. \n", second_sum2, hour_cal, min_cal, sec_cal);
}
```

**Output:** The converted values match the two sample runs. However, the code prints an extra `"\n"` before the separator, so a blank line appears above it, and the separator has 33 `-` characters instead of the 35 in the sample runs. Each result line ends with one trailing space.

```text
시간을 차례로 입력하세요(시,분,초): 2 10 47
2시간 10분 47초는 총 7847초입니다. 

---------------------------------
환산할 초를 입력하세요: 3989
3989초는 1시간 6분 29초입니다. 
```

```text
시간을 차례로 입력하세요(시,분,초): 7 1 55
7시간 1분 55초는 총 25315초입니다. 

---------------------------------
환산할 초를 입력하세요: 25315
25315초는 7시간 1분 55초입니다. 
```

> **Note:** For a negative number of seconds, C99 integer division truncates toward zero and the sign of the remainder follows the dividend, so the hours, minutes, and seconds are all printed as negative numbers. The problem assumes an input of 0 or greater.

```text
시간을 차례로 입력하세요(시,분,초): 0 0 0
0시간 0분 0초는 총 0초입니다. 

---------------------------------
환산할 초를 입력하세요: -3725
-3725초는 -1시간 -2분 -5초입니다. 
```

---

<br>

## Exercise 3: Convert Red, Green, and Blue Values to a Hexadecimal RGB Value

**Problem:** Read Red, Green, and Blue values from 0 to 255, combine them into a single 4-byte RGB value in the layout of Figure 2, and print it as a 6-digit hexadecimal number. The full problem and sample runs are in [Exercise 3](Exercises.md#exercise-3-convert-red-green-and-blue-values-to-a-hexadecimal-rgb-value).

### Solution

**Approach:** Shift each channel left into its position and combine them with bitwise OR ([Chapter 4, Section 6.3](Concepts_Lecture.md#63-practical-example-rgb-color)). Red moves by 0 bits, Green by 8 bits, and Blue by 16 bits.

- **Combining:** `RGB = red | green << 8 | blue << 16;` has no parentheses, but `<<` has higher precedence than `|`, so it is computed as `red | (green << 8) | (blue << 16)` ([Chapter 4, Section 10.1](Concepts_Lecture.md#101-precedence-table)). Because the 1 bits of the three values do not overlap, OR gives the same result as addition. The three commented-out `|=` lines perform the same process with compound assignment.
- **Output:** In `%#08X`, `#` adds `0X` in front of the hexadecimal number, `0` pads empty positions with 0, and the width 8 counts all characters including `0X`. The hexadecimal part therefore has 6 digits, printed as `0X8200FF` and `0X0DC843`.

**Code:** [Lab_Q3.c](../../Coursework/Lab04_Operators/Lab_Q3.c)

```c
/**
 * @file    A10104-1_C04Q3.c
 * @brief   Q3. 4바이트 RGB값을 16진수 RGB값으로 변환
 * @author  박철원 (Cheolwon Park)
 * @date    2024-03-27
 *  
 * @note    소스 코드에 사용된 scanf_s는 Visual Studio 이외의
 * 	    IDE에서 실행이 불가할 수 있음에 주의하시기 바랍니다.
 */

#include <stdio.h>

int main()
{
	int red, green, blue;
	int RGB = 0;

	printf("Red 값 입력(0~255): ");
	scanf_s(" %d", &red);
	printf("Green 값 입력(0~255): ");
	scanf_s(" %d", &green);
	printf("Blue 값 입력(0~255): ");
	scanf_s(" %d", &blue);

	RGB = red | green << 8 | blue << 16;

	/* 위와 동일한 과정
	RGB |= blue << 16;
	RGB |= green << 8;
	RGB |= red; */

	printf("RGB = %#08X", RGB);
}
```

**Output:** The RGB values match the two sample runs. The input prompts read `(0~255)` instead of `(0-255)`, the code prints no blank line before `RGB =`, and it prints no newline after the last line.

```text
Red 값 입력(0~255): 255
Green 값 입력(0~255): 0
Blue 값 입력(0~255): 130
RGB = 0X8200FF
```

```text
Red 값 입력(0~255): 67
Green 값 입력(0~255): 200
Blue 값 입력(0~255): 13
RGB = 0X0DC843
```

> **Caution:** **Boundary inputs.** The `#` flag adds no prefix when the value is 0, so if all three values are 0, the output is `00000000` rather than `0X000000`. Also, there is no range check, so a value greater than 255 spills into the bits of the neighboring channel. Entering 256 for Red sets bit 8 and gives `0X000100`, the same as Green being 1.

```text
Red 값 입력(0~255): 0
Green 값 입력(0~255): 0
Blue 값 입력(0~255): 0
RGB = 00000000
```

```text
Red 값 입력(0~255): 256
Green 값 입력(0~255): 0
Blue 값 입력(0~255): 0
RGB = 0X000100
```

---

<br>

## Exercise 4: Convert a Hexadecimal RGB Value to Red, Green, and Blue Values

**Problem:** Read a 6-digit hexadecimal RGB value, extract the Red, Green, and Blue values, and print each as a 2-digit hexadecimal value and a decimal value. The full problem and sample runs are in [Exercise 4](Exercises.md#exercise-4-convert-a-hexadecimal-rgb-value-to-red-green-and-blue-values).

### Solution

**Approach:** Shift the desired channel right into the low 8 bits and clear the remaining bits with `& 0xFF` ([Chapter 4, Section 6.3](Concepts_Lecture.md#63-practical-example-rgb-color)).

- **Input:** `%x` reads a hexadecimal number and accepts both uppercase and lowercase digits. `A73803` is stored as the decimal value 10958851.
- **Red:** `RGB & 0xFF` extracts the low 8 bits, `0x03`.
- **Green:** `(RGB >> 8) & 0xFF` moves bits 8-15 down and extracts them. The low 8 bits of `0xA738`, `0x38`, remain.
- **Blue:** Only `RGB >> 16` is applied, without a mask. For an input of at most 6 digits, bits 24 and above are 0, so only `0xA7` remains.
- **Output:** `%#04x` prints with a width of 4 including `0x`, so the hexadecimal part has 2 digits.

**Code:** [Lab_Q4.c](../../Coursework/Lab04_Operators/Lab_Q4.c)

```c
/**
 * @file    A10104-1_C04Q4.c
 * @brief   Q4. 16진수 RGB값을 4바이트 RGB값으로 변환
 * @author  박철원 (Cheolwon Park)
 * @date    2024-03-27
 *  
 * @note    소스 코드에 사용된 scanf_s는 Visual Studio 이외의
 * 	    IDE에서 실행이 불가할 수 있음에 주의하시기 바랍니다.
 */

#include <stdio.h>

int main()
{
	int RGB = 0;
	int red, green, blue;

	printf("RGB 값을 입력(16진수 6자리): ");
	scanf_s(" %x", &RGB);

	red = (RGB & 0xFF);
    // AND 연산을 이용하여 0~7번째 비트(하위 8비트) 추출
    // 예: 00000000 00000000 11111111 => 0x0000FF => 255

    green = ((RGB >> 8) & 0xFF);
    // RGB를 오른쪽으로 8비트 시프트한 뒤
    // AND 연산으로 0~7번째 비트(녹색 정보) 추출

    blue = (RGB >> 16);
    // RGB를 오른쪽으로 16비트 시프트하여
    // 하위 8비트(파란색 정보)만 남김

	printf("\nRed    = %#04x (%d) \n", red, red);
	printf("Green  = %#04x (%d) \n", green, green);
	printf("Blue   = %#04x (%d) \n", blue, blue);
} 
```

**Output:** The extracted values match the two sample runs. The output format differs as follows. Because the conversion specifier is a lowercase `x`, the output is lowercase, as in `0x03` instead of `0X03`, and the number of spaces after `Red`, `Green`, and `Blue`, the space before the parenthesis, and the trailing space also differ from the sample runs. In the second run, where Green is 0, the `#` flag adds no prefix to 0, so `0000` is printed instead of `0x00`. The input prompt reads `RGB 값을 입력`.

```text
RGB 값을 입력(16진수 6자리): A73803

Red    = 0x03 (3) 
Green  = 0x38 (56) 
Blue   = 0xa7 (167) 
```

```text
RGB 값을 입력(16진수 6자리): FF00DD

Red    = 0xdd (221) 
Green  = 0000 (0) 
Blue   = 0xff (255) 
```

> **Note:** `%x` in `scanf` expects an `unsigned int *`, so declaring `RGB` as `unsigned int` would be precise. Also, because Blue is not masked, entering 7 or more digits mixes the upper bits into Blue. Entering `1A73803` makes Blue `0x1a7` (423), whereas masking with `(RGB >> 16) & 0xFF` would keep only the low 8 bits even in this case.

```text
RGB 값을 입력(16진수 6자리): 1A73803

Red    = 0x03 (3) 
Green  = 0x38 (56) 
Blue   = 0x1a7 (423) 
```

---

<br>

## Exercise 5: Statements About Operators

**Textbook Problem:** Chapter 4 exercise 1

**Problem:** Of eight statements about operators, operands, and operator expressions, choose all the incorrect ones. The options are in [Exercise 5](Exercises.md#exercise-5-statements-about-operators).

### Solution

**Answer:** ④, ⑤, ⑥, ⑧

**Explanation:** An operator is a symbol that performs an operation on one or more operands, and an operator expression made of operators and operands is an expression that has a value ([Chapter 4, Section 1.1](Concepts_Lecture.md#11-expressions), [Section 1.2](Concepts_Lecture.md#12-operators-and-operands)).

- **① (correct):** An operator is a symbol that denotes an operation, such as `+`, `=`, or `&&`. Some operators, such as `sizeof`, are keywords.
- **② (correct):** A value that is the target of an operation, such as `a` and `b` in `a + b`, is called an operand.
- **③ (correct):** An operator expression is an expression, and every expression has a type and a value. An assignment such as `x = 5` is also an expression whose value is 5.
- **④ (incorrect):** An operand is the target of an operation, so there is no operator without operands. Depending on its kind, a C operator has 1 (unary), 2 (binary), or 3 (ternary) operands.
- **⑤ (incorrect):** In C, the programmer cannot define new operators. `#` is the symbol that marks preprocessor directives such as `#include` and `#define`, and the `#` used inside a macro definition is also a feature that the preprocessor defines in advance.
- **⑥ (incorrect):** `^` is the bitwise XOR operator, which compares the bits of two operands, so it is a binary operator ([Chapter 4, Section 6.1](Concepts_Lecture.md#61-bitwise-and-or-xor-not)).
- **⑦ (correct):** The comma (`,`) is the operator with the lowest precedence ([Chapter 4, Section 10.1](Concepts_Lecture.md#101-precedence-table)). `a, b` evaluates `a` first and then `b`, and the value of the whole expression is the value of `b`. However, a comma that separates variables in a declaration such as `int x, y;` or separates the arguments of a function is a separator, not an operator.
- **⑧ (incorrect):** An operator expression has a value, so it can be used as part of another expression. `y = (x = 5) + 1;` adds 1 to 5, the value of the assignment `x = 5`, and assigns 6 to `y`, and `printf("%d\n", x = 5);` prints 5, the value of the assignment.

> **Note:** ③ is a statement about operators that produce values. An expression that calls a function whose return type is `void` contains the function call operator `()` but has no value, so it cannot be used as an operand of another expression. Return types of functions are covered in Chapter 6.

---

<br>

## Exercise 6: Unary Operators

**Textbook Problem:** Chapter 4 exercise 2

**Problem:** Of ten operators, choose all the unary operators. The options are in [Exercise 6](Exercises.md#exercise-6-unary-operators).

### Solution

**Answer:** ①, ②, ③, ④, ⑤, ⑧

**Explanation:** A unary operator is an operator with one operand ([Chapter 4, Section 1.2](Concepts_Lecture.md#12-operators-and-operands)). The operators grouped at level 2 of the precedence table, such as `++x`, `--x`, `+x`, `-x`, `!`, `~`, `(type)`, and `sizeof`, and the postfix increment and decrement operators `x++` and `x--` at level 1 are unary operators ([Chapter 4, Section 10.1](Concepts_Lecture.md#101-precedence-table)).

- **① (unary):** Used as a sign operator, as in `+x`, it is a unary operator. With two operands, as in `a + b`, it is the binary operator for addition ([Chapter 4, Section 2.1](Concepts_Lecture.md#21-operators)).
- **② (unary):** Used as the operator that negates the sign, as in `-x`, it is a unary operator. The subtraction in `a - b` is a binary operator.
- **③ (unary):** The increment operator `++` acts on a single variable, as in `++x` and `x++`.
- **④ (unary):** The logical NOT `!` reverses the truth value of one operand.
- **⑤ (unary):** `sizeof` is a unary operator written as a keyword, and it gives the size of one operand (`sizeof x`, `sizeof(int)`) in bytes.
- **⑥ (binary):** The shift operator `<<` has two operands, as in `x << n`.
- **⑦ (binary):** The logical AND `&&` combines two operands.
- **⑧ (unary):** The bitwise NOT `~` inverts all the bits of one operand.
- **⑨ (binary):** The compound assignment operator `*=` has the variable on the left and the value on the right as its operands, as in `x *= y`.
- **⑩ (binary):** The equality operator `==` compares two values.

---

<br>

## Exercise 7: Statements About Arithmetic Operators

**Textbook Problem:** Chapter 4 exercise 3

**Problem:** Of seven statements about arithmetic operators, choose all the incorrect ones. The options are in [Exercise 7](Exercises.md#exercise-7-statements-about-arithmetic-operators).

### Solution

**Answer:** ③, ④, ⑥

**Explanation:** The arithmetic operators are the binary operators `+`, `-`, `*`, `/`, and `%` and the unary operators `+x` and `-x`, and integer and floating-point operations are distinguished by the types of the operands ([Chapter 4, Section 2.1](Concepts_Lecture.md#21-operators), [Section 2.2](Concepts_Lecture.md#22-integer-division-vs-float-division)).

- **① (correct):** The binary arithmetic operators are `+`, `-`, `*`, `/`, and `%`. This option does not list the sign operators, but it does not claim that these five are the only arithmetic operators, and all five listed operators are arithmetic operators, so the statement is correct.
- **② (correct):** With a single operand, `+` and `-` are used as sign operators (`+x`, `-x`).
- **③ (incorrect):** When both operands are integers, integer division is performed, giving the integer quotient with the fractional part truncated. `7 / 2` is 3, not 3.5.
- **④ (incorrect):** `%` can be used only on integer operands, and `7.5 % 2.0` is a compile error ([Chapter 4, Section 2.3](Concepts_Lecture.md#23-modulo-operator)). The remainder of floating-point numbers is computed with the `fmod` function of `<math.h>`.
- **⑤ (correct):** If one of the two operands of a binary operator has a floating-point type, the other operand is also converted to a floating-point type before the operation. In `5 + 2.5`, 5 is converted to 5.0 ([Chapter 4, Section 9.1](Concepts_Lecture.md#91-implicit-promotion)).
- **⑥ (incorrect):** Even when the two operands have the same type, `char` and `short` are converted to `int` by integer promotion before the operation. With `char a = 10, b = 20;`, the type of `a + b` is `int`, not `char` ([Chapter 4, Section 9.1](Concepts_Lecture.md#91-implicit-promotion), [Section 9.3](Concepts_Lecture.md#93-sizeof-of-expression-result)).
- **⑦ (correct):** `*`, `/`, and `%` are at precedence level 3 and `+` and `-` are at level 4, so the multiplicative operators bind first. `2 + 3 * 4` is 14 ([Chapter 4, Section 10.1](Concepts_Lecture.md#101-precedence-table)).

---

<br>

## Exercise 8: Result Types of Expressions

**Textbook Problem:** Chapter 4 exercise 4

**Problem:** Write the result types of six expressions made of constants and `char` and `short` variables. The expressions are in [Exercise 8](Exercises.md#exercise-8-result-types-of-expressions).

### Solution

**Answer:** (1) `double`, (2) `double`, (3) `double`, (4) `int`, (5) `int`, (6) `int`

**Explanation:** A floating-point constant without a suffix has type `double`, a floating-point constant with the suffix `F` has type `float`, and an integer constant has type `int`. The two operands of a binary operation are brought to the larger type, and `char` and `short` are first promoted to `int` ([Chapter 4, Section 9.1](Concepts_Lecture.md#91-implicit-promotion)).

- **(1) `double`:** `1` is an `int` and `0.5` is a `double`, so `1` is converted to `double`.
- **(2) `double`:** `1.01F` is a `float` and `0.5` is a `double`, so the `float` value is converted to `double`.
- **(3) `double`:** `0.5F` is a `float` and `2.4` is a `double`, so the result is a `double`. The result type is the larger type regardless of the order of the operands.
- **(4) `int`:** Both operands are `int`, so the result is also an `int`.
- **(5) `int`:** `ch` is promoted to `int` and `1` is an `int`, so the result is an `int`. Its value is 98, the ASCII code 97 of `'a'` plus 1.
- **(6) `int`:** `a` and `b` are both `short`, but integer promotion makes them `int`, so the result is an `int`. Its value is -10.

Applying `sizeof` to each expression confirms this through the size of the result type ([Chapter 4, Section 9.3](Concepts_Lecture.md#93-sizeof-of-expression-result)). In an environment where `double` is 8 bytes and `int` is 4 bytes, `sizeof` of the six expressions is 8, 8, 8, 4, 4, and 4 in order.

---

<br>

## Exercise 9: Values of Expressions and Variables After Operations

**Textbook Problem:** Chapter 4 exercise 5

**Problem:** Starting from `int x = 1, y = 2, z = 3;` each time, perform each of twelve operations and write the value of the expression and the values of `x`, `y`, and `z`. The expressions are in [Exercise 9](Exercises.md#exercise-9-values-of-expressions-and-variables-after-operations).

### Solution

**Answer:** The result of each operation is shown in Table 1.

| Item | Expression | Value of the expression | `x` | `y` | `z` |
|:-----|:-----|:-----:|:-----:|:-----:|:-----:|
| (1) | `z % y` | 1 | 1 | 2 | 3 |
| (2) | `++y` | 3 | 1 | 3 | 3 |
| (3) | `z = x--` | 1 | 0 | 2 | 1 |
| (4) | `z = y = x` | 1 | 1 | 1 | 1 |
| (5) | `z *= x` | 3 | 1 | 2 | 3 |
| (6) | `z *= y + 1` | 9 | 1 | 2 | 9 |
| (7) | `x > z && y < z` | 0 | 1 | 2 | 3 |
| (8) | `! x \|\| y < z` | 1 | 1 | 2 | 3 |
| (9) | `x && y` | 1 | 1 | 2 | 3 |
| (10) | `z << y` | 12 | 1 | 2 | 3 |
| (11) | `x \|= z` | 3 | 3 | 2 | 3 |
| (12) | `y = x + 1 > z ? y : y - 1` | 1 | 1 | 1 | 3 |

*Table 1. Value of each expression and values of the variables after each operation*

**Explanation:** The value of an assignment or compound assignment is the assigned value, and the value of a relational or logical expression is 1 or 0 ([Chapter 4, Section 4.2](Concepts_Lecture.md#42-result-type), [Section 5.4](Concepts_Lecture.md#54-truthiness-in-c)).

- **(1):** `%` is the remainder operator, so 3 % 2 = 1. No variable changes ([Chapter 4, Section 2.3](Concepts_Lecture.md#23-modulo-operator)).
- **(2):** The prefix increment `++y` increases `y` to 3 and then gives the increased value 3 as the value of the expression ([Chapter 4, Section 3.1](Concepts_Lecture.md#31-prefix-vs-postfix)).
- **(3):** The postfix decrement `x--` gives the current value 1 of `x` as the value of the expression and then decreases `x` to 0. Therefore 1 is assigned to `z`, and the value of the assignment is also 1.
- **(4):** The assignment operator associates from right to left, so this is `z = (y = x)`. 1 is assigned to `y`, and the value 1 of that assignment is then assigned to `z` ([Chapter 4, Section 7.2](Concepts_Lecture.md#72-chained-assignment)).
- **(5):** `z *= x` is `z = z * x`, so 3 * 1 = 3 is assigned to `z` and the value stays the same.
- **(6):** The compound assignment operator has lower precedence than `+`, so this is `z *= (y + 1)`, that is, `z = z * (y + 1)` = 3 * 3 = 9 ([Chapter 4, Section 7.1](Concepts_Lecture.md#71-simple-and-compound-assignment)). It differs from `z = z * y + 1` (= 7).
- **(7):** `x > z` is 1 > 3, which is false (0). When the left operand of `&&` is 0, the right operand `y < z` is not evaluated and the result is fixed at 0 ([Chapter 4, Section 5.3](Concepts_Lecture.md#53-short-circuit-evaluation)).
- **(8):** `!` has higher precedence than `<` and `||`, so this is `(!x) || (y < z)`. `!x` is `!1` = 0, so the right operand `y < z` (2 < 3, true) is evaluated, and the result is 1.
- **(9):** Both `x` and `y` are nonzero, so the expression is true, and the result of the logical operation is 1. The result is 1, not 2, the value of `y`.
- **(10):** `z << y` shifts 3 left by 2 bits, so binary `11` becomes `1100`, which is $3 \times 2^2 = 12$ ([Chapter 4, Section 6.2](Concepts_Lecture.md#62-shift-operators)). The shift does not change `z`.
- **(11):** `x |= z` is `x = x | z`, so binary `01 | 11` = `11`, that is, 3 is assigned to `x` ([Chapter 4, Section 6.1](Concepts_Lecture.md#61-bitwise-and-or-xor-not)).
- **(12):** The precedence order is `+`, `>`, `?:`, `=`, so this is `y = (((x + 1) > z) ? y : (y - 1))`. `x + 1 > z` is 2 > 3, which is false, so `y - 1` = 1 is selected and assigned to `y` ([Chapter 4, Section 8.1](Concepts_Lecture.md#81-ternary-operator), [Section 10.1](Concepts_Lecture.md#101-precedence-table)).

A similar problem that prints the values of relational and logical operators is in [HW03 Problem 1](../../Coursework/HW03_Control-Statements-I/Assignment-Explanation.md#2-problem-1-values-of-operators), and a problem that traces increment, decrement, and assignment statement by statement is in [HW03 Problem 3](../../Coursework/HW03_Control-Statements-I/Assignment-Explanation.md#4-problem-3-increment-decrement-and-assignment).

---

<br>

## Exercise 10: Statements About Relational and Logical Operators

**Textbook Problem:** Chapter 4 exercise 6

**Problem:** Of eight statements about relational and logical operators, choose all the incorrect ones. The options are in [Exercise 10](Exercises.md#exercise-10-statements-about-relational-and-logical-operators).

### Solution

**Answer:** ②, ⑤, ⑥, ⑦

**Explanation:** A relational operator compares two values and gives 1 if the comparison is true and 0 if it is false, and a logical operator treats nonzero values as true and 0 as false and gives 1 or 0 as its result ([Chapter 4, Section 4.2](Concepts_Lecture.md#42-result-type), [Section 5.4](Concepts_Lecture.md#54-truthiness-in-c)).

- **① (correct):** Operators that compare two values, such as `>`, `<`, `>=`, `<=`, `==`, and `!=`, are relational operators ([Chapter 4, Section 4.1](Concepts_Lecture.md#41-comparison-operators)).
- **② (incorrect):** `=` is the assignment operator, and the operator that compares whether two values are equal is `==` ([Chapter 4, Section 4.3](Concepts_Lecture.md#43-common-mistake--vs-)).
- **③ (correct):** The result of `!`, `&&`, and `||` is always the `int` value 0 or 1, regardless of the values of the operands.
- **④ (correct):** The relational operators (precedence levels 6 and 7) have higher precedence than the binary logical operators `&&` (11) and `||` (12), so `a > 0 && b > 0` is computed as `(a > 0) && (b > 0)` ([Chapter 4, Section 10.1](Concepts_Lecture.md#101-precedence-table)).
- **⑤ (incorrect):** `~` is the bitwise NOT operator, which inverts all bits, and the logical NOT operator is `!`. In two's complement representation, `~1` is -2, but `!1` is 0 ([Chapter 4, Section 6.1](Concepts_Lecture.md#61-bitwise-and-or-xor-not)).
- **⑥ (incorrect):** C treats every nonzero value as true. 2 and -5 are also true, so `2 && -5` is 1.
- **⑦ (incorrect):** `!expr` becomes 1 when `expr` is 0, so it replaces `expr == 0`. `expr != 0` becomes 1 when `expr` is nonzero, so as a condition, writing just `expr` has the same meaning.
- **⑧ (correct):** `&&` (precedence level 11) has higher precedence than `||` (12), so `a || b && c` is grouped as `a || (b && c)`.

> **Note:** **Precedence and evaluation order.** The order of performing that ④ and ⑧ describe means operator precedence, that is, which operator an operand is bound to first. Among the logical operators, the unary operator `!` has higher precedence than the relational operators, so `!x < y` is computed as `(!x) < y`, and ④ is a statement about the binary logical operators `&&` and `||`. Also, `&&` and `||` always evaluate the left operand first, so `a || b && c` is grouped as `a || (b && c)`, but `a` is evaluated first, and if `a` is true, `b && c` is not evaluated ([Chapter 4, Section 5.3](Concepts_Lecture.md#53-short-circuit-evaluation)).

---

<br>

## Exercise 11: Data for Manipulating Specific Bits

**Textbook Problem:** Chapter 4 exercise 7

**Problem:** Write the name of the data used in bitwise logical operations to manipulate specific bit values. The full problem is in [Exercise 11](Exercises.md#exercise-11-data-for-manipulating-specific-bits).

### Solution

**Answer:** Bitmask or mask

**Explanation:** A bitmask is a value used as one operand of a bitwise logical operator `&`, `|`, or `^` to extract, set, clear, or invert only specific bits of the other operand ([Chapter 4, Section 6.3](Concepts_Lecture.md#63-practical-example-rgb-color)). The 1 bits of the mask mark the positions to manipulate.

- **Extracting bits:** `x & 0xFF` keeps only the positions where the mask `0xFF` (binary `1111 1111`) has 1, that is, the lower 8 bits, and sets the other bits to 0.
- **Setting a bit:** `x | 0x80` sets bit 7 to 1 and leaves the other bits as they are.
- **Clearing a bit:** `x & ~0x80` sets only bit 7 to 0 and leaves the other bits as they are.
- **Inverting bits:** `x ^ 0x0F` inverts only the lower 4 bits.

---

<br>

## Exercise 12: Parenthesizing Expressions in Evaluation Order

**Textbook Problem:** Chapter 4 exercise 8

**Problem:** Enclose the operations of ten expressions in `()` in the order in which they are performed. The expressions are in [Exercise 12](Exercises.md#exercise-12-parenthesizing-expressions-in-evaluation-order).

### Solution

**Answer:** The parenthesized form of each expression is shown in Table 2.

| Item | Expression | Parenthesized expression | Binding order (precedence) |
|:-----|:-----|:-----|:-----|
| (1) | `x - y / 3` | `(x - (y / 3))` | `/` (3), then `-` (4). |
| (2) | `x < 0 \|\| x > 100` | `((x < 0) \|\| (x > 100))` | `<` and `>` (6), then `\|\|` (12). |
| (3) | `x == 0 \|\| y == 0 && z == 1` | `((x == 0) \|\| ((y == 0) && (z == 1)))` | `==` (7), `&&` (11), then `\|\|` (12). |
| (4) | `x = a > b` | `(x = (a > b))` | `>` (6), then `=` (14). |
| (5) | `!x && !y` | `((!x) && (!y))` | `!` (2), then `&&` (11). |
| (6) | `x += y * 2` | `(x += (y * 2))` | `*` (3), then `+=` (14). |
| (7) | `~x & y` | `((~x) & y)` | `~` (2), then `&` (8). |
| (8) | `x < 0 \|\| ! y && z` | `((x < 0) \|\| ((!y) && z))` | `!` (2), `<` (6), `&&` (11), then `\|\|` (12). |
| (9) | `x = x > 0 ? y + 1 : z + 2` | `(x = ((x > 0) ? (y + 1) : (z + 2)))` | `+` (4), `>` (6), `?:` (13), then `=` (14). |
| (10) | `z = (double) x / y` | `(z = (((double) x) / y))` | Cast (2), `/` (3), then `=` (14). |

*Table 2. Expressions parenthesized in the order of their operations*

**Explanation:** Operators with higher precedence are bound to their operands first, and operators with the same precedence follow their associativity ([Chapter 4, Section 10.1](Concepts_Lecture.md#101-precedence-table), [Section 10.2](Concepts_Lecture.md#102-associativity)). The numbers in parentheses in Table 2 are the levels in the precedence table of Chapter 4, Section 10.1, and the outermost parentheses of each expression mark the operation performed last, so they may be omitted.

- **(3) and (8):** It is tempting to group from left to right, but `&&` has higher precedence than `||`, so the `&&` on the right is bound first. Grouping (3) as `((x == 0) || (y == 0)) && (z == 1)` gives a different result when `x` is 0 and `z` is not 1.
- **(10):** The cast applies only to the operand right after it, `x`, so `x` is converted to `double` and then floating-point division is performed ([Chapter 4, Section 9.2](Concepts_Lecture.md#92-cast-operator)).

---

<br>

## Exercise 13: Computing an Entrance Fee with the Conditional Operator

**Textbook Problem:** Chapter 4 exercise 9

**Problem:** Fill in the blank of `fee = ____;` with the conditional operator so that the fee is 70,000 won in the peak season (June-August) and 35,000 won otherwise. The full problem and code are in [Exercise 13](Exercises.md#exercise-13-computing-an-entrance-fee-with-the-conditional-operator).

### Solution

**Answer:** `(month >= 6 && month <= 8) ? 70000 : 35000`

**Explanation:** The condition of being June or later and August or earlier is `month >= 6 && month <= 8`, two relational expressions joined by `&&`, and the conditional operator gives 70000 as the value of the expression if the condition is true and 35000 if it is false ([Chapter 4, Section 8.1](Concepts_Lecture.md#81-ternary-operator)). The relational operators have higher precedence than `&&`, and `&&` has higher precedence than the conditional operator, so writing `month >= 6 && month <= 8 ? 70000 : 35000` without parentheses is the same ([Chapter 4, Section 10.1](Concepts_Lecture.md#101-precedence-table)). Writing it as in mathematics, `6 <= month <= 8`, is computed as `(6 <= month) <= 8`, and since the left comparison result, 0 or 1, is always 8 or less, the condition is always true. A similar problem that writes range conditions as expressions is in [HW03 Problem 2](../../Coursework/HW03_Control-Statements-I/Assignment-Explanation.md#3-problem-2-writing-conditions-as-expressions).

The code with the blank filled in is as follows.

```c
#define _CRT_SECURE_NO_WARNINGS    // required to use scanf in Visual Studio 2022
#include <stdio.h>

int main(void)
{
    int month;
    int fee;

    printf("what month? ");
    scanf("%d", &month);            // reads the month
    fee = (month >= 6 && month <= 8) ? 70000 : 35000;

    printf("entrance fee = %d\n", fee);
}
```

**Output:** It compiles with `gcc -std=c99 -Wall entrance_fee.c -o entrance_fee` without warnings, and the results for July, in the peak season, and December, outside it, are as follows.

```text
what month? 7
entrance fee = 70000
```

```text
what month? 12
entrance fee = 35000
```

---

<br>

## Exercise 14: Output of a Bitwise Operation Program

**Textbook Problem:** Chapter 4 exercise 10

**Problem:** With the `unsigned char` variables `a = 0xcd` and `b = 0xf0`, a program computes `a ^ b` and `~a | b << 2` and prints them with `%02x`. Write its output. The program is in [Exercise 14](Exercises.md#exercise-14-output-of-a-bitwise-operation-program).

### Solution

**Answer:** The first line prints `z = 3d`, and the second line prints `z = f2`.

**Explanation:** The value at each step is shown in Table 3. `~a` and `b << 2` are 32-bit values promoted to `int`, so the identical bits in the middle are abbreviated as `...`.

| Step | Binary | Hexadecimal |
|:-----|:-----|:-----|
| `a` | `1100 1101` | `0xcd` |
| `b` | `1111 0000` | `0xf0` |
| `a ^ b` | `0011 1101` | `0x3d` |
| `~a` | `1111 ... 1111 0011 0010` | `0xffffff32` |
| `b << 2` | `0000 ... 0011 1100 0000` | `0x000003c0` |
| `~a \| b << 2` | `1111 ... 1111 1111 0010` | `0xfffffff2` |
| `c` (lower 8 bits) | `1111 0010` | `0xf2` |

*Table 3. Values at each step of the bitwise operations in Exercise 14*

- **First output:** `^` gives 1 where the two bits differ, so `a ^ b` is `0011 1101` = `0x3d` ([Chapter 4, Section 6.1](Concepts_Lecture.md#61-bitwise-and-or-xor-not)). `%02x` prints lowercase hexadecimal with at least 2 digits, so `z = 3d` is printed ([Chapter 3, Section 5.2](../Ch03_Data-Types-and-Variables/Concepts_Lecture.md#52-width-and-alignment)).
- **Precedence:** The second expression is grouped in the order unary `~` (precedence level 2), shift `<<` (5), bitwise OR `|` (10), and assignment `=` (14), so it is `c = ((~a) | (b << 2))` ([Chapter 4, Section 10.1](Concepts_Lecture.md#101-precedence-table)).
- **Integer promotion:** `a` and `b`, of type `unsigned char`, are promoted to `int` before the operations ([Chapter 4, Section 9.1](Concepts_Lecture.md#91-implicit-promotion)). Therefore `~a` inverts all 32 bits, making the upper 24 bits all 1, and `b << 2` becomes `0x3c0`, which exceeds 8 bits.
- **Assignment:** Assigning the result `0xfffffff2` to `c`, of type `unsigned char`, cuts off the upper bits and keeps only the lower 8 bits `1111 0010` ([Chapter 3, Section 1.1](../Ch03_Data-Types-and-Variables/Concepts_Lecture.md#overflow-and-underflow)). In the lower 8 bits alone, this is the OR of `0011 0010` from `~a` and `1100 0000` from `b << 2`, so `z = f2` is printed.

Compiling the program in the problem with `gcc -std=c99 -Wall bitwise.c -o bitwise` produces no warnings, and its output is as follows.

```text
z = 3d
z = f2
```

---

<br>

## Exercise 15: Computing Density

**Textbook Problem:** Chapter 4 programming assignment 1

**Problem:** Read a mass (g) and a volume ($\text{cm}^3$) as floating-point numbers and print the density, the mass divided by the volume. The full problem and sample run are in [Exercise 15](Exercises.md#exercise-15-computing-density).

### Solution

**Approach:** Read the mass and the volume into `double` variables and compute the density with one floating-point division ([Chapter 4, Section 2.2](Concepts_Lecture.md#22-integer-division-vs-float-division)).

- **Input:** In `scanf`, a `double` is read with `%lf` ([Chapter 2, Section 2.3](../Ch02_C-Program-Basics/Concepts_Lecture.md#23-scanf)). Even an input without a decimal point, such as `33`, is stored as 33.0.
- **Computation:** Both operands are `double`, so `mass / volume` is a floating-point division. 33 / 400 = 0.0825.
- **Output:** `%f` prints six digits after the decimal point, giving `0.082500`.

**Code:**

```c
#define _CRT_SECURE_NO_WARNINGS  // allows scanf in Visual Studio
#include <stdio.h>

int main(void)
{
    double mass;     // mass in grams
    double volume;   // volume in cubic centimeters
    double density;  // density in g/cm^3

    printf("질량(g)? ");
    scanf("%lf", &mass);
    printf("부피(세제곱센티미터)? ");
    scanf("%lf", &volume);

    density = mass / volume;
    printf("밀도: %f\n", density);

    return 0;
}
```

**Output:** It compiles with `gcc -std=c99 -Wall density.c -o density` without warnings and prints the same result as the sample run.

```text
질량(g)? 33
부피(세제곱센티미터)? 400
밀도: 0.082500
```

> **Caution:** Entering 0 for the volume divides by 0. In an environment that uses IEEE 754 floating-point numbers, floating-point division by 0 does not stop the program but produces infinity, so `inf` is printed. The volume of a real object is greater than 0, so checking the input requires the `if` statement of Chapter 5.

```text
질량(g)? 33
부피(세제곱센티미터)? 0
밀도: inf
```

---

<br>

## Exercise 16: Computing an Electricity Bill

**Textbook Problem:** Chapter 4 programming assignment 2

**Problem:** Read the monthly usage (kWh) and compute the electricity bill as usage × 190 won. The full problem and sample run are in [Exercise 16](Exercises.md#exercise-16-computing-an-electricity-bill).

### Solution

**Approach:** Define the unit price of 190 won as the macro constant `PRICE_PER_KWH` and multiply the usage by it ([Chapter 3, Section 4.2](../Ch03_Data-Types-and-Variables/Concepts_Lecture.md#42-define-macro-constants)).

- **Macro constant:** Giving the number a name instead of writing 190 directly in the code shows its meaning, and when the unit price changes, only one place needs to be edited.
- **Computation:** The usage is read as an integer, as in the sample run, so `usage * PRICE_PER_KWH` is an `int` multiplication. 375 × 190 = 71250.
- **Output:** `원` follows `%d`, so the program prints `전기 요금: 71250원`.

**Code:**

```c
#define _CRT_SECURE_NO_WARNINGS  // allows scanf in Visual Studio
#include <stdio.h>

#define PRICE_PER_KWH 190  // charge per kWh in won

int main(void)
{
    int usage;  // monthly usage in kWh
    int fee;    // electricity bill in won

    printf("월 사용량(kWh)? ");
    scanf("%d", &usage);

    fee = usage * PRICE_PER_KWH;
    printf("전기 요금: %d원\n", fee);

    return 0;
}
```

**Output:** It compiles with `gcc -std=c99 -Wall electric_bill.c -o electric_bill` without warnings and prints the same result as the sample run.

```text
월 사용량(kWh)? 375
전기 요금: 71250원
```

---

<br>

## Exercise 17: Computing an Electricity Bill with a Basic Charge

**Textbook Problem:** Chapter 4 programming assignment 3

**Problem:** Read a basic charge and the monthly usage (kWh) and compute the electricity bill as basic charge + usage × 190 won. A compound assignment operator can be used without a separate variable for the basic charge. The full problem and sample run are in [Exercise 17](Exercises.md#exercise-17-computing-an-electricity-bill-with-a-basic-charge).

### Solution

**Approach:** Read the basic charge into the bill variable `fee` first, and then add the usage charge with the compound assignment operator `+=` ([Chapter 4, Section 7.1](Concepts_Lecture.md#71-simple-and-compound-assignment)). The unit price is a macro constant, as in Exercise 16.

- **Input:** `scanf("%d", &fee);` reads the basic charge directly into `fee`. At this point, `fee` holds the basic charge.
- **Compound assignment:** `fee += usage * PRICE_PER_KWH;` is the same as `fee = fee + usage * PRICE_PER_KWH;`. `+=` has lower precedence than `*`, so the usage charge 71250 is computed first, and 2500 + 71250 = 73750 is stored in `fee`.
- **Output:** The format is the same as in Exercise 16.

**Code:**

```c
#define _CRT_SECURE_NO_WARNINGS  // allows scanf in Visual Studio
#include <stdio.h>

#define PRICE_PER_KWH 190  // charge per kWh in won

int main(void)
{
    int fee;    // starts as the basic charge, then the usage charge is added
    int usage;  // monthly usage in kWh

    printf("기본 요금? ");
    scanf("%d", &fee);
    printf("월 사용량(kWh)? ");
    scanf("%d", &usage);

    fee += usage * PRICE_PER_KWH;  // fee = fee + usage * PRICE_PER_KWH
    printf("전기 요금: %d원\n", fee);

    return 0;
}
```

**Output:** It compiles with `gcc -std=c99 -Wall electric_bill_basic.c -o electric_bill_basic` without warnings and prints the same result as the sample run.

```text
기본 요금? 2500
월 사용량(kWh)? 375
전기 요금: 73750원
```

---

<br>

## Exercise 18: Checking Whether a Month Value Is Valid

**Textbook Problem:** Chapter 4 programming assignment 4

**Problem:** Read a month and print that the value is valid if it is 1-12 and invalid otherwise. A `printf` call can be used in an operand position of the conditional operator. The full problem and sample run are in [Exercise 18](Exercises.md#exercise-18-checking-whether-a-month-value-is-valid).

### Solution

**Approach:** Write the range condition of 1 or more and 12 or less as `month >= 1 && month <= 12`, and put `printf` calls that print different messages in the second and third operand positions of the conditional operator ([Chapter 4, Section 8.1](Concepts_Lecture.md#81-ternary-operator)).

- **Range condition:** As in Exercise 13, two relational expressions are joined with `&&`. If `month` is 15, `month <= 12` is false, so the whole condition is 0.
- **Using `printf` as an operand:** `printf` is a function that returns the number of characters (bytes) it printed, so a call to it is an expression with a value and can be an operand of the conditional operator. The conditional operator evaluates only the selected one of its second and third operands, so only one of the two messages is printed.
- **Expression statement:** Adding `;` at the end of the conditional expression makes it a statement, and the value of the expression, the number of bytes printed, is discarded without being used.

The same behavior can also be written by choosing the string to print with the conditional operator, as in `printf((month >= 1 && month <= 12) ? "올바른 값입니다.\n" : "잘못된 값입니다.\n");`.

**Code:**

```c
#define _CRT_SECURE_NO_WARNINGS  // allows scanf in Visual Studio
#include <stdio.h>

int main(void)
{
    int month;

    printf("몇 월? ");
    scanf("%d", &month);

    // printf returns a value, so a call can be an operand of ?:
    (month >= 1 && month <= 12) ? printf("올바른 값입니다.\n")
                                : printf("잘못된 값입니다.\n");

    return 0;
}
```

**Output:** It compiles with `gcc -std=c99 -Wall month_check.c -o month_check` without warnings and prints the same result as the sample run.

```text
몇 월? 15
잘못된 값입니다.
```

The boundary values 12 and 0 are judged valid and invalid, respectively.

```text
몇 월? 12
올바른 값입니다.
```

```text
몇 월? 0
잘못된 값입니다.
```

---

<br>

## Exercise 19: Converting Fahrenheit to Celsius

**Textbook Problem:** Chapter 4 programming assignment 5

**Problem:** Read a Fahrenheit temperature as a floating-point number, compute the Celsius temperature as (Fahrenheit temperature - 32) × 5/9, and print it. `5/9` is 0 by integer division, so use `5.0/9.0`. The full problem and sample run are in [Exercise 19](Exercises.md#exercise-19-converting-fahrenheit-to-celsius).

### Solution

**Approach:** When translating the fraction $\frac{5}{9}$ of the formula into C, write it with floating-point literals as `5.0 / 9.0` so that no integer division occurs ([Chapter 4, Section 2.4](Concepts_Lecture.md#24-math-formula-conversion-to-c)).

- **Integer division pitfall:** `5 / 9` is 0 because both operands are integers, and `(fahrenheit - 32) * (5 / 9)` is 0 regardless of the input.
- **Computation:** For an input of 72, `(fahrenheit - 32) * (5.0 / 9.0)` is 40 × 0.5555... = 22.222....
- **Order of computation:** Without the parentheses, `(fahrenheit - 32) * 5 / 9` computes the `double` value `(fahrenheit - 32) * 5` first, so the result is correct. However, if the order is changed, as in `5 / 9 * (fahrenheit - 32)`, `5 / 9` is computed first and becomes 0, so writing the constant as `5.0 / 9.0` is safe regardless of the order of computation.
- **Output:** The Celsius temperature is printed with `%.2f`, rounded to two digits after the decimal point, as `22.22`. The Fahrenheit temperature is printed with `%g`. `%g` prints within the default 6 significant digits and drops trailing zeros and the decimal point, so 72 is printed as `72` and 98.6 as `98.6`.

**Code:**

```c
#define _CRT_SECURE_NO_WARNINGS  // allows scanf in Visual Studio
#include <stdio.h>

int main(void)
{
    double fahrenheit;  // temperature in degrees Fahrenheit
    double celsius;     // temperature in degrees Celsius

    printf("화씨온도? ");
    scanf("%lf", &fahrenheit);

    celsius = (fahrenheit - 32) * (5.0 / 9.0);  // 5 / 9 would be 0
    printf("%g F = %.2f C\n", fahrenheit, celsius);

    return 0;
}
```

**Output:** It compiles with `gcc -std=c99 -Wall fahrenheit.c -o fahrenheit` without warnings and prints the same result as the sample run. For a Fahrenheit temperature with a fractional part, 98.6, the input value is printed as it is.

```text
화씨온도? 72
72 F = 22.22 C
```

```text
화씨온도? 98.6
98.6 F = 37.00 C
```

---

<br>

## Exercise 20: Computing Kinetic Energy

**Textbook Problem:** Chapter 4 programming assignment 6

**Problem:** Read a mass (kg) and a speed (m/s) as floating-point numbers and compute the kinetic energy = 1/2 × mass × the square of the speed. The full problem and sample run are in [Exercise 20](Exercises.md#exercise-20-computing-kinetic-energy).

### Solution

**Approach:** Write the $\frac{1}{2}$ of the formula as the floating-point division `1.0 / 2.0`, and write the square of the speed as a repeated multiplication, `speed * speed` ([Chapter 4, Section 2.4](Concepts_Lecture.md#24-math-formula-conversion-to-c)).

- **Fractional constant:** `1 / 2` is 0 by integer division, so writing it this way makes the kinetic energy always 0. Use `1.0 / 2.0` or `0.5`.
- **Square:** C has no exponentiation operator, and `^` is the bitwise XOR operator, so the square cannot be written as `speed ^ 2`. If `speed` is a `double`, it cannot be an operand of `^`, and a compile error occurs. Write `speed * speed`, or use `pow(speed, 2)` from `<math.h>`.
- **Computation and output:** 0.5 × 5.5 × 4 × 4 = 44, and `%.2f` prints `44.00`.

**Code:**

```c
#define _CRT_SECURE_NO_WARNINGS  // allows scanf in Visual Studio
#include <stdio.h>

int main(void)
{
    double mass;    // mass in kg
    double speed;   // speed in m/s
    double energy;  // kinetic energy in J

    printf("질량(kg)? ");
    scanf("%lf", &mass);
    printf("속력(m/s)? ");
    scanf("%lf", &speed);

    energy = 1.0 / 2.0 * mass * speed * speed;  // 1 / 2 would be 0
    printf("운동에너지: %.2f J\n", energy);

    return 0;
}
```

**Output:** It compiles with `gcc -std=c99 -Wall kinetic_energy.c -o kinetic_energy` without warnings and prints the same result as the sample run.

```text
질량(kg)? 5.5
속력(m/s)? 4
운동에너지: 44.00 J
```

---

<br>

## Exercise 21: Computing Percent Concentration

**Textbook Problem:** Chapter 4 programming assignment 7

**Problem:** Read the masses (g) of a solvent and a solute as integers and compute the percent concentration = solute / (solvent + solute) × 100. The full problem and sample run are in [Exercise 21](Exercises.md#exercise-21-computing-percent-concentration).

### Solution

**Approach:** Because the inputs are integers, convert the numerator to `double` with the cast operator so that the division is a floating-point division ([Chapter 4, Section 9.2](Concepts_Lecture.md#92-cast-operator)).

- **Integer division pitfall:** `solute / (solvent + solute) * 100` computes 24 / 224 = 0 first and becomes 0. `solute * 100 / (solvent + solute)` becomes 2400 / 224 = 10 and loses the fractional part.
- **Cast:** In `(double)solute / (solvent + solute) * 100`, the cast applies only to `solute`, but because one side of the division is a `double`, `(solvent + solute)` is also converted to `double` and the division is a floating-point division. 24.0 / 224 × 100 = 10.714.... Casting the whole division, as in `(double)(solute / (solvent + solute))`, converts the 0 produced by the integer division that has already finished, giving 0.0.
- **Printing `%`:** In a format string, `%` starts a conversion specification, so the character `%` is printed with `%%` ([Chapter 3, Section 5.1](../Ch03_Data-Types-and-Variables/Concepts_Lecture.md#51-common-specifiers)). `"%.2f %%"` prints `10.71 %`.

**Code:**

```c
#define _CRT_SECURE_NO_WARNINGS  // allows scanf in Visual Studio
#include <stdio.h>

int main(void)
{
    int solvent;           // mass of the solvent in grams
    int solute;            // mass of the solute in grams
    double concentration;  // percent concentration

    printf("용매(g)? ");
    scanf("%d", &solvent);
    printf("용질(g)? ");
    scanf("%d", &solute);

    // the cast makes the division a floating-point division
    concentration = (double)solute / (solvent + solute) * 100;
    printf("농도: %.2f %%\n", concentration);

    return 0;
}
```

**Output:** It compiles with `gcc -std=c99 -Wall concentration.c -o concentration` without warnings and prints the same result as the sample run.

```text
용매(g)? 200
용질(g)? 24
농도: 10.71 %
```

> **Caution:** Entering 0 for both the solvent and the solute divides 0.0 by 0, so in an IEEE 754 environment the result is `nan` (Not a Number). The mass of the solution is assumed to be greater than 0.

```text
용매(g)? 0
용질(g)? 0
농도: nan %
```

---

<br>

## Exercise 22: Converting a Playback Time to Hours, Minutes, and Seconds

**Textbook Problem:** Chapter 4 programming assignment 8

**Problem:** Read the playback time of a video in seconds and print how many hours, minutes, and seconds it is. The full problem and sample run are in [Exercise 22](Exercises.md#exercise-22-converting-a-playback-time-to-hours-minutes-and-seconds).

### Solution

This assignment is the same computation as the second part of Exercise 2, which converts seconds to hours, minutes, and seconds, so it follows [the solution of Exercise 2](#exercise-2-converting-between-time-and-seconds). The only differences are that the input prompt is `재생 시간(초)?` and the result is printed in the form `재생 시간은 1시간 2분 30초입니다.`, and 3750 seconds is 3750 / 3600 = 1 hour, 3750 % 3600 / 60 = 2 minutes, and 3750 % 60 = 30 seconds. The improvement that omits units equal to 0 can be made, as in Exercise 18, by putting `printf` calls in the operand positions of the conditional operator so that only nonzero units are printed.

---

<br>

## Exercise 23: Computing a Discounted Price and the Discount Amount

**Textbook Problem:** Chapter 4 programming assignment 9

**Problem:** Read the price of a product and a discount rate (%) and print the discounted price and the discount amount. The full problem and sample run are in [Exercise 23](Exercises.md#exercise-23-computing-a-discounted-price-and-the-discount-amount).

### Solution

**Approach:** The discount amount is price × discount rate / 100, and the discounted price is the price minus the discount amount. Compute in `double` with a cast, and make the result in won an integer again with a cast ([Chapter 4, Section 9.2](Concepts_Lecture.md#92-cast-operator)).

- **Integer division pitfall:** Writing `rate / 100 * price` computes 25 / 100 = 0 first, so the discount amount is always 0.
- **Computation:** In `(double)price * rate / 100`, the cast `price` is a `double`, so both the multiplication and the division are computed in `double`. 12000.0 × 25 / 100 = 3000.0. Multiplying two `int` values, the product 2.5 billion for a price of 100 million won and a discount rate of 25% exceeds the maximum `int` value (about 2.1 billion), but computing in `double` avoids such an overflow.
- **Conversion to won:** The outer `(int)` cast discards the fractional part of the result and converts it to `int`. Assigning a `double` value to an `int` variable without a cast performs the same conversion, but writing the cast makes the intent of discarding the fractional part visible in the code.
- **Output:** The discounted price is 12000 - 3000 = 9000. The `%` in the input prompt is inside the format string of `printf`, so it is written as `%%`.

**Code:**

```c
#define _CRT_SECURE_NO_WARNINGS  // allows scanf in Visual Studio
#include <stdio.h>

int main(void)
{
    int price;       // price of the product in won
    int rate;        // discount rate in percent
    int discount;    // discount amount in won
    int sale_price;  // discounted price in won

    printf("제품의 가격? ");
    scanf("%d", &price);
    printf("할인율(%%)? ");
    scanf("%d", &rate);

    // compute in double, then drop the fraction of a won
    discount = (int)((double)price * rate / 100);
    sale_price = price - discount;
    printf("할인가: %d원 (%d원 할인)\n", sale_price, discount);

    return 0;
}
```

**Output:** It compiles with `gcc -std=c99 -Wall discount.c -o discount` without warnings and prints the same result as the sample run.

```text
제품의 가격? 12000
할인율(%)? 25
할인가: 9000원 (3000원 할인)
```

> **Note:** When the discount amount has a fraction of a won, the `(int)` cast discards it. A 15% discount on 9999 won gives a discount amount of 1499 won, not 1499.85 won, and a discounted price of 8500 won. To round instead, add 0.5 before discarding the fractional part, as in `(int)((double)price * rate / 100 + 0.5)`.

```text
제품의 가격? 9999
할인율(%)? 15
할인가: 8500원 (1499원 할인)
```

---

<br>

## Exercise 24: Printing Each Byte in Hexadecimal

**Textbook Problem:** Chapter 4 programming assignment 10

**Problem:** Read an unsigned integer in hexadecimal and print the value of each byte in hexadecimal, starting from the least significant byte. Apply a bitmask with the `&` operator. The full problem and sample run are in [Exercise 24](Exercises.md#exercise-24-printing-each-byte-in-hexadecimal).

### Solution

**Approach:** Move the wanted byte to the position of the least significant byte with a right shift, and then AND it with the bitmask `0xFF` to keep only those 8 bits ([Chapter 4, Section 6.3](Concepts_Lecture.md#63-practical-example-rgb-color)). This is the same method used to extract the channels of an RGB value in Exercise 4.

- **Input:** `%x` reads a hexadecimal number and stores it in an `unsigned int` variable, and it also accepts a leading `0x` or `0X`. Therefore `0xa1b2c3d4` and `a1b2c3d4` are read as the same value.
- **Byte n:** Byte n occupies bits 8n through 8n + 7, so it is extracted with `(data >> (8 * n)) & 0xFF`. Byte 0 is `0xd4`, obtained with `data & 0xFF` without a shift, and byte 1 is `0xc3`, the lower 8 bits of `0xa1b2c3`, obtained with `(data >> 8) & 0xFF`.
- **Byte 3:** If `unsigned int` is 32 bits, `data >> 24` fills the left side with 0, so it gives the same value without the mask, but `& 0xFF` is added so that all four bytes are extracted in the same form.
- **Output:** `%02x` prints lowercase hexadecimal with at least 2 digits, padding empty positions with 0, so a byte such as `0x05` is also printed as `05` ([Chapter 3, Section 5.2](../Ch03_Data-Types-and-Variables/Concepts_Lecture.md#52-width-and-alignment)).

`(data & 0x0000FF00) >> 8`, which applies the mask first, also extracts byte 1. This method places the mask at the position of the wanted byte and then moves the remaining bits to the right.

**Code:**

```c
#define _CRT_SECURE_NO_WARNINGS  // allows scanf in Visual Studio
#include <stdio.h>

int main(void)
{
    unsigned int data;  // 32-bit data read in hexadecimal

    printf("16진수로 데이터를 입력하세요: ");
    scanf("%x", &data);

    // shift the wanted byte down to bits 0-7, then keep only those bits
    printf("byte 0 : %02x\n", data & 0xFF);
    printf("byte 1 : %02x\n", (data >> 8) & 0xFF);
    printf("byte 2 : %02x\n", (data >> 16) & 0xFF);
    printf("byte 3 : %02x\n", (data >> 24) & 0xFF);

    return 0;
}
```

**Output:** It compiles with `gcc -std=c99 -Wall bytes.c -o bytes` without warnings and prints the same result as the sample run.

```text
16진수로 데이터를 입력하세요: 0xa1b2c3d4
byte 0 : d4
byte 1 : c3
byte 2 : b2
byte 3 : a1
```

> **Note:** If the input is shorter than 8 digits, the upper bytes are 0. Entering `1f` prints `00` for bytes 1-3. Shifts and masks operate on the bit positions of the value, so the result does not depend on the order in which the bytes are stored in memory (endianness).

```text
16진수로 데이터를 입력하세요: 1f
byte 0 : 1f
byte 1 : 00
byte 2 : 00
byte 3 : 00
```

---

<br>

## Exercise 25: Building an RGB Color with Overflow Handling

**Textbook Problem:** Chapter 4 programming assignment 11

**Problem:** Read red, green, and blue, build an RGB color in the same layout as Figure 2 of Exercise 3 (red in bits 0-7, green in 8-15, blue in 16-23), and print it in hexadecimal. A value greater than 255 is handled as an overflow, so 256 is stored as 0. The full problem and sample run are in [Exercise 25](Exercises.md#exercise-25-building-an-rgb-color-with-overflow-handling).

### Solution

**Approach:** Handle the overflow by keeping only the lower 8 bits of each channel with `& 0xFF`, and then combine the channels with left shifts and bitwise OR ([Chapter 4, Section 6.3](Concepts_Lecture.md#63-practical-example-rgb-color)). The bit layout is the same as in [the solution of Exercise 3](#exercise-3-convert-red-green-and-blue-values-to-a-hexadecimal-rgb-value), but this program handles out-of-range values and uses a different output format.

- **Input:** The three values are read into `unsigned int` variables with `%u`. Reading directly into an `unsigned char` with `%hhu` leaves the result for an out-of-range input undefined by the C standard, so the values are read into a wider type and then reduced with the mask.
- **Overflow handling:** `red &= 0xFF;` is `red = red & 0xFF;` and sets all bits from bit 8 up to 0. 256 (`0x100`) has all 0s in its lower 8 bits, so it becomes 0, and 300 (`0x12C`) becomes `0x2C` (44). This is the same result as the overflow that occurs when a value is stored in an `unsigned char` variable, where the upper bits are cut off and the remainder of division by 256 is left ([Chapter 3, Section 1.1](../Ch03_Data-Types-and-Variables/Concepts_Lecture.md#overflow-and-underflow)).
- **Without the handling:** Combining without a mask, as in the solution of Exercise 3, lets a red value of 256 set bit 8 and change the green value. Applying the mask first keeps each channel within its own 8 bits.
- **Combining:** `(blue << 16) | (green << 8) | red` places `0xFF`, `0x80`, and `0x00` at bits 16, 8, and 0, respectively, producing `0xFF8000`.
- **Output:** `%06X` prints uppercase hexadecimal with at least 6 digits, padding empty positions with 0. Unlike `%#08X` in Exercise 3, it has no `0X` prefix, and even a value of 0 keeps six digits as `000000`.

**Code:**

```c
#define _CRT_SECURE_NO_WARNINGS  // allows scanf in Visual Studio
#include <stdio.h>

int main(void)
{
    unsigned int red, green, blue;  // color channels
    unsigned int rgb;               // 0x00BBGGRR

    printf("red? ");
    scanf("%u", &red);
    printf("green? ");
    scanf("%u", &green);
    printf("blue? ");
    scanf("%u", &blue);

    // keep only the lower 8 bits, as storing into unsigned char would
    red &= 0xFF;
    green &= 0xFF;
    blue &= 0xFF;

    rgb = (blue << 16) | (green << 8) | red;
    printf("RGB 색상: %06X\n", rgb);

    return 0;
}
```

**Output:** It compiles with `gcc -std=c99 -Wall rgb_color.c -o rgb_color` without warnings and prints the same result as the sample run. The 256 entered for red is stored as 0.

```text
red? 256
green? 128
blue? 255
RGB 색상: FF8000
```

Entering 300 for red and 511 for blue leaves their lower 8 bits, `0x2C` and `0xFF`, respectively.

```text
red? 300
green? 0
blue? 511
RGB 색상: FF002C
```
