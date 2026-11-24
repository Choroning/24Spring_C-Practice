# HW3 과제 안내문 — 제어문 I

[레포지토리 안내](../../../README.ko.md) | [English](Assignment.md) | [한국어](Assignment.ko.md)

> **최종 수정일:** 2026-11-24

컴퓨터언어실습Ⅰ 3분반의 3차 과제이다. 주어진 프로그램의 실행 결과와 그 이유를 쓰는 문제 두 개, 말로 주어진 조건을 수식으로 표현하는 문제 하나, 코드 작성 문제 하나로 이루어진다.

- **작성 내용:** 코드 작성 문제는 코드와 함께 반드시 코드 분석 내용을 작성해야 한다.
- **실행 예시:** 실행 예시 끝의 `Program ended with exit code: 0`은 프로그램의 출력이 아니라 Xcode 콘솔이 덧붙이는 종료 메시지이다.

---

<br>

## 문제 1. 연산자의 결과값

**교재 문항:** 4장 연습 문제 7번(일부 변경)

다음 프로그램의 결과를 작성하고, 해당 결과가 나오는 이유를 설명하라.

```c
#include <stdio.h>
int main()
{
	int no = 10, count = 20;
	char ch = 'a';
	printf(" %d", no > count);
	printf(" %d", no < count * 4);
	printf(" %d", (no != 10) || (count >= 20));
	printf(" %d", (no <= 10) && (count > 20));
	printf("\n------\n");
	printf(" %d \n", !(no > count));
	printf(" %d \n", 3);
	printf(" %d \n", ch);
	printf(" %d \n", 'b');
	printf(" %d \n", sizeof(3.2));
	printf(" %d \n", sizeof(3.2f));
	printf(" %d \n", sizeof(float));
	printf(" %d \n", sizeof(double));
}
```

---

<br>

## 문제 2. 조건의 수식 표현

**교재 문항:** 5장 연습 문제 1번(변경)

다음 설명을 컴퓨터 수식(관계 연산 및 논리 연산 등 활용)으로 표현하라. `if`문을 배우기 전이므로 수식으로만 표현한다.

- (1) 정수 `number`가 1보다 크고 10 미만이다.
- (2) 정수 `number`는 1 ~ 10에 속한다.
- (3) 문자 상수 `ch`는 `'q'`도 아니고 `'z'`도 아니다.
- (4) `no`는 1과 10 사이의 수이지만 5는 아니다.
- (5) `no`는 1과 10 사이의 수가 아니다.
- (6) `ch`는 공백 문자(`' '`)이거나 개행 문자(`'\n'`)이다.

---

<br>

## 문제 3. 증감 연산과 대입

다음 프로그램의 결과를 작성하고, 해당 결과가 나오는 이유를 설명하라.

```c
#include <stdio.h>

int main()
{
	int a = 3, b = 0;
	printf("%d , %d \n", a, b);

	b = ++a * 2;
	printf("%d , %d \n", a, b);

	a = b-- * 2;
	printf("%d , %d \n", a, b);

	a = a++ % 4;
	printf("%d , %d \n", a, b);

	a += a * b;
	printf("%d , %d \n", a, b);
}
```

---

<br>

## 문제 4. 대소 비교

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

---

<br>

문제를 풀어 본 뒤 [과제 해설](../Assignment-Explanation.ko.md)에서 정답과 풀이를 볼 수 있다.
