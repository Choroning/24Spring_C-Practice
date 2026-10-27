# Chapter 4 Exercises — Operators

[Repository Guide](../../README.md) | [English](Exercises.md) | [한국어](Exercises.ko.md)

> **Last Updated:** 2026-10-27
>
> Warming-Up C Programming, 천정아, Ch 4

**Problem Source:** Prof. Younghee Im, Computer Language Ⅰ (DCCS101-04)

**Common Requirement:** Every program must use meaningful variable names.

Exercises 1-4 are lab problems, Exercises 5-14 are exercises 1-10 of Chapter 4 of the textbook, and Exercises 15-25 are programming assignments 1-11 of Chapter 4.

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

**Textbook Problem:** Adapted from Chapter 4 programming assignment 8

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

---

<br>

## Exercise 5: Statements About Operators

**Textbook Problem:** Chapter 4 exercise 1

**Problem:** Choose all the incorrect statements about operators.

- ① An operator is a symbol used in an operation.
- ② A value that is the target of an operation is called an operand.
- ③ An expression that contains an operator always has a value.
- ④ Some operators have no operands.
- ⑤ `#` can be defined as an operator and used.
- ⑥ `^` is a unary operator.
- ⑦ The comma (`,`) is also an operator.
- ⑧ An operator expression cannot be used as part of another expression.

**[Solution](Solutions.md#exercise-5-statements-about-operators)**

---

<br>

## Exercise 6: Unary Operators

**Textbook Problem:** Chapter 4 exercise 2

**Problem:** Choose all the unary operators below.

- ① `+`
- ② `-`
- ③ `++`
- ④ `!`
- ⑤ `sizeof`
- ⑥ `<<`
- ⑦ `&&`
- ⑧ `~`
- ⑨ `*=`
- ⑩ `==`

**[Solution](Solutions.md#exercise-6-unary-operators)**

---

<br>

## Exercise 7: Statements About Arithmetic Operators

**Textbook Problem:** Chapter 4 exercise 3

**Problem:** Choose all the incorrect statements about arithmetic operators.

- ① There are addition (`+`), subtraction (`-`), multiplication (`*`), division (`/`), and remainder (`%`) operators.
- ② `+` and `-` can be used as sign operators.
- ③ Integer / integer computes the quotient as a floating-point number.
- ④ The remainder (`%`) operator can also be used on floating-point numbers.
- ⑤ In a mixed operation on an integer and a floating-point number, the type is converted to a floating-point type.
- ⑥ When the operands have the same data type, no type conversion takes place.
- ⑦ The `*` and `/` operators have higher precedence than the `+` and `-` operators.

**[Solution](Solutions.md#exercise-7-statements-about-arithmetic-operators)**

---

<br>

## Exercise 8: Result Types of Expressions

**Textbook Problem:** Chapter 4 exercise 4

**Problem:** Write the type of the result of each expression below.

- (1) `1 + 0.5`
- (2) `1.01F + 0.5`
- (3) `0.5F * 2.4`
- (4) `12 + 56`
- (5) `ch + 1` with `char ch = 'a';`
- (6) `a - b` with `short a = 10, b = 20;`

**[Solution](Solutions.md#exercise-8-result-types-of-expressions)**

---

<br>

## Exercise 9: Values of Expressions and Variables After Operations

**Textbook Problem:** Chapter 4 exercise 5

**Problem:** For the variables declared below, perform each operation and write the value of the expression and the values of the variables `x`, `y`, and `z`. For each of (1)-(12), assume that `x`, `y`, and `z` are declared as follows.

```c
int x = 1, y = 2, z = 3;
```

- (1) `z % y`
- (2) `++y;`
- (3) `z = x--;`
- (4) `z = y = x;`
- (5) `z *= x;`
- (6) `z *= y + 1;`
- (7) `x > z && y < z`
- (8) `! x || y < z`
- (9) `x && y`
- (10) `z << y`
- (11) `x |= z`
- (12) `y = x + 1 > z ? y : y - 1;`

**[Solution](Solutions.md#exercise-9-values-of-expressions-and-variables-after-operations)**

---

<br>

## Exercise 10: Statements About Relational and Logical Operators

**Textbook Problem:** Chapter 4 exercise 6

**Problem:** Choose all the incorrect statements about relational and logical operators.

- ① An operator that compares the values of two numbers is called a relational operator.
- ② `=` is the operator that compares whether two numbers are equal.
- ③ The value of a logical expression is always 0 or 1.
- ④ When relational and logical operators are used together, the relational operators are performed first.
- ⑤ `~` is the logical NOT operator.
- ⑥ An operand of a logical operator is considered true only when its value is 1.
- ⑦ `!expr` can be used instead of `expr != 0`.
- ⑧ The `&&` operation is performed before `||`.

**[Solution](Solutions.md#exercise-10-statements-about-relational-and-logical-operators)**

---

<br>

## Exercise 11: Data for Manipulating Specific Bits

**Textbook Problem:** Chapter 4 exercise 7

**Problem:** What is the data used in bitwise logical operations for the purpose of manipulating specific bit values called?

**[Solution](Solutions.md#exercise-11-data-for-manipulating-specific-bits)**

---

<br>

## Exercise 12: Parenthesizing Expressions in Evaluation Order

**Textbook Problem:** Chapter 4 exercise 8

**Problem:** For each expression below, enclose the operations in `()` in the order in which they are performed.

- (1) `x - y / 3`
- (2) `x < 0 || x > 100`
- (3) `x == 0 || y == 0 && z == 1`
- (4) `x = a > b`
- (5) `!x && !y`
- (6) `x += y * 2`
- (7) `~x & y`
- (8) `x < 0 || ! y && z`
- (9) `x = x > 0 ? y + 1 : z + 2`
- (10) `z = (double) x / y`

**[Solution](Solutions.md#exercise-12-parenthesizing-expressions-in-evaluation-order)**

---

<br>

## Exercise 13: Computing an Entrance Fee with the Conditional Operator

**Textbook Problem:** Chapter 4 exercise 9

**Problem:** The following code computes an entrance fee. Fill in the blank in the code using the conditional operator so that the entrance fee is 70,000 won in the peak season (June-August) and 35,000 won otherwise.

```c
#define _CRT_SECURE_NO_WARNINGS    // required to use scanf in Visual Studio 2022
#include <stdio.h>

int main(void)
{
    int month;
    int fee;

    printf("what month? ");
    scanf("%d", &month);            // reads the month
    fee = ______________________________;

    printf("entrance fee = %d\n", fee);
}
```

**[Solution](Solutions.md#exercise-13-computing-an-entrance-fee-with-the-conditional-operator)**

---

<br>

## Exercise 14: Output of a Bitwise Operation Program

**Textbook Problem:** Chapter 4 exercise 10

**Problem:** Write the output of the following program.

```c
#include <stdio.h>

int main(void)
{
    unsigned char a = 0xcd;
    unsigned char b = 0xf0;
    unsigned char c;

    c = a ^ b;
    printf("z = %02x\n", c);

    c = ~a | b << 2;
    printf("z = %02x\n", c);
}
```

**[Solution](Solutions.md#exercise-14-output-of-a-bitwise-operation-program)**

---

<br>

## Exercise 15: Computing Density

**Textbook Problem:** Chapter 4 programming assignment 1

**Problem:** Write a program that reads a mass and a volume as floating-point numbers and computes the density. The mass is read in g, and the volume is read in $\text{cm}^3$.

$$\text{density}(\text{g/cm}^3) = \frac{\text{mass}(\text{g})}{\text{volume}(\text{cm}^3)}$$

**Sample Run:**

```text
질량(g)? 33
부피(세제곱센티미터)? 400
밀도: 0.082500
```

**[Solution](Solutions.md#exercise-15-computing-density)**

---

<br>

## Exercise 16: Computing an Electricity Bill

**Textbook Problem:** Chapter 4 programming assignment 2

**Problem:** Write a program that reads the monthly usage (kWh) and computes the electricity bill. The charge for the usage is 190 won/kWh.

$$\text{electricity bill} = \text{monthly usage}(\text{kWh}) \times 190\,\text{won/kWh}$$

**Sample Run:**

```text
월 사용량(kWh)? 375
전기 요금: 71250원
```

**[Solution](Solutions.md#exercise-16-computing-an-electricity-bill)**

---

<br>

## Exercise 17: Computing an Electricity Bill with a Basic Charge

**Textbook Problem:** Chapter 4 programming assignment 3

**Problem:** Write a program that reads a basic charge and the monthly usage (kWh) and computes the electricity bill. The charge for the usage is 190 won/kWh. The expression can be written with a compound assignment operator, without declaring a separate variable to store the basic charge.

$$\text{electricity bill} = \text{basic charge} + \text{monthly usage}(\text{kWh}) \times 190\,\text{won/kWh}$$

**Sample Run:**

```text
기본 요금? 2500
월 사용량(kWh)? 375
전기 요금: 73750원
```

**[Solution](Solutions.md#exercise-17-computing-an-electricity-bill-with-a-basic-charge)**

---

<br>

## Exercise 18: Checking Whether a Month Value Is Valid

**Textbook Problem:** Chapter 4 programming assignment 4

**Problem:** Write a program that reads the month of a date and prints that the value is valid if a value from 1 to 12 is entered, and that the value is invalid otherwise. Because `printf` is a function that returns a value, a call to `printf` can be used in the positions of `expr1`, `expr2`, and `expr3` in `expr1 ? expr2 : expr3`.

**Sample Run:**

```text
몇 월? 15
잘못된 값입니다.
```

**[Solution](Solutions.md#exercise-18-checking-whether-a-month-value-is-valid)**

---

<br>

## Exercise 19: Converting Fahrenheit to Celsius

**Textbook Problem:** Chapter 4 programming assignment 5

**Problem:** Write a program that reads a Fahrenheit temperature (°F) as a floating-point number, converts it to a Celsius temperature (°C), and prints it. The formula that converts a Fahrenheit temperature to a Celsius temperature is as follows. Because integer / integer computes the quotient as an integer, `5/9` is 0. Therefore, `5.0/9.0` must be computed and used.

$$\text{Celsius temperature} = (\text{Fahrenheit temperature} - 32) \times \frac{5}{9}$$

**Sample Run:**

```text
화씨온도? 72
72 F = 22.22 C
```

**[Solution](Solutions.md#exercise-19-converting-fahrenheit-to-celsius)**

---

<br>

## Exercise 20: Computing Kinetic Energy

**Textbook Problem:** Chapter 4 programming assignment 6

**Problem:** Write a program that reads a mass and a speed as floating-point numbers and computes the kinetic energy. The mass is read in kg, and the speed is read in m/s.

$$\text{kinetic energy} = \frac{1}{2} \times \text{mass} \times (\text{speed})^2$$

**Sample Run:**

```text
질량(kg)? 5.5
속력(m/s)? 4
운동에너지: 44.00 J
```

**[Solution](Solutions.md#exercise-20-computing-kinetic-energy)**

---

<br>

## Exercise 21: Computing Percent Concentration

**Textbook Problem:** Chapter 4 programming assignment 7

**Problem:** Write a program that reads the mass of a solvent and the mass of a solute as integers and computes the percent concentration of the solution. The masses of the solvent and the solute are read in g.

$$\text{percent concentration}(\%) = \frac{\text{mass of solute}}{\text{mass of solvent} + \text{mass of solute}} \times 100$$

**Sample Run:**

```text
용매(g)? 200
용질(g)? 24
농도: 10.71 %
```

**[Solution](Solutions.md#exercise-21-computing-percent-concentration)**

---

<br>

## Exercise 22: Converting a Playback Time to Hours, Minutes, and Seconds

**Textbook Problem:** Chapter 4 programming assignment 8

**Problem:** Write a program that reads the playback time of a video in seconds and prints how many hours, minutes, and seconds it is. With the conditional operator, the program can be improved to print "재생 시간은 5분입니다." instead of "재생 시간은 0시간 5분 0초입니다.", that is, to print the hours, minutes, and seconds only when they are not 0.

**Sample Run:**

```text
재생 시간(초)? 3750
재생 시간은 1시간 2분 30초입니다.
```

**[Solution](Solutions.md#exercise-22-converting-a-playback-time-to-hours-minutes-and-seconds)**

---

<br>

## Exercise 23: Computing a Discounted Price and the Discount Amount

**Textbook Problem:** Chapter 4 programming assignment 9

**Problem:** Write a program that reads the price of a product and a discount rate (%) and prints the discounted price and the discount amount.

**Sample Run:**

```text
제품의 가격? 12000
할인율(%)? 25
할인가: 9000원 (3000원 할인)
```

**[Solution](Solutions.md#exercise-23-computing-a-discounted-price-and-the-discount-amount)**

---

<br>

## Exercise 24: Printing Each Byte in Hexadecimal

**Textbook Problem:** Chapter 4 programming assignment 10

**Problem:** Write a program that reads an unsigned integer in hexadecimal and prints the value of each byte in hexadecimal, in order from the least significant byte. Use a bitmask with the `&` operator.

**Sample Run:**

```text
16진수로 데이터를 입력하세요: 0xa1b2c3d4
byte 0 : d4
byte 1 : c3
byte 2 : b2
byte 3 : a1
```

**[Solution](Solutions.md#exercise-24-printing-each-byte-in-hexadecimal)**

---

<br>

## Exercise 25: Building an RGB Color with Overflow Handling

**Textbook Problem:** Chapter 4 programming assignment 11

**Problem:** The RGB notation for 24-bit true color represents a color using 8 bits each for red, green, and blue. An RGB color is stored in a 32-bit unsigned integer, which stores the color information in the order red, green, blue starting from the least significant byte and leaves the most significant byte unused. This bit layout is the same as Figure 2 of Exercise 3. Write a program that reads red, green, and blue, builds the RGB color, and prints it. Print the RGB color in hexadecimal so that its value is easy to read byte by byte. If a value greater than 255 is entered for red, green, or blue, it must be handled as an overflow. That is, if 256 is entered for red, 0, not 256, must be stored in red.

**Sample Run:**

```text
red? 256
green? 128
blue? 255
RGB 색상: FF8000
```

**[Solution](Solutions.md#exercise-25-building-an-rgb-color-with-overflow-handling)**
