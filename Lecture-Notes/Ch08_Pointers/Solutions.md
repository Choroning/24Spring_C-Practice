# Chapter 8 Solutions — Pointers

[Repository Guide](../../README.md) | [English](Solutions.md) | [한국어](Solutions.ko.md)

> **Last Updated:** 2026-11-19
>
> Warming-Up C Programming, 천정아, Ch 8

**Problem Source:** Exercises 1 and 2 are from Prof. Younghee Im, Computer Language Ⅰ (DCCS101-04)

---

<br>

## Table of Contents

- [Exercise 1: 2D Plane Coordinate Calculator](#exercise-1-2d-plane-coordinate-calculator)
- [Exercise 2: Lotto Program](#exercise-2-lotto-program)
- [Exercise 3: Declaring and Initializing Pointers](#exercise-3-declaring-and-initializing-pointers)
- [Exercise 4: Results of Pointer Arithmetic](#exercise-4-results-of-pointer-arithmetic)
- [Exercise 5: `const` Pointers and Compile Errors](#exercise-5-const-pointers-and-compile-errors)
- [Exercise 6: Output of Increment and Dereference](#exercise-6-output-of-increment-and-dereference)
- [Exercise 7: A Function That Computes a Sum and an Average](#exercise-7-a-function-that-computes-a-sum-and-an-average)
- [Exercise 8: Minimum, Maximum, and Reversing an Array with Pointers](#exercise-8-minimum-maximum-and-reversing-an-array-with-pointers)

---

<br>

## Exercise 1: 2D Plane Coordinate Calculator

**Problem:** Complete the program by defining `display_point()`, which prints a coordinate, `compute_distance()`, which computes and returns the distance between two points, and `move_point()`, which changes two coordinate values by a displacement. The full problem and sample runs are in [Exercise 1](Exercises.md#exercise-1-2d-plane-coordinate-calculator).

### Solution

**Approach:** The passing method is chosen by whether the function only reads the argument values or must change the caller's variables ([Chapter 8, Section 3.3](Concepts_Lecture.md#33-returning-multiple-values)).

- **`display_point()`:** The x and y values are input parameters that are only read, so they are received by value and printed in the form `(x, y)`, followed by a newline.
- **`compute_distance()`:** It receives the four coordinates by value and computes $\sqrt{(x_2 - x_1)^2 + (y_2 - y_1)^2}$ with `sqrt()`. The squares are computed with `int` multiplication and converted to `double` when passed to `sqrt()`. This code declares the function as `void` and prints the computed distance inside the function with `%.5f`.
- **`move_point()`:** It must change `x2` and `y2` of `main()`, so it receives the two coordinates by address (`int *x, int *y`). Inside the function, `*x += move;` and `*y += move;` modify the originals, and the caller passes the addresses, as in `move_point(&x2, &y2, move);` ([Chapter 8, Section 3.2](Concepts_Lecture.md#32-modifying-a-variable-through-a-pointer)).

**Code:** [Lab_Q1.c](../../Coursework/Lab08_Pointers/Lab_Q1.c)

```c
/**
 * @file    A10104-1_C08Q1.c
 * @brief   Q1. 2차원 평면 좌표 계산기
 * @author  박철원 (Cheolwon Park)
 * @date    2024-05-14
 * 
 * @note    소스 코드에 사용된 scanf_s는 Visual Studio 이외의
 *          IDE에서 실행이 불가할 수 있음에 주의하시기 바랍니다.
 */

#include <stdio.h>
#include <math.h>

void display_point(int x, int y);
void compute_distance(int x1, int y1, int x2, int y2);
void move_point(int *x, int *y, int move);

int main()
{
    int x1, x2, y1, y2, move;
    double distance;

    printf("p1 좌표 입력(x1, y1 좌표값 입력): ");
    scanf_s(" %d %d", &x1, &y1);
    
    printf("p2 좌표 입력(x2, y2 좌표값 입력): ");
    scanf_s(" %d %d", &x2, &y2);

    printf("p1 = ");
    display_point(x1, y1);

    printf("p2 = ");
    display_point(x2, y2);

    compute_distance(x1, y1, x2, y2);

    printf("좌표 이동량 입력: ");
    scanf_s(" %d", &move);

    move_point(&x2, &y2, move);

    printf("p2를 x축과 y축으로 각각 %d만큼 이동 = ", move);
    display_point(x2, y2);

    return 0;
}

void display_point(int x, int y)
{
    printf("(%d, %d)\n", x, y);
}

void compute_distance(int x1, int y1, int x2, int y2)
{
    double distance;
    distance = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    printf("두 점 사이의 거리 = %.5f\n\n", distance);
}

void move_point(int *x, int *y, int move)
{
    *x += move;
    *y += move;
}
```

**Output:** `scanf_s` is a function provided by Visual Studio (MSVC); it belongs to Annex K, which is optional in the C11 standard, and is not declared in the standard libraries used by gcc and clang. The `scanf_s` calls in this code read only integers (`%d`), so they behave like `scanf`, and with gcc or clang the code is compiled by defining a macro, as in `gcc -std=c99 -Wall -Dscanf_s=scanf Lab_Q1.c -lm`. This produces one warning that the local variable `distance` in `main()` is unused. Entering the values of the sample runs gives the following results, with the entered values shown as they appear in a terminal.

```text
p1 좌표 입력(x1, y1 좌표값 입력): 1 1
p2 좌표 입력(x2, y2 좌표값 입력): 3 7
p1 = (1, 1)
p2 = (3, 7)
두 점 사이의 거리 = 6.32456

좌표 이동량 입력: -1
p2를 x축과 y축으로 각각 -1만큼 이동 = (2, 6)
```

```text
p1 좌표 입력(x1, y1 좌표값 입력): -2 4
p2 좌표 입력(x2, y2 좌표값 입력): 3 -5
p1 = (-2, 4)
p2 = (3, -5)
두 점 사이의 거리 = 10.29563

좌표 이동량 입력: 3
p2를 x축과 y축으로 각각 3만큼 이동 = (6, -2)
```

The first distance is $\sqrt{2^2 + 6^2} = \sqrt{40} \approx 6.324555$, and the second is $\sqrt{5^2 + 9^2} = \sqrt{106} \approx 10.295630$. The output format differs in three ways. First, the input prompts read `(x1, y1 좌표값 입력)` and `(x2, y2 좌표값 입력)` instead of `(x축, y축 좌표값 입력)`. Second, `만큼` follows the displacement without a space. Third, the distance is printed with five decimal places (`%.5f`), so the second distance appears as `10.29563` instead of `10.2956`. The distances in the sample runs are printed with six significant digits (the default form of `%g`). The last line of the sample runs, `Program ended with exit code: 0`, is not program output but the exit message added by the Xcode console.

> **Note:** The requirements state that `compute_distance()` returns the distance and contains no output statement, but this code returns nothing and prints inside the function. To follow the requirements, declare it as `double compute_distance(int x1, int y1, int x2, int y2)`, return the distance with `return sqrt(...);`, receive it in `main()` with `distance = compute_distance(x1, y1, x2, y2);`, and print it with `printf`. The `distance` variable declared in the example code is then used as well, and the warning disappears.

> **Caution:** `(x2 - x1) * (x2 - x1)` is computed as `int`, so if the absolute coordinate difference is 46341 or more, the product exceeds the maximum `int` value ($2^{31} - 1$) and overflows. To handle large coordinates, convert to `double` first, as in `(double)(x2 - x1)`, before multiplying. Also, `sqrt()` is a math library function declared in `<math.h>`, so gcc on Linux needs the `-lm` option to link the math library.

---

<br>

## Exercise 2: Lotto Program

**Problem:** Complete a lotto program that randomly draws 6 distinct numbers from 1-45 and prints them in ascending order. Implement the array printing function `printArray()` with pointer increments, the duplicate check function `existDuplication()` with pointer indexing, and the selection sort function `selectionSort()` with pointer arithmetic and calls to `swap()`. The full problem and sample runs are in [Exercise 2](Exercises.md#exercise-2-lotto-program).

### Solution

**Approach:** The three functions handle the same array with different pointer notations ([Chapter 8, Section 2](Concepts_Lecture.md#2-arrays-and-pointers)).

- **`printArray()`:** The parameter `const int p[]` is actually the pointer variable `const int *p`, so it can be incremented. `*p++` reads the current element and then moves `p` to the next element. Each number is printed with `%2d` and two spaces to align the columns.
- **`existDuplication()`:** It compares every index pair `(i, j)` with `i < j` using `p[i] == p[j]` and returns 1 as soon as it finds an equal value. If no equal value is found by the end, it returns 0. With 6 elements, there are at most $6 \times 5 / 2 = 15$ comparisons.
- **`swap()`:** It receives the addresses of two integers and exchanges their values with a temporary variable ([Chapter 8, Section 3.2](Concepts_Lecture.md#32-modifying-a-variable-through-a-pointer)).
- **`selectionSort()`:** It finds the index `index_min` of the smallest element from position `i` to the end by comparing `*(p + index_min) > *(p + j)`. If `index_min` differs from `i`, `swap(p + i, p + index_min)` exchanges the two elements. Repeating this for `i = 0` through `size - 2` sorts the array in ascending order.
- **`main()`:** The `do-while` statement draws 6 numbers and draws again while `existDuplication(lotto, 6)` returns 1, that is, while there is a duplicate. Once it gets a set without duplicates, it sorts and prints the set.

**Code:** [Lab_Q2.c](../../Coursework/Lab08_Pointers/Lab_Q2.c)

```c
/**
 * @file    A10104-1_C08Q2.c
 * @brief   Q2. 로또 프로그램
 * @author  박철원 (Cheolwon Park)
 * @date    2024-05-14
 * 
 * @note    소스 코드에 사용된 scanf_s는 Visual Studio 이외의
 *          IDE에서 실행이 불가할 수 있음에 주의하시기 바랍니다.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printArray(const int p[], int size);
int existDuplication(const int p[], int size);
void swap(int* p, int* q);
void selectionSort(int p[], int size);

int main()
{
    int lotto[6], setNo;

    srand((unsigned int)time(NULL));
    printf("몇 세트의 로또 번호를 생성할까요? ");
    scanf_s(" %d", &setNo);

    for (int k = 0; k < setNo; k++) {
        do {
            for (int i = 0; i < 6; i++) {
                lotto[i] = rand() % 45 + 1;
            }
        } while (existDuplication(lotto, 6));
        selectionSort(lotto, 6);
        printArray(lotto, 6);
    }
    printf("\n행운을 빕니다!\n");
    return 0;
}

void printArray(const int p[], int size)
{
    for (int i = 0; i < size; i++) {
        printf("%2d  ", *p++);
    }
    printf("\n");
}

int existDuplication(const int p[], int size)
{
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (p[i] == p[j])
                return 1;
        }
    }
    return 0;
}

void swap(int* p, int* q)
{
    int temp;
    temp = *p;
    *p = *q;
    *q = temp;
}

void selectionSort(int p[], int size)
{
    int index_min, i, j;

    for (i = 0; i < size - 1; i++) {
        index_min = i;
        for (j = i + 1; j < size; j++) {
            if (*(p + index_min) > *(p + j)) {
                index_min = j;
            }
        }
        if (index_min != i) {
            swap((p + i), (p + index_min));
        }
    }
}
```

**Output:** As in Exercise 1, compile with `gcc -std=c99 -Wall` and `-Dscanf_s=scanf`. The numbers differ on every run according to the seed set by `srand(time(NULL))`. One example run that generates 5 sets is shown below.

```text
몇 세트의 로또 번호를 생성할까요? 5
 4  21  28  31  35  45  
 9  15  17  24  25  45  
 4  12  23  39  40  42  
 5   7  12  15  31  45  
 9  13  18  22  36  39  

행운을 빕니다!
```

Each set has no duplicates and is sorted in ascending order. The prompt says `로또 번호` instead of the sample run's `복권 번호`, and because two spaces are printed after each number, each line ends with trailing spaces.

> **Note:** When 6 numbers are drawn independently, the probability that none is duplicated is $\frac{45 \times 44 \times 43 \times 42 \times 41 \times 40}{45^6} \approx 0.706$. So about 29% of the attempts are redrawn because of duplicates on average, and getting one set takes about 1.42 draws on average. Also, `rand() % 45` has a bias toward slightly more frequent small numbers when `RAND_MAX + 1` is not a multiple of 45, but the bias is negligible for the purpose of this program.

---

<br>

## Exercise 3: Declaring and Initializing Pointers

**Textbook Problem:** Chapter 8 exercise 3

**Problem:** Select the wrong ones among seven pointer declarations and initializations and explain why. The choices are in [Exercise 3](Exercises.md#exercise-3-declaring-and-initializing-pointers).

### Solution

**Answer:** ③, ⑥, ⑦

**Explanation:** A pointer is given only the address of a variable of the same type or a null pointer ([Chapter 8, Section 1.7](Concepts_Lecture.md#17-precautions-when-using-pointers)). ① and ② initialize null pointers, and since the integer constant 0 becomes a null pointer, both are correct. ④ is the address of an `int` variable and ⑤ is the array name, the address of its first element, so both are correct. For the three wrong declarations, Clang reports the following.

```text
error: incompatible integer to pointer conversion initializing 'int *' with an expression of type 'int' [-Wint-conversion]
error: initializing 'double *' with an expression of incompatible type 'double'; take the address with &
warning: incompatible pointer types initializing 'short *' with an expression of type 'int *' [-Wincompatible-pointer-types]
```

③ tries to store a nonzero integer as an absolute address, and ⑥ tries to store the `double` value itself without `&`. ⑦ points to an `int` variable with a `short*`, so dereferencing it would interpret only 2 bytes of the 4-byte variable as a `short`.

---

<br>

## Exercise 4: Results of Pointer Arithmetic

**Textbook Problem:** Chapter 8 exercise 5

**Problem:** Compute the values of six expressions formed with a pointer to the `int` array `{2, 4, 6, 8}` at address `0x100`. The expressions are in [Exercise 4](Exercises.md#exercise-4-results-of-pointer-arithmetic).

### Solution

**Answer:** ① 2, ② `0x108`, ③ 6, ④ 8, ⑤ 3, ⑥ 4

**Explanation:** `ptr + n` is the address n elements away, that is, `n * sizeof(int)` bytes away, not n bytes ([Chapter 8, Section 2.1](Concepts_Lecture.md#21-pointer-arithmetic)). Therefore ② `ptr + 2` is 0x100 + 2 × 4 = 0x108, and ③ `*(ptr + 2)` is the element at that address, `arr[2]` = 6. ④ `ptr[3]` is the same as `*(ptr + 3)`, so it is `arr[3]` = 8. ⑤ obtains `*ptr` first because of the parentheses and adds 1 to that 2, giving 3, and the array does not change. ⑥ is `arr[1]` = 4.

---

<br>

## Exercise 5: `const` Pointers and Compile Errors

**Textbook Problem:** Chapter 8 exercise 6

**Problem:** Select every statement among six statements about `const int *ptr = x;` that causes a compile error. The choices are in [Exercise 5](Exercises.md#exercise-5-const-pointers-and-compile-errors).

### Solution

**Answer:** ①, ⑤, ⑥

**Explanation:** `const int *ptr` is a pointer that can only read the `int` it points to, while the pointer itself can be changed ([Chapter 8, Section 1.6](Concepts_Lecture.md#16-const-pointer)). Therefore ① `*ptr = 0`, ⑤ `(*ptr)++`, and ⑥ `ptr[1] = 3`, which change the pointed-to value, are all the error `read-only variable is not assignable` in Clang. ② makes `ptr` a null pointer, ③ makes it point to another array `y`, and ④ makes it point to the next element; these change the pointer itself and are allowed. To fix the pointer itself, write `const` after `*`, as in `int *const ptr = x;`.

---

<br>

## Exercise 6: Output of Increment and Dereference

**Textbook Problem:** Chapter 8 exercise 12

**Problem:** Write the output of a loop that prints `++(*p)` through a pointer to an array and moves with `p++`, followed by a loop that prints the array. The code is in [Exercise 6](Exercises.md#exercise-6-output-of-increment-and-dereference).

### Solution

**Approach:** `++(*p)` first obtains `*p` inside the parentheses, the element `p` points to, then increments that element by 1 and yields the incremented value. The `p++` on the next line moves the pointer to the next element.

| Iteration | Element `p` Points To | Result of `++(*p)` | Array After the Iteration |
|:-----|:-----|-----:|:-----|
| 0 | `arr[0]` | 2 | `{2, 2, 3, 4, 5}` |
| 1 | `arr[1]` | 3 | `{2, 3, 3, 4, 5}` |
| 2 | `arr[2]` | 4 | `{2, 3, 4, 4, 5}` |
| 3 | `arr[3]` | 5 | `{2, 3, 4, 5, 5}` |
| 4 | `arr[4]` | 6 | `{2, 3, 4, 5, 6}` |

**Output:**

```text
2 3 4 5 6
2 3 4 5 6
```

Each element was incremented once, so the array in the second line is the same as the first line. Writing it in one expression, as in `++*p++`, binds the postfix `++` first, giving `++(*(p++))`; it produces the same result but is hard to read.

---

<br>

## Exercise 7: A Function That Computes a Sum and an Average

**Textbook Problem:** A variation of Chapter 8 exercise 13

**Problem:** Write `get_sum_average`, which gives back the sum as the return value and the average through an output parameter, and make it skip storing the average when `NULL` is passed. The sample run is in [Exercise 7](Exercises.md#exercise-7-a-function-that-computes-a-sum-and-an-average).

### Solution

**Approach:** There are two results, so one is the return value, and the other is written to `*average` through the address of the caller's variable ([Chapter 8, Section 3.3](Concepts_Lecture.md#33-returning-multiple-values)). For calls that do not need the output parameter, it is checked against `NULL` before dereferencing.

```c
#include <stdio.h>

int get_sum_average(const int arr[], int size, double *average)
{
    int sum, i;

    for (i = 0, sum = 0; i < size; i++)
        sum += arr[i];
    if (average != NULL)
        *average = (double)sum / size;
    return sum;
}

int main(void)
{
    int scores[5] = { 98, 99, 78, 85, 91 };
    double ave;

    printf("sum: %d\n", get_sum_average(scores, 5, &ave));
    printf("average: %.2f\n", ave);
    printf("sum only: %d\n", get_sum_average(scores, 3, NULL));
    return 0;
}
```

- `(double)sum / size` converts `sum` to a real number before dividing, so it is not integer division. 451 / 5 = 90.2.
- `ave` holds a value only after the first `printf` call finishes, so the average is printed separately in the next statement. Writing `get_sum_average(scores, 5, &ave)` and `ave` together among the arguments of one `printf` could read the value before it is stored, because the evaluation order of arguments is not specified.
- The third call passes `NULL`, so it does not store an average and returns only the sum of the first 3, 98 + 99 + 78 = 275.

**Output:**

```text
sum: 451
average: 90.20
sum only: 275
```

---

<br>

## Exercise 8: Minimum, Maximum, and Reversing an Array with Pointers

**Problem:** Write `get_min_max`, which gives back the minimum and maximum through output parameters, and `reverse`, which reverses an array with two pointers at its two ends. The sample run is in [Exercise 8](Exercises.md#exercise-8-minimum-maximum-and-reversing-an-array-with-pointers).

### Solution

**Approach:** `get_min_max` gives back both results through output parameters. `reverse` keeps `left`, pointing to the first element, and `right`, pointing to the last, and while `left` is before `right`, it swaps the two elements and moves the pointers toward each other.

```c
#include <stdio.h>

void get_min_max(const int *arr, int size, int *min, int *max)
{
    int i;

    *min = *max = arr[0];
    for (i = 1; i < size; i++) {
        if (arr[i] < *min)
            *min = arr[i];
        if (arr[i] > *max)
            *max = arr[i];
    }
}

void reverse(int *arr, int size)
{
    int *left = arr, *right = arr + size - 1, t;

    while (left < right) {
        t = *left;
        *left = *right;
        *right = t;
        left++;
        right--;
    }
}

int main(void)
{
    int data[6] = { 23, 45, 62, 12, 99, 83 };
    int lo, hi, i;

    get_min_max(data, 6, &lo, &hi);
    printf("min = %d, max = %d\n", lo, hi);
    reverse(data, 6);
    for (i = 0; i < 6; i++)
        printf("%d ", data[i]);
    printf("\n");
    return 0;
}
```

- `*min = *max = arr[0];` starts both results at the first element with a chained assignment. Starting from 0 or an arbitrary value, as cautioned in Chapter 7, Section 5.1, gives a wrong result when every element is larger or smaller than that value.
- `arr + size - 1` is the address of the last element `arr[5]`. Two pointers into the same array can be compared with `<`, so when `left < right` becomes false, the middle has been reached.
- With 6 elements, the three pairs (`arr[0]`, `arr[5]`), (`arr[1]`, `arr[4]`), and (`arr[2]`, `arr[3]`) are swapped, after which `left` is `arr + 3` and `right` is `arr + 2`, and the loop stops. With an odd number of elements, the two pointers meet at the middle element, which stays in place.

**Output:**

```text
min = 12, max = 99
83 99 12 62 45 23
```
