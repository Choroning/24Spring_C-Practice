# 4장 연습 문제 풀이 — 연산자

[레포지토리 안내](../../README.ko.md) | [English](Solutions.md) | [한국어](Solutions.ko.md)

> **최종 수정일:** 2026-10-19
>
> Warming-Up C Programming, 천정아, Ch 4

**문항 출처:** 임영희 교수, 컴퓨터언어Ⅰ (DCCS101-04)

---

<br>

## 목차

- [연습 문제 1: 헬멧의 체적과 표면적 계산](#연습-문제-1-헬멧의-체적과-표면적-계산)
- [연습 문제 2: 시간과 초의 환산](#연습-문제-2-시간과-초의-환산)
- [연습 문제 3: Red, Green, Blue 값을 16진수 RGB 값으로 변환](#연습-문제-3-red-green-blue-값을-16진수-rgb-값으로-변환)
- [연습 문제 4: 16진수 RGB 값을 Red, Green, Blue 값으로 변환](#연습-문제-4-16진수-rgb-값을-red-green-blue-값으로-변환)

---

<br>

## 연습 문제 1: 헬멧의 체적과 표면적 계산

**문제:** 정수로 입력받은 헬멧의 높이 h와 밑면 반지름 a로 체적 $V = \frac{\pi}{6} h (3a^2 + h^2)$와 표면적 $S = 2\pi \left(\frac{h}{3} + \frac{V}{\pi h^2}\right) h$를 계산하라. π는 `#define`으로 정의한 3.14159265를 쓰고, 정수 나눗셈이 일어나지 않게 한다. 문제 전문과 실행 예시는 [연습 문제 1](Exercises.ko.md#연습-문제-1-헬멧의-체적과-표면적-계산)에 있다.

### 풀이

**접근 방법:** 입력은 `int`이지만 계산 결과는 소수이므로, 나눗셈이 들어가는 모든 곳에서 피연산자 하나 이상이 실수형이 되게 한다([4장 2.2절](Concepts_Lecture.ko.md#22-정수-나눗셈-vs-실수-나눗셈)).

- **매크로 상수:** `#define PI 3.14159265`로 π를 정의한다. 전처리기가 `PI`를 실수 리터럴 `3.14159265`로 바꾸므로 `PI`가 들어간 식은 `double`로 계산된다.
- **체적:** `(PI / 6.0 * height)`는 `double`이고, 두 번째 괄호 `(3 * base_radius * base_radius + height * height)`는 `int`로 계산된 뒤 곱셈에서 `double`로 변환된다. 나눗셈은 `PI / 6.0` 하나뿐이고 두 피연산자가 모두 실수이다.
- **표면적:** `height / 3.0`처럼 분모를 실수 리터럴로 써서 정수 나눗셈을 피한다. `height / 3`으로 쓰면 높이가 1일 때 0이 되어 결과가 틀린다. `volume / (PI * height * height)`는 분자와 분모가 모두 `double`이다.
- **출력:** `printf`의 `%lf`는 C99부터 `%f`와 같은 뜻이며 소수점 아래 6자리를 출력한다.

공식을 정리하면 $\frac{V}{\pi h^2} = \frac{3a^2 + h^2}{6h}$이므로 $S = 2\pi h \cdot \frac{a^2 + h^2}{2h} = \pi (a^2 + h^2)$, 즉 구관(spherical cap)의 곡면 넓이가 된다. 매크로 값 3.14159265를 π로 쓰면 h = 1, a = 1에서 $2 \times 3.14159265 \approx 6.283185$이고, h = 12, a = 20에서 $544 \times 3.14159265 \approx 1709.026402$로 실행 예시와 같다.

**코드:** [Lab_Q1.c](../../Coursework/Lab04_Operators/Lab_Q1.c)

```c
/**
 * @file    A10104-1_C04Q1.c
 * @brief   Q1. 헬멧의 체적과 표면적 계산
 * @author  박철원 (Cheolwon Park)
 * @date    2024-03-26
 * 
 * @note    소스 코드에 사용된 scanf_s는 Visual Studio 이외의
 * 	    IDE에서 실행이 불가할 수 있음에 주의하시기 바랍니다.
 */

#include <stdio.h>
#define PI 3.14159265

int main()
{
	int height, base_radius;
	double volume, surface_area;

	printf("헬멧의 높이: ");
	scanf_s(" %d", &height);

	printf("base 반지름 입력: ");
	scanf_s(" %d", &base_radius);

	volume = (PI / 6.0 * height) * (3 * base_radius * base_radius + height * height);
	surface_area = 2.0 * PI * ((height / 3.0) + (volume / (PI * height * height))) * height;

	printf("헬멧의 체적: %lf \n", volume);
	printf("헬멧의 표면적: %lf \n", surface_area);
}
```

**실행 결과:** 두 실행 예시와 같은 값을 입력하면 같은 체적과 표면적이 출력된다. 코드는 형식 문자열 끝의 `" \n"` 때문에 각 줄 끝에 공백을 하나 남긴다. 실행 예시의 마지막 줄 `Program ended with exit code: 0`은 프로그램의 출력이 아니라 Xcode 콘솔이 덧붙이는 종료 메시지이다.

```text
헬멧의 높이: 1
base 반지름 입력: 1
헬멧의 체적: 2.094395 
헬멧의 표면적: 6.283185 
```

```text
헬멧의 높이: 12
base 반지름 입력: 20
헬멧의 체적: 8444.601043 
헬멧의 표면적: 1709.026402 
```

> **참고:** **`scanf_s`와 실행 환경.** 이 장의 코드가 쓰는 `scanf_s`는 Visual Studio(MSVC)가 제공하는 함수이다. C11의 선택 사항인 부록 K(Annex K)에도 같은 이름의 함수가 정의되어 있지만, gcc와 clang이 쓰는 표준 라이브러리 대부분은 이를 제공하지 않으므로 그대로 컴파일하면 선언되지 않은 함수라는 오류가 난다. 위의 실행 결과는 코드를 바꾸지 않고 `gcc -std=c99 -Wall -Dscanf_s=scanf`로 `scanf_s`를 `scanf`로 대체하여 컴파일한 것이다. `%d`, `%x`처럼 숫자를 읽는 변환에서는 두 함수의 동작이 같다.

> **주의:** 높이로 0을 입력하면 `volume / (PI * height * height)`가 0을 0으로 나누므로 표면적이 `nan`(Not a Number)으로 출력된다. 실수 나눗셈은 0으로 나누어도 프로그램이 멈추지 않고 무한대나 `nan`을 낸다. 또 `3 * base_radius * base_radius`는 `int`로 계산되므로, a가 26754보다 크면 `int`의 범위를 넘는다.

```text
헬멧의 높이: 0
base 반지름 입력: 5
헬멧의 체적: 0.000000 
헬멧의 표면적: nan 
```

---

<br>

## 연습 문제 2: 시간과 초의 환산

**교재 문항:** 4장 연습 문제 8번 응용

**문제:** 시, 분, 초를 입력받아 전체 초로 환산하고, 이어서 전체 초를 입력받아 시, 분, 초로 환산하라. 기호 상수 `SEC_PER_HOUR`(3600)와 `SEC_PER_MIN`(60)을 사용한다. 문제 전문과 실행 예시는 [연습 문제 2](Exercises.ko.md#연습-문제-2-시간과-초의-환산)에 있다.

### 풀이

**접근 방법:** 앞의 환산은 곱셈과 덧셈으로, 뒤의 환산은 정수 나눗셈의 몫과 나머지로 한다([4장 2.3절](Concepts_Lecture.ko.md#23-나머지-연산자)). 여기서는 소수 부분을 버리는 정수 나눗셈이 바로 필요한 연산이다.

- **시, 분, 초 → 초:** `hour * SEC_PER_HOUR + min * SEC_PER_MIN + sec`이다. 2시간 10분 47초는 7200 + 600 + 47 = 7847초이다.
- **초 → 시:** `second_sum2 / SEC_PER_HOUR`는 3600초 단위의 몫이다. 3989초이면 1시간이다.
- **초 → 분:** 시간을 빼고 남은 초 `second_sum2 % SEC_PER_HOUR`를 60으로 나눈 몫이다. 3989 % 3600 = 389이고 389 / 60 = 6분이다.
- **초 → 초:** `second_sum2 % SEC_PER_MIN`이다. 3600은 60의 배수이므로 60으로 나눈 나머지는 시간을 뺀 뒤의 나머지와 같다. 3989 % 60 = 29초이다.

**코드:** [Lab_Q2.c](../../Coursework/Lab04_Operators/Lab_Q2.c)

```c
/**
 * @file    A10104-1_C04Q2.c
 * @brief   Q2. 시간 - 초 환산
 * @author  박철원 (Cheolwon Park)
 * @date    2024-03-27
 *  
 * @note    소스 코드에 사용된 scanf_s는 Visual Studio 이외의
 * 	    IDE에서 실행이 불가할 수 있음에 주의하시기 바랍니다.
 */

#define SEC_PER_HOUR 3600
#define SEC_PER_MIN 60
#include <stdio.h>

int main()
{
	int hour, min, sec;
	int hour_cal, min_cal, sec_cal;
	int second_sum1, second_sum2;

	printf("시간을 차례로 입력하세요(시,분,초): ");
	scanf_s(" %d %d %d", &hour, &min, &sec);

	second_sum1 = hour * SEC_PER_HOUR + min * SEC_PER_MIN + sec;

	printf("%d시간 %d분 %d초는 총 %d초입니다. \n", hour, min, sec, second_sum1);
	printf("\n---------------------------------\n");

	printf("환산할 초를 입력하세요: ");
	scanf_s(" %d", &second_sum2);

	hour_cal = (second_sum2 / SEC_PER_HOUR);
	min_cal = (second_sum2 % SEC_PER_HOUR) / SEC_PER_MIN;
	sec_cal = (second_sum2 % SEC_PER_MIN);

	printf("%d초는 %d시간 %d분 %d초입니다. \n", second_sum2, hour_cal, min_cal, sec_cal);
}
```

**실행 결과:** 환산 값은 두 실행 예시와 같다. 다만 코드는 구분선 앞에 `"\n"`을 하나 더 출력하므로 구분선 위에 빈 줄이 생기고, 구분선의 `-`는 실행 예시의 35개가 아니라 33개이다. 각 결과 줄 끝에는 공백이 하나 남는다.

```text
시간을 차례로 입력하세요(시,분,초): 2 10 47
2시간 10분 47초는 총 7847초입니다. 

---------------------------------
환산할 초를 입력하세요: 3989
3989초는 1시간 6분 29초입니다. 
```

```text
시간을 차례로 입력하세요(시,분,초): 7 1 55
7시간 1분 55초는 총 25315초입니다. 

---------------------------------
환산할 초를 입력하세요: 25315
25315초는 7시간 1분 55초입니다. 
```

> **참고:** 음수 초를 입력하면 C99의 정수 나눗셈이 0 방향으로 절삭하고 나머지의 부호가 피제수를 따르므로, 시, 분, 초가 모두 음수로 출력된다. 문제는 0 이상의 입력을 가정한다.

```text
시간을 차례로 입력하세요(시,분,초): 0 0 0
0시간 0분 0초는 총 0초입니다. 

---------------------------------
환산할 초를 입력하세요: -3725
-3725초는 -1시간 -2분 -5초입니다. 
```

---

<br>

## 연습 문제 3: Red, Green, Blue 값을 16진수 RGB 값으로 변환

**문제:** 0~255의 Red, Green, Blue 값을 입력받아 그림 2의 배치대로 하나의 4바이트 RGB 값으로 합치고 6자리 16진수로 출력하라. 문제 전문과 실행 예시는 [연습 문제 3](Exercises.ko.md#연습-문제-3-red-green-blue-값을-16진수-rgb-값으로-변환)에 있다.

### 풀이

**접근 방법:** 각 채널을 자기 자리로 왼쪽 시프트한 뒤 비트 OR로 합친다([4장 6.3절](Concepts_Lecture.ko.md#63-실전-예제-rgb-색상)). Red는 0비트, Green은 8비트, Blue는 16비트만큼 옮긴다.

- **결합:** `RGB = red | green << 8 | blue << 16;`은 괄호가 없지만, `<<`가 `|`보다 우선순위가 높으므로 `red | (green << 8) | (blue << 16)`으로 계산된다([4장 10.1절](Concepts_Lecture.ko.md#101-우선순위-표)). 세 값의 1인 비트가 서로 겹치지 않으므로 OR는 덧셈과 같은 결과를 낸다. 주석으로 남긴 `|=` 세 줄도 같은 과정을 복합 대입으로 쓴 것이다.
- **출력:** `%#08X`에서 `#`은 16진수 앞에 `0X`를 붙이고, `0`은 빈자리를 0으로 채우며, 폭 8은 `0X`를 포함한 전체 글자 수이다. 따라서 16진수 부분은 6자리가 되어 `0X8200FF`, `0X0DC843`처럼 출력된다.

**코드:** [Lab_Q3.c](../../Coursework/Lab04_Operators/Lab_Q3.c)

```c
/**
 * @file    A10104-1_C04Q3.c
 * @brief   Q3. 4바이트 RGB값을 16진수 RGB값으로 변환
 * @author  박철원 (Cheolwon Park)
 * @date    2024-03-27
 *  
 * @note    소스 코드에 사용된 scanf_s는 Visual Studio 이외의
 * 	    IDE에서 실행이 불가할 수 있음에 주의하시기 바랍니다.
 */

#include <stdio.h>

int main()
{
	int red, green, blue;
	int RGB = 0;

	printf("Red 값 입력(0~255): ");
	scanf_s(" %d", &red);
	printf("Green 값 입력(0~255): ");
	scanf_s(" %d", &green);
	printf("Blue 값 입력(0~255): ");
	scanf_s(" %d", &blue);

	RGB = red | green << 8 | blue << 16;

	/* 위와 동일한 과정
	RGB |= blue << 16;
	RGB |= green << 8;
	RGB |= red; */

	printf("RGB = %#08X", RGB);
}
```

**실행 결과:** RGB 값은 두 실행 예시와 같다. 입력 안내 문구는 `(0-255)`가 아니라 `(0~255)`이고, 코드가 `RGB =` 앞에 빈 줄을 출력하지 않으며 마지막 줄 뒤에 줄바꿈도 출력하지 않는다.

```text
Red 값 입력(0~255): 255
Green 값 입력(0~255): 0
Blue 값 입력(0~255): 130
RGB = 0X8200FF
```

```text
Red 값 입력(0~255): 67
Green 값 입력(0~255): 200
Blue 값 입력(0~255): 13
RGB = 0X0DC843
```

> **주의:** **경계 입력.** `#` 플래그는 값이 0이면 접두사를 붙이지 않으므로, 세 값이 모두 0이면 `0X000000`이 아니라 `00000000`이 출력된다. 또 범위 검사가 없으므로 255보다 큰 값을 입력하면 이웃 채널의 비트를 침범한다. Red에 256을 입력하면 비트 8이 켜져 Green이 1인 것과 같은 `0X000100`이 된다.

```text
Red 값 입력(0~255): 0
Green 값 입력(0~255): 0
Blue 값 입력(0~255): 0
RGB = 00000000
```

```text
Red 값 입력(0~255): 256
Green 값 입력(0~255): 0
Blue 값 입력(0~255): 0
RGB = 0X000100
```

---

<br>

## 연습 문제 4: 16진수 RGB 값을 Red, Green, Blue 값으로 변환

**문제:** 6자리 16진수 RGB 값을 입력받아 Red, Green, Blue 값을 추출하고 각각 2자리 16진수와 10진수로 출력하라. 문제 전문과 실행 예시는 [연습 문제 4](Exercises.ko.md#연습-문제-4-16진수-rgb-값을-red-green-blue-값으로-변환)에 있다.

### 풀이

**접근 방법:** 원하는 채널을 하위 8비트로 오른쪽 시프트한 뒤 `& 0xFF`로 나머지 비트를 지운다([4장 6.3절](Concepts_Lecture.ko.md#63-실전-예제-rgb-색상)).

- **입력:** `%x`는 16진수를 읽으며 대문자와 소문자를 모두 받는다. `A73803`은 10진수 10958851로 저장된다.
- **Red:** `RGB & 0xFF`로 하위 8비트 `0x03`을 꺼낸다.
- **Green:** `(RGB >> 8) & 0xFF`로 비트 8~15를 하위로 옮긴 뒤 꺼낸다. `0xA738`의 하위 8비트인 `0x38`이 남는다.
- **Blue:** `RGB >> 16`만 하고 마스크는 하지 않는다. 6자리 이하의 입력이면 비트 24 이상이 0이므로 `0xA7`만 남는다.
- **출력:** `%#04x`는 `0x`를 포함하여 폭 4로 출력하므로 16진수 부분이 2자리가 된다.

**코드:** [Lab_Q4.c](../../Coursework/Lab04_Operators/Lab_Q4.c)

```c
/**
 * @file    A10104-1_C04Q4.c
 * @brief   Q4. 16진수 RGB값을 4바이트 RGB값으로 변환
 * @author  박철원 (Cheolwon Park)
 * @date    2024-03-27
 *  
 * @note    소스 코드에 사용된 scanf_s는 Visual Studio 이외의
 * 	    IDE에서 실행이 불가할 수 있음에 주의하시기 바랍니다.
 */

#include <stdio.h>

int main()
{
	int RGB = 0;
	int red, green, blue;

	printf("RGB 값을 입력(16진수 6자리): ");
	scanf_s(" %x", &RGB);

	red = (RGB & 0xFF);
    // AND 연산을 이용하여 0~7번째 비트(하위 8비트) 추출
    // 예: 00000000 00000000 11111111 => 0x0000FF => 255

    green = ((RGB >> 8) & 0xFF);
    // RGB를 오른쪽으로 8비트 시프트한 뒤
    // AND 연산으로 0~7번째 비트(녹색 정보) 추출

    blue = (RGB >> 16);
    // RGB를 오른쪽으로 16비트 시프트하여
    // 하위 8비트(파란색 정보)만 남김

	printf("\nRed    = %#04x (%d) \n", red, red);
	printf("Green  = %#04x (%d) \n", green, green);
	printf("Blue   = %#04x (%d) \n", blue, blue);
} 
```

**실행 결과:** 추출한 값은 두 실행 예시와 같다. 출력 형식에는 다음 차이가 있다. 형식 지정자가 소문자 `x`이므로 `0X03`이 아니라 `0x03`처럼 소문자로 출력되고, `Red`, `Green`, `Blue` 뒤의 공백 수와 괄호 앞의 공백, 줄 끝의 공백도 실행 예시와 다르다. Green이 0인 두 번째 실행에서는 `#` 플래그가 0에 접두사를 붙이지 않으므로 `0x00`이 아니라 `0000`이 출력된다. 입력 안내 문구는 `RGB 값을 입력`이다.

```text
RGB 값을 입력(16진수 6자리): A73803

Red    = 0x03 (3) 
Green  = 0x38 (56) 
Blue   = 0xa7 (167) 
```

```text
RGB 값을 입력(16진수 6자리): FF00DD

Red    = 0xdd (221) 
Green  = 0000 (0) 
Blue   = 0xff (255) 
```

> **참고:** `scanf`의 `%x`는 `unsigned int *`를 기대하므로 `RGB`는 `unsigned int`로 선언하는 것이 정확하다. 또 Blue에 마스크를 하지 않았기 때문에 7자리 이상을 입력하면 Blue에 위쪽 비트가 섞인다. `1A73803`을 입력하면 Blue가 `0x1a7`(423)이 되며, `(RGB >> 16) & 0xFF`로 마스크하면 이런 경우에도 하위 8비트만 남는다.

```text
RGB 값을 입력(16진수 6자리): 1A73803

Red    = 0x03 (3) 
Green  = 0x38 (56) 
Blue   = 0x1a7 (423) 
```
