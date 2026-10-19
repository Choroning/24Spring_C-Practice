# HW3 과제 해설 — 제어문 I

[레포지토리 안내](../../README.ko.md) | [English](Assignment-Explanation.md) | [한국어](Assignment-Explanation.ko.md)

> **최종 수정일:** 2026-10-19

> **학습 목표:**
> 1. 조건 연산자 `? :`의 형식과 평가 순서를 설명할 수 있다
> 2. 조건 연산자를 두 번 적용하여 세 값 중 최댓값을 구할 수 있다
> 3. 같은 값이나 음수가 섞인 입력에서도 결과가 맞는지 경계 조건을 점검할 수 있다

**문항 출처:** 이종욱 교수, 컴퓨터언어실습Ⅰ (DCCS103-03)

---

## 목차

- [1. 과제 구성과 실행 방법](#1-과제-구성과-실행-방법)
- [2. 문제 1: 대소 비교](#2-문제-1-대소-비교)
  - [2.1 문제](#21-문제)
  - [2.2 풀이](#22-풀이)
  - [2.3 실행 결과와 경계 조건](#23-실행-결과와-경계-조건)
- [요약](#요약)
- [점검 문제](#점검-문제)

---

<br>

## 1. 과제 구성과 실행 방법

`if`문 없이 조건 연산자만으로 세 정수 중 가장 큰 값을 구하는 과제이다. 조건 연산자는 조건에 따라 두 값 중 하나를 고르는 수식이므로, 선택 구조를 문장이 아니라 수식으로 표현하는 연습이 된다.

```text
Coursework/HW03_Control-Statements-I/
├── Assignment-Explanation.ko.md   # 이 문서 (한국어)
├── Assignment-Explanation.md      # 이 문서 (영어)
└── Solution/
    └── Q1.c                       # 문제 1: 대소 비교
```

*그림 1. HW3 과제의 디렉토리 구성*

프로그램은 Visual Studio(MSVC)에서 작성되어 입력에 `scanf_s`를 쓴다. `scanf_s`는 MSVC가 제공하는 함수이고 gcc와 clang이 쓰는 표준 라이브러리 대부분에는 없으므로, 다른 환경에서는 코드를 바꾸지 않고 `-Dscanf_s=scanf` 옵션으로 `scanf`로 대체하여 컴파일한다. 이 문서의 실행 결과는 다음 명령으로 얻은 것이다.

```bash
cd Coursework/HW03_Control-Statements-I/Solution
gcc -std=c99 -Wall -Dscanf_s=scanf -o Q1 Q1.c
./Q1
```

과제 문서의 실행 예시 끝에 있는 `Program ended with exit code: 0`은 프로그램의 출력이 아니라 Xcode 콘솔이 덧붙이는 종료 메시지이다.

---

<br>

## 2. 문제 1: 대소 비교

### 2.1 문제

공백으로 구분된 3개의 정수 정보를 사용자로부터 입력받은 후 가장 큰 값을 출력하라. 조건 연산자만을 사용해야 한다.

**실행 예시:**

```text
Input 3 values: 3 -4 9
Max: 9

Program ended with exit code: 0
```

```text
Input 3 values: 23 4 -5
Max: 23

Program ended with exit code: 0
```

```text
Input 3 values: -12 -3 -24
Max: -3

Program ended with exit code: 0
```

### 2.2 풀이

**접근 방법:** 조건 연산자 `조건 ? 값1 : 값2`는 조건이 참이면 값1을, 거짓이면 값2를 수식의 값으로 낸다([4장 8.1절](../../Lecture-Notes/Ch04_Operators/Concepts_Lecture.ko.md#81-삼항-연산자)). 두 값의 최댓값은 조건 연산자 하나로 구할 수 있으므로, 세 값의 최댓값은 두 단계로 나누어 구한다.

- **1단계:** `max1 = num1 > num2 ? num1 : num2;`로 앞의 두 수 중 큰 값을 구한다.
- **2단계:** `max2 = max1 > num3 ? max1 : num3;`로 1단계의 결과와 세 번째 수 중 큰 값을 구한다. 이 값이 세 수의 최댓값이다.
- **괄호가 없어도 되는 이유:** 관계 연산자 `>`는 조건 연산자보다, 조건 연산자는 대입 연산자보다 우선순위가 높다([4장 10.1절](../../Lecture-Notes/Ch04_Operators/Concepts_Lecture.ko.md#101-우선순위-표)). 따라서 `max1 = num1 > num2 ? num1 : num2`는 `max1 = ((num1 > num2) ? num1 : num2)`로 계산된다.

**코드:** [Solution/Q1.c](Solution/Q1.c)

```c
/**
 * @file    A10303-1_C05Q1.c
 * @brief   Q1. 대소 비교
 * @author  박철원 (Cheolwon Park)
 * @date    2024-03-28
 * 
 * @note    소스 코드에 사용된 scanf_s는 Visual Studio 이외의
 *	    IDE에서 실행이 불가할 수 있음에 주의하시기 바랍니다.
 */

#include <stdio.h>

int main()
{
	int num1, num2, num3;
	int max1, max2;

	printf("Input 3 values: ");
	scanf_s(" %d %d %d", &num1, &num2, &num3);

	max1 = num1 > num2 ? num1 : num2;
	max2 = max1 > num3 ? max1 : num3;

	printf("Max: %d", max2);
}
```

### 2.3 실행 결과와 경계 조건

**실행 결과:** 세 실행 예시와 같다. 출력 끝에 줄바꿈을 출력하지 않는다. 세 번째 실행에서는 -12 > -3이 거짓이므로 `max1`이 -3이 되고, -3 > -24가 참이므로 `max2`도 -3이 된다.

```text
Input 3 values: 3 -4 9
Max: 9
Input 3 values: 23 4 -5
Max: 23
Input 3 values: -12 -3 -24
Max: -3
```

> **참고:** **같은 값이 있을 때.** 두 수가 같으면 `num1 > num2`가 거짓이 되어 `num2`가 선택되지만, 두 값이 같으므로 결과는 달라지지 않는다. 세 수가 모두 같아도 그 값이 그대로 출력된다. 중간 변수 없이 하나의 수식으로 쓰려면 `num1 > num2 ? (num1 > num3 ? num1 : num3) : (num2 > num3 ? num2 : num3)`처럼 조건 연산자를 중첩한다.

```text
Input 3 values: 5 5 5
Max: 5
```

---

<br>

## 요약

| 개념 | 핵심 요약 |
|:-----|:-----|
| 조건 연산자 | `조건 ? 값1 : 값2`는 조건이 참이면 값1, 거짓이면 값2를 수식의 값으로 내는 C의 유일한 삼항 연산자이다. |
| 두 값의 최댓값 | `a > b ? a : b`는 `if`문 없이 두 값 중 큰 값을 구한다. |
| 세 값의 최댓값 | 두 값의 최댓값을 먼저 구한 뒤 세 번째 값과 다시 비교하는 두 단계로 구한다. |
| 우선순위 | 관계 연산자, 조건 연산자, 대입 연산자 순으로 먼저 결합하므로 이 식에는 괄호가 필요 없다. |
| 경계 조건 | 같은 값이 있거나 모두 음수여도 비교만 하므로 결과가 맞다. |

---

<br>

## 점검 문제

1. **조건 연산자의 평가:** `int x = 1, y = 0; int r = x ? 10 : y++;`를 실행한 뒤 `r`과 `y`의 값을 쓰라.

   <details>
   <summary>정답</summary>

   `r`은 10, `y`는 0이다. 조건 `x`가 참(0이 아님)이므로 두 번째 피연산자 10이 수식의 값이 되고, 세 번째 피연산자 `y++`는 평가되지 않는다. 조건 연산자는 두 값 중 선택된 쪽만 평가한다.

   </details>

2. **중간 과정 추적:** 입력이 `23 4 -5`일 때 `max1`과 `max2`의 값을 차례로 쓰라.

   <details>
   <summary>정답</summary>

   23 > 4가 참이므로 `max1`은 23이고, 23 > -5가 참이므로 `max2`는 23이다.

   </details>

3. **최솟값:** 같은 방법으로 세 값 중 가장 작은 값을 구하려면 코드의 어느 부분을 바꾸어야 하는가?

   <details>
   <summary>정답</summary>

   두 조건 연산자의 비교를 `>`에서 `<`로 바꾼다. `min1 = num1 < num2 ? num1 : num2;`, `min2 = min1 < num3 ? min1 : num3;`이 세 값의 최솟값이다.

   </details>

4. **하나의 수식:** 중간 변수 없이 조건 연산자만으로 `a`, `b`, `c`의 최댓값을 구하는 수식을 쓰고, `a = 5, b = 9, c = 7`일 때의 값을 구하라.

   <details>
   <summary>정답</summary>

   `a > b ? (a > c ? a : c) : (b > c ? b : c)`이다. 5 > 9가 거짓이므로 `(b > c ? b : c)`가 평가되고, 9 > 7이 참이므로 값은 9이다.

   </details>
