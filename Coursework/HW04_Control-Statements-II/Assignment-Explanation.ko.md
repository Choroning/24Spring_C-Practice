# HW4 과제 해설 — 제어문 II

[레포지토리 안내](../../README.ko.md) | [English](Assignment-Explanation.md) | [한국어](Assignment-Explanation.ko.md)

> **최종 수정일:** 2026-10-19
>
> 문제풀이 중심의 C언어 연습, 김용일 외, Ch 5

> **학습 목표:**
> 1. 문자의 ASCII 코드 범위를 비교하여 영문자의 대소문자를 판별하고 변환할 수 있다
> 2. 나머지 연산자로 음수를 포함한 정수의 홀짝을 판별할 수 있다
> 3. 범위 조건을 `switch`문의 정수 case로 바꾸고 범위 밖의 값을 따로 처리할 수 있다
> 4. 여러 case를 묶은 `switch`문을 `||`를 쓴 `if-else`문으로 바꿀 수 있다
> 5. case 레이블을 연달아 두어 대문자와 소문자 입력을 같은 문장으로 처리할 수 있다

**문항 출처:** 이종욱 교수, 컴퓨터언어실습Ⅰ (DCCS103-03)

---

## 목차

- [1. 과제 구성과 실행 방법](#1-과제-구성과-실행-방법)
- [2. 문제 1: 영문자 변환](#2-문제-1-영문자-변환)
  - [2.1 문제](#21-문제)
  - [2.2 풀이](#22-풀이)
  - [2.3 실행 결과와 경계 조건](#23-실행-결과와-경계-조건)
- [3. 문제 2: 홀짝 판별](#3-문제-2-홀짝-판별)
  - [3.1 문제](#31-문제)
  - [3.2 풀이](#32-풀이)
  - [3.3 실행 결과와 경계 조건](#33-실행-결과와-경계-조건)
- [4. 문제 3: switch-if 변환 (1)](#4-문제-3-switch-if-변환-1)
  - [4.1 문제](#41-문제)
  - [4.2 풀이](#42-풀이)
  - [4.3 실행 결과와 경계 조건](#43-실행-결과와-경계-조건)
- [5. 문제 4: switch-if 변환 (2)](#5-문제-4-switch-if-변환-2)
  - [5.1 문제](#51-문제)
  - [5.2 풀이](#52-풀이)
  - [5.3 실행 결과와 경계 조건](#53-실행-결과와-경계-조건)
- [6. 문제 5: switch 분기 연습](#6-문제-5-switch-분기-연습)
  - [6.1 문제](#61-문제)
  - [6.2 풀이](#62-풀이)
  - [6.3 실행 결과와 경계 조건](#63-실행-결과와-경계-조건)
- [요약](#요약)
- [점검 문제](#점검-문제)

---

<br>

## 1. 과제 구성과 실행 방법

교재 5장(조건문)의 연습 문제로 `if`문과 `switch`문을 연습하는 과제이다. 문제 1과 2는 `if-else`로 문자와 정수를 판별하고, 문제 3과 4는 같은 동작을 하는 `if`문과 `switch`문을 서로 바꾸어 쓰며, 문제 5는 `switch`문으로 문자 입력에 따라 분기한다.

```text
Coursework/HW04_Control-Statements-II/
├── Assignment-Explanation.ko.md   # 이 문서 (한국어)
├── Assignment-Explanation.md      # 이 문서 (영어)
└── Solution/
    ├── Q1.c                       # 문제 1: 영문자 변환
    ├── Q2.c                       # 문제 2: 홀짝 판별
    ├── Q3.c                       # 문제 3: if문을 switch문으로 변환
    ├── Q4.c                       # 문제 4: switch문을 if문으로 변환
    └── Q5.c                       # 문제 5: switch 분기 연습
```

*그림 1. HW4 과제의 디렉토리 구성*

다섯 프로그램은 모두 표준 `scanf`를 쓰므로 어느 C 컴파일러에서나 그대로 컴파일된다. 이 문서의 실행 결과는 다음과 같은 명령으로 얻은 것이다.

```bash
cd Coursework/HW04_Control-Statements-II/Solution
gcc -std=c99 -Wall -o Q1 Q1.c
./Q1
```

과제 문서의 실행 예시 끝에 있는 `Program ended with exit code: 0`은 프로그램의 출력이 아니라 Xcode 콘솔이 덧붙이는 종료 메시지이다.

---

<br>

## 2. 문제 1: 영문자 변환

### 2.1 문제

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

### 2.2 풀이

**접근 방법:** C의 문자는 정수 코드로 저장되므로 관계 연산자로 범위를 비교하고 산술 연산으로 변환할 수 있다. ASCII에서 소문자 `'a'`\~`'z'`는 97\~122, 대문자 `'A'`\~`'Z'`는 65\~90으로 각각 연속되어 있고, 같은 글자의 소문자와 대문자는 `'a' - 'A'` = 32만큼 차이 난다.

- **입력:** `scanf(" %c", &ch)`의 공백이 앞의 공백 문자를 건너뛰고 문자 하나를 읽는다.
- **소문자 판별과 변환:** `ch >= 'a' && ch <= 'z'`이면 소문자이며, `ch - 32`가 대응하는 대문자이다.
- **대문자 처리:** 코드는 `ch >= 'A' && ch <= 'Z'`인 경우도 따로 처리하여 `ch + 32`, 즉 소문자로 바꾸어 출력한다. 문제가 요구한 동작보다 넓은 기능이다.
- **그 밖의 문자:** 숫자나 기호처럼 영문자가 아니면 `-> Input error!`를 출력한다.

**코드:** [Solution/Q1.c](Solution/Q1.c)

```c
/**
 * @file    A10303-2_C05Q1.c
 * @brief   Q1. 영문자 변환
 * @author  박철원 (Cheolwon Park)
 * @date    2024-04-05
 */

#include <stdio.h>

int main()
{
	char ch;

	printf(">> Input char: ");
	scanf(" %c", &ch);

	if (ch >= 'a' && ch <= 'z') {
		printf("-> Changed lower case %c to upper case %c!\n", ch, ch - 32);
	} else if (ch >= 'A' && ch <= 'Z') {
		printf("-> Changed upper case %c to lower case %c!\n", ch, ch + 32);
	} else {
		printf("-> Input error!\n");
	}

	return 0;
}
```

### 2.3 실행 결과와 경계 조건

**실행 결과:** 소문자 `q`의 결과는 실행 예시와 같다. 대문자 `G`는 실행 예시에서 `-> Input error!`이지만, 코드는 대문자를 소문자로 바꾸는 분기를 두었으므로 `-> Changed upper case G to lower case g!`를 출력한다. 영문자가 아닌 `5`에서는 오류 메시지가 출력된다.

```text
>> Input char: q
-> Changed lower case q to upper case Q!
>> Input char: G
-> Changed upper case G to lower case g!
>> Input char: 5
-> Input error!
```

> **참고:** 32를 직접 쓰는 방법은 ASCII 코드에 기대므로, `ch - 'a' + 'A'`처럼 문자 상수의 차이로 쓰면 의도가 더 분명하다. 표준 라이브러리 `<ctype.h>`의 `islower()`, `toupper()`를 쓰면 판별과 변환을 함수 하나씩으로 할 수 있다.

---

<br>

## 3. 문제 2: 홀짝 판별

### 3.1 문제

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

### 3.2 풀이

**접근 방법:** 2로 나눈 나머지가 0이면 짝수, 0이 아니면 홀수이다. C에서 0이 아닌 값은 참이므로 `num % 2`를 그대로 `if`의 조건으로 쓴다.

- **조건:** `if (num % 2)`는 `if (num % 2 != 0)`과 같다. 나머지가 0이 아니면(홀수) 첫 번째 블록이, 0이면(짝수) `else` 블록이 실행된다.
- **음수:** C99 이후 나머지의 부호는 피제수를 따르므로 `-3 % 2`는 -1이다. -1도 0이 아니므로 음수 홀수도 올바르게 홀수로 판별된다. `num % 2 == 1`로 비교했다면 음수 홀수를 짝수로 잘못 판별했을 것이다.

**코드:** [Solution/Q2.c](Solution/Q2.c)

```c
/**
 * @file    A10303-2_C05Q2.c
 * @brief   Q2. 홀짝 판별
 * @author  박철원 (Cheolwon Park)
 * @date    2024-04-05
 */

#include <stdio.h>

int main()
{
	int num;

	printf(">> Input value: ");
	scanf(" %d", &num);

	if (num % 2) {
		printf("-> %d is an odd number.\n", num);
	} else {
		printf("-> %d is an even number.\n", num);
	}

	return 0;
}
```

### 3.3 실행 결과와 경계 조건

**실행 결과:** 판별 결과는 두 실행 예시와 같다. 다만 문장 끝이 실행 예시의 `!`가 아니라 `.`이다. 마지막 실행은 음수 홀수 -3을 입력한 경우이다.

```text
>> Input value: 3
-> 3 is an odd number.
>> Input value: 6
-> 6 is an even number.
>> Input value: -3
-> -3 is an odd number.
```

---

<br>

## 4. 문제 3: switch-if 변환 (1)

### 4.1 문제

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

### 4.2 풀이

**접근 방법:** `switch`문은 범위를 직접 비교할 수 없으므로, 점수를 10으로 나눈 몫으로 바꾸어 10점 단위 구간을 정수 하나로 나타낸다([5장 2.7절](../../Lecture-Notes/Ch05_Control-Statements/Concepts_Lecture.ko.md#27-switch)). 90\~100점은 몫이 9 또는 10, 80\~89점은 8이 되는 식이다.

- **범위 밖의 값:** 몫만 쓰면 범위 밖의 값이 잘못 분류된다. C99 이후 정수 나눗셈은 0 방향으로 절삭하므로 -5 / 10은 0이 되어 F로, 105 / 10은 10이 되어 A로 판정된다. 그래서 `switch`의 식을 `(score < 0 || score > 100) ? -1 : (score / 10)`으로 하여, 범위 밖이면 어느 case에도 없는 -1을 만들어 `default`로 보낸다.
- **case 묶기:** `case 10:`과 `case 9:`를 연달아 두어 둘 다 A를 출력하고, `case 5:`부터 `case 0:`까지를 묶어 F를 출력한다. 각 묶음의 끝에는 `break`를 두어 다음 case로 넘어가지 않게 한다.

**코드:** [Solution/Q3.c](Solution/Q3.c)

```c
/**
 * @file    A10303-2_C05Q3.c
 * @brief   Q3. switch-if 변환 (1)
 * @author  박철원 (Cheolwon Park)
 * @date    2024-04-05
 */

#include <stdio.h>

int main()
{
    int score;
    printf(">> Input score(0~100): ");
    scanf(" %d", &score);

    switch ((score < 0 || score > 100) ? -1 : (score / 10)) {
    case 10:
    case 9:
        printf("%d is a/an A!", score);
        break;
    case 8:
        printf("%d is a/an B!", score);
        break;
    case 7:
        printf("%d is a/an C!", score);
        break;
    case 6:
        printf("%d is a/an D!", score);
        break;
    case 5: 
	case 4: 
	case 3: 
	case 2: 
	case 1: 
	case 0:
        printf("%d is a/an F!", score);
        break;
    default:
        printf("Input error!");
    }

    return 0;
}
```

### 4.3 실행 결과와 경계 조건

**실행 결과:** 각 등급 구간의 대표값과 경계값을 입력한 결과는 예시 코드의 `if`문과 같다. 출력 끝에 줄바꿈을 출력하지 않는다.

```text
>> Input score(0~100): 100
100 is a/an A!
>> Input score(0~100): 95
95 is a/an A!
>> Input score(0~100): 85
85 is a/an B!
>> Input score(0~100): 72
72 is a/an C!
>> Input score(0~100): 61
61 is a/an D!
>> Input score(0~100): 59
59 is a/an F!
>> Input score(0~100): 0
0 is a/an F!
>> Input score(0~100): -5
Input error!
>> Input score(0~100): 101
Input error!
```

---

<br>

## 5. 문제 4: switch-if 변환 (2)

### 5.1 문제

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

### 5.2 풀이

**접근 방법:** `switch`의 case 하나는 `grade == 값`이라는 동등 비교이고, 문장을 공유하도록 연달아 둔 case들은 그 비교들의 논리합이다. 따라서 각 묶음을 `||`로 이은 조건으로 바꾸고 `else if` 사다리로 차례로 검사한다.

- **case 1:** `grade == 1`이다.
- **case 2, 3:** `grade == 2 || grade == 3`이다. 4와 5, 6과 7도 같은 방식이다.
- **default:** 어떤 조건에도 맞지 않을 때 실행되는 마지막 `else`에 해당한다.

**코드:** [Solution/Q4.c](Solution/Q4.c)

```c
/**
 * @file    A10303-2_C05Q4.c
 * @brief   Q4. switch-if 변환 (2)
 * @author  박철원 (Cheolwon Park)
 * @date    2024-04-05
 */

#include <stdio.h>

int main()
{
	int grade;

	printf(">> Input grade(1~7): ");
	scanf(" %d", &grade);

	if (grade == 1)
		printf("Very good!");
	else if (grade == 2 || grade == 3)
		printf("Good!");
	else if (grade == 4 || grade == 5)
		printf("So So!");
	else if (grade == 6 || grade == 7)
		printf("Cheer up!");
	else
		printf("Input error!");
}
```

### 5.3 실행 결과와 경계 조건

**실행 결과:** 각 묶음의 값과 범위 밖의 값을 입력한 결과는 예시 코드의 `switch`문과 같다. 출력 끝에 줄바꿈을 출력하지 않는다.

```text
>> Input grade(1~7): 1
Very good!
>> Input grade(1~7): 3
Good!
>> Input grade(1~7): 5
So So!
>> Input grade(1~7): 7
Cheer up!
>> Input grade(1~7): 8
Input error!
```

> **참고:** 2와 3처럼 연속된 값의 묶음은 `grade >= 2 && grade <= 3`처럼 범위로 써도 같다. `switch`는 값이 흩어져 있어도 case를 나열하기만 하면 되지만, `if`문은 연속된 구간일 때 범위 조건으로 짧게 쓸 수 있다.

---

<br>

## 6. 문제 5: switch 분기 연습

### 6.1 문제

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

### 6.2 풀이

**접근 방법:** 입력 문자를 `switch`의 식으로 쓰고, 소문자 case와 대문자 case를 연달아 두어 같은 언어명을 출력한다. 첫 case에는 문장이 없으므로 실행이 바로 다음 case의 문장으로 이어지는데, 이것은 의도한 폴스루이다([5장 2.7절](../../Lecture-Notes/Ch05_Control-Statements/Concepts_Lecture.ko.md#27-switch)).

- **case 묶음:** `'c'`와 `'C'`, `'p'`와 `'P'`, `'j'`와 `'J'`, `'l'`과 `'L'`의 네 묶음이 있고, 각 묶음의 끝에 `break`가 있다.
- **default:** 네 묶음에 해당하지 않는 모든 문자에서 `-> Input Error!`를 출력한다.

**코드:** [Solution/Q5.c](Solution/Q5.c)

```c
/**
 * @file    A10303-2_C05Q5.c
 * @brief   Q5. switch 분기 연습
 * @author  박철원 (Cheolwon Park)
 * @date    2024-04-05
 */

#include <stdio.h>

int main()
{
    char ch;

    printf(">> Input the character: ");
    scanf(" %c", &ch);

    switch (ch) {
    case 'c': 
	case 'C':
        printf("-> C Language\n");
        break;
    case 'p': 
	case 'P':
        printf("-> Python\n");
        break;
    case 'j': 
	case 'J':
        printf("-> JAVA\n");
        break;
    case 'l': 
	case 'L':
        printf("-> LISP\n");
        break;
    default:
        printf("-> Input Error!\n");
    }
}
```

### 6.3 실행 결과와 경계 조건

**실행 결과:** 세 실행 예시와 같으며, 나머지 두 언어의 결과도 함께 보인다.

```text
>> Input the character: p
-> Python
>> Input the character: C
-> C Language
>> Input the character: m
-> Input Error!
>> Input the character: j
-> JAVA
>> Input the character: L
-> LISP
```

> **주의:** 묶음 끝의 `break`를 빠뜨리면 다음 묶음의 문장까지 실행된다. 예를 들어 `Python` 뒤의 `break`가 없으면 `p`를 입력했을 때 `-> Python`과 `-> JAVA`가 함께 출력된다.

---

<br>

## 요약

| 개념 | 핵심 요약 |
|:-----|:-----|
| 문자의 범위 비교 | 문자는 정수 코드이므로 `ch >= 'a' && ch <= 'z'`처럼 관계 연산자로 소문자인지 판별한다. |
| 대소문자 변환 | ASCII에서 소문자와 대문자는 32만큼 차이 나므로 `ch - 32` 또는 `ch - 'a' + 'A'`로 변환한다. |
| 홀짝 판별 | `num % 2`가 0이 아니면 홀수이며, 음수 홀수의 나머지는 -1이므로 `== 1`이 아니라 `!= 0`으로 판별한다. |
| 범위의 `switch` 변환 | 점수를 10으로 나눈 몫을 case로 쓰고, 범위 밖의 값은 조건 연산자로 -1을 만들어 `default`로 보낸다. |
| `switch`의 `if` 변환 | 연달아 둔 case들은 `||`로 이은 동등 비교가 되고, `default`는 마지막 `else`가 된다. |
| 의도한 폴스루 | 소문자와 대문자 case를 연달아 두면 같은 문장을 공유하며, 묶음 끝의 `break`로 다음 묶음과 분리한다. |

---

<br>

## 점검 문제

1. **대소문자 변환:** `char ch = 'g';`일 때 `ch - 32`의 정수값과 그 값이 나타내는 문자를 쓰라.

   <details>
   <summary>정답</summary>

   `'g'`의 ASCII 코드는 103이므로 `ch - 32`는 71이고, 71은 `'G'`이다.

   </details>

2. **음수의 홀짝:** `num`이 -7일 때 `num % 2`의 값은 얼마인가? 홀수 판별 조건을 `num % 2 == 1`로 쓰면 어떤 문제가 생기는가?

   <details>
   <summary>정답</summary>

   C99 이후 나머지의 부호는 피제수를 따르므로 -7 % 2는 -1이다. `num % 2 == 1`은 거짓이 되어 -7을 짝수로 잘못 판별한다. `num % 2 != 0` 또는 `if (num % 2)`로 써야 음수 홀수도 올바르게 판별된다.

   </details>

3. **범위 밖의 점수:** 문제 3의 코드에서 `switch`의 식을 범위 검사 없이 `score / 10`으로만 쓰면 105와 -5는 각각 어떤 결과를 내는가?

   <details>
   <summary>정답</summary>

   105 / 10은 10이므로 `105 is a/an A!`가 출력되고, -5 / 10은 0 방향으로 절삭되어 0이므로 `-5 is a/an F!`가 출력된다. 두 값 모두 `Input error!`가 나와야 하므로, 범위 밖의 값을 -1로 바꾸는 조건 연산자가 필요하다.

   </details>

4. **`switch`에서 `if`로:** 다음 `switch`문을 같은 동작의 `if-else`문으로 바꾸어 쓰라.

   ```c
   switch (n) {
   case 1: case 3: printf("odd"); break;
   case 2: case 4: printf("even"); break;
   default: printf("other");
   }
   ```

   <details>
   <summary>정답</summary>

   `if (n == 1 || n == 3) printf("odd"); else if (n == 2 || n == 4) printf("even"); else printf("other");`이다. 연달아 둔 case는 `||`로 이은 동등 비교가 되고, `default`는 마지막 `else`가 된다.

   </details>
