# 8차 과제

**문항 출처:** *이종욱 교수, 컴퓨터언어실습Ⅰ 교수자 (DCCS103-03) / 박철원* <br>
**Source:** *Prof. Jonguk&nbsp;Lee, Instructor of COMPUTER LANGUAGE AND TRAINING Ⅰ (DCCS103-03) / Cheolwon Park*

---

## Q1. 맞바꾸기

실행 예시를 참고하여 두 변수에 저장된 데이터를 맞바꾸는 프로그램을 작성하시오. 이때, 포인터를 사용해 두 값을 바꾸는 swap() 함수를 정의하여 활용한다.


<br>**실행 예시**

```text
초기상태: a = 3, b = 8
맞바꾸기: a = 8, b = 3

Program ended with exit code: 0
```



---

## Q2. 배열 연산

아래와 같이 선언된 3개의 배열 arrX, arrY, arrZ가 존재한다.
```c
int arrX[4] = { -2, 4, 6, -32 };
int arrY[4] = { 4, 3, -5, 6 };
int arrZ[4] = { 0 };
```
아래에 주어진 함수의 선언을 변경하지 않고 활용하여 arrX와 arrY의 각 원소끼리 합한 뒤, 연산 결과를 arrZ 배열에 저장하고 배열의 내용을 출력하시오.
```c
void arrSum(int* pX, int* pY, int* pZ);
```


<br>**실행 예시**

```text
arrZ:  2   7   1  -26

Program ended with exit code: 0
```



---