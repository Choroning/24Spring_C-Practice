# Chapter 4 Solutions — Operators

[Repository Guide](../../README.md) | [English](Solutions.md) | [한국어](Solutions.ko.md)

> **Last Updated:** 2026-10-19
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

> **Note:** **`scanf_s` and the build environment.** The `scanf_s` used by the code in this chapter is a function provided by Visual Studio (MSVC). The optional Annex K of C11 also defines a function with this name, but most standard libraries used with gcc and clang do not provide it, so compiling the code as is fails with an undeclared function error. The outputs above were produced without changing the code by compiling with `gcc -std=c99 -Wall -Dscanf_s=scanf`, which replaces `scanf_s` with `scanf`. For conversions that read numbers, such as `%d` and `%x`, the two functions behave the same.

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

**Textbook Problem:** Adapted from Chapter 4 exercise 8

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
