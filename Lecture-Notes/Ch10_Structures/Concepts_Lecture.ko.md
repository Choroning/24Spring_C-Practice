# 10장 — 구조체

[레포지토리 안내](../../README.ko.md) | [English](Concepts_Lecture.md) | [한국어](Concepts_Lecture.ko.md)

> **최종 수정일:** 2026-11-19
>
> Warming-Up C Programming, 천정아, Ch 10

> **학습 목표:**
> 1. 구조체를 정의하고 구조체 변수를 선언, 초기화, 대입할 수 있다
> 2. 패딩과 정렬 때문에 구조체의 크기가 멤버 크기의 합보다 클 수 있는 이유를 설명할 수 있다
> 3. 점 연산자와 화살표 연산자로 구조체 변수와 구조체 포인터의 멤버에 접근할 수 있다
> 4. 구조체 배열을 순회, 검색, 정렬하고 구조체를 함수에 값 또는 포인터로 전달할 수 있다
> 5. 중첩 구조체, `enum`, `union`, `typedef`의 쓰임과 특징을 설명할 수 있다

---

## 목차

- [1. 구조체 기초](#1-구조체-기초)
  - [1.1 구조체 개념](#11-구조체-개념)
  - [1.2 구조체 정의](#12-구조체-정의)
  - [1.3 구조체 변수 선언](#13-구조체-변수-선언)
  - [1.4 구조체 초기화](#14-구조체-초기화)
  - [1.5 멤버 접근](#15-멤버-접근)
  - [1.6 구조체 대입](#16-구조체-대입)
  - [1.7 구조체 비교](#17-구조체-비교)
  - [1.8 `offsetof`로 확인하는 구조체의 배치](#18-offsetof로-확인하는-구조체의-배치)
  - [1.9 일부 멤버만 초기화한 구조체](#19-일부-멤버만-초기화한-구조체)
- [2. 구조체 활용](#2-구조체-활용)
  - [2.1 구조체 배열](#21-구조체-배열)
  - [2.2 구조체 포인터](#22-구조체-포인터)
  - [2.3 함수에 구조체 전달](#23-함수에-구조체-전달)
  - [2.4 중첩 구조체](#24-중첩-구조체)
  - [2.5 구조체를 반환하는 함수](#25-구조체를-반환하는-함수)
  - [2.6 비트 필드](#26-비트-필드)
  - [2.7 구조체 배열과 구조체 포인터의 연산](#27-구조체-배열과-구조체-포인터의-연산)
  - [2.8 구조체 멤버의 입력](#28-구조체-멤버의-입력)
  - [2.9 중첩 구조체와 공용체의 메모리 배치](#29-중첩-구조체와-공용체의-메모리-배치)
- [3. 관련 데이터 타입](#3-관련-데이터-타입)
  - [3.1 `enum`](#31-enum)
  - [3.2 `union`](#32-union)
  - [3.3 `typedef`](#33-typedef)
  - [3.4 `typedef`의 여러 가지 용도](#34-typedef의-여러-가지-용도)
  - [3.5 열거체와 `switch`로 방향 처리하기](#35-열거체와-switch로-방향-처리하기)
  - [3.6 구조체와 관련 타입의 흔한 실수](#36-구조체와-관련-타입의-흔한-실수)
  - [3.7 종합 예: 성적 처리 프로그램](#37-종합-예-성적-처리-프로그램)
  - [3.8 열거 상수의 이름 출력과 값의 검사](#38-열거-상수의-이름-출력과-값의-검사)
- [개념 적용](#개념-적용)
- [요약](#요약)
- [점검 문제](#점검-문제)

---

<br>

## 1. 구조체 기초

### 1.1 구조체 개념

**배열**은 **같은** 데이터 타입의 값을 여러 개 저장한다. **구조체**는 **서로 다른** 데이터 타입의 변수를 하나의 이름으로 묶어 **사용자 정의 데이터 타입**을 만든다. C 언어에서 구조체는 사용자 정의형을 만드는 방법이다.

```text
배열 vs 구조체
├── 배열    : 같은 데이터 타입 × N     → int scores[5];
└── 구조체  : 다른 데이터 타입 × N     → struct student { char name[20]; int age; double gpa; };
```

*그림 1. 같은 데이터 타입을 묶는 배열과 다른 데이터 타입을 묶는 구조체*

| 특성 | 배열 | 구조체 |
|:----|:-----|:------|
| 요소 데이터 타입 | 모두 동일 | 서로 다를 수 있음 |
| 접근 방식 | 인덱스 `a[i]` | 멤버 이름 `s.age` |
| 사용자 정의 | 아니오 (내장) | 예 (`struct`) |
| 용도 | 같은 데이터 타입의 데이터 모음 | 서로 다른 데이터 타입의 필드를 가진 레코드 |

*표 1. 배열과 구조체의 비교*

구조체는 `struct` 키워드로 정의한다. 닫는 중괄호 `}` 뒤에 반드시 **세미콜론**을 붙여야 한다. 여러 함수에서 사용하려면 **함수 바깥**(파일 범위)에 정의하며, 소스 파일의 시작 부분에 정의하는 것이 좋다.

```c
struct content {
    char title[50];
    int price;
    double rate;
};              // <-- 세미콜론 필수!
```

### 1.2 구조체 정의

**문법:**

```c
struct 태그명 {
    자료형1 멤버1;
    자료형2 멤버2;
    // ...
};
```

- **태그명(tag name):** 구조체를 구별하는 이름이다. **완전한 데이터 타입 이름**은 `struct 태그명`이며, `struct` 키워드를 반드시 함께 써야 한다.
- **멤버(member, 구성 변수):** 구조체를 구성하는 개별 변수이다.

```c
struct content {
    char title[50];    // 멤버 1
    int price;         // 멤버 2
    double rate;       // 멤버 3
};
```

구조체를 정의하면 새로운 데이터 타입이 만들어질 뿐 구조체 변수가 생성되는 것은 아니다. 구조체형의 변수를 선언해야 구조체 변수가 메모리에 할당된다.

> **주의:** `struct` 없이 태그명만 쓰면 컴파일러가 `content`가 구조체 이름이라는 것을 알 수 없으므로 **컴파일 오류**가 발생한다.
> ```c
> content c1;          // 컴파일 오류!
> struct content c1;   // 올바른 사용
> ```

**크기와 정렬:**

구조체의 크기는 멤버 크기의 합 **이상**이다. 컴파일러가 효율적인 메모리 접근을 위해 멤버 사이나 끝에 **패딩/정렬(padding/alignment)** 바이트를 삽입할 수 있기 때문이다.

```c
struct example {
    char c;      // 1바이트
    int n;       // 4바이트
    double d;    // 8바이트
};
// 합계 = 13바이트이지만, sizeof(struct example)은 16 또는 24가 될 수 있음

printf("크기: %zu\n", sizeof(struct example));  // 16 또는 24일 가능성
```

```text
메모리 레이아웃 (패딩 포함 가능):
┌─────┬─────────┬──────────┬──────────────────┐
│  c  │   패딩   │    n     │        d         │
│ 1B  │   3B    │    4B    │        8B        │
└─────┴─────────┴──────────┴──────────────────┘
sizeof(struct example) = 16  (13이 아님)
```

*그림 2. `struct example`의 패딩을 포함한 메모리 레이아웃 (일반적인 64비트 시스템)*

일반적인 64비트 시스템에서 `int`는 4의 배수 주소에, `double`은 8의 배수 주소에 놓이므로 `c` 뒤에 3바이트가 채워져 크기가 16이 된다. 멤버 순서를 `char c; double d; int n;`으로 바꾸면 `c` 뒤에 7바이트, `n` 뒤에 4바이트가 채워져 크기가 24가 되므로, 같은 멤버라도 선언 순서에 따라 크기가 달라질 수 있다.

> **핵심:** `sizeof(struct 태그명)` >= 멤버 크기의 합이다. 컴파일러가 멤버 사이에 정렬을 위한 패딩 바이트를 삽입할 수 있다.

### 1.3 구조체 변수 선언

구조체를 정의한 후, 해당 데이터 타입의 변수를 선언할 수 있다.

```c
struct content c1, c2, c3;   // 변수 3개 선언
```

구조체 **정의와 동시에** 변수를 선언할 수도 있다.

```c
struct content {
    char title[50];
    int price;
    double rate;
} c1, c2;                    // 구조체 정의와 c1, c2 선언을 동시에
```

**익명 구조체** (태그명 없음):

```c
struct {
    char title[50];
    int price;
    double rate;
} c1;                        // 작동하지만, 이 자료형으로 추가 변수를 선언할 수 없음
```

> **주의:** 익명 구조체는 태그명이 없으므로, 나중에 같은 데이터 타입의 변수를 **다시 선언할 수 없다**.

**메모리 할당:** 멤버는 **선언 순서대로** 메모리에 차례로 할당된다.

```text
struct content c1;

┌────────────────────────┬──────────┬────────────────┐
│    c1.title (50바이트)   │ c1.price │    c1.rate     │
│                        │  (4바이트) │    (8바이트)     │
└────────────────────────┴──────────┴────────────────┘
            (멤버 사이에 패딩이 포함될 수 있음)
```

*그림 3. 구조체 변수 c1의 멤버가 선언 순서대로 할당된 모습*

### 1.4 구조체 초기화

**초기화 리스트** `{}`를 사용하여 **멤버 선언 순서**에 맞게 초기화한다.

```c
struct content c1 = {"Avengers", 11000, 8.8};
```

| 초기화 | `title` | `price` | `rate` |
|:------|:--------|:--------|:-------|
| `{"Avengers", 11000, 8.8}` | `"Avengers"` | `11000` | `8.8` |

*표 2. 초기화 리스트의 값이 대응되는 멤버*

**부분 초기화:** 초기값이 부족하면 나머지 멤버는 **0**으로 채워진다.

```c
struct content c2 = {"Inception"};
// c2.title = "Inception", c2.price = 0, c2.rate = 0.0
```

**초기값이 너무 많으면:** 초기값이 멤버의 개수보다 많으면 안 된다. 표준을 어기는 코드이므로 컴파일러가 진단 메시지를 내며, Visual Studio는 컴파일 오류로 처리하고 gcc와 clang은 기본적으로 경고를 낸 뒤 남는 값을 버린다.

```c
struct content c3 = {"Matrix", 9000, 9.1, 100};  // 컴파일 오류!
```

**다른 구조체 변수로 초기화:** 같은 멤버끼리 1:1로 복사하여 초기화한다.

```c
struct content c1 = {"Avengers", 11000, 8.8};
struct content c2 = c1;   // c1의 모든 멤버를 c2로 복사
```

### 1.5 멤버 접근

**점 연산자**(`.`, 멤버 접근 연산자)를 사용하여 구조체 변수를 통해 멤버에 접근한다.

```c
struct content c1 = {"Avengers", 11000, 8.8};

c1.rate = 8.9;                      // 멤버 수정
c1.price *= 0.8;                    // 멤버에 복합 대입
strcat(c1.title, ": Endgame");      // 멤버에 문자열 연산
printf("제목: %s\n", c1.title);      // 멤버 읽기
```

> **핵심:** 멤버는 구조체 변수를 통해서**만** 접근할 수 있다. 멤버 이름을 단독으로 사용할 수 없으며, `title`만으로는 `c1.title`을 가리키지 않는다. 같은 이름의 일반 변수가 있으면 `title`은 그 변수를 뜻한다.

```c
// title = "Test";       // 컴파일 오류: title은 독립 변수가 아님
c1.title;                // 올바른 사용: 구조체 변수를 통한 접근
```

구조체 변수를 여러 개 선언하면 서로 다른 메모리에 할당되며, 멤버도 구조체 변수마다 따로 할당된다. 멤버에는 항상 구조체 변수를 통해 접근하므로 어느 변수의 멤버인지 구분할 수 있다.

### 1.6 구조체 대입

선언 이후, 같은 데이터 타입의 구조체를 다른 구조체에 **대입**할 수 있다. 이때 **모든 멤버가 1:1로 복사**된다.

```c
struct content c1 = {"Avengers", 11000, 8.8};
struct content c3;

c3 = c1;   // title, price, rate 모두 c1에서 c3으로 복사
```

**제한 사항:**

선언 이후에는 초기화 리스트 `{}`를 사용할 수 **없다**(선언 시점에서만 가능).

```c
struct content c3;
c3 = {"Matrix", 9000, 9.1};    // 컴파일 오류!
```

배열 멤버끼리는 직접 대입할 수 **없으므로** 문자열에는 `strcpy`를 사용해야 한다.

```c
struct content c1 = {"Avengers", 11000, 8.8};
struct content c3;

// c3.title = c1.title;         // 컴파일 오류: 배열은 대입 불가!
strcpy(c3.title, c1.title);     // 올바른 방법: 문자열에는 strcpy 사용
c3.price = c1.price;            // OK: 배열이 아닌 멤버는 대입 가능
c3.rate = c1.rate;              // OK
```

> **참고:** **팁.** 구조체 전체 대입 `c3 = c1`은 정상 작동하며 배열 멤버도 올바르게 복사된다(구조체 전체를 바이트 단위로 복사). 제한은 `c3.title = c1.title`처럼 **개별** 배열 멤버를 대입하려 할 때만 적용된다.

### 1.7 구조체 비교

구조체 변수에는 관계 연산자를 사용할 수 없으므로 `==`나 `!=`로 직접 비교할 수 **없다**.

```c
struct content c1 = {"Avengers", 11000, 8.8};
struct content c2 = c1;

// if (c1 == c2) { ... }     // 컴파일 오류!
```

대신 **멤버별로 비교**해야 한다. 문자열 멤버에는 `strcmp`를 사용한다.

```c
if (strcmp(c1.title, c2.title) == 0 &&
    c1.price == c2.price &&
    c1.rate == c2.rate) {
    printf("c1과 c2는 같다\n");
}
```

> **주의:** C에서 구조체를 `==`로 비교하면 컴파일 오류가 발생한다. 반드시 각 멤버를 **개별적으로** 비교해야 한다. 문자열(char 배열) 멤버는 `strcmp`를 사용하고, `==`로 비교하면 안 된다. 패딩 바이트와 문자열의 널 문자 뒤 바이트의 값은 정해져 있지 않으므로, 구조체 전체를 `memcmp`로 비교하는 방법도 믿을 수 없다.

### 1.8 `offsetof`로 확인하는 구조체의 배치

1.2절의 패딩은 `<stddef.h>`의 매크로 `offsetof(구조체 타입, 멤버)`로 직접 확인할 수 있다. `offsetof`는 구조체의 시작에서 그 멤버까지 몇 바이트 떨어져 있는지를 알려 준다. 다음 두 구조체는 같은 멤버 `char` 두 개와 `int` 하나를 순서만 바꾸어 담는다.

```c
#include <stdio.h>
#include <stddef.h>

struct A {
    char c;
    int n;
    char d;
};

struct B {
    int n;
    char c;
    char d;
};

int main(void)
{
    printf("A: size %zu, c %zu, n %zu, d %zu\n", sizeof(struct A),
           offsetof(struct A, c), offsetof(struct A, n), offsetof(struct A, d));
    printf("B: size %zu, n %zu, c %zu, d %zu\n", sizeof(struct B),
           offsetof(struct B, n), offsetof(struct B, c), offsetof(struct B, d));
    return 0;
}
```

```text
A: size 12, c 0, n 4, d 8
B: size 8, n 0, c 4, d 5
```

```text
struct A (12바이트)
         0     1     2     3     4     5     6     7     8     9    10    11   ← 오프셋
      ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
      │  c  │ /// │ /// │ /// │  n  │  n  │  n  │  n  │  d  │ /// │ /// │ /// │
      └─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘
struct B (8바이트)
         0     1     2     3     4     5     6     7   ← 오프셋
      ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
      │  n  │  n  │  n  │  n  │  c  │  d  │ /// │ /// │
      └─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘
```

*그림 4. struct A와 struct B의 멤버 오프셋과 패딩(///)*

이 환경에서 4바이트 `int`는 주소가 4의 배수인 자리에 놓여야 한다. `struct A`는 오프셋 0의 `c` 뒤에 `n`이 4의 배수인 오프셋 4에 오도록 3바이트를 채우고, 오프셋 8의 `d` 뒤에도 3바이트를 채운다. 끝에 채우는 패딩은 `struct A`의 배열을 만들었을 때 다음 원소의 `n`도 4의 배수 자리에 오게 하기 위한 것이므로, 구조체의 크기는 가장 큰 정렬 단위(여기서는 4)의 배수가 된다. 멤버의 합은 1 + 4 + 1 = 6바이트이지만 `struct A`는 12바이트이다. `struct B`처럼 큰 멤버를 앞에 두고 작은 멤버를 모으면 `c`와 `d`가 오프셋 4, 5에 붙어 놓이고 끝에 2바이트만 채우므로 8바이트로 줄어든다. 정렬 규칙은 플랫폼이 정하므로, 구조체의 크기는 숫자를 더해 짐작하지 않고 `sizeof`로 구한다.

### 1.9 일부 멤버만 초기화한 구조체

배열과 마찬가지로 구조체의 초기화 리스트에 초기값이 모자라면 나머지 멤버는 0으로 초기화된다. 문자 배열 멤버는 모든 원소가 널 문자가 되어 빈 문자열이 된다. 따라서 `{ 0 }`은 멤버가 몇 개이든 구조체 전체를 0으로 시작하게 하는 관용구이다.

```c
struct item {
    char name[8];
    int price;
    int stock;
};

struct item a = { "pen", 1500 };
struct item b = { 0 };

printf("[%s] %d %d\n", a.name, a.price, a.stock);
printf("[%s] %d %d\n", b.name, b.price, b.stock);
```

```text
[pen] 1500 0
[] 0 0
```

`a`는 `stock`의 초기값이 없어 0이 되고, `b`는 첫 멤버만 0으로 지정했지만 모든 멤버가 0이다. Clang에 `-Wextra`를 주면 `a`의 초기화에 `missing field 'stock' initializer` 경고를 낸다. 일부러 생략한 것이 아니라 빠뜨렸을 가능성을 알려 주는 경고이며, `{ 0 }`에는 이 경고를 내지 않는다. 반면 초기화 리스트 없이 함수 안에서 선언한 구조체 변수 `struct item c;`는 모든 멤버가 쓰레기 값이므로, 쓰기 전에 각 멤버에 값을 대입해야 한다.

> **참고:** **지정 초기화.** C99부터는 `struct item c = { .price = 900, .name = "clip" };`처럼 멤버 이름을 지정하여 순서와 관계없이 초기화할 수 있다. 지정하지 않은 `stock`은 0이 된다. 멤버가 많은 구조체에서 어느 값이 어느 멤버에 들어가는지 분명해지지만, 교재의 ANSI C 문법에는 없는 기능이다.

---

<br>

## 2. 구조체 활용

### 2.1 구조체 배열

**구조체 배열**은 같은 구조체 데이터 타입의 레코드를 여러 개 저장한다. 구조체 배열의 원소도 메모리에 연속으로 할당된다.

```c
struct content movies[10];
```

배열 인덱스와 점 연산자로 멤버에 접근한다. `movies[i]`가 구조체 변수이므로 `movies[i].멤버`로 쓴다.

```c
movies[0].price = 12000;
strcpy(movies[0].title, "Avengers");
movies[0].rate = 8.8;
```

**중첩 중괄호로 초기화:**

```c
struct content movies[3] = {
    {"Avengers", 11000, 8.8},
    {"Inception", 9000, 9.2},
    {"Parasite", 10000, 9.5}
};
```

**구조체 배열 순회:**

```c
for (int i = 0; i < 3; i++) {
    printf("%-15s %6d %5.1f\n",
           movies[i].title, movies[i].price, movies[i].rate);
}
```

**구조체 배열 검색:** 검색할 제목을 입력받아, 제목이 같은 원소를 찾으면 `break`로 `for` 문을 빠져나온다. 반복이 끝난 뒤 `i`가 배열 크기보다 작으면 `i`가 찾은 원소의 인덱스이고, 배열 크기와 같으면 검색에 실패한 것이다.

```c
char title[50];
int i;

printf("검색할 제목: ");
scanf("%s", title);
for (i = 0; i < 3; i++) {
    if (strcmp(movies[i].title, title) == 0)
        break;                    // 찾으면 for 탈출 (i는 찾은 원소의 인덱스)
}
if (i < 3)
    printf("가격: %d, 평점: %.1f\n", movies[i].price, movies[i].rate);
else
    printf("찾는 콘텐츠가 없습니다.\n");
```

**구조체 배열 정렬 (평점 내림차순, 선택 정렬):**

```c
for (int i = 0; i < n - 1; i++) {
    int max_idx = i;
    for (int j = i + 1; j < n; j++) {
        if (movies[j].rate > movies[max_idx].rate) {
            max_idx = j;
        }
    }
    if (max_idx != i) {
        struct content temp = movies[i];
        movies[i] = movies[max_idx];
        movies[max_idx] = temp;
    }
}
```

> **참고:** **팁.** 구조체 변수 두 개를 교환하려면 같은 구조체 데이터 타입의 임시 변수를 사용한다. 구조체 전체 대입으로 모든 멤버가 복사된다.

### 2.2 구조체 포인터

**구조체 포인터**는 구조체 변수의 주소를 저장한다.

```c
struct content c1 = {"Avengers", 11000, 8.8};
struct content *p = &c1;
```

포인터를 통해 멤버에 접근할 때는 **화살표 연산자**(`->`, 간접 멤버 접근 연산자)를 사용한다.

```c
printf("제목: %s\n", p->title);     // 화살표 연산자
printf("가격: %d\n", p->price);
printf("평점: %.1f\n", p->rate);
```

화살표 연산자 `->`는 역참조 `(*p).멤버`와 동일하다.

```c
p->title      // (*p).title과 동일
p->price      // (*p).price과 동일
p->rate       // (*p).rate과 동일
```

> **주의:** `(*p).title`에서 괄호가 필수이다. 점 `.`이 `*`보다 우선순위가 높기 때문에, 괄호 없이 `*p.title`이라 쓰면 `*(p.title)`로 해석되어 `p`가 구조체 포인터일 때 오류가 발생한다.

```text
 p ──────► ┌───────────────────────┐
           │ c1.title = "Avengers" │
           │ c1.price = 11000      │
           │ c1.rate  = 8.8        │
           └───────────────────────┘

p->title   ≡  (*p).title   ≡  c1.title
```

*그림 5. 구조체 변수 c1을 가리키는 구조체 포인터 p*

구조체 변수에 읽기 전용으로 접근하게 하려면 `const struct content *p = &c1;`처럼 `const` 포인터로 선언한다. 이 포인터로는 `p->price`를 읽을 수만 있고, `p->price = 0;`처럼 멤버를 변경하면 컴파일 오류가 난다.

### 2.3 함수에 구조체 전달

구조체를 함수의 인자로 전달할 때는 값에 의한 전달과 포인터에 의한 전달을 모두 사용할 수 있다.

**값에 의한 전달(pass by value):** 함수가 **복사본**을 받는다.

```c
void display(struct content c) {
    printf("%s %d %.1f\n", c.title, c.price, c.rate);
    c.price = 0;   // 복사본만 수정: 원본은 변하지 않음
}

int main() {
    struct content c1 = {"Avengers", 11000, 8.8};
    display(c1);    // 복사본 전달
    printf("가격: %d\n", c1.price);  // 여전히 11000
    return 0;
}
```

**포인터에 의한 전달(pass by pointer):** 함수가 **원본을 수정**할 수 있다.

```c
void discount(struct content *p, double rate) {
    p->price *= rate;   // 원본 구조체를 수정
}

int main() {
    struct content c1 = {"Avengers", 11000, 8.8};
    discount(&c1, 0.8);
    printf("가격: %d\n", c1.price);  // 8800
    return 0;
}
```

구조체를 값으로 전달하면 구조체 전체를 복사해야 하므로 시간과 메모리 면에서 성능이 떨어진다. `int` 두 개로 된 좌표 구조체처럼 작은 구조체는 값으로 전달해도 성능 저하가 거의 없지만, `content`처럼 큰 구조체는 주소를 전달하는 편이 좋다. 구조체가 출력 매개변수나 입출력 매개변수이거나 구조체를 복사하지 않고 전달하려면 포인터로 전달하고, 입력 매개변수이면 `const` 포인터로 전달한다.

**구조체 배열 전달:** 배열은 항상 포인터로 변환된다.

```c
void display_all(const struct content arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%-15s %6d %5.1f\n",
               arr[i].title, arr[i].price, arr[i].rate);
    }
}

int main() {
    struct content movies[3] = {
        {"Avengers", 11000, 8.8},
        {"Inception", 9000, 9.2},
        {"Parasite", 10000, 9.5}
    };
    display_all(movies, 3);
    return 0;
}
```

> **핵심:** 함수가 구조체를 **수정하지 않아야** 할 때는 매개변수에 `const`를 사용한다. 의도를 명시하고 실수로 인한 변경을 방지한다.

**포인터를 이용한 입력 함수:**

```c
void input_content(struct content *p) {
    printf("제목: ");
    scanf("%s", p->title);
    printf("가격: ");
    scanf("%d", &p->price);
    printf("평점: ");
    scanf("%lf", &p->rate);
}
```

구조체를 함수의 인자로 전달하는 방법을 정리하면 다음과 같다. (1) 함수의 매개변수를 구조체 포인터형으로 선언한다. (2) 구조체 변수가 입력 매개변수이면 `const`를 지정한다. (3) 함수를 호출할 때 구조체 변수의 주소를 인자로 전달한다. (4) 함수를 정의할 때 구조체 포인터와 `->`로 멤버에 접근한다.

값에 의한 전달과 포인터에 의한 전달의 차이는 복사되는 바이트 수로 확인할 수 있다. 1.2절의 `struct content`를 두 방식으로 넘기는 함수가 각자 받은 매개변수의 크기를 출력하면 다음과 같다.

```c
void by_value(struct content c)
{
    printf("by value: %zu bytes copied\n", sizeof c);
}

void by_pointer(const struct content *p)
{
    printf("by pointer: %zu bytes copied\n", sizeof p);
}
```

```text
by value: 64 bytes copied
by pointer: 8 bytes copied
```

`struct content`는 `title` 50바이트 뒤에 `int`를 4의 배수 자리에 맞추는 2바이트 패딩, `price` 4바이트, `rate` 8바이트가 이어져 64바이트이다. 값으로 넘기면 호출할 때마다 이 64바이트가 매개변수로 복사되고, 포인터로 넘기면 주소 8바이트만 복사된다. 구조체가 클수록, 그리고 함수를 많이 호출할수록 이 차이가 커지므로 큰 구조체는 포인터로 넘기고, 함수가 구조체를 바꾸지 않으면 `const`를 붙여 값에 의한 전달처럼 원본을 보호한다.

### 2.4 중첩 구조체

구조체가 다른 구조체를 멤버로 포함할 수 있다. 멤버로 쓰이는 구조체(`date`)는 그것을 포함하는 구조체(`student`)보다 앞에 정의되어 있어야 한다.

```c
struct date {
    int year;
    int month;
    int day;
};

struct student {
    char name[20];
    int id;
    struct date birthday;   // 중첩 구조체
};
```

**초기화:**

```c
struct student s1 = {"Kim", 2024001, {2005, 3, 15}};
```

**중첩 멤버 접근:** 점 연산자를 연속해서 사용한다.

```c
printf("이름: %s\n", s1.name);
printf("생일: %d-%02d-%02d\n",
       s1.birthday.year, s1.birthday.month, s1.birthday.day);
```

**포인터와 함께:**

```c
struct student *p = &s1;
printf("년도: %d\n", p->birthday.year);   // 포인터->외부.내부
```

```text
struct student s1

┌───────────────────────────────┐
│ name = "Kim"                  │
│ id = 2024001                  │
│ birthday ┌─────────────────┐  │
│          │ year  = 2005    │  │
│          │ month = 3       │  │
│          │ day   = 15      │  │
│          └─────────────────┘  │
└───────────────────────────────┘
```

*그림 6. `struct date`를 멤버로 포함하는 구조체 변수 s1*

`s1.birthday`는 그 자체로 `struct date`형 변수처럼 사용할 수 있다.

### 2.5 구조체를 반환하는 함수

배열과 달리 구조체는 대입할 수 있으므로 함수의 반환형으로도 쓸 수 있다. 함수가 구조체를 반환하면 멤버 전체가 복사되어 호출한 쪽에 전달되므로, 여러 값을 하나의 구조체로 묶어 한꺼번에 돌려줄 수 있다. 다음 코드는 두 점의 중점을 구조체로 반환하는 함수와, 점의 좌표를 포인터로 바꾸는 함수를 비교한다.

```c
struct point {
    int x, y;
};

struct point midpoint(struct point a, struct point b)
{
    struct point m;

    m.x = (a.x + b.x) / 2;
    m.y = (a.y + b.y) / 2;
    return m;                       // m의 멤버 전체가 복사되어 반환된다
}

void move(struct point *p, int dx, int dy)
{
    p->x += dx;                     // 호출한 쪽의 구조체를 직접 바꾼다
    p->y += dy;
}

int main(void)
{
    struct point a = { 0, 0 }, b = { 10, 6 }, m;

    m = midpoint(a, b);
    printf("m = (%d, %d)\n", m.x, m.y);
    move(&m, 1, -1);
    printf("m = (%d, %d)\n", m.x, m.y);
    printf("sizeof(struct point) = %zu\n", sizeof(struct point));
    return 0;
}
```

```text
m = (5, 3)
m = (6, 2)
sizeof(struct point) = 8
```

`midpoint`는 지역 변수 `m`을 반환하지만, 반환되는 것은 `m`의 주소가 아니라 멤버의 값을 복사한 구조체이므로 8장 3.5절의 댕글링 포인터 문제가 생기지 않는다. (0 + 10) / 2 = 5, (0 + 6) / 2 = 3이므로 중점은 (5, 3)이고, `move(&m, 1, -1)`이 주소를 통해 `m`을 (6, 2)로 바꾼다. 결과를 새 값으로 만들어 돌려주는 함수는 반환형을 구조체로, 기존 구조체를 고치는 함수는 매개변수를 구조체 포인터로 쓰는 것이 자연스럽다. `struct point`는 8바이트라 복사 비용이 작지만, 문자 배열 멤버가 있는 큰 구조체는 2.3절처럼 `const` 포인터로 받는 편이 효율적이다.

### 2.6 비트 필드

**비트 필드(bit field)** 는 구조체 멤버가 차지할 비트 수를 직접 지정하는 문법이다. 값의 범위가 작은 멤버 여러 개를 하나의 정수 안에 비트 단위로 나누어 저장하므로 메모리를 줄일 수 있다. 멤버 이름 뒤에 콜론과 비트 수를 쓰며, 사용하는 방법은 일반 구조체와 같다.

```c
struct date_bits {
    unsigned int day : 5;       /* 1~31: 5 bits */
    unsigned int month : 4;     /* 1~12: 4 bits */
    unsigned int year : 12;     /* 0~4095: 12 bits */
};

struct date_ints {
    unsigned int day, month, year;
};

int main(void)
{
    struct date_bits d = { 19, 11, 2026 };

    printf("%u-%u-%u\n", d.year, d.month, d.day);
    printf("sizeof bits = %zu, sizeof ints = %zu\n", sizeof(struct date_bits), sizeof(struct date_ints));
    d.month = 13;
    printf("month = %u\n", d.month);
    d.month = 17;
    printf("month = %u\n", d.month);
    return 0;
}
```

```text
2026-11-19
sizeof bits = 4, sizeof ints = 12
month = 13
month = 1
```

5 + 4 + 12 = 21비트이므로 세 멤버가 `unsigned int` 하나(32비트)에 들어가 구조체의 크기는 4바이트이고, 같은 멤버를 각각 `unsigned int`로 둔 구조체는 12바이트이다. 그 대신 각 멤버가 담을 수 있는 값은 비트 수로 제한된다. 4비트 `month`는 0~15만 담으므로 13은 저장되지만 의미상 잘못된 달이고, 17(`10001`)은 하위 4비트 `0001`만 남아 1이 된다. Clang은 상수 17의 대입에 `implicit truncation from 'int' to bit-field changes value from 17 to 1` 경고를 낸다. 비트 필드의 멤버는 주소를 가질 수 없으므로 `&d.month`나 `scanf("%u", &d.month)`는 쓸 수 없으며, 비트의 배치 순서는 구현이 정한다. 하드웨어 레지스터처럼 비트 배치가 정해진 데이터를 다룰 때의 주의점은 13장에서 다룬다.

### 2.7 구조체 배열과 구조체 포인터의 연산

구조체 포인터에도 8장의 포인터 연산이 그대로 적용된다. `struct point *p`에 1을 더하면 `sizeof(struct point)`만큼, 즉 구조체 하나만큼 이동하므로, 구조체 배열을 포인터로 훑을 수 있다.

```c
struct point {
    int x, y;
};

int main(void)
{
    struct point pts[3] = { { 1, 2 }, { 3, 4 }, { 5, 6 } };
    struct point *p;
    int sum = 0;

    for (p = pts; p < pts + 3; p++) {
        sum += p->x * p->y;
        printf("p = %p, p->x = %d, p->y = %d\n", (void *)p, p->x, p->y);
    }
    printf("sum = %d\n", sum);
    p = pts;
    printf("%d %d %d\n", (p + 1)->x, pts[1].x, (*(p + 2)).y);
    return 0;
}
```

```text
p = 0x16f442af0, p->x = 1, p->y = 2
p = 0x16f442af8, p->x = 3, p->y = 4
p = 0x16f442b00, p->x = 5, p->y = 6
sum = 44
3 3 6
```

```text
          pts[0]                pts[1]                pts[2]
          af0        af4        af8        afc        b00        b04      ← 주소의 끝
        ┌──────────┬──────────┬──────────┬──────────┬──────────┬──────────┐
        │  x = 1   │  y = 2   │  x = 3   │  y = 4   │  x = 5   │  y = 6   │
        └──────────┴──────────┴──────────┴──────────┴──────────┴──────────┘
          ▲ p                   ▲ p + 1               ▲ p + 2
```

*그림 7. 구조체 배열 pts와 포인터 p의 이동*

`p`의 값은 회차마다 `struct point`의 크기인 8씩 커진다. 합계는 1 × 2 + 3 × 4 + 5 × 6 = 2 + 12 + 30 = 44이다. 마지막 줄의 세 수식은 같은 원소를 다르게 쓴 것이다. `(p + 1)->x`와 `pts[1].x`는 모두 두 번째 원소의 `x`인 3이고, `(*(p + 2)).y`는 세 번째 원소의 `y`인 6이다. 일반적으로 `pts[i].멤버`, `(pts + i)->멤버`, `(*(pts + i)).멤버`는 같다. `->`의 왼쪽에는 구조체의 주소가, `.`의 왼쪽에는 구조체 자체가 와야 한다는 규칙만 지키면 어느 표기든 쓸 수 있다.

`->`는 `.`, `[]`, 후위 `++`와 함께 가장 먼저 결합하는 연산자이므로, 증감 연산자와 섞으면 무엇이 증가하는지 주의해야 한다. `pts = { {1, 2}, {5, 6} }`이고 `p = pts`일 때 다음 세 수식을 차례로 실행하면 결과가 다르다.

```c
a = ++p->x;         // ++(p->x): pts[0].x가 2가 되고 a는 2
printf("%d %d\n", a, pts[0].x);
a = (++p)->x;       // p가 pts[1]로 이동하고 a는 5
printf("%d %d\n", a, (int)(p - pts));
a = p->x++;         // (p->x)++: a는 5, pts[1].x는 6이 됨
printf("%d %d\n", a, pts[1].x);
```

```text
2 2
5 1
5 6
```

첫 줄은 `->`가 전위 `++`보다 먼저 결합하므로 멤버 `x`가 증가한다. 둘째 줄은 괄호 때문에 포인터 `p`가 먼저 증가하여 다음 원소를 가리키며, `p - pts`가 1이다. 셋째 줄은 후위 `++`이므로 증가하기 전의 값 5가 `a`에 들어가고 멤버는 6이 된다. 포인터를 옮기려는 것인지 멤버를 바꾸려는 것인지에 따라 괄호를 분명히 쓴다.

### 2.8 구조체 멤버의 입력

구조체 멤버도 일반 변수와 같은 규칙으로 `scanf`에 넘긴다. `int` 멤버는 `&s.score`처럼 주소를 넘기고, 문자 배열 멤버는 배열 이름이 이미 주소이므로 `s.name`처럼 `&` 없이 넘긴다. 중첩 구조체의 멤버는 바깥에서부터 `.`으로 이어 쓴다. `.`이 `&`보다 먼저 결합하므로 `&s.birthday.year`는 `&(s.birthday.year)`, 즉 `year` 멤버의 주소이다.

```c
struct date {
    int year, month, day;
};

struct student {
    char name[20];
    int score;
    struct date birthday;
};

int main(void)
{
    struct student s;

    printf("name score year month day? ");
    if (scanf("%19s %d %d %d %d", s.name, &s.score, &s.birthday.year,
              &s.birthday.month, &s.birthday.day) != 5)
        return 1;
    printf("%s (%d) born %d-%d-%d\n", s.name, s.score, s.birthday.year,
           s.birthday.month, s.birthday.day);
    return 0;
}
```

```text
name score year month day? Kim 91 2005 3 14
Kim (91) born 2005-3-14
```

`%19s`는 `name`의 20바이트 가운데 널 문자 자리를 남기고 최대 19글자만 읽는다. `&`를 반대로 붙이면 Clang이 각각 다음과 같이 경고한다. 첫째는 `int` 멤버에 `&`를 빠뜨린 `scanf("%d", v.score)`, 둘째는 문자 배열 멤버에 `&`를 붙인 `scanf("%19s", &v.name)`에 대한 경고이다.

```text
warning: format specifies type 'int *' but the argument has type 'int' [-Wformat]
warning: format specifies type 'char *' but the argument has type 'char (*)[20]' [-Wformat]
```

둘째 경우 `&v.name`은 8장 2.6절의 `&arr`처럼 배열 전체의 주소(`char (*)[20]`)이다. 주소의 값은 `v.name`과 같아서 우연히 동작할 수 있지만 타입이 맞지 않으므로 `&` 없이 쓴다.

### 2.9 중첩 구조체와 공용체의 메모리 배치

2.4절의 중첩 구조체는 안쪽 구조체 전체가 바깥 구조체의 한 멤버로 그대로 들어간다. 2.8절의 `struct student`를 `offsetof`로 재면 다음과 같다. `offsetof`의 두 번째 인수에는 `birthday.year`처럼 중첩 멤버도 쓸 수 있다.

```c
printf("student: size %zu, name %zu, score %zu, birthday %zu\n", sizeof(struct student),
       offsetof(struct student, name), offsetof(struct student, score),
       offsetof(struct student, birthday));
printf("birthday.year %zu, birthday.day %zu, sizeof(struct date) %zu\n",
       offsetof(struct student, birthday.year), offsetof(struct student, birthday.day),
       sizeof(struct date));
printf("value: size %zu, i %zu, d %zu, c %zu\n", sizeof(union value),
       offsetof(union value, i), offsetof(union value, d), offsetof(union value, c));
```

```text
student: size 36, name 0, score 20, birthday 24
birthday.year 24, birthday.day 32, sizeof(struct date) 12
value: size 8, i 0, d 0, c 0
```

```text
struct student (36바이트)
        0                   20         24         28         32         36   ← 오프셋
      ┌───────────────────┬──────────┬──────────┬──────────┬──────────┐
      │ name[20]          │ score    │ year     │ month    │ day      │
      └───────────────────┴──────────┴──────────┴──────────┴──────────┘
                                     └──────── birthday (12B) ────────┘
```

*그림 8. 중첩 구조체 struct student의 멤버 오프셋*

`name`은 20바이트이고 20은 4의 배수이므로 `score`는 패딩 없이 오프셋 20에 놓인다. `birthday`는 그 뒤 오프셋 24부터 `struct date`의 12바이트를 차지하며, 그 안의 `year`, `month`, `day`는 24, 28, 32에 있다. 20 + 4 + 12 = 36이므로 이 구조체에는 패딩이 없다. 같은 방법으로 공용체 `union value { int i; double d; char c[4]; }`를 재면 세 멤버의 오프셋이 모두 0이고, 크기는 가장 큰 멤버인 `double`의 8바이트이다. 구조체는 멤버를 차례로 늘어놓고, 공용체는 모든 멤버를 같은 시작 주소에 겹쳐 놓는다는 차이가 숫자로 드러난다.

---

<br>

## 3. 관련 데이터 타입

### 3.1 `enum`

**열거형(enumeration)** 은 이름이 붙은 **정수 상수**의 집합을 정의한다. 정수형 변수가 특정 값들 중 하나를 가질 때 그 값들을 열거 상수로 정의하며, 열거체도 일종의 사용자 정의형이다.

```c
enum color { RED, GREEN, BLUE };
```

기본적으로 값은 **0**부터 시작하여 1씩 증가한다.

| 이름 | 기본값 |
|:----|:------|
| `RED` | `0` |
| `GREEN` | `1` |
| `BLUE` | `2` |

*표 3. 열거 상수의 기본값*

**사용자 지정 값**을 부여할 수 있다.

```c
enum color { RED = 1, GREEN = 5, BLUE = 10 };
```

일부 값만 지정하면 이후 값은 마지막 지정 값에서 1씩 커진다.

```c
enum level { LOW = 1, MEDIUM, HIGH };
// LOW = 1, MEDIUM = 2, HIGH = 3
```

C 컴파일러는 열거체를 `int`형으로 처리하고 열거 상수를 정수형 상수로 정의한다. 그래서 열거체 변수의 값을 `%d`로 출력하면 정수가 출력되고, 열거 상수를 `switch` 문의 `case`에 쓸 수 있다. 열거체도 구조체처럼 `enum 태그명`으로 사용해야 하며, 태그명을 생략하고 열거 상수만 정의할 수도 있다.

**사용 예:**

```c
enum color c = RED;

switch (c) {
case RED:
    printf("빨강\n");
    break;
case GREEN:
    printf("초록\n");
    break;
case BLUE:
    printf("파랑\n");
    break;
}
```

> **참고:** **팁.** 관련된 상수에는 `#define` 대신 `enum`을 사용한다. 매크로 상수는 전처리기가 값으로 바꿔 버리므로 컴파일러와 디버거가 이름을 알지 못하지만, 열거 상수는 컴파일러가 다루는 이름이다. C의 열거 상수는 `int` 상수이므로 타입 검사가 엄격하지는 않지만, 관련된 상수를 한곳에 묶어 의미를 드러내고, 디버거가 값 대신 이름을 보여 주며, gcc와 clang은 `switch` 문에서 처리하지 않은 열거 상수를 경고할 수 있다(`-Wswitch`).

### 3.2 `union`

**공용체(union)** 는 구조체와 비슷하게 생겼지만, 모든 멤버가 **메모리를 공유**한다. 공용체의 멤버들은 모두 같은 주소에 할당되므로 한 멤버의 값을 바꾸면 다른 멤버의 값도 함께 바뀐다. 한 번에 **하나의 멤버만** 의미 있는 값을 가지며, 공용체의 크기는 **가장 큰 멤버**를 담을 수 있는 크기이다.

```c
union data {
    int i;
    float f;
    char c;
};

printf("크기: %zu\n", sizeof(union data));  // 4 (int 또는 float의 크기)
```

```text
union data d;

┌──────────────────┐
│    i (4바이트)     │  ← 세 멤버 모두
│    f (4바이트)     │    같은 메모리
│    c (1바이트)     │    위치를 공유
└──────────────────┘
sizeof(union data) = 4  (가장 큰 멤버)
```

*그림 9. 세 멤버가 같은 메모리를 공유하는 공용체 변수 d*

공용체의 크기는 대부분 가장 큰 멤버의 크기와 같지만, 정렬 때문에 그보다 커질 수 있다. 예를 들어 `union { char s[5]; int i; }`는 가장 큰 멤버가 5바이트이지만 `int`의 정렬에 맞추어 크기가 8이다. 공용체를 초기화할 때는 `{}` 안에 첫 번째 멤버의 초기값만 지정한다(`union data d = {42};`는 `d.i`를 초기화한다). 멤버에 접근할 때는 구조체처럼 `.`를, 공용체 포인터로 접근할 때는 `->`를 사용한다.

```c
union data d;
d.i = 42;
printf("i = %d\n", d.i);    // 42

d.f = 3.14;
printf("f = %.2f\n", d.f);  // 3.14
printf("i = %d\n", d.i);    // 쓰레기 값: d.f에 의해 덮어씌워짐!
```

마지막 줄은 의미 없는 값을 출력하지만, 무작위 값은 아니다. `d.f`에 저장된 `3.14f`의 IEEE 754 단정도 비트 패턴 `0x4048F5C3`을 `int`로 다시 해석한 값 `1078523331`이 출력된다(`int`와 `float`가 모두 4바이트인 일반적인 시스템). C 표준은 마지막으로 쓴 멤버가 아닌 멤버를 읽으면 그 바이트를 새 데이터 타입으로 다시 해석한다고 정한다.

> **주의:** 공용체의 한 멤버에 값을 쓰면 다른 모든 멤버가 덮어씌워진다. 의미 있는 값을 갖는 것은 **마지막으로 쓴 멤버**뿐이다.

### 3.3 `typedef`

`typedef`는 기존 데이터 타입에 대한 **별칭(alias)** 을 생성한다.

```c
typedef unsigned int uint;
typedef int BOOL;

uint count = 100;     // unsigned int count = 100;과 동일
BOOL flag = 1;        // int flag = 1;과 동일
```

**가장 일반적인 용도는 구조체 선언의 간소화이다.** 구조체를 정의할 때 `typedef`로 `struct 태그명` 대신 쓸 이름을 만들어 두면 사용하기 편하다.

```c
typedef struct point {
    int x;
    int y;
} Point;

Point p1 = {10, 20};         // "struct point"라고 쓸 필요 없음
Point p2 = {30, 40};
```

이는 다음과 동일하다.

```c
struct point {
    int x;
    int y;
};
typedef struct point Point;
```

`typedef` 없이는 항상 `struct point`라고 써야 한다. `typedef`를 정의한 다음에도 기존 데이터 타입 이름 `struct point`를 그대로 쓸 수 있다.

```c
struct point p1 = {10, 20};   // 장황함
Point p1 = {10, 20};          // 간결함: typedef 사용
```

> **핵심:** `typedef`는 새로운 데이터 타입을 만드는 것이 **아니라**, 기존 데이터 타입에 새 **이름**을 부여하는 것이다. `Point`와 `struct point`는 같은 데이터 타입이다.

### 3.4 `typedef`의 여러 가지 용도

`typedef`는 구조체 외의 타입에도 쓸 수 있다. 첫째, 의미를 드러내는 이름을 붙인다. `typedef unsigned char BYTE;`로 정의한 `BYTE`는 값이 아니라 바이트 단위의 데이터임을 이름으로 보여 준다. 둘째, 복잡한 타입을 짧게 쓴다. 구조체 포인터에 이름을 붙이면 `Student *` 대신 `StudentPtr`로 쓸 수 있다. 셋째, 플랫폼에 따라 달라지는 타입을 감춘다. 표준 라이브러리의 `size_t`도 `typedef`로 정의된 이름이며, 그 실제 타입은 플랫폼마다 다르다. 타입이 바뀌어야 할 때 `typedef` 한 줄만 고치면 되므로 이식성이 높아진다.

```c
typedef unsigned char BYTE;
typedef struct student {
    char name[20];
    int score;
} Student;
typedef Student *StudentPtr;

int main(void)
{
    BYTE b = 255;
    Student s = { "Kim", 91 };
    StudentPtr p = &s;

    b++;
    printf("b = %u, %s %d\n", b, p->name, p->score);
    printf("%zu %zu\n", sizeof(BYTE), sizeof(size_t));
    return 0;
}
```

```text
b = 0, Kim 91
1 8
```

`BYTE`는 `unsigned char`의 다른 이름일 뿐이므로 255에 1을 더하면 3장의 부호 없는 정수 순환에 따라 0이 된다. 이 환경에서 `size_t`는 8바이트이다. 다만 포인터 타입에 `typedef`를 쓰면 선언에서 `*`가 보이지 않아 그 변수가 포인터라는 사실을 놓치기 쉬우므로, 구조체 이름처럼 자주 쓰고 뜻이 분명한 경우에만 쓰는 것이 좋다.

### 3.5 열거체와 `switch`로 방향 처리하기

열거체는 정해진 몇 가지 값 가운데 하나를 갖는 데이터를 이름으로 표현할 때 쓴다. 다음 코드는 상하좌우 방향을 `enum direction`으로 정의하고, `switch`로 방향에 따라 점의 좌표를 한 칸 옮긴다.

```c
enum direction { UP, DOWN, LEFT, RIGHT };

struct point {
    int x, y;
};

void move(struct point *p, enum direction d)
{
    switch (d) {
    case UP:
        p->y++;
        break;
    case DOWN:
        p->y--;
        break;
    case LEFT:
        p->x--;
        break;
    case RIGHT:
        p->x++;
        break;
    }
}

int main(void)
{
    enum direction path[5] = { UP, UP, RIGHT, DOWN, RIGHT };
    struct point pos = { 0, 0 };
    int i;

    for (i = 0; i < 5; i++) {
        move(&pos, path[i]);
        printf("step %d: dir = %d, pos = (%d, %d)\n", i + 1, path[i], pos.x, pos.y);
    }
    return 0;
}
```

```text
step 1: dir = 0, pos = (0, 1)
step 2: dir = 0, pos = (0, 2)
step 3: dir = 3, pos = (1, 2)
step 4: dir = 1, pos = (1, 1)
step 5: dir = 3, pos = (2, 1)
```

열거 상수는 차례로 `UP` = 0, `DOWN` = 1, `LEFT` = 2, `RIGHT` = 3이므로 `%d`로 출력하면 이 정수가 나온다. 이동 경로를 따라가면 (0, 0)에서 위로 두 번 가서 (0, 2), 오른쪽으로 (1, 2), 아래로 (1, 1), 오른쪽으로 (2, 1)에 이른다. `switch`의 `case`에 숫자 대신 열거 상수를 쓰면 코드가 무엇을 비교하는지 드러나고, 컴파일러가 빠진 경우를 찾아 준다. `LEFT`와 `RIGHT`의 `case`를 지운 `switch`를 `-Wall`로 컴파일하면 Clang은 `enumeration values 'LEFT' and 'RIGHT' not handled in switch` 경고를 낸다. 이 경고는 `default`가 있으면 나오지 않으므로, 모든 열거 값을 처리해야 하는 `switch`에서는 `default` 대신 모든 `case`를 쓰는 편이 실수를 찾기 쉽다.

### 3.6 구조체와 관련 타입의 흔한 실수

구조체를 처음 쓸 때 자주 나오는 오류는 `.`과 `->`의 혼동, `struct` 키워드의 누락이다. 다음 코드의 세 줄은 각각 Clang에서 오류가 된다.

```c
struct point { int x, y; };

struct point pt = { 1, 2 }, *p = &pt;
int a = p.x;            // 포인터에 .을 씀
int b = pt->y;          // 구조체 변수에 ->를 씀
point q;                // struct 없이 태그 이름만 씀
```

```text
error: member reference type 'struct point *' is a pointer; did you mean to use '->'?
error: member reference type 'struct point' is not a pointer; did you mean to use '.'?
error: must use 'struct' tag to refer to type 'point'
```

| 실수 | 바로잡는 방법 |
|:-----|:-----|
| 포인터에 `.`을 씀 | `p->x` 또는 `(*p).x` |
| 구조체 변수에 `->`를 씀 | `pt.y` |
| `struct` 없이 태그 이름만 씀 | `struct point q;`로 쓰거나 3.3절의 `typedef`로 별칭을 정의 |
| 구조체 정의 끝의 세미콜론 누락 | `};`로 끝냄 (1.2절) |
| 문자 배열 멤버에 `=`로 문자열 대입 | `strcpy(s.name, "Kim");` (1.6절) |
| 구조체를 `==`로 비교 | 멤버별로 비교 (1.7절) |
| 공용체에서 마지막으로 쓰지 않은 멤버를 읽음 | 어느 멤버를 썼는지 별도의 변수로 기록 (3.2절) |

*표 4. 구조체와 관련 타입의 흔한 실수*

처음 두 오류에서 Clang은 맞는 연산자를 제안까지 해 준다. 세 번째 오류는 C에서 구조체의 태그 이름이 타입 이름과 다른 이름 공간에 있기 때문에 생긴다. `struct point`가 하나의 타입 이름이며, `point`만으로 쓰려면 `typedef struct point point;`처럼 같은 이름의 별칭을 따로 정의해야 한다.

`.`과 `->`의 선택은 왼쪽에 오는 것의 타입으로 정해진다. 구조체 변수이면 `.`, 구조체 포인터이면 `->`이다. 함수의 매개변수가 구조체 포인터이면 함수 안에서는 모두 `->`를 쓰고, `main`의 구조체 변수에서는 `.`을 쓰므로, 같은 멤버라도 코드의 위치에 따라 연산자가 바뀐다. 헷갈릴 때는 왼쪽에 오는 식의 타입을 먼저 확인하고, 포인터이면 `->`, 구조체이면 `.`을 쓴다. 배열 원소 `pts[i]`는 구조체이므로 `.`을, `pts + i`는 주소이므로 `->`를 쓴다.

### 3.7 종합 예: 성적 처리 프로그램

이 장의 내용을 한 프로그램으로 묶는다. `typedef`로 정의한 `Student` 구조체의 배열에 세 학생의 국어, 영어, 수학 점수를 저장하고, 총점을 구하는 함수와 총점이 가장 높은 학생을 찾는 함수를 구조체 포인터로 작성한다.

```c
typedef struct {
    char name[20];
    int kor, eng, math;
} Student;

int total(const Student *s)
{
    return s->kor + s->eng + s->math;
}

const Student *find_best(const Student list[], int n)
{
    const Student *best = &list[0];
    int i;

    for (i = 1; i < n; i++)
        if (total(&list[i]) > total(best))
            best = &list[i];
    return best;
}

int main(void)
{
    Student list[3] = {
        { "Kim", 90, 80, 70 }, { "Lee", 85, 95, 90 }, { "Park", 70, 75, 100 }
    };
    const Student *best;
    int i;

    for (i = 0; i < 3; i++)
        printf("%-5s total = %3d, average = %.2f\n", list[i].name,
               total(&list[i]), total(&list[i]) / 3.0);
    best = find_best(list, 3);
    printf("best: %s (%d)\n", best->name, total(best));
    return 0;
}
```

```text
Kim   total = 240, average = 80.00
Lee   total = 270, average = 90.00
Park  total = 245, average = 81.67
best: Lee (270)
```

- **타입의 정의:** 태그 없는 구조체에 `typedef`로 `Student`라는 이름을 붙였으므로, 이후에는 `struct` 없이 `Student`만 쓴다(3.3절).
- **`total`:** 구조체를 바꾸지 않으므로 `const Student *`로 받고 `->`로 세 멤버를 더한다. 구조체 전체를 복사하지 않고 주소 8바이트만 넘긴다.
- **`find_best`:** 지금까지의 최고 학생을 가리키는 포인터 `best`를 첫 원소로 시작하고, 총점이 더 큰 원소를 만나면 그 원소의 주소로 바꾼다. 반환하는 주소는 호출한 쪽의 배열 원소이므로 함수가 끝나도 유효하다(8장 3.5절). 총점은 240, 270, 245이므로 `best`는 `i`가 1일 때 `&list[1]`로 바뀌고 `i`가 2일 때는 바뀌지 않는다.
- **`main`:** `%-5s`는 이름을 5칸에 왼쪽 정렬하여 열을 맞춘다. 평균은 `3.0`으로 나누어 실수 나눗셈이 되게 하며, Park의 평균은 245 / 3 = 81.666...이 `%.2f`로 81.67이 된다.

### 3.8 열거 상수의 이름 출력과 값의 검사

열거 상수는 컴파일 뒤에 정수로만 남으므로, `printf`로는 `UP` 같은 이름을 출력할 수 없다. 이름이 필요하면 열거 상수의 값을 인덱스로 하는 문자열 포인터 배열(9장 7.2절)을 둔다. 목록의 끝에 `DIR_COUNT`를 두면 그 값이 앞의 상수 개수 4와 같아져서 배열의 크기와 반복의 끝으로 쓸 수 있다.

```c
enum direction { UP, DOWN, LEFT, RIGHT, DIR_COUNT };

const char *names[DIR_COUNT] = { "UP", "DOWN", "LEFT", "RIGHT" };

const char *dir_name(enum direction d)
{
    if (d < UP || d >= DIR_COUNT)       // 범위를 벗어난 값을 걸러 낸다
        return "?";
    return names[d];
}

int main(void)
{
    enum direction d;
    enum direction bad = 7;

    for (d = UP; d < DIR_COUNT; d++)
        printf("%d %s\n", d, dir_name(d));
    printf("%d %s\n", bad, dir_name(bad));
    return 0;
}
```

```text
0 UP
1 DOWN
2 LEFT
3 RIGHT
7 ?
```

열거체 변수에는 정해진 상수가 아닌 정수도 저장된다. `enum direction bad = 7;`은 Clang에서 `-Wall -Wextra`로도 경고 없이 컴파일되었다. 열거체는 정수형으로 처리될 뿐 값의 범위를 검사하지 않으므로, 열거 상수를 배열의 인덱스로 쓰는 함수는 `dir_name`처럼 범위를 먼저 확인해야 한다. 검사가 없으면 `names[7]`은 원소가 4개인 배열의 범위를 넘는 접근이 된다. `d++`처럼 열거체 변수를 증가시켜 상수를 차례로 훑는 것은 상수가 0부터 1씩 커질 때만 맞는 방법이다.

---

<br>

## 개념 적용

**T/F 점검:**

| 문장 | 판단과 근거 |
|:-----|:-----|
| 구조체의 크기는 항상 멤버 크기의 합과 같다. | **F.** 정렬을 위한 패딩 때문에 합보다 클 수 있다. |
| 같은 타입의 구조체는 `=`로 대입할 수 있고, 이때 배열 멤버도 복사된다. | **T.** 구조체 대입은 모든 멤버를 그대로 복사한다. |
| 구조체는 `==`로 비교할 수 있다. | **F.** 구조체에는 `==`를 쓸 수 없으므로 멤버별로 비교한다. |
| 구조체 포인터 `p`에 대해 `p->x`와 `(*p).x`는 같다. | **T.** `->`는 역참조와 멤버 접근을 한 번에 하는 연산자이다. |
| `*p.x`는 `(*p).x`와 같다. | **F.** `.`이 `*`보다 먼저 결합하여 `*(p.x)`가 되므로, 포인터 `p`에 쓰면 컴파일 오류이다. |
| 함수가 지역 구조체 변수를 반환하면 댕글링 포인터 문제가 생긴다. | **F.** 반환되는 것은 주소가 아니라 멤버를 복사한 값이므로 안전하다. |
| 비트 필드 멤버의 주소는 `&`로 구할 수 있다. | **F.** 비트 필드 멤버는 바이트 단위의 주소를 갖지 않으므로 `&`를 쓸 수 없다. |
| `typedef`는 새로운 데이터 타입을 만든다. | **F.** 기존 데이터 타입에 새 이름을 붙일 뿐이다. |
| `p->x`는 `(*p).x`의 줄임이며, `p`가 구조체 배열의 원소를 가리키면 `p + 1`은 다음 원소를 가리킨다. | **T.** 포인터 연산은 구조체 하나의 크기 단위로 이동한다. |
| 구조체의 크기는 멤버를 선언하는 순서와 관계없다. | **F.** 정렬을 위한 패딩의 양이 순서에 따라 달라지므로 크기도 달라질 수 있다. |
| `scanf("%s", s.name)`의 `s.name`에는 `&`를 붙여야 한다. | **F.** 문자 배열 멤버의 이름은 이미 첫 원소의 주소이다. |
| 공용체의 모든 멤버는 오프셋이 0이다. | **T.** 모든 멤버가 같은 시작 주소를 공유한다. |
| `enum direction d = 7;`처럼 정의되지 않은 값을 열거체 변수에 저장하면 컴파일 오류가 난다. | **F.** 열거체는 정수형으로 처리되어 값의 범위를 검사하지 않으므로 컴파일된다. |
| `++p->x`는 포인터 `p`를 다음 원소로 옮긴다. | **F.** `->`가 먼저 결합하므로 멤버 `x`가 증가하며, 포인터를 옮기려면 `(++p)->x`로 쓴다. |
| 큰 구조체를 값으로 넘기면 구조체 전체가 복사된다. | **T.** `struct content`는 호출마다 64바이트가 복사되고, 포인터로 넘기면 8바이트만 복사된다. |

---

<br>

## 요약

| 개념 | 핵심 요약 |
|:----|:---------|
| 구조체 | **서로 다른 데이터 타입**의 변수를 하나의 이름으로 묶는 사용자 정의 데이터 타입이다. |
| `struct` vs 배열 | 배열은 같은 데이터 타입을, 구조체는 다른 데이터 타입을 묶는다. |
| 정의 | `struct 태그명 { 멤버들 };`으로 정의하며, `}` 뒤의 세미콜론이 필수이고 보통 파일 범위에 정의한다. |
| 태그명 | 완전한 데이터 타입 이름은 `struct 태그명`이며, `struct` 없이 태그명만 쓰면 컴파일 오류이다. |
| 크기 | 패딩과 정렬 때문에 `sizeof(struct 태그명)`은 멤버 크기의 합 이상이다. |
| 선언 | `struct 태그명 var1, var2;`로 선언하며, 멤버는 선언 순서대로 할당된다. |
| 익명 구조체 | 태그명이 없어 나중에 같은 데이터 타입을 다시 사용할 수 없다. |
| 초기화 | `struct 태그명 v = {값1, 값2, ...};`처럼 멤버 순서대로 초기화하며, 부분 초기화하면 나머지는 0이 된다. |
| 복사 초기화 | `struct 태그명 c2 = c1;`은 모든 멤버를 복사하여 초기화한다. |
| 멤버 접근 | `c1.rate`, `c1.title`처럼 점 연산자로 접근하며, 구조체 변수를 통해서만 접근할 수 있다. |
| 대입 | `c3 = c1`은 모든 멤버를 복사하지만, 선언 이후에는 `{}`를 쓸 수 없고 개별 배열 멤버에는 `strcpy`가 필요하다. |
| 비교 | 구조체에는 `==`와 `!=`를 쓸 수 없으므로 멤버별로 비교하고, 문자열 멤버는 `strcmp`로 비교한다. |
| 구조체 배열 | `struct 태그명 arr[N];`으로 선언하고 `arr[i].멤버`로 접근하며, 검색과 정렬에 활용한다. |
| 구조체 포인터 | `struct 태그명 *p = &c1;`로 선언하고 `p->멤버` 또는 `(*p).멤버`로 접근한다. |
| 화살표 연산자 | `p->멤버`는 `(*p).멤버`와 같으며, `(*p)`의 괄호는 필수이다. |
| 값 전달 | 함수가 복사본을 받으므로 원본이 변경되지 않지만, 큰 구조체는 복사 비용이 크다. |
| 포인터 전달 | 함수가 원본을 수정할 수 있으며, 읽기 전용이면 `const` 포인터를 사용한다. |
| 중첩 구조체 | 구조체 안에 다른 구조체를 멤버로 두며, `외부.내부.필드`로 접근한다. |
| `enum` | 이름이 붙은 `int` 상수의 집합이며, 기본값은 0부터 시작하여 1씩 증가한다. |
| `union` | 모든 멤버가 같은 메모리를 공유하여 크기는 가장 큰 멤버를 담을 수 있는 크기이고, 의미 있는 값은 마지막으로 쓴 멤버뿐이다. |
| `typedef` | 기존 데이터 타입에 별칭을 부여하며, 구조체와 함께 쓰면 `struct` 키워드를 생략할 수 있다. |
| 구조체 반환 | 구조체는 대입할 수 있으므로 반환형으로 쓸 수 있고, 반환되는 것은 멤버의 복사본이라 지역 변수를 반환해도 안전하다. |
| 비트 필드 | `unsigned int day : 5;`처럼 멤버의 비트 수를 지정하여 메모리를 줄이며, 범위를 넘는 값은 잘리고 멤버의 주소는 구할 수 없다. |
| `typedef`의 용도 | 의미 있는 이름 부여, 복잡한 타입의 축약, 플랫폼에 따라 다른 타입의 은닉(`size_t`)에 쓴다. |
| `offsetof`와 패딩 | `offsetof`로 멤버의 위치를 확인하며, 큰 멤버를 앞에 두고 작은 멤버를 모으면 패딩이 줄어든다. |
| 구조체 포인터의 연산 | `p + 1`은 구조체 하나만큼 이동하고, `pts[i].x`, `(pts + i)->x`, `(*(pts + i)).x`는 같다. |
| 구조체 멤버의 입력 | `int` 멤버는 `&s.score`로, 문자 배열 멤버는 `s.name`으로 넘기며, `&s.birthday.year`는 중첩 멤버의 주소이다. |
| 열거체와 `switch` | 열거 상수를 `case`에 쓰면 의미가 드러나고, `default`가 없을 때 처리하지 않은 값을 컴파일러가 경고한다. |
| 구조체의 흔한 실수 | 포인터에는 `->`, 변수에는 `.`을 쓰고, 태그 이름은 `struct`와 함께 쓴다. |
| 일부 멤버의 초기화 | 초기값이 모자라면 나머지 멤버는 0이 되며, `{ 0 }`은 구조체 전체를 0으로 시작하는 관용구이다. |
| 구조체 포인터를 받는 함수 | 읽기만 하는 함수는 `const` 구조체 포인터로 받아 복사를 피하고, 배열 원소의 주소를 반환할 수 있다. |
| 중첩 구조체와 공용체의 배치 | 중첩 구조체는 안쪽 구조체 전체가 한 멤버로 들어가고, 공용체는 모든 멤버의 오프셋이 0이다. |
| 열거 상수의 이름 | 이름은 열거 상수를 인덱스로 하는 문자열 배열로 출력하며, 열거체 변수는 범위를 검사하지 않으므로 인덱스로 쓰기 전에 확인한다. |

---

<br>

## 점검 문제

1. **패딩:** 일반적인 64비트 시스템에서 `struct A { char c; int n; double d; };`와 `struct B { char c; double d; int n; };`의 `sizeof`는 각각 얼마인가? 이유를 쓰라.

   <details>
   <summary>정답</summary>

   `struct A`는 16, `struct B`는 24이다. `A`는 `c`(1바이트) 뒤에 `int`를 4의 배수 주소에 맞추려고 3바이트를 채우고, `n`이 끝난 오프셋 8에 `d`가 놓여 1 + 3 + 4 + 8 = 16이다. `B`는 `d`를 8의 배수 주소에 맞추려고 `c` 뒤에 7바이트를 채우고, `n` 뒤에는 구조체 전체 크기를 가장 큰 정렬 단위 8의 배수로 맞추려고 4바이트를 채워 1 + 7 + 8 + 4 + 4 = 24가 된다.

   </details>

2. **화살표 연산자:** `struct content c1; struct content *p = &c1;`일 때 `*p.price`가 오류인 이유를 쓰고, `c1.price`에 접근하는 올바른 표현 두 가지를 쓰라.

   <details>
   <summary>정답</summary>

   `.`이 `*`보다 우선순위가 높으므로 `*p.price`는 `*(p.price)`로 해석되는데, `p`는 구조체가 아니라 포인터이므로 `p.price`가 성립하지 않는다. 올바른 표현은 `(*p).price`와 `p->price`이다.

   </details>

3. **공용체:** `union data { int i; float f; char c; } d;`에서 `sizeof(union data)`는 얼마이며, `d.i = 42; d.f = 3.14;` 다음에 `d.i`를 읽으면 왜 42가 아닌가?

   <details>
   <summary>정답</summary>

   크기는 가장 큰 멤버인 `int`와 `float`의 크기인 4바이트이다. 세 멤버가 같은 메모리를 공유하므로 `d.f`에 쓰는 순간 `d.i`가 차지하던 4바이트가 `3.14f`의 비트 패턴으로 덮어씌워진다. 따라서 `d.i`는 그 비트 패턴(`0x4048F5C3`)을 정수로 해석한 1078523331이 되며, 의미 있는 값을 갖는 멤버는 마지막으로 쓴 `d.f`뿐이다.

   </details>

4. **열거 상수의 값:** `enum level { LOW = 1, MEDIUM, HIGH = 10, MAX };`에서 네 열거 상수의 값을 쓰라.

   <details>
   <summary>정답</summary>

   `LOW = 1`, `MEDIUM = 2`, `HIGH = 10`, `MAX = 11`이다. 값을 지정하지 않은 열거 상수는 바로 앞 열거 상수의 값보다 1 크다.

   </details>

5. **구조체 전달:** `price`가 11000인 `c1`에 대해 `void f(struct content c) { c.price *= 0.8; }`와 `void g(struct content *p) { p->price *= 0.8; }`를 각각 호출한 뒤 `c1.price`는 얼마인가? 구조체를 수정하지 않는 함수의 매개변수로는 어떤 형이 적합한가?

   <details>
   <summary>정답</summary>

   `f(c1)`은 복사본을 수정하므로 `c1.price`는 11000 그대로이고, `g(&c1)`은 원본을 수정하므로 11000 × 0.8 = 8800이 된다. 구조체를 수정하지 않는 함수는 복사 비용을 피하면서 변경을 막기 위해 `const struct content *p`처럼 `const` 구조체 포인터로 받는 것이 적합하다.

   </details>

6. **구조체 반환:** 2.5절의 `midpoint`에서 a가 (3, 9), b가 (8, 2)일 때 `midpoint(a, b)`가 반환하는 점은 무엇인가? 정수 나눗셈에 주의하라.

   <details>
   <summary>정답</summary>

   x는 (3 + 8) / 2 = 11 / 2 = 5, y는 (9 + 2) / 2 = 11 / 2 = 5이므로 (5, 5)이다. 정수 나눗셈이 소수 부분 0.5를 버린다. 정확한 중점 (5.5, 5.5)가 필요하면 멤버를 `double`로 선언한다.

   </details>

7. **비트 필드:** `struct flags { unsigned int a : 1; unsigned int b : 3; };`에서 `f.b = 9;`를 실행하면 `f.b`의 값은 얼마인가? 또 `f.a`가 가질 수 있는 값을 모두 쓰라.

   <details>
   <summary>정답</summary>

   9는 2진수 `1001`이고 3비트 멤버에는 하위 3비트 `001`만 남으므로 `f.b`는 1이다. 1비트 부호 없는 멤버 `f.a`는 0과 1만 가질 수 있다.

   </details>

8. **반환형의 선택:** 학생의 점수를 10점 올리는 함수와, 두 학생 중 점수가 높은 학생의 정보를 돌려주는 함수를 만들 때 각각 매개변수와 반환형을 어떻게 정하는 것이 알맞은가?

   <details>
   <summary>정답</summary>

   점수를 올리는 함수는 호출한 쪽의 구조체를 바꿔야 하므로 `void raise(struct student *s)`처럼 포인터 매개변수를 쓴다. 점수가 높은 학생을 돌려주는 함수는 입력을 바꾸지 않으므로 `const struct student *` 두 개를 받아 높은 쪽의 포인터를 반환하거나, 작은 구조체라면 `struct student`를 값으로 반환할 수 있다. 큰 구조체는 복사 비용 때문에 포인터 쪽이 효율적이다.

   </details>
