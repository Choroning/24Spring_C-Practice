# 9장 연습 문제 — 문자열

[레포지토리 안내](../../README.ko.md) | [English](Exercises.md) | [한국어](Exercises.ko.md)

> **최종 수정일:** 2026-10-19

**문항 출처:** 임영희 교수, 컴퓨터언어Ⅰ (DCCS101-04)

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

```c
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

```text
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
