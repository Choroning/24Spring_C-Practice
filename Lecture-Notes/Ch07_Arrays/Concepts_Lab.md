# Chapter 7 Lab — One-Dimensional and Multidimensional Arrays

[Repository Guide](../../README.md) | [English](Concepts_Lab.md) | [한국어](Concepts_Lab.ko.md)

> **Last Updated:** 2026-10-27
>
> 문제풀이 중심의 C언어 연습, 김용일 외, Ch 8, 9

> **Learning Objectives:**
> 1. State the three elements needed to declare an array and access its elements by index
> 2. Initialize a one-dimensional array in three ways and find the values of omitted elements
> 3. Input, print, and compute over the elements of an array in turn with loops and `sizeof`
> 4. Declare and initialize two-dimensional arrays and explain their row-major memory layout
> 5. Write programs that find the position of a value in an array and transpose a matrix

---

## Table of Contents

- [1. One-Dimensional Arrays](#1-one-dimensional-arrays)
  - [1.1 What an Array Is](#11-what-an-array-is)
  - [1.2 Declaring Arrays and Accessing Elements](#12-declaring-arrays-and-accessing-elements)
  - [1.3 Initializing Arrays](#13-initializing-arrays)
- [2. One-Dimensional Array Practice](#2-one-dimensional-array-practice)
  - [2.1 Printing the Number of Days per Month](#21-printing-the-number-of-days-per-month)
  - [2.2 Sum of Entered Elements](#22-sum-of-entered-elements)
  - [2.3 Element-wise Difference of Two Arrays](#23-element-wise-difference-of-two-arrays)
- [3. Multidimensional Arrays](#3-multidimensional-arrays)
  - [3.1 Declaring Multidimensional Arrays](#31-declaring-multidimensional-arrays)
  - [3.2 Accessing Elements of a Two-Dimensional Array](#32-accessing-elements-of-a-two-dimensional-array)
  - [3.3 Actual Memory Layout](#33-actual-memory-layout)
  - [3.4 Initializing Two-Dimensional Arrays](#34-initializing-two-dimensional-arrays)
  - [3.5 Omitting Array Sizes](#35-omitting-array-sizes)
- [4. Array Search and Matrix Practice](#4-array-search-and-matrix-practice)
  - [4.1 Finding the Position of a Value in an Array](#41-finding-the-position-of-a-value-in-an-array)
  - [4.2 Transposing a Matrix](#42-transposing-a-matrix)
- [Summary](#summary)
- [Self-Check Questions](#self-check-questions)

---

<br>

## 1. One-Dimensional Arrays

### 1.1 What an Array Is

An **array** secures several variables of the same data type at once in a contiguous memory space. Instead of declaring variables one by one, as in `int a, b, c, d, e;`, declaring `int arr[5];` places five `int`s side by side in memory, all handled by the same name `arr` and a number ([Chapter 7, Section 1.2](Concepts_Lecture.md#12-array-concepts)).

### 1.2 Declaring Arrays and Accessing Elements

Declaring an array requires three things ([Chapter 7, Section 1.3](Concepts_Lecture.md#13-array-declaration)).

| Element | Meaning | In `int array[10];` |
|:-----|:-----|:-----|
| Array length (size) | The number of variables (elements) in the array; set with a constant | `10` |
| Data type of the elements | The type of each element of the array | `int` |
| Array name | The name used to access the array | `array` |

*Table 1. The three elements needed to declare an array*

The position of each element of an array is given by an **index**, and indices start at 0. So the first element of an array of size 10 is `array[0]` and the last is `array[9]` ([Chapter 7, Section 3.1](Concepts_Lecture.md#31-element-access)).

```c
int array[10];      // declares an array of 10 ints
array[0] = 10;      // first element: index 0
array[1] = 20;      // second element
array[2] = 30;      // third element
/* ... */
array[9] = 100;     // tenth element: the last index is 9
```

The following program stores four real numbers in an array and computes their average.

```c
#include <stdio.h>

int main(void)
{
    double total;
    double val[4];      // four double elements in a row

    val[0] = 1.01;
    val[1] = 2.02;
    val[2] = 3.03;
    val[3] = 4.04;

    total = val[0] + val[1] + val[2] + val[3];    // total is assigned here, so it needs no initial 0
    printf("평균 : %.1f \n", total / 4);

    return 0;
}
```

```text
평균 : 2.5 
```

A variable that accumulates a sum must be initialized with `sum = 0` before adding with `sum += ...`, but `total` in this program receives the sum of the four elements in a single assignment, `total = val[0] + ... + val[3];`, so it does not need to be initialized to 0. 1.01 + 2.02 + 3.03 + 4.04 = 10.1, and the average is 2.525, which prints as 2.5 with `%.1f`.

> **Caution:** The C compiler does not check whether an index is within the range of the array. Accessing with an out-of-range index, as in `array[10]`, is undefined behavior and can overwrite the value of another variable or crash the program ([Chapter 7, Section 3.3](Concepts_Lecture.md#33-index-out-of-bounds)).

### 1.3 Initializing Arrays

An array can be initialized at its declaration with a list of initial values in braces ([Chapter 7, Section 2.1](Concepts_Lecture.md#21-initializer-list), [Section 2.2](Concepts_Lecture.md#22-omitting-size)).

```c
#include <stdio.h>

int main(void)
{
    int arr1[5] = {1, 2, 3, 4, 5};
    int arr2[] = {1, 3, 5, 7, 9};      // size 5 from the number of initial values
    int arr3[5] = {1, 2};              // the missing elements become 0
    int i;

    for (i = 0; i < 5; i++)
        printf("%d %d %d\n", arr1[i], arr2[i], arr3[i]);

    return 0;
}
```

```text
1 1 1
2 3 2
3 5 0
4 7 0
5 9 0
```

| Declaration | Size | Elements |
|:-----|:---:|:-----|
| `int arr1[5] = {1, 2, 3, 4, 5};` | 5 | 1, 2, 3, 4, 5 |
| `int arr2[] = {1, 3, 5, 7, 9};` | 5 | If the size is omitted, the number of initial values sets the size |
| `int arr3[5] = {1, 2};` | 5 | 1, 2, 0, 0, 0; if there are too few initial values, the rest are initialized to 0 |

*Table 2. Three ways to initialize a one-dimensional array*

---

<br>

## 2. One-Dimensional Array Practice

The elements of an array can be handled one by one, but that is inefficient for a large array, so they are processed by making the index the variable of a loop ([Chapter 7, Section 3.2](Concepts_Lecture.md#32-array-with-loops)). The following programs compile with `gcc -std=c99 -Wall` without warnings, and the outputs are from actual runs.

### 2.1 Printing the Number of Days per Month

**Problem:** Initialize the array as `int day[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};` and print its contents in the form `1월은 31일`.

**Solution:** Indices start at 0 and months at 1, so the element at index `i` is the number of days of month `i + 1`. `%2d` fits the month into two columns so that the lines of January and December align.

```c
#include <stdio.h>

int main(void)
{
    int day[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};   // days of each month
    int i;

    for (i = 0; i < 12; i++)
        printf("%2d월은 %d일\n", i + 1, day[i]);   // index i holds month i + 1

    return 0;
}
```

```text
 1월은 31일
 2월은 28일
 3월은 31일
 4월은 30일
 5월은 31일
 6월은 30일
 7월은 31일
 8월은 31일
 9월은 30일
10월은 31일
11월은 30일
12월은 31일
```

### 2.2 Sum of Entered Elements

**Problem:** Read the values of the one-dimensional array `int val[5]` of five elements from the screen, and print the sum of the five elements in the form `+ 1 + 2 + 4 + 6 + -4 = 9`.

**Solution:** `scanf` must receive the address of the place to store into, so the address of the element, `&val[i]`, is used. The first loop reads all the input, and the second prints each element while accumulating the sum.

```c
#define _CRT_SECURE_NO_WARNINGS  // allows scanf in Visual Studio
#include <stdio.h>

int main(void)
{
    int val[5];
    int i, sum = 0;

    for (i = 0; i < 5; i++) {
        printf("%d번째 data input: ", i + 1);
        scanf("%d", &val[i]);      // &val[i] is the address of element i
    }

    for (i = 0; i < 5; i++) {
        printf(" + %d", val[i]);
        sum += val[i];
    }
    printf(" = %d\n", sum);

    return 0;
}
```

```text
1번째 data input: 1
2번째 data input: 2
3번째 data input: 4
4번째 data input: 6
5번째 data input: -4
 + 1 + 2 + 4 + 6 + -4 = 9
```

### 2.3 Element-wise Difference of Two Arrays

**Problem:** For the five-element arrays `int arr1[5] = {1, 3, 5, 7, 9};` and `int arr2[] = {4, 4, 6, 6, 8};`, print in table form the difference between the elements at the same index.

**Solution:** Read the elements of both arrays with the same index `i` and compute `arr1[i] - arr2[i]`. The number of elements is the size of the whole array divided by the size of one element, `sizeof(arr1) / sizeof(arr1[0])`, that is, 20 / 4 = 5. This way the number of repetitions need not change when elements are added to the array ([Chapter 7, Section 1.4](Concepts_Lecture.md#14-sizeof-with-arrays)).

```c
#include <stdio.h>

int main(void)
{
    int arr1[5] = {1, 3, 5, 7, 9};
    int arr2[] = {4, 4, 6, 6, 8};
    int size = (int)(sizeof(arr1) / sizeof(arr1[0]));    // number of elements: 20 / 4 = 5
    int i;

    printf("arr1  arr2  (arr1-arr2)\n");
    for (i = 0; i < size; i++)
        printf("%3d %5d %9d\n", arr1[i], arr2[i], arr1[i] - arr2[i]);

    return 0;
}
```

```text
arr1  arr2  (arr1-arr2)
  1     4        -3
  3     4        -1
  5     6        -1
  7     6         1
  9     8         1
```

> **Note:** The result of `sizeof` is the unsigned integer type `size_t`, and in a 64-bit (x64) build `size_t` is 8 bytes. Assigning this value to an `int` variable or comparing it with an `int` makes Visual Studio warn about possible data loss (C4267) or a signed/unsigned mismatch, whereas in a 32-bit (x86) build `size_t` is 4 bytes and this warning does not appear. Rather than switching the platform setting to x86, converting explicitly with `(int)` as in the code above, or using a `size_t` variable with `%zu`, avoids the warning in any build.

Finding the maximum and minimum of seven array elements is covered in [HW07 Problem 2](../../Coursework/HW07_Arrays/Assignment-Explanation.md#3-problem-2-comparing-values-in-an-array).

---

<br>

## 3. Multidimensional Arrays

### 3.1 Declaring Multidimensional Arrays

An array of two or more dimensions is a **multidimensional array**. The number of brackets is the number of dimensions ([Chapter 7, Section 4](Concepts_Lecture.md#4-multidimensional-arrays)).

| Declaration | Dimensions |
|:-----|:-----|
| `int arr[100];` | One-dimensional array |
| `int arr[10][10];` | 10 × 10, two-dimensional array |
| `int arr[5][5][5];` | 5 × 5 × 5, three-dimensional array |

*Table 3. Array declarations and dimensions*

The two-dimensional array `int arr2[3][4];` can be thought of as a table of 3 rows and 4 columns. The first size is the number of rows and the second the number of columns.

### 3.2 Accessing Elements of a Two-Dimensional Array

An element of a two-dimensional array is accessed by writing the row index and the column index in turn, as `arr[row][column]`. Both indices start at 0 ([Chapter 7, Section 4.2](Concepts_Lecture.md#42-2d-declaration-and-access)).

```c
int arr[3][3];
arr[0][0] = 2;      // row 0, column 0
arr[1][0] = 4;      // row 1, column 0
arr[2][2] = 8;      // row 2, column 2: the last element
```

```text
          col 0  col 1  col 2
        ┌──────┬──────┬──────┐
 row 0  │  2   │      │      │   arr[0][0]
        ├──────┼──────┼──────┤
 row 1  │  4   │      │      │   arr[1][0]
        ├──────┼──────┼──────┤
 row 2  │      │      │  8   │   arr[2][2]
        └──────┴──────┴──────┘
```

*Figure 1. Positions of three elements in a 3 × 3 array*

### 3.3 Actual Memory Layout

A multidimensional array also uses a contiguous memory space, like a one-dimensional array. Two or three dimensions are only a way of interpreting and understanding that contiguous space as rows and columns. C stores the array in **row-major** order, placing all the elements of the first row before the next row.

```c
#include <stdio.h>

int main(void)
{
    int a[2][3] = { {1, 2, 3}, {4, 5, 6} };
    int i, j;

    for (i = 0; i < 2; i++)
        for (j = 0; j < 3; j++)
            printf("a[%d][%d] = %d at offset %d bytes\n", i, j, a[i][j],
                   (int)((char *)&a[i][j] - (char *)&a[0][0]));

    return 0;
}
```

```text
a[0][0] = 1 at offset 0 bytes
a[0][1] = 2 at offset 4 bytes
a[0][2] = 3 at offset 8 bytes
a[1][0] = 4 at offset 12 bytes
a[1][1] = 5 at offset 16 bytes
a[1][2] = 6 at offset 20 bytes
```

```text
 Memory layout of int a[2][3] (int is 4 bytes)
  0       4       8       12      16      20      (byte offset)
┌───────┬───────┬───────┬───────┬───────┬───────┐
│a[0][0]│a[0][1]│a[0][2]│a[1][0]│a[1][1]│a[1][2]│
└───────┴───────┴───────┴───────┴───────┴───────┘
 └────── row 0 ─────────┘└────── row 1 ─────────┘
```

*Figure 2. A 2 × 3 array placed in memory in row-major order*

The position of `a[i][j]` is (i × 3 + j) × 4 bytes from the start of the array.

### 3.4 Initializing Two-Dimensional Arrays

A two-dimensional array is initialized either with braces around each row or by listing the values in order inside a single pair of braces ([Chapter 7, Section 4.3](Concepts_Lecture.md#43-2d-initialization)).

```c
int a[3][3] = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };
int b[3][3] = { {1}, {4, 5}, {7, 8, 9} };      // each row is filled from the left, the rest is 0
int c[3][3] = { 1, 2, 3, 4, 5, 6, 7 };         // filled row by row, the rest is 0
```

Printing the elements of the three arrays row by row gives the following.

```text
 1 2 3
 4 5 6
 7 8 9
--
 1 0 0
 4 5 0
 7 8 9
--
 1 2 3
 4 5 6
 7 0 0
```

- **With braces around each row:** Each pair of braces fills one row from the left. The first row of `b` is `{1}`, so it becomes 1, 0, 0, and the second row is `{4, 5}`, so it becomes 4, 5, 0.
- **Listed in one pair of braces:** The values fill the array from the first row in row-major order. The seven values of `c` fill the first row, the second row, and the first element of the third row, and the remaining two elements become 0.

> **Note:** The initialization of `c`, which omits the braces around each row, is valid C, but clang issues the `-Wmissing-braces` warning ("suggest braces around initialization of subobject") under `-Wall`. Writing braces around each row, which makes the rows clear, is preferable.

### 3.5 Omitting Array Sizes

A one-dimensional array may omit its size if it has initial values. In a two-dimensional array, only the first size (the number of rows) may be omitted, and the second size (the number of columns) must always be written. The number of columns is needed to decide how many of the listed initial values form one row.

```c
int arr[] = {1, 2, 3, 4, 5};                  // OK: 5 elements
int arr[][] = {1, 2, 3, 4, 5, 6, 7, 8};       // error: the column size is missing
int arr[3][] = {1, 2, 3, 4, 5, 6, 7, 8};      // error: the column size is missing
int arr[][4] = {1, 2, 3, 4, 5, 6, 7, 8};      // OK: 2 rows of 4
int arr[][2] = {1, 2, 3, 4, 5, 6, 7, 8};      // OK: 4 rows of 2
int arr[4][2] = {1, 2, 3, 4, 5, 6, 7, 8};     // OK
int arr[2][4] = {1, 2, 3, 4, 5, 6, 7, 8};     // OK
```

Each of the declarations above is a separate example. The two declarations without the number of columns give the clang error "array has incomplete element type 'int[]'". When the number of rows is omitted, it becomes the number of initial values divided by the number of columns, rounded up, so `int arr[][4]` has 2 rows and `int arr[][2]` has 4 rows.

---

<br>

## 4. Array Search and Matrix Practice

The solution code of the following problems is the example files in this unit folder. Each file compiles with `gcc -std=c99 -Wall` without warnings, and the outputs are from actual runs.

### 4.1 Finding the Position of a Value in an Array

**Problem:** In the array of size 7, `int arr[] = { 23, 45, -34, 23, -124, 22, 2 };`, print the position (index) where a value entered on the screen is stored.

**Solution:** Use **sequential search**, which compares from the beginning of the array to the end in order ([Chapter 7, Section 5.5](Concepts_Lecture.md#55-sequential-search)). The number of repetitions is obtained with `sizeof(arr) / sizeof(arr[0])`, so the code need not change when the number of elements changes.

- **When the same value appears several times:** Breaking out as soon as the value is found, as in the first comment of the code, prints only the first position of a value that appears two or more times, such as 23. So the code compares to the end without `break` and counts the matches in `count`.
- **When the value is absent:** If `count` is 0 after the loop, the program prints a message that the value is not in the array.
- **A function that prints the array:** The comment at the end of the code shows the form of a function `print_array` that receives an array and its size and prints the elements. Passing arrays to functions is covered in Chapter 8.

**Code:** [Example_LinearSearch.c](Example_LinearSearch.c)

```c
#define _CRT_SECURE_NO_WARNINGS  // allows scanf in Visual Studio
#include <stdio.h>

int main() // works even if the number of elements in the array changes
{
    int arr[] = { 23, 45, -34, 23, -124, 22, 2 };
    int i, val, count = 0;

    printf("arr = ");
    for (i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
    {
        printf("%d ", arr[i]);
    }

    printf("\n>> input value: ");
    scanf(" %d", &val);

    /*for (i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
    {
        if (val == arr[i])
        {
            printf("인덱스 %d에 %d값이 위치함! \n", i, val);
            break; // written this way, it does not work correctly when the value appears two or more times in the array
        } // in that case, declare and use a variable such as count
    }
    if (i == sizeof(arr) / sizeof(arr[0]))
    {
        printf("배열에 %d값이 없습니다! \n", val);
    }*/

    for (i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
    {
        if (val == arr[i])
        {
            printf("인덱스 %d에 %d값이 위치함! \n", i, val);
            count++;
        }
    }
    if (count == 0)
    {
        printf("배열에 %d값이 없습니다! \n", val);
    }


    // With the function below, main can call it as print_array(arr, size);

    /*void print_array(int pArr[], int size){
        int i;
        for (i = 0; i < size; i++)
            printf("%d ", pArr[i]);
        printf("\n");
    }*/
}
```

```text
arr = 23 45 -34 23 -124 22 2 
>> input value: 23
인덱스 0에 23값이 위치함! 
인덱스 3에 23값이 위치함! 
```

```text
arr = 23 45 -34 23 -124 22 2 
>> input value: 7
배열에 7값이 없습니다! 
```

> **Note:** `i` is an `int` and `sizeof(arr) / sizeof(arr[0])` is the unsigned `size_t`, so comparing them converts `i` to `size_t`. In this code `i` never becomes negative, so the result is the same, but a stricter warning option (`-Wextra`) reports a sign-comparison warning (the note of Section 2.3).

An assignment that solves the same sequential search with an array of size 10 is in [HW07 Problem 4](../../Coursework/HW07_Arrays/Assignment-Explanation.md#5-problem-4-finding-a-value-in-an-array).

### 4.2 Transposing a Matrix

**Problem:** Transpose the 3 × 3 matrix `int matA[][3] = { {5, 7, 4}, {6, 1, 8}, {3, 2, 7} };` into `int matB[3][3] = { 0 };` and print both matrices. Transposing turns each row into a column.

**Solution:** The element at row i, column j of the transposed matrix is the element at row j, column i of the original. So a double `for` loop visits every (i, j) and executes `matB[j][i] = matA[i][j];`. The output uses the same double loop, printing each row with `%3d` and then ending the line. The comment at the start of the code is an attempt to pass the two-dimensional array to a function for printing; passing a two-dimensional array to a function is covered in [HW09 Problem 2](../../Coursework/HW09_Pointers-II/Assignment-Explanation.md#2-printing-a-2d-array).

**Code:** [Example_Transpose.c](Example_Transpose.c)

```c
#include <stdio.h>

// Passing array contents between functions (not covered yet)
/*void print_array(int* pmat[], int vsize, int hsize)
{
    int i, j;

    for (i = 0; i < vsize; i++)
    {
        for (j = 0; j < hsize; j++)
        {
            printf("%3d", *pmat);
            *pmat++;
        }
        printf("\n");
    }
}*/

int main()
{
    int matA[][3] = { {5, 7, 4}, {6, 1, 8}, {3, 2, 7} };
    int matB[3][3] = { 0 };
    int i, j;

    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            matB[j][i] = matA[i][j];
        }
    }

    printf("[matA] \n");
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            printf("%3d", matA[i][j]);
        }
        printf("\n");
    }

    printf("[matB] \n");
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            printf("%3d", matB[i][j]);
        }
        printf("\n");
    }
}
```

```text
[matA] 
  5  7  4
  6  1  8
  3  2  7
[matB] 
  5  6  3
  7  1  2
  4  8  7
```

The first row 5, 7, 4 of `matA` became the first column of `matB`. The diagonal elements 5, 1, 7 stay in place after transposition.

---

<br>

## Summary

| Concept | Key Summary |
|:-----|:-----|
| Array | Several variables of the same type secured in contiguous memory, declared with a size, an element type, and a name. |
| Index | Gives the position of an element and starts at 0, so the last index of an array of size n is n - 1. |
| One-dimensional initialization | The initial values can set the size, and if there are too few, the remaining elements become 0. |
| Loops and arrays | The index becomes the loop variable to process elements in turn, and the number of elements is `sizeof(arr) / sizeof(arr[0])`. |
| Multidimensional array | The number of brackets is the number of dimensions, and a two-dimensional array is accessed as `arr[row][column]`. |
| Memory layout | Multidimensional arrays are also stored in contiguous memory in row-major order. |
| Two-dimensional initialization | Braces around each row fill row by row; a single list fills in row-major order; the rest become 0. |
| Omitting sizes | A two-dimensional array may omit only the number of rows; the number of columns must always be written. |
| Sequential search | Compares from beginning to end; if a value appears several times, counting to the end without `break` finds them all. |
| Transpose | `matB[j][i] = matA[i][j]` swaps rows and columns. |

---

<br>

## Self-Check Questions

1. **Index:** Write the first and last elements of `int score[30];`, and explain what problem arises when a value is assigned to `score[30]`.

   <details>
   <summary>Answer</summary>

   The first element is `score[0]` and the last is `score[29]`. `score[30]` is outside the range of the array, and since C does not check bounds, writing there overwrites other data, which is undefined behavior.

   </details>

2. **Initialization:** With `int d[6] = {5, 6};`, what are the values of `d[1]` and `d[4]`?

   <details>
   <summary>Answer</summary>

   `d[1]` is the second initial value 6, and `d[4]`, which has no initial value, is 0.

   </details>

3. **Number of elements:** For `double v[] = {1.5, 2.5, 3.5, 4.5};`, write the values of `sizeof(v)` and `sizeof(v) / sizeof(v[0])`.

   <details>
   <summary>Answer</summary>

   A `double` is 8 bytes and there are 4 elements, so `sizeof(v)` is 32, and the number of elements is 32 / 8 = 4.

   </details>

4. **Two-dimensional initialization:** Write the elements of `int m[2][3] = { {1}, {2, 3} };` and `int n[2][3] = { 1, 2, 3 };` row by row.

   <details>
   <summary>Answer</summary>

   `m` has braces around each row, so its first row is 1, 0, 0 and its second row is 2, 3, 0. `n` is a single list, so its first row is 1, 2, 3 and its second row is 0, 0, 0.

   </details>

5. **Memory layout:** In `int a[3][4];`, which element from the start of the array is `a[2][1]`, and how many bytes away is it when `int` is 4 bytes?

   <details>
   <summary>Answer</summary>

   It is stored in row-major order, so it is element 2 × 4 + 1 = 9, counting from 0, and it is 9 × 4 = 36 bytes away.

   </details>
