# Chapter 9. 문자열 실습

**문항 출처:** *임영희 교수, 컴퓨터언어Ⅰ 교수자 (DCCS101-04)* <br>
**Source:** *Prof. Younghee&nbsp;Im, Instructor of COMPUTER LANGUAGE Ⅰ (DCCS101-04)*

---

## Q1. 문자열 조작

문자열을 다루는 다양한 함수를 정의하여 예시 코드를 완성하시오.

<br>**프로그램 요구사항**

1. 아래 제시된 함수의 원형을 변경할 수 없으며, 입출력 함수를 제외하고 문자열을 다루는 어떠한 라이브러리 함수도 사용할 수 없다.

2. `int my_strlen(const char *p);`<br>
   문자 배열 또는 문자열 상수(이하 문자열)를 전달받아 문자열의 길이를 반환하는 함수<br>
   단, 널 문자는 길이에 포함하지 않는다.

3. `void my_strcpy(char *p1, const char *p2);`<br>
   두 문자열을 전달받아 두 번째 문자열을 첫 번째 문자열에 복사하는 함수

4. `int my_strcmp(const char *p1, const char *p2);`<br>
   전달받은 두 문자열을 비교하여 같으면 0, 다를 경우 두 문자열의 ASCII 값을 비교하여 반환한다.<br>
   왼쪽 문자열의 ASCII 값이 작으면 -1, 크면 1을 반환하며 이는 `strcmp()`와 동일한 기능이다.

5. `void makeUpper(char p[]);`<br>
   문자 배열을 전달받아 소문자를 대문자로 변환하는 함수<br>
   소문자 이외의 문자는 변환되지 않아야 하며, 포인터의 증가연산을 이용해 구현해야 한다.

6. `void makeReverse(char p[]);`<br>
   문자 배열을 전달받아 역으로 변환해주는 함수<br>
   단, 함수 내에서 임시 배열을 선언하여 사용할 수 없다.

7. `void strSwap(char *p1, char *p2);`<br>
   전달받은 두 문자열의 내용을 서로 교환하는 함수<br>
   단, 함수 내에서 임시 배열을 선언하여 사용할 수 없으며, 포인터의 산술 연산을 이용해 구현해야 한다.


<br>**예시 코드**

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
   if (result == my_strcmp("abc", "abcd"))
      printf("\nstrcmp(\"abc\", \"abcd\") = %d\n", result);
   if (result == my_strcmp("C++", "C"))
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


<br>**실행 예시**

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

---