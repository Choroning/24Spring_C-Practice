# Chapter 5. 4차 과제

**문항 출처:** *이종욱 교수, 컴퓨터언어실습Ⅰ 교수자 (DCCS103-03)* <br>
**Source:** *Prof. Jonguk&nbsp;Lee, Instructor of COMPUTER LANGUAGE AND TRAINING Ⅰ (DCCS103-03)*

---

## Q1. 영문자 변환

실행 예시를 참고하여 사용자로부터 임의의 영문 소문자를 입력받은 후, 대문자로 변환하여 출력하는 프로그램을 작성하시오.


<br>**실행 예시**

```text
>> Input char: q
-> Changed lower case q to upper case Q!

Program ended with exit code: 0
```

```text
>> Input char: G
-> Input error!

Program ended with exit code: 0
```



---

## Q2. 홀짝 판별

실행 예시를 참고하여 사용자로부터 임의의 정수를 입력받은 후, 홀짝 여부를 판별하여 출력하는 프로그램을 작성하시오.


<br>**실행 예시**

```text
>> Input value: 3
-> 3 is an odd number!

Program ended with exit code: 0
```

```text
>> Input value: 6
-> 6 is an even number!

Program ended with exit code: 0
```



---

## Q3. switch-if 변환 (1)

예시 코드를 참고하여 if문을 사용한 코드를 switch문을 사용하도록 바꾸어 작성하시오.


<br>**예시 코드**

```c
#include <stdio.h>

int main()
{
	int score;
	printf(">> Input score(0~100): ");
	scanf(" %d", &score);

	if (score >= 90 && score <= 100)
		printf("%d is a/an A!", score);
	else if (score >= 80 && score <= 89)
		printf("%d is a/an B!", score);
	else if (score >= 70 && score <= 79)
		printf("%d is a/an C!", score);
	else if (score >= 60 && score <= 69)
		printf("%d is a/an D!", score);
	else if (score < 60 && score >= 0)
		printf("%d is a/an F!", score);
	else
		printf("Input error!");
}
```



---

## Q4. switch-if 변환 (2)

예시 코드를 참고하여 switch문을 사용한 코드를 if문을 사용하도록 바꾸어 작성하시오.


<br>**예시 코드**

```c
#include <stdio.h>

int main()
{
	int grade;

	printf(">> Input grade(1~7): ");
	scanf(" %d", &grade);

	switch (grade) {
	case 1:
		printf("Very good!");
		break;
	case 2:
	case 3:
		printf("Good!");
		break;
	case 4:
	case 5:
		printf("So So!");
		break;
	case 6:
	case 7:
		printf("Cheer up!");
		break;
	default:
		printf("Input error!");
	}
}
```



---

## Q5. switch 분기 연습

사용자로부터 임의의 영문자를 입력받은 후, 해당 영문자의 첫 글자로 시작하는 프로그래밍 언어명을 출력하는 프로그램을 작성하시오.


<br>**프로그램 요구사항**

1. `switch`문을 사용해 작성하십시오.
2. 각 영문자는 아래와 같이 대응하시오.
    - `c` or `C` 입력 시 `C Language` 출력
    - `p` or `P` 입력 시 `Python` 출력
    - `j` or `J` 입력 시 `JAVA` 출력
    - `l` or `L` 입력 시 `LISP` 출력
    - 이외의 영문자 입력 시 `Input Error!` 출력


<br>**실행 예시**

```text
>> Input the character: p
-> Python

Program ended with exit code: 0
```

```text
>> Input the character: C
-> C Language

Program ended with exit code: 0
```

```text
>> Input the character: m
-> Input Error!

Program ended with exit code: 0
```


---