# 7장 연습 문제 풀이 — 배열

[레포지토리 안내](../../README.ko.md) | [English](Solutions.md) | [한국어](Solutions.ko.md)

> **최종 수정일:** 2026-11-19
>
> Warming-Up C Programming, 천정아, Ch 7

**문항 출처:** 연습 문제 1~3은 임영희 교수, 컴퓨터언어Ⅰ (DCCS101-04)

---

<br>

## 목차

- [연습 문제 1: UPC 바코드의 검증 숫자 계산](#연습-문제-1-upc-바코드의-검증-숫자-계산)
- [연습 문제 2: 선택 정렬 변형](#연습-문제-2-선택-정렬-변형)
- [연습 문제 3: 빈도와 상대 빈도 계산](#연습-문제-3-빈도와-상대-빈도-계산)
- [연습 문제 4: 배열 선언의 판단](#연습-문제-4-배열-선언의-판단)
- [연습 문제 5: 2차원 배열 누적의 실행 결과](#연습-문제-5-2차원-배열-누적의-실행-결과)
- [연습 문제 6: 배열 매개변수에 대한 설명](#연습-문제-6-배열-매개변수에-대한-설명)
- [연습 문제 7: 실수 배열을 채우고 합계를 구하는 함수](#연습-문제-7-실수-배열을-채우고-합계를-구하는-함수)
- [연습 문제 8: 좌석 예매](#연습-문제-8-좌석-예매)
- [연습 문제 9: 배열의 왼쪽 회전](#연습-문제-9-배열의-왼쪽-회전)

---

<br>

## 연습 문제 1: UPC 바코드의 검증 숫자 계산

**문제:** 변수 12개로 UPC 바코드의 검증 숫자를 계산하는 예시 코드를, 크기를 매크로 상수로 정한 배열을 이용하도록 바꾸어 작성하라. 문제 전문과 실행 예시는 [연습 문제 1](Exercises.ko.md#연습-문제-1-upc-바코드의-검증-숫자-계산)에 있다.

### 풀이

**접근 방법:** 변수 `dig1`\~`dig11`을 배열 원소 `dig[0]`\~`dig[10]`으로 바꾸면, 1번째부터 세는 홀수 위치는 인덱스 0, 2, ..., 10이고 짝수 위치는 인덱스 1, 3, ..., 9이다. 따라서 인덱스를 2씩 늘리는 반복문 두 개로 두 합을 구할 수 있다([7장 5.4절](Concepts_Lecture.ko.md#54-upc-바코드-검증-숫자)).

- **입력:** `SIZE - 1`번, 즉 11번 반복하며 `"%1d"`로 숫자를 하나씩 읽어 `dig[0]`부터 저장한다. `%1d`는 최대 한 자리만 정수로 읽으므로, 실행 예시처럼 공백으로 구분한 `0 3 6 0 0 0 2 9 1 4 5`뿐 아니라 붙여 쓴 `03600029145`도 같은 결과를 낸다. `%d`처럼 앞의 공백 문자는 건너뛴다.
- **검증 숫자 계산:** 인덱스 0부터 2씩 늘리며 홀수 위치의 숫자를 `sum`에 더한 뒤 `sum *= 3`으로 3을 곱하고, 인덱스 1부터 2씩 늘리며 짝수 위치의 숫자를 더한다. 마지막으로 `(10 - sum % 10) % 10`을 배열의 마지막 원소 `dig[SIZE - 1]`에 저장한다. 바깥의 `% 10`은 `sum`이 10의 배수일 때 검증 숫자가 10이 아니라 0이 되게 한다.
- **입력값 출력:** 입력받은 11개의 숫자를 반복문으로 출력한다.

**코드:** [Lab_Q1.c](../../Coursework/Lab07_Arrays/Lab_Q1.c)

```c
/**
 * @file    A10104-1_C07Q1.c
 * @brief   Q1. UPC 바코드의 Check Digit 계산
 * @author  박철원 (Cheolwon Park)
 * @date    2024-05-11
 * 
 * @note    소스 코드에 사용된 scanf_s는 Visual Studio 이외의
 *	    IDE에서 실행이 불가할 수 있음에 주의하시기 바랍니다.
 */

#include <stdio.h>
#define SIZE 12

int main()
{
	int dig[SIZE], sum = 0, i;

	printf("Please enter the first eleven UPC digits, separated by white space: \n");

	for (i = 0; i < SIZE - 1; i++) {
		scanf_s("%1d", &dig[i]);
	}
	for (i = 0; i < SIZE - 1; i++) {
		printf("입력된 숫자: %d", dig[i]);
	}
	
	for (i = 0; i < SIZE - 1; i += 2) {
		sum += dig[i];
	}
	sum *= 3;
	for (i = 1; i < SIZE - 1; i += 2) {
		sum += dig[i];
	}
	dig[SIZE - 1] = (10 - sum % 10) % 10;

	printf("\nThe check digit is: %d \n", dig[SIZE - 1]);
	return 0;
}
```

**실행 결과:** 실행 예시의 숫자를 입력하면 검증 숫자 2가 나온다. 다만 출력 형식은 실행 예시와 두 군데 다르다. 입력값을 출력하는 반복문이 `"입력된 숫자: %d"`를 통째로 반복하므로 `입력된 숫자: `가 숫자마다 11번 출력되고, 마지막 줄은 `The check digit is: 2`처럼 `is` 뒤에 콜론이 붙는다. 실행 예시와 같게 하려면 `printf("입력된 숫자: ");`를 반복문 앞으로 옮기고 반복문 안에서는 `printf("%d", dig[i]);`만 실행하면 된다.

```text
Please enter the first eleven UPC digits, separated by white space: 
0 3 6 0 0 0 2 9 1 4 5
입력된 숫자: 0입력된 숫자: 3입력된 숫자: 6입력된 숫자: 0입력된 숫자: 0입력된 숫자: 0입력된 숫자: 2입력된 숫자: 9입력된 숫자: 1입력된 숫자: 4입력된 숫자: 5
The check digit is: 2 
```

> **참고:** **`scanf_s`와 `%1d`.** `scanf_s`는 Visual Studio가 제공하는 함수이며, 숫자를 읽는 `%1d` 변환에서는 `scanf`와 똑같이 동작한다([6장 연습 문제 1의 풀이](../Ch06_Functions/Solutions.ko.md#연습-문제-1-실수-반올림) 참고). 앞 11자리가 0 1 2 3 4 5 6 7 8 9 0이면 홀수 위치의 합 20에 3을 곱한 60과 짝수 위치의 합 25를 더해 85가 되므로, 프로그램은 검증 숫자 5를 출력한다.

---

<br>

## 연습 문제 2: 선택 정렬 변형

**교재 문항:** 7장 예제 7-11 (오름차순 선택 정렬)의 변형

**문제:** 교재 예제 7-11의 오름차순 선택 정렬을, 정렬되지 않은 부분에서 최댓값을 골라 뒤에서부터 제자리로 보내는 방식으로 바꾸어 작성하라. 정렬 결과는 오름차순이어야 한다. 문제 전문과 예제 7-11의 코드는 [연습 문제 2](Exercises.ko.md#연습-문제-2-선택-정렬-변형)에 있다.

### 풀이

**접근 방법:** 오름차순으로 정렬된 배열에서 가장 큰 값은 마지막 자리에 있어야 한다. 따라서 정렬되지 않은 부분 `data[0]`~`data[i]`에서 최댓값을 찾아 `data[i]`와 바꾸고, `i`를 `SIZE - 1`부터 하나씩 줄여 가면 `data[i]`부터 끝까지가 정렬된 상태로 늘어난다. 예제 7-11이 최솟값을 앞으로 보내며 정렬된 부분을 앞에서부터 키우는 것과 방향만 반대이다([7장 5.6절](Concepts_Lecture.ko.md#56-선택-정렬)).

- **바깥 반복문:** `i`를 `SIZE - 1`부터 0까지 줄이며, 이번 패스에서 채울 자리 `i`를 정한다. `index_max`를 `i`로 초기화한다.
- **안쪽 반복문:** `j`를 `i - 1`부터 0까지 줄이며 `data[index_max] < data[j]`이면 `index_max`를 `j`로 바꾼다. 안쪽 반복문이 끝나면 `index_max`는 `data[0]`~`data[i]` 중 최댓값의 인덱스이다.
- **교환과 출력:** `i != index_max`일 때만 `data[i]`와 `data[index_max]`를 맞바꾸고, 패스가 끝날 때마다 예제 7-11의 `print_array()`로 배열 전체를 출력한다.
- **추적:** 처음 배열 `{52, 31, 28, 17, 46}`에서 `i` = 4일 때 최댓값 52(인덱스 0)를 맨 뒤와 바꾸어 `{46, 31, 28, 17, 52}`, `i` = 3일 때 46(인덱스 0)을 바꾸어 `{17, 31, 28, 46, 52}`, `i` = 2일 때 31(인덱스 1)을 바꾸어 `{17, 28, 31, 46, 52}`가 된다. `i` = 1에서는 28이 이미 제자리에 있어 교환하지 않는다.

**코드:** [Lab_Q2.c](../../Coursework/Lab07_Arrays/Lab_Q2.c)

```c
/**
 * @file    A10104-1_C07Q2.c
 * @brief   Q2. 선택 정렬 변형
 * @author  박철원 (Cheolwon Park)
 * @date    2024-05-11
 */

#include <stdio.h>
#define SIZE 5

void print_array(int arr[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int data[SIZE] = { 52, 31, 28, 17, 46 };
    int i, j, temp;
    int index_max;

    for (i = SIZE - 1; i >= 0; i--) {
        index_max = i;

        for (j = i - 1; j >= 0; j--) {
            if (data[index_max] < data[j])
                index_max = j;
        }

        if (i != index_max) {
            temp = data[i];
            data[i] = data[index_max];
            data[index_max] = temp;
        }

        printf("i = %d회 반복 후 배열 : ", i);
        print_array(data, SIZE);
    }

    return 0;
}
```

**실행 결과:** 세 번째 패스(`i` = 2)가 끝나면 배열이 오름차순 `17 28 31 46 52`로 정렬되고, 남은 패스에서는 교환이 일어나지 않는다. 각 줄 끝에는 `print_array()`가 출력한 공백이 하나 남는다.

```text
i = 4회 반복 후 배열 : 46 31 28 17 52 
i = 3회 반복 후 배열 : 17 31 28 46 52 
i = 2회 반복 후 배열 : 17 28 31 46 52 
i = 1회 반복 후 배열 : 17 28 31 46 52 
i = 0회 반복 후 배열 : 17 28 31 46 52 
```

> **참고:** **패스의 수.** 바깥 반복문은 `i` = 0까지 실행되지만, `i` = 0이면 안쪽 반복문이 한 번도 실행되지 않고 교환도 없다. 원소가 하나만 남은 부분은 이미 정렬되어 있으므로, 예제 7-11이 `SIZE - 1`번만 반복하는 것처럼 조건을 `i > 0`으로 써도 결과가 같다. 또 출력의 `i = 4회 반복 후`에서 4는 반복 횟수가 아니라 이번 패스에서 채운 자리의 인덱스이다.

---

<br>

## 연습 문제 3: 빈도와 상대 빈도 계산

**문제:** 원소가 40개인 정수 배열을 `rand()`로 150~199의 난수로 채우고, 150부터 10 단위로 나눈 다섯 구간의 빈도수와 상대 빈도수를 출력하라. 시드는 `srand((unsigned)time(NULL))`로 바꾸고, 빈도수는 `switch`문으로 센다. 문제 전문과 실행 예시는 [연습 문제 3](Exercises.ko.md#연습-문제-3-빈도와-상대-빈도-계산)에 있다.

### 풀이

**접근 방법:** 값을 구간 번호로 바꾸는 식 `(값 - 150) / 10`을 쓰면 150\~159는 0, 160\~169는 1, ..., 190\~199는 4가 된다. 정수 나눗셈은 몫만 남기므로 같은 구간의 값은 모두 같은 번호가 된다([7장 5.7절](Concepts_Lecture.ko.md#57-빈도-수-세기)).

- **난수 생성:** 프로그램 시작 시 `srand((unsigned)time(NULL));`을 한 번 호출하여 실행할 때마다 다른 수열이 나오게 한다. `rand() % 50`은 0\~49이므로 150을 더하면 150\~199의 값이 된다([7장 5.8절](Concepts_Lecture.ko.md#58-난수-생성-rand-srand-time)).
- **빈도수 계산:** 원소를 하나 만들 때마다 `switch ((data[i] - 150) / 10)`의 `case 0`~`case 4`에서 해당하는 `frequency` 원소를 1 늘린다. 각 `case` 끝의 `break`가 없으면 아래 `case`의 문장까지 이어서 실행되므로 `break`가 반드시 필요하다.
- **상대 빈도수:** `frequency[i] / 40.0`처럼 `double` 상수로 나누어 실수 나눗셈을 한다. `frequency[i] / 40`으로 쓰면 정수 나눗셈이 되어 40보다 작은 빈도의 상대 빈도수가 모두 0이 된다.
- **출력:** `data[10 * i + j]`로 한 줄에 10개씩 네 줄을 출력한 뒤, 구간마다 `150 + 10 * i`부터 `150 + 10 * i + 9`까지의 범위와 빈도수, 소수 셋째 자리까지의 상대 빈도수를 출력한다.

**코드:** [Lab_Q3.c](../../Coursework/Lab07_Arrays/Lab_Q3.c)

```c
/**
 * @file    A10104-1_C07Q3.c
 * @brief   Q3. 빈도와 상대 빈도 계산
 * @author  박철원 (Cheolwon Park)
 * @date    2024-05-11
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int frequency[5] = { 0 }, data[40], i, j;
    double relative_freq[5];

    srand((unsigned)time(NULL));

    for (i = 0; i < 40; i++) {
        data[i] = rand() % 50 + 150;

        switch ((data[i] - 150) / 10) {    // data[i] 값에 해당하는 구간의 인덱스
        case 0:
            frequency[0] += 1;
            break;
        case 1:
            frequency[1] += 1;
            break;
        case 2:
            frequency[2] += 1;
            break;
        case 3:
            frequency[3] += 1;
            break;
        case 4:
            frequency[4] += 1;
            break;
        }
    }
    for (i = 0; i < 5; i++)
        relative_freq[i] = frequency[i] / 40.0;

    printf("배열 출력:\n");
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 10; j++) {
            printf("%d ", data[10 * i + j]);
        }
        printf("\n");
    }

    printf("\n\n\n-----------------------------\n");
    printf("구간 범위     도수    상대도수\n");
    printf("-----------------------------\n");

    for (i = 0; i < 5; i++) {
        printf("%d - %d     %2d     %.3f\n",
               150 + 10 * i, 150 + 10 * i + 9,
               frequency[i], relative_freq[i]);
    }

    return 0;
}
```

**실행 결과:** 난수를 쓰므로 실행할 때마다 값이 달라진다. 아래는 실행 한 번의 결과이며, 다섯 빈도수의 합은 40, 상대 빈도수의 합은 1.000이다. 실행 예시와 비교하면 첫 줄이 `배열 출력:`이고, 원소 사이를 공백 한 칸으로 구분하며, 표 앞에 빈 줄이 세 개 있고, 표 머리글이 `구간 범위`인 점이 다르다.

```text
배열 출력:
153 198 185 184 169 153 179 189 159 158 
186 180 169 191 158 180 191 187 159 157 
193 152 182 188 191 197 154 154 154 178 
172 178 187 182 160 195 186 152 170 196 



-----------------------------
구간 범위     도수    상대도수
-----------------------------
150 - 159     12     0.300
160 - 169      3     0.075
170 - 179      5     0.125
180 - 189     12     0.300
190 - 199      8     0.200
```

> **참고:** **매크로 상수.** 이 문제의 공통 요구사항은 배열의 크기를 매크로 상수로 지정하는 것이지만, 풀이 코드는 원소 수 40과 구간 수 5를 리터럴로 썼다. `#define SIZE 40`과 `#define GROUPS 5`를 두고 배열 선언, 반복 조건, `40.0`을 `(double)SIZE`로 바꾸면 크기를 한 곳에서 바꿀 수 있다([7장 1.5절](Concepts_Lecture.ko.md#15-define과-sizeof를-이용한-배열-크기-관리)).

> **참고:** **`rand() % 50`의 치우침.** `RAND_MAX + 1`이 50의 배수가 아니면 `rand() % 50`의 값 가운데 일부가 다른 값보다 약간 더 자주 나온다. glibc처럼 `RAND_MAX`가 2,147,483,647이면 `rand()`가 낼 수 있는 $2^{31}$개의 값 가운데 50으로 나눈 나머지가 0~47인 값은 각각 42,949,673개, 48과 49인 값은 각각 42,949,672개이다. 차이가 약 4,300만분의 1이므로 이 문제에서는 무시해도 된다.

---

<br>

## 연습 문제 4: 배열 선언의 판단

**교재 문항:** 7장 연습 문제 2번

**문제:** 함수 안의 여섯 가지 배열 선언 가운데 ANSI C에서 잘못된 것을 고르고, C99 이후에 달라지는 선언의 이유를 설명하라. 보기는 [연습 문제 4](Exercises.ko.md#연습-문제-4-배열-선언의-판단)에 있다.

### 풀이

**정답:** ②, ③, ⑤, ⑥

**해설:** 배열의 크기는 0보다 큰 정수형 상수여야 한다([7장 1.3절](Concepts_Lecture.ko.md#13-배열-선언)).

- ① 올바르다.
- ② 크기가 0인 배열은 표준에 없다. Clang은 `-pedantic`에서 `zero size arrays are an extension` 경고를 내며 확장 기능으로만 받아들인다.
- ③ 크기도 초기화 리스트도 없으므로 원소의 개수를 알 수 없다. Clang은 `definition of variable with array type needs an explicit size or an initializer` 오류를 낸다.
- ④ 매크로 상수 `MAX`는 전처리 단계에서 10으로 바뀌므로 `int arr[10];`과 같고 올바르다.
- ⑤, ⑥ C에서 `const` 변수와 일반 변수는 상수식이 아니므로 ANSI C에서는 잘못이다. C99 이후의 컴파일러에서는 함수 안의 이 두 선언이 가변 길이 배열(VLA)로 해석되어 컴파일된다. Clang은 두 선언을 경고 없이 받아들이지만, VLA를 지원하지 않는 Visual Studio에서는 컴파일 오류이다. 교재의 규칙대로 배열 크기에는 매크로 상수를 쓰면 어느 컴파일러에서나 같은 결과가 나온다.

---

<br>

## 연습 문제 5: 2차원 배열 누적의 실행 결과

**교재 문항:** 7장 연습 문제 12번의 변형

**문제:** 일부 원소만 초기화한 4행 3열 배열의 앞 3행을 마지막 행에 누적한 뒤 배열 전체를 출력하는 프로그램의 실행 결과를 쓰라. 코드는 [연습 문제 5](Exercises.ko.md#연습-문제-5-2차원-배열-누적의-실행-결과)에 있다.

### 풀이

**접근 방법:** 먼저 초기화가 끝난 배열을 그리고, 반복문이 바꾸는 원소인 `x[3][0]`, `x[3][1]`, `x[3][2]`만 따라간다.

행별 초기화에서 초기값이 모자란 원소와 초기값이 없는 4행 전체는 0이므로, 반복 전의 배열은 다음과 같다.

```text
x[0]:  2  4  6
x[1]:  1  3  0
x[2]:  5  0  0
x[3]:  0  0  0
```

바깥 반복은 `i`가 0, 1, 2인 행을, 안쪽 반복은 각 열을 돌면서 `x[3][j]`에 더한다. 따라서 `x[3][0]` = 2 + 1 + 5 = 8, `x[3][1]` = 4 + 3 + 0 = 7, `x[3][2]` = 6 + 0 + 0 = 6이고, 앞 3행은 바뀌지 않는다. `%2d`는 두 칸에 오른쪽 정렬하므로 한 자리 수 앞에 빈칸이 하나씩 붙는다.

**실행 결과:**

```text
 2 4 6
 1 3 0
 5 0 0
 8 7 6
```

---

<br>

## 연습 문제 6: 배열 매개변수에 대한 설명

**교재 문항:** 7장 연습 문제 6번

**문제:** 배열을 함수의 인자로 전달하는 방법에 대한 일곱 가지 설명 가운데 잘못된 것을 모두 고르라. 보기는 [연습 문제 6](Exercises.ko.md#연습-문제-6-배열-매개변수에-대한-설명)에 있다.

### 풀이

**정답:** ①, ③, ⑦

**해설:** ① 1차원 배열 매개변수는 `int arr[]`처럼 크기를 생략하여 선언하며, 크기를 써도 무시된다. ③ 호출할 때는 첫 원소의 값이 아니라 배열 이름, 즉 배열의 시작 주소를 넘긴다. ⑦ 매개변수 `arr`는 실제로는 주소를 담는 포인터이므로 `sizeof(arr)`는 포인터의 크기(64비트 환경에서 8)이고, 그래서 ④처럼 원소의 개수를 따로 받는다([7장 5.9절](Concepts_Lecture.ko.md#59-함수의-인자로-배열-전달하기)). ②, ④, ⑤, ⑥은 올바른 설명이다. ⑥에서 `int` 배열을 `double arr[]` 매개변수에 넘기면 원소 하나의 크기와 해석이 달라 올바르게 처리할 수 없으며, 컴파일러는 호환되지 않는 포인터 타입이라는 진단을 낸다.

---

<br>

## 연습 문제 7: 실수 배열을 채우고 합계를 구하는 함수

**교재 문항:** 7장 프로그래밍 과제 6번, 7번

**문제:** `double` 배열의 모든 원소를 한 값으로 채우는 `fill_array`와 원소의 합계를 반환하는 `sum_array`를 정의하고 시험하라. 실행 예시는 [연습 문제 7](Exercises.ko.md#연습-문제-7-실수-배열을-채우고-합계를-구하는-함수)에 있다.

### 풀이

**접근 방법:** 원소를 바꾸는 `fill_array`는 `double arr[]`로, 읽기만 하는 `sum_array`는 `const double arr[]`로 받고, 두 함수 모두 원소의 개수를 `size`로 받는다.

```c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define SIZE 5

void fill_array(double arr[], int size, double value)
{
    int i;

    for (i = 0; i < size; i++)
        arr[i] = value;
}

double sum_array(const double arr[], int size)
{
    double sum = 0.0;
    int i;

    for (i = 0; i < size; i++)
        sum += arr[i];
    return sum;
}

int main(void)
{
    double data[SIZE];
    int i;

    fill_array(data, SIZE, 1.5);
    printf("sum after fill = %.2f\n", sum_array(data, SIZE));

    printf("five real numbers? ");
    for (i = 0; i < SIZE; i++)
        scanf("%lf", &data[i]);
    printf("sum = %f\n", sum_array(data, SIZE));
    return 0;
}
```

- `fill_array(data, SIZE, 1.5)`는 배열의 시작 주소를 넘기므로 함수가 `data`의 원소를 직접 바꾼다. 합계는 1.5 × 5 = 7.50이다.
- `sum_array`의 누적 변수 `sum`은 0.0으로 초기화해야 하며, 반환형이 `double`이므로 실수 합계가 그대로 반환된다.
- `scanf("%lf", &data[i])`는 원소 하나의 주소를 넘긴다. 배열 원소도 변수이므로 `&`가 필요하다.

**실행 결과:**

```text
sum after fill = 7.50
five real numbers? 12.3 4.34 54.45 0.125 0.0002
sum = 71.215200
```

12.3 + 4.34 + 54.45 + 0.125 + 0.0002 = 71.2152이고, `%f`는 소수점 이하 6자리로 출력한다.

---

<br>

## 연습 문제 8: 좌석 예매

**교재 문항:** 7장 프로그래밍 과제 10번

**문제:** 10개 좌석의 상태를 0과 1로 저장하는 배열로, 요청한 수만큼 앞 번호부터 빈 좌석을 배정하는 예매 프로그램을 작성하라. 세부 조건과 실행 예시는 [연습 문제 8](Exercises.ko.md#연습-문제-8-좌석-예매)에 있다.

### 풀이

**접근 방법:** 예매된 좌석의 수 `reserved`를 따로 세어 두면, 남은 좌석 수는 `SEATS - reserved`로 바로 구할 수 있다. 배정은 배열을 앞에서부터 훑으며 0인 원소를 1로 바꾸고, 요청한 수만큼 배정하면 멈춘다.

```c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define SEATS 10

void print_seats(const int seat[], int size)
{
    int i;

    printf("seats: [");
    for (i = 0; i < size; i++)
        printf("%c", seat[i] ? 'X' : 'O');
    printf("]\n");
}

int main(void)
{
    int seat[SEATS] = { 0 };
    int reserved = 0, want, i, given;

    while (reserved < SEATS) {
        print_seats(seat, SEATS);
        printf("how many? ");
        if (scanf("%d", &want) != 1 || want <= 0)
            break;
        if (want > SEATS - reserved) {
            printf("only %d seats left\n", SEATS - reserved);
            continue;
        }
        printf("reserved:");
        for (i = 0, given = 0; i < SEATS && given < want; i++) {
            if (seat[i] == 0) {
                seat[i] = 1;
                printf(" %d", i + 1);
                given++;
            }
        }
        printf("\n");
        reserved += want;
    }
    print_seats(seat, SEATS);
    return 0;
}
```

- `int seat[SEATS] = { 0 };`은 모든 좌석을 빈 좌석으로 시작한다.
- `print_seats`는 배열을 바꾸지 않으므로 `const`로 받고, 조건 연산자로 0과 1을 `O`와 `X`로 바꾸어 출력한다.
- 바깥 `while`의 조건 `reserved < SEATS`가 거짓이 되면 모든 좌석이 찬 것이므로 반복을 끝낸다. 입력이 정수가 아니거나 0 이하이면 `break`로 끝낸다.
- 남은 좌석보다 많이 요청하면 안내만 출력하고 `continue`로 반복의 처음으로 돌아가므로 배열과 `reserved`는 바뀌지 않는다.
- 배정 반복은 `given < want`가 거짓이 되는 순간 멈추므로 요청한 수보다 많이 배정하지 않는다. 좌석 번호는 인덱스에 1을 더해 출력한다.

**실행 결과:** 입력 3, 4, 5, 3을 차례로 준 결과이다. 5좌석을 요청한 회차에는 남은 좌석이 3개여서 아무것도 배정하지 않고, 마지막 3좌석을 배정한 뒤 `reserved`가 10이 되어 반복이 끝난다.

```text
seats: [OOOOOOOOOO]
how many? 3
reserved: 1 2 3
seats: [XXXOOOOOOO]
how many? 4
reserved: 4 5 6 7
seats: [XXXXXXXOOO]
how many? 5
only 3 seats left
seats: [XXXXXXXOOO]
how many? 3
reserved: 8 9 10
seats: [XXXXXXXXXX]
```

---

<br>

## 연습 문제 9: 배열의 왼쪽 회전

**문제:** 정수 배열을 왼쪽으로 k칸 회전시키는 `rotate_left`를 작성하고, k가 원소의 개수 이상인 경우도 처리하라. 실행 예시는 [연습 문제 9](Exercises.ko.md#연습-문제-9-배열의-왼쪽-회전)에 있다.

### 풀이

**접근 방법:** 한 칸 회전은 첫 원소를 임시 변수에 저장하고, 나머지 원소를 한 칸씩 앞으로 당긴 뒤, 저장한 값을 맨 끝에 넣는 것이다. 이를 k번 되풀이한다. 원소가 n개이면 n칸 회전은 원래 배열과 같으므로 k를 `k % size`로 줄인다.

```c
#include <stdio.h>
#define SIZE 7

void rotate_left(int arr[], int size, int k)
{
    int i, j, first;

    k %= size;
    for (i = 0; i < k; i++) {
        first = arr[0];
        for (j = 0; j < size - 1; j++)
            arr[j] = arr[j + 1];
        arr[size - 1] = first;
    }
}

int main(void)
{
    int a[SIZE] = { 1, 2, 3, 4, 5, 6, 7 };
    int i;

    rotate_left(a, SIZE, 3);
    for (i = 0; i < SIZE; i++)
        printf("%d ", a[i]);
    printf("\n");
    rotate_left(a, SIZE, 11);
    for (i = 0; i < SIZE; i++)
        printf("%d ", a[i]);
    printf("\n");
    return 0;
}
```

한 칸 회전의 과정을 `{1, 2, 3, 4, 5, 6, 7}`로 따라가면, `first`에 1을 저장하고 `arr[0]`부터 `arr[5]`까지 각각 오른쪽 이웃의 값 2, 3, 4, 5, 6, 7을 받은 뒤 `arr[6]`에 1을 넣어 `{2, 3, 4, 5, 6, 7, 1}`이 된다. 안쪽 반복의 조건이 `j < size - 1`이므로 마지막으로 읽는 원소는 `arr[size - 1]`이며 범위를 넘지 않는다. 3번 회전하면 `4 5 6 7 1 2 3`이 된다. 두 번째 호출의 11칸은 `11 % 7` = 4칸과 같고, 앞의 3칸과 합쳐 모두 7칸을 회전했으므로 처음 배열로 돌아온다.

**실행 결과:**

```text
4 5 6 7 1 2 3
1 2 3 4 5 6 7
```

이 방법은 원소를 n번 옮기는 한 칸 회전을 k번 하므로 원소의 이동 횟수가 약 k × n이다. 크기가 k인 임시 배열에 앞의 k개를 옮겨 두고 나머지를 한 번에 당기면 이동 횟수를 약 n으로 줄일 수 있다.
