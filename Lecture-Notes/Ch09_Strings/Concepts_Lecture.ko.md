# 9장 — 문자열

[레포지토리 안내](../../README.ko.md) | [English](Concepts_Lecture.md) | [한국어](Concepts_Lecture.ko.md)

> **최종 수정일:** 2026-11-27
>
> Warming-Up C Programming, 천정아, Ch 9

> **학습 목표:**
> 1. 문자와 문자열의 차이와 널 종료 문자열의 저장 방식을 설명할 수 있다
> 2. 문자 배열을 선언하고 초기화하며 배열 크기와 문자열 길이의 관계를 설명할 수 있다
> 3. `<string.h>`의 길이, 복사, 비교, 연결, 검색, 토큰 분리 함수를 사용하고 버퍼 오버플로의 위험을 설명할 수 있다
> 4. `<ctype.h>`의 문자 함수와 문자열 입출력 함수, 데이터 변환 함수를 사용할 수 있다
> 5. 문자 배열, `char*`, `const char*`의 차이를 설명하고 용도에 맞는 형을 고를 수 있다
> 6. 2차원 문자 배열과 문자열 포인터 배열을 비교하여 상황에 맞게 선택할 수 있다

---

## 목차

- [1. 문자 배열](#1-문자-배열)
  - [1.1 문자와 문자열의 차이](#11-문자와-문자열의-차이)
  - [1.2 선언과 초기화](#12-선언과-초기화)
  - [1.3 사용법](#13-사용법)
  - [1.4 널 문자를 이용한 문자열 처리](#14-널-문자를-이용한-문자열-처리)
- [2. 표준 문자열 함수 (`<string.h>`)](#2-표준-문자열-함수-stringh)
  - [2.1 `strlen`](#21-strlen)
  - [2.2 `strcpy` / `strncpy`](#22-strcpy--strncpy)
  - [2.3 `strcmp` / `strncmp`](#23-strcmp--strncmp)
  - [2.4 `strcat` / `strncat`](#24-strcat--strncat)
  - [2.5 `strchr` / `strstr`](#25-strchr--strstr)
  - [2.6 `strtok`](#26-strtok)
  - [2.7 문자열의 비교와 맞바꾸기](#27-문자열의-비교와-맞바꾸기)
  - [2.8 문자열 함수의 직접 구현](#28-문자열-함수의-직접-구현)
- [3. 문자 함수 (`<ctype.h>`)](#3-문자-함수-ctypeh)
  - [3.1 분류](#31-분류)
  - [3.2 변환](#32-변환)
- [4. 문자열 입출력](#4-문자열-입출력)
  - [4.1 `scanf` / `printf`와 `%s`](#41-scanf--printf와-s)
  - [4.2 `fgets` / `gets_s`](#42-fgets--gets_s)
  - [4.3 `puts`](#43-puts)
  - [4.4 문자열 입력의 흔한 문제](#44-문자열-입력의-흔한-문제)
- [5. 데이터 변환 함수 (`<stdlib.h>`, `<stdio.h>`)](#5-데이터-변환-함수-stdlibh-stdioh)
  - [5.1 문자열을 숫자로 변환](#51-문자열을-숫자로-변환)
  - [5.2 `sscanf` / `sprintf`](#52-sscanf--sprintf)
- [6. 문자열 포인터](#6-문자열-포인터)
  - [6.1 `char*` 문자열 포인터](#61-char-문자열-포인터)
  - [6.2 `const char*`](#62-const-char)
  - [6.3 사용 지침](#63-사용-지침)
  - [6.4 문자열을 매개변수로 받는 함수의 작성](#64-문자열을-매개변수로-받는-함수의-작성)
  - [6.5 `char[]`와 `char*`의 저장 방식 비교](#65-char와-char의-저장-방식-비교)
- [7. 문자열 배열](#7-문자열-배열)
  - [7.1 2차원 `char` 배열](#71-2차원-char-배열)
  - [7.2 문자열 포인터 배열](#72-문자열-포인터-배열)
  - [7.3 두 가지 문자열 배열의 메모리 비교](#73-두-가지-문자열-배열의-메모리-비교)
- [개념 적용](#개념-적용)
- [요약](#요약)
- [점검 문제](#점검-문제)

---

<br>

## 1. 문자 배열

### 1.1 문자와 문자열의 차이

**문자열(string)** 은 연속된 문자들의 모임이고, **문자(character)** 는 하나의 문자이다. C에서 **문자**와 **문자열**은 근본적으로 다르다.

| 항목 | 예시 | 크기 | 저장 형태 |
|:----|:----|:----|:---------|
| 문자 리터럴 | `'A'` | `char` 변수에 저장하면 1바이트 (C에서 문자 상수 자체는 `int`형이므로 `sizeof('A')`는 `sizeof(int)`) | ASCII 값 `65` |
| 문자열 리터럴 | `"A"` | 2바이트 | `'A'` + `'\0'` |

*표 1. 문자 리터럴과 문자열 리터럴의 비교*

C에서 **문자열**은 **널 종료 문자 배열(null-terminated character array)** 로, `'\0'` (ASCII 0)으로 끝나는 `char` 값의 연속이다. 문자열의 끝을 나타내는 널 문자를 함께 저장하므로 널 종료 문자열이라고 한다.

```text
Character:  'A'      →  [ 65 ]                           (1 byte)
String:     "A"      →  [ 65 ][ 0 ]                      (2 bytes)
String:     "Hello"  →  [ H ][ e ][ l ][ l ][ o ][ \0 ]  (6 bytes)
```

*그림 1. 문자 `'A'`와 문자열 `"A"`, `"Hello"`의 저장 형태*

**문자열 상수와 문자열 변수:**

- **문자열 상수**(리터럴)인 `"Hello"`는 값이 바뀌지 않는 문자열이며, 컴파일러가 일반적으로 **읽기 전용 메모리**에 저장한다. 수정할 수 없다.
- **문자열 변수**는 문자열의 사본을 담고 있는 `char` 배열이다. 내용을 수정할 수 있으므로, 실행 중에 사용자로부터 입력받은 문자열이나 내용이 바뀌는 문자열은 문자 배열에 저장해야 한다.

> **핵심:** 널 종료 문자 `'\0'`는 모든 문자열 함수에게 문자열이 어디서 끝나는지 알려준다. 이것이 없으면 `printf("%s", ...)`와 같은 함수가 배열 경계를 넘어서 읽게 되며, 이는 **미정의 동작(undefined behavior)** 이다.

### 1.2 선언과 초기화

문자 배열은 문자열 길이에 `'\0'`를 위한 **1바이트를 더한** 크기여야 한다. 즉 배열의 크기는 저장할 문자열의 길이 + 1 이상으로 지정한다.

```c
// Explicit size: remaining positions filled with '\0'
char str1[10] = "abc";    // stores: 'a','b','c','\0','\0',...,'\0' (size 10)

// Auto-sized: compiler determines size from initializer
char str2[] = "abc";      // stores: 'a','b','c','\0' (size 4)

// Initialized with character list (must include '\0' manually)
char str3[] = {'a', 'b', 'c', '\0'};  // same as str2

// Initialized with character list WITHOUT '\0': NOT a valid string!
char str4[] = {'a', 'b', 'c'};        // size 3, no null terminator
```

초기값을 지정하면 배열 크기를 생략할 수 있으며, 이때 문자열의 길이 + 1 크기로 배열이 할당된다. 문자 배열 전체를 널 문자로 초기화하려면 널 문자 하나로 이루어진 **널 문자열**(`""`)로 초기화한다.

```c
char str5[10] = "";   // all 10 bytes are '\0'
```

**`char str[10] = "abc";`의 메모리 배치:**

```text
Index:   [0]  [1]  [2]   [3]  [4]  [5]  [6]  [7]  [8]  [9]
Value:   'a'  'b'  'c'  '\0' '\0' '\0' '\0' '\0' '\0' '\0'
```

*그림 2. `char str[10] = "abc";`의 메모리 배치*

> **주의:** 문자열 길이가 배열 크기와 같거나 초과하면, `'\0'`이 저장되지 않는다. 이렇게 하면 유효한 문자열이 **아닌** 문자 배열이 만들어져 모든 문자열 함수에서 버그가 발생한다. 문자열 길이가 배열 크기와 같으면 C는 널 문자 없이 초기화하고, 배열 크기보다 길면 컴파일러가 경고하거나 오류를 낸다.

```c
char danger[3] = "abc";  // stores: 'a','b','c', NO '\0'!
printf("%s", danger);     // undefined behavior: reads past array boundary
```

### 1.3 사용법

**개별 문자 접근:** 인덱스로 배열의 원소에 접근할 수 있다.

```c
char str[] = "Hello";
printf("%c\n", str[0]);   // H
printf("%c\n", str[4]);   // o
str[0] = 'h';             // OK: modify individual character
printf("%s\n", str);      // hello
```

**문자열 출력:** 문자를 하나씩 `%c`로 출력할 수도 있고, `%s` 서식 지정자로 널 문자를 만날 때까지 문자열 전체를 한꺼번에 출력할 수도 있다.

```c
char str[] = "Hello";
printf("%s\n", str);      // prints until '\0': Hello
printf("%c\n", str[1]);   // prints one character: e
```

**선언 후 문자열 대입 불가:**

```c
char str[10];
str = "Hello";   // ERROR: array name is a constant pointer, cannot reassign
```

배열 이름 `str`은 배열의 시작 주소이며 변경할 수 없는 **상수 포인터**처럼 동작한다. 가리키는 대상을 바꿀 수 없으므로 대신 `strcpy()`를 사용한다.

```c
char str[10];
strcpy(str, "Hello");  // correct way to copy a string into an array
```

개별 문자는 수정할 수 있지만(`str[0] = 'X'`), `=`로 전체 문자열을 교체할 수는 없다. 선언 후 문자열 전체를 대입하려면 반드시 `strcpy()`를 사용한다.

### 1.4 널 문자를 이용한 문자열 처리

문자열의 끝은 길이가 아니라 널 문자로 표시되므로, 문자열을 처리하는 반복문은 원소의 개수 대신 `'\0'`을 만날 때까지 진행한다. 다음 코드는 길이를 직접 세고, 소문자를 대문자로 바꾸면서 원래 대문자였던 문자의 개수를 센다.

```c
char s[20] = "Hello, C";
int n = 0, i, upper = 0;

while (s[n] != '\0')                    // until the null character
    n++;
printf("length = %d\n", n);

for (i = 0; s[i] != '\0'; i++) {
    if (s[i] >= 'a' && s[i] <= 'z')
        s[i] = s[i] - 'a' + 'A';        // lowercase to uppercase
    else if (s[i] >= 'A' && s[i] <= 'Z')
        upper++;
}
printf("%s, originally uppercase = %d\n", s, upper);
```

```text
length = 8
HELLO, C, originally uppercase = 2
```

`"Hello, C"`는 `H`, `e`, `l`, `l`, `o`, `,`, 빈칸, `C`의 8문자이고 `s[8]`이 `'\0'`이므로 첫 반복은 `n`이 8일 때 멈춘다. 배열의 크기 20은 반복의 끝을 정하는 데 쓰이지 않는다. 둘째 반복에서 `s[i] - 'a' + 'A'`는 ASCII에서 소문자와 대문자의 코드 차이가 같다는 성질(3장 1.3절)을 이용하며, 쉼표와 빈칸은 어느 조건에도 해당하지 않아 그대로 남는다. 원래 대문자는 `H`와 `C`의 2개이다. 이 방식은 `'\0'`이 있다는 것을 전제로 하므로, 1.2절의 주의처럼 `'\0'`이 없는 문자 배열에 쓰면 반복이 배열을 넘어 계속되어 정의되지 않은 동작이 된다. 같은 일을 하는 표준 함수가 2절의 `strlen`과 3절의 `toupper`이다.

---

<br>

## 2. 표준 문자열 함수 (`<string.h>`)

아래의 모든 함수는 `#include <string.h>`가 필요하다. 문자열 처리 함수를 이용하면 구체적인 처리 과정을 몰라도 간단하게 문자열을 다룰 수 있다.

### 2.1 `strlen`

문자열의 **길이**를 반환하며, 널 종료 문자는 **제외**한다. 문자 배열이나 문자열 리터럴을 전달할 수 있다.

```c
#include <string.h>

char str[] = "Hello";
size_t len = strlen(str);   // 5
```

**`strlen`과 `sizeof` 비교:**

| 표현식 | 값 | 의미 |
|:------|:---|:----|
| `strlen("Hello")` | `5` | `'\0'` 앞의 문자 수 |
| `sizeof("Hello")` | `6` | 할당된 총 바이트 수 (`'\0'` 포함) |

*표 2. `strlen`과 `sizeof`의 비교*

```c
char str[20] = "Hello";
printf("strlen: %zu\n", strlen(str));   // 5  (string length)
printf("sizeof: %zu\n", sizeof(str));   // 20 (array size in bytes)
```

> **핵심:** `strlen`은 실행 중에 `'\0'`을 찾을 때까지 탐색한다(O(n)). `sizeof`는 컴파일할 때 결정된다(O(1)). `strlen`의 반환 타입은 `size_t`(부호 없는 정수)이다.

### 2.2 `strcpy` / `strncpy`

**`strcpy(dest, src)`** 는 원본 문자열 전체(`'\0'` 포함)를 목적지에 복사하고 `dest`를 반환한다.

```c
char src[] = "Hello";
char dest[20];
strcpy(dest, src);         // dest is now "Hello"
```

**`strncpy(dest, src, n)`** 는 최대 `n`개의 문자를 복사한다. `src`가 `n`보다 짧으면 나머지를 `'\0'`으로 채운다. `src`가 더 길면 **`'\0'`이 추가되지 않는다**.

```c
char dest[10];
strncpy(dest, "Hello, World!", 9);
dest[9] = '\0';   // always manually null-terminate after strncpy!
```

> **주의:** `strcpy`는 **경계 검사를 하지 않는다**. `dest`가 너무 작으면 할당받은 메모리 범위를 넘어서 값을 저장하여 메모리를 변조하는 **버퍼 오버플로**(버퍼 오버런)가 발생하며, 이는 C에서 가장 위험한 버그 중 하나이다. 항상 `dest`의 크기가 충분한지 확인한다.

> **참고:** **Visual Studio의 안전 문자열 함수.** Visual Studio 2019 이후의 기본 프로젝트 설정에서는 `strcpy`처럼 버퍼 오버런 위험이 있는 함수를 쓰면 보안 경고(C4996)가 오류로 처리되어 컴파일되지 않는다. 대신 목적지 배열의 크기를 함께 받는 `errno_t strcpy_s(char *dest, rsize_t destsz, const char *src);`를 쓰거나, 라이브러리 헤더를 포함하는 문장보다 **앞에** `#define _CRT_SECURE_NO_WARNINGS`를 정의하여 경고를 끈다. `strcat`에도 같은 형태의 `strcat_s(dest, destsz, src)`가 있다. 이 함수들은 C11 표준의 선택 사항인 부록 K(Annex K)에 속하므로, gcc와 clang의 표준 라이브러리는 제공하지 않는다.

### 2.3 `strcmp` / `strncmp`

**`strcmp(s1, s2)`** 는 두 문자열을 문자 코드(ASCII 값) 기준으로 한 문자씩 비교한다. 즉 두 문자열을 사전순으로 비교하여, `s1`이 앞이면 음수, 뒤이면 양수, 같으면 0을 반환한다.

| 반환 값 | 의미 |
|:--------|:----|
| `0` | 두 문자열이 같음 |
| `> 0` | 첫 번째 다른 문자에서 `s1`이 `s2`보다 큼 |
| `< 0` | 첫 번째 다른 문자에서 `s1`이 `s2`보다 작음 |

*표 3. `strcmp`의 반환 값*

```c
strcmp("abc", "abc");   // returns 0  (equal)
strcmp("abd", "abc");   // returns > 0  ('d' > 'c')
strcmp("abc", "abd");   // returns < 0  ('c' < 'd')
strcmp("abc", "abcd");  // returns < 0  ('\0' < 'd')
```

표준은 반환값의 부호만 정하므로, 0이 아닌 반환값이 반드시 -1이나 1인 것은 아니다. 결과는 `strcmp(...) < 0`처럼 부호로 판단한다.

**`strncmp(s1, s2, n)`** 은 처음 `n`개 문자만 비교한다.

```c
strncmp("Hello", "Help", 3);   // returns 0  (first 3 chars are equal)
strncmp("Hello", "Help", 4);   // returns < 0  ('l' < 'p')
```

> **주의:** 문자열 비교에 `==`를 사용하지 않는다. `s1 == s2`는 **포인터 주소**를 비교하는 것이지, 문자열 내용을 비교하는 것이 아니다. 반드시 `strcmp`를 사용한다.

### 2.4 `strcat` / `strncat`

**`strcat(dest, src)`** 는 `dest`에 저장된 문자열의 끝에 `src`를 복사하여 이어붙인다.

```c
char dest[20] = "Hello";
strcat(dest, ", ");       // "Hello, "
strcat(dest, "World!");   // "Hello, World!"
```

**`strncat(dest, src, n)`** 는 `src`에서 최대 `n`개의 문자를 이어붙인 후 `'\0'`을 추가한다.

```c
char dest[20] = "Hello";
strncat(dest, ", World!!!!!", 7);  // "Hello, World" (appends 7 chars + '\0')
```

> **주의:** `dest`에는 기존 문자열 + 이어붙일 문자열 + `'\0'`을 위한 **충분한 공간**이 있어야 한다. `strcat`은 경계 검사를 수행하지 않으므로 버퍼 오버런의 위험이 있다.

### 2.5 `strchr` / `strstr`

**`strchr(str, ch)`** 는 `str`에서 문자 `ch`의 **첫 번째 위치**를 찾는다. 찾은 문자에 대한 포인터를 반환하고, 없으면 `NULL`을 반환한다.

```c wide-ok
char str[] = "Hello, World!";
char *p = strchr(str, 'o');
if (p != NULL) {
    printf("'o' 위치: 인덱스 %ld\n", p - str);   // 4
    printf("'o'부터 끝까지: %s\n", p);             // o, World!
}
```

**`strstr(str, substr)`** 는 `str`에서 부분 문자열 `substr`의 **첫 번째 위치**를 찾는다. 일치하는 위치의 포인터를 반환하고, 없으면 `NULL`을 반환한다. 예를 들어 파일 이름에서 `".txt"`를 찾아 텍스트 파일인지 판단할 수 있다.

```c wide-ok
char str[] = "Hello, World!";
char *p = strstr(str, "World");
if (p != NULL) {
    printf("위치: 인덱스 %ld\n", p - str);   // 7
    printf("부분 문자열: %s\n", p);            // World!
}
```

### 2.6 `strtok`

**`strtok(str, delim)`** 는 `delim`에 있는 구분 문자들을 기준으로 문자열을 **토큰**으로 분할한다. 토큰은 문장에서 더 이상 나눌 수 없는 최소 단위이며, `delim`에 쓴 문자 하나하나가 모두 구분 문자이다.

- **첫 번째 호출:** 분할할 문자열을 전달한다.
- **이후 호출:** 같은 문자열을 계속 분할하려면 `NULL`을 전달한다.
- 원본 문자열의 구분자를 `'\0'`으로 대체하여 **원본을 수정**한다. 토큰의 주소를 반환하고, 토큰이 더 없으면 `NULL`을 반환한다.

```c
char str[] = "Alice,Bob,Charlie,David";
char *token = strtok(str, ",");

while (token != NULL) {
    printf("%s\n", token);
    token = strtok(NULL, ",");
}
// Output:
// Alice
// Bob
// Charlie
// David
```

> **주의:** `strtok`은 원본 문자열을 수정한다. 원본을 보존해야 한다면 먼저 `strcpy`로 사본을 만든다. 같은 이유로 수정할 수 없는 문자열 리터럴을 `strtok`에 넘기면 안 된다.

### 2.7 문자열의 비교와 맞바꾸기

`strcmp(s1, s2)`는 두 문자열을 앞에서부터 한 문자씩 비교하다가 처음으로 다른 문자를 만나면, 그 두 문자의 코드값의 대소로 결과를 정한다. `s1`이 앞서면 음수, 같으면 0, 뒤에 오면 양수를 반환하며, 반환값의 크기는 구현마다 다르므로 부호만 검사한다. 다음은 각 비교의 결과를 부호로 확인한 것이다.

```c
printf("%d\n", strcmp("apple", "apricot") < 0);
printf("%d\n", strcmp("apple", "app") > 0);
printf("%d\n", strcmp("Zebra", "apple") < 0);
printf("%d\n", strcmp("abc", "abc") == 0);
printf("%d\n", strncmp("apple", "apricot", 2) == 0);
```

```text
1
1
1
1
1
```

| 비교 | 처음 다른 위치 | 결과의 부호와 이유 |
|:-----|:-----|:-----|
| `"apple"`과 `"apricot"` | 인덱스 2 (`'p'`와 `'r'`) | 음수, `'p'`(112) < `'r'`(114) |
| `"apple"`과 `"app"` | 인덱스 3 (`'l'`과 `'\0'`) | 양수, 짧은 쪽이 먼저 끝나 `'\0'`(0)이 더 작음 |
| `"Zebra"`와 `"apple"` | 인덱스 0 (`'Z'`와 `'a'`) | 음수, 대문자 `'Z'`(90) < 소문자 `'a'`(97) |
| `"abc"`와 `"abc"` | 없음 | 0, 모든 문자와 널 문자가 같음 |
| 앞 2문자만 비교한 `"apple"`과 `"apricot"` | 없음 | 0, `strncmp`는 n개까지만 비교 |

*표 4. `strcmp`의 비교 과정*

`strcmp`의 순서는 사전 순서와 비슷하지만 문자 코드를 따르므로, ASCII에서는 모든 대문자가 모든 소문자보다 앞선다. 대소문자를 무시하고 비교하려면 두 문자열을 3절의 `tolower`로 바꾼 사본끼리 비교한다.

두 문자열을 맞바꿀 때는 배열에 `=`로 대입할 수 없으므로(1.3절) 임시 배열을 두고 `strcpy`를 세 번 쓴다. 다음 코드는 두 단어가 사전 순서가 아니면 맞바꾼다.

```c
char a[20] = "banana", b[20] = "apple", temp[20];

if (strcmp(a, b) > 0) {         // if a comes after b
    strcpy(temp, a);
    strcpy(a, b);
    strcpy(b, temp);
}
printf("%s %s\n", a, b);
```

```text
apple banana
```

`'b'`가 `'a'`보다 크므로 `strcmp(a, b)`는 양수이고, 세 번의 복사로 두 내용이 바뀐다. 이때 세 배열은 모두 상대 문자열을 담을 만큼 커야 한다. 두 배열의 크기가 다르면 긴 문자열을 짧은 배열로 복사할 때 2.2절의 버퍼 오버런이 일어날 수 있다.

### 2.8 문자열 함수의 직접 구현

표준 문자열 함수의 동작은 포인터와 널 문자만으로 직접 구현해 보면 분명해진다. 다음은 `strlen`, `strcpy`, `strcat`과 같은 일을 하는 함수이다.

```c
size_t my_strlen(const char *s)
{
    const char *p = s;

    while (*p != '\0')          // move p up to the null character
        p++;
    return (size_t)(p - s);     // the number of slots moved is the length
}

char *my_strcpy(char *dest, const char *src)
{
    char *d = dest;

    while ((*d++ = *src++) != '\0')     // copy one character at a time, through the null
        ;
    return dest;
}

char *my_strcat(char *dest, const char *src)
{
    my_strcpy(dest + my_strlen(dest), src);     // copy from the position of dest's null
    return dest;
}

int main(void)
{
    char buf[20];

    my_strcpy(buf, "data");
    printf("%s %zu\n", buf, my_strlen(buf));
    my_strcat(buf, "base");
    printf("%s %zu\n", buf, my_strlen(buf));
    return 0;
}
```

```text
data 4
database 8
```

- **`my_strlen`:** `p`를 널 문자에 이를 때까지 옮긴 뒤, 같은 배열 안의 두 포인터의 차 `p - s`로 문자의 개수를 구한다(8장 2.1절). `"data"`이면 `p`가 4칸 이동하여 4를 반환한다.
- **`my_strcpy`:** 조건식 `(*d++ = *src++) != '\0'`은 한 번에 세 가지 일을 한다. `*src`를 `*d`에 대입하고, 두 포인터를 다음 칸으로 옮기며, 방금 대입한 문자가 널 문자인지 검사한다. 널 문자도 복사한 뒤에 반복이 끝나므로 복사본은 항상 널 문자로 끝난다. 반복 본체는 5장 3.7절의 널 문장이다. `"data"`를 복사하면 `'d'`, `'a'`, `'t'`, `'a'`, `'\0'`의 5번 대입이 일어난다.
- **`my_strcat`:** `dest + my_strlen(dest)`는 `dest`의 널 문자가 있는 자리이다. 그 자리부터 `src`를 복사하면 널 문자가 덮이고 `src`가 이어 붙는다. `buf`가 `"data"`일 때 오프셋 4부터 `"base"`를 복사하여 `"database"`가 된다.

이 구현은 표준 함수와 같은 약점도 그대로 보여 준다. 어느 함수도 `dest`의 크기를 모르므로, 복사할 문자열이 배열보다 길면 2.2절의 버퍼 오버런이 일어난다. 크기를 함께 받는 함수를 써야 하는 이유이다.

---

<br>

## 3. 문자 함수 (`<ctype.h>`)

아래의 모든 함수는 `#include <ctype.h>`가 필요하다. `int`(문자)를 인자로 받아 참이면 0이 아닌 값, 거짓이면 0을 반환한다.

### 3.1 분류

| 함수 | 참인 조건 |
|:----|:---------|
| `isalpha(c)` | `c`가 영문자 (`A-Z`, `a-z`) |
| `isdigit(c)` | `c`가 숫자 (`0-9`) |
| `isalnum(c)` | `c`가 영문자 또는 숫자 |
| `isupper(c)` | `c`가 대문자 (`A-Z`) |
| `islower(c)` | `c`가 소문자 (`a-z`) |
| `isspace(c)` | `c`가 공백 문자 (스페이스, `\t`, `\n` 등) |
| `isxdigit(c)` | `c`가 16진수 숫자 (`0-9`, `A-F`, `a-f`) |

*표 5. `<ctype.h>`의 문자 분류 함수*

```c wide-ok
#include <ctype.h>

char c = 'A';
if (isalpha(c))  printf("영문자\n");   // 영문자
if (isupper(c))  printf("대문자\n");   // 대문자
if (isdigit(c))  printf("숫자\n");     // (not printed)
```

> **주의:** 이 함수들의 인자는 `unsigned char`로 나타낼 수 있는 값이거나 `EOF`여야 한다. `char`가 부호 있는 형인 시스템에서 한글처럼 ASCII가 아닌 바이트는 음수가 되므로, `isspace((unsigned char)str[i])`처럼 `unsigned char`로 변환하여 넘긴다.

### 3.2 변환

| 함수 | 동작 |
|:----|:----|
| `toupper(c)` | `c`가 소문자이면 대문자로 변환하여 반환 |
| `tolower(c)` | `c`가 대문자이면 소문자로 변환하여 반환 |

*표 6. `<ctype.h>`의 대소문자 변환 함수*

```c
printf("%c\n", toupper('a'));   // A
printf("%c\n", tolower('Z'));   // z
printf("%c\n", toupper('1'));   // 1 (non-letter unchanged)
```

**문자열 전체를 대문자로 변환:**

```c
char str[] = "Hello, World!";
for (int i = 0; str[i] != '\0'; i++) {
    str[i] = toupper(str[i]);
}
printf("%s\n", str);   // HELLO, WORLD!
```

`toupper`와 `tolower`는 영문자가 아닌 문자에 대해서는 변환 없이 그대로 반환한다. 따라서 영문자인지 먼저 검사하지 않고 호출해도 된다.

---

<br>

## 4. 문자열 입출력

문자열 입출력 함수를 사용하려면 `<stdio.h>`를 포함해야 한다.

### 4.1 `scanf` / `printf`와 `%s`

**`scanf("%s", str)`** 는 입력 버퍼에서 **공백 문자**(스페이스, 탭, 개행)를 만날 때까지 문자를 읽는다. 배열 이름이 배열의 시작 주소로 변환되므로 `&`가 필요 없다.

```c wide-ok
char name[20];
printf("이름 입력: ");
scanf("%s", name);          // reads one word only
printf("안녕하세요, %s!\n", name);
```

**`printf("%s", str)`** 는 `'\0'`까지 문자를 출력한다.

| 입력 | `scanf("%s", name)`에 저장되는 값 |
|:----|:-------------------------------|
| `Alice` | `"Alice"` |
| `Alice Bob` | `"Alice"` (공백에서 중단; `"Bob"`은 버퍼에 남음) |

*표 7. 입력에 따라 `scanf("%s", name)`에 저장되는 값*

> **주의:** `scanf("%s", ...)`는 기본적으로 길이 제한이 없어서 버퍼 오버플로를 일으킬 수 있다. `scanf("%19s", name)`처럼 너비 지정자를 사용하면 최대 19문자를 읽어 `'\0'`을 위한 공간이 남는다. Visual Studio의 `scanf_s`로 문자열을 읽을 때는 `scanf_s("%s", name, (unsigned)sizeof(name))`처럼 배열의 크기를 함께 전달하며, 배열보다 긴 문자열이 입력되면 첫 원소를 널 문자로 만들어 빈 문자열로 처리한다.

### 4.2 `fgets` / `gets_s`

빈칸을 포함한 문자열을 한 줄 입력받으려면 `fgets`나 `gets_s`를 이용한다. **`fgets(str, count, stdin)`** 는 최대 `count - 1`개의 문자 또는 개행 문자까지(둘 중 먼저 오는 것까지) 읽는다. 저장된 문자열에 개행 문자 `'\n'`이 **포함**된다.

```c wide-ok
char line[100];
printf("한 줄 입력: ");
fgets(line, 100, stdin);
// If user types "Hello World\n", line contains "Hello World\n\0"
```

**끝의 개행 문자 제거:**

```c
char line[100];
fgets(line, 100, stdin);
size_t len = strlen(line);
if (len > 0 && line[len - 1] == '\n') {
    line[len - 1] = '\0';
}
```

**`gets_s(str, count)`** (C11)는 개행 문자까지 읽되, 저장된 문자열에서 `'\n'`을 **제외**한다. `gets_s`는 C11의 선택 사항인 부록 K에 속하여 Visual Studio는 제공하지만 gcc와 clang의 표준 라이브러리는 제공하지 않는다.

```c
char line[100];
gets_s(line, 100);   // reads line without '\n'
```

| 함수 | 읽는 범위 | `'\n'` 포함 여부 | 버퍼 오버플로 방지 |
|:----|:---------|:----------------|:-----------------|
| `scanf("%s", ...)` | 공백 문자까지 | 아니오 | 없음 (너비 지정자 사용) |
| `fgets(str, n, stdin)` | 개행 또는 `n-1`자까지 | 예 | 예 |
| `gets_s(str, n)` | 개행까지 | 아니오 | 예 |

*표 8. 문자열 입력 함수의 비교*

전체 줄을 읽을 때는 `fgets`를 사용한다. 안전하고 모든 시스템에서 사용할 수 있다. 끝의 `'\n'`이 필요 없으면 제거해야 한다.

입력한 줄이 배열보다 길면 `fgets`는 배열 크기보다 하나 적은 문자만 읽고 널 문자를 붙인 뒤 멈추며, 나머지는 버퍼에 남아 다음 `fgets`가 이어서 읽는다. 크기가 8인 `buf`로 `programming`을 두 번 읽으면 첫 호출은 `program`(7문자), 둘째 호출은 남은 `ming`과 줄바꿈(5문자)을 얻는다. 그래서 읽은 문자열의 끝에 `'\n'`이 없으면 줄이 다 읽히지 않았다고 판단할 수 있다.

### 4.3 `puts`

**`puts(str)`** 는 문자열 한 줄을 출력하고 **자동으로 개행**을 추가한다.

```c
char str[] = "Hello, World!";
puts(str);    // prints: Hello, World!\n
// equivalent to: printf("%s\n", str);
```

### 4.4 문자열 입력의 흔한 문제

문자열 입력에서 자주 생기는 두 가지 문제는 입력 버퍼(5장 3.8절)로 설명된다. 다음 프로그램은 두 문제를 차례로 보여 준다.

```c
char word[20], rest[40], line[40];
int age = 0;

scanf("%19s", word);
fgets(rest, sizeof(rest), stdin);
printf("word = [%s], rest = [%s]\n", word, rest);

scanf("%d", &age);
fgets(line, sizeof(line), stdin);
printf("age = %d, line = [%s], len = %zu\n", age, line, strlen(line));
```

```text
Kim Minsu
21
Seoul
```

위의 세 줄을 입력하면 다음이 출력된다.

```text
word = [Kim], rest = [ Minsu
]
age = 21, line = [
], len = 1
```

첫째, `%s`는 공백 문자를 만나면 읽기를 멈춘다. `"Kim Minsu"`에서 `word`에는 `Kim`만 들어가고, 빈칸부터의 `" Minsu\n"`은 버퍼에 남아 다음 `fgets`가 가져간다. 빈칸이 들어 있는 한 줄 전체를 읽으려면 `scanf("%s")`가 아니라 `fgets`를 쓴다. 둘째, `scanf("%d")`가 21을 읽은 뒤 남긴 `'\n'` 때문에 바로 다음의 `fgets`는 사용자의 입력을 기다리지 않고 줄바꿈 하나만 읽어 길이 1의 문자열을 만든다. `Seoul`은 읽히지 않는다.

두 번째 문제는 `scanf` 뒤에 버퍼에 남은 문자를 줄바꿈까지 버리면 해결된다. 다음 코드에서 `getchar()`는 버퍼에서 문자 하나를 읽어 반환하는 함수이며, 반복은 `'\n'`을 읽을 때까지 남은 문자를 버린다. 이어서 `fgets`로 읽은 줄 끝의 `'\n'`을 `strcspn`으로 찾아 지운다.

```c
scanf("%d", &age);
while ((c = getchar()) != '\n' && c != EOF)     // discard the rest of the line
    ;
fgets(line, sizeof(line), stdin);
line[strcspn(line, "\n")] = '\0';               // remove the '\n' at the end of the line
```

```text
age? 21
address? Seoul Mapo
[21] [Seoul Mapo] len = 10
```

`c`는 `int`로 선언해야 `getchar`가 반환하는 `EOF`(음수)와 문자 코드를 모두 구별할 수 있다. 정수와 문자열을 섞어 읽는 프로그램은 처음부터 모든 입력을 `fgets`로 한 줄씩 읽고, 숫자는 5절의 `sscanf`로 꺼내는 방법도 많이 쓴다.

---

<br>

## 5. 데이터 변환 함수 (`<stdlib.h>`, `<stdio.h>`)

### 5.1 문자열을 숫자로 변환

아래 함수들은 `<stdlib.h>`에 선언되어 있다.

| 함수 | 변환 대상 | 예시 |
|:----|:---------|:----|
| `atoi(str)` | `int` | `atoi("42")` → `42` |
| `atof(str)` | `double` | `atof("3.14")` → `3.14` |
| `atol(str)` | `long` | `atol("1000000")` → `1000000L` |

*표 9. 문자열을 숫자로 변환하는 함수*

```c
#include <stdlib.h>

char s1[] = "123";
char s2[] = "3.14";
char s3[] = "99abc";

int n = atoi(s1);       // 123
double d = atof(s2);    // 3.14
int m = atoi(s3);       // 99 (stops at first non-numeric character)
int z = atoi("abc");    // 0  (no valid number found)
```

> **핵심:** `atoi`, `atof`, `atol`은 앞의 공백을 건너뛰고, 가능한 한 많은 유효 문자를 읽은 후, 유효하지 않은 첫 문자에서 멈춘다. 유효한 변환이 불가능하면 `0`을 반환한다.

### 5.2 `sscanf` / `sprintf`

**`sscanf(str, format, ...)`** 는 (표준 입력 대신) **문자열로부터** 서식에 맞는 데이터를 읽는다.

```c wide-ok
char data[] = "Alice 25 3.85";
char name[20];
int age;
double gpa;

sscanf(data, "%s %d %lf", name, &age, &gpa);
printf("이름: %s, 나이: %d, 학점: %.2f\n", name, age, gpa);
// Name: Alice, Age: 25, GPA: 3.85
```

**`sprintf(str, format, ...)`** 는 (표준 출력 대신) **문자열에** 서식화된 데이터를 쓴다.

```c
char result[50];
int x = 42;
double pi = 3.14159;

sprintf(result, "x = %d, pi = %.2f", x, pi);
printf("%s\n", result);   // x = 42, pi = 3.14
```

`sscanf`와 `sprintf`는 `scanf`와 `printf`의 문자열 버전으로, 문자열 안의 데이터를 파싱하거나 포맷팅할 때 유용하다. 한 줄을 `gets_s`나 `fgets`로 읽은 뒤 `sscanf`로 값을 꺼내거나, `sprintf`로 출력할 문자열을 만든 뒤 `puts`로 출력하는 식으로 함께 쓰는 경우가 많다. `sprintf`도 대상 배열의 크기를 검사하지 않으므로, 크기를 받는 `snprintf`(C99)가 더 안전하다.

---

<br>

## 6. 문자열 포인터

### 6.1 `char*` 문자열 포인터

**문자열 포인터**는 `char*`형의 포인터로, `char`형 변수나 `char`형 배열의 원소를 가리킬 수 있다. `char*` 포인터는 **읽기 전용 메모리**에 저장된 문자열 리터럴을 가리킬 수도 있다. 문자열 리터럴은 텍스트 세그먼트(문자열 테이블)라는 변경할 수 없는 메모리 영역에 보관되며, 수식에서 문자열 리터럴의 값은 그 주소이다.

```c
char *p = "Hello";   // p points to a string literal
printf("%s\n", p);   // Hello
```

**메모리 배치:**

```text
Read-only memory:  [ H ][ e ][ l ][ l ][ o ][ \0 ]
                     ▲
                     │
            p ───────┘
```

*그림 3. 문자열 리터럴을 가리키는 `char*` 포인터 p*

> **주의:** 포인터를 통해 문자열 리터럴을 수정하는 것은 **미정의 동작**이며, 일반적으로 프로그램이 충돌한다.

```c
char *p = "Hello";
p[0] = 'h';      // UNDEFINED BEHAVIOR! String literals are read-only.
```

**수정 가능한 사본**을 만드는 `char` 배열과 비교한다.

```c
char arr[] = "Hello";
arr[0] = 'h';     // OK: arr is a modifiable copy
```

문자열 포인터에 다른 문자열 리터럴을 대입하면 포인터가 가리키는 대상만 달라진다. `char*`형 포인터는 주로 문자 배열을 가리키는 데 사용하며, 이때 포인터가 가리키는 배열의 내용을 변경할 수 있다. 배열을 직접 쓰지 않고 포인터를 쓰는 이유는 포인터를 배열의 특정 위치로 옮겨 가면서 문자열을 처리할 수 있기 때문이다.

```c
char str[] = "hello world";
char *p = strchr(str, ' ');   // address of the space character
if (p != NULL) {
    p++;                      // point to the character after the space
    printf("%s\n", p);        // world
}
```

### 6.2 `const char*`

`const char*`를 사용하면 문자열을 수정하지 않겠다는 의도를 명시적으로 선언할 수 있다. 이를 통해 컴파일러가 실수로 인한 수정을 잡아낼 수 있다. `const char*`는 주로 문자열 리터럴을 가리키는 데 쓰며, 문자 배열을 가리킬 때는 배열의 내용을 읽기만 하고 변경할 수 없게 한다.

```c
const char *msg = "Hello";
msg[0] = 'h';    // COMPILE ERROR: cannot modify const data
msg = "World";   // OK: can change what the pointer points to
```

### 6.3 사용 지침

| 용도 | 선언 | 수정 가능 여부 |
|:----|:----|:---------|
| 문자열 수정이 필요할 때 | `char str[] = "Hello";` | 예 |
| 읽기 전용 문자열 참조 | `const char *str = "Hello";` | 아니오 |
| 함수 매개변수 (읽기 전용) | `void print(const char *s);` | 아니오 |
| 함수 매개변수 (수정 가능) | `void modify(char *s);` | 예 |

*표 10. 용도에 따른 문자열 선언*

```c
// Mutable string (array: copies the literal)
char greeting[] = "Hello";
greeting[0] = 'h';             // OK

// Immutable reference (pointer: points to literal)
const char *message = "Hello";
// message[0] = 'h';           // compile error
```

문자열 내용을 변경해야 하면 `char[]`를 사용하고, 읽기 또는 전달만 필요하면 `const char*`를 사용한다. 사용자로부터 입력받거나 변경할 수 있는 문자열은 문자 배열에 저장하고, 실행 중에 변경되지 않는 문자열은 문자열 리터럴로 나타낸다. `char*` 포인터는 변경할 수 있는 문자열(문자 배열)을 가리킬 때만 쓰고, 문자열 리터럴을 가리키거나 문자 배열을 읽기 전용으로 접근할 때는 `const char*` 포인터를 쓴다.

문자열을 매개변수로 받는 함수를 정의할 때는 다음을 지킨다. 문자열이 출력 매개변수이면 `char*`형 매개변수를 쓰고 문자 배열의 크기도 매개변수로 받아, 함수 안에서 문자열을 바꿀 때 배열 크기를 넘지 않게 한다. 문자열이 입력 매개변수이면 `const char*`형 매개변수를 쓰며, 문자열의 끝을 널 문자로 확인할 수 있으므로 배열 크기를 받을 필요가 없다. 함수 안에서는 포인터에 인덱스를 써서 문자 배열처럼 다룰 수 있다.

이런 함수를 호출할 때, 매개변수가 `char*`형이면 문자 배열과 `char*`형 포인터만 인자로 전달할 수 있고 호출 후 문자열의 내용이 바뀔 수 있다. 매개변수가 `const char*`형이면 문자 배열, 문자열 리터럴, `char*`형 포인터, `const char*`형 포인터를 모두 전달할 수 있고 호출 후에도 문자열의 내용은 바뀌지 않는다.

### 6.4 문자열을 매개변수로 받는 함수의 작성

6.3절의 지침에 따라 문자열을 읽기만 하는 함수는 `const char*` 매개변수로, 문자열을 바꾸는 함수는 `char*` 매개변수로 작성한다. 다음 `count_space`는 빈칸의 개수를 세고, `reverse`는 문자열을 제자리에서 뒤집는다.

```c
int count_space(const char *s)
{
    int count = 0;

    while (*s != '\0') {        // while the character s points to is not null
        if (*s == ' ')
            count++;
        s++;                    // move to the next character
    }
    return count;
}

void reverse(char *s)
{
    int i = 0, j = 0;
    char t;

    while (s[j] != '\0')        // move j to the position of the null character
        j++;
    j--;                        // position of the last character
    while (i < j) {
        t = s[i];
        s[i] = s[j];
        s[j] = t;
        i++;
        j--;
    }
}

int main(void)
{
    char text[] = "to be or not";

    printf("spaces = %d\n", count_space(text));
    printf("spaces = %d\n", count_space("a b c d"));
    reverse(text);
    printf("%s\n", text);
    return 0;
}
```

```text
spaces = 3
spaces = 3
ton ro eb ot
```

`count_space`의 `s++`는 매개변수 `s`, 즉 인수로 받은 주소의 복사본을 다음 문자로 옮길 뿐이므로 호출한 쪽의 배열이나 포인터는 바뀌지 않는다. `const char*` 매개변수에는 문자 배열과 문자열 리터럴을 모두 넘길 수 있다. `reverse`는 양 끝의 인덱스 `i`, `j`를 가운데로 좁히며 문자를 교환하는데, 7장 5.3절의 배열 뒤집기에서 원소 개수 대신 널 문자의 위치로 끝을 찾는 점만 다르다. 12문자의 `"to be or not"`에서는 6번 교환한 뒤 `i`가 6, `j`가 5가 되어 멈춘다.

`const`가 있는 쪽에서 없는 쪽으로는 전달할 수 없다. `const char *p`를 `char*` 매개변수에 넘기면 Clang은 `passing 'const char *' to parameter of type 'char *' discards qualifiers` 경고를 낸다. 반면 C에서 문자열 리터럴의 타입은 `const`가 붙지 않은 `char` 배열이므로, `reverse("abc")`처럼 리터럴을 `char*` 매개변수에 넘겨도 경고 없이 컴파일된다. 그러나 함수가 리터럴을 바꾸려 하면 6.1절의 정의되지 않은 동작이 되며, `char *p = "abc"; p[0] = 'X';`를 arm64 macOS에서 실행한 프로그램은 버스 오류(SIGBUS)로 비정상 종료되었다. 바꿀 문자열은 반드시 문자 배열로 넘긴다. 함수의 매개변수를 `const char *`로 선언해 두면 이런 실수를 컴파일러가 찾는다.

### 6.5 `char[]`와 `char*`의 저장 방식 비교

`char arr[] = "hello";`와 `const char *ptr = "hello";`는 같은 문자열을 다루는 것처럼 보이지만 메모리에 놓이는 방식이 다르다.

```c
char arr[] = "hello";
const char *ptr = "hello";
const char *ptr2 = "hello";

printf("arr: %p, sizeof %zu\n", (void *)arr, sizeof arr);
printf("ptr: %p, sizeof %zu, &ptr %p\n", (void *)ptr, sizeof ptr, (void *)&ptr);
printf("ptr == ptr2: %d, arr == ptr: %d\n", ptr == ptr2, arr == ptr);
arr[0] = 'j';
ptr = "world";
printf("%s %s\n", arr, ptr);
```

```text
arr: 0x16fd1eb04, sizeof 6
ptr: 0x1000e0590, sizeof 8, &ptr 0x16fd1eaf8
ptr == ptr2: 1, arr == ptr: 0
jello world
```

```text
local variable area (0x16f...)             string constant area (0x100...)
┌────────────────────────────┐           ┌────────────────────────────┐
│ arr: h  e  l  l  o  \0     │           │ "hello\0"  @0x1000e0590    │
├────────────────────────────┤           └────────────────────────────┘
│ ptr: 0x1000e0590 ──────────┼─────────────────▲
└────────────────────────────┘
arr: 6-byte array, modifiable              constant: used as read-only
ptr: 8-byte address
```

*그림 4. char 배열과 char 포인터가 놓이는 메모리 영역*

`arr`는 문자 6개(널 문자 포함)를 담는 배열이 지역 변수 영역에 만들어지고, 문자열 상수의 내용이 그 배열로 복사된다. 그래서 `sizeof arr`는 6이고 `arr[0] = 'j'`로 내용을 바꿀 수 있다. `ptr`은 8바이트 포인터 하나이며, 프로그램의 문자열 상수 영역에 있는 `"hello"`의 주소를 담는다. 출력에서 `arr`(0x16f...)와 `ptr`(0x100...)의 주소 범위가 다른 것이 두 영역이 다르다는 표시이다. `ptr`과 `ptr2`가 같은 주소를 가리키는 것은 컴파일러가 같은 내용의 문자열 상수를 하나로 합쳤기 때문이며, 이는 컴파일러가 정할 수 있는 동작이므로 의존하지 않는다. `ptr = "world";`는 포인터가 다른 상수를 가리키게 할 뿐 문자를 복사하지 않으며, 반대로 `arr = "world";`는 배열에 대입할 수 없으므로 컴파일 오류이다.

문자열 상수 영역은 프로그램이 실행되는 동안 계속 남아 있으므로, 함수가 `return "hello";`처럼 문자열 상수의 주소를 반환하는 것은 8장 3.5절의 지역 변수 주소와 달리 안전하다. 반면 함수 안의 `char arr[] = "hello";`는 지역 배열이므로 그 주소를 반환하면 댕글링 포인터가 된다.

문자 배열과 문자열 상수를 혼동한 실수 가운데 두 가지는 Clang이 경고로 알려 준다. 첫째, `char s[5] = "hello!";`처럼 배열보다 긴 문자열로 초기화하면 `initializer-string for char array is too long` 경고가 나고, 배열에는 앞의 5문자만 들어가 널 문자가 없는 문자 배열이 된다. 둘째, `if (t == "abc")`는 두 문자열의 내용이 아니라 배열 `t`의 주소와 문자열 상수의 주소를 비교하므로 Clang은 `result of comparison against a string literal is unspecified (use an explicit string comparison function instead)` 경고를 낸다. 이 비교는 6.5절의 `arr == ptr`처럼 내용이 같아도 거짓이 될 수 있으므로, 내용의 비교에는 반드시 `strcmp(t, "abc") == 0`을 쓴다. 두 경우 모두 컴파일은 되므로 경고를 읽지 않으면 실행 결과로만 알게 된다.

---

<br>

## 7. 문자열 배열

### 7.1 2차원 `char` 배열

입력된 문자열이나 실행 중에 바뀌는 문자열 여러 개를 저장하려면 2차원 문자 배열을 사용한다. 2차원 문자 배열은 **고정된 열 크기**로 여러 문자열을 저장하며, 널 문자를 포함한 문자열의 길이를 열 크기로, 문자열의 개수를 행 크기로 지정한다.

```c
char names[3][20] = {
    "Alice",
    "Bob",
    "Charlie"
};
```

**메모리 배치 (각 행은 20바이트):**

```text
names[0]: [ A ][ l ][ i ][ c ][ e ][ \0 ][ \0 ]...[ \0 ]  (20 bytes)
names[1]: [ B ][ o ][ b ][ \0 ][ \0 ][ \0 ][ \0 ]...[ \0 ]  (20 bytes)
names[2]: [ C ][ h ][ a ][ r ][ l ][ i ][ e ][ \0 ]...[ \0 ]  (20 bytes)
```

*그림 5. `char names[3][20]`의 메모리 배치*

각 문자열에는 행 인덱스만 써서 `names[i]`로 접근하고, `i`번째 문자열의 `j`번째 문자에는 `names[i][j]`처럼 행 인덱스와 열 인덱스를 모두 써서 접근한다.

```c
// Access and print each name
for (int i = 0; i < 3; i++) {
    printf("%s\n", names[i]);
}

// Modify a name
strcpy(names[1], "Bobby");   // OK: each row is a mutable char array
```

열 크기(20)는 **가장 긴 문자열 + 1** 이상이어야 하며, 모든 문자열이 이 고정된 열 크기 안에 들어가야 한다. 짧은 문자열은 나머지 공간을 낭비한다.

### 7.2 문자열 포인터 배열

변경되지 않는 문자열 여러 개를 저장하려면 문자열 포인터의 배열을 사용한다. `char*` 포인터 배열은 문자열 리터럴의 **주소**만 배열로 저장한다.

```c
const char *names[] = {
    "Alice",
    "Bob",
    "Charlie"
};
```

**메모리 배치 (읽기 전용 리터럴을 가리키는 포인터):**

```text
names[0] ──► "Alice\0"    (6 bytes in read-only memory)
names[1] ──► "Bob\0"      (4 bytes in read-only memory)
names[2] ──► "Charlie\0"  (8 bytes in read-only memory)
```

*그림 6. 문자열 리터럴을 가리키는 포인터 배열 names*

```c
// Access and print
for (int i = 0; i < 3; i++) {
    printf("%s\n", names[i]);
}

// Can change which string a pointer refers to
names[1] = "Bobby";   // OK: changes the pointer, not the string

// CANNOT modify the characters of the string literal
// names[1][0] = 'b';  // UNDEFINED BEHAVIOR: literals are read-only
```

**2차원 배열과 포인터 배열 비교:**

| 특성 | `char names[3][20]` | `const char *names[3]` |
|:----|:--------------------|:----------------------|
| 메모리 | 고정 60바이트 (3 x 20) | 포인터 + 리터럴 저장 (낭비 없음) |
| 문자열 수정 | 가능 (`strcpy`, `names[i][j] = ...`) | 불가 (리터럴은 읽기 전용) |
| 다른 문자열로 재대입 | 불가 (배열 이름은 상수) | 가능 (`names[i] = "New"`) |
| 공간 낭비 | 있음 (`'\0'`으로 패딩) | 없음 |
| 대표 용도 | 수정 가능한 문자열 테이블 | 읽기 전용 조회 테이블 |

*표 11. 2차원 문자 배열과 문자열 포인터 배열의 비교*

문자열을 **읽고 수정**해야 한다면 2차원 `char` 배열을 사용한다. **읽기 전용** 문자열 상수 목록만 필요하다면 `const char*` 포인터 배열이 효율적이다.

### 7.3 두 가지 문자열 배열의 메모리 비교

7.1절의 2차원 문자 배열과 7.2절의 문자열 포인터 배열에 같은 네 문자열을 저장하고 크기를 재면 다음과 같다.

```c
char a[4][20] = { "avengers", "iron man", "thor", "captain america" };
const char *p[4] = { "avengers", "iron man", "thor", "captain america" };
size_t lit = sizeof("avengers") + sizeof("iron man") + sizeof("thor") + sizeof("captain america");

printf("2D array: %zu bytes, row %zu\n", sizeof a, sizeof a[0]);
printf("pointer array: %zu bytes + literals %zu bytes\n", sizeof p, lit);
printf("%p %p\n", (void *)a[0], (void *)a[1]);
a[2][0] = 'T';
printf("%s %s\n", a[2], p[2]);
```

```text
2D array: 80 bytes, row 20
pointer array: 32 bytes + literals 39 bytes
0x16f4eaab8 0x16f4eaacc
Thor thor
```

```text
a (4 rows, 20 columns, 80 bytes)     p (4 pointers, 32 bytes)
a[0] avengers\0.......... (20)       p[0] ──► "avengers\0"         (9)
a[1] iron man\0.......... (20)       p[1] ──► "iron man\0"         (9)
a[2] thor\0.............. (20)       p[2] ──► "thor\0"             (5)
a[3] captain america\0... (20)       p[3] ──► "captain america\0"  (16)
```

*그림 7. 2차원 문자 배열과 문자열 포인터 배열의 메모리*

2차원 배열은 모든 행이 가장 긴 문자열에 맞춘 20바이트이므로, 짧은 `"thor"` 행에서는 15바이트가 비어 있다(그림의 `.`). `a[0]`과 `a[1]`의 주소 차이는 0xacc - 0xab8 = 0x14 = 20으로 한 행의 크기이다. 포인터 배열은 포인터 4개의 32바이트와 각 문자열 상수의 실제 길이 + 1을 더한 39바이트, 모두 71바이트로 더 작다. 대신 2차원 배열은 행마다 자기 문자 배열을 가지므로 `a[2][0] = 'T'`처럼 내용을 바꿀 수 있고, `const char *` 배열이 가리키는 문자열 상수는 바꿀 수 없다. 문자열을 입력받거나 고쳐야 하면 2차원 문자 배열을, 고정된 이름 목록처럼 읽기만 하면 문자열 포인터 배열을 쓴다.

---

<br>

## 개념 적용

**T/F 점검:**

| 문장 | 판단과 근거 |
|:-----|:-----|
| `"abc"`를 저장하려면 크기가 3인 `char` 배열이면 충분하다. | **F.** 널 문자까지 4바이트가 필요하다. |
| `strlen`은 널 문자를 포함한 길이를 반환한다. | **F.** `strlen`은 널 문자 앞까지의 문자 개수를 반환한다. |
| `char s[10];`을 선언한 뒤 `s = "hi";`로 문자열을 대입할 수 있다. | **F.** 배열은 대입할 수 없으므로 `strcpy(s, "hi");`를 쓴다. |
| `strcmp`가 0을 반환하면 두 문자열의 내용이 같다. | **T.** 같으면 0, 다르면 처음 다른 문자에 따라 음수나 양수이다. |
| ASCII에서 `strcmp("Zoo", "apple")`은 음수이다. | **T.** 대문자 `'Z'`(90)가 소문자 `'a'`(97)보다 작기 때문이다. |
| `strncpy(dest, src, n)`은 항상 널 문자로 끝나는 문자열을 만든다. | **F.** `src`가 n문자 이상이면 널 문자를 붙이지 않으므로 직접 넣어야 한다. |
| 문자열 리터럴을 가리키는 `char *p`로 `p[0] = 'X';`를 실행하면 정의되지 않은 동작이다. | **T.** 리터럴은 바꿀 수 없는 메모리에 있을 수 있으며, 실행 환경에 따라 비정상 종료된다. |
| `fgets`는 공간이 있으면 읽은 줄의 줄바꿈 문자도 배열에 저장한다. | **T.** 그래서 줄바꿈이 필요 없으면 `strcspn` 등으로 찾아 널 문자로 바꾼다. |
| `char arr[] = "hello";`와 `const char *p = "hello";`의 `sizeof`는 같다. | **F.** `sizeof arr`는 배열 전체인 6이고, `sizeof p`는 포인터의 크기인 8(64비트)이다. |
| `scanf("%s", s)`로 빈칸이 들어 있는 한 줄을 모두 읽을 수 있다. | **F.** `%s`는 공백 문자에서 멈추므로 한 줄 전체는 `fgets`로 읽는다. |
| `if (s == "abc")`는 `s`의 내용이 `"abc"`인지 검사한다. | **F.** 두 주소를 비교하므로 내용의 비교에는 `strcmp`를 쓴다. |
| 2차원 문자 배열은 모든 행이 같은 크기를 차지한다. | **T.** 짧은 문자열의 행에도 선언한 열의 크기만큼 메모리가 할당된다. |

---

<br>

## 요약

| 개념 | 핵심 요약 |
|:----|:---------|
| 문자 vs 문자열 | `'A'`는 `char`에 저장하면 1바이트이고 `"A"`는 `'A'`와 `'\0'`으로 이루어진 2바이트이며, 문자열은 널 종료된다. |
| `char` 배열 초기화 | `char s[10] = "abc"`는 나머지를 `'\0'`으로 채우고, `char s[] = "abc"`는 크기를 4로 자동 설정한다. |
| 배열 대입 | 선언 후 `str = "xyz"`는 허용되지 않으므로 `strcpy()`를 사용한다. |
| `strlen` | `'\0'`을 제외한 길이를 `size_t`로 반환하며, 배열 크기를 주는 `sizeof`와 다르다. |
| `strcpy` / `strncpy` | 문자열을 복사하며, `strcpy`는 경계 검사를 하지 않아 버퍼 오버플로의 위험이 있다. |
| `strcmp` / `strncmp` | 같으면 0, 사전순으로 뒤이면 양수, 앞이면 음수를 반환하며, 문자열을 `==`로 비교하면 안 된다. |
| `strcat` / `strncat` | 문자열을 이어붙이며, 대상 배열에 충분한 공간이 있어야 한다. |
| `strchr` / `strstr` | 문자나 부분 문자열을 검색하여 찾은 위치의 포인터 또는 `NULL`을 반환한다. |
| `strtok` | 구분 문자로 문자열을 분할하며, 원본을 수정하고 첫 호출 이후에는 `NULL`을 전달한다. |
| `isalpha`, `isdigit`, ... | `<ctype.h>`의 분류 함수로, 참이면 0이 아닌 값을 반환한다. |
| `toupper` / `tolower` | 대소문자를 변환하며, 영문자가 아니면 그대로 반환한다. |
| `scanf("%s", ...)` | 공백에서 멈추어 한 단어를 읽으며, 배열에는 `&`가 필요 없다. |
| `fgets` | `'\n'`을 포함하여 한 줄을 읽으며, 크기 제한이 있어 안전하다. |
| `puts` | 문자열을 출력하고 개행을 자동으로 추가한다. |
| `atoi` / `atof` / `atol` | 문자열을 각각 `int`, `double`, `long`으로 변환한다. |
| `sscanf` / `sprintf` | 서식 지정자로 문자열에서 읽거나 문자열에 쓴다. |
| `char*` 포인터 | 문자열 리터럴(읽기 전용 메모리)을 가리킬 수 있지만 그 내용을 수정하면 안 되며, 주로 문자 배열을 가리키는 데 쓴다. |
| `const char*` | 문자열이 읽기 전용임을 명시하여 실수로 인한 수정을 막는다. |
| 2차원 `char` 배열 | 행의 크기가 고정되어 수정할 수 있지만, 짧은 문자열은 공간을 낭비한다. |
| `char*` 포인터 배열 | 공간 낭비 없이 유연하지만, 리터럴을 가리키면 문자열은 읽기 전용이다. |
| 널 문자를 이용한 처리 | 문자열 반복은 `s[i] != '\0'`까지 진행하며, 배열의 크기가 아니라 널 문자가 끝을 정한다. |
| `strcmp`의 비교 | 처음 다른 문자의 코드로 부호를 정하며, 짧은 문자열은 `'\0'` 때문에 앞서고 ASCII에서 대문자가 소문자보다 앞선다. |
| 문자열 맞바꾸기 | 배열은 `=`로 대입할 수 없으므로 임시 배열과 `strcpy` 세 번으로 맞바꾸며, 세 배열 모두 충분히 커야 한다. |
| 문자열 매개변수 | 읽기만 하면 `const char*`, 바꾸면 `char*`로 받고, 함수 안에서 포인터를 옮겨도 호출한 쪽은 바뀌지 않는다. |
| 문자열 함수의 직접 구현 | `strlen`은 널 문자까지 센 칸 수, `strcpy`는 널 문자까지의 복사, `strcat`은 널 문자 자리부터의 복사이며 모두 대상의 크기를 모른다. |
| 문자열 입력의 문제 | `%s`는 공백에서 멈추고, `scanf` 뒤에 남은 `'\n'`은 다음 `fgets`가 읽으므로 줄의 나머지를 버린 뒤 읽는다. |
| `char[]`와 `char*` | 배열은 지역 영역에 복사본을 만들어 수정할 수 있고, 포인터는 문자열 상수 영역의 주소만 담는다. |
| 두 문자열 배열의 메모리 | 2차원 문자 배열은 행마다 같은 크기를 차지해 수정할 수 있고, 포인터 배열은 포인터와 실제 길이만큼의 상수로 더 작지만 내용을 바꿀 수 없다. |

---

<br>

## 점검 문제

1. **배열 크기와 길이:** `char s[10] = "abc";`와 `char t[] = "abc";`에 대해 `strlen(s)`, `sizeof(s)`, `sizeof(t)`의 값을 구하라.

   <details>
   <summary>정답</summary>

   `strlen(s)`는 널 문자 앞의 문자 수이므로 3, `sizeof(s)`는 선언한 배열 크기이므로 10이다. `t`는 크기를 생략했으므로 문자열 길이 + 1인 4바이트 배열이 되어 `sizeof(t)`는 4이다.

   </details>

2. **문자열 비교:** `strcmp("apple", "apricot")`의 반환값의 부호를 구하고 이유를 쓰라.

   <details>
   <summary>정답</summary>

   음수이다. 두 문자열은 처음 두 문자 `a`, `p`가 같고, 세 번째 문자에서 `'p'`(112)와 `'r'`(114)이 처음으로 달라진다. `'p'`가 `'r'`보다 작으므로 `"apple"`이 사전순으로 앞이다. 표준은 부호만 정하므로 값이 -1이라고 단정할 수는 없다.

   </details>

3. **`fgets`의 개행 문자:** `char line[10];`에 `fgets(line, 10, stdin)`으로 `Hi`를 입력하고 Enter를 눌렀다. `strlen(line)`은 얼마이며, 개행 문자를 지우려면 어떻게 하는가?

   <details>
   <summary>정답</summary>

   `line`에는 `"Hi\n"`이 저장되므로 `strlen(line)`은 3이다. `fgets`는 개행 문자를 포함하여 저장하기 때문이다. `size_t len = strlen(line);`로 길이를 구한 뒤 `len > 0`이고 `line[len - 1] == '\n'`이면 `line[len - 1] = '\0';`으로 지운다. `line[strcspn(line, "\n")] = '\0';`도 같은 일을 한다.

   </details>

4. **포인터와 배열:** `char *p = "Hello"; p[0] = 'h';`와 `char a[] = "Hello"; a[0] = 'h';`의 차이를 설명하라.

   <details>
   <summary>정답</summary>

   `p`는 읽기 전용 메모리에 있는 문자열 리터럴을 가리키므로 `p[0] = 'h'`는 미정의 동작이며 일반적으로 실행 중에 프로그램이 비정상 종료된다. `a`는 리터럴의 내용을 복사한 수정 가능한 문자 배열이므로 `a[0] = 'h'`는 정상적으로 동작하여 `a`가 `"hello"`가 된다. 리터럴을 가리킬 때 `const char *p`로 선언하면 이런 실수를 컴파일 단계에서 막을 수 있다.

   </details>

5. **`strtok`과 원본:** `char d[] = "2024-05-28";`에 `strtok(d, "-")`와 `strtok(NULL, "-")`를 차례로 호출하면 어떤 토큰들이 나오며, 토큰을 모두 얻은 뒤 `printf("%s", d)`는 무엇을 출력하는가?

   <details>
   <summary>정답</summary>

   토큰은 `"2024"`, `"05"`, `"28"`의 순서로 나오고, 그다음 호출은 `NULL`을 반환한다. `strtok`이 구분 문자 `'-'`를 `'\0'`으로 바꾸므로 `d`의 첫 문자열은 `"2024"`에서 끝나고, `printf("%s", d)`는 `2024`를 출력한다.

   </details>

6. **`strcmp`의 부호:** `strcmp("cat", "car")`, `strcmp("car", "cart")`, `strcmp("Car", "car")`의 부호를 각각 쓰고 이유를 설명하라.

   <details>
   <summary>정답</summary>

   첫째는 인덱스 2에서 `'t'`(116) > `'r'`(114)이므로 양수이다. 둘째는 `"car"`가 먼저 끝나 인덱스 3에서 `'\0'`(0) < `'t'`(116)이므로 음수이다. 셋째는 인덱스 0에서 `'C'`(67) < `'c'`(99)이므로 음수이다.

   </details>

7. **널 문자 반복:** `char w[10] = "level";`에 대해 `for (i = 0; w[i] != '\0'; i++)`의 본체는 몇 번 실행되는가? 이 반복으로 `w`가 앞뒤가 같은 문자열(회문)인지 판단하는 방법을 쓰라.

   <details>
   <summary>정답</summary>

   `"level"`은 5문자이므로 본체는 5번 실행되고 반복이 끝난 뒤 `i`는 5이다. 이 반복으로 길이 n을 구한 뒤, `k`를 0부터 n / 2 - 1까지 움직이며 `w[k]`와 `w[n - 1 - k]`를 비교하여 모두 같으면 회문이다. `"level"`은 (`l`, `l`), (`e`, `e`)가 같으므로 회문이다.

   </details>

8. **문자열 매개변수:** `void shout(char *s)`가 문자열의 모든 소문자를 대문자로 바꾼다. `shout(name)`(`char name[] = "kim";`)과 `shout("kim")`의 차이를 설명하라.

   <details>
   <summary>정답</summary>

   `name`은 문자 배열이므로 함수가 원소를 바꿀 수 있고, 호출 뒤 `name`은 `"KIM"`이 된다. `"kim"`은 문자열 리터럴이므로 C에서는 경고 없이 컴파일되지만, 함수가 그 내용을 바꾸려 하면 정의되지 않은 동작이며 일반적으로 프로그램이 비정상 종료된다.

   </details>
