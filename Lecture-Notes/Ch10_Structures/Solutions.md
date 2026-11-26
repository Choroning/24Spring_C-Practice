# Chapter 10 Solutions — Structures

[Repository Guide](../../README.md) | [English](Solutions.md) | [한국어](Solutions.ko.md)

> **Last Updated:** 2026-11-27
>
> Warming-Up C Programming, 천정아, Ch 10

**Problem Source:** Exercises 1 and 2 are from Prof. Younghee Im, Computer Language Ⅰ (DCCS101-04)

---

<br>

## Table of Contents

- [Exercise 1: Student Structure](#exercise-1-student-structure)
- [Exercise 2: Rectangle Structure](#exercise-2-rectangle-structure)
- [Exercise 3: Correcting a Structure Definition](#exercise-3-correcting-a-structure-definition)
- [Exercise 4: Errors in Code That Uses Structure Variables](#exercise-4-errors-in-code-that-uses-structure-variables)
- [Exercise 5: Statements About Bit Fields, Unions, and Enumerations](#exercise-5-statements-about-bit-fields-unions-and-enumerations)
- [Exercise 6: A Login Information Structure](#exercise-6-a-login-information-structure)
- [Exercise 7: Checking Holidays](#exercise-7-checking-holidays)
- [Exercise 8: Printing Students at or Above the Average](#exercise-8-printing-students-at-or-above-the-average)

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

```c wide-ok
/**
 * @file    A10104-1_C10Q1.c
 * @brief   Q1. The Student Structure
 * @author  Cheolwon Park
 * @date    2024-06-13
 * 
 * @note    Note that scanf_s used in this source code may not run in IDEs
 *          other than Visual Studio.
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

**Output:** `#pragma warning(disable:4996)` and `#pragma warning(disable:6031)` are MSVC-specific directives that turn off Visual Studio's warnings C4996 (use of security-risk functions such as `scanf`) and C6031 (ignored return value). Compiling with `gcc -std=c99 -Wall -Dscanf_s=scanf Lab_Q1.c` produces warnings that these two `#pragma` directives are unknown, but execution is not affected. Entering the values of the sample run gives the following result.

```text wide-ok
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

이ㅇㅇ's average is (97 + 84 + 87) / 3 = 268 / 3 ≈ 89.33, and 김ㅇㅇ's average is 131 / 3 ≈ 43.67. The prompts (`A반 학생 수를 입력하세요:`, `이름을 입력하세요:`, `국어 점수:`, and so on), the length of the table's separator lines, and the column spacing differ from the sample run, and there is no blank line before the table after the last student is entered. Also, `%-10s` pads to a width in bytes, not in screen columns, and a Hangul character takes 3 bytes in UTF-8, so only one space is padded after `이ㅇㅇ` (9 bytes). On a Windows console that stores Hangul in 2 bytes (CP949), the same code places the columns differently.

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

```c wide-ok
/**
 * @file    A10104-1_C10Q2.c
 * @brief   Q2. The Rectangle Structure
 * @author  Cheolwon Park
 * @date    2024-06-14
 * 
 * @note    Note that scanf_s used in this source code may not run in IDEs
 *          other than Visual Studio.
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
    // Check that the upper-left and lower-right coordinates were entered correctly
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

**Output:** Entering the values of the two sample runs gives the following results.

```text wide-ok
사각형의 좌표를 입력하세요.
좌상단 좌표: 1 3
우하단 좌표: 7 10
y 좌표가 반대로 입력되어 서로 교환합니다.
사각형의 면적 = 42
```

```text wide-ok
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

(-2, 5) and (7, 5) have the same y coordinate and (1, 10) and (1, -4) have the same x coordinate, so they are not rectangles, and (-2, 5) and (4, -1) give a width of 6 and a height of 6, so the area is 36. The first run gives the area (7 - 1) × (10 - 3) = 42 and prints an extra line that the sample run does not have, `y 좌표가 반대로 입력되어 서로 교환합니다.`. In the first sample run, the upper-left y (3) is smaller than the lower-right y (10), as in a screen coordinate system where y increases downward, while in the second sample run the upper-left y (5) is larger than the lower-right y (-1), so the two samples use different coordinate systems. This code is based on the mathematical coordinate system but normalizes the coordinates whichever way they are entered, so it computes the areas of both samples correctly.

> **Note:** **Differences from the requirements.** The requirements say not to change the prototype `int isRectangle(Rect r);`, but this code changes it to `int isRectangle(Rect* r);` so that it can swap coordinates and normalize the original, and it also prints messages inside the check function. To keep the prototype, `isRectangle()` should only return `r.leftUp.x != r.rightDown.x && r.leftUp.y != r.rightDown.y` for the `r` received by value, and `computeArea()` should multiply the absolute values of the width and height. Then the area is the same whichever coordinate system is used for input, and the first run gives the same result as the sample run without the message.

> **Caution:** If a non-numeric value is entered, `scanf` fails and leaves the character in the input buffer, so every iteration fails again on the same character and the program falls into an infinite loop. It is necessary to check that `scanf` returns 2 and, on failure, discard the remaining input up to the end of the line. Also, the product of the width and height is computed as `int`, so very large coordinates can cause an overflow.

---

<br>

## Exercise 3: Correcting a Structure Definition

**Textbook Problem:** Chapter 10 exercise 2

**Problem:** Correct the parts of the `employee` structure definition, which contains a member `gender` for storing one character, that cause compile errors. The code is in [Exercise 3](Exercises.md#exercise-3-correcting-a-structure-definition).

### Solution

**Answer:** Two places are corrected. The member `gender` has no data type, so it is written as `char gender;`, and since a structure definition is a declaration, a semicolon is attached after the closing brace, ending it with `};`.

```c
struct employee {
    char name[20];
    char gender;            // a member needs a data type
    int salary;
    char department[20];
};                          // a structure definition ends with a semicolon
```

**Explanation:** Compiling the original code with Clang gives two errors. The first points to the member written as a name without a type, and the second to the missing semicolon after the structure definition ([Chapter 10, Section 1.2](Concepts_Lecture.md#12-structure-definition)).

```text
error: type name requires a specifier or qualifier
error: expected ';' after struct
```

When the semicolon is missing, the compiler tries to read up to the `int main(void)` on the following line as part of this structure definition, so the error is sometimes reported at the next declaration rather than at the end of the definition.

---

<br>

## Exercise 4: Errors in Code That Uses Structure Variables

**Textbook Problem:** Chapter 10 exercise 5

**Problem:** Select every statement among six statements using the `contact` structure variables `c1` and `c2` that causes a compile error. The code is in [Exercise 4](Exercises.md#exercise-4-errors-in-code-that-uses-structure-variables).

### Solution

**Answer:** ②, ④, ⑤

**Explanation:** Clang reports the following errors for the three statements in order.

```text
error: array type 'char[20]' is not assignable
error: expected expression
error: invalid operands to binary expression ('struct contact' and 'struct contact')
```

- ② `name` is a `char` array, so a string cannot be assigned to it with `=`. Copy it with `strcpy(c2.name, "Lee");` ([Chapter 10, Section 1.6](Concepts_Lecture.md#16-structure-assignment)).
- ④ A brace-enclosed initializer list can be used only in a declaration, so it cannot be assigned to `c2`, which is already declared. Assign the members one at a time, or assign another structure variable holding the same values.
- ⑤ `==` cannot be used on structures, so they are compared member by member ([Chapter 10, Section 1.7](Concepts_Lecture.md#17-structure-comparison)).
- ① is a whole-structure assignment that copies everything, including the array members, so it is correct, and ③ is an assignment to an `int` member, so it is correct. ⑥ is the correct way to compare string members with `strcmp`.

---

<br>

## Exercise 5: Statements About Bit Fields, Unions, and Enumerations

**Textbook Problem:** Chapter 10 exercises 6 and 8

**Problem:** Select every wrong statement among eight statements about bit fields, unions, and enumerations. The choices are in [Exercise 5](Exercises.md#exercise-5-statements-about-bit-fields-unions-and-enumerations).

### Solution

**Answer:** ③, ④, ⑦

**Explanation:** ③ The members of a union share the same memory, so the size of a union is usually the size of its largest member, possibly a little larger because of alignment, and never the sum of the member sizes ([Chapter 10, Section 3.2](Concepts_Lecture.md#32-union)). ④ A bit field is a feature that reduces memory by packing several small-range members into one integer. The date bit field of Chapter 10, Section 2.6 took 4 bytes, less than the 12 bytes of the same members as three `unsigned int` values. ⑦ An enumeration constant is an integer constant, so it cannot be given a floating-point value ([Chapter 10, Section 3.1](Concepts_Lecture.md#31-enum)). The rest are correct. For example, in `enum color { RED, GREEN = 5, BLUE };`, `RED`, which has no specified value, is 0, and `BLUE` is 6, one more than the preceding `GREEN`.

---

<br>

## Exercise 6: A Login Information Structure

**Textbook Problem:** Chapter 10 programming assignments 1 and 2

**Problem:** Define a `login_info` structure that stores an ID and a password, and write `normalize`, which converts both members to lowercase, and `print_login`, which prints the password masked with `*`. The sample run is in [Exercise 6](Exercises.md#exercise-6-a-login-information-structure).

### Solution

**Approach:** Both members are declared as `char[21]`, adding room for the null character to the maximum of 20 characters. `normalize`, which changes the structure, takes a structure pointer, and `print_login`, which only reads it, takes a `const` structure pointer. The lowercase conversion is made a separate function that processes one string and is reused for both members.

```c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct login_info {
    char id[21];
    char password[21];
};

void to_lower_str(char *s)
{
    for (; *s != '\0'; s++)
        *s = (char)tolower((unsigned char)*s);
}

void normalize(struct login_info *info)
{
    to_lower_str(info->id);
    to_lower_str(info->password);
}

void print_login(const struct login_info *info)
{
    size_t i, n = strlen(info->password);

    printf("ID: %s\nPW: ", info->id);
    for (i = 0; i < n; i++)
        putchar('*');
    putchar('\n');
}

int main(void)
{
    struct login_info user;

    printf("ID? ");
    scanf("%20s", user.id);
    printf("Password? ");
    scanf("%20s", user.password);
    normalize(&user);
    print_login(&user);
    printf("stored: %s / %s\n", user.id, user.password);
    return 0;
}
```

- The width 20 in `scanf("%20s", user.id)` reads at most 20 characters so that the 21-byte array is not exceeded. The array name is the starting address, so `&` is not attached.
- `info->id` is the same as `(*info).id`, and `to_lower_str` changes the characters of that array directly, so `user` in `main` changes.
- `print_login` obtains the length of the password with `strlen` and prints that many `*`, without printing the password itself. `putchar` is a function that prints one character.

**Output:**

```text
ID? Anonymous
Password? IDontKnow
ID: anonymous
PW: *********
stored: anonymous / idontknow
```

`IDontKnow` has 9 characters, so 9 `*` are printed.

---

<br>

## Exercise 7: Checking Holidays

**Textbook Problem:** Chapter 10 programming assignment 4

**Problem:** Define a `date` structure and `same_date`, which compares two dates, and find an entered date in an array of holidays and print the result. The sample run is in [Exercise 7](Exercises.md#exercise-7-checking-holidays).

### Solution

**Approach:** Structures cannot be compared with `==`, so `same_date` compares all three members. The entered date is found by sequential search, comparing it with each element of the holiday array in turn.

```c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

struct date {
    int year, month, day;
};

int same_date(struct date a, struct date b)
{
    return a.year == b.year && a.month == b.month && a.day == b.day;
}

int main(void)
{
    struct date holidays[] = {
        { 2024, 1, 1 }, { 2024, 3, 1 }, { 2024, 5, 5 }, { 2024, 6, 6 },
        { 2024, 8, 15 }, { 2024, 10, 3 }, { 2024, 10, 9 }, { 2024, 12, 25 }
    };
    int n = sizeof(holidays) / sizeof(holidays[0]);
    struct date d;
    int i, found;

    while (1) {
        printf("date? ");
        if (scanf("%d %d %d", &d.year, &d.month, &d.day) != 3)
            break;
        if (d.year == 0 && d.month == 0 && d.day == 0)
            break;
        found = 0;
        for (i = 0; i < n; i++) {
            if (same_date(d, holidays[i])) {
                found = 1;
                break;
            }
        }
        printf("%d/%d/%d is %sa holiday\n", d.year, d.month, d.day, found ? "" : "not ");
    }
    return 0;
}
```

- `same_date` returns the value 1 or 0 of the relational expressions and `&&` directly. It is a small structure, so receiving it by value costs little to copy.
- The array size is omitted and set by the initial values, and the element count 8 is obtained with `sizeof(holidays) / sizeof(holidays[0])`, so `n` need not be edited when holidays are added.
- If `scanf` fails to read three values, the loop ends, so non-numeric input does not cause an infinite loop (Chapter 5, Section 3.8).
- `found ? "" : "not "` chooses the string to print with the conditional operator, so `not ` appears only when the date was not found.

**Output:**

```text
date? 2024 8 15
2024/8/15 is a holiday
date? 2024 5 2
2024/5/2 is not a holiday
date? 0 0 0
```

---

<br>

## Exercise 8: Printing Students at or Above the Average

**Problem:** Compute the average of a structure array holding the names and scores of five students, and print the students at or above the average. The data and sample run are in [Exercise 8](Exercises.md#exercise-8-printing-students-at-or-above-the-average).

### Solution

**Approach:** Comparison requires knowing the average, so the array is scanned twice. The first loop computes the sum to calculate the average, and the second compares each student's score with the average.

```c
#include <stdio.h>

struct student {
    char name[20];
    int score;
};

int main(void)
{
    struct student s[5] = {
        { "Kim", 82 }, { "Lee", 67 }, { "Park", 91 }, { "Choi", 74 }, { "Jung", 88 }
    };
    int i, n = 5, sum = 0;
    double avg;

    for (i = 0; i < n; i++)
        sum += s[i].score;
    avg = (double)sum / n;
    printf("average = %.1f\n", avg);
    for (i = 0; i < n; i++)
        if (s[i].score >= avg)
            printf("%s %d\n", s[i].name, s[i].score);
    return 0;
}
```

The sum is 82 + 67 + 91 + 74 + 88 = 402, and the average is 402 / 5 = 80.4. In `s[i].score >= avg`, the `int` score is converted to `double` for the comparison, so with an average of 80.4, the scores 82, 91, and 88 satisfy the condition. Computing the average as an `int` would give 80 and change the comparison threshold, so it is cast with `(double)`. `s[i].name` selects the element with `[]` and then the member with `.`.

**Output:**

```text
average = 80.4
Kim 82
Park 91
Jung 88
```
