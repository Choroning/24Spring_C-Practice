# 9장 연습 문제 풀이 — 문자열

[레포지토리 안내](../../README.ko.md) | [English](Solutions.md) | [한국어](Solutions.ko.md)

> **최종 수정일:** 2026-10-27

**문항 출처:** 임영희 교수, 컴퓨터언어Ⅰ (DCCS101-04)

---

<br>

## 목차

- [연습 문제 1: 문자열 조작](#연습-문제-1-문자열-조작)

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
