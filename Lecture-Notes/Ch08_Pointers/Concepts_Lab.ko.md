# 8장 실습 — 포인터의 기초와 포인터 연산

[레포지토리 안내](../../README.ko.md) | [English](Concepts_Lab.md) | [한국어](Concepts_Lab.ko.md)

> **최종 수정일:** 2026-10-27
>
> 문제풀이 중심의 C언어 연습, 김용일과 강문설, Ch 9

> **학습 목표:**
> 1. 변수를 복사한 다른 변수로는 원래 변수를 바꿀 수 없는 이유를 메모리 주소로 설명할 수 있다
> 2. 변수의 주소를 `%p`로 출력하고, 출력되는 주소가 빌드 설정과 실행마다 달라지는 이유를 설명할 수 있다
> 3. 포인터를 선언, 초기화하고 역참조 연산자로 가리키는 변수의 값을 읽고 바꿀 수 있다
> 4. 포인터에 정수를 더할 때 주소가 가리키는 타입의 크기만큼 바뀌는 것을 설명하고, 포인터로 배열의 원소에 접근할 수 있다
> 5. 값에 의한 호출로 작성한 swap 함수가 실패하는 이유를 설명할 수 있다

---

## 목차

- [1. 변수의 복사와 메모리 주소](#1-변수의-복사와-메모리-주소)
  - [1.1 변수 b로 a의 값을 바꿀 수 있는가](#11-변수-b로-a의-값을-바꿀-수-있는가)
  - [1.2 메모리 주소의 출력](#12-메모리-주소의-출력)
- [2. 포인터](#2-포인터)
  - [2.1 주소를 저장하는 변수](#21-주소를-저장하는-변수)
  - [2.2 역참조로 값 바꾸기](#22-역참조로-값-바꾸기)
  - [2.3 포인터의 타입과 크기](#23-포인터의-타입과-크기)
- [3. 포인터 연산과 배열](#3-포인터-연산과-배열)
  - [3.1 포인터에 정수 더하기](#31-포인터에-정수-더하기)
  - [3.2 포인터와 배열](#32-포인터와-배열)
- [4. 포인터 실습](#4-포인터-실습)
  - [4.1 포인터 수식의 결과 예측](#41-포인터-수식의-결과-예측)
  - [4.2 main에서 두 변수의 값 교환](#42-main에서-두-변수의-값-교환)
  - [4.3 함수로 두 변수의 값 교환](#43-함수로-두-변수의-값-교환)
- [요약](#요약)
- [점검 문제](#점검-문제)

---

<br>

## 1. 변수의 복사와 메모리 주소

### 1.1 변수 b로 a의 값을 바꿀 수 있는가

`int a = 3;`이 선언되어 있을 때, 다른 변수 `b`를 이용하여 `a`의 값을 5로 바꿀 수 있는지 생각한다. `int b = a;`로 `b`를 만든 뒤 `b = 5;`를 실행하는 다음 코드는 `a`를 바꾸지 못한다. 코드는 [Example_VariableCopy.c](Example_VariableCopy.c)이다.

```c
#include <stdio.h>

int main()
{
    int a = 3;
    int b = a;

    printf("[1] %d, %d \n", a, b); // expected: 3, 3
    printf("[1-1] %p, %p \n", &a, &b);

    // Can the value of a be changed through variable b?
    b = 5;

    printf("[2] %d, %d \n", a, b); // expected: 3, 5
}
```

```text
[1] 3, 3 
[1-1] 0x16ce8abbc, 0x16ce8abb8 
[2] 3, 5 
```

`int b = a;`는 `a`에 저장된 값 3을 `b`의 메모리에 복사할 뿐이며, `a`와 `b`는 서로 다른 주소에 있는 다른 변수이다. `[1-1]` 줄의 두 주소가 다르다는 것이 이를 보여 준다. 그래서 `b = 5;`는 `b`의 메모리만 바꾸고 `a`는 3 그대로이다.

```text
 b = 5; 실행 후
   a                   b
┌───────┐           ┌───────┐
│   3   │           │   5   │
└───────┘           └───────┘
 0x16ce8abbc         0x16ce8abb8
```

*그림 1. 서로 다른 주소에 있는 변수 a와 b*

### 1.2 메모리 주소의 출력

변수의 주소는 주소 연산자 `&`로 구하고, 주소를 출력하는 전용 형식 지정자 `%p`로 출력한다. 위 출력처럼 macOS의 64비트 프로그램에서 `%p`는 `0x`로 시작하는 16진수를 출력한다. 출력 형식은 구현이 정하며, Visual Studio는 `00D5FAEC`처럼 `0x` 없이 대문자 16진수를 자릿수에 맞추어 출력한다.

주소를 16진수 정수의 형식 지정자 `%x`나 `%#x`로 출력할 수도 있지만, `%x`는 `unsigned int`를 기대하므로 주소를 넘기면 형식과 인자의 타입이 맞지 않는다. 64비트 빌드에서는 8바이트 주소 중 하위 4바이트만 출력될 수 있으며, `-Wall`로 컴파일하면 "format specifies type 'unsigned int' but the argument has type 'int \*'" 경고가 난다. 다음은 같은 컴퓨터에서 `%#x`로 출력한 결과로, 주소의 하위 4바이트(16진수 8자리)만 출력되었다. 한 실행에서 두 형식 지정자로 같은 주소를 함께 출력하면 `%p`의 `0x16fd56be8`이 `%#x`에서는 `0x6fd56be8`이 된다.

```text
[1] 3, 3 
[1-1] 0x6f55ebf8, 0x6f55ebf4 
[2] 3, 5 
```

> **참고:** **출력되는 주소의 길이와 값.** 주소의 크기는 빌드의 대상 플랫폼에 따라 정해진다. 32비트(x86) 빌드에서는 주소가 4바이트이므로 `00D5FAEC`처럼 16진수 8자리로, 64비트(x64, ARM64) 빌드에서는 8바이트이므로 더 긴 값으로 출력된다. 교재는 32비트 기준으로 주소를 설명하므로 Visual Studio의 플랫폼을 x86으로 바꾸면 교재와 같은 길이의 주소를 볼 수 있다. 또 오늘날의 운영체제는 보안을 위해 실행할 때마다 스택의 위치를 무작위로 바꾸므로(ASLR, Address Space Layout Randomization), 같은 프로그램도 실행할 때마다 다른 주소가 출력된다. 이 노트의 주소는 한 번 실행한 예이며, 주소 사이의 차이(4바이트, 8바이트 등)만 의미가 있다.

> **[운영체제]** 프로그램이 출력하는 주소는 운영체제가 프로세스마다 따로 제공하는 가상 주소 공간의 주소이며, 운영체제가 이 가상 주소를 실제 메모리의 물리 주소에 대응시킨다. 실행할 때마다 주소가 바뀌는 ASLR도 운영체제의 메모리 관리와 보호 기법의 하나이며, 가상 메모리는 운영체제에서 다룬다.

---

<br>

## 2. 포인터

### 2.1 주소를 저장하는 변수

**포인터(pointer)** 또는 포인터 변수는 다른 변수의 메모리 주소를 저장하는 특별한 변수이다([8장 1.1절](Concepts_Lecture.ko.md#11-포인터-개념)). `int *p = &a;`는 `int`를 가리키는 포인터 `p`를 선언하고 `a`의 주소로 초기화한다. 이때 `p`가 `a`를 **가리킨다(points to)** 고 말한다([8장 1.2절](Concepts_Lecture.ko.md#12-포인터-선언)).

포인터 `p` 앞에 **역참조 연산자(dereference operator)** `*`를 붙인 `*p`는 `p`에 저장된 주소에 있는 메모리, 즉 `p`가 가리키는 변수를 뜻한다. `*p`를 읽으면 그 변수의 값을 얻고, `*p`에 대입하면 그 변수의 값이 바뀐다([8장 1.4절](Concepts_Lecture.ko.md#14-역참조-연산자-)). 코드는 [Example_Dereference.c](Example_Dereference.c)이다.

```c
#include <stdio.h>

int main()
{
    int a = 3;
    int* p = &a;

    printf("[1] a: %d \n", a);
    printf("[2] &a: %p \n", &a);

    printf("[3] p: %p \n", p);
    printf("[4] &p: %p \n", &p);

    // use the data at the place pointer p refers to: dereference
    printf("[5] *p: %d \n", *p);

    // *p is interpreted as the memory area that pointer p refers to,
    // that is, 5 is assigned to the memory area p refers to!
    *p = 5;
    printf("[6] a: %d \n", a);
    printf("[7] *p: %d \n", *p);
}
```

```text
[1] a: 3 
[2] &a: 0x16d732bbc 
[3] p: 0x16d732bbc 
[4] &p: 0x16d732bb0 
[5] *p: 3 
[6] a: 5 
[7] *p: 5 
```

- **`[2]`와 `[3]`:** `p`에 저장된 값은 `a`의 주소 `&a`와 같다.
- **`[4]`:** 포인터도 변수이므로 자신의 주소 `&p`가 있으며, 그 주소는 `a`의 주소와 다르다.
- **`[5]`:** `*p`는 `p`가 가리키는 곳의 데이터, 즉 `a`의 값 3이다.
- **`[6]`과 `[7]`:** `*p = 5;`는 `p`가 가리키는 메모리 영역에 5를 대입하므로 `a`가 5로 바뀐다. 1.1절에서 `b`로는 바꾸지 못한 `a`의 값을 포인터로는 바꿀 수 있다.

```text
   p (0x16d732bb0)             a (0x16d732bbc)
┌──────────────┐            ┌───────┐
│ 0x16d732bbc  │ ─────────▶ │ 3 → 5 │
└──────────────┘            └───────┘
                              *p
```

*그림 2. a를 가리키는 포인터 p와 그 역참조*

### 2.2 역참조로 값 바꾸기

`*p = 2 + *p;`처럼 대입 연산자의 양쪽에 `*p`가 있는 문장은 다음과 같이 해석한다. 코드는 [Example_DereferenceUpdate.c](Example_DereferenceUpdate.c)이다.

- **대입 연산자의 왼쪽:** `*p`는 `p`가 가리키는 **메모리 영역**으로 해석된다.
- **대입 연산자의 오른쪽:** `2 + *p`는 정수 2와 `p`가 가리키는 메모리의 **데이터**, 즉 `a`의 값 3의 합 5이다.
- 따라서 이 문장은 `*p = 5;`와 같고, 5가 `p`가 가리키는 메모리 영역(`a`)에 대입된다.

```c
#include <stdio.h>

int main()
{
    int a = 3;
    int* p = &a;

    printf("1. a: %d, &a: %p \n", a, &a);
    printf("2. p: %p, &p: %p \n", p, &p);
    printf("3. *p: %d \n", *p);

    *p = 2 + *p;
    printf("4. a: %d, &a: %p \n", a, &a);
    printf("5. p: %p, &p: %p \n", p, &p);
    printf("6. *p: %d \n", *p);
}
```

```text
1. a: 3, &a: 0x16b15abac 
2. p: 0x16b15abac, &p: 0x16b15aba0 
3. *p: 3 
4. a: 5, &a: 0x16b15abac 
5. p: 0x16b15abac, &p: 0x16b15aba0 
6. *p: 5 
```

`a`의 값은 3에서 5로 바뀌지만, `a`의 주소, `p`에 저장된 주소, `p` 자신의 주소는 모두 그대로이다. 역참조는 가리키는 변수의 값만 바꾼다.

### 2.3 포인터의 타입과 크기

포인터는 가리키는 변수의 타입에 맞추어 선언한다. `char *pc = &ch;`, `int *pi = &di;`, `double *pd = &db;`처럼 선언하며, 포인터의 타입은 역참조할 때 메모리를 몇 바이트, 어떤 형식으로 읽을지 정한다. 반면 포인터 변수 자체의 크기는 가리키는 타입과 관계없이 모두 같다. 포인터는 주소를 저장하는 변수이기 때문이다. 32비트 환경에서는 4바이트, 64비트 환경에서는 8바이트이다([8장 1.2절](Concepts_Lecture.ko.md#12-포인터-선언)).

```c
#include <stdio.h>

int main(void)
{
    char ch = 'a';
    int di = 3;
    double db = 3.2;

    char *pc = &ch;
    int *pi = &di;
    double *pd = &db;

    printf("pointer sizes: %zu, %zu, %zu\n", sizeof(pc), sizeof(pi), sizeof(pd));
    printf("pointee sizes: %zu, %zu, %zu\n", sizeof(*pc), sizeof(*pi), sizeof(*pd));

    return 0;
}
```

```text
pointer sizes: 8, 8, 8
pointee sizes: 1, 4, 8
```

64비트 macOS에서 실행한 결과이므로 세 포인터가 모두 8바이트이다. 가리키는 대상의 크기는 `char` 1, `int` 4, `double` 8바이트로 다르다.

---

<br>

## 3. 포인터 연산과 배열

### 3.1 포인터에 정수 더하기

포인터에 1을 더하면 주소가 1바이트가 아니라 가리키는 타입의 크기만큼 증가한다. 즉 `p + n`의 주소는 `p`의 주소 + n × `sizeof(*p)`이다([8장 2.1절](Concepts_Lecture.ko.md#21-포인터-연산)). 코드는 [Example_PointerArithmetic.c](Example_PointerArithmetic.c)이다.

```c
#include <stdio.h>

int main()
{
    char ch = 'a';
    int di = 3;
    double db = 3.2;

    char* pc = &ch;
    int* pi = &di;
    double* pd = &db;

    printf("1. %p, %p, %p \n", pc, pi, pd);
    printf("2. %p, %p, %p \n", pc + 1, pi + 1, pd + 1);
}
```

```text
1. 0x16db32baf, 0x16db32ba8, 0x16db32ba0 
2. 0x16db32bb0, 0x16db32bac, 0x16db32ba8 
```

| 포인터 | `p` | `p + 1` | 증가량 |
|:-----|:-----|:-----|-----:|
| `char *pc` | `...baf` | `...bb0` | 1 |
| `int *pi` | `...ba8` | `...bac` | 4 |
| `double *pd` | `...ba0` | `...ba8` | 8 |

*표 1. 포인터에 1을 더했을 때의 주소 증가량*

> **주의:** `pc + 1`, `pi + 1`, `pd + 1`은 배열의 원소를 가리키지 않는 포인터에 1을 더한 것이다. C 표준은 배열이 아닌 변수를 원소가 하나인 배열로 보아 그 바로 다음 위치까지의 주소 계산을 허용하지만, 그 주소를 역참조하는 것은 정의되지 않은 동작이다. 포인터 연산은 3.2절처럼 배열 안에서 쓴다.

### 3.2 포인터와 배열

배열 이름은 식에서 첫 원소의 주소로 변환되므로, `int *p = arr;`는 `int *p = &arr[0];`과 같다. 그러면 `p + i`는 `arr[i]`의 주소이고 `*(p + i)`는 `arr[i]`의 값이며, 포인터에 첨자를 쓴 `p[i]`도 `*(p + i)`와 같다([8장 2.2절](Concepts_Lecture.ko.md#22-포인터를-배열처럼-사용), [2.3절](Concepts_Lecture.ko.md#23-배열을-포인터처럼-사용)). 코드는 [Example_ArrayPointer.c](Example_ArrayPointer.c)이다.

```c
#include <stdio.h>
#define MAX 5

int main()
{
    int i, arr[MAX] = { 1,3,5,7,9 };
    int* p = arr;

    printf("arr: %p \n", arr);

    for (i = 0; i < MAX; i++)
    {
        printf("[%d, %d, %d], ", arr[i], *(p + i), p[i]);
        printf("[%p, %p] \n", &arr[i], (p + i));
    }
    printf("====================\n");

    for (i = 0; i < MAX; i++)
    {
        printf("[%d, %d], ", *(arr + i), *p);
        p++;
        printf("[%p, %p] \n", &arr[i], p);
    }
}
```

```text
arr: 0x16bc1ab90 
[1, 1, 1], [0x16bc1ab90, 0x16bc1ab90] 
[3, 3, 3], [0x16bc1ab94, 0x16bc1ab94] 
[5, 5, 5], [0x16bc1ab98, 0x16bc1ab98] 
[7, 7, 7], [0x16bc1ab9c, 0x16bc1ab9c] 
[9, 9, 9], [0x16bc1aba0, 0x16bc1aba0] 
====================
[1, 1], [0x16bc1ab90, 0x16bc1ab94] 
[3, 3], [0x16bc1ab94, 0x16bc1ab98] 
[5, 5], [0x16bc1ab98, 0x16bc1ab9c] 
[7, 7], [0x16bc1ab9c, 0x16bc1aba0] 
[9, 9], [0x16bc1aba0, 0x16bc1aba4] 
```

- **첫 번째 반복:** `arr[i]`, `*(p + i)`, `p[i]`가 같은 값을, `&arr[i]`와 `p + i`가 같은 주소를 낸다. `p`는 바뀌지 않으며, 원소의 주소는 4바이트씩 증가한다.
- **두 번째 반복:** `*(arr + i)`는 배열 이름에 정수를 더한 주소를 역참조하여 `arr[i]`와 같은 값을 낸다. `p++`는 `p`에 저장된 주소 자체를 다음 원소로 옮기므로, `*p`를 읽은 직후의 `p`는 `&arr[i]`보다 한 원소(4바이트) 뒤를 가리킨다. 마지막 줄의 `p`는 배열의 끝 바로 다음 위치이며, 이 주소는 비교에 쓸 수는 있지만 역참조하면 안 된다.

```text
            arr[0]   arr[1]   arr[2]   arr[3]   arr[4]
          ┌────────┬────────┬────────┬────────┬────────┐
 arr      │   1    │   3    │   5    │   7    │   9    │
          └────────┴────────┴────────┴────────┴────────┘
           ...b90   ...b94   ...b98   ...b9c   ...ba0
             ▲
 p ──────────┘   p + 1 → ...b94,  p + 2 → ...b98, ...
```

*그림 3. 배열 arr의 첫 원소를 가리키는 포인터 p*

> **참고:** 배열 이름 `arr`과 포인터 `p`는 같은 방식으로 원소에 접근하지만, `arr`은 변수가 아니므로 `arr++`처럼 값을 바꿀 수 없다. 반면 `p`는 변수이므로 `p++`로 다른 원소를 가리키게 할 수 있다([8장 2.4절](Concepts_Lecture.ko.md#24-배열과-포인터-비교)).

---

<br>

## 4. 포인터 실습

다음 문제의 풀이 코드는 이 단원 폴더의 예제 파일이다. 각 파일은 `gcc -std=c99 -Wall`로 경고 없이 컴파일되며, 출력은 실제로 실행한 결과이다.

### 4.1 포인터 수식의 결과 예측

**문제:** 크기 6의 정수 배열 `arr`의 초기값이 `{ 1, -3, 5, -6, 12, 4 }`이고 `int *p = arr;`일 때, 다음 다섯 줄의 출력을 예측하라.

**풀이:** 역참조 연산자 `*`는 단항 연산자이므로 이항 연산자 `+`보다 먼저 결합한다. 이 우선순위가 `*p + 1`과 `*(p + 1)`의 차이를 만든다([4장 실습 6절](../Ch04_Operators/Concepts_Lab.ko.md#6-연산자-우선순위와-결합-방향)).

| 식 | 해석 | 값 |
|:-----|:-----|:---:|
| `p[2]` | `*(p + 2)`, 즉 `arr[2]` | 5 |
| `*p + 1` | `(*p) + 1`, 즉 `arr[0] + 1` | 2 |
| `*(p + 1)` | `arr[1]` | -3 |
| `*(p + 3)` | `arr[3]` | -6 |
| `*p = arr[2] - *p;` 뒤의 `arr[0]` | `arr[0]`에 5 - 1 = 4를 대입 | 4 |

*표 2. 포인터 수식의 해석과 값*

**코드:** [Example_PointerExpressions.c](Example_PointerExpressions.c)

```c
#include <stdio.h>

int main()
{
    int arr[6] = { 1,-3,5,-6,12,4 };
    int* p = arr;

    printf("1. %d \n", p[2]);       // result: 1. 5
    printf("2. %d \n", *p + 1);     // result: 2. 2
    printf("3. %d \n", *(p + 1));   // result: 3. -3
    printf("4. %d \n", *(p + 3));   // result: 4. -6

    *p = arr[2] - *p;
    printf("5. %d \n", arr[0]);     // result: 5. 4
}
```

```text
1. 5 
2. 2 
3. -3 
4. -6 
5. 4 
```

### 4.2 main에서 두 변수의 값 교환

**문제:** `main`에 `int a = 3, b = 5;`가 선언되어 있다. 필요하면 변수를 추가하여, `main` 안에서 `a`와 `b`의 값을 맞바꾸라.

**풀이:** `a = b; b = a;`처럼 바로 대입하면 첫 대입에서 `a`의 원래 값 3이 사라져 두 변수가 모두 5가 된다. 그래서 임시 변수 `temp`에 `a`의 값을 먼저 보관한 뒤, `a`에 `b`를, `b`에 `temp`를 대입한다.

**코드:** [Example_SwapInline.c](Example_SwapInline.c)

```c
#include <stdio.h>

int main()
{
    int a = 3, b = 5, temp;
    printf("1. a, b: %d, %d \n", a, b);

    temp = a;
    a = b;
    b = temp;

    printf("2. a, b: %d, %d \n", a, b);
}
```

```text
1. a, b: 3, 5 
2. a, b: 5, 3 
```

### 4.3 함수로 두 변수의 값 교환

**문제:** 4.2절의 교환 부분을 `void swap(int x, int y)` 함수로 작성하면 `main`의 `a`와 `b`가 바뀌지 않는다. 실행하여 문제가 무엇인지 분석하라.

**풀이:** `swap(a, b)`를 호출하면 `a`와 `b`의 값 3과 5가 매개변수 `x`, `y`에 복사된다. `swap`은 자신의 지역 변수인 `x`와 `y`만 맞바꾸고, 함수가 끝나면 `x`, `y`, `temp`는 사라진다. 따라서 `main`의 `a`와 `b`에는 변화가 없다([8장 3.1절](Concepts_Lecture.ko.md#31-값에-의한-전달-vs-주소에-의한-전달)). C의 함수는 결과값을 하나만 반환할 수 있으므로, 바뀐 두 값을 반환값으로 돌려줄 수도 없다. 그래서 반환형은 `void`이다.

**코드:** [Example_SwapByValue.c](Example_SwapByValue.c)

```c
#include <stdio.h>      // Extra problem 1: rewrite the swap with a function
void swap(int x, int y)
{
    int temp;
    temp = x;
    x = y;
    y = temp;
}

int main()
{
    int a = 3, b = 5;
    printf("1. a, b: %d, %d \n", a, b);

    swap(a, b);

    printf("2. a, b: %d, %d \n", a, b);
}
```

```text
1. a, b: 3, 5 
2. a, b: 3, 5 
```

```text
   main                     swap (호출 중)
┌──────────┐             ┌──────────┐
│ a = 3    │ ──복사───▶  │ x = 3→5  │
│ b = 5    │ ──복사───▶  │ y = 5→3  │
└──────────┘             │ temp = 3 │
 바뀌지 않음              └──────────┘
                          반환하면 사라짐
```

*그림 4. 값에 의한 호출에서 swap이 복사본만 바꾸는 모습*

반환값을 하나만 쓰면서 교환하는 방법도 있다. [Example_SwapReturn.c](Example_SwapReturn.c)의 `exchange()`는 `y`의 값, 즉 `b`의 원래 값을 반환하고, `main`은 미리 구해 둔 두 값의 합에서 그 값을 빼어 나머지 하나를 되살린다.

```c
#include <stdio.h>      // Extra problem 1: rewrite the swap with a function
int exchange(int x, int y)
{
    int temp;
    temp = x;
    x = y;
    y = temp;

    return x;
}

int main()
{
    int a = 3, b = 5, temp;
    printf("1. a, b: %d, %d \n", a, b);

    temp = a + b;
    a = exchange(a, b);
    b = temp - a;

    printf("2. a, b: %d, %d \n", a, b);
}
```

```text
1. a, b: 3, 5 
2. a, b: 5, 3 
```

> **참고:** 이 방법은 `a`와 `b`를 `main`에서 다시 대입하는 것이므로, 함수가 호출한 쪽의 변수를 직접 바꾼 것은 아니다. 또 `a + b`가 `int`의 범위를 넘으면 오버플로가 일어난다. 함수가 호출한 쪽의 변수를 직접 바꾸려면 `void swap(int *x, int *y)`처럼 변수의 주소를 매개변수로 받아 `*x`와 `*y`를 맞바꾸어야 하며, 이 풀이는 [HW08 문제 1](../../Coursework/HW08_Pointers-I/Assignment-Explanation.ko.md#1-맞바꾸기)에 있다([8장 3.2절](Concepts_Lecture.ko.md#32-포인터를-통한-변수-수정)).

---

<br>

## 요약

| 개념 | 핵심 요약 |
|:-----|:-----|
| 변수의 복사 | `int b = a;`는 값만 복사하므로, `b`를 바꿔도 다른 주소에 있는 `a`는 바뀌지 않는다. |
| 주소 출력 | 주소는 `&`로 구하고 `%p`로 출력하며, 길이는 빌드의 비트 수에, 값은 실행마다 달라진다. |
| 포인터 | 다른 변수의 주소를 저장하는 변수이며, `int *p = &a;`처럼 선언하고 초기화한다. |
| 역참조 | `*p`는 `p`가 가리키는 변수이며, 읽으면 값을 얻고 대입하면 그 변수가 바뀐다. |
| 포인터의 크기 | 가리키는 타입과 관계없이 32비트 환경에서 4바이트, 64비트 환경에서 8바이트이다. |
| 포인터 연산 | `p + n`은 `p`의 주소에 n × `sizeof(*p)`를 더한 주소이다. |
| 포인터와 배열 | `int *p = arr;`이면 `p[i]`, `*(p + i)`, `arr[i]`, `*(arr + i)`가 모두 같은 원소이다. |
| 값에 의한 호출과 swap | 매개변수는 복사본이므로 `swap(int x, int y)`는 호출한 쪽의 변수를 바꾸지 못한다. |

---

<br>

## 점검 문제

1. **역참조:** `int x = 10; int *q = &x; *q = *q * 3;`을 실행한 뒤 `x`의 값을 쓰라.

   <details>
   <summary>정답</summary>

   오른쪽의 `*q`는 `x`의 값 10이고, 왼쪽의 `*q`는 `x`의 메모리 영역이므로 `x`에 30이 대입된다.

   </details>

2. **포인터 연산:** `double d[4];`에서 `&d[0]`이 `0x1000`일 때 `&d[0] + 3`의 주소는 무엇인가?

   <details>
   <summary>정답</summary>

   `double`이 8바이트이므로 0x1000 + 3 × 8 = 0x1018이다. 이 주소는 `&d[3]`과 같다.

   </details>

3. **우선순위:** `int a[3] = {10, 20, 30}; int *p = a;`일 때 `*p + 2`와 `*(p + 2)`의 값은 각각 무엇인가?

   <details>
   <summary>정답</summary>

   `*`가 `+`보다 먼저 결합하므로 `*p + 2`는 `a[0] + 2`, 즉 12이다. `*(p + 2)`는 `a[2]`, 즉 30이다.

   </details>

4. **포인터의 크기:** 64비트 빌드에서 `char *c;`와 `double *d;`의 `sizeof` 값은 각각 얼마이며, 그 이유는 무엇인가?

   <details>
   <summary>정답</summary>

   둘 다 8이다. 포인터는 주소를 저장하는 변수이고, 64비트 환경에서 주소는 가리키는 타입과 관계없이 8바이트이기 때문이다.

   </details>

5. **swap:** 4.3절의 `swap(int x, int y)` 안에 `printf("%d %d\n", x, y);`를 맨 끝에 추가하면 무엇이 출력되는가? 이것이 `main`의 결과와 다른 이유는 무엇인가?

   <details>
   <summary>정답</summary>

   `5 3`이 출력된다. `swap` 안에서는 복사본 `x`, `y`가 맞바뀌었지만, 이들은 `main`의 `a`, `b`와 다른 메모리에 있는 지역 변수이므로 `main`으로 돌아가면 `a`, `b`는 3, 5 그대로이다.

   </details>
