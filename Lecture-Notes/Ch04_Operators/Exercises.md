# Chapter 4 Exercises — Operators

[Repository Guide](../../README.md) | [English](Exercises.md) | [한국어](Exercises.ko.md)

> **Last Updated:** 2026-10-19
>
> Warming-Up C Programming, 천정아, Ch 4

**Problem Source:** Prof. Younghee Im, Computer Language Ⅰ (DCCS101-04)

**Common Requirement:** Every program must use meaningful variable names.

---

<br>

## Exercise 1: Volume and Surface Area of a Helmet

**Problem:** Write a program that computes the volume and the surface area of a helmet.

As shown in Figure 1, the helmet is the part of a sphere of radius R cut off so that the diameter of its base is 2a, and h is the height of the helmet. The surface area and volume of the helmet are computed from the height h and the base radius a by the following formulas.

![Figure 1. Height h of the helmet, radius R of the sphere, and base diameter 2a](../../images/Ch04_Helmet-Dimensions.png)

*Figure 1. Height h of the helmet, radius R of the sphere, and base diameter 2a*

$$V = \frac{\pi}{6} \times h \times (3a^2 + h^2)$$

$$S = 2\pi \times \left(\frac{h}{3} + \frac{V}{\pi \times h^2}\right) \times h$$

- **Input:** The height (h) and base radius (a) of the helmet (h and a are integers)
- **Output:** The volume (V) and surface area (S) of the helmet

**Program Requirements:**

1. Use 3.14159265 as the value of π and define it as a macro constant with a `#define` statement.
2. The input data, the height (h) and base radius (a) of the helmet, are of type `int`.
3. Take care that integer division does not occur, and print the exact results as in the sample runs.

**Sample Runs:**

```text
헬멧의 높이: 1
base 반지름 입력: 1
헬멧의 체적: 2.094395
헬멧의 표면적: 6.283185

Program ended with exit code: 0
```

```text
헬멧의 높이: 12
base 반지름 입력: 20
헬멧의 체적: 8444.601043
헬멧의 표면적: 1709.026402

Program ended with exit code: 0
```

**[Solution](Solutions.md#exercise-1-volume-and-surface-area-of-a-helmet)**

---

<br>

## Exercise 2: Converting Between Time and Seconds

**Textbook Problem:** Adapted from Chapter 4 exercise 8

**Problem:** Referring to the sample runs, write a program that does the following two things.

1. Read hours, minutes, and seconds, and convert them to a total number of seconds.
2. Read a number of seconds and convert it to hours, minutes, and seconds.

- **Input:**
  1. Hours, minutes, and seconds (all integers)
  2. Total seconds (an integer)
- **Output:**
  1. Total seconds
  2. Hours, minutes, and seconds

**Program Requirements:** Use the following symbolic constants.

```c
#define SEC_PER_HOUR 3600
#define SEC_PER_MIN  60
```

**Sample Runs:**

```text
시간을 차례로 입력하세요(시,분,초): 2 10 47
2시간 10분 47초는 총 7847초입니다.
-----------------------------------
환산할 초를 입력하세요: 3989
3989초는 1시간 6분 29초입니다.

Program ended with exit code: 0
```

```text
시간을 차례로 입력하세요(시,분,초): 7 1 55
7시간 1분 55초는 총 25315초입니다.
-----------------------------------
환산할 초를 입력하세요: 25315
25315초는 7시간 1분 55초입니다.

Program ended with exit code: 0
```

**[Solution](Solutions.md#exercise-2-converting-between-time-and-seconds)**

---

<br>

## Exercise 3: Convert Red, Green, and Blue Values to a Hexadecimal RGB Value

**Background:** The RGB model is one way a computer represents colors. It expresses a color by combining three colors, red, green, and blue, each with a value from 0 to 255. In this exercise and Exercise 4, as shown in Figure 2, bits 0-7 of a 32-bit integer store the Red value, bits 8-15 the Green value, and bits 16-23 the Blue value, each in the range 0-255 (0x00-0xFF), and the upper 8 bits (24-31) are filled with 0.

![Figure 2. 32-bit memory layout of the RGB model](../../images/Ch04_RGB-Bit-Layout.png)

*Figure 2. 32-bit memory layout of the RGB model*

**Problem:** Read decimal Red, Green, and Blue values between 0 and 255 from the user, build a 4-byte RGB value, and print it as a 6-digit hexadecimal number.

- **Input:** Red, Green, Blue (integers between 0 and 255)
- **Output:** The RGB value (6-digit hexadecimal)

**Sample Runs:**

```text
Red 값 입력(0-255): 255
Green 값 입력(0-255): 0
Blue 값 입력(0-255): 130

RGB = 0X8200FF

Program ended with exit code: 0
```

```text
Red 값 입력(0-255): 67
Green 값 입력(0-255): 200
Blue 값 입력(0-255): 13

RGB = 0X0DC843

Program ended with exit code: 0
```

**[Solution](Solutions.md#exercise-3-convert-red-green-and-blue-values-to-a-hexadecimal-rgb-value)**

---

<br>

## Exercise 4: Convert a Hexadecimal RGB Value to Red, Green, and Blue Values

**Problem:** Read an RGB value as a 6-digit hexadecimal integer from the user, extract the Red, Green, and Blue values, and print them in the form below. The bit layout is the same as in Figure 2 of Exercise 3.

- **Input:** The RGB value (6-digit hexadecimal)
- **Output:** Each of Red, Green, and Blue as a 2-digit hexadecimal value and a decimal value

**Sample Runs:**

```text
RGB 값 입력(16진수 6자리): A73803

Red   = 0X03 (3)
Green = 0X38 (56)
Blue  = 0XA7 (167)

Program ended with exit code: 0
```

```text
RGB 값 입력(16진수 6자리): FF00DD

Red   = 0XDD (221)
Green = 0X00 (0)
Blue  = 0XFF (255)

Program ended with exit code: 0
```

**[Solution](Solutions.md#exercise-4-convert-a-hexadecimal-rgb-value-to-red-green-and-blue-values)**
