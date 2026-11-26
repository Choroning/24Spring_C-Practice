# 9장 연습 문제 — 문자열

[레포지토리 안내](../../README.ko.md) | [English](Exercises.md) | [한국어](Exercises.ko.md)

> **최종 수정일:** 2026-11-27
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

**문제:** 문자열을 다루는 함수를 직접 작성하면서 문자열과 포인터의 관계를 익힌다. 아래의 함수를 정의하여 예시 코드를 완성하라.

**프로그램 요구사항:**

1. 아래 제시된 함수의 원형을 변경할 수 없으며, 입출력 함수를 제외하고 문자열을 다루는 어떠한 라이브러리 함수도 사용할 수 없다.
   모든 문자열 함수는 널 문자를 기준으로 연산을 수행한다.

2. `int my_strlen(const char *p);`
   문자 배열 또는 문자열 상수(이하 문자열)를 전달받아 문자열의 길이를 반환하는 함수이다.
   단, 널 문자는 길이에 포함하지 않는다.

3. `void my_strcpy(char *p1, const char *p2);`
   두 문자열을 전달받아 두 번째 문자열을 첫 번째 문자열에 복사하는 함수이다.

4. `int my_strcmp(const char *p1, const char *p2);`
   전달받은 두 문자열을 비교하여 같으면 0을 반환하고, 다르면 두 문자열의 ASCII 값을 비교한 결과를 반환한다.
   왼쪽 문자열의 ASCII 값이 작으면 -1, 크면 1을 반환하며, `strcmp()`와 같은 기능을 하도록 작성한다.

5. `void makeUpper(char p[]);`
   문자 배열을 전달받아 소문자를 대문자로 변환하는 함수이다.
   소문자 이외의 문자는 변환되지 않아야 하며, 포인터의 증가 연산을 이용해 구현해야 한다.

6. `void makeReverse(char p[]);`
   문자 배열을 전달받아 역순으로 변환하는 함수이다.
   단, 함수 안에서 임시 배열을 선언하여 사용할 수 없다.

7. `void strSwap(char *p1, char *p2);`
   전달받은 두 문자열의 내용을 서로 교환하는 함수이다.
   단, 함수 안에서 임시 배열을 선언하여 사용할 수 없으며, 포인터의 산술 연산을 이용해 구현해야 한다.

8. `void swap(char *a, char *b);`
   두 문자의 내용을 교환하는 함수이며, `makeReverse()` 함수와 `strSwap()` 함수에서 호출된다.

**예시 코드:** 함수의 선언과 정의를 추가하여 완성한다.

```c wide-ok
#include <stdio.h>
#define SIZE 64

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
   printf("\nstr1을 대문자로 변환 = %s\n", str2);

   makeReverse(str2);
   printf("\nstr2의 역순 = %s\n", str2);

   my_strcpy(str3, str1);

   if (!my_strcmp(str1, str3))
      printf("\n%s == %s\n", str1, str3);
   if (result = my_strcmp("abc", "abcd"))
      printf("\nstrcmp(\"abc\", \"abcd\") = %d\n", result);
   if (result = my_strcmp("C++", "C"))
      printf("\nstrcmp(\"C++\", \"C\") = %d\n\n", result);
   
   my_strcpy(str3, "C is powerful");
   printf("------ strSwap() 함수 호출 전 ------ \n");
   printf("str1 = %s\nstr3 = %s\n", str1, str3);
   strSwap(str1, str3);
   printf("------ 첫 번째 strSwap() 함수 호출 후 ------\n");
   printf("str1 = %s\nstr3 = %s\n", str1, str3);
   strSwap(str1, str3);
   printf("------ 두 번째 strSwap() 함수 호출 후 ------\n");
   printf("str1 = %s\nstr3 = %s\n", str1, str3);

   return 0;
}
```

**실행 예시:**

```text wide-ok
문자열(str1) 입력: c is fun!!

str1의 길이: 10

str2 = c is fun!!

str1을 대문자로 변환 = C IS FUN!!

str2의 역순 = !!NUF SI C

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

Program ended with exit code: 0
```

**[풀이](Solutions.ko.md#연습-문제-1-문자열-조작)**

---

<br>

## 연습 문제 2: 문자열 포인터 수식의 값

**교재 문항:** 9장 연습 문제 4번

**문제:** `const char *p = "summer";`이고 문자열 `"summer"`가 `0x8000`번지에 있다고 가정한다. 다음 각 문장이 출력하는 값을 쓰라.

- (1) `printf("%p", p);`
- (2) `printf("%p", p + 2);`
- (3) `printf("%c", *p);`
- (4) `printf("%c", p[1]);`
- (5) `printf("%s", p + 1);`

**[풀이](Solutions.ko.md#연습-문제-2-문자열-포인터-수식의-값)**

---

<br>

## 연습 문제 3: 문자열 배열 수식의 값

**교재 문항:** 9장 연습 문제 10번

**문제:** `char movies[][20] = { "avengers", "iron man", "thor", "captain america" };`에 대하여 다음 각 수식의 값을 쓰라.

- (1) `movies[0]`
- (2) `sizeof(movies) / sizeof(movies[0])`
- (3) `movies[0][1]`
- (4) `movies[1][0]`
- (5) `movies[2]`
- (6) `sizeof(movies[0]) / sizeof(movies[0][0])`
- (7) `sizeof(movies) / sizeof(movies[0][0])`
- (8) `*movies[3]`

**[풀이](Solutions.ko.md#연습-문제-3-문자열-배열-수식의-값)**

---

<br>

## 연습 문제 4: `strcpy`의 잘못된 사용

**교재 문항:** 9장 연습 문제 2번

**문제:** 다음 코드 가운데 `strcpy`를 잘못 사용한 것을 모두 고르고, 각각 어떤 문제가 생기는지 쓰라.

- ① `char s1[10]; strcpy(s1, "abc");`
- ② `char s2[10] = "x"; strcpy("apple", s2);`
- ③ `char s3[3]; strcpy(s3, "good job");`
- ④ `char s4[] = "xyz", s5[4]; strcpy(s5, s4);`
- ⑤ `strcpy("hello", "bye");`

**[풀이](Solutions.ko.md#연습-문제-4-strcpy의-잘못된-사용)**

---

<br>

## 연습 문제 5: 이니셜 출력

**교재 문항:** 9장 프로그래밍 과제 2번

**문제:** 영문 이름을 한 줄로 입력받아 각 단어의 첫 글자를 대문자로 모아 이니셜을 출력하는 프로그램을 작성하라. 단어는 빈칸으로 구분하며, 앞뒤나 단어 사이에 빈칸이 여러 개 있어도 올바르게 동작해야 한다. 입력은 `fgets`로 읽는다.

**실행 예시:**

```text
name? Son Heung Min
initials: SHM
name?   ada   lovelace
initials: AL
```

**[풀이](Solutions.ko.md#연습-문제-5-이니셜-출력)**

---

<br>

## 연습 문제 6: 대소문자를 구분하지 않는 문자열 비교

**교재 문항:** 9장 프로그래밍 과제 6번

**문제:** 대소문자를 구분하지 않고 두 문자열을 비교하는 함수 `int strcmp_ic(const char *lhs, const char *rhs)`를 작성하라. 반환값의 부호는 `strcmp`와 같아서, `lhs`가 앞서면 음수, 같으면 0, 뒤에 오면 양수이다. `strcmp`를 쓰지 않고 두 문자열을 한 문자씩 직접 비교해야 한다. 다음 세 비교의 결과가 모두 1(참)로 출력되어야 한다.

```c
printf("%d\n", strcmp_ic("Avengers", "avengers") == 0);
printf("%d\n", strcmp_ic("Thor", "thanos") > 0);
printf("%d\n", strcmp_ic("iron", "Iron Man") < 0);
```

**[풀이](Solutions.ko.md#연습-문제-6-대소문자를-구분하지-않는-문자열-비교)**

---

<br>

## 연습 문제 7: 단어 수 세기

**문제:** 문자열에 들어 있는 단어의 수를 반환하는 함수 `int count_words(const char *s)`를 작성하라. 단어는 빈칸, 탭, 줄바꿈이 아닌 문자가 이어진 부분이며, 공백 문자가 여러 개 이어지거나 문자열의 앞뒤에 있어도 단어를 정확히 세야 한다.

**실행 예시:** 세 문자열 `"to be or not to be"`, `"   leading and   double  spaces  "`, `""`에 대한 결과이다.

```text
6
4
0
```

**[풀이](Solutions.ko.md#연습-문제-7-단어-수-세기)**
