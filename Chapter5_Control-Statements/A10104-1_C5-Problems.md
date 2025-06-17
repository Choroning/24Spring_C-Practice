# Chapter 5. 조건문(선택문) 실습

**문항 출처:** *임영희 교수, 컴퓨터언어Ⅰ 교수자 (DCCS101-04)* <br>
**Source:** *Prof. Younghee&nbsp;Im, Instructor of COMPUTER LANGUAGE Ⅰ (DCCS101-04)*

---

## Q1. 이차원 평면의 점 좌표 사분면 판별

이차원 평면에 있는 점의 좌표 `(x,y)`를 입력받아 어느 사분면에 위치한 점인지 출력하는 프로그램을 작성하시오. (교재 182p. 3번)

- **입력(Input)**: 점 좌표(x축 값, y축 값)
- **출력(Output)**: 원점, x축 위, y축 위, 제n사분면 위의 점 중 하나

<br>**실행 예시**

```text
점의 좌표 (x,y)? 0 0
(0,0)은 원점에 위치합니다.

Program ended with exit code: 0
```

```text
점의 좌표 (x,y)? -2 0
(-2,0)은 x축 위에 위치합니다.

Program ended with exit code: 0
```

```text
점의 좌표 (x,y)? 0 10
(0,10)은 y축 위에 위치합니다.

Program ended with exit code: 0
```

```text
점의 좌표 (x,y)? 3 7
(3,7)은 1사분면 위에 위치합니다.

Program ended with exit code: 0
```

```text
점의 좌표 (x,y)? 8 -2
(8,-2)은 4사분면 위에 위치합니다.

Program ended with exit code: 0
```


---

## Q2. 섭씨 ↔ 화씨 단위 변환

온도를 입력받아 섭씨는 화씨로, 화씨는 섭씨로 변환하는 프로그램을 작성하시오. (교재 183p. 5번)

![섭씨온도=(5/9)*(화씨온도-32), 화씨온도=(9/5)*(섭씨온도+32)](/src/images/C5_A10104-1_1.png)

- **입력(Input)**: 온도 및 온도 단위(섭씨는 C, 화씨는 F)
- **출력(Output)**: 단위 변환된 온도


<br>**프로그램 요구사항**

1. 온도 단위는 대소문자, 띄어쓰기 구분 없이 입력받을 수 있어야 합니다.
2. switch문을 사용해 작성하십시오.


<br>**실행 예시**

```text
온도? 32C
32 C == 89.60 F

Program ended with exit code: 0
```

```text
온도? 100 f
100 F == 37.78 C

Program ended with exit code: 0
```

```text
온도? -28 g
입력 오류! 온도의 단위는 C(또는 c)와 F(또는 f)만 가능합니다.

Program ended with exit code: 0
```


---

## Q3. 이차 방정식의 근 계산

이차 방정식(`ax²+bx+c=0`)의 상관계수 a, b, c를 입력받아 근을 계산하는 프로그램을 작성하시오.

- **입력(Input)**: 이차 방정식의 상관계수 a, b, c (단, a ≠ 0이고 a, b, c는 모두 정수)
- **출력(Output)**: 이차 방정식의 근


<br>**프로그램 요구사항**

1. 판별식(`b²-4ac`)의 값에 따라 이차 방정식의 근은 다음과 같이 판별할 수 있다.
![b²-4ac이 0보다 작을 경우, 허근을 갖는다. 0일 경우, 중근을 갖는다. 0보다 큰 경우, 서로 다른 두 근을 갖는다. 근을 구할 때는 이차 방정식의 근의 공식을 활용하시오.](/src/images/C5_A10104-1_2.png)
2. 근을 구할 때, 정수 나눗셈이 발생하지 않도록 주의하여 정확한 계산 결과를 출력해야 한다.
3. 제곱근은 라이브러리 함수 `sqrt()`를 이용하여 계산한다. (헤더 `<math.h>`)


<br>**실행 예시**

```text
이차 방정식의 상관계수 a, b, c 입력: 3 -1 -2
입력하신 이차 방정식은 두 근 x1 = 1, x2 = -0.666667 을 갖습니다.

Program ended with exit code: 0
```

```text
이차 방정식의 상관계수 a, b, c 입력: 9 -12 4
입력하신 이차 방정식은 중근 x = 0.666667 을 갖습니다.

Program ended with exit code: 0
```

```text
이차 방정식의 상관계수 a, b, c 입력: 1 1 1
입력하신 이차 방정식은 허근을 갖습니다.

Program ended with exit code: 0
```


---
