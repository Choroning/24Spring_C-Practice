# 6장 실습 — 함수의 작성과 활용

[레포지토리 안내](../../README.ko.md) | [English](Concepts_Lab.md) | [한국어](Concepts_Lab.ko.md)

> **최종 수정일:** 2026-10-27
>
> 문제풀이 중심의 C언어 연습, 김용일과 강문설, Ch 7

> **학습 목표:**
> 1. 수학의 함수를 입력, 하는 일, 결과로 나누어 C 함수의 매개변수, 본체, 반환값으로 옮길 수 있다
> 2. 함수의 원형, 정의, 호출의 역할과 위치를 설명할 수 있다
> 3. 매개변수와 반환값의 유무에 따른 네 가지 함수 형태를 구분하여 작성할 수 있다
> 4. 함수 호출 과정에서 매개변수와 지역 변수가 만들어지고 사라지는 과정을 추적할 수 있다
> 5. 지역 변수와 전역 변수를 함수에서 사용할 때의 결과를 예측할 수 있다

---

## 목차

- [1. 함수란 무엇인가](#1-함수란-무엇인가)
- [2. 함수의 작성](#2-함수의-작성)
  - [2.1 y = x + 3을 C 함수로](#21-y--x--3을-c-함수로)
  - [2.2 원형, 호출, 정의](#22-원형-호출-정의)
  - [2.3 매개변수가 두 개인 함수](#23-매개변수가-두-개인-함수)
  - [2.4 매개변수와 반환값이 없는 함수](#24-매개변수와-반환값이-없는-함수)
  - [2.5 함수를 쓰는 이유와 네 가지 형태](#25-함수를-쓰는-이유와-네-가지-형태)
- [3. 함수 호출과 메모리](#3-함수-호출과-메모리)
- [4. 지역 변수와 전역 변수](#4-지역-변수와-전역-변수)
  - [4.1 매개변수는 인수의 복사본이다](#41-매개변수는-인수의-복사본이다)
  - [4.2 전역 변수는 모든 함수가 공유한다](#42-전역-변수는-모든-함수가-공유한다)
- [5. 함수 실습](#5-함수-실습)
  - [5.1 입력한 개수만큼 별 출력](#51-입력한-개수만큼-별-출력)
  - [5.2 대문자와 소문자를 판별하는 함수](#52-대문자와-소문자를-판별하는-함수)
  - [5.3 거듭제곱 함수](#53-거듭제곱-함수)
  - [5.4 각도를 라디안으로 바꾸는 함수](#54-각도를-라디안으로-바꾸는-함수)
  - [5.5 양수만 합산하기](#55-양수만-합산하기)
- [요약](#요약)
- [점검 문제](#점검-문제)

---

<br>

## 1. 함수란 무엇인가

C의 **함수(function)** 는 수학에서 말하는 함수와 같은 생각에서 출발한다. sin, cos 같은 함수나 1차, 2차 함수 같은 수학의 함수는 입력, 하는 일, 결과의 세 가지로 나누어 볼 수 있으며, 1차 함수 y = x + 3에서는 다음과 같다([6장 1.1절](Concepts_Lecture.ko.md#11-함수의-필요성)).

| 구성 | y = x + 3에서 | C 함수에서 |
|:-----|:-----|:-----|
| 입력 (input) | 정수 x | 매개변수(parameter) |
| 하는 일 (to do) | x + 3을 계산하여 y에 대입 | 함수 본체(body)의 문장 |
| 결과 (result) | y | 반환값(return value) |

*표 1. 수학의 함수와 C 함수의 대응*

---

<br>

## 2. 함수의 작성

### 2.1 y = x + 3을 C 함수로

y = x + 3을 C 함수로 옮기려면 다음이 필요하다.

- **함수 이름:** `getPlus`
- **함수를 수행할 때 전달해야 할 정보(매개변수):** `int x`
- **하는 일:** `int y;`를 선언하고 `y = x + 3;`을 계산한다.
- **결과값의 반환:** 함수에게 작업을 시킨 곳으로 결과를 되돌려 준다. `return y;`
- **결과값의 데이터 타입:** `y`는 정수이므로 반환형은 `int`이다.

이를 모으면 다음 **함수 정의(function definition)** 가 된다. 반환형, 이름, 매개변수 목록으로 된 첫 줄이 **함수 헤더(function header)** 이고, 중괄호 안이 **함수 본체(function body)** 이다([6장 2.1절](Concepts_Lecture.ko.md#21-함수-정의)).

```c
int getPlus(int x)      // function header
{                       // function body
    int y;
    y = x + 3;
    return y;
}
```

### 2.2 원형, 호출, 정의

함수를 쓰는 프로그램에는 세 부분이 있다([6장 1.3절](Concepts_Lecture.ko.md#13-함수-사용의-세-가지-요소)). 다음 코드에서 `main` 앞의 `int getPlus(int x);`는 **함수 원형(function prototype)** 또는 선언이고, `main` 안의 `getPlus(val)`은 **함수 호출(function call)** 이며, `main` 뒤의 코드가 함수 정의이다.

```c
#include <stdio.h>
int getPlus(int x);     // function prototype (declaration)

int main(void)
{
    int val = 2, result;

    result = getPlus(val);                      // function call: the return value is assigned to result
    printf("1. result: %d \n", result);
    printf("2. result: %d \n", getPlus(3));     // function call: the return value is printed with %d

    return 0;
}

int getPlus(int x)      // function definition
{
    int y;
    y = x + 3;
    return y;
}
```

```text
1. result: 5 
2. result: 6 
```

- **원형:** 컴파일러는 소스를 위에서 아래로 읽으므로, 정의가 `main` 뒤에 있으면 호출 지점에서 함수의 반환형과 매개변수를 알 수 있도록 원형을 먼저 선언한다([6장 2.6절](Concepts_Lecture.ko.md#26-함수-선언-원형)).
- **호출:** `getPlus(val)`은 `val`의 값 2를 매개변수 `x`에 전달하고, 반환값 5를 `result`에 대입한다. `getPlus(3)`처럼 반환값을 변수에 저장하지 않고 `printf`의 인자로 바로 쓸 수도 있다.

### 2.3 매개변수가 두 개인 함수

2차 함수 y = a² + x - 3을 C 함수로 옮기면 매개변수가 두 개(`int a`, `int x`)인 함수 `getQuad`가 된다. 호출할 때는 인수를 매개변수의 순서대로 쉼표로 구분하여 전달한다.

```c
int getQuad(int a, int x)
{
    int y;
    y = a * a + x - 3;
    return y;
}
```

`getQuad(1, 3)`은 1 + 3 - 3 = 1을, `getQuad(2, 4)`는 4 + 4 - 3 = 5를 반환한다. 두 함수를 한 프로그램에서 호출하는 코드는 [Example_ReturnValue.c](Example_ReturnValue.c)이다.

```c
#include <stdio.h>
int getPlus(int x);
int getQuad(int a, int x);

int main()
{
    // getPlus(): one parameter
    int val = 2, result;

    result = getPlus(val);
    printf("1. result: %d \n", result);
    printf("2. result: %d \n", getPlus(3));

    // getQuad(): two parameters
    int a = 1, x = 3;

    result = getQuad(a, x);
    printf("1. result: %d \n", result);
    printf("2. result: %d \n", getQuad(2, 4));
}

int getPlus(int x) {
    int y;
    y = x + 3;
    return y;
}

int getQuad(int a, int x) {
    int y;
    y = a * a + x - 3;
    return y;
}
```

```text
1. result: 5 
2. result: 6 
1. result: 1 
2. result: 5 
```

### 2.4 매개변수와 반환값이 없는 함수

화면에 별표를 무조건 5개 출력하는 함수 `showStar`를 생각한다. 이 함수는 전달받을 정보가 없으므로 매개변수 자리에 `void`를 쓰고(빈 괄호로 써도 된다), 되돌려 줄 결과가 없으므로 반환형도 `void`로 쓴다. 반환형의 `void`는 생략할 수 없다. 반환값이 없는 함수의 `return;`은 생략할 수 있다.

```c
#include <stdio.h>
void showStar(void);    // prototype (declaration)

int main(void)
{
    showStar();         // call
    showStar();         // call

    return 0;
}

void showStar(void)     // definition
{
    printf("***** \n");
}
```

```text
***** 
***** 
```

> **참고:** 정의에서 `void showStar()`처럼 빈 괄호를 쓰면 매개변수가 없는 함수가 된다. 하지만 C23 이전의 C에서 원형을 `void showStar();`처럼 빈 괄호로 쓰면 매개변수 정보를 생략한 선언이 되어 컴파일러가 인수의 개수를 검사하지 않으므로, 원형에는 `void`를 쓰는 것이 안전하다([6장 2.4절](Concepts_Lecture.ko.md#24-매개변수와-인수)).

### 2.5 함수를 쓰는 이유와 네 가지 형태

함수를 정의하는 이유는 다음과 같다([6장 1.1절](Concepts_Lecture.ko.md#11-함수의-필요성)).

- **모듈화에 의한 프로그램의 질 향상:** 기능 단위로 나눈 함수는 따로 작성하고 시험할 수 있다.
- **유지 보수와 확장의 용이성:** 기능을 고칠 때 그 함수만 수정하면 된다.
- **문제 해결의 용이성:** 큰 문제를 작은 문제로 나누어 푼다(분할 정복, divide and conquer).

함수는 매개변수와 반환값의 유무에 따라 네 가지 형태로 나뉜다.

| 매개변수 | 반환값 | 예 |
|:---:|:---:|:-----|
| 있음 | 있음 | `int getPlus(int x)` |
| 있음 | 없음 | `void showStar(int n)` (5.1절) |
| 없음 | 있음 | `int getInput(void)` (입력을 읽어 반환) |
| 없음 | 없음 | `void showStar(void)` |

*표 2. 매개변수와 반환값의 유무에 따른 함수의 형태*

---

<br>

## 3. 함수 호출과 메모리

다음 프로그램으로 함수가 호출될 때 메모리가 어떻게 바뀌는지 살펴본다.

```c
#include <stdio.h>
int Add(int i, int j); // function prototype

int main(void) {
    int d;
    d = Add(3, 4); // function call
    printf("%d \n", d);
    return 0; // may be omitted
}

int Add(int i, int j) { // function definition
    int result = i + j;
    return result;
}
```

```text
7 
```

1. `main`이 시작되면 `main`의 지역 변수 `d`의 메모리가 만들어진다. 이 시점의 `d`에는 쓰레기 값이 있다.
2. `Add(3, 4)`를 호출하면 `Add`의 매개변수 `i`, `j`의 메모리가 새로 만들어지고 인수 3과 4가 복사된다. 이어서 지역 변수 `result`가 만들어지고 7이 저장된다.
3. `return result;`가 실행되면 값 7이 호출한 곳으로 전달되고, `Add`의 매개변수와 지역 변수 `i`, `j`, `result`의 메모리는 사라진다.
4. `main`은 반환값 7을 `d`에 대입하고 출력한다. `main`의 `return 0;`은 C99부터 생략할 수 있다.

```text
 Add 실행 중                         Add 반환 후
┌─────────────────────────┐        ┌─────────────────────────┐
│ Add   i = 3             │        │                         │
│       j = 4             │        │  (i, j, result 소멸)     │
│       result = 7        │        │                         │
├─────────────────────────┤        ├─────────────────────────┤
│ main  d = garbage       │        │ main  d = 7             │
└─────────────────────────┘        └─────────────────────────┘
```

*그림 1. Add 함수의 호출 중과 반환 후의 메모리*

이처럼 함수의 매개변수와 지역 변수는 함수가 호출될 때마다 만들어지고 함수가 끝나면 사라진다([6장 3.1절](Concepts_Lecture.ko.md#31-지역-변수), [4절](Concepts_Lecture.ko.md#4-함수-호출-오버헤드)).

---

<br>

## 4. 지역 변수와 전역 변수

### 4.1 매개변수는 인수의 복사본이다

다음 코드의 결과를 예측한다.

```c
#include <stdio.h>
int getPlus(int);

int main(void)
{
    int x = 3;
    printf("1. x: %d \n", x);
    printf("result: %d \n", getPlus(x));
    printf("2. x: %d \n", x);
}

int getPlus(int x) {
    x = x + 3;
    printf("3. x: %d \n", x);
    return x;
}
```

```text
1. x: 3 
3. x: 6 
result: 6 
2. x: 3 
```

`main`의 `x`와 `getPlus`의 매개변수 `x`는 이름만 같은 서로 다른 변수이다. 호출할 때 `main`의 `x`의 값 3이 매개변수 `x`에 복사되고, `getPlus` 안의 `x = x + 3`은 매개변수만 6으로 바꾼다. 따라서 `getPlus`가 끝난 뒤 `main`의 `x`는 3 그대로이다. 이렇게 인수의 값을 복사하여 전달하는 방식을 **값에 의한 호출(call by value)** 이라고 한다([6장 2.4절](Concepts_Lecture.ko.md#24-매개변수와-인수)).

### 4.2 전역 변수는 모든 함수가 공유한다

다음 코드의 결과를 예측한다.

```c
#include <stdio.h>
int getPlus(void);
int x; // global variable

int main(void)
{
    x += 2;
    printf("1. x: %d \n", x);
    printf("result: %d \n", getPlus());
    printf("2. x: %d \n", x);
}

int getPlus(void) {
    x = x + 3;
    printf("3. x: %d \n", x);
    return x;
}
```

```text
1. x: 2 
3. x: 5 
result: 5 
2. x: 5 
```

`x`는 모든 함수 바깥에 선언된 **전역 변수(global variable)** 이므로 `main`과 `getPlus`가 같은 메모리를 쓴다. 전역 변수는 초기값을 쓰지 않으면 0으로 초기화되므로, `main`의 `x += 2`로 `x`는 2가 된다. `getPlus`의 `x = x + 3`은 같은 전역 변수를 5로 바꾸므로, `getPlus`가 끝난 뒤 `main`에서 출력하는 `x`도 5이다([6장 3.2절](Concepts_Lecture.ko.md#32-전역-변수)).

> **주의:** 전역 변수는 어느 함수에서나 바꿀 수 있으므로, 값이 어디에서 바뀌었는지 찾기 어려워진다. 함수 사이에 값을 주고받을 때는 가능하면 매개변수와 반환값을 쓴다.

---

<br>

## 5. 함수 실습

다음 문제의 풀이 코드는 이 단원 폴더의 예제 파일이다. 메시지 끝에 `\n`이 없는 프로그램은 실제 터미널에서 다음 프롬프트가 메시지 바로 뒤에 이어진다.

### 5.1 입력한 개수만큼 별 출력

**문제:** 정수를 입력받아 함수에 전달하고, 그 개수만큼 `*`를 출력하는 함수 `showStar()`를 작성하라.

**풀이:** 2.4절의 `showStar`에 출력할 개수를 매개변수 `int n`으로 받는다. `for`문으로 `*`를 n번 출력하며, 결과를 돌려줄 필요가 없으므로 반환형은 `void`이다. n이 0 이하이면 반복이 한 번도 실행되지 않아 아무것도 출력하지 않는다.

**코드:** [Example_ShowStar.c](Example_ShowStar.c)

```c
#define _CRT_SECURE_NO_WARNINGS  // allows scanf in Visual Studio
#include <stdio.h>
void showStar(int n);

int main() {
    int num;
    printf(">> input value: ");
    scanf(" %d", &num);

    showStar(num);
}

void showStar(int n) {
    int i;
    for (i = 1; i <= n; i++) {
        printf("*");
    }
    return;
}
```

```text
>> input value: 5
*****
```

### 5.2 대문자와 소문자를 판별하는 함수

**문제:** 문자를 전달받아 대문자이면 1, 소문자이면 -1, 영문자가 아니면 0을 반환하는 함수 `isUpper()`를 작성하고 활용하라.

**풀이:** `isUpper()`는 판별 결과를 정수로 돌려주고, `main`은 그 반환값에 따라 메시지를 고른다. 판별과 출력을 나누어 두면 `isUpper()`를 다른 프로그램에서도 그대로 쓸 수 있다. 함수 안의 `return`은 값을 돌려주는 동시에 함수를 끝내므로, 첫 조건이 참이면 나머지 조건은 검사하지 않는다.

**코드:** [Example_IsUpper.c](Example_IsUpper.c)

```c
#define _CRT_SECURE_NO_WARNINGS  // allows scanf in Visual Studio
#include <stdio.h>
int isUpper(char ch);

int main()
{
    int ret;
    char alpha;
    printf(">> input char: ");
    scanf(" %c", &alpha);

    ret = isUpper(alpha);

    if (ret == 1) {
        printf("%c is a/an upper case!", alpha);
    }
    else if (ret == -1) {
        printf("%c is a/an lower case!", alpha);
    }
    else if (ret == 0) {
        printf("It's not an English alphabet!");
    }
}

int isUpper(char ch) {
    if (ch >= 'A' && ch <= 'Z') {
        return 1;
    }
    else if (ch >= 'a' && ch <= 'z') {
        return -1;
    }
    else {
        return 0;
    }
}
```

```text
>> input char: Q
Q is a/an upper case!
```

```text
>> input char: q
q is a/an lower case!
```

```text
>> input char: 7
It's not an English alphabet!
```

### 5.3 거듭제곱 함수

**문제:** 두 정수 x, y를 입력받아 xʸ를 계산하는 함수 `getPower()`를 작성하라.

**풀이:** 결과를 저장할 `xycal`을 곱셈의 항등원 1로 초기화하고, `x`를 y번 곱한다. y가 0이면 반복이 실행되지 않아 x⁰ = 1이 반환된다.

**코드:** [Example_Power.c](Example_Power.c)

```c
#define _CRT_SECURE_NO_WARNINGS  // allows scanf in Visual Studio
#include <stdio.h>
int getPower(int x, int y);

int main()
{
    int x, y;

    printf(">> input two values: ");
    scanf(" %d %d", &x, &y);

    printf("%d to the power of %d: %d", x, y, getPower(x, y));
}

int getPower(int x, int y) {
    int i, xycal = 1;
    for (i = 0; i < y; i++) {
        xycal *= x;
    }
    return xycal;
}
```

```text
>> input two values: 2 10
2 to the power of 10: 1024
```

```text
>> input two values: 3 0
3 to the power of 0: 1
```

> **주의:** y가 음수이면 반복이 실행되지 않아 1이 반환되므로 x⁻¹ 같은 값은 구할 수 없다. 또 결과가 `int`의 범위를 넘으면(예: 2³¹) 부호 있는 정수의 오버플로가 일어나 정의되지 않은 동작이 된다.

### 5.4 각도를 라디안으로 바꾸는 함수

**문제:** 0°\~359°의 각도를 라디안으로 바꾸는 함수 `getRadian()`을 작성하라. 0\~359만 입력된다고 가정하므로 범위 검사는 하지 않는다. π는 `#define PI 3.14159`로 정의하고, 라디안 = 각도 / 180 × π이다.

**풀이:** 각도는 `int`로 받지만 결과는 소수이므로 반환형을 `double`로 한다. `deg / 180.0`처럼 실수 상수로 나누어야 정수 나눗셈이 일어나지 않는다. `deg / 180`으로 쓰면 90 / 180이 0이 되어 결과가 0이 된다.

**코드:** [Example_Radian.c](Example_Radian.c)

```c
#define _CRT_SECURE_NO_WARNINGS  // allows scanf in Visual Studio
#include <stdio.h>
#define PI 3.14159
double getRadian(int deg);

int main()
{
    int deg;

    printf(">> input degree(0~359): ");
    scanf(" %d", &deg);

    printf("The radian value of %d degrees is %.2lf", deg, getRadian(deg));
}
double getRadian(int deg) {
    double caldeg;
    caldeg = (deg / 180.0) * PI;

    return caldeg;
}
```

```text
>> input degree(0~359): 90
The radian value of 90 degrees is 1.57
```

```text
>> input degree(0~359): 180
The radian value of 180 degrees is 3.14
```

### 5.5 양수만 합산하기

**문제:** 정수 10개를 차례로 입력받으면서 함수 `getSign()`으로 각 정수가 양수인지 확인하고, 양수인 정수만 더한 결과를 출력하라.

**풀이:** `getSign()`은 판별 결과를 1 또는 0으로 돌려주므로, `if (getSign(val))`처럼 반환값을 조건식으로 바로 쓸 수 있다. 입력은 `do-while`로 10번 반복한다. 이 코드의 `getSign()`은 0도 1로 판별하지만, 0을 더해도 합은 바뀌지 않으므로 결과는 양수만 더한 것과 같다. 같은 과제를 `for`문과 `val > 0` 조건으로 푼 코드는 [HW06 문제 2](../../Coursework/HW06_Functions/Assignment-Explanation.ko.md#3-문제-2-조건에-따라-합-구하기)에 있다.

**코드:** [Example_PositiveSum.c](Example_PositiveSum.c)

```c
#define _CRT_SECURE_NO_WARNINGS  // allows scanf in Visual Studio
#include <stdio.h>
int getSign(int val);

int main()
{
    int count = 1, val, sum = 0;

    do {
        printf(">> (%d) input val: ", count);
        scanf(" %d", &val);

        if (getSign(val)) {
            sum += val;
        }
        count++;
    } while (count <= 10);

    printf("-> sum of positive values: %d", sum);
}
int getSign(int val) {
    if (val >= 0) {
        return 1;
    }
    else {
        return 0;
    }
}
```

```text
>> (1) input val: 3
>> (2) input val: -2
>> (3) input val: 5
>> (4) input val: 0
>> (5) input val: -7
>> (6) input val: 8
>> (7) input val: 1
>> (8) input val: -1
>> (9) input val: 4
>> (10) input val: 6
-> sum of positive values: 27
```

3 + 5 + 0 + 8 + 1 + 4 + 6 = 27이다.

---

<br>

## 요약

| 개념 | 핵심 요약 |
|:-----|:-----|
| 함수 | 입력(매개변수)을 받아 정해진 일(본체)을 하고 결과(반환값)를 돌려주는 코드 묶음이다. |
| 함수 정의 | 반환형, 이름, 매개변수 목록으로 된 헤더와 중괄호 안의 본체로 이루어진다. |
| 함수 원형 | 정의가 호출보다 뒤에 있을 때 반환형과 매개변수를 컴파일러에 미리 알리는 선언이다. |
| 함수 호출 | 인수를 매개변수의 순서대로 전달하여 함수를 실행하며, 반환값을 변수에 저장하거나 수식에 바로 쓴다. |
| `void` | 반환값이 없으면 반환형을 `void`로 쓰고, 매개변수가 없으면 괄호 안에 `void`를 쓴다. |
| 네 가지 형태 | 매개변수와 반환값의 유무에 따라 네 가지 함수 형태가 있다. |
| 호출과 메모리 | 매개변수와 지역 변수는 호출될 때 만들어지고 함수가 끝나면 사라진다. |
| 값에 의한 호출 | 매개변수는 인수의 복사본이므로 함수 안에서 바꿔도 호출한 쪽의 변수는 바뀌지 않는다. |
| 전역 변수 | 모든 함수 바깥에 선언되어 모든 함수가 공유하며, 초기값이 없으면 0으로 초기화된다. |

---

<br>

## 점검 문제

1. **함수의 구성:** 반지름 r을 받아 원의 넓이 πr²을 돌려주는 함수를 작성하려 한다. 함수 이름, 매개변수, 반환형을 정하고 원형을 쓰라.

   <details>
   <summary>정답</summary>

   예를 들어 이름은 `getCircleArea`, 매개변수는 `double r`, 결과가 소수이므로 반환형은 `double`이다. 원형은 `double getCircleArea(double r);`이다.

   </details>

2. **원형:** 2.2절의 프로그램에서 원형 `int getPlus(int x);`를 지우면 C99 이후의 컴파일러에서 어떤 일이 일어나는가?

   <details>
   <summary>정답</summary>

   `main`에서 `getPlus`를 호출하는 시점에 선언이 없으므로, C99부터 제거된 암시적 함수 선언이 되어 컴파일러가 오류나 경고를 낸다. 원형을 다시 넣거나 `getPlus`의 정의를 `main`보다 앞으로 옮겨야 한다.

   </details>

3. **값에 의한 호출:** 4.1절의 `getPlus`가 매개변수를 6으로 바꿨는데도 `main`의 `x`가 3인 이유를 설명하라.

   <details>
   <summary>정답</summary>

   호출할 때 `main`의 `x`의 값 3이 `getPlus`의 매개변수 `x`에 복사될 뿐, 두 변수는 서로 다른 메모리이다. `getPlus` 안에서는 복사본만 바뀌고, 그 복사본은 함수가 끝나면 사라진다.

   </details>

4. **전역 변수:** 4.2절의 프로그램에서 `main` 안에 `int x = 10;`을 추가로 선언하면 출력은 어떻게 바뀌는가?

   <details>
   <summary>정답</summary>

   `main` 안에서는 지역 변수 `x`가 전역 변수를 가리므로 `x += 2`로 지역 변수가 12가 되고 `1. x: 12`가 출력된다. `getPlus`는 전역 변수 `x`(0)를 3으로 바꾸어 `3. x: 3`과 `result: 3`을 출력하고, 마지막 줄은 지역 변수를 출력하여 `2. x: 12`가 된다.

   </details>

5. **정수 나눗셈:** 5.4절의 `getRadian`에서 `(deg / 180.0) * PI`를 `deg / 180 * PI`로 바꾸면 90을 입력했을 때 결과는 무엇인가?

   <details>
   <summary>정답</summary>

   `deg / 180`은 정수 나눗셈이므로 90 / 180 = 0이 되고, 0 × π = 0이 반환되어 `0.00`이 출력된다. 180 이상의 각도에서는 몫만 남아 180이면 π, 270이면 역시 1 × π가 되어 틀린 값이 나온다.

   </details>
