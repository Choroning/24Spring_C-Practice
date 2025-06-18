# Chapter 7. 배열 실습

**문항 출처:** *임영희 교수, 컴퓨터언어Ⅰ 교수자 (DCCS101-04)* <br>
**Source:** *Prof. Younghee&nbsp;Im, Instructor of COMPUTER LANGUAGE Ⅰ (DCCS101-04)*

---

## Q1. UPC 바코드의 Check Digit 계산

UPC 바코드는 총 12자리 숫자로 이루어지며, 마지막 12번째 숫자는 이전 11자리의 숫자를 바탕으로 생성된 오류 검증용 숫자이다. 아래에 12번째 숫자를 생성하는 프로그램의 예시 코드가 주어질 때, 이를 배열을 이용하도록 변환하여 작성하시오.

<br>**예시 코드**

```c
#include <stdio.h>
int main() {
    int dig1, dig2, dig3, dig4, dig5, dig6, dig7, dig8, dig9, dig10, dig11, dig12, sum;

    printf("Please enter the first eleven UPC digits, seperated by white space: \n");

    scanf("%d%d%d%d%d%d%d%d%d%d%d", &dig1, &dig2, &dig3, &dig4, &dig5, &dig6, &dig7, &dig8, &dig9, &dig10, &dig11);

    printf("입력된 숫자: %d%d%d%d%d%d%d%d%d%d%d", dig1, dig2, dig3, dig4, dig5, dig6, dig7, dig8, dig9, dig10, dig11);

    sum = 3 * (dig1 + dig3 + dig5 + dig7 + dig9 + dig11);
    sum = sum + (dig2 + dig4 + dig6 + dig8 + dig10);
    dig12 = (10 - sum % 10) % 10;

    printf("The check digit is %d \n", dig12);

    return 0;
}
```


<br>**프로그램 요구사항**

1. 배열을 이용하도록 바꿔 작성하시오.
2. 배열의 크기는 매크로 상수로 지정하여 사용하시오.


<br>**실행 예시**

```text
Please enter the first eleven UPC digits, seperated by white space:
0 3 6 0 0 0 2 9 1 4 5
입력된 숫자: 03600029145
The check digit is 2

Program ended with exit code: 0
```


---

## Q2. 선택 정렬 변형

아래 `예제7-11`의 선택정렬을 오름차순으로 정렬하되 최댓값을 선택하여 자리를 찾는 방식으로 방식으로 변경하여 작성하시오.

![선택정렬 코드: 교재 262p. 예제7-11](/src/images/C7_A10104-1_1.png)



---

## Q3. 빈도와 상대 빈도 계산

원소의 개수가 40개인 1차원 정수 배열을 150 - 199 사이의 임의의 값으로 채우고, 구간별 빈도수와 상대 빈도수를 계산하여 출력하는 프로그램을 작성하시오.

<br>**프로그램 요구사항**

1. 각 구간의 빈도수와 상대 빈도수를 저장할 배열 선언
```c
int frequency[5] = { 0 };
double relative_freq[5];
```
2. `rand()` 함수를 이용하여 배열의 원소값(150 - 199) 대입
3. `srand()` 함수를 호출하여 `rand()` 함수의 seed 값 변경
```c
srand((unsigned)time(NULL))
```
4. 빈도수 계산 시 `switch`문을 사용하시오.


<br>**실행 예시**

```text
배열 내용:
165  183  186  171  165  190  174  151  152  198
193  172  196  165  199  181  181  167  155  160
191  191  175  184  187  197  160  164  198  155
155  152  157  165  170  169  153  196  151  169

------------------------------
값의 범위        도수      상대도수
------------------------------
150 - 159       9       0.225
160 - 169      10       0.250
170 - 179       5       0.125
180 - 189       6       0.150
190 - 199      10       0.250

Program ended with exit code: 0
```


---