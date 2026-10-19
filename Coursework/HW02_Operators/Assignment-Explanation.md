# HW2 Assignment Explanation — Operators

[Repository Guide](../../README.md) | [English](Assignment-Explanation.md) | [한국어](Assignment-Explanation.ko.md)

> **Last Updated:** 2026-10-19
>
> 문제풀이 중심의 C언어 연습, 김용일 외, Ch 3

> **Learning Objectives:**
> 1. Print an integer in decimal, octal, and hexadecimal with the `%d`, `%o`, and `%x` conversions of `printf` and the `#` flag
> 2. Align output digits with a field width and precision (`%6d`, `%6.1lf`)
> 3. Divide by a floating-point literal to obtain the average of integers as a floating-point value
> 4. Design a simple calculation program that combines input, arithmetic, and formatted output

**Problem Source:** Prof. Jonguk Lee, Computer Language and Training Ⅰ (DCCS103-03)

---

## Table of Contents

- [1. Assignment Layout and How to Run](#1-assignment-layout-and-how-to-run)
- [2. Problem 1: Printing a Value in Different Bases](#2-problem-1-printing-a-value-in-different-bases)
  - [2.1 Problem](#21-problem)
  - [2.2 Solution](#22-solution)
  - [2.3 Output and Edge Cases](#23-output-and-edge-cases)
- [3. Problem 2: Basic Arithmetic](#3-problem-2-basic-arithmetic)
  - [3.1 Problem](#31-problem)
  - [3.2 Solution](#32-solution)
  - [3.3 Output and Edge Cases](#33-output-and-edge-cases)
- [4. Problem 3: Free Code](#4-problem-3-free-code)
  - [4.1 Problem](#41-problem)
  - [4.2 Solution](#42-solution)
  - [4.3 Output and Edge Cases](#43-output-and-edge-cases)
- [Summary](#summary)
- [Self-Check Questions](#self-check-questions)

---

<br>

## 1. Assignment Layout and How to Run

This assignment prints an input integer in several bases (Problem 1), prints the sum and average of three integers with aligned digits (Problem 2), and freely writes a program that uses the input, output, and operations learned so far (Problem 3). Problems 1 and 2 come from the exercises of Chapter 3 (input and output statements) of the textbook.

```text
Coursework/HW02_Operators/
├── Assignment-Explanation.ko.md   # this document (Korean)
├── Assignment-Explanation.md      # this document (English)
└── Solution/
    ├── Q1.c                       # Problem 1: printing a value in different bases
    ├── Q2.c                       # Problem 2: basic arithmetic
    └── Q3.c                       # Problem 3: free code (cafe revenue calculator)
```

*Figure 1. Directory layout of HW2*

The three programs were written in Visual Studio (MSVC) and use `scanf_s` for input. `scanf_s` is provided by MSVC and is missing from most standard libraries used with gcc and clang, so in other environments the code is compiled without changes by replacing it with `scanf` through the `-Dscanf_s=scanf` option. For `%d`, which reads numbers, the two functions behave the same. All outputs in this document were obtained with the following commands.

```bash
cd Coursework/HW02_Operators/Solution
gcc -std=c99 -Wall -Dscanf_s=scanf -o Q1 Q1.c
./Q1
```

The line `Program ended with exit code: 0` at the end of the sample runs in the assignment is not program output but the exit message added by the Xcode console.

---

<br>

## 2. Problem 1: Printing a Value in Different Bases

### 2.1 Problem

**Textbook Problem:** Chapter 3 exercise 7

Referring to the sample run, read an arbitrary positive integer from the user into the variable `no`, and print that value in decimal, octal, and hexadecimal form.

**Sample Run:**

```text
enter no: 10
10, 012, 0xa

Program ended with exit code: 0
```

### 2.2 Solution

**Approach:** Store the value only once and choose the base with the `printf` conversion specifier at output time. An integer is simply stored in binary in memory, and decimal, octal, and hexadecimal differ only in how that value is written as characters.

- **Conversion specifiers:** `%d` prints in decimal, `%o` in octal, and `%x` in lowercase hexadecimal.
- **The `#` flag:** `%#o` adds `0` in front of the octal number, and `%#x` adds `0x` in front of the hexadecimal number. These prefixes match the notation for octal and hexadecimal integer constants in C source code (`012`, `0xa`).
- **Arguments:** All three conversions print the same variable, so `no` is passed three times.

**Code:** [Solution/Q1.c](Solution/Q1.c)

```c
/**
 * @file    A10303-1_C04Q1.c
 * @brief   Q1. 값의 n진수 출력
 * @author  박철원 (Cheolwon Park)
 * @date    2024-03-20
 * 
 * @note    소스 코드에 사용된 scanf_s는 Visual Studio 이외의
 *	    IDE에서 실행이 불가할 수 있음에 주의하시기 바랍니다.
 */

#include <stdio.h>

int main()
{
	int no;
	printf("enter no: ");
	scanf_s(" %d", &no);
	printf("%d, %#o, %#x", no, no, no);
}
```

### 2.3 Output and Edge Cases

**Output:** Identical to the sample run. 10 is 1 × 8 + 2 = `012` in octal and `0xa` in hexadecimal. The program prints no newline at the end of the output.

```text
enter no: 10
10, 012, 0xa
enter no: 255
255, 0377, 0xff
```

> **Caution:** **Zero and negative numbers.** The `#` flag adds no `0x` prefix when the value is 0, so 0 is printed as `0, 0, 0`. Also, `%o` and `%x` expect an `unsigned int` argument, so if a negative number is entered, contrary to the problem's assumption, the program prints its bit pattern interpreted as an unsigned number. With a 32-bit `int`, -10 is interpreted as $2^{32} - 10$, giving `037777777766` and `0xfffffff6`.

```text
enter no: 0
0, 0, 0
enter no: -10
-10, 037777777766, 0xfffffff6
```

---

<br>

## 3. Problem 2: Basic Arithmetic

### 3.1 Problem

**Textbook Problem:** Chapter 3 exercise 9

Referring to the sample run, read three integers from the user and compute and print their sum and average. The average must be a floating-point value.

**Sample Run:**

```text
Enter 3 values: 1 2 4
     1
     2
     4
--------
     7
   2.3

Program ended with exit code: 0
```

### 3.2 Solution

**Approach:** Compute the sum as an integer, obtain the average by floating-point division, and print every number right-aligned in a width of 6 so that the units digits line up.

- **Sum:** `sum = first + second + third;` computes the integer sum.
- **Average:** In `sum / 3.0`, the floating-point literal `3.0` converts `sum` to `double`, so the division is floating-point. Writing `sum / 3` would perform the integer division 7 / 3 = 2 and lose the fractional part.
- **Alignment:** `%6d` prints an integer right-aligned in at least 6 columns, and `%6.1lf` prints a floating-point value rounded to one decimal place in at least 6 columns. 2.333... becomes `2.3`, preceded by 3 spaces.

**Code:** [Solution/Q2.c](Solution/Q2.c)

```c
/**
 * @file    A10303-1_C04Q2.c
 * @brief   Q2. 연산의 기본
 * @author  박철원 (Cheolwon Park)
 * @date    2024-03-23
 * 
 * @note    소스 코드에 사용된 scanf_s는 Visual Studio 이외의
 *	    IDE에서 실행이 불가할 수 있음에 주의하시기 바랍니다.
 */

#include <stdio.h>

int main()
{
	int first, second, third, sum;
	printf("Enter 3 values: ");
	scanf_s(" %d %d %d", &first, &second, &third);
	sum = first + second + third;
	printf("%6d \n", first);
	printf("%6d \n", second);
	printf("%6d \n", third);
	printf("-------- \n");
	printf("%6d \n", sum);
	printf("%6.1lf \n", sum / 3.0);
}
```

### 3.3 Output and Edge Cases

**Output:** Identical to the sample run, except that each format string ends with `" \n"`, so every line ends with one trailing space.

```text
Enter 3 values: 1 2 4
     1 
     2 
     4 
-------- 
     7 
   2.3 
```

> **Note:** A field width is a minimum width, so if the text to print is longer than 6 characters, it is printed in full without truncation and the alignment breaks. An average with 7 characters, such as `33334.7`, is one column longer than the other lines.

```text
Enter 3 values: 100000 -3 7
100000 
    -3 
     7 
-------- 
100004 
33334.7 
```

---

<br>

## 4. Problem 3: Free Code

### 4.1 Problem

Freely write code that uses what has been learned so far, and explain why you wrote it. The purpose is to summarize for yourself how well you understood the course content.

### 4.2 Solution

**Purpose of the program:** The program is a revenue calculator for prospective cafe owners: given menu prices and expected sales, it shows a menu board, a sales slip, and the difference from a target revenue. The topic was chosen so that one program uses everything learned up to this assignment: variable declarations, input with `scanf`, arithmetic, field widths in `printf`, and the distinction between integer and floating-point division.

- **Variable design:** The prices and sales counts of three drinks (Americano, vanilla latte, Hallabong ade) and three breads (blueberry bagel, strawberry cake, chicken sandwich) are stored in separate `int` variables, and the total revenue and total count of drinks and of breads and the target revenue have their own variables. The variable names are abbreviations of the menu names (`amer`, `vala`, `hala`, `blba`, `stca`, `chsa`).
- **Input stage:** The program reads the target revenue, the six menu prices, and the six sales counts in order. After the prices are read, it prints a menu board with the prices aligned by `%5d`.
- **Calculation stage:** The revenue of each menu item is price × count, and the total revenue and total count of drinks and of breads are the sums over their three items.
- **Output stage:** For each menu item, the program prints `price * count => revenue` aligned with `%5d`, `%4d`, and `%8d`, and it prints the average count and average revenue per item with `%.1lf` after floating-point division by `/ 3.0`. Finally, it prints the total count, the total revenue, and the target revenue minus the total revenue.

**Code:** [Solution/Q3.c](Solution/Q3.c)

```c
/**
 * @file    A10303-1_C04Q3.c
 * @brief   Q3. 자유 코드
 * @author  박철원 (Cheolwon Park)
 * @date    2024-03-23
 * 
 * @note    소스 코드에 사용된 scanf_s는 Visual Studio 이외의
 *	    IDE에서 실행이 불가할 수 있음에 주의하시기 바랍니다.
 */

#include <stdio.h>

int main()
{
	int amer, vala, hala;     // 순서대로 (음료) 아메리카노, 바닐라라떼, 한라봉에이드의 가격
	int amer_amount, vala_amount, hala_amount;     // 음료 항목들의 개수
	int drink, drink_amount;     // 순서대로 음료 항목들의 총 판매금액 합, 총 판매개수 합

	int blba, stca, chsa;     // 순서대로 (빵) 블루베리 베이글, 딸기 케이크, 치킨 샌드위치의 가격
	int blba_amount, stca_amount, chsa_amount;     // 빵 항목들의 개수
	int bread, bread_amount;     // 순서대로 빵 항목들의 총 매출, 총 판매개수

	int target;     // 목표 매출

	printf("============================= * ============================= \n");
	printf("안녕하세요. 예비 카페 창업주들을 위한 매출 계산 프로그램입니다. \n");
	printf("매출 예상에 쓰일 메뉴는 총 6개이며, 음료 3개와 빵 3개입니다. \n\n");
	printf(" [ 음료 메뉴판 ]                [ 빵 메뉴판 ] \n");
	printf(" 아메리카노                     블루베리 베이글 \n");
	printf(" 바닐라 라떼                    딸기 케이크 \n");
	printf(" 한라봉 에이드                  치킨 샌드위치 \n");
	printf("============================= * ============================= \n\n");

	printf("목표 매출은 얼마인가요? \n");
	scanf_s(" %d", &target);
	printf("이제 각 메뉴의 금액을 설정해주세요. \n");

	printf("\n아메리카노는 얼마에 판매할까요? (양의 정수만 입력, 최대 99,999원) \n");
	scanf_s(" %d", &amer);
	printf("\n바닐라 라떼는 얼마에 판매할까요? (양의 정수만 입력, 최대 99,999원) \n");
	scanf_s(" %d", &vala);
	printf("\n한라봉 에이드는 얼마에 판매할까요? (양의 정수만 입력, 최대 99,999원) \n");
	scanf_s(" %d", &hala);
	printf("\n블루베리 베이글은 얼마에 판매할까요? (양의 정수만 입력, 최대 99,999원) \n");
	scanf_s(" %d", &blba);
	printf("\n딸기 케이크는 얼마에 판매할까요? (양의 정수만 입력, 최대 99,999원) \n");
	scanf_s(" %d", &stca);
	printf("\n치킨 샌드위치는 얼마에 판매할까요? (양의 정수만 입력, 최대 99,999원) \n");
	scanf_s(" %d", &chsa);

	printf("\n설정하신 가격을 바탕으로 메뉴판을 완성했습니다. \n\n");
	printf("============================= * ============================= \n");
	printf(" [ 음료 메뉴판 ]                [ 빵 메뉴판 ] \n");
	printf(" 아메리카노     %5d원         블루베리 베이글  %5d원 \n", amer, blba);
	printf(" 바닐라 라떼    %5d원         딸기 케이크      %5d원 \n", vala, stca);
	printf(" 한라봉 에이드  %5d원         치킨 샌드위치    %5d원 \n", hala, chsa);
	printf("============================= * ============================= \n\n");

	printf("이제 예상되는 판매 개수를 설정해주세요. \n");

	printf("\n아메리카노는 몇 잔을 판매할까요? (양의 정수만 입력, 최대 9,999잔) \n");
	scanf_s(" %d", &amer_amount);
	printf("\n바닐라 라떼는 몇 잔을 판매할까요? (양의 정수만 입력, 최대 9,999잔) \n");
	scanf_s(" %d", &vala_amount);
	printf("\n한라봉 에이드는 몇 잔을 판매할까요? (양의 정수만 입력, 최대 9,999잔) \n");
	scanf_s(" %d", &hala_amount);
	printf("\n블루베리 베이글은 몇 개를 판매할까요? (양의 정수만 입력, 최대 9,999개) \n");
	scanf_s(" %d", &blba_amount);
	printf("\n딸기 케이크는 몇 개를 판매할까요? (양의 정수만 입력, 최대 9,999개) \n");
	scanf_s(" %d", &stca_amount);
	printf("\n치킨 샌드위치는 몇 개를 판매할까요? (양의 정수만 입력, 최대 9,999개) \n");
	scanf_s(" %d", &chsa_amount);

	drink_amount = amer_amount + vala_amount + hala_amount;
	drink = amer * amer_amount + vala * vala_amount + hala * hala_amount;

	bread_amount = blba_amount + stca_amount + chsa_amount;
	bread = blba * blba_amount + stca * stca_amount + chsa * chsa_amount;

	printf("\n\n\n\n설정하신 가격을 바탕으로 매출전표를 완성했습니다. \n\n");
	printf("======================= * ======================= \n");
	printf("[ 음료 매출 ] \n\n");
	printf("아메리카노       %5d원 * %4d잔 => %8d원 \n", amer, amer_amount, amer * amer_amount);
	printf("바닐라 라떼      %5d원 * %4d잔 => %8d원 \n", vala, vala_amount, vala * vala_amount);
	printf("한라봉 에이드    %5d원 * %4d잔 => %8d원 \n\n", hala, hala_amount, hala * hala_amount);
	printf("음료는 총 %d잔을 판매하였고, 한 메뉴당 평균 판매 잔수는 %.1lf잔입니다. \n", drink_amount, drink_amount / 3.0);
	printf("음료 매출은 총 %d원이고, 메뉴당 평균 매출은 약 %.1lf원입니다. \n\n", drink, drink / 3.0);

	printf("[ 빵 매출 ] \n\n");
	printf("블루베리 베이글  %5d원 * %4d개 => %8d원 \n", blba, blba_amount, blba * blba_amount);
	printf("딸기 케이크      %5d원 * %4d개 => %8d원 \n", stca, stca_amount, stca * stca_amount);
	printf("치킨 샌드위치    %5d원 * %4d개 => %8d원 \n\n", chsa, chsa_amount, chsa * chsa_amount);
	printf("빵은 총 %d개를 판매하였고, 한 메뉴당 평균 판매 개수는 %.1lf개입니다. \n", bread_amount, bread_amount / 3.0);
	printf("빵 매출은 총 %d원이고, 메뉴당 평균 매출은 약 %.1lf원입니다. \n\n", bread, bread / 3.0);

	printf("음료와 빵은 총 %d개를 판매하였고, 총 매출은 %d원입니다. \n", drink_amount + bread_amount, drink + bread);
	printf("======================= * ======================= \n\n");

	printf("목표 매출과 %9d원 만큼 차이납니다. \n", target - (drink + bread));
}
```

### 4.3 Output and Edge Cases

**Output:** This run enters a target revenue of 1,500,000 won, prices of 4,500, 5,500, 6,000, 3,500, 6,500, and 7,000 won, and sales counts of 100, 50, 40, 30, 20, and 25. Drink revenue is 450,000 + 275,000 + 240,000 = 965,000 won and bread revenue is 105,000 + 130,000 + 175,000 = 410,000 won, so the total is 1,375,000 won and the difference from the target is 125,000 won. The average number of drinks per item, 190 / 3 = 63.333..., is printed as `63.3`.

```text
============================= * ============================= 
안녕하세요. 예비 카페 창업주들을 위한 매출 계산 프로그램입니다. 
매출 예상에 쓰일 메뉴는 총 6개이며, 음료 3개와 빵 3개입니다. 

 [ 음료 메뉴판 ]                [ 빵 메뉴판 ] 
 아메리카노                     블루베리 베이글 
 바닐라 라떼                    딸기 케이크 
 한라봉 에이드                  치킨 샌드위치 
============================= * ============================= 

목표 매출은 얼마인가요? 
1500000
이제 각 메뉴의 금액을 설정해주세요. 

아메리카노는 얼마에 판매할까요? (양의 정수만 입력, 최대 99,999원) 
4500

바닐라 라떼는 얼마에 판매할까요? (양의 정수만 입력, 최대 99,999원) 
5500

한라봉 에이드는 얼마에 판매할까요? (양의 정수만 입력, 최대 99,999원) 
6000

블루베리 베이글은 얼마에 판매할까요? (양의 정수만 입력, 최대 99,999원) 
3500

딸기 케이크는 얼마에 판매할까요? (양의 정수만 입력, 최대 99,999원) 
6500

치킨 샌드위치는 얼마에 판매할까요? (양의 정수만 입력, 최대 99,999원) 
7000

설정하신 가격을 바탕으로 메뉴판을 완성했습니다. 

============================= * ============================= 
 [ 음료 메뉴판 ]                [ 빵 메뉴판 ] 
 아메리카노      4500원         블루베리 베이글   3500원 
 바닐라 라떼     5500원         딸기 케이크       6500원 
 한라봉 에이드   6000원         치킨 샌드위치     7000원 
============================= * ============================= 

이제 예상되는 판매 개수를 설정해주세요. 

아메리카노는 몇 잔을 판매할까요? (양의 정수만 입력, 최대 9,999잔) 
100

바닐라 라떼는 몇 잔을 판매할까요? (양의 정수만 입력, 최대 9,999잔) 
50

한라봉 에이드는 몇 잔을 판매할까요? (양의 정수만 입력, 최대 9,999잔) 
40

블루베리 베이글은 몇 개를 판매할까요? (양의 정수만 입력, 최대 9,999개) 
30

딸기 케이크는 몇 개를 판매할까요? (양의 정수만 입력, 최대 9,999개) 
20

치킨 샌드위치는 몇 개를 판매할까요? (양의 정수만 입력, 최대 9,999개) 
25




설정하신 가격을 바탕으로 매출전표를 완성했습니다. 

======================= * ======================= 
[ 음료 매출 ] 

아메리카노        4500원 *  100잔 =>   450000원 
바닐라 라떼       5500원 *   50잔 =>   275000원 
한라봉 에이드     6000원 *   40잔 =>   240000원 

음료는 총 190잔을 판매하였고, 한 메뉴당 평균 판매 잔수는 63.3잔입니다. 
음료 매출은 총 965000원이고, 메뉴당 평균 매출은 약 321666.7원입니다. 

[ 빵 매출 ] 

블루베리 베이글   3500원 *   30개 =>   105000원 
딸기 케이크       6500원 *   20개 =>   130000원 
치킨 샌드위치     7000원 *   25개 =>   175000원 

빵은 총 75개를 판매하였고, 한 메뉴당 평균 판매 개수는 25.0개입니다. 
빵 매출은 총 410000원이고, 메뉴당 평균 매출은 약 136666.7원입니다. 

음료와 빵은 총 265개를 판매하였고, 총 매출은 1375000원입니다. 
======================= * ======================= 

목표 매출과    125000원 만큼 차이납니다. 
```

> **Caution:** **Sign of the difference and integer range.** The difference is `target - (drink + bread)`, so it becomes negative when the total exceeds the target. With a target of 1,000,000 won, the last line becomes `목표 매출과   -375000원 만큼 차이납니다.`, which indicates that the target was exceeded only through the sign. Also, with the maximum values the prompts allow (a price of 99,999 won and 9,999 units), the revenue of one item, 999,890,001 won, fits in an `int`, but the sum of three items, 2,999,670,003 won, exceeds the maximum of a 32-bit `int`, 2,147,483,647, and overflows. Use `long long` for large amounts.

---

<br>

## Summary

| Concept | Key Summary |
|:--------|:------------|
| Printing in bases | `%d`, `%o`, and `%x` print the same integer as decimal, octal, and hexadecimal characters. |
| The `#` flag | `%#o` adds the prefix `0` and `%#x` adds `0x`, but no `0x` is added when the value is 0. |
| Unsigned interpretation | `%o` and `%x` interpret the argument as `unsigned int`, so a negative number is printed as a large positive number. |
| Field width | `%6d` right-aligns in at least 6 columns, and a longer value is not truncated but breaks the alignment. |
| Precision | `%6.1lf` prints a floating-point value rounded to one decimal place in at least 6 columns. |
| Floating-point average | Dividing by a floating-point literal, as in `sum / 3.0`, avoids losing the fractional part to integer division. |
| Free code design | Dividing a program into input, calculation, and output stages combines variables, arithmetic, and formatted output in one program. |
| Integer overflow | A wider type should be used when products and sums can exceed the 32-bit `int` maximum of 2,147,483,647. |

---

<br>

## Self-Check Questions

1. **Printing in bases:** Write the output of `printf("%d, %#o, %#x", 255, 255, 255);`.

   <details>
   <summary>Answer</summary>

   It is `255, 0377, 0xff`. 255 = 3 × 64 + 7 × 8 + 7, so it is 377 in octal, and 255 = 15 × 16 + 15, so it is ff in hexadecimal. The `#` flag adds `0` and `0x`, respectively.

   </details>

2. **Computing the average:** Given `int sum = 7;`, what is wrong with `printf("%6.1lf", sum / 3);`, and how should it be fixed?

   <details>
   <summary>Answer</summary>

   `sum / 3` is integer division, so the result is the `int` 2. `%lf` expects a `double` argument, so passing an `int` mismatches the format and the argument type and results in undefined behavior, and even with matching types the fractional part is already gone. Writing `sum / 3.0` performs floating-point division and prints `   2.3`.

   </details>

3. **Field width:** Write the outputs of `printf("[%6d]", 42);` and `printf("[%6d]", 1234567);`.

   <details>
   <summary>Answer</summary>

   They are `[    42]` and `[1234567]`. 42 has 2 characters, so 4 spaces are added in front to make 6 columns. A field width is a minimum width, so 1234567, with 7 characters, is printed in full without truncation.

   </details>

4. **Overflow:** In the program of Problem 3, if all three drink prices are entered as 80,000 won and all sales counts as 9,000 cups, what goes wrong in computing the total drink revenue `drink`?

   <details>
   <summary>Answer</summary>

   The revenue of one item, 80,000 × 9,000 = 720,000,000 won, fits in an `int`, but the sum of three items, 2,160,000,000 won, is larger than the 32-bit `int` maximum of 2,147,483,647. Signed integer overflow is undefined behavior, and in typical environments a wrong value such as a negative number is printed. `drink` should be declared as `long long`, and the multiplication should also be computed in `long long`.

   </details>
