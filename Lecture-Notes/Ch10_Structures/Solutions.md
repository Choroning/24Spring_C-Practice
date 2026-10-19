# Chapter 10 Solutions — Structures

[Repository Guide](../../README.md) | [English](Solutions.md) | [한국어](Solutions.ko.md)

> **Last Updated:** 2026-10-19

**Problem Source:** Prof. Younghee Im, Computer Language Ⅰ (DCCS101-04)

---

<br>

## Table of Contents

- [Exercise 1: Student Structure](#exercise-1-student-structure)
- [Exercise 2: Rectangle Structure](#exercise-2-rectangle-structure)

---

<br>

## Exercise 1: Student Structure

**Problem:** For a `student` structure whose members are the name, the Korean, English, and math scores, the average, and the rank, define `input_student()`, which reads a student's data and computes the average, `display_student_arr()`, which prints the whole array as a table, `swap_student()`, which exchanges two students, and `sort_student_arr()`, which sorts in descending order of the average and assigns ranks. The full problem and sample run are in [Exercise 1](Exercises.md#exercise-1-student-structure).

### Solution

**Approach:** Functions that change a structure receive a structure pointer, and functions that only read receive a `const` structure array ([Chapter 10, Section 2.3](Concepts_Lecture.md#23-passing-structs-to-functions)).

- **`input_student()`:** It accesses the members of the student pointed to by `p` with `->`. `p->name` is an array, so no `&` is added in `scanf("%s", p->name)`, while the integer members are passed by address, as in `&p->kor`. The average divides the sum of the three scores by `3.0` so that `double` division is used. Dividing by `3` would be integer division and would discard the fractional part.
- **`display_student_arr()`:** It prints three header lines and then one line per student in the formats `%-10s` (left-aligned name), `%3d` (scores), `%6.2f` (average), and `%2d` (rank). It only prints, so its parameter is `const struct student p[]`.
- **`swap_student()`:** It assigns `*p1` to a temporary variable `temp` of the same structure type and exchanges the two structures as a whole with `*p1 = *p2;` and `*p2 = temp;`. Structure assignment copies everything, including the array member `name` ([Chapter 10, Section 1.6](Concepts_Lecture.md#16-structure-assignment)).
- **`sort_student_arr()`:** Using selection sort, it finds the index of the student with the largest average from position `i` to the end (updating when `p[index_min].avg < p[j].avg`) and exchanges that student with the `i`-th one. The variable is named `index_min`, but it actually holds the index of the maximum. After sorting, it assigns `rank` values 1, 2, 3, ... from the front.
- **`main()`:** `input_student(&classA[i])` passes the address of each element. It is the same address as `classA + i` in the example code.

**Code:** [Lab_Q1.c](../../Coursework/Lab10_Structures/Lab_Q1.c)

```c
/**
 * @file    A10104-1_C10Q1.c
 * @brief   Q1. Student 구조체
 * @author  박철원 (Cheolwon Park)
 * @date    2024-06-13
 * 
 * @note    소스 코드에 사용된 scanf_s는 Visual Studio 이외의
 *          IDE에서 실행이 불가할 수 있음에 주의하시기 바랍니다.
 */

#pragma warning(disable:4996)
#pragma warning(disable:6031)
#include <stdio.h>
#include <string.h>
#define MAX_STD 20

struct student {
    char name[20];
    int kor, eng, math;
    double avg;
    int rank;
};

void input_student(struct student* p);
void display_student_arr(const struct student p[], int size);
void swap_student(struct student* p1, struct student* p2);
void sort_student_arr(struct student p[], int size);

int main() {
    struct student classA[MAX_STD];
    int size;

    printf("A반 학생 수를 입력하세요: ");
    scanf_s("%d", &size);

    for (int i = 0; i < size; i++) {
        input_student(&classA[i]);
    }

    sort_student_arr(classA, size);
    display_student_arr(classA, size);

    return 0;
}

void input_student(struct student* p) {
    printf("\n이름을 입력하세요: ");
    scanf("%s", p->name);

    printf("국어 점수: ");
    scanf("%d", &p->kor);

    printf("영어 점수: ");
    scanf("%d", &p->eng);

    printf("수학 점수: ");
    scanf("%d", &p->math);

    p->avg = (p->kor + p->eng + p->math) / 3.0;
}

void display_student_arr(const struct student p[], int size) {
    printf("--------------------------------------------------------\n");
    printf("   이름        국어   영어   수학     평균     등수\n");
    printf("--------------------------------------------------------\n");

    for (int i = 0; i < size; i++)
        printf(" %-10s   %3d   %3d   %3d   %6.2f   %2d\n",
               p[i].name, p[i].kor, p[i].eng, p[i].math, p[i].avg, p[i].rank);
}

void swap_student(struct student* p1, struct student* p2) {
    struct student temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

void sort_student_arr(struct student p[], int size) {
    int i, j, index_min;

    for (i = 0; i < size - 1; i++) {
        index_min = i;
        for (j = i + 1; j < size; j++) {
            if (p[index_min].avg < p[j].avg)
                index_min = j;
        }
        if (i != index_min) {
            swap_student(&p[i], &p[index_min]);
        }
    }
    for (i = 0; i < size; i++)
        p[i].rank = i + 1;
}
```

**Output:** `#pragma warning(disable:4996)` and `#pragma warning(disable:6031)` are MSVC-specific directives that turn off Visual Studio's warnings C4996 (use of security-risk functions such as `scanf`) and C6031 (ignored return value). Compiling with `gcc -std=c99 -Wall -Dscanf_s=scanf Lab_Q1.c` produces warnings that these two `#pragma` directives are unknown, but execution is not affected. Entering the same values as in the sample run gives the following result.

```text
A반 학생 수를 입력하세요: 5

이름을 입력하세요: 김ㅇㅇ
국어 점수: 53
영어 점수: 41
수학 점수: 37

이름을 입력하세요: 이ㅇㅇ
국어 점수: 97
영어 점수: 84
수학 점수: 87

이름을 입력하세요: 박ㅇㅇ
국어 점수: 64
영어 점수: 88
수학 점수: 71

이름을 입력하세요: 최ㅇㅇ
국어 점수: 37
영어 점수: 98
수학 점수: 100

이름을 입력하세요: 정ㅇㅇ
국어 점수: 67
영어 점수: 89
수학 점수: 76
--------------------------------------------------------
   이름        국어   영어   수학     평균     등수
--------------------------------------------------------
 이ㅇㅇ     97    84    87    89.33    1
 최ㅇㅇ     37    98   100    78.33    2
 정ㅇㅇ     67    89    76    77.33    3
 박ㅇㅇ     64    88    71    74.33    4
 김ㅇㅇ     53    41    37    43.67    5
```

The sort order, averages, and ranks match the sample run. For example, 이ㅇㅇ's average is (97 + 84 + 87) / 3 = 268 / 3 ≈ 89.33, and 김ㅇㅇ's average is 131 / 3 ≈ 43.67. The prompts (`A반 학생 수를 입력하세요:`, `이름을 입력하세요:`, `국어 점수:`, and so on), the length of the table's separator lines, and the column spacing differ from the sample run, and there is no blank line before the table after the last student is entered. Also, `%-10s` pads to a width in bytes, not in screen columns, and a Hangul character takes 3 bytes in UTF-8, so only one space is padded after `이ㅇㅇ` (9 bytes). On a Windows console that stores Hangul in 2 bytes (CP949), the same code places the columns differently.

> **Caution:** If `size` is greater than `MAX_STD` (20), the program writes past the `classA` array, so it is safer to check that the entered `size` is between 1 and `MAX_STD`. Also, `scanf("%s", p->name)` has no length limit, so a width such as `%19s` is needed to prevent an overflow from a name longer than 19 bytes (7 or more Hangul characters in UTF-8). Students with the same average do not share a rank but receive different ranks according to their sorted positions.

---

<br>

## Exercise 2: Rectangle Structure

**Problem:** For the rectangle structure `Rect` defined by its upper-left and lower-right points, write `isRectangle()`, which checks whether the two points form a rectangle, and `computeArea()`, which returns the area, and complete a program that reads the coordinates again until a rectangle is formed and then prints the area. The full problem and sample runs are in [Exercise 2](Exercises.md#exercise-2-rectangle-structure).

### Solution

**Approach:** For two points to form a rectangle, their x coordinates must differ and their y coordinates must also differ. If either the x or the y coordinates are equal, the points form a segment or a point with zero area. This code uses the mathematical coordinate system in which y increases upward, so the upper-left point has a smaller x and a larger y, and the lower-right point has a larger x and a smaller y.

- **`isRectangle()`:** It divides the relation of the two points into four cases. (1) If the upper-left and lower-right points are entered correctly, it returns 1. (2) If only the x coordinates are reversed, it swaps the x coordinates of the two points; (3) if only the y coordinates are reversed, it swaps the y coordinates; (4) if both are reversed, it swaps the two points as a whole; in each of these cases it prints a message and returns 1. In any other case, that is, if the x coordinates or the y coordinates are equal, it returns 0. Because it swaps coordinates and must change the caller's `rect`, it receives the parameter as the pointer `Rect* r`.
- **`computeArea()`:** It multiplies the width `rightDown.x - leftUp.x` by the height `leftUp.y - rightDown.y`. If the product is negative, it returns the product with its sign flipped. Since it is called after `isRectangle()` has normalized the coordinates, the product is in fact always positive.
- **`main()`:** Inside an infinite loop, it reads the two points; if `isRectangle(&rect)` returns 1, it prints the area and leaves with `break`, and if it returns 0, it prints an error message and reads again.

**Code:** [Lab_Q2.c](../../Coursework/Lab10_Structures/Lab_Q2.c)

```c
/**
 * @file    A10104-1_C10Q2.c
 * @brief   Q2. Rectangle 구조체
 * @author  박철원 (Cheolwon Park)
 * @date    2024-06-14
 * 
 * @note    소스 코드에 사용된 scanf_s는 Visual Studio 이외의
 *          IDE에서 실행이 불가할 수 있음에 주의하시기 바랍니다.
 */

#include <stdio.h>

typedef struct point {
    int x, y;
} Point;

typedef struct rectangle {
    Point leftUp;
    Point rightDown;
} Rect;

int isRectangle(Rect* r);
int computeArea(const Rect* p);

int main()
{
    Rect rect;

    printf("사각형의 좌표를 입력하세요.\n");
    while (1) {
        printf("좌상단 좌표: ");
        scanf_s(" %d %d", &rect.leftUp.x, &rect.leftUp.y);
        printf("우하단 좌표: ");
        scanf_s(" %d %d", &rect.rightDown.x, &rect.rightDown.y);

        if (isRectangle(&rect)) {
            int area = computeArea(&rect);
            printf("사각형의 면적 = %d\n\n", area);
            break;
        }
        else {
            printf("입력 오류! 입력한 좌표로는 사각형을 만들 수 없습니다.\n\n");
        }
    }

    return 0;
}

int isRectangle(Rect* r) {
    // 좌상단과 우하단 좌표가 올바르게 입력되었는지 확인
    if ((r->leftUp.x < r->rightDown.x) && (r->leftUp.y > r->rightDown.y))
        return 1;
    else if ((r->leftUp.x > r->rightDown.x) && (r->leftUp.y > r->rightDown.y)) {
        printf("x 좌표가 반대로 입력되어 서로 교환합니다.\n");
        int temp = r->leftUp.x;
        r->leftUp.x = r->rightDown.x;
        r->rightDown.x = temp;
        return 1;
    }
    else if ((r->leftUp.x < r->rightDown.x) && (r->leftUp.y < r->rightDown.y)) {
        printf("y 좌표가 반대로 입력되어 서로 교환합니다.\n");
        int temp = r->leftUp.y;
        r->leftUp.y = r->rightDown.y;
        r->rightDown.y = temp;
        return 1;
    }
    else if ((r->leftUp.x > r->rightDown.x) && (r->leftUp.y < r->rightDown.y)) {
        printf("반대로 입력된 좌상단 좌표와 우하단 좌표를 서로 교환합니다.\n");
        Point temp = r->leftUp;
        r->leftUp = r->rightDown;
        r->rightDown = temp;
        return 1;
    }
    else
        return 0;
}

int computeArea(const Rect* p) {
    int width = p->rightDown.x - p->leftUp.x;
    int height = p->leftUp.y - p->rightDown.y;

    if ((width * height) < 0)
        return -width * height;
    else
        return width * height;
}
```

**Output:** It compiles without warnings with `gcc -std=c99 -Wall -Dscanf_s=scanf Lab_Q2.c`. Entering the same values as in the two sample runs gives the following results.

```text
사각형의 좌표를 입력하세요.
좌상단 좌표: 1 3
우하단 좌표: 7 10
y 좌표가 반대로 입력되어 서로 교환합니다.
사각형의 면적 = 42
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
```

The second run matches the sample run. (-2, 5) and (7, 5) have the same y coordinate and (1, 10) and (1, -4) have the same x coordinate, so they are not rectangles, and (-2, 5) and (4, -1) give a width of 6 and a height of 6, so the area is 36. The first run gives the area (7 - 1) × (10 - 3) = 42, as in the sample run, but prints the extra line `y 좌표가 반대로 입력되어 서로 교환합니다.`. In the first sample run, the upper-left y (3) is smaller than the lower-right y (10), as in a screen coordinate system where y increases downward, while in the second sample run the upper-left y (5) is larger than the lower-right y (-1), so the two samples use different coordinate systems. This code is based on the mathematical coordinate system but normalizes the coordinates whichever way they are entered, so it computes the areas of both samples correctly.

> **Note:** **Differences from the requirements.** The requirements say not to change the prototype `int isRectangle(Rect r);`, but this code changes it to `int isRectangle(Rect* r);` so that it can swap coordinates and normalize the original, and it also prints messages inside the check function. To keep the prototype, `isRectangle()` should only return `r.leftUp.x != r.rightDown.x && r.leftUp.y != r.rightDown.y` for the `r` received by value, and `computeArea()` should multiply the absolute values of the width and height. Then the area is the same whichever coordinate system is used for input, and the first run gives the same result as the sample run without the message.

> **Caution:** If a non-numeric value is entered, `scanf` fails and leaves the character in the input buffer, so every iteration fails again on the same character and the program falls into an infinite loop. It is necessary to check that `scanf` returns 2 and, on failure, discard the remaining input up to the end of the line. Also, the product of the width and height is computed as `int`, so very large coordinates can cause an overflow.
