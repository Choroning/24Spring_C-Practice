# Chapter 10 — 구조체

> **최종 수정일:** 2026-03-16
>
> **교재 참조:** *Warming-Up C Programming 2판* — 10장

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
- [2. 구조체 활용](#2-구조체-활용)
  - [2.1 구조체 배열](#21-구조체-배열)
  - [2.2 구조체 포인터](#22-구조체-포인터)
  - [2.3 함수에 구조체 전달](#23-함수에-구조체-전달)
  - [2.4 중첩 구조체](#24-중첩-구조체)
- [3. 관련 자료형](#3-관련-자료형)
  - [3.1 `enum`](#31-enum)
  - [3.2 `union`](#32-union)
  - [3.3 `typedef`](#33-typedef)
- [요약](#요약)

---

<br>

## 1. 구조체 기초

### 1.1 구조체 개념

**배열**은 **같은** 자료형의 값을 여러 개 저장한다. **구조체**는 **서로 다른** 자료형의 변수를 하나의 이름으로 묶어 **사용자 정의 자료형**을 만든다.

```
배열 vs 구조체
├── 배열    : 같은 자료형 × N     → int scores[5];
└── 구조체  : 다른 자료형 × N     → struct student { char name[20]; int age; double gpa; };
```

| 특성 | 배열 | 구조체 |
|:----|:-----|:------|
| 요소 자료형 | 모두 동일 | 서로 다를 수 있음 |
| 접근 방식 | 인덱스 `a[i]` | 멤버 이름 `s.age` |
| 사용자 정의 | 아니오 (내장) | 예 (`struct`) |
| 용도 | 같은 자료형의 데이터 모음 | 서로 다른 자료형의 필드를 가진 레코드 |

구조체는 `struct` 키워드로 정의한다. 닫는 중괄호 `}` 뒤에 반드시 **세미콜론**을 붙여야 한다. 전역적으로 사용하려면 **함수 바깥**(파일 범위)에 정의한다.

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

- **태그명(tag name):** 구조체를 구별하는 이름. **완전한 자료형 이름**은 `struct 태그명`이며, `struct` 키워드를 반드시 함께 써야 한다.
- **멤버(member, 구성 변수):** 구조체 내부의 개별 변수.

```c
struct content {
    char title[50];    // 멤버 1
    int price;         // 멤버 2
    double rate;       // 멤버 3
};
```

> **경고:** `struct` 없이 태그명만 쓰면 **컴파일 오류**가 발생한다:
> ```c
> content c1;          // 컴파일 오류!
> struct content c1;   // 올바른 사용
> ```

**크기와 정렬:**

구조체의 크기는 멤버 크기의 합 **이상**이다. 컴파일러가 효율적인 메모리 접근을 위해 **패딩/정렬(padding/alignment)** 바이트를 삽입할 수 있기 때문이다.

```c
struct example {
    char c;      // 1바이트
    int n;       // 4바이트
    double d;    // 8바이트
};
// 합계 = 13바이트이지만, sizeof(struct example)은 16 또는 24가 될 수 있음

printf("크기: %zu\n", sizeof(struct example));  // 16 또는 24일 가능성
```

```
메모리 레이아웃 (패딩 포함 가능):
┌─────┬─────────┬──────────┬──────────────────┐
│  c  │ 패딩    │    n     │        d         │
│ 1B  │  3B     │   4B     │       8B         │
└─────┴─────────┴──────────┴──────────────────┘
sizeof(struct example) = 16  (13이 아님)
```

> **핵심:** `sizeof(struct 태그명)` >= 멤버 크기의 합. 컴파일러가 멤버 사이에 정렬을 위한 패딩 바이트를 삽입할 수 있다.

### 1.3 구조체 변수 선언

구조체를 정의한 후, 해당 자료형의 변수를 선언할 수 있다:

```c
struct content c1, c2, c3;   // 변수 3개 선언
```

구조체 **정의와 동시에** 변수를 선언할 수도 있다:

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

> **경고:** 익명 구조체는 태그명이 없으므로, 나중에 같은 자료형의 변수를 **다시 선언할 수 없다**.

**메모리 할당:** 멤버는 **선언 순서대로** 연속된 메모리에 할당된다.

```
struct content c1;

┌────────────────────────┬───────────┬───────────┐
│    c1.title (50바이트) │ c1.price  │  c1.rate  │
│                        │  (4바이트)│ (8바이트) │
└────────────────────────┴───────────┴───────────┘
            (멤버 사이에 패딩이 포함될 수 있음)
```

### 1.4 구조체 초기화

**초기화 리스트** `{}`를 사용하여 **멤버 선언 순서**에 맞게 초기화한다:

```c
struct content c1 = {"Avengers", 11000, 8.8};
```

| 초기화 | `title` | `price` | `rate` |
|:------|:--------|:--------|:-------|
| `{"Avengers", 11000, 8.8}` | `"Avengers"` | `11000` | `8.8` |

**부분 초기화** — 나머지 멤버는 **0**으로 채워진다:

```c
struct content c2 = {"Inception"};
// c2.title = "Inception", c2.price = 0, c2.rate = 0.0
```

**초기값이 너무 많으면** — 컴파일 오류:

```c
struct content c3 = {"Matrix", 9000, 9.1, 100};  // 컴파일 오류!
```

**다른 구조체 변수로 초기화:**

```c
struct content c1 = {"Avengers", 11000, 8.8};
struct content c2 = c1;   // c1의 모든 멤버를 c2로 복사
```

### 1.5 멤버 접근

**점 연산자**(`.`)를 사용하여 구조체 변수를 통해 멤버에 접근한다:

```c
struct content c1 = {"Avengers", 11000, 8.8};

c1.rate = 8.9;                      // 멤버 수정
c1.price *= 0.8;                    // 멤버에 복합 대입
strcat(c1.title, ": Endgame");      // 멤버에 문자열 연산
printf("제목: %s\n", c1.title);      // 멤버 읽기
```

> **핵심:** 멤버는 구조체 변수를 통해서**만** 접근할 수 있다. 멤버 이름을 단독으로 사용할 수 없다 — `title`만으로는 `c1.title`을 가리키지 않는다.

```c
// title = "Test";       // 컴파일 오류 — title은 독립 변수가 아님
c1.title;                // 올바른 사용 — 구조체 변수를 통한 접근
```

### 1.6 구조체 대입

선언 이후, 같은 자료형의 구조체를 다른 구조체에 **대입**할 수 있다. 이때 **모든 멤버가 1:1로 복사**된다:

```c
struct content c1 = {"Avengers", 11000, 8.8};
struct content c3;

c3 = c1;   // title, price, rate 모두 c1에서 c3으로 복사
```

**제한 사항:**

선언 이후에는 초기화 리스트 `{}`를 사용할 수 **없다** (선언 시점에서만 가능):

```c
struct content c3;
c3 = {"Matrix", 9000, 9.1};    // 컴파일 오류!
```

배열 멤버는 직접 대입할 수 **없다** — `strcpy`를 사용해야 한다:

```c
struct content c1 = {"Avengers", 11000, 8.8};
struct content c3;

// c3.title = c1.title;         // 컴파일 오류 — 배열은 대입 불가!
strcpy(c3.title, c1.title);     // 올바른 방법 — 문자열에는 strcpy 사용
c3.price = c1.price;            // OK — 배열이 아닌 멤버는 대입 가능
c3.rate = c1.rate;              // OK
```

> **팁:** 구조체 전체 대입 `c3 = c1`은 정상 작동하며 배열 멤버도 올바르게 복사된다(멤버별 바이트 복사). 제한은 `c3.title = c1.title`처럼 **개별** 배열 멤버를 대입하려 할 때만 적용된다.

### 1.7 구조체 비교

구조체에 `==`나 `!=`를 직접 사용하여 비교할 수 **없다**:

```c
struct content c1 = {"Avengers", 11000, 8.8};
struct content c2 = c1;

// if (c1 == c2) { ... }     // 컴파일 오류!
```

대신 **멤버별로 비교**해야 한다. 문자열 멤버에는 `strcmp`를 사용한다:

```c
if (strcmp(c1.title, c2.title) == 0 &&
    c1.price == c2.price &&
    c1.rate == c2.rate) {
    printf("c1과 c2는 같다\n");
}
```

> **경고:** C에서 구조체를 `==`로 비교하면 컴파일 오류가 발생한다. 반드시 각 멤버를 **개별적으로** 비교해야 한다. 문자열(char 배열) 멤버는 `strcmp`를 사용하고, `==`로 비교하면 안 된다.

---

<br>

## 2. 구조체 활용

### 2.1 구조체 배열

**구조체 배열**은 같은 구조체 자료형의 레코드를 여러 개 저장한다:

```c
struct content movies[10];
```

배열 인덱스와 점 연산자로 멤버에 접근한다:

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

**구조체 배열 정렬 (평점 내림차순 — 선택 정렬):**

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

> **팁:** 구조체 변수 두 개를 교환하려면 같은 구조체 자료형의 임시 변수를 사용한다. 구조체 전체 대입으로 모든 멤버가 복사된다.

### 2.2 구조체 포인터

**구조체 포인터**는 구조체 변수의 주소를 저장한다:

```c
struct content c1 = {"Avengers", 11000, 8.8};
struct content *p = &c1;
```

포인터를 통해 멤버에 접근할 때는 **화살표 연산자**(`->`)를 사용한다:

```c
printf("제목: %s\n", p->title);     // 화살표 연산자
printf("가격: %d\n", p->price);
printf("평점: %.1f\n", p->rate);
```

화살표 연산자 `->`는 역참조 `(*p).멤버`와 동일하다:

```c
p->title      // (*p).title과 동일
p->price      // (*p).price과 동일
p->rate       // (*p).rate과 동일
```

> **경고:** `(*p).title`에서 괄호가 필수이다. 점 `.`이 `*`보다 우선순위가 높기 때문에, 괄호 없이 `*p.title`이라 쓰면 `*(p.title)`로 해석되어 `p`가 구조체 포인터일 때 오류가 발생한다.

```
 p ──────► ┌────────────────────┐
           │ c1.title = "Avengers"│
           │ c1.price = 11000     │
           │ c1.rate  = 8.8       │
           └────────────────────┘

p->title   ≡  (*p).title   ≡  c1.title
```

### 2.3 함수에 구조체 전달

**값에 의한 전달(pass by value)** — 함수가 **복사본**을 받는다:

```c
void display(struct content c) {
    printf("%s %d %.1f\n", c.title, c.price, c.rate);
    c.price = 0;   // 복사본만 수정 — 원본은 변하지 않음
}

int main() {
    struct content c1 = {"Avengers", 11000, 8.8};
    display(c1);    // 복사본 전달
    printf("가격: %d\n", c1.price);  // 여전히 11000
    return 0;
}
```

**포인터에 의한 전달(pass by pointer)** — 함수가 **원본을 수정**할 수 있다:

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

**구조체 배열 전달** — 배열은 항상 포인터로 변환된다:

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

### 2.4 중첩 구조체

구조체가 다른 구조체를 멤버로 포함할 수 있다:

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

**중첩 멤버 접근** — 점 연산자를 연쇄적으로 사용:

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

```
struct student s1

┌──────────────────────────────────────────────┐
│ name = "Kim"                                 │
│ id = 2024001                                 │
│ birthday ┌──────────────────────────────┐    │
│          │ year  = 2005                 │    │
│          │ month = 3                    │    │
│          │ day   = 15                   │    │
│          └──────────────────────────────┘    │
└──────────────────────────────────────────────┘
```

---

<br>

## 3. 관련 자료형

### 3.1 `enum`

**열거형(enumeration)**은 이름이 붙은 **정수 상수**의 집합을 정의한다:

```c
enum color { RED, GREEN, BLUE };
```

기본적으로 값은 **0**부터 시작하여 1씩 증가한다:

| 이름 | 기본값 |
|:----|:------|
| `RED` | `0` |
| `GREEN` | `1` |
| `BLUE` | `2` |

**사용자 지정 값**을 부여할 수 있다:

```c
enum color { RED = 1, GREEN = 5, BLUE = 10 };
```

일부 값만 지정하면 이후 값은 마지막 지정 값에서 이어진다:

```c
enum level { LOW = 1, MEDIUM, HIGH };
// LOW = 1, MEDIUM = 2, HIGH = 3
```

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

> **팁:** 관련된 상수에는 `#define` 대신 `enum`을 사용하라. 컴파일러가 더 나은 타입 검사와 디버깅 지원을 제공할 수 있다.

### 3.2 `union`

**공용체(union)**는 구조체와 비슷하게 생겼지만, 모든 멤버가 **메모리를 공유**한다. 한 번에 **하나의 멤버만** 유효하며, 공용체의 크기는 **가장 큰 멤버**의 크기와 같다.

```c
union data {
    int i;
    float f;
    char c;
};

printf("크기: %zu\n", sizeof(union data));  // 4 (int 또는 float의 크기)
```

```
union data d;

┌──────────────────┐
│   i (4바이트)    │  ← 세 멤버 모두
│   f (4바이트)    │    같은 메모리
│   c (1바이트)    │    위치를 공유
└──────────────────┘
sizeof(union data) = 4  (가장 큰 멤버)
```

```c
union data d;
d.i = 42;
printf("i = %d\n", d.i);    // 42

d.f = 3.14;
printf("f = %.2f\n", d.f);  // 3.14
printf("i = %d\n", d.i);    // 쓰레기 값 — d.f에 의해 덮어씌워짐!
```

> **경고:** 공용체의 한 멤버에 값을 쓰면 다른 모든 멤버가 덮어씌워진다. **마지막으로 쓴 멤버**만 유효한 값을 갖는다.

### 3.3 `typedef`

`typedef`는 기존 자료형에 대한 **별칭(alias)**을 생성한다:

```c
typedef unsigned int uint;
typedef int BOOL;

uint count = 100;     // unsigned int count = 100;과 동일
BOOL flag = 1;        // int flag = 1;과 동일
```

**가장 일반적인 용도 — 구조체 선언 간소화:**

```c
typedef struct point {
    int x;
    int y;
} Point;

Point p1 = {10, 20};         // "struct point"라고 쓸 필요 없음
Point p2 = {30, 40};
```

이는 다음과 동일하다:

```c
struct point {
    int x;
    int y;
};
typedef struct point Point;
```

`typedef` 없이는 항상 `struct point`라고 써야 한다:

```c
struct point p1 = {10, 20};   // 장황함
Point p1 = {10, 20};          // 간결함 — typedef 사용
```

> **핵심:** `typedef`는 새로운 자료형을 만드는 것이 **아니라**, 기존 자료형에 새 **이름**을 부여하는 것이다. `Point`와 `struct point`는 같은 자료형이다.

---

<br>

## 요약

| 개념 | 핵심 정리 |
|:----|:---------|
| 구조체 | **서로 다른 자료형**의 변수를 하나의 이름으로 묶음; 사용자 정의 자료형 |
| `struct` vs 배열 | 배열 = 같은 자료형; 구조체 = 다른 자료형 |
| 정의 | `struct 태그명 { 멤버들 };` — `}` 뒤 세미콜론 필수; 파일 범위에 정의 |
| 태그명 | 완전한 자료형 이름은 `struct 태그명`; `struct` 없이 태그명만 사용하면 컴파일 오류 |
| 크기 | `sizeof(struct 태그명)` >= 멤버 크기의 합 (패딩/정렬) |
| 선언 | `struct 태그명 var1, var2;` — 멤버는 선언 순서대로 할당 |
| 익명 구조체 | 태그명 없음; 나중에 같은 자료형을 재사용할 수 없음 |
| 초기화 | `struct 태그명 v = {값1, 값2, ...};` 멤버 순서대로; 부분 초기화 시 나머지는 0 |
| 복사 초기화 | `struct 태그명 c2 = c1;` 모든 멤버 복사 |
| 멤버 접근 | 점 연산자: `c1.rate`, `c1.title`; 구조체 변수를 통해서만 접근 가능 |
| 대입 | `c3 = c1`으로 모든 멤버 복사; 선언 이후 `{}` 사용 불가; 배열 멤버는 `strcpy` 필요 |
| 비교 | 구조체에 `==`/`!=` 사용 불가; 멤버별로 비교; 문자열은 `strcmp` 사용 |
| 구조체 배열 | `struct 태그명 arr[N];` — `arr[i].멤버`로 접근 |
| 구조체 포인터 | `struct 태그명 *p = &c1;` — `p->멤버` 또는 `(*p).멤버`로 접근 |
| 화살표 연산자 | `p->멤버`는 `(*p).멤버`와 동일; `(*p)`에 괄호 필수 |
| 값 전달 | 함수가 복사본을 받음; 원본 변경 없음 |
| 포인터 전달 | 함수가 원본 수정 가능; 읽기 전용에는 `const` 사용 |
| 중첩 구조체 | 구조체 안에 구조체 멤버; `외부.내부.필드`로 접근 |
| `enum` | 이름이 붙은 정수 상수; 기본값은 0부터 시작, 1씩 증가 |
| `union` | 모든 멤버가 메모리 공유; 크기 = 가장 큰 멤버; 한 번에 하나만 유효 |
| `typedef` | 자료형에 별칭 부여; 구조체와 함께 사용하여 `struct` 키워드 생략 가능 |

---
