# HW10 과제 해설 — 문자열

[레포지토리 안내](../../README.ko.md) | [English](Assignment-Explanation.md) | [한국어](Assignment-Explanation.ko.md)

> **최종 수정일:** 2026-10-19

> **학습 목표:**
> 1. 문자 코드의 범위를 비교하여 문자열의 대문자와 소문자를 각각 셀 수 있다
> 2. 두 포인터를 양 끝에서 안쪽으로 옮기며 문자열을 제자리에서 뒤집을 수 있다
> 3. `fgets`로 공백을 포함한 한 줄을 입력받고 끝의 개행 문자를 제거할 수 있다
> 4. `isspace`로 공백 문자를 판별하여 문자열을 공백 단위로 나누어 출력할 수 있다

**문항 출처:** 이종욱 교수, 컴퓨터언어실습Ⅰ (DCCS103-03) / 박철원

---

## 목차

- [1. 문자열 검색](#1-문자열-검색)
  - [1.1 문제](#11-문제)
  - [1.2 풀이](#12-풀이)
  - [1.3 실행 결과](#13-실행-결과)
- [2. 문자열 뒤집기](#2-문자열-뒤집기)
  - [2.1 문제](#21-문제)
  - [2.2 풀이](#22-풀이)
  - [2.3 실행 결과](#23-실행-결과)
- [3. 문자열 분리](#3-문자열-분리)
  - [3.1 문제](#31-문제)
  - [3.2 풀이](#32-풀이)
  - [3.3 실행 결과](#33-실행-결과)
- [요약](#요약)
- [점검 문제](#점검-문제)

---

<br>

## 1. 문자열 검색

### 1.1 문제

사용자로부터 입력받은 문자열에 포함된 대문자와 소문자의 개수를 각각 찾아 출력하는 프로그램을 작성하라.

**실행 예시:**

```text
Input str: aB3 2# dfkW
Uppercase letters: 2
Lowercase letters: 4

Program ended with exit code: 0
```

### 1.2 풀이

**접근 방법:** 공백이 포함된 한 줄을 읽어야 하므로 `%s`가 아니라 한 줄을 읽는 `gets_s`를 쓴다([9장 4.2절](../../Lecture-Notes/Ch09_Strings/Concepts_Lecture.ko.md#42-fgets--gets_s)). 그다음 널 문자를 만날 때까지 한 문자씩 검사한다.

- **입력:** `char str[50] = "";`로 배열 전체를 널 문자로 초기화하고, `gets_s(str, sizeof(str))`로 개행 문자를 뺀 한 줄을 읽는다. `sizeof(str)`는 배열 크기 50이므로 최대 49글자까지 읽는다.
- **분류:** 반복 조건 `str[i]`는 현재 문자가 널 문자(0)가 아닌 동안 참이다. 문자가 `'a'`부터 `'z'` 사이이면 `countL`을, `'A'`부터 `'Z'` 사이이면 `countU`를 1 늘린다. ASCII에서 영문 대문자와 소문자는 각각 연속된 코드를 가지므로 범위 비교로 판별할 수 있다.
- **출력:** 대문자 개수와 소문자 개수를 차례로 출력한다.

`aB3 2# dfkW`에서 대문자는 `B`, `W`의 2개, 소문자는 `a`, `d`, `f`, `k`의 4개이며, 숫자, 공백, `#`은 어느 쪽에도 세지 않는다.

**코드:** [Solution/Q1.c](Solution/Q1.c)

```c
/**
 * @file    A10303-1_C09Q1.c
 * @brief   Q1. 문자열 검색
 * @author  박철원 (Cheolwon Park)
 * @date    2024-05-31
 * 
 * @note    소스 코드에 사용된 gets_s는 Visual Studio 이외의
 *          IDE에서 실행이 불가할 수 있음에 주의하시기 바랍니다.
 */

#include <stdio.h>

int main()
{
	char str[50] = "";
	int i, countU = 0, countL = 0;
	
	printf("Input str: ");
	gets_s(str, sizeof(str));

	for (i = 0; str[i]; i++) {
		if (str[i] >= 'a' && str[i] <= 'z')
			countL++;
		else if (str[i] >= 'A' && str[i] <= 'Z')
			countU++;
	}

	printf("Uppercase letters: %d\n", countU);
	printf("Lowercase letters: %d\n", countL);
}
```

### 1.3 실행 결과

`gets_s`는 C11 표준에서 선택 사항인 부록 K에 속하여 Visual Studio는 제공하지만 gcc와 clang의 표준 라이브러리에는 없다. gcc나 clang에서 실행하려면 9장 연습 문제 풀이처럼 한 줄을 읽고 개행 문자를 버리는 같은 동작의 `gets_s`를 정의한 헤더를 `-include` 옵션으로 넣는다([9장 연습 문제 1 풀이](../../Lecture-Notes/Ch09_Strings/Solutions.ko.md#연습-문제-1-문자열-조작)). 이렇게 `gcc -std=c99 -Wall`로 경고 없이 컴파일되며, 실행 예시와 같은 문자열을 입력한 결과는 다음과 같다.

```text
Input str: aB3 2# dfkW
Uppercase letters: 2
Lowercase letters: 4
```

실행 예시와 같다. 실행 예시의 마지막 줄 `Program ended with exit code: 0`은 프로그램의 출력이 아니라 Xcode 콘솔이 덧붙이는 종료 메시지이며, 이 문서의 다른 실행 예시에서도 마찬가지이다.

> **참고:** 범위 비교 대신 `<ctype.h>`의 `isupper()`, `islower()`를 쓰면 의도가 더 잘 드러나고, ASCII가 아닌 문자 집합에서도 올바르게 동작한다([9장 3.1절](../../Lecture-Notes/Ch09_Strings/Concepts_Lecture.ko.md#31-분류)). 이식성이 필요하면 `gets_s` 대신 `fgets`로 읽고 개행 문자를 지우는 방법(3절)을 쓴다. 이때 개행 문자는 영문자가 아니므로 지우지 않아도 이 문제의 개수는 달라지지 않는다.

---

<br>

## 2. 문자열 뒤집기

### 2.1 문제

사용자로부터 입력받은 문자열을 역순으로 뒤집어 출력하는 프로그램을 작성하라.

**프로그램 요구사항:**

1. 사용자로부터 입력받은 문자열을 역순으로 뒤집어 저장하는 `revStr()` 함수를 정의하여 사용한다.
2. `<string.h>` 라이브러리를 사용하지 않고 작성한다.

**실행 예시:**

```text
Input str: aB3 2# dfkW
Reversed str: Wkfd #2 3Ba

Program ended with exit code: 0
```

### 2.2 풀이

**접근 방법:** 새 배열을 만들지 않고, 문자열의 양 끝을 가리키는 두 포인터를 안쪽으로 옮기며 두 문자를 교환한다. 두 포인터가 만나거나 엇갈리면 모든 문자가 제자리에 놓인다.

- **`revStr()`:** `start`와 `end`를 모두 문자열의 시작 주소로 둔 뒤, `end`를 널 문자까지 옮기고 한 칸 뒤로 물려 마지막 문자를 가리키게 한다. 이 과정이 `strlen` 없이 문자열의 끝을 찾는 역할을 한다. 그다음 `start < end`인 동안 `*start`와 `*end`를 임시 변수로 교환하고 `start`는 앞으로, `end`는 뒤로 한 칸씩 옮긴다. 포인터끼리의 비교 `start < end`는 같은 배열 안의 두 위치를 비교한다([8장 2.1절](../../Lecture-Notes/Ch08_Pointers/Concepts_Lecture.ko.md#21-포인터-연산)).
- **`main()`:** `fgets(str, sizeof(str), stdin)`로 한 줄을 읽고, `<string.h>`를 쓸 수 없으므로 반복문으로 개행 문자를 찾아 널 문자로 바꾼다. 개행 문자를 지우지 않으면 뒤집은 문자열의 맨 앞에 개행 문자가 온다. `fgets`가 `NULL`을 반환하면(입력 끝) 아무것도 출력하지 않는다.

```text
단계 1:  [a][b][c][d][e]   start → a, end → e   : a와 e 교환
단계 2:  [e][b][c][d][a]   start → b, end → d   : b와 d 교환
단계 3:  [e][d][c][b][a]   start == end (c)     : 반복 종료
```

*그림 1. `revStr()`이 `"abcde"`를 뒤집는 과정*

**코드:** [Solution/Q2.c](Solution/Q2.c)

```c
/**
 * @file    A10303-1_C09Q2.c
 * @brief   Q2. 문자열 뒤집기
 * @author  박철원 (Cheolwon Park)
 * @date    2024-05-31
 */

#include <stdio.h>

void revStr(char* str) {
    char* start = str;
    char* end = str;

    while (*end) {
        end++;
    }
    end--;
	
    while (start < end) {
        char tmp = *start;
        *start = *end;
        *end = tmp;

        start++;
        end--;
    }
}

int main() {
    char str[100];

    printf("Input str: ");
    if (fgets(str, sizeof(str), stdin)) {
        for (int i = 0; str[i]; i++) {
            if (str[i] == '\n') {
                str[i] = '\0';
                break;
            }
        }

        revStr(str);
        printf("Reversed str: %s\n", str);
    }
}
```

### 2.3 실행 결과

`gcc -std=c99 -Wall`로 경고 없이 컴파일되며, 실행 예시와 같은 문자열을 입력한 결과는 다음과 같다.

```text
Input str: aB3 2# dfkW
Reversed str: Wkfd #2 3Ba
```

실행 예시와 같다. 길이 11인 문자열이므로 교환은 5번 일어나고, 가운데 문자인 `#`(인덱스 5)은 그대로 남는다.

> **주의:** 빈 문자열을 입력하면 `end`가 처음부터 널 문자를 가리키므로 `end--`가 배열의 시작보다 앞을 가리키게 된다. `start < end`가 거짓이라 역참조는 일어나지 않지만, 배열 범위 밖을 가리키는 포인터를 만드는 것 자체가 C 표준에서 정의되지 않은 동작이므로 `if (*str == '\0') return;`처럼 먼저 검사하는 편이 안전하다. 또한 이 함수는 바이트 단위로 뒤집으므로, 한글처럼 한 글자가 여러 바이트인 UTF-8 문자열을 넣으면 바이트 순서가 뒤집혀 글자가 깨진다.

---

<br>

## 3. 문자열 분리

### 3.1 문제

실행 예시를 참고하여 사용자로부터 입력받은 문자열에 공백이 포함된 경우 그 지점에서 줄바꿈을 한 뒤 이어서 출력하는 프로그램을 작성하라.

**프로그램 요구사항:**

1. `<ctype.h>`의 `isspace()` 라이브러리 함수를 활용하여 배열의 원소가 공백 문자(스페이스나 탭 등)인지 확인한다. `isspace()`는 다음과 같이 동작한다.
   - `<ctype.h>`에 `int isspace(int c);`의 형태로 선언되어 있으며, `char` 인자를 전달하면 자동으로 `int`로 변환되어 처리된다.
   - 인자가 공백 문자이면 0이 아닌 값(참)을, 그렇지 않으면 0(거짓)을 반환한다.
   - `' '`, `'\t'`, `'\n'`, `'\v'`, `'\f'`, `'\r'`의 여섯 문자(일반 공백과 공백 계열 제어 문자)를 공백 문자로 판단한다.

2. `fgets()` 함수를 사용하여 사용자 입력을 처리한다. 이때 입력을 마치려고 누른 개행 문자(Enter, `\n`)가 입력한 내용과 함께 저장된다. 이 개행 문자는 다음 문장을 덧붙여 삭제할 수 있다.

   ```c
   str[strcspn(str, "\n")] = '\0';
   ```

   `strcspn()` 라이브러리 함수를 사용하려면 `<string.h>`를 포함해야 한다.

**실행 예시:**

```text
Input str: aB 3# ! D
Output:
aB
3#
!
D

Program ended with exit code: 0
```

### 3.2 풀이

**접근 방법:** 문자열을 한 문자씩 출력하되, 공백 문자 자리에는 그 문자 대신 개행 문자를 출력한다. 그러면 공백으로 나뉜 조각이 한 줄에 하나씩 출력된다.

- **입력과 개행 문자 제거:** `fgets`로 최대 99글자를 읽고, `strcspn(str, "\n")`으로 처음 나오는 개행 문자의 위치(개행 문자가 없으면 문자열의 길이)를 구해 그 자리를 널 문자로 바꾼다. 개행 문자를 지우지 않으면 마지막에 빈 줄이 하나 더 출력된다.
- **분리 출력:** 각 문자에 대해 `isspace((unsigned char)str[i])`가 참이면 `'\n'`을, 거짓이면 그 문자를 조건 연산자로 골라 `putchar()`로 출력한다. `unsigned char`로 변환하는 이유는 `char`가 부호 있는 형인 시스템에서 한글 같은 비ASCII 바이트가 음수가 되어 `isspace()`에 넘길 수 없는 값이 되기 때문이다([9장 3.1절](../../Lecture-Notes/Ch09_Strings/Concepts_Lecture.ko.md#31-분류)).
- **마무리:** 마지막 조각 뒤에 `putchar('\n')`로 줄을 바꾼다.

**코드:** [Solution/Q3.c](Solution/Q3.c)

```c
/**
 * @file    A10303-1_C09Q3.c
 * @brief   Q3. 문자열 분리
 * @author  박철원 (Cheolwon Park)
 * @date    2024-05-27
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char str[100];

    printf("Input str: ");
    if (fgets(str, sizeof(str), stdin)) {
        str[strcspn(str, "\n")] = '\0';

        for (int i = 0; i < strlen(str); i++) {
            putchar(isspace((unsigned char)str[i]) ? '\n' : str[i]);
        }
        putchar('\n');
    }

    return 0;
}
```

### 3.3 실행 결과

`gcc -std=c99 -Wall`로 경고 없이 컴파일되며, 실행 예시와 같은 문자열을 입력한 결과는 다음과 같다.

```text
Input str: aB 3# ! D
aB
3#
!
D
```

나뉜 조각은 실행 예시와 같지만, 실행 예시의 두 번째 줄 `Output:`을 출력하지 않는다. 같은 형식으로 맞추려면 반복문 앞에 `printf("Output:\n");`를 추가한다.

> **주의:** 공백 문자를 각각 개행 문자로 바꾸므로, `a  b`처럼 공백이 연속되면 그 사이에 빈 줄이 생긴다(`a`, 빈 줄, `b`의 세 줄). 연속된 공백을 하나로 취급하려면 직전에 출력한 문자가 개행 문자인지 기억해 두고 개행 문자를 연달아 출력하지 않게 한다. 또 반복 조건 `i < strlen(str)`는 매번 `strlen`을 다시 호출하여 길이 $n$인 문자열에 대해 $O(n^2)$의 시간이 들고, `int`와 `size_t`(부호 없는 정수)를 비교한다. 길이를 반복 전에 `size_t len = strlen(str);`로 한 번만 구하거나 `str[i] != '\0'`을 조건으로 쓰는 편이 낫다.

---

<br>

## 요약

| 개념 | 핵심 요약 |
|:----|:---------|
| 대소문자 판별 | ASCII에서 영문자는 연속된 코드를 가지므로 `'a' <= c && c <= 'z'`처럼 범위로 판별할 수 있고, `isupper()`, `islower()`를 쓰면 더 이식성이 높다. |
| 한 줄 입력 | 공백이 포함된 한 줄은 `gets_s`나 `fgets`로 읽으며, `gets_s`는 개행 문자를 버리고 `fgets`는 개행 문자를 함께 저장한다. |
| 개행 문자 제거 | `str[strcspn(str, "\n")] = '\0';` 또는 직접 개행 문자를 찾아 널 문자로 바꾸는 반복문으로 `fgets`가 저장한 개행 문자를 지운다. |
| 제자리 뒤집기 | 양 끝을 가리키는 두 포인터를 `start < end`인 동안 교환하며 안쪽으로 옮기면 길이 $n$인 문자열을 $\lfloor n/2 \rfloor$번의 교환으로 뒤집을 수 있다. |
| 빈 문자열 처리 | 마지막 문자를 가리키려고 포인터를 한 칸 물리기 전에 빈 문자열인지 검사해야 배열 앞을 가리키는 포인터를 만들지 않는다. |
| `isspace()` | 스페이스, `\t`, `\n`, `\v`, `\f`, `\r`을 공백 문자로 판단하며, 인자는 `unsigned char`로 변환하여 넘긴다. |
| 반복 조건의 비용 | `i < strlen(str)`는 반복마다 길이를 다시 계산하므로, 길이를 한 번만 구하거나 널 문자를 조건으로 쓴다. |

---

<br>

## 점검 문제

1. **대소문자 개수:** 1절의 프로그램에 `Hello World 2024`를 입력하면 대문자와 소문자의 개수는 각각 얼마인가?

   <details>
   <summary>정답</summary>

   대문자는 `H`, `W`의 2개이고, 소문자는 `e`, `l`, `l`, `o`, `o`, `r`, `l`, `d`의 8개이다. 공백과 숫자는 세지 않는다.

   </details>

2. **뒤집기의 교환 횟수:** `revStr()`로 `"abcd"`와 `"abcde"`를 뒤집을 때 교환은 각각 몇 번 일어나며, 결과는 무엇인가?

   <details>
   <summary>정답</summary>

   `"abcd"`는 (a, d)와 (b, c)를 교환하여 2번 만에 `"dcba"`가 된다. `"abcde"`는 (a, e)와 (b, d)를 교환한 뒤 두 포인터가 가운데 `c`에서 만나 반복이 끝나므로 2번 만에 `"edcba"`가 된다. 길이가 $n$이면 교환은 $\lfloor n/2 \rfloor$번이다.

   </details>

3. **개행 문자를 지우지 않으면:** 2절의 `main()`에서 개행 문자를 지우는 반복문을 빼고 `abc`를 입력하면 출력은 어떻게 되는가?

   <details>
   <summary>정답</summary>

   `str`에는 `"abc\n"`이 저장되어 있으므로 뒤집으면 `"\ncba"`가 된다. 따라서 `Reversed str: ` 다음에 줄이 바뀌고, 다음 줄에 `cba`가 출력된 뒤 `printf`의 `\n`으로 다시 줄이 바뀐다.

   </details>

4. **연속된 공백:** 3절의 프로그램에 `a  b`(공백 두 칸)를 입력하면 `Input str:` 줄 다음에 몇 줄이 출력되는가?

   <details>
   <summary>정답</summary>

   세 줄이 출력된다. 첫 번째 공백이 `a` 뒤에서 줄을 바꾸고, 두 번째 공백이 빈 줄을 만든 뒤, `b`가 출력되고 마지막 `putchar('\n')`으로 줄이 바뀐다. 즉 `a`, 빈 줄, `b`의 순서이다.

   </details>
