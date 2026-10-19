# Chapter 6 Exercises — Functions

[Repository Guide](../../README.md) | [English](Exercises.md) | [한국어](Exercises.ko.md)

> **Last Updated:** 2026-10-19

**Problem Source:** Prof. Younghee Im, Computer Language Ⅰ (DCCS101-04)

---

<br>

## Exercise 1: Rounding a Real Number

**Problem:** Define a function `round()` that receives a real number and returns the integer obtained by rounding it at the first decimal place. Using this function, write a program that reads real numbers until `0.0` is entered and prints the rounded result of each in turn.

|               | Program       | `round()` Function |
|:-------------:|:------------:|:-----------:|
|**Input**       |Real number (0.0 to quit)|Real number          |
|**Output**      |Rounded result   |Rounded value       |

*Table 1. Input and output of the program and the `round()` function in Exercise 1*

**Program Requirements:**

- The `round()` function must work correctly for both positive and negative numbers.

**Sample Run:**

```text
실수를 입력하세요 (0.0 입력 시 종료): 2.75
2.750000의 반올림 결과 = 3

실수를 입력하세요 (0.0 입력 시 종료): 9.1
9.100000의 반올림 결과 = 9

실수를 입력하세요 (0.0 입력 시 종료): -6.3
-6.300000의 반올림 결과 = -6

실수를 입력하세요 (0.0 입력 시 종료): -7.815
-7.815000의 반올림 결과 = -8

실수를 입력하세요 (0.0 입력 시 종료): 0.0

Program ended with exit code: 0
```

**[Solution](Solutions.md#exercise-1-rounding-a-real-number)**

---

<br>

## Exercise 2: Leap Year Test

**Problem:** Define a function `isLeapYear()` that receives a year and determines whether it is a leap year. Using this function, write a program that prints all leap years from 2000 to 2150, 10 per line.

The leap year conditions are as follows.

1. A year divisible by 4 is a leap year.
2. A year that meets condition 1 and is divisible by 100 is a common year.
3. A year that meets conditions 1 and 2 and is divisible by 400 is a leap year.

|               | Program                    | `isLeapYear()` Function |
|:-------------:|:-------------------------:|:------------:|
|**Input**       | None                       | Year          |
|**Output**      |List of leap years from 2000 to 2150|1: leap year, 0: common year|

*Table 2. Input and output of the program and the `isLeapYear()` function in Exercise 2*

**Program Requirements:**

1. Print the results 10 per line.
2. Separate the items with a space character.

**Sample Run:**

```text
-------------------------------------------------
               2000~2150년 사이의 윤년
-------------------------------------------------
2000 2004 2008 2012 2016 2020 2024 2028 2032 2036
2040 2044 2048 2052 2056 2060 2064 2068 2072 2076
2080 2084 2088 2092 2096 2104 2108 2112 2116 2120
2124 2128 2132 2136 2140 2144 2148

Program ended with exit code: 0
```

**[Solution](Solutions.md#exercise-2-leap-year-test)**

---

<br>

## Exercise 3: Number of Days in a Month

**Problem:** Define a function `GetDaysOfMonth()` that receives a year and a month and returns the number of days in that month. Using this function, write a program that reads a year and a month from the user and prints the number of days in that month.

|               | Program    | `GetDaysOfMonth()` Function |
|:-------------:|:---------:|:--------------------:|
|**Input**       | Year, month    | Year, month               |
|**Output**      |Days of that month| Number of days                |

*Table 3. Input and output of the program and the `GetDaysOfMonth()` function in Exercise 3*

**Program Requirements:**

1. January, March, May, July, August, October, and December have 31 days, and April, June, September, and November have 30 days.
2. February has 29 days in a leap year and 28 days in a common year.
3. Determine whether the year is a leap year with the `isLeapYear()` function written in Exercise 2.

**Sample Run:**

```text
연도와 월을 입력하세요: 2017 4
2017년 4월은 30일까지 있습니다.

Program ended with exit code: 0
```

```text
연도와 월을 입력하세요: 2020 8
2020년 8월은 31일까지 있습니다.

Program ended with exit code: 0
```

```text
연도와 월을 입력하세요: 2000 2
2000년 2월은 29일까지 있습니다.

Program ended with exit code: 0
```

```text
연도와 월을 입력하세요: 2100 2
2100년 2월은 28일까지 있습니다.

Program ended with exit code: 0
```

**[Solution](Solutions.md#exercise-3-number-of-days-in-a-month)**
