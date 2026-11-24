# HW5 과제 안내문 — 제어문 III

[레포지토리 안내](../../../README.ko.md) | [English](Assignment.md) | [한국어](Assignment.ko.md)

> **최종 수정일:** 2026-11-24

컴퓨터언어실습Ⅰ 3분반의 5차 과제이다. 반복문을 다루는 네 문제로 이루어진다.

- **작성 내용:** 코드 작성 문제는 코드와 함께 반드시 코드 분석 내용을 작성해야 한다.
- **실행 예시:** 실행 예시 끝의 `Program ended with exit code: 0`은 프로그램의 출력이 아니라 Xcode 콘솔이 덧붙이는 종료 메시지이다.

---

<br>

## 문제 1. 반복문 연습 (1)

사용자로부터 1~100 사이의 정수(no)를 연속으로 입력받아 최댓값과 최솟값을 출력하는 프로그램을 작성하라.

**프로그램 요구사항:**

1. `while`문을 이용한다.
2. `0`이 입력되면 더 이상 입력을 받지 않고, 최댓값과 최솟값을 출력한다.
3. 실행 예시를 참고하여 입력받은 값이 0~100이 아닐 경우에 대해 예외 처리한다.

**실행 예시:**

```text
Input value(no): 3
Input value(no): 9
Input value(no): 54
Input value(no): 87
Input value(no): 5
Input value(no): 234
-- Error --
Input value(no): 3
Input value(no): 0
MAX: 87, MIN: 3

Program ended with exit code: 0
```

---

<br>

## 문제 2. 반복문 연습 (2)

0을 포함한 양수(0 이상의 수)만 입력된다고 가정한다. 입력된 양수의 합과 평균을 계산하여 출력하라. 이때, 처음부터 0이 입력되면 `0만 입력되었습니다!`가 출력되도록 한다.

**실행 예시:**

```text
>> Input value: 1
>> Input value: 2
>> Input value: 2
>> Input value: 0
=====================
-> SUM: 5, AVE: 1.7

Program ended with exit code: 0
```

```text
>> Input value: 0
=====================
-> 0만 입력되었습니다!

Program ended with exit code: 0
```

---

<br>

## 문제 3. 반복문 연습 (3)

`for`문을 이용하여 `1-2+3- ... +9-10`의 계산 결과를 출력하는 프로그램을 작성하라.

**실행 예시:**

```text
1 - 2 + 3 - 4 + 5 - 6 + 7 - 8 + 9 - 10 = -5

Program ended with exit code: 0
```

---

<br>

## 문제 4. 반복문 연습 (4)

중첩 `for`문을 이용하여 실행 예시와 같이 출력하는 코드를 작성하라.

**실행 예시:**

```text
0
0 1
0 1 2
0 1 2 3
0 1 2 3 4
0 1 2 3
0 1 2
0 1
0

Program ended with exit code: 0
```

---

<br>

문제를 풀어 본 뒤 [과제 해설](../Assignment-Explanation.ko.md)에서 정답과 풀이를 볼 수 있다.
