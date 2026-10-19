# Chapter 10 Exercises — Structures

[Repository Guide](../../README.md) | [English](Exercises.md) | [한국어](Exercises.ko.md)

> **Last Updated:** 2026-10-19

**Problem Source:** Prof. Younghee Im, Computer Language Ⅰ (DCCS101-04)

---

<br>

## Exercise 1: Student Structure

**Problem:** Define various functions that handle structures and complete the example code.

**Program Requirements:**

1. The function prototypes given below cannot be changed.

2. `void input_student(struct student *p);`
   A function that receives the address of a `student` structure variable, reads the name and the Korean, English, and math scores from the keyboard, and computes the average.
   Assume that no spaces are entered in the name, and do not compute `rank`.

3. `void display_student_arr(const struct student p[], int size);`
   A function that receives a `student` structure array and its size and prints the whole structure array (see the sample run).

4. `void swap_student(struct student *p1, struct student *p2);`
   A function that exchanges the contents of two `student` structure variables.
   This function is used in the `sort_student_arr()` function.

5. `void sort_student_arr(struct student p[], int size);`
   It receives a `student` structure array and its size and sorts it in descending order of the average.
   It also computes the `rank` values while sorting.

**Example Code:**

```c
#include <stdio.h>
#define MAX_STD 20

struct student {
   char name[20];
   int kor, eng, math;
   double avg;
   int rank;
};

void input_student(struct student *p);
void display_student_arr(const struct student p[], int size);
void swap_student(struct student *p1, struct student *p2);
void sort_student_arr(struct student p[], int size);

int main()
{
   struct student classA[MAX_STD];
   int size;

   printf("A클래스의 실제 학생수 입력: ");
   scanf_s("%d", &size);

   for (int i = 0; i < size; i++) {
      input_student(classA + i);
   }

   sort_student_arr(classA, size);
   display_student_arr(classA, size);

   return 0;
}
```

**Sample Run:**

```text
A클래스의 실제 학생 수 입력: 5

이름 입력: 김ㅇㅇ
국어: 53
영어: 41
수학: 37

이름 입력: 이ㅇㅇ
국어: 97
영어: 84
수학: 87

이름 입력: 박ㅇㅇ
국어: 64
영어: 88
수학: 71

이름 입력: 최ㅇㅇ
국어: 37
영어: 98
수학: 100

이름 입력: 정ㅇㅇ
국어: 67
영어: 89
수학: 76

------------------------------------------------
    이름    국어    영어    수학     평균     등수
------------------------------------------------
   이ㅇㅇ    97     84     87    89.33     1
   최ㅇㅇ    37     98    100    78.33     2
   정ㅇㅇ    67     89     76    77.33     3
   박ㅇㅇ    64     88     71    74.33     4
   김ㅇㅇ    53     41     37    43.67     5

Program ended with exit code: 0
```

**[Solution](Solutions.md#exercise-1-student-structure)**

---

<br>

## Exercise 2: Rectangle Structure

**Problem:** The rectangle structure `Rect` (`struct rectangle`) is defined by two diagonal corner points of the rectangle as follows. Write a program that satisfies the program requirements. The given function prototypes cannot be changed.

![Figure 1. Rectangle defined by its upper-left corner (x1, y1) and lower-right corner (x2, y2)](../../images/Ch10_Rectangle-Corners.png)

*Figure 1. Rectangle defined by its upper-left corner (x1, y1) and lower-right corner (x2, y2)*

```c
typedef struct point {
    int x, y;
} Point;

typedef struct rectangle {
    Point leftUp;
    Point rightDown;
} Rect;
```

**Program Requirements:**

1. The `main()` function
   - Declare a `rectangle` structure variable.
   - Read the coordinates of the two points of the rectangle from the user.
   - Call `isRectangle()` to verify whether the two points entered by the user form a rectangle, and if not, read them again until they do.
   - Call `computeArea()` to compute the area of the rectangle and print it.

2. `int isRectangle(Rect r);`
   - A function that receives one rectangle structure and verifies whether it forms a rectangle.
   - It returns 1 if a rectangle is formed and 0 otherwise.
   - It must not check by calling `computeArea()` and testing whether the area is 0.

3. `int computeArea(const Rect *p);`
   - A function that receives a rectangle structure variable as a parameter and computes and returns the area of the rectangle.

**Sample Run:**

```text
사각형의 좌표를 입력하세요.
좌상단 좌표: 1 3
우하단 좌표: 7 10
사각형의 면적 = 42

Program ended with exit code: 0
```

```text
사각형의 좌표를 입력하세요.
좌상단 좌표: -2 5
우하단 좌표: 7 5
입력 오류! 입력한 좌표로는 사각형을 만들 수 없습니다.

좌상단 좌표: 1 10
우하단 좌표: 1 -4
입력 오류! 입력한 좌표로는 사각형을 만들 수 없습니다.

좌상단 좌표: -2 5
우하단 좌표: 4 -1
사각형의 면적 = 36

Program ended with exit code: 0
```

**[Solution](Solutions.md#exercise-2-rectangle-structure)**
