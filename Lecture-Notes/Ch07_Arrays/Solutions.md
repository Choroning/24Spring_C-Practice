# Chapter 7 Solutions — Arrays

[Repository Guide](../../README.md) | [English](Solutions.md) | [한국어](Solutions.ko.md)

> **Last Updated:** 2026-11-19
>
> Warming-Up C Programming, 천정아, Ch 7

**Problem Source:** Exercises 1-3 are from Prof. Younghee Im, Computer Language Ⅰ (DCCS101-04)

---

<br>

## Table of Contents

- [Exercise 1: Computing the Check Digit of a UPC Barcode](#exercise-1-computing-the-check-digit-of-a-upc-barcode)
- [Exercise 2: Selection Sort Variant](#exercise-2-selection-sort-variant)
- [Exercise 3: Computing Frequency and Relative Frequency](#exercise-3-computing-frequency-and-relative-frequency)
- [Exercise 4: Judging Array Declarations](#exercise-4-judging-array-declarations)
- [Exercise 5: Output of Accumulating a 2D Array](#exercise-5-output-of-accumulating-a-2d-array)
- [Exercise 6: Statements About Array Parameters](#exercise-6-statements-about-array-parameters)
- [Exercise 7: Functions That Fill and Sum a Real Array](#exercise-7-functions-that-fill-and-sum-a-real-array)
- [Exercise 8: Seat Reservation](#exercise-8-seat-reservation)
- [Exercise 9: Rotating an Array to the Left](#exercise-9-rotating-an-array-to-the-left)

---

<br>

## Exercise 1: Computing the Check Digit of a UPC Barcode

**Problem:** Rewrite the example code, which computes the check digit of a UPC barcode with 12 variables, to use an array whose size is fixed by a macro constant. The full problem and sample run are in [Exercise 1](Exercises.md#exercise-1-computing-the-check-digit-of-a-upc-barcode).

### Solution

**Approach:** When the variables `dig1`-`dig11` become the array elements `dig[0]`-`dig[10]`, the odd positions counted from 1 are indices 0, 2, ..., 10 and the even positions are indices 1, 3, ..., 9. The two sums can therefore be computed with two loops that increase the index by 2 ([Chapter 7, Section 5.4](Concepts_Lecture.md#54-upc-barcode-check-digit)).

- **Input:** It repeats `SIZE - 1`, that is 11, times, reading one digit at a time with `"%1d"` and storing it from `dig[0]` on. Because `%1d` reads at most one digit as an integer, not only the space-separated `0 3 6 0 0 0 2 9 1 4 5` of the sample run but also the unseparated `03600029145` gives the same result. Like `%d`, it skips leading whitespace.
- **Computing the check digit:** It adds the digits at odd positions to `sum` while increasing the index by 2 from 0, multiplies by 3 with `sum *= 3`, and then adds the digits at even positions while increasing the index by 2 from 1. Finally it stores `(10 - sum % 10) % 10` in the last element `dig[SIZE - 1]`. The outer `% 10` makes the check digit 0 rather than 10 when `sum` is a multiple of 10.
- **Printing the input:** It prints the 11 input digits with a loop.

**Code:** [Lab_Q1.c](../../Coursework/Lab07_Arrays/Lab_Q1.c)

```c
/**
 * @file    A10104-1_C07Q1.c
 * @brief   Q1. UPC 바코드의 Check Digit 계산
 * @author  박철원 (Cheolwon Park)
 * @date    2024-05-11
 * 
 * @note    소스 코드에 사용된 scanf_s는 Visual Studio 이외의
 *	    IDE에서 실행이 불가할 수 있음에 주의하시기 바랍니다.
 */

#include <stdio.h>
#define SIZE 12

int main()
{
	int dig[SIZE], sum = 0, i;

	printf("Please enter the first eleven UPC digits, separated by white space: \n");

	for (i = 0; i < SIZE - 1; i++) {
		scanf_s("%1d", &dig[i]);
	}
	for (i = 0; i < SIZE - 1; i++) {
		printf("입력된 숫자: %d", dig[i]);
	}
	
	for (i = 0; i < SIZE - 1; i += 2) {
		sum += dig[i];
	}
	sum *= 3;
	for (i = 1; i < SIZE - 1; i += 2) {
		sum += dig[i];
	}
	dig[SIZE - 1] = (10 - sum % 10) % 10;

	printf("\nThe check digit is: %d \n", dig[SIZE - 1]);
	return 0;
}
```

**Output:** Given the digits of the sample run, the program prints the check digit 2. The output format, however, differs from the sample run in two places. The loop that prints the input repeats the whole `"입력된 숫자: %d"`, so `입력된 숫자: ` is printed 11 times, once per digit, and the last line has a colon after `is`, as in `The check digit is: 2`. To match the sample run, move `printf("입력된 숫자: ");` before the loop and run only `printf("%d", dig[i]);` inside it.

```text
Please enter the first eleven UPC digits, separated by white space: 
0 3 6 0 0 0 2 9 1 4 5
입력된 숫자: 0입력된 숫자: 3입력된 숫자: 6입력된 숫자: 0입력된 숫자: 0입력된 숫자: 0입력된 숫자: 2입력된 숫자: 9입력된 숫자: 1입력된 숫자: 4입력된 숫자: 5
The check digit is: 2 
```

> **Note:** **`scanf_s` and `%1d`.** `scanf_s` is a function provided by Visual Studio, and for the numeric conversion `%1d` it behaves exactly like `scanf` (see [the solution to Chapter 6, Exercise 1](../Ch06_Functions/Solutions.md#exercise-1-rounding-a-real-number)). If the first 11 digits are 0 1 2 3 4 5 6 7 8 9 0, the sum 20 at odd positions times 3 is 60, and adding the sum 25 at even positions gives 85, so the program prints the check digit 5.

---

<br>

## Exercise 2: Selection Sort Variant

**Textbook Problem:** A variant of Chapter 7, Example 7-11 (ascending selection sort)

**Problem:** Rewrite the ascending selection sort of textbook Example 7-11 so that it picks the maximum of the unsorted portion and sends it to its final position from the back. The result must be in ascending order. The full problem and the code of Example 7-11 are in [Exercise 2](Exercises.md#exercise-2-selection-sort-variant).

### Solution

**Approach:** In an array sorted in ascending order, the largest value must be in the last position. Therefore, finding the maximum of the unsorted portion `data[0]`-`data[i]`, swapping it with `data[i]`, and decreasing `i` by one from `SIZE - 1` grows the sorted part from `data[i]` to the end. This is the same as Example 7-11, which sends the minimum to the front and grows the sorted part from the front, except for the direction ([Chapter 7, Section 5.6](Concepts_Lecture.md#56-selection-sort)).

- **Outer loop:** It decreases `i` from `SIZE - 1` to 0 to choose the position `i` to fill in this pass, and initializes `index_max` to `i`.
- **Inner loop:** It decreases `j` from `i - 1` to 0 and changes `index_max` to `j` if `data[index_max] < data[j]`. When the inner loop ends, `index_max` is the index of the maximum among `data[0]`-`data[i]`.
- **Swap and output:** Only if `i != index_max` does it swap `data[i]` and `data[index_max]`, and after each pass it prints the whole array with `print_array()` from Example 7-11.
- **Trace:** Starting from `{52, 31, 28, 17, 46}`, at `i` = 4 the maximum 52 (index 0) is swapped with the last element, giving `{46, 31, 28, 17, 52}`; at `i` = 3, 46 (index 0) is swapped, giving `{17, 31, 28, 46, 52}`; at `i` = 2, 31 (index 1) is swapped, giving `{17, 28, 31, 46, 52}`. At `i` = 1, 28 is already in place, so no swap occurs.

**Code:** [Lab_Q2.c](../../Coursework/Lab07_Arrays/Lab_Q2.c)

```c
/**
 * @file    A10104-1_C07Q2.c
 * @brief   Q2. 선택 정렬 변형
 * @author  박철원 (Cheolwon Park)
 * @date    2024-05-11
 */

#include <stdio.h>
#define SIZE 5

void print_array(int arr[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int data[SIZE] = { 52, 31, 28, 17, 46 };
    int i, j, temp;
    int index_max;

    for (i = SIZE - 1; i >= 0; i--) {
        index_max = i;

        for (j = i - 1; j >= 0; j--) {
            if (data[index_max] < data[j])
                index_max = j;
        }

        if (i != index_max) {
            temp = data[i];
            data[i] = data[index_max];
            data[index_max] = temp;
        }

        printf("i = %d회 반복 후 배열 : ", i);
        print_array(data, SIZE);
    }

    return 0;
}
```

**Output:** After the third pass (`i` = 2), the array is sorted in ascending order as `17 28 31 46 52`, and no swaps occur in the remaining passes. Each line ends with one space printed by `print_array()`.

```text
i = 4회 반복 후 배열 : 46 31 28 17 52 
i = 3회 반복 후 배열 : 17 31 28 46 52 
i = 2회 반복 후 배열 : 17 28 31 46 52 
i = 1회 반복 후 배열 : 17 28 31 46 52 
i = 0회 반복 후 배열 : 17 28 31 46 52 
```

> **Note:** **Number of passes.** The outer loop runs down to `i` = 0, but at `i` = 0 the inner loop never runs and no swap occurs. A portion with only one element left is already sorted, so writing the condition as `i > 0`, which repeats only `SIZE - 1` times like Example 7-11, gives the same result. Also, the 4 in `i = 4회 반복 후` in the output is not a repetition count but the index of the position filled in that pass.

---

<br>

## Exercise 3: Computing Frequency and Relative Frequency

**Problem:** Fill an integer array of 40 elements with random numbers from 150 to 199 using `rand()`, and print the frequency and relative frequency of the five intervals obtained by dividing from 150 in units of 10. Change the seed with `srand((unsigned)time(NULL))` and count the frequencies with a `switch` statement. The full problem and sample run are in [Exercise 3](Exercises.md#exercise-3-computing-frequency-and-relative-frequency).

### Solution

**Approach:** The expression `(value - 150) / 10`, which turns a value into an interval number, maps 150-159 to 0, 160-169 to 1, ..., and 190-199 to 4. Integer division keeps only the quotient, so all values in the same interval get the same number ([Chapter 7, Section 5.7](Concepts_Lecture.md#57-frequency-counting)).

- **Generating random numbers:** It calls `srand((unsigned)time(NULL));` once at program start so that each run produces a different sequence. `rand() % 50` is 0-49, so adding 150 gives a value from 150 to 199 ([Chapter 7, Section 5.8](Concepts_Lecture.md#58-random-numbers-rand-srand-time)).
- **Counting frequencies:** Each time it generates an element, it increases the corresponding `frequency` element by 1 in `case 0`-`case 4` of `switch ((data[i] - 150) / 10)`. Without the `break` at the end of each `case`, execution would continue into the statements of the following `case`, so the `break` statements are required.
- **Relative frequency:** It divides by a `double` constant, as in `frequency[i] / 40.0`, to perform floating-point division. Writing `frequency[i] / 40` would be integer division, and every relative frequency for a count below 40 would become 0.
- **Output:** It prints four lines of 10 using `data[10 * i + j]`, and then for each interval prints the range from `150 + 10 * i` to `150 + 10 * i + 9`, the frequency, and the relative frequency to three decimal places.

**Code:** [Lab_Q3.c](../../Coursework/Lab07_Arrays/Lab_Q3.c)

```c
/**
 * @file    A10104-1_C07Q3.c
 * @brief   Q3. 빈도와 상대 빈도 계산
 * @author  박철원 (Cheolwon Park)
 * @date    2024-05-11
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int frequency[5] = { 0 }, data[40], i, j;
    double relative_freq[5];

    srand((unsigned)time(NULL));

    for (i = 0; i < 40; i++) {
        data[i] = rand() % 50 + 150;

        switch ((data[i] - 150) / 10) {    // data[i] 값에 해당하는 구간의 인덱스
        case 0:
            frequency[0] += 1;
            break;
        case 1:
            frequency[1] += 1;
            break;
        case 2:
            frequency[2] += 1;
            break;
        case 3:
            frequency[3] += 1;
            break;
        case 4:
            frequency[4] += 1;
            break;
        }
    }
    for (i = 0; i < 5; i++)
        relative_freq[i] = frequency[i] / 40.0;

    printf("배열 출력:\n");
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 10; j++) {
            printf("%d ", data[10 * i + j]);
        }
        printf("\n");
    }

    printf("\n\n\n-----------------------------\n");
    printf("구간 범위     도수    상대도수\n");
    printf("-----------------------------\n");

    for (i = 0; i < 5; i++) {
        printf("%d - %d     %2d     %.3f\n",
               150 + 10 * i, 150 + 10 * i + 9,
               frequency[i], relative_freq[i]);
    }

    return 0;
}
```

**Output:** Because the program uses random numbers, the values change with every run. Below is the result of one run; the five frequencies sum to 40 and the relative frequencies sum to 1.000. Compared with the sample run, the first line is `배열 출력:`, the elements are separated by a single space, there are three blank lines before the table, and the table header reads `구간 범위`.

```text
배열 출력:
153 198 185 184 169 153 179 189 159 158 
186 180 169 191 158 180 191 187 159 157 
193 152 182 188 191 197 154 154 154 178 
172 178 187 182 160 195 186 152 170 196 



-----------------------------
구간 범위     도수    상대도수
-----------------------------
150 - 159     12     0.300
160 - 169      3     0.075
170 - 179      5     0.125
180 - 189     12     0.300
190 - 199      8     0.200
```

> **Note:** **Macro constants.** The common requirement of these problems is to specify array sizes with macro constants, but the solution code writes the element count 40 and the number of intervals 5 as literals. Defining `#define SIZE 40` and `#define GROUPS 5` and using them in the array declarations, the loop conditions, and `(double)SIZE` in place of `40.0` would let the sizes be changed in one place ([Chapter 7, Section 1.5](Concepts_Lecture.md#15-using-define-and-sizeof-for-array-size)).

> **Note:** **Bias of `rand() % 50`.** If `RAND_MAX + 1` is not a multiple of 50, some values of `rand() % 50` appear slightly more often than others. When `RAND_MAX` is 2,147,483,647, as in glibc, among the $2^{31}$ values `rand()` can produce, those with remainder 0-47 when divided by 50 number 42,949,673 each, and those with remainder 48 or 49 number 42,949,672 each. The difference is about 1 in 43 million, so it can be ignored in this problem.

---

<br>

## Exercise 4: Judging Array Declarations

**Textbook Problem:** Chapter 7 exercise 2

**Problem:** Select which of six array declarations inside a function are wrong in ANSI C, and explain why some declarations differ from C99 on. The choices are in [Exercise 4](Exercises.md#exercise-4-judging-array-declarations).

### Solution

**Answer:** ②, ③, ⑤, ⑥

**Explanation:** The size of an array must be an integer constant greater than 0 ([Chapter 7, Section 1.3](Concepts_Lecture.md#13-array-declaration)).

- ① is correct.
- ② An array of size 0 does not exist in the standard. Clang issues the warning `zero size arrays are an extension` under `-pedantic` and accepts it only as an extension.
- ③ It has neither a size nor an initializer list, so the number of elements is unknown. Clang reports the error `definition of variable with array type needs an explicit size or an initializer`.
- ④ The macro constant `MAX` becomes 10 in preprocessing, so it is the same as `int arr[10];` and is correct.
- ⑤, ⑥ In C, a `const` variable and an ordinary variable are not constant expressions, so these are wrong in ANSI C. On compilers supporting C99 or later, these two declarations inside a function are interpreted as variable-length arrays (VLAs) and compile. Clang accepts both without a warning, but Visual Studio, which does not support VLAs, reports compile errors. Following the rule of the textbook and using macro constants for array sizes gives the same result on every compiler.

---

<br>

## Exercise 5: Output of Accumulating a 2D Array

**Textbook Problem:** A variation of Chapter 7 exercise 12

**Problem:** Write the output of a program that accumulates the first 3 rows of a 4-by-3 array, only partly initialized, into its last row and then prints the whole array. The code is in [Exercise 5](Exercises.md#exercise-5-output-of-accumulating-a-2d-array).

### Solution

**Approach:** First draw the array after initialization, then follow only the elements the loop changes, `x[3][0]`, `x[3][1]`, and `x[3][2]`.

In row-wise initialization, elements without enough initial values and the whole 4th row, which has none, are 0, so the array before the loop is as follows.

```text
x[0]:  2  4  6
x[1]:  1  3  0
x[2]:  5  0  0
x[3]:  0  0  0
```

The outer loop visits the rows where `i` is 0, 1, and 2, and the inner loop visits each column and adds to `x[3][j]`. Therefore `x[3][0]` = 2 + 1 + 5 = 8, `x[3][1]` = 4 + 3 + 0 = 7, and `x[3][2]` = 6 + 0 + 0 = 6, and the first 3 rows do not change. `%2d` right-aligns in two columns, so each one-digit number gets one space in front.

**Output:**

```text
 2 4 6
 1 3 0
 5 0 0
 8 7 6
```

---

<br>

## Exercise 6: Statements About Array Parameters

**Textbook Problem:** Chapter 7 exercise 6

**Problem:** Select every wrong statement among seven statements about passing arrays as function arguments. The choices are in [Exercise 6](Exercises.md#exercise-6-statements-about-array-parameters).

### Solution

**Answer:** ①, ③, ⑦

**Explanation:** ① A one-dimensional array parameter is declared with its size omitted, as in `int arr[]`, and a size, if written, is ignored. ③ The call passes the name of the array, that is, its starting address, not the value of the first element. ⑦ The parameter `arr` is actually a pointer holding an address, so `sizeof(arr)` is the size of a pointer (8 in a 64-bit environment), which is why the number of elements is received separately, as in ④ ([Chapter 7, Section 5.9](Concepts_Lecture.md#59-passing-arrays-as-function-arguments)). ②, ④, ⑤, and ⑥ are correct. In ⑥, passing an `int` array to a `double arr[]` parameter cannot be processed correctly because the size and interpretation of each element differ, and the compiler reports incompatible pointer types.

---

<br>

## Exercise 7: Functions That Fill and Sum a Real Array

**Textbook Problem:** Chapter 7 programming assignments 6 and 7

**Problem:** Define and test `fill_array`, which fills every element of a `double` array with one value, and `sum_array`, which returns the sum of the elements. The sample run is in [Exercise 7](Exercises.md#exercise-7-functions-that-fill-and-sum-a-real-array).

### Solution

**Approach:** `fill_array`, which changes elements, takes `double arr[]`, and `sum_array`, which only reads them, takes `const double arr[]`; both functions take the number of elements as `size`.

```c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define SIZE 5

void fill_array(double arr[], int size, double value)
{
    int i;

    for (i = 0; i < size; i++)
        arr[i] = value;
}

double sum_array(const double arr[], int size)
{
    double sum = 0.0;
    int i;

    for (i = 0; i < size; i++)
        sum += arr[i];
    return sum;
}

int main(void)
{
    double data[SIZE];
    int i;

    fill_array(data, SIZE, 1.5);
    printf("sum after fill = %.2f\n", sum_array(data, SIZE));

    printf("five real numbers? ");
    for (i = 0; i < SIZE; i++)
        scanf("%lf", &data[i]);
    printf("sum = %f\n", sum_array(data, SIZE));
    return 0;
}
```

- `fill_array(data, SIZE, 1.5)` passes the starting address of the array, so the function changes the elements of `data` directly. The sum is 1.5 × 5 = 7.50.
- The accumulating variable `sum` of `sum_array` must be initialized to 0.0, and since the return type is `double`, the real-number sum is returned as it is.
- `scanf("%lf", &data[i])` passes the address of one element. An array element is also a variable, so `&` is needed.

**Output:**

```text
sum after fill = 7.50
five real numbers? 12.3 4.34 54.45 0.125 0.0002
sum = 71.215200
```

12.3 + 4.34 + 54.45 + 0.125 + 0.0002 = 71.2152, and `%f` prints 6 digits after the decimal point.

---

<br>

## Exercise 8: Seat Reservation

**Textbook Problem:** Chapter 7 programming assignment 10

**Problem:** Write a reservation program that stores the states of 10 seats as 0 and 1 in an array and assigns free seats from the lowest number for each request. The detailed conditions and sample run are in [Exercise 8](Exercises.md#exercise-8-seat-reservation).

### Solution

**Approach:** Keeping a separate count `reserved` of reserved seats gives the number of remaining seats directly as `SEATS - reserved`. Assignment scans the array from the front, changes elements that are 0 to 1, and stops once the requested number has been assigned.

```c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define SEATS 10

void print_seats(const int seat[], int size)
{
    int i;

    printf("seats: [");
    for (i = 0; i < size; i++)
        printf("%c", seat[i] ? 'X' : 'O');
    printf("]\n");
}

int main(void)
{
    int seat[SEATS] = { 0 };
    int reserved = 0, want, i, given;

    while (reserved < SEATS) {
        print_seats(seat, SEATS);
        printf("how many? ");
        if (scanf("%d", &want) != 1 || want <= 0)
            break;
        if (want > SEATS - reserved) {
            printf("only %d seats left\n", SEATS - reserved);
            continue;
        }
        printf("reserved:");
        for (i = 0, given = 0; i < SEATS && given < want; i++) {
            if (seat[i] == 0) {
                seat[i] = 1;
                printf(" %d", i + 1);
                given++;
            }
        }
        printf("\n");
        reserved += want;
    }
    print_seats(seat, SEATS);
    return 0;
}
```

- `int seat[SEATS] = { 0 };` starts with every seat free.
- `print_seats` does not change the array, so it takes it as `const`, and it prints 0 and 1 as `O` and `X` with the conditional operator.
- When the condition `reserved < SEATS` of the outer `while` becomes false, every seat is taken, so the loop ends. If the input is not an integer or is 0 or less, `break` ends it.
- If more seats are requested than remain, only the notice is printed, and `continue` returns to the start of the loop, so the array and `reserved` do not change.
- The assignment loop stops the moment `given < want` becomes false, so it never assigns more than requested. Seat numbers are printed as the index plus 1.

**Output:** This is the result of entering 3, 4, 5, and 3 in order. In the iteration that requests 5 seats, only 3 remain, so nothing is assigned; after the last 3 seats are assigned, `reserved` becomes 10 and the loop ends.

```text
seats: [OOOOOOOOOO]
how many? 3
reserved: 1 2 3
seats: [XXXOOOOOOO]
how many? 4
reserved: 4 5 6 7
seats: [XXXXXXXOOO]
how many? 5
only 3 seats left
seats: [XXXXXXXOOO]
how many? 3
reserved: 8 9 10
seats: [XXXXXXXXXX]
```

---

<br>

## Exercise 9: Rotating an Array to the Left

**Problem:** Write `rotate_left`, which rotates an integer array k places to the left, and handle the case where k is at least the number of elements. The sample run is in [Exercise 9](Exercises.md#exercise-9-rotating-an-array-to-the-left).

### Solution

**Approach:** A rotation by one place saves the first element in a temporary variable, pulls the remaining elements forward by one place, and puts the saved value at the end. This is repeated k times. With n elements, a rotation by n places equals the original array, so k is reduced to `k % size`.

```c
#include <stdio.h>
#define SIZE 7

void rotate_left(int arr[], int size, int k)
{
    int i, j, first;

    k %= size;
    for (i = 0; i < k; i++) {
        first = arr[0];
        for (j = 0; j < size - 1; j++)
            arr[j] = arr[j + 1];
        arr[size - 1] = first;
    }
}

int main(void)
{
    int a[SIZE] = { 1, 2, 3, 4, 5, 6, 7 };
    int i;

    rotate_left(a, SIZE, 3);
    for (i = 0; i < SIZE; i++)
        printf("%d ", a[i]);
    printf("\n");
    rotate_left(a, SIZE, 11);
    for (i = 0; i < SIZE; i++)
        printf("%d ", a[i]);
    printf("\n");
    return 0;
}
```

Following a one-place rotation of `{1, 2, 3, 4, 5, 6, 7}`, `first` saves 1, `arr[0]` through `arr[5]` each receive the value of their right neighbor, 2, 3, 4, 5, 6, and 7, and then 1 is put in `arr[6]`, giving `{2, 3, 4, 5, 6, 7, 1}`. The condition of the inner loop is `j < size - 1`, so the last element read is `arr[size - 1]`, which stays within range. Three rotations give `4 5 6 7 1 2 3`. The 11 places of the second call equal `11 % 7` = 4 places, and together with the earlier 3 places, 7 places have been rotated in all, so the array returns to its original order.

**Output:**

```text
4 5 6 7 1 2 3
1 2 3 4 5 6 7
```

This method performs a one-place rotation, which moves n elements, k times, so the number of element moves is about k × n. Moving the first k elements into a temporary array of size k and pulling the rest forward at once reduces the number of moves to about n.
