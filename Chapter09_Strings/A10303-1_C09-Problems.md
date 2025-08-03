# 10차 과제

**문항 출처:** *이종욱 교수, 컴퓨터언어실습Ⅰ 교수자 (DCCS103-03) / 박철원* <br>
**Source:** *Prof. Jonguk&nbsp;Lee, Instructor of COMPUTER LANGUAGE AND TRAINING Ⅰ (DCCS103-03) / Cheolwon Park*

---

## Q1. 문자열 검색

사용자로부터 입력받은 문자열에 포함된 대소문자 개수를 각각 찾아 출력하는 프로그램을 작성하시오.


<br>**실행 예시**

```text
Input str: aB3 2# dfkW
Uppercase letters: 2
Lowercase letters: 4

Program ended with exit code: 0
```



---

## Q2. 문자열 뒤집기

사용자로부터 입력받은 문자열을 역순으로 뒤집어 출력하는 프로그램을 작성하시오.


<br>**프로그램 요구사항**

1. 사용자로부터 입력받은 문자열을 역순으로 뒤집어 저장하는 `revStr()` 함수를 정의하여 사용하시오.
2. `<string.h>` 라이브러리를 사용하지 않고 작성하시오.


<br>**실행 예시**

```text
Input str: aB3 2# dfkW
Reversed str: Wkfd #2 3Ba

Program ended with exit code: 0
```



---

## Q3. 문자열 분리

실행 예시를 참고하여 사용자로부터 입력받은 문자열에 공백이 포함된 경우 해당 지점에서 줄바꿈을 수행한 뒤 이어 출력하는 프로그램을 작성하시오.


<br>**프로그램 요구사항**

1. `<ctype.h>` 라이브러리를 사용하여 배열의 요소가 공백 문자(`Space` 또는 `Tab`)인지 확인하는 `isspace()` 라이브러리 함수를 활용하시오. `isspace()`는 다음과 같은 방식으로 작동합니다.
    ```text
    본 함수는 라이브러리 내에 int isspace(int c); 의 형태로 선언되어 있습니다. char 형태의 인자를 전달할 경우, 자동으로 정수형으로 변환되어 처리합니다.

    매개변수로 받은 인자가 공백 문자이면 0이 아닌 값(true)를 반환, 그렇지 않으면 0(false)를 반환합니다.

    isspace()는 ' ', '\t', '\n', '\v', '\f', '\r'의 여섯 개의 문자(일반공백 및 모든 공백계열 제어문자)를 공백 문자로 판단합니다.
    ```

2. `fgets()` 함수를 사용하여 사용자 입력을 처리하시오. 이때, 마지막에 입력을 완료하고자 입력하는 개행 문자  (`Enter` 또는 `\n`)가 입력받은 내용과 함께 저장됩니다. 이 개행 문자는 아래 명령을 덧붙여 삭제할 수 있음을 참고하시오.
    ```c
    str[strcspn(str, "\n")] = '\0';
    ```
    `strcspn()` 라이브러리 함수 사용을 위해서 `<string.h>` 라이브러리를 사용해야 함에 유의하시오.
  

<br>**실행 예시**

```text
Input str: aB 3# ! D
Output:
aB
3#
!
D

Program ended with exit code: 0
```



---