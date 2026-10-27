# 10장 실습 — 구조체 기초와 문자열의 정수 변환

[레포지토리 안내](../../README.ko.md) | [English](Concepts_Lab.md) | [한국어](Concepts_Lab.ko.md)

> **최종 수정일:** 2026-10-27
>
> 문제풀이 중심의 C언어 연습, 김용일 외, Ch 9

> **학습 목표:**
> 1. 관련된 정보를 개별 변수로 표현할 때의 한계와 구조체로 묶어 표현하는 이유를 설명할 수 있다
> 2. 구조체를 정의하고 구조체 변수를 선언한 뒤, 점 연산자로 멤버에 접근할 수 있다
> 3. 문자 배열 멤버에 문자열을 대입할 수 없는 이유를 설명하고 `strcpy`로 값을 넣을 수 있다
> 4. 초기화 리스트로 구조체 변수를 초기화하고, 초기값이 없는 멤버의 값을 설명할 수 있다
> 5. 숫자 문자의 ASCII 코드를 이용하여 정수로 된 문자열을 정수로 변환하는 함수를 구현할 수 있다

---

## 목차

- [1. 구조체 기초](#1-구조체-기초)
  - [1.1 개별 변수로 표현한 정보](#11-개별-변수로-표현한-정보)
  - [1.2 구조체 정의와 변수 선언](#12-구조체-정의와-변수-선언)
  - [1.3 멤버 접근과 문자 배열 멤버](#13-멤버-접근과-문자-배열-멤버)
  - [1.4 구조체 초기화](#14-구조체-초기화)
- [2. 문자열을 정수로 변환](#2-문자열을-정수로-변환)
  - [2.1 문제](#21-문제)
  - [2.2 숫자 문자와 ASCII 코드](#22-숫자-문자와-ascii-코드)
  - [2.3 자릿값을 곱해 더하는 방법](#23-자릿값을-곱해-더하는-방법)
  - [2.4 앞에서부터 10을 곱해 가는 방법](#24-앞에서부터-10을-곱해-가는-방법)
- [요약](#요약)
- [점검 문제](#점검-문제)

---

<br>

## 1. 구조체 기초

이 절의 코드는 모두 `gcc -std=c99 -Wall`로 경고 없이 컴파일되고, 출력은 실제로 실행한 결과이다.

### 1.1 개별 변수로 표현한 정보

학생의 성적을 관리하는 작은 프로그램을 생각해 보자. 필요한 정보는 이름(`char name[]`), 국어 점수(`int kor`), 영어 점수(`int eng`), 평균(`double ave`)이다. 지금까지 배운 방법으로는 각 정보를 개별 변수로 선언한다.

```c
#include <stdio.h>

int main()
{
    char name[] = "hong gil dong";
    int kor, eng;
    double ave;

    kor = 80;
    eng = 91;
    ave = (kor + eng) / 2.0;

    printf("name: %s \n", name);
    printf("%d, %d \n", kor, eng);
    printf("%.1f \n", ave);
}
```

```text
name: hong gil dong 
80, 91 
85.5 
```

출력은 한 학생의 정보처럼 보이지만, `name`, `kor`, `eng`, `ave`는 서로 아무 관계가 없는 네 개의 개별 변수이다. 같은 학생의 정보를 출력할 때 함께 출력했을 뿐, 코드 어디에도 네 정보가 한 학생에게 속한다는 표시는 없다. 학생이 여러 명이 되면 `name1`, `kor1`, `name2`, `kor2`처럼 변수가 늘어나고, 어느 점수가 어느 학생의 것인지는 변수 이름에 붙인 번호로만 구분해야 한다.

관련된 정보를 하나의 단위로 묶어 표현하면 이 문제가 해결된다. 이렇게 데이터를 하나의 구조로 만들어 표현하는 방법이 **구조체**(structure)이다([10장 1.1절](Concepts_Lecture.ko.md#11-구조체-개념)).

### 1.2 구조체 정의와 변수 선언

구조체는 프로그래머가 특정한 목적과 관련된 변수들을 하나로 묶어 새로운 자료형을 설계하는 방법이다. 키워드 `struct` 다음에 구조체의 이름(태그)을 쓰고, 중괄호 안에 묶을 변수들을 선언한다. 중괄호 안의 변수를 **멤버**(member)라고 하며, 정의의 끝에는 세미콜론을 쓴다([10장 1.2절](Concepts_Lecture.ko.md#12-구조체-정의)).

```c
struct grade {
    char name[20];
    int kor, math;
    double ave;
};
```

이 정의는 이름, 국어 점수, 수학 점수, 평균을 묶은 `struct grade`라는 자료형을 만든다. 정의는 자료형의 모양을 알려 줄 뿐이고, 정의만으로는 메모리가 할당되지 않는다. `int`로 변수를 선언하듯이 `struct grade hong;`으로 구조체 변수를 선언해야 메모리가 할당되며, 이때 `name`, `kor`, `math`, `ave` 네 멤버가 함께 만들어진다. 이 멤버들은 `hong`에 속한 변수이다([10장 1.3절](Concepts_Lecture.ko.md#13-구조체-변수-선언)).

```text
 hong
 오프셋 0                   20       24       28       32                40
 ┌─────────────────────────┬────────┬────────┬────────┬─────────────────┐
 │ name[20]                │ kor    │ math   │ (패딩) │ ave             │
 └─────────────────────────┴────────┴────────┴────────┴─────────────────┘
```

*그림 1. 구조체 변수 hong의 메모리 배치 (arm64 macOS, clang)*

멤버는 선언한 순서대로 배치된다. 멤버 크기의 합은 20 + 4 + 4 + 8 = 36바이트이지만, `sizeof(hong)`은 40이다. `double`형 멤버 `ave`는 8의 배수 주소에서 시작하도록 정렬되므로, 컴파일러가 `math` 뒤에 4바이트의 패딩을 넣었기 때문이다. 패딩의 크기는 컴파일러와 시스템에 따라 다를 수 있다.

### 1.3 멤버 접근과 문자 배열 멤버

구조체 변수의 멤버에는 **점 연산자**(`.`)로 접근한다. `hong.kor`는 `hong`의 멤버 `kor`이며, 일반 `int` 변수처럼 값을 대입하고 읽을 수 있다([10장 1.5절](Concepts_Lecture.ko.md#15-멤버-접근)).

```c
#include <stdio.h>
#include <string.h>

struct grade {
    char name[20];
    int kor, math;
    double ave;
};

int main()
{
    struct grade hong;      // members name, kor, math, ave are created together

    // hong.name = "hong gil dong";     // compile error: an array cannot be assigned
    strcpy(hong.name, "hong gil dong");
    hong.kor = 90;
    hong.math = 79;
    hong.ave = (hong.kor + hong.math) / 2.0;

    printf("-> name: %s \n", hong.name);
    printf("-> %d, %d \n", hong.kor, hong.math);
    printf("-> %.1f \n", hong.ave);
    printf("-> size: %zu \n", sizeof(hong));
}
```

```text
-> name: hong gil dong 
-> 90, 79 
-> 84.5 
-> size: 40 
```

- **문자 배열 멤버:** `hong.name = "hong gil dong";`은 컴파일 오류이다. `hong.name`은 배열이고, 배열 이름에는 대입 연산자로 값을 넣을 수 없기 때문이다. clang은 `array type 'char[20]' is not assignable`이라는 오류를 낸다. 문자 배열 멤버에 문자열을 넣을 때는 `strcpy(hong.name, "hong gil dong");`처럼 `strcpy`로 복사한다([9장 실습 1.3절](../Ch09_Strings/Concepts_Lab.ko.md#13-문자-배열의-수정)).
- **정수와 실수 멤버:** `hong.kor = 90;`처럼 대입 연산자로 값을 넣고, `(hong.kor + hong.math) / 2.0`처럼 일반 변수와 같이 연산에 사용한다.

> **참고:** Visual Studio에서는 `strcpy`에 경고 C4996이 발생하므로, 파일 맨 앞에 `#pragma warning(disable:4996)`을 쓰거나 `#define _CRT_SECURE_NO_WARNINGS`를 쓴다. Visual Studio 2019 이후 버전에서는 `scanf`의 반환값을 사용하지 않을 때 나오는 경고 C6031도 `#pragma warning(disable:6031)`로 끌 수 있다([3장 실습 5.1절](../Ch03_Data-Types-and-Variables/Concepts_Lab.ko.md#51-c4996-경고)).

### 1.4 구조체 초기화

구조체 변수도 선언할 때 **초기화 리스트** `{ }`로 초기화할 수 있다. 초기값은 멤버를 선언한 순서대로 대응되며, 문자 배열 멤버는 초기화 리스트 안에서 문자열 리터럴로 초기화할 수 있다([10장 1.4절](Concepts_Lecture.ko.md#14-구조체-초기화)).

```c
#include <stdio.h>

struct grade {
    char name[20];
    int kor, math;
    double ave;
};

int main()
{
    struct grade hong = { "hong gil dong", 87, 88 };    // ave is not given

    printf("-> name: %s \n", hong.name);
    printf("-> %d, %d \n", hong.kor, hong.math);
    printf("-> %.1f \n", hong.ave);

    hong.ave = (hong.kor + hong.math) / 2.0;
    printf("============\n");
    printf("-> name: %s \n", hong.name);
    printf("-> %d, %d \n", hong.kor, hong.math);
    printf("-> %.1f \n", hong.ave);
}
```

```text
-> name: hong gil dong 
-> 87, 88 
-> 0.0 
============
-> name: hong gil dong 
-> 87, 88 
-> 87.5 
```

`{ "hong gil dong", 87, 88 }`의 세 초기값은 순서대로 `name`, `kor`, `math`에 들어간다. 초기값이 멤버의 개수보다 적으면 나머지 멤버는 0으로 초기화되므로, 초기값이 없는 `ave`는 0.0이다. 첫 번째 출력에서 평균이 0.0인 것은 이 때문이며, 평균을 계산하여 `hong.ave`에 대입한 뒤에는 87.5가 출력된다.

> **핵심:** 초기화 리스트로 문자 배열 멤버에 문자열을 넣는 것은 선언할 때만 가능하다. 선언 이후에는 1.3절처럼 `strcpy`를 사용해야 한다.

구조체 배열을 함수로 입력, 출력, 정렬하는 문제는 [10장 연습 문제 1번](Exercises.ko.md#연습-문제-1-student-구조체)에서 다룬다.

---

<br>

## 2. 문자열을 정수로 변환

### 2.1 문제

**문제:** 정수로 된 문자열을 입력받아, 그 문자열을 정수로 변환한 값을 돌려주는 함수 `strToInt()`를 구현하라. `main` 함수는 돌려받은 정수에 2를 곱하여 `%6d`로 출력한다(교재 문제 9-14).

문자열 `"124"`는 문자 `'1'`, `'2'`, `'4'`와 널 문자가 이어진 문자 배열일 뿐이고, 산술 연산을 할 수 있는 정수 124가 아니다. 따라서 문자 하나하나를 정수로 바꾼 뒤, 각 숫자가 있는 자리에 맞게 정수 값을 다시 만들어야 한다.

### 2.2 숫자 문자와 ASCII 코드

숫자 문자 `'0'`\~`'9'`의 ASCII 코드는 48\~57로 연속해 있다.

| 문자 | `'0'` | `'1'` | `'2'` | `'3'` | `'4'` | `'5'` | `'6'` | `'7'` | `'8'` | `'9'` |
|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
| 10진수 코드 | 48 | 49 | 50 | 51 | 52 | 53 | 54 | 55 | 56 | 57 |
| 16진수 코드 | 0x30 | 0x31 | 0x32 | 0x33 | 0x34 | 0x35 | 0x36 | 0x37 | 0x38 | 0x39 |

*표 1. 숫자 문자의 ASCII 코드*

코드가 연속해 있으므로 숫자 문자의 코드에서 `'0'`의 코드 48을 빼면 그 문자가 나타내는 정수가 된다. 예를 들어 `'1' - '0'`은 49 - 48 = 1이고, `'4' - '0'`은 52 - 48 = 4이다. 48 대신 `'0'`이라고 쓰면 ASCII 코드 값을 외우지 않아도 되고, 코드의 의도도 분명해진다. 문자는 연산할 때 정수로 승격되므로 `pstr[i] - '0'`의 결과는 `int`형이다.

### 2.3 자릿값을 곱해 더하는 방법

`"124"`에서 `'1'`은 백의 자리, `'2'`는 십의 자리, `'4'`는 일의 자리 숫자이다. 각 숫자를 정수로 바꾼 뒤 자릿값을 곱해 더하면 정수 124가 된다.

1. 문자열의 길이(자릿수) len을 구한다. `"124"`이면 3이다.
2. 첫 숫자의 자릿값 place를 10의 (len - 1)제곱으로 구한다. len이 3이면 100이다.
3. 앞에서부터 숫자 하나마다 (숫자 문자 - `'0'`) × place를 결과에 더하고, place를 10으로 나눈다.

| i | `pstr[i]` | `pstr[i] - '0'` | place | 더하는 값 | result |
|:---:|:---:|:---:|:---:|:---:|:---:|
| 0 | `'1'` | 1 | 100 | 100 | 100 |
| 1 | `'2'` | 2 | 10 | 20 | 120 |
| 2 | `'4'` | 4 | 1 | 4 | 124 |

*표 2. "124"를 자릿값으로 변환하는 과정*

```c
#include <stdio.h>
#include <string.h>

int strToInt(const char *pstr);

int main()
{
    char str[20];

    printf(">> input str: ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0';     // remove the newline that fgets keeps

    printf("-> output int: %6d \n", strToInt(str) * 2);
}

int strToInt(const char *pstr)
{
    int len = 0, place = 1, result = 0;

    while (pstr[len] != '\0')           // number of digits
        len++;
    for (int i = 1; i < len; i++)       // place value of the first digit
        place *= 10;

    for (int i = 0; i < len; i++) {
        result += (pstr[i] - '0') * place;      // '1' - '0' is the integer 1
        place /= 10;
    }
    return result;
}
```

```text
>> input str: 124
-> output int:    248 
```

```text
>> input str: 1352
-> output int:   2704 
```

- **문자열 입력:** `fgets`는 읽은 줄 바꿈 문자를 배열에 남기므로 `strcspn`으로 찾아 널 문자로 바꾼다. 줄 바꿈 문자가 남아 있으면 길이에 포함되어 자릿수가 하나 늘어난다([9장 실습 1.6절](../Ch09_Strings/Concepts_Lab.ko.md#16-문자열-입력-함수)).
- **매개변수:** `strToInt`는 문자열을 읽기만 하므로 매개변수를 `const char *`로 선언하였다.
- **출력:** 돌려받은 정수에 2를 곱할 수 있다는 것이 문자열이 정수로 바뀌었다는 뜻이다. `%6d`는 6칸의 오른쪽에 맞추어 출력하므로 248 앞에 공백 세 칸, 2704 앞에 공백 두 칸이 붙는다.

### 2.4 앞에서부터 10을 곱해 가는 방법

자릿수를 미리 구하지 않고도 변환할 수 있다. 앞에서부터 숫자를 하나 읽을 때마다 지금까지의 결과에 10을 곱하여 한 자리씩 왼쪽으로 옮긴 뒤 새 숫자를 더한다.

```c
int strToInt(const char *pstr)
{
    int result = 0;

    for (int i = 0; pstr[i] != '\0'; i++)
        result = result * 10 + (pstr[i] - '0');
    return result;
}
```

`"124"`이면 result가 0 → 0 × 10 + 1 = 1 → 1 × 10 + 2 = 12 → 12 × 10 + 4 = 124로 바뀐다. 이 함수를 2.3절의 `strToInt` 대신 쓰면 같은 결과가 나온다. 길이를 세는 반복문과 자릿값을 구하는 반복문이 필요 없어 문자열을 한 번만 훑는다.

> **주의:** 두 함수 모두 입력이 숫자로만 이루어져 있다고 가정한다. `-12`처럼 부호가 있거나 `12a`처럼 숫자가 아닌 문자가 섞이면 잘못된 값을 돌려주고, `int`의 범위를 넘는 큰 수는 오버플로가 일어난다. 표준 라이브러리 함수 `atoi`는 앞의 공백과 부호를 처리하고 숫자가 아닌 문자에서 변환을 멈춘다([9장 5.1절](../Ch09_Strings/Concepts_Lecture.ko.md#51-문자열을-숫자로-변환)).

---

<br>

## 요약

| 개념 | 핵심 정리 |
|:-----|:-----|
| 구조체 | 특정한 목적과 관련된 변수들을 하나로 묶어 프로그래머가 설계한 자료형이다. |
| 구조체 정의 | `struct 태그 { 멤버 선언 };`의 형태이며, 정의만으로는 메모리가 할당되지 않는다. |
| 구조체 변수 | `struct grade hong;`처럼 선언하면 모든 멤버가 함께 할당된다. |
| 구조체의 크기 | 정렬을 위한 패딩 때문에 멤버 크기의 합보다 클 수 있다. |
| 점 연산자 | `hong.kor`처럼 구조체 변수를 통해 멤버에 접근한다. |
| 문자 배열 멤버 | 대입 연산자로 문자열을 넣을 수 없으므로 `strcpy`로 복사한다. |
| 구조체 초기화 | 초기값은 멤버 선언 순서대로 대응되고, 초기값이 없는 멤버는 0이 된다. |
| 숫자 문자의 변환 | 숫자 문자에서 `'0'`을 빼면 그 문자가 나타내는 정수가 된다. |
| 문자열의 정수 변환 | 숫자마다 자릿값을 곱해 더하거나, 결과에 10을 곱하고 새 숫자를 더해 간다. |

---

<br>

## 점검 문제

1. **구조체 정의:** `struct point { int x, y; };`를 정의하기만 하고 변수를 선언하지 않으면 메모리가 할당되는가?

   <details>
   <summary>정답</summary>

   할당되지 않는다. 구조체 정의는 자료형의 모양을 알려 줄 뿐이며, `struct point p;`처럼 변수를 선언해야 멤버 `x`와 `y`의 메모리가 할당된다.

   </details>

2. **문자 배열 멤버:** `struct grade s;`를 선언한 뒤 `s.name = "kim";`이라고 쓰면 어떻게 되는가? 어떻게 고쳐야 하는가?

   <details>
   <summary>정답</summary>

   `s.name`은 배열이므로 대입할 수 없어 컴파일 오류가 난다. `strcpy(s.name, "kim");`으로 복사해야 한다.

   </details>

3. **부분 초기화:** `struct grade s = { "lee", 70 };`이면 `s.math`와 `s.ave`의 값은 무엇인가?

   <details>
   <summary>정답</summary>

   초기값이 없는 멤버는 0으로 초기화되므로 `s.math`는 0, `s.ave`는 0.0이다.

   </details>

4. **구조체의 크기:** 1.2절의 `struct grade`에서 멤버 크기의 합은 36바이트인데 `sizeof(struct grade)`가 40인 이유는 무엇인가?

   <details>
   <summary>정답</summary>

   `double`형 멤버 `ave`가 8의 배수 위치에서 시작하도록 컴파일러가 `math` 뒤에 4바이트의 패딩을 넣었기 때문이다.

   </details>

5. **문자열의 정수 변환:** 2.4절의 함수로 `"305"`를 변환할 때 result는 어떻게 바뀌는가?

   <details>
   <summary>정답</summary>

   0 → 3 → 30 → 305로 바뀐다. `'0' - '0'`은 0이므로 가운데 숫자 0도 올바르게 처리된다.

   </details>
