# 9장 연습 문제 풀이 — 문자열

[레포지토리 안내](../../README.ko.md) | [English](Solutions.md) | [한국어](Solutions.ko.md)

> **최종 수정일:** 2026-11-19
>
> Warming-Up C Programming, 천정아, Ch 9

**문항 출처:** 연습 문제 1은 임영희 교수, 컴퓨터언어Ⅰ (DCCS101-04)

---

<br>

## 목차

- [연습 문제 1: 문자열 조작](#연습-문제-1-문자열-조작)
- [연습 문제 2: 문자열 포인터 수식의 값](#연습-문제-2-문자열-포인터-수식의-값)
- [연습 문제 3: 문자열 배열 수식의 값](#연습-문제-3-문자열-배열-수식의-값)
- [연습 문제 4: `strcpy`의 잘못된 사용](#연습-문제-4-strcpy의-잘못된-사용)
- [연습 문제 5: 이니셜 출력](#연습-문제-5-이니셜-출력)
- [연습 문제 6: 대소문자를 구분하지 않는 문자열 비교](#연습-문제-6-대소문자를-구분하지-않는-문자열-비교)
- [연습 문제 7: 단어 수 세기](#연습-문제-7-단어-수-세기)

---

<br>

## 연습 문제 1: 문자열 조작

**문제:** 문자열 라이브러리 함수를 쓰지 않고 `my_strlen()`, `my_strcpy()`, `my_strcmp()`, `makeUpper()`, `makeReverse()`, `strSwap()`, `swap()`을 직접 정의하라. `makeUpper()`는 포인터의 증가 연산으로, `strSwap()`은 포인터의 산술 연산으로 구현하고, `makeReverse()`와 `strSwap()`은 임시 배열 없이 `swap()`으로 문자를 교환한다. 문제 전문과 실행 예시는 [연습 문제 1](Exercises.ko.md#연습-문제-1-문자열-조작)에 있다.

### 풀이

**접근 방법:** 모든 함수는 널 문자 `'\0'`을 문자열의 끝으로 보고 동작한다([9장 1.1절](Concepts_Lecture.ko.md#11-문자와-문자열의-차이)). 문자열을 읽기만 하는 매개변수는 `const char*`로, 내용을 바꾸는 매개변수는 `char*`로 받는다([9장 6.3절](Concepts_Lecture.ko.md#63-사용-지침)).

- **`my_strlen()`:** 인덱스 `len`을 0부터 늘리면서 `p[len]`이 널 문자가 될 때까지 센다. 널 문자는 세지 않으므로 반복이 끝났을 때의 `len`이 길이이다.
- **`my_strcpy()`:** `p2[i]`가 널 문자가 아닌 동안 한 문자씩 `p1[i]`에 복사하고, 마지막에 `p1[i] = '\0'`으로 널 문자를 붙여 복사한 문자열을 끝맺는다.
- **`my_strcmp()`:** 두 문자열의 길이를 구하여 긴 쪽의 길이만큼 같은 위치의 문자를 비교한다. 처음으로 다른 문자가 나오면 `p1`의 문자가 크면 1, 작으면 -1을 반환하고, 끝까지 같으면 0을 반환한다. 짧은 문자열의 끝에서는 널 문자(0)가 상대 문자와 비교되므로, `"abc"`와 `"abcd"`는 인덱스 3에서 `'\0' < 'd'`가 되어 -1, `"C++"`와 `"C"`는 인덱스 1에서 `'+' > '\0'`이 되어 1이다. 차이가 나는 위치에서 바로 반환하므로 짧은 문자열의 널 문자 뒤를 읽는 일은 없다.
- **`makeUpper()`:** 매개변수 `p`를 증가시키면서 `*p`가 `'a'`부터 `'z'` 사이이면 32를 뺀다. ASCII에서 소문자와 대문자의 코드 차이가 `'a' - 'A' = 32`이기 때문이다.
- **`makeReverse()`:** 길이가 `size`일 때 `i = 0`부터 `size / 2 - 1`까지 `p[i]`와 `p[size - i - 1]`을 `swap()`으로 교환한다. 가운데까지만 교환하므로 길이가 홀수이면 가운데 문자는 그대로 남는다.
- **`strSwap()`:** 두 문자열 중 긴 쪽의 길이 `j`를 구하고, 인덱스 0부터 `j`까지(긴 문자열의 널 문자 포함) 같은 위치의 문자를 `swap()`으로 교환한다. 긴 문자열의 널 문자까지 교환하므로 두 배열의 문자열이 모두 온전히 바뀐다.
- **`swap()`:** 두 문자의 주소를 받아 임시 변수로 교환한다.

**코드:** [Lab_Q1.c](../../Coursework/Lab09_Strings/Lab_Q1.c)

```c
/**
 * @file    A10104-1_C09Q1.c
 * @brief   Q1. 문자열 조작
 * @author  박철원 (Cheolwon Park)
 * @date    2024-05-28
 * 
 * @note    소스 코드에 사용된 gets_s는 Visual Studio 이외의
 *          IDE에서 실행이 불가할 수 있음에 주의하시기 바랍니다.
 */

 #include <stdio.h>
#define SIZE 64

int my_strlen(const char* p);
void my_strcpy(char* p1, const char* p2);
int my_strcmp(const char* p1, const char* p2);
void makeUpper(char p[]);
void makeReverse(char p[]);
void strSwap(char* p1, char* p2);
void swap(char* a, char* b);

int main()
{
    char str1[SIZE], str2[SIZE], str3[SIZE];
    int result;

    printf("문자열(str1) 입력: ");
    gets_s(str1, SIZE);
    printf("\nstr1의 길이: %d\n", my_strlen(str1));

    my_strcpy(str2, str1);
    printf("\nstr2 = %s\n", str2);

    makeUpper(str2);
    printf("\nstr2를 대문자로 변환 = %s\n", str2);

    makeReverse(str2);
    printf("\nstr2를 역순으로 변환 = %s\n", str2);

    my_strcpy(str3, str1);
    if (!my_strcmp(str1, str3))
        printf("\n%s == %s\n", str1, str3);
    if (result = my_strcmp("abc", "abcd"))
        printf("\nstrcmp(\"abc\", \"abcd\") = %d\n", result);
    if (result = my_strcmp("C++", "C"))
        printf("\nstrcmp(\"C++\", \"C\") = %d\n\n", result);

    my_strcpy(str3, "C is powerful");

    printf("------ strSwap() 함수 호출 전 ------\n");
    printf("str1 = %s\nstr3 = %s\n", str1, str3);

    strSwap(str1, str3);
    printf("------ 첫 번째 strSwap() 함수 호출 후 ------\n");
    printf("str1 = %s\nstr3 = %s\n", str1, str3);

    strSwap(str1, str3);
    printf("------ 두 번째 strSwap() 함수 호출 후 ------\n");
    printf("str1 = %s\nstr3 = %s\n", str1, str3);

    return 0;
}

int my_strlen(const char* p)
{
    int len = 0;
    while (p[len])
        len++;
    return len;
}

void my_strcpy(char* p1, const char* p2)
{
    int i = 0;
    while (p2[i]) {
        p1[i] = p2[i];
        i++;
    }
    p1[i] = '\0';
}

int my_strcmp(const char* p1, const char* p2)
{
    int i, j, len1 = 0, len2 = 0;
    while (p1[len1]) len1++;
    while (p2[len2]) len2++;
    j = (len1 >= len2) ? len1 : len2;

    for (i = 0; i < j; i++) {
        if (p1[i] > p2[i]) return 1;
        else if (p1[i] < p2[i]) return -1;
    }
    return 0;
}

void makeUpper(char p[])
{
    while (*p) {
        if (*p >= 'a' && *p <= 'z')
            *p -= 32;
        p++;
    }
}

void makeReverse(char p[])
{
    int i, size = my_strlen(p);
    for (i = 0; i < size / 2; i++) {
        swap(&p[i], &p[size - i - 1]);
    }
}

void strSwap(char* p1, char* p2)
{
    int i, j, len1 = my_strlen(p1), len2 = my_strlen(p2);
    j = len1 > len2 ? len1 : len2;
    for (i = 0; i <= j; i++) {
        swap(&p1[i], &p2[i]);
    }
}

void swap(char* a, char* b)
{
    char temp = *a;
    *a = *b;
    *b = temp;
}
```

**실행 결과:** `gets_s`는 C11 표준에서 선택 사항인 부록 K에 속하여 Visual Studio는 제공하지만 gcc와 clang의 표준 라이브러리에는 없다([9장 4.2절](Concepts_Lecture.ko.md#42-fgets--gets_s)). gcc나 clang에서 실행하려면 한 줄을 읽고 개행 문자를 버리는 같은 동작의 함수를 헤더(예: `gets_s_compat.h`)에 정의하고, `gcc -std=c99 -Wall -include gets_s_compat.h Lab_Q1.c`처럼 `-include` 옵션으로 넣는다.

```c
#include <stdio.h>
#include <string.h>

static char *gets_s(char *s, size_t n) {
    if (!fgets(s, (int)n, stdin)) return NULL;
    s[strcspn(s, "\n")] = '\0';   // 개행 문자를 버림
    return s;
}
```

이렇게 컴파일하면 조건식 안의 대입 `if (result = my_strcmp(...))`에 대해 괄호로 의도를 밝히라는 경고(`-Wparentheses`) 두 개가 나온다. 실행 예시의 문자열을 입력한 결과는 다음과 같다.

```text
문자열(str1) 입력: c is fun!!

str1의 길이: 10

str2 = c is fun!!

str2를 대문자로 변환 = C IS FUN!!

str2를 역순으로 변환 = !!NUF SI C

c is fun!! == c is fun!!

strcmp("abc", "abcd") = -1

strcmp("C++", "C") = 1

------ strSwap() 함수 호출 전 ------
str1 = c is fun!!
str3 = C is powerful
------ 첫 번째 strSwap() 함수 호출 후 ------
str1 = C is powerful
str3 = c is fun!!
------ 두 번째 strSwap() 함수 호출 후 ------
str1 = c is fun!!
str3 = C is powerful
```

안내문 두 줄이 실행 예시와 다른데, 대문자 변환 결과는 `str1을 대문자로 변환` 대신 `str2를 대문자로 변환`으로, 역순 결과는 `str2의 역순` 대신 `str2를 역순으로 변환`으로 출력한다. 대문자로 바꾸는 대상이 `str2`이므로 코드의 안내문이 실제 동작에 더 맞다. 실행 예시의 마지막 줄 `Program ended with exit code: 0`은 Xcode 콘솔이 덧붙이는 종료 메시지이다.

> **참고:** **요구사항과의 차이.** 요구사항은 `strSwap()`을 포인터의 산술 연산으로 구현하도록 했지만, 이 코드는 `&p1[i]`, `&p2[i]`처럼 첨자 표기로 주소를 구한다. `&p1[i]`는 `p1 + i`와 같은 주소이므로 동작은 같으며, 요구사항의 표기를 따르려면 `swap(p1 + i, p2 + i);`로 쓴다([8장 2.2절](../Ch08_Pointers/Concepts_Lecture.ko.md#22-포인터를-배열처럼-사용)). 또한 조건식 안의 대입은 `if ((result = my_strcmp("abc", "abcd")) != 0)`처럼 쓰면 의도가 분명해지고 경고도 사라진다.

> **주의:** `my_strcmp()`는 `char` 값을 그대로 비교한다. `char`가 부호 있는 형인 시스템에서 한글 UTF-8처럼 0x80 이상의 바이트는 음수가 되므로, 이런 문자가 섞이면 바이트를 `unsigned char`로 비교하는 표준 `strcmp()`와 결과의 부호가 다를 수 있다. `strSwap()`은 짧은 문자열 쪽 배열의 널 문자 뒤 위치까지 접근하므로, 두 배열이 모두 긴 문자열 + 1 이상의 크기여야 한다(이 프로그램은 두 배열이 모두 `SIZE` = 64바이트이다). 입력이 63글자를 넘으면 `gets_s`는 배열을 넘어서 쓰지 않고 오류로 처리하지만(Visual Studio에서는 잘못된 매개변수 처리기가 호출되어 기본적으로 프로그램이 종료된다), 다른 입력 함수로 바꿀 때는 입력이 배열 크기를 넘지 않는지 따로 확인해야 한다.

---

<br>

## 연습 문제 2: 문자열 포인터 수식의 값

**교재 문항:** 9장 연습 문제 4번

**문제:** `0x8000`번지의 `"summer"`를 가리키는 `const char *p`로 만든 다섯 수식의 출력값을 쓰라. 수식은 [연습 문제 2](Exercises.ko.md#연습-문제-2-문자열-포인터-수식의-값)에 있다.

### 풀이

**정답:** (1) `0x8000` (2) `0x8002` (3) `s` (4) `u` (5) `ummer`

**해설:** `p`는 첫 문자 `'s'`의 주소를 담으므로 (1)은 그 주소이다. `%p`가 주소를 어떤 모양으로 출력하는지는 구현이 정하며, 이 환경은 `0x`가 붙은 16진수로 출력한다. `char`는 1바이트이므로 (2) `p + 2`는 0x8000 + 2 = 0x8002이며 세 번째 문자 `'m'`의 주소이다. (3) `*p`는 첫 문자 `s`, (4) `p[1]`은 `*(p + 1)`이므로 두 번째 문자 `u`이다. (5) `%s`는 주어진 주소부터 널 문자까지 출력하므로 두 번째 문자부터의 `ummer`가 출력된다([9장 6.1절](Concepts_Lecture.ko.md#61-char-문자열-포인터)).

---

<br>

## 연습 문제 3: 문자열 배열 수식의 값

**교재 문항:** 9장 연습 문제 10번

**문제:** 2차원 문자 배열 `movies[][20]`에 대한 여덟 수식의 값을 쓰라. 수식은 [연습 문제 3](Exercises.ko.md#연습-문제-3-문자열-배열-수식의-값)에 있다.

### 풀이

**정답:** (1) `"avengers"` (2) 4 (3) `'v'` (4) `'i'` (5) `"thor"` (6) 20 (7) 80 (8) `'c'`

**해설:** 초기값이 4개이므로 행의 크기가 4로 정해져 `movies`는 4행 20열이고 전체 크기는 4 × 20 = 80바이트이다([9장 7.1절](Concepts_Lecture.ko.md#71-2차원-char-배열)). (1)과 (5)의 `movies[i]`는 i행, 즉 i번째 문자열이다. (2)는 전체 크기 80을 한 행의 크기 20으로 나눈 행의 개수 4이고, (6)은 한 행의 크기 20을 `char` 하나의 크기 1로 나눈 열의 개수 20이며, (7)은 전체 원소의 개수 80이다. (3)은 `"avengers"`의 두 번째 문자, (4)는 `"iron man"`의 첫 문자이다. (8) `*movies[3]`은 `[]`가 먼저 결합하여 `*(movies[3])`, 즉 `"captain america"`의 첫 문자 `'c'`이다. 다음은 같은 수식을 실제로 출력한 결과이다.

```text
avengers 4 v i thor
20 80 c
```

---

<br>

## 연습 문제 4: `strcpy`의 잘못된 사용

**교재 문항:** 9장 연습 문제 2번

**문제:** `strcpy`를 사용한 다섯 코드 가운데 잘못된 것을 고르고 각각의 문제를 쓰라. 보기는 [연습 문제 4](Exercises.ko.md#연습-문제-4-strcpy의-잘못된-사용)에 있다.

### 풀이

**정답:** ②, ③, ⑤

**해설:** `strcpy(dest, src)`는 `dest`가 가리키는 수정 가능한 배열에 `src`를 널 문자까지 복사하므로, `dest`는 문자 배열이어야 하고 `src`의 길이 + 1바이트 이상이어야 한다([9장 2.2절](Concepts_Lecture.ko.md#22-strcpy--strncpy)).

- ① `s1`은 10바이트이고 `"abc"`는 널 문자를 포함해 4바이트이므로 올바르다.
- ② 목적지가 문자열 리터럴이다. C에서 리터럴의 타입은 `const`가 없는 `char` 배열이어서 컴파일 경고가 나지 않을 수 있지만, 리터럴을 바꾸는 것은 정의되지 않은 동작이며 일반적으로 프로그램이 비정상 종료된다.
- ③ `"good job"`은 널 문자를 포함해 9바이트인데 `s3`은 3바이트이므로 버퍼 오버런이 일어난다. Clang은 `'strcpy' will always overflow; destination buffer has size 3, but the source string has length 9 (including NUL byte)` 경고를 낸다.
- ④ `s4`는 `"xyz"`로 초기화한 4바이트 배열이고 `s5`도 4바이트이므로 널 문자까지 남는 공간 없이 복사되어 올바르다.
- ⑤ ②와 같이 목적지가 리터럴이므로 잘못이다.

---

<br>

## 연습 문제 5: 이니셜 출력

**교재 문항:** 9장 프로그래밍 과제 2번

**문제:** 한 줄로 입력받은 영문 이름에서 각 단어의 첫 글자를 대문자로 모아 출력하고, 빈칸이 여러 개여도 올바르게 동작하게 하라. 실행 예시는 [연습 문제 5](Exercises.ko.md#연습-문제-5-이니셜-출력)에 있다.

### 풀이

**접근 방법:** "지금 단어가 시작될 자리인가"를 나타내는 변수 `at_start`를 둔다. 빈칸을 만나면 `at_start`를 1로 만들고, 빈칸이 아닌 문자를 만났을 때 `at_start`가 1이면 그 문자가 단어의 첫 글자이므로 이니셜에 더한 뒤 `at_start`를 0으로 만든다.

```c
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    char name[64], initials[16];
    int i, n = 0, at_start = 1;

    printf("name? ");
    if (fgets(name, sizeof(name), stdin) == NULL)
        return 1;
    name[strcspn(name, "\n")] = '\0';

    for (i = 0; name[i] != '\0'; i++) {
        if (name[i] == ' ') {
            at_start = 1;
        } else if (at_start) {
            initials[n++] = (char)toupper((unsigned char)name[i]);
            at_start = 0;
        }
    }
    initials[n] = '\0';
    printf("initials: %s\n", initials);
    return 0;
}
```

- `fgets`는 줄바꿈 문자까지 배열에 저장하므로, `strcspn(name, "\n")`으로 첫 `'\n'`의 위치를 구해 그 자리에 널 문자를 넣는다. 줄바꿈이 없으면 `strcspn`은 문자열의 길이를 반환하므로 원래의 널 문자 자리에 다시 널 문자를 넣을 뿐이다.
- `at_start`의 초기값이 1이므로 첫 단어의 첫 글자도 이니셜이 된다. 앞이나 단어 사이에 빈칸이 여러 개이면 `at_start`가 1로 여러 번 바뀔 뿐 결과는 같다.
- `toupper`에 넘기는 값은 `unsigned char`로 바꾸는데, `<ctype.h>`의 함수는 `EOF`와 `unsigned char`로 나타낼 수 있는 값만 받기 때문이다.
- 이니셜을 모은 뒤 `initials[n] = '\0'`으로 문자열을 끝내야 `%s`로 출력할 수 있다.

**실행 결과:**

```text
name? Son Heung Min
initials: SHM
name?   ada   lovelace
initials: AL
```

---

<br>

## 연습 문제 6: 대소문자를 구분하지 않는 문자열 비교

**교재 문항:** 9장 프로그래밍 과제 6번

**문제:** `strcmp`와 같은 부호 규칙을 따르되 대소문자를 구분하지 않는 `strcmp_ic`를 한 문자씩 비교하여 작성하라. 시험 코드는 [연습 문제 6](Exercises.ko.md#연습-문제-6-대소문자를-구분하지-않는-문자열-비교)에 있다.

### 풀이

**접근 방법:** 두 문자를 모두 소문자로 바꾸어 비교하고, 다르면 그 차를 반환한다. 한쪽 문자열이 먼저 끝나면 끝난 쪽의 `'\0'`(0)과 다른 쪽 문자의 차가 부호를 정한다.

```c
#include <stdio.h>
#include <ctype.h>

int strcmp_ic(const char *lhs, const char *rhs)
{
    int a, b;

    while (*lhs != '\0' && *rhs != '\0') {
        a = tolower((unsigned char)*lhs);
        b = tolower((unsigned char)*rhs);
        if (a != b)
            return a - b;
        lhs++;
        rhs++;
    }
    return tolower((unsigned char)*lhs) - tolower((unsigned char)*rhs);
}

int main(void)
{
    printf("%d\n", strcmp_ic("Avengers", "avengers") == 0);
    printf("%d\n", strcmp_ic("Thor", "thanos") > 0);
    printf("%d\n", strcmp_ic("iron", "Iron Man") < 0);
    return 0;
}
```

- `"Avengers"`와 `"avengers"`는 소문자로 바꾸면 모든 문자가 같고 두 문자열이 함께 끝나므로, 반복 뒤의 차는 0 - 0 = 0이다.
- `"Thor"`와 `"thanos"`는 세 번째 문자에서 `'o'`(111)와 `'a'`(97)가 달라 111 - 97 = 14인 양수를 반환한다.
- `"iron"`이 4문자 뒤에 끝나면 반복을 빠져나와 `'\0'`(0)과 `' '`(32)의 차 -32를 반환하므로 음수이다.

**실행 결과:**

```text
1
1
1
```

---

<br>

## 연습 문제 7: 단어 수 세기

**문제:** 공백 문자로 구분된 단어의 수를 반환하는 `count_words`를 작성하고, 공백이 이어지거나 앞뒤에 있는 경우도 정확히 세라. 실행 예시는 [연습 문제 7](Exercises.ko.md#연습-문제-7-단어-수-세기)에 있다.

### 풀이

**접근 방법:** 공백을 세어 1을 더하는 방법은 공백이 이어지거나 앞뒤에 있으면 틀린다. 대신 "지금 단어 안에 있는가"를 나타내는 변수 `in_word`를 두고, 공백이 아닌 문자를 만났는데 `in_word`가 0일 때, 즉 단어가 새로 시작될 때만 개수를 늘린다.

```c
#include <stdio.h>

int count_words(const char *s)
{
    int count = 0, in_word = 0;

    while (*s != '\0') {
        if (*s == ' ' || *s == '\t' || *s == '\n') {
            in_word = 0;
        } else if (!in_word) {
            in_word = 1;
            count++;
        }
        s++;
    }
    return count;
}

int main(void)
{
    printf("%d\n", count_words("to be or not to be"));
    printf("%d\n", count_words("   leading and   double  spaces  "));
    printf("%d\n", count_words(""));
    return 0;
}
```

두 번째 문자열에서 앞의 빈칸 3개 동안 `in_word`는 0에 머물고, `l`에서 단어가 시작되어 1이 된다. `leading` 뒤의 빈칸에서 0이 되고 `and`에서 2, 빈칸 3개 뒤의 `double`에서 3, `spaces`에서 4가 되며, 끝의 빈칸은 개수를 바꾸지 않는다. 빈 문자열은 반복이 한 번도 실행되지 않아 0을 반환한다. 이 방식은 상태를 나타내는 변수 하나로 입력을 한 번만 훑으며 처리하므로, 공백의 개수나 위치와 관계없이 단어 수를 정확히 센다.

**실행 결과:**

```text
6
4
0
```
