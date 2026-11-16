# HW4 과제 안내문 — 제어문 II

[레포지토리 안내](../../../README.ko.md) | [English](Assignment.md) | [한국어](Assignment.ko.md)

> **최종 수정일:** 2026-11-16

컴퓨터언어실습Ⅰ 3분반의 4차 과제이다. 교재 5장의 연습 문제 다섯 개로 이루어지며, 문제 3과 4는 수업 중에 푼 예시 코드를 다른 제어문으로 바꾸어 쓰는 문제이다.

- **제출 기한:** 2024-04-08 (월) 14:00, 수업 시작 전까지이다. 기한이 지나면 과제가 자동으로 비공개된다.
- **제출 방법:** 과목이 배포한 과제 제출 양식(.hwp)에 작성하여 블랙보드의 과제 제출란에만 제출한다.
- **작성 내용:** 코드 작성 문제는 코드와 함께 반드시 코드 분석 내용을 작성해야 한다.
- **실행 예시:** 실행 예시 끝의 `Program ended with exit code: 0`은 프로그램의 출력이 아니라 Xcode 콘솔이 덧붙이는 종료 메시지이다.

---

<br>

## 문제 1. 영문자 변환

**교재 문항:** 5장 연습 문제 9번

실행 예시를 참고하여 사용자로부터 임의의 영문 소문자를 입력받은 후, 대문자로 변환하여 출력하는 프로그램을 작성하라.

**실행 예시:**

```text
>> Input char: q
-> Changed lower case q to upper case Q!

Program ended with exit code: 0
```

```text
>> Input char: G
-> Input error!

Program ended with exit code: 0
```

---

<br>

## 문제 2. 홀짝 판별

**교재 문항:** 5장 연습 문제 11번

실행 예시를 참고하여 사용자로부터 임의의 정수를 입력받은 후, 홀짝 여부를 판별하여 출력하는 프로그램을 작성하라.

**실행 예시:**

```text
>> Input value: 3
-> 3 is an odd number!

Program ended with exit code: 0
```

```text
>> Input value: 6
-> 6 is an even number!

Program ended with exit code: 0
```

---

<br>

## 문제 3. switch-if 변환 (1)

**교재 문항:** 5장 연습 문제 14번

예시 코드를 참고하여 if문을 사용한 코드를 switch문을 사용하도록 바꾸어 작성하라.

**예시 코드:**

```c
#include <stdio.h>

int main()
{
	int score;
	printf(">> Input score(0~100): ");
	scanf(" %d", &score);

	if (score >= 90 && score <= 100)
		printf("%d is a/an A!", score);
	else if (score >= 80 && score <= 89)
		printf("%d is a/an B!", score);
	else if (score >= 70 && score <= 79)
		printf("%d is a/an C!", score);
	else if (score >= 60 && score <= 69)
		printf("%d is a/an D!", score);
	else if (score < 60 && score >= 0)
		printf("%d is a/an F!", score);
	else
		printf("Input error!");
}
```

---

<br>

## 문제 4. switch-if 변환 (2)

**교재 문항:** 5장 연습 문제 15번

예시 코드를 참고하여 switch문을 사용한 코드를 if문을 사용하도록 바꾸어 작성하라.

**예시 코드:**

```c
#include <stdio.h>

int main()
{
	int grade;

	printf(">> Input grade(1~7): ");
	scanf(" %d", &grade);

	switch (grade) {
	case 1:
		printf("Very good!");
		break;
	case 2:
	case 3:
		printf("Good!");
		break;
	case 4:
	case 5:
		printf("So So!");
		break;
	case 6:
	case 7:
		printf("Cheer up!");
		break;
	default:
		printf("Input error!");
	}
}
```

---

<br>

## 문제 5. switch 분기 연습

**교재 문항:** 5장 연습 문제 16번

사용자로부터 임의의 영문자를 입력받은 후, 해당 영문자의 첫 글자로 시작하는 프로그래밍 언어명을 출력하는 프로그램을 작성하라.

**프로그램 요구사항:**

1. `switch`문을 사용하여 작성한다.
2. 각 영문자는 아래와 같이 대응한다.
    - `c` 또는 `C`를 입력하면 `C Language`를 출력한다.
    - `p` 또는 `P`를 입력하면 `Python`을 출력한다.
    - `j` 또는 `J`를 입력하면 `JAVA`를 출력한다.
    - `l` 또는 `L`을 입력하면 `LISP`를 출력한다.
    - 이외의 영문자를 입력하면 `Input Error!`를 출력한다.

**실행 예시:**

```text
>> Input the character: p
-> Python

Program ended with exit code: 0
```

```text
>> Input the character: C
-> C Language

Program ended with exit code: 0
```

```text
>> Input the character: m
-> Input Error!

Program ended with exit code: 0
```

---

<br>

문제를 풀어 본 뒤 [과제 해설](../Assignment-Explanation.ko.md)에서 정답과 풀이를 볼 수 있다.
