# 9장 실습 — 문자열과 문자열 포인터

[레포지토리 안내](../../README.ko.md) | [English](Concepts_Lab.md) | [한국어](Concepts_Lab.ko.md)

> **최종 수정일:** 2026-10-27
>
> 문제풀이 중심의 C언어 연습, 김용일 외, Ch 8, 9

> **학습 목표:**
> 1. 문자열 상수와 문자열 변수(문자 배열)를 구분하고, 널 문자가 문자열의 끝을 나타내는 방식을 설명할 수 있다
> 2. 문자 배열을 문자열 리터럴과 문자 상수로 초기화하고, 원소 단위로 수정하거나 `strcpy`로 복사할 수 있다
> 3. `scanf("%s")`와 줄 단위 입력 함수의 차이와 입력 버퍼에 남는 문자를 설명할 수 있다
> 4. 라이브러리 함수 없이 문자열의 길이 계산, 대문자 변환, 뒤집기, 비교를 구현할 수 있다
> 5. 문자열 리터럴을 가리키는 포인터와 문자 배열을 가리키는 포인터의 차이를 설명할 수 있다

---

## 목차

- [1. 문자열](#1-문자열)
  - [1.1 문자열 상수와 문자열 변수](#11-문자열-상수와-문자열-변수)
  - [1.2 문자열의 출력과 %s](#12-문자열의-출력과-s)
  - [1.3 문자 배열의 수정](#13-문자-배열의-수정)
  - [1.4 초기화와 널 문자](#14-초기화와-널-문자)
  - [1.5 문자열 배열](#15-문자열-배열)
  - [1.6 문자열 입력 함수](#16-문자열-입력-함수)
- [2. 문자열 실습](#2-문자열-실습)
  - [2.1 문자열의 길이](#21-문자열의-길이)
  - [2.2 소문자를 대문자로 변환](#22-소문자를-대문자로-변환)
- [3. 문자열 포인터](#3-문자열-포인터)
  - [3.1 문자열 리터럴을 가리키는 포인터](#31-문자열-리터럴을-가리키는-포인터)
  - [3.2 문자열 리터럴은 수정할 수 없다](#32-문자열-리터럴은-수정할-수-없다)
  - [3.3 문자 배열을 가리키는 포인터](#33-문자-배열을-가리키는-포인터)
- [4. 문자열 포인터 실습](#4-문자열-포인터-실습)
  - [4.1 문자열 뒤집기](#41-문자열-뒤집기)
  - [4.2 공백에서 줄 바꾸기](#42-공백에서-줄-바꾸기)
  - [4.3 두 문자열 비교](#43-두-문자열-비교)
- [요약](#요약)
- [점검 문제](#점검-문제)

---

<br>

## 1. 문자열

### 1.1 문자열 상수와 문자열 변수

큰따옴표 안에 표현된 문자의 나열을 **문자열 상수(string constant)** 또는 **문자열 리터럴(string literal)** 이라고 한다. `printf("Hello World!");`의 `"Hello World!"`가 그 예이다. 문자열 리터럴은 문자열이면서 상수의 성질을 가지므로 수정할 수 없으며, 프로그램은 문자열 리터럴을 따로 보관하는 메모리 영역에 저장한다([9장 1.1절](Concepts_Lecture.ko.md#11-문자와-문자열의-차이)).

**문자열 변수**는 문자열을 문자 배열에 저장하여 사용하는 것이다. 일반적으로 문자열이라고 하면 문자열 변수를 뜻하며, 문자 배열에 보관된 값은 바꿀 수 있다. 문자열은 마지막에 **널 문자(null character)** `'\0'`(코드 값 0)이 있어 끝을 나타낸다([9장 1.2절](Concepts_Lecture.ko.md#12-선언과-초기화)).

```c
char str1[5] = "Good";                      // a string literal adds '\0' automatically
char str2[] = {'a', 'b', 'c', '\0'};        // with character constants, '\0' must be written
```

```text
        [0]    [1]    [2]    [3]    [4]
 str1 │ 'G' │ 'o' │ 'o' │ 'd' │ '\0' │
 str2 │ 'a' │ 'b' │ 'c' │ '\0' │
```

*그림 1. 문자 배열 str1과 str2의 원소*

문자열 리터럴로 초기화하면 널 문자가 자동으로 끝에 추가되므로 `"Good"`을 저장하려면 5칸이 필요하다. 문자 상수를 이어서 초기화할 때는 널 문자를 직접 넣어야 한다.

### 1.2 문자열의 출력과 %s

문자열은 형식 지정자 `%s`로 출력한다.

```c
#include <stdio.h>

int main(void)
{
    char str1[5] = "Good";                      // a string literal adds '\0' automatically
    char str2[] = {'a', 'b', 'c', '\0'};        // with character constants, '\0' must be written

    printf("%s \n", str1);      // %s prints characters until it meets '\0'
    printf("%s \n", str2);

    return 0;
}
```

```text
Good 
abc 
```

`printf("%s", str1);`에서 문자 배열의 이름 `str1`은 그 문자열의 메모리 시작 주소이다. `printf`는 이 주소로 가서 원소를 하나씩 화면에 출력하다가 널 문자를 만나면 출력을 끝낸다([9장 4.1절](Concepts_Lecture.ko.md#41-scanf--printf와-s)).

### 1.3 문자 배열의 수정

초기값 없이 선언한 문자 배열에 문자열을 넣는 방법은 두 가지이다. 코드는 [Example_CharArray.c](Example_CharArray.c)이다.

- **문자 상수로 원소마다 대입:** 문자열은 문자 상수가 이어진 것이므로 각 원소를 `str[0] = 'H';`처럼 문자 상수로 바꾼다. 이때 문자열의 끝을 알리는 널 문자 `'\0'`도 마지막 위치에 반드시 직접 넣어야 한다. 코드의 첫 번째 주석이 이 방법이다.
- **`strcpy`로 복사:** 문자열 복사 함수 `strcpy(str, "Hello");`는 널 문자까지 한꺼번에 복사한다. `strcpy`를 쓰려면 `<string.h>`를 포함해야 한다([9장 2.2절](Concepts_Lecture.ko.md#22-strcpy--strncpy)).

```c
#define _CRT_SECURE_NO_WARNINGS  // allows strcpy in Visual Studio
#include <stdio.h>
#include <string.h>

/*int main()
{
    char str[7];
    printf("1. %s \n", str);

    // assign values with character literals
    str[0] = 'H';
    str[1] = 'e';
    str[2] = 'l';
    str[3] = 'l';
    str[4] = 'o';
    str[5] = '\0';
    printf("2. %s \n", str);
}*/

int main()
{
    char str[7];
    printf("1. %s \n", str);  // str is not initialized yet, so this prints whatever is in memory

    // update the string with strcpy()
    strcpy(str, "Hello");
    printf("2. %s \n", str);
}
```

```text
2. Hello 
```

첫 번째 `printf`는 초기화하지 않은 배열을 출력하므로, 그 메모리에 남아 있던 알 수 없는 바이트가 출력되거나 널 문자가 나올 때까지 배열 밖을 읽을 수 있다. 정의되지 않은 동작이므로 실행마다 결과가 다르며, 위 출력에는 `strcpy` 뒤의 둘째 줄만 보였다.

> **참고:** Visual Studio는 `strcpy`가 대상 배열의 크기를 검사하지 않는다는 이유로 C4996 경고를 내며, `#define _CRT_SECURE_NO_WARNINGS` 또는 `#pragma warning(disable:4996)`으로 끈다([3장 실습 5.1절](../Ch03_Data-Types-and-Variables/Concepts_Lab.ko.md#51-c4996-경고)). 대상 배열이 복사할 문자열과 널 문자를 담기에 충분히 커야 한다는 점은 컴파일러가 검사하지 않으므로 프로그래머가 보장해야 한다.

선언과 동시에 문자열 리터럴로 초기화한 문자 배열도 원소 단위로 바꿀 수 있다.

```c
#include <stdio.h>

int main(void)
{
    char str[6] = "hello";
    printf("1. %s \n", str);

    str[0] = 'H';               // an element of a char array can be changed
    printf("2. %s \n", str);

    return 0;
}
```

```text
1. hello 
2. Hello 
```

### 1.4 초기화와 널 문자

문자열 리터럴로 초기화하면 널 문자가 자동으로 맨 뒤에 추가되지만, 문자 상수로 초기화하면 널 문자를 직접 넣어야 한다.

```c
#include <stdio.h>

int main(void)
{
    char arr1[] = "abc";                        // 4 elements: 'a', 'b', 'c', '\0'
    char arr2[] = {'a', 'b', 'c'};              // 3 elements: no '\0', so not a string
    char arr3[] = {'a', 'b', 'c', '\0'};        // 4 elements: the same as arr1

    printf("%zu %zu %zu\n", sizeof(arr1), sizeof(arr2), sizeof(arr3));

    return 0;
}
```

```text
4 3 4
```

`arr2`는 널 문자가 없는 3칸짜리 문자 배열이므로 문자열이 아니다. `printf("%s", arr2);`처럼 문자열로 쓰면 배열 끝을 넘어 널 문자를 찾을 때까지 읽으므로 정의되지 않은 동작이 된다.

널 문자는 문자열의 끝 지점을 알려 준다. 문자열을 출력할 때는 시작 위치부터 문자를 하나씩 출력하다가 널 문자를 만나면 멈추고, 문자열의 길이를 구할 때도 널 문자를 만날 때까지 센다.

```c
#include <stdio.h>

int main(void)
{
    char str[10] = "Ab # 31";   // str[7] to str[9] are filled with '\0'
    int i;

    printf("%s \n", str);       // printing stops at the first '\0'
    for (i = 0; i < 10; i++)
        printf("%d ", str[i]);  // the character codes of all 10 elements
    printf("\n");

    return 0;
}
```

```text
Ab # 31 
65 98 32 35 32 51 49 0 0 0 
```

`"Ab # 31"`은 공백을 포함한 7개의 문자이므로 `str[0]`\~`str[6]`에 저장되고, 나머지 `str[7]`\~`str[9]`는 0(널 문자)으로 채워진다. 공백 문자(코드 32)는 널 문자가 아니므로 출력이 공백에서 멈추지 않는다.

### 1.5 문자열 배열

여러 문자열을 쓰려면 2차원 문자 배열을 쓴다. `char str[3][6]`은 최대 5글자(널 문자 포함 6칸)의 문자열 3개를 저장하며, `str[i]`는 i번째 문자열, `str[i][j]`는 그 문자열의 j번째 문자이다([9장 7.1절](Concepts_Lecture.ko.md#71-2차원-char-배열)). 코드는 [Example_StringArray.c](Example_StringArray.c)이다.

```c
#include <stdio.h>

int main()
{
    char str[3][6] = { {"ABC"}, {"defg"}, {"1Q$"} };
    int i;

    for (i = 0; i < 3; i++) {
        printf("%s \n", str[i]);
    }
    printf("------------ \n");
    str[0][0] = 'a';
    str[0][2] = 'c';
    printf("%c \n", str[0][0]);
    printf("%s \n", str[0]);
}
```

```text
ABC 
defg 
1Q$ 
------------ 
a 
aBc 
```

|  | [0] | [1] | [2] | [3] | [4] | [5] |
|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
| `str[0]` | `'a'` | `'B'` | `'c'` | `'\0'` | `'\0'` | `'\0'` |
| `str[1]` | `'d'` | `'e'` | `'f'` | `'g'` | `'\0'` | `'\0'` |
| `str[2]` | `'1'` | `'@'` | `'$'` | `'\0'` | `'\0'` | `'\0'` |

*표 1. str[0][0]과 str[0][2]를 바꾼 뒤의 문자열 배열*

`str[0][0] = 'a';`와 `str[0][2] = 'c';`는 첫 문자열 `"ABC"`의 첫째와 셋째 문자만 바꾸므로 `str[0]`은 `"aBc"`가 된다. `%c`로 `str[0][0]`을 출력하면 문자 하나 `a`가, `%s`로 `str[0]`을 출력하면 문자열 `aBc`가 출력된다.

### 1.6 문자열 입력 함수

`scanf("%s", ...)`는 공백 문자(공백, 탭, 줄바꿈)를 만나면 읽기를 멈추므로 한 단어만 읽는다. 공백을 포함한 한 줄을 읽으려면 줄 단위 입력 함수를 쓴다. 코드는 [Example_InputBuffer.c](Example_InputBuffer.c)이다.

```c
#define _CRT_SECURE_NO_WARNINGS  // allows scanf in Visual Studio
#include <stdio.h>
#include <string.h>
int main()
{
    char nOne[20] = "";
    char nTwo[20] = "";

    printf(">> 1. input name: ");
    scanf(" %s", nOne);     // enter a name such as hong gil dong

    // also note how the program behaves when the while loop below (which empties the buffer) is commented out
    while (getchar() != '\n');      // " gil dong" and Enter remain in the buffer after hong is read; this discards them

    printf(">> 2. input name: ");
    fgets(nTwo, sizeof(nTwo), stdin);   // enter a name such as hong gil dong
    nTwo[strcspn(nTwo, "\n")] = '\0';   // remove the newline that fgets keeps

    printf("-> nOne: %s \n", nOne);     // prints only hong (scanf stops at the space)
    printf("-> nTwo: %s \n", nTwo);     // prints all of hong gil dong
}
```

```text
>> 1. input name: hong gil dong
>> 2. input name: hong gil dong
-> nOne: hong 
-> nTwo: hong gil dong 
```

- **첫 번째 입력:** `scanf(" %s", nOne);`은 `hong`까지만 읽어 `nOne`에 저장하고, 나머지 ` gil dong`과 줄바꿈 문자는 입력 버퍼에 남는다. 배열 이름 `nOne`은 이미 주소이므로 `&`를 붙이지 않는다.
- **버퍼 비우기:** `while (getchar() != '\n');`은 버퍼에 남은 문자를 줄바꿈 문자까지 하나씩 읽어 버린다. 이 줄이 없으면 두 번째 입력 함수가 사용자의 입력을 기다리지 않고 버퍼에 남은 ` gil dong`을 바로 읽는다.
- **두 번째 입력:** 줄 단위 입력 함수는 공백을 포함한 한 줄 전체 `hong gil dong`을 읽는다.

> **참고:** **`gets`, `gets_s`, `fgets`.** 배열의 크기를 받지 않아 버퍼 오버플로를 일으킬 수 있는 `gets`는 C11에서 표준에서 제거되었다. Visual Studio는 대신 `gets_s(str, sizeof(str));`를 제공하는데, 이 함수는 C11의 선택 사항인 부록 K에 속하므로 gcc와 clang의 표준 라이브러리에는 대개 없다. 이 레포지토리의 예제는 어느 컴파일러에서나 컴파일되도록 표준 함수 `fgets(str, sizeof(str), stdin);`를 쓴다. `fgets`는 `gets_s`와 달리 읽은 줄바꿈 문자를 배열에 남기므로, `str[strcspn(str, "\n")] = '\0';`으로 줄바꿈 문자를 널 문자로 바꾼다([9장 4.2절](Concepts_Lecture.ko.md#42-fgets--gets_s)). 같은 이유로 `scanf_s`로 문자열을 읽을 때는 `scanf_s("%s", nOne, 20);`처럼 배열의 크기를 함께 넘겨야 한다.

---

<br>

## 2. 문자열 실습

다음 문제는 `strlen`, `isupper` 같은 라이브러리 함수를 쓰지 않고 널 문자를 기준으로 문자열을 처리하는 연습이다. 풀이 코드는 이 단원 폴더의 예제 파일이며, 각 파일은 `gcc -std=c99 -Wall`로 경고 없이 컴파일되고, 출력은 실제로 실행한 결과이다.

### 2.1 문자열의 길이

**문제:** 문자 배열 `char str[15] = "";`를 선언한 뒤 화면에서 문자열(14자 이하)을 입력받아, `strlen` 함수를 쓰지 않고 길이를 구하여 출력하라.

**풀이:** 인덱스 `len`을 0부터 늘리면서 `str[len]`이 널 문자가 아닌 동안 센다. 반복이 끝났을 때의 `len`이 널 문자의 인덱스이고, 그 값이 곧 문자열의 길이이다. 공백도 문자이므로 길이에 포함된다.

**코드:** [Example_StringLength.c](Example_StringLength.c)

```c
#include <stdio.h>
#include <string.h>

int main()
{
    char str[15] = "";
    int len = 0;

    printf(">> input str: ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0';     // remove the newline that fgets keeps

    while (str[len] != '\0')
        len++;

    printf("-> len: %d \n", len);       // strlen(str) also gives the length
}
```

```text
>> input str: Hello World
-> len: 11 
```

### 2.2 소문자를 대문자로 변환

**문제:** `char str[15] = "";`에 문자열을 입력받아 소문자를 모두 대문자로 바꾸어 저장한 뒤 출력하라. `isupper` 같은 문자 함수와 `strlen`을 쓰지 않는다.

**풀이:** 소문자 `'a'`\~`'z'`와 대문자 `'A'`\~`'Z'`는 ASCII 코드에서 같은 간격으로 연속해 있고, 같은 글자의 소문자와 대문자는 `'a' - 'A'` = 32만큼 차이가 난다. 따라서 소문자이면 32를 빼서 대문자로 바꾼다. 반복 조건을 `str[i] != '\0'` 대신 `str[i]`로만 써도 되는 이유는 널 문자의 코드가 0이어서 조건식에서 거짓이 되기 때문이며, 그래서 문자열의 길이를 미리 구하지 않아도 된다. 소문자가 아닌 문자(대문자, 숫자, 공백)는 그대로 둔다.

**코드:** [Example_ToUpper.c](Example_ToUpper.c)

```c
#include <stdio.h>
#include <string.h>

int main()
{
    char str[15] = "";
    int i;

    printf(">> input str: ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0';     // remove the newline that fgets keeps

    /*int len = 0;

    while (str[len] != '\0')
        len++;

    for (i = 0; i < len; i++) {
        if (str[i] >= 'a' && str[i] <= 'z')
            str[i] -= 'a' - 'A';
    }*/

    for (i = 0; str[i]; i++) {      // the loop range can be set without computing the length as above (str[i] != '\0')
                                    // str[i] alone works instead of str[i] != '\0' because the ASCII value of \0 is 0
        if (str[i] >= 'a' && str[i] <= 'z')
            str[i] -= 'a' - 'A';
    }

    printf("-> str: %s", str);
}
```

```text
>> input str: Hello C 2024
-> str: HELLO C 2024
```

입력 문자열의 대문자와 소문자의 개수를 세는 문제는 [HW10 문제 2](../../Coursework/HW10_Strings/Assignment-Explanation.ko.md#2-문자열-검색)에서 다룬다.

---

<br>

## 3. 문자열 포인터

### 3.1 문자열 리터럴을 가리키는 포인터

`char *pc = "AbCde";`는 문자열 리터럴 `"AbCde"`를 문자 배열에 복사하지 않고, 문자열 리터럴 전용 저장 공간에 있는 그 문자열의 시작 주소를 포인터 `pc`에 저장한다([9장 6.1절](Concepts_Lecture.ko.md#61-char-문자열-포인터)). `pc`로 문자열을 읽고 출력할 수는 있다.

```text
 [문자열 리터럴 저장 공간]
   0x102ab44e4
  ┌─────┬─────┬─────┬─────┬─────┬──────┐
  │ 'A' │ 'b' │ 'C' │ 'd' │ 'e' │ '\0' │
  └─────┴─────┴─────┴─────┴─────┴──────┘
     ▲
 pc ─┘  (pc = 0x102ab44e4)
```

*그림 2. 문자열 리터럴을 가리키는 포인터 pc*

### 3.2 문자열 리터럴은 수정할 수 없다

문자열 리터럴은 수정할 수 없으므로, 포인터로 리터럴의 문자를 바꾸려 하면 정의되지 않은 동작이 된다. 코드는 [Example_StringLiteral.c](Example_StringLiteral.c)이다.

```c
#include <stdio.h>

int main()
{
    char* pc = "AbCde";

    printf("%p \n", pc);
    printf("%s \n", pc);

    pc[1] = 'B';        // attempt to change a string literal through a pointer -> run-time error
    puts(pc);
}
```

```text
0x102ab44e4 
AbCde 
```

`pc[1] = 'B';`는 컴파일 오류 없이 컴파일되지만, 실행하면 그 줄에서 프로그램이 비정상 종료되어 마지막 `puts(pc);`는 실행되지 않는다. 대부분의 운영체제는 문자열 리터럴을 읽기 전용 메모리에 두므로, 쓰기를 시도하면 메모리 접근 위반이 일어난다. 위 결과는 macOS에서 실행한 것으로 프로그램이 버스 오류(SIGBUS)로 끝났고, Visual Studio에서는 디버거가 쓰기 액세스 위반 예외를 표시한다.

> **주의:** 문자열 리터럴을 가리킬 포인터는 `const char *pc = "AbCde";`처럼 `const`를 붙여 선언하는 것이 좋다. 그러면 `pc[1] = 'B';` 같은 쓰기를 컴파일러가 오류로 잡아 준다([9장 6.2절](Concepts_Lecture.ko.md#62-const-char)).

### 3.3 문자 배열을 가리키는 포인터

문자열 리터럴을 문자 배열에 저장한 뒤 그 배열을 포인터로 가리키면, 포인터로 문자열의 내용을 바꿀 수 있다. `char str[] = "AbCde";`는 리터럴의 내용을 수정 가능한 배열에 복사하기 때문이다.

```c
#include <stdio.h>

int main(void)
{
    char str[] = "AbCde";       // a char array initialized with a copy of the literal
    char *ps = str;             // ps points to the first element of the array

    ps[1] = 'B';                // changes str[1]: the array is modifiable
    printf("%s \n", str);

    return 0;
}
```

```text
ABCde 
```

`ps`는 `str[0]`을 가리키므로 `ps[1]`은 `str[1]`이며, `ps[1] = 'B';`로 배열의 둘째 문자가 `'b'`에서 `'B'`로 바뀐다.

---

<br>

## 4. 문자열 포인터 실습

풀이 코드는 이 단원 폴더의 예제 파일이며, 각 파일은 `gcc -std=c99 -Wall`로 경고 없이 컴파일되고, 출력은 실제로 실행한 결과이다. 메시지 끝에 `\n`이 없는 프로그램은 실제 터미널에서 다음 프롬프트가 메시지 바로 뒤에 이어진다.

### 4.1 문자열 뒤집기

**문제:** 화면에서 입력한 문자열을 배열에 저장하고, 배열의 내용을 거꾸로 저장하는 함수 `revStr`를 호출한 뒤 바뀐 문자열을 출력하라.

**풀이:** 함수의 매개변수 `char *arr`는 배열을 가리키는 포인터이며, 포인터가 배열을 가리킬 때는 `arr[i]`처럼 인덱스를 쓸 수 있다. 길이가 len인 문자열을 뒤집으려면 i번째 문자와 (len - 1 - i)번째 문자를 맞바꾼다.

```text
 len = 6:  [0] [1] [2] [3] [4] [5]     [0]↔[5], [1]↔[4], [2]↔[3]
            A   b   c   ' ' 3   B      i = 0, 1, 2 (i < 3)

 len = 5:  [0] [1] [2] [3] [4]         [0]↔[4], [1]↔[3], [2]는 그대로
            A   b   c   ' ' 3          i = 0, 1 (i < 2.5)
```

*그림 3. 문자열을 뒤집을 때 맞바꾸는 위치*

교환은 문자열의 절반까지만 하면 된다. 끝까지 진행하면 바꾼 쌍을 다시 바꾸어 원래 문자열로 돌아간다. 코드의 조건 `i < (len / 2.0)`은 실수 나눗셈이므로 len이 홀수일 때 가운데 문자의 인덱스 len / 2에서도 반복하지만, 그 문자는 자기 자신과 맞바뀌므로 결과는 같다. 정수 나눗셈 `i < len / 2`로 써도 된다.

**코드:** [Example_ReverseString.c](Example_ReverseString.c)

```c
#include <stdio.h>
#include <string.h>
#define SIZE 10

void revStr(char* arr);
void swap(char* a, char* b);

int main()
{
    char str[SIZE] = "";

    printf(">> input str: ");
    fgets(str, SIZE, stdin);
    str[strcspn(str, "\n")] = '\0';     // remove the newline that fgets keeps

    revStr(str);
    printf("-> A reverse str: %s", str);
}

void revStr(char* arr)
{
    int i, len = strlen(arr);

    for (i = 0; i < (len / 2.0); i++) {
        swap(&arr[i], &arr[len - i - 1]);
    }
}

void swap(char* a, char* b)
{
    int temp;

    temp = *a;
    *a = *b;
    *b = temp;
}
```

```text
>> input str: Abc 3B
-> A reverse str: B3 cbA
```

```text
>> input str: Abc 3
-> A reverse str: 3 cbA
```

`swap`은 두 문자의 주소 `&arr[i]`와 `&arr[len - i - 1]`을 받아 그 자리의 값을 맞바꾼다([8장 실습 4.3절](../Ch08_Pointers/Concepts_Lab.ko.md#43-함수로-두-변수의-값-교환)). 배열의 크기 `SIZE`가 10이므로 9자를 넘는 입력은 `fgets`가 9자까지만 읽는다. 두 포인터를 양 끝에서 안쪽으로 옮기는 방식의 풀이는 [HW10 문제 3](../../Coursework/HW10_Strings/Assignment-Explanation.ko.md#3-문자열-뒤집기)에 있다.

### 4.2 공백에서 줄 바꾸기

**문제:** 사용자가 입력한 문자열을 출력하되, 공백 문자가 나오면 다음 줄에서 이어서 출력하라. 공백 문자인지는 `<ctype.h>`의 `isspace` 함수로 확인한다.

**풀이:** 문자열을 처음부터 한 문자씩 검사하여 공백 문자이면 줄바꿈 문자를, 아니면 그 문자를 출력한다. `isspace`는 공백 문자(공백, 탭, 줄바꿈 등)이면 0이 아닌 값을, 아니면 0을 반환하므로 조건식에 바로 쓸 수 있다([9장 3.1절](Concepts_Lecture.ko.md#31-분류)).

**코드:** [Example_WordSplit.c](Example_WordSplit.c)

```c
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main()
{
    char str[15] = "";
    int i;

    printf(">> input str: ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0';     // remove the newline that fgets keeps

    printf("word: \n");
    for (i = 0; i < strlen(str); i++) {
        if (isspace(str[i]))        // isspace() returns 0 for a non-space character and a nonzero value for a space character
            printf("\n");
        else
            printf("%c", str[i]);
    }
}
```

```text
>> input str: I love C
word: 
I
love
C
```

> **참고:** 반복 조건의 `strlen(str)`은 반복할 때마다 호출되어 문자열의 길이를 다시 센다. 짧은 문자열에서는 문제가 없지만, 길이를 반복 전에 한 번 구해 두거나 2.2절처럼 `str[i]`를 조건으로 쓰면 불필요한 계산을 줄일 수 있다. 또 `isspace`의 인수는 `unsigned char`로 나타낼 수 있는 값이어야 하므로, 한글처럼 코드 값이 128 이상인 바이트가 들어올 수 있으면 `isspace((unsigned char)str[i])`로 쓴다. 같은 문제를 `fgets`와 `putchar`로 푼 코드는 [HW10 문제 4](../../Coursework/HW10_Strings/Assignment-Explanation.ko.md#4-문자열-분리)에 있다.

### 4.3 두 문자열 비교

**문제:** 두 문자열이 같으면 1을, 같지 않으면 0을 반환하는 함수 `StrComp`를 구현하라.

**풀이:** 먼저 두 문자열의 길이를 비교하여 다르면 같은 문자열일 수 없으므로 바로 0을 반환한다. 길이가 같으면 같은 인덱스의 문자를 하나씩 비교하여 하나라도 다르면 0을, 끝까지 모두 같으면 1을 반환한다.

**코드:** [Example_StringCompare.c](Example_StringCompare.c)

```c
#include <stdio.h>
#include <string.h>

int StrComp(char* pOne, char* pTwo);

int main()
{
    char sOne[10] = "ab c";
    char sTwo[10] = "ab d";

    printf("1. result: %d \n", StrComp(sOne, sTwo));
    printf("2. result: %d \n", StrComp("hi", "hi"));
    printf("3. result: %d \n", StrComp("hi", "hi#"));
}

int StrComp(char* pOne, char* pTwo)
{
    int i, lenOne = strlen(pOne), lenTwo = strlen(pTwo);

    if (lenOne != lenTwo)       // strings of different lengths are treated as different
        return 0;

    for (i = 0; i < lenOne; i++) {
        if (pOne[i] != pTwo[i])
            return 0;
    }
    return 1;
}
```

```text
1. result: 0 
2. result: 1 
3. result: 0 
```

- `"ab c"`와 `"ab d"`는 길이가 4로 같지만 넷째 문자 `'c'`와 `'d'`가 달라 0이다.
- `"hi"`와 `"hi"`는 모든 문자가 같아 1이다.
- `"hi"`와 `"hi#"`는 길이가 2와 3으로 달라 0이다.

> **참고:** 표준 함수 `strcmp`는 같으면 0을, 첫 번째 문자열이 사전 순으로 앞이면 음수를, 뒤이면 양수를 반환하므로, `StrComp`와 반환값의 의미가 반대이다([9장 2.3절](Concepts_Lecture.ko.md#23-strcmp--strncmp)). 또 `StrComp`의 매개변수는 문자열을 읽기만 하므로 `const char *`로 선언하는 것이 좋다.

---

<br>

## 요약

| 개념 | 핵심 요약 |
|:-----|:-----|
| 문자열 리터럴 | 큰따옴표로 표현한 문자열 상수이며, 별도의 메모리 영역에 저장되고 수정할 수 없다. |
| 문자열 변수 | 문자 배열에 저장한 문자열이며, 원소를 바꿀 수 있다. |
| 널 문자 | 코드 값이 0인 `'\0'`으로 문자열의 끝을 나타내며, 리터럴로 초기화하면 자동으로 추가된다. |
| `%s` | 문자열의 시작 주소에서부터 널 문자를 만날 때까지 문자를 출력한다. |
| `strcpy` | 널 문자까지 문자열을 복사하며, 대상 배열이 충분히 커야 한다. |
| 문자열 배열 | 2차원 문자 배열로 여러 문자열을 저장하며, `str[i]`가 i번째 문자열이다. |
| 문자열 입력 | `scanf("%s")`는 공백에서 멈추고, 줄 단위 입력 함수는 공백을 포함한 한 줄을 읽는다. |
| 문자열 포인터 | 리터럴을 가리키는 포인터로는 문자를 바꿀 수 없고, 문자 배열을 가리키는 포인터로는 바꿀 수 있다. |
| 문자열 뒤집기 | i번째와 (len - 1 - i)번째 문자를 문자열의 절반까지만 맞바꾼다. |
| 문자열 비교 | 길이가 다르면 다르고, 같으면 문자를 하나씩 비교한다. |

---

<br>

## 점검 문제

1. **배열의 크기:** `char s[] = "C language";`의 `sizeof(s)`는 얼마인가?

   <details>
   <summary>정답</summary>

   공백을 포함한 문자 10개와 자동으로 추가되는 널 문자 1개를 저장하므로 11이다.

   </details>

2. **널 문자:** `char t[8] = "AB\0CD";`를 `printf("%s", t);`로 출력하면 무엇이 출력되는가?

   <details>
   <summary>정답</summary>

   `%s`는 첫 널 문자에서 출력을 멈추므로 `AB`만 출력된다. 배열에는 `'C'`와 `'D'`도 저장되어 있다.

   </details>

3. **입력 함수:** 사용자가 `New York`을 입력할 때 `scanf("%s", city);`로 읽으면 `city`에 무엇이 저장되며, 입력 버퍼에는 무엇이 남는가?

   <details>
   <summary>정답</summary>

   `city`에는 `New`가 저장되고, 버퍼에는 ` York`과 줄바꿈 문자가 남는다. 공백을 포함한 줄 전체를 읽으려면 `fgets` 같은 줄 단위 입력 함수를 쓴다.

   </details>

4. **문자열 포인터:** `char a[] = "dog"; char *p = "cat";`일 때 `a[0] = 'f';`와 `p[0] = 'b';` 중 어느 것이 문제를 일으키는가?

   <details>
   <summary>정답</summary>

   `p[0] = 'b';`이다. `p`는 수정할 수 없는 문자열 리터럴을 가리키므로 쓰기가 정의되지 않은 동작이 된다. `a`는 리터럴의 내용을 복사한 문자 배열이므로 `a[0] = 'f';`는 문제없다.

   </details>

5. **뒤집기:** 4.1절의 `revStr`에서 반복 조건을 `i < len`으로 바꾸면 `"abc"`의 결과는 무엇인가?

   <details>
   <summary>정답</summary>

   i = 0에서 a와 c를 바꾸어 `cba`가 되고, i = 1에서 가운데 b를 자기 자신과 바꾸며, i = 2에서 다시 첫째와 셋째 문자를 바꾸어 `abc`로 돌아간다. 따라서 문자열이 바뀌지 않은 것처럼 보인다.

   </details>
