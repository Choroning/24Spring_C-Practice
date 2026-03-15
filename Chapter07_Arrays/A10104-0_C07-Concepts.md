# Chapter 07 — Arrays

> **Last Updated:** 2026-03-16
>
> **Textbook Reference:** *Warming-Up C Programming, 2nd Edition* — Chapter 7

---

## Table of Contents

- [1. Array Basics](#1-array-basics)
  - [1.1 Why Arrays](#11-why-arrays)
  - [1.2 Array Concepts](#12-array-concepts)
  - [1.3 Array Declaration](#13-array-declaration)
  - [1.4 `sizeof` with Arrays](#14-sizeof-with-arrays)
  - [1.5 Using `#define` and `sizeof` for Array Size](#15-using-define-and-sizeof-for-array-size)
- [2. Array Initialization](#2-array-initialization)
  - [2.1 Initializer List](#21-initializer-list)
  - [2.2 Omitting Size](#22-omitting-size)
  - [2.3 Without Initialization](#23-without-initialization)
- [3. Array Usage](#3-array-usage)
  - [3.1 Element Access](#31-element-access)
  - [3.2 Array with Loops](#32-array-with-loops)
  - [3.3 Index Out of Bounds](#33-index-out-of-bounds)
- [4. Multidimensional Arrays](#4-multidimensional-arrays)
  - [4.1 2D Array Concept](#41-2d-array-concept)
  - [4.2 2D Declaration and Access](#42-2d-declaration-and-access)
  - [4.3 2D Initialization](#43-2d-initialization)
- [5. Array Applications](#5-array-applications)
  - [5.1 Finding Max / Min](#51-finding-max--min)
  - [5.2 Average and Standard Deviation](#52-average-and-standard-deviation)
  - [5.3 Reversing an Array](#53-reversing-an-array)
  - [5.4 UPC Barcode Check Digit](#54-upc-barcode-check-digit)
  - [5.5 Selection Sort](#55-selection-sort)
  - [5.6 Frequency Counting](#56-frequency-counting)
  - [5.7 Random Numbers (`rand`, `srand`, `time`)](#57-random-numbers-rand-srand-time)
- [Summary](#summary)

---

<br>

## 1. Array Basics

### 1.1 Why Arrays

Without arrays, storing five scores requires five separate variables:

```c
int s1, s2, s3, s4, s5;
scanf("%d", &s1);
scanf("%d", &s2);
scanf("%d", &s3);
scanf("%d", &s4);
scanf("%d", &s5);
```

Problems with this approach:
- You need a new variable name for each value.
- You cannot use a loop to process them.
- The code does not scale (imagine 100 or 1000 values).

An **array** solves all of these:

```c
int scores[5];
for (int i = 0; i < 5; i++) {
    scanf("%d", &scores[i]);
}
```

| Advantage | Explanation |
|:----------|:-----------|
| Same type | All elements share the same data type |
| Contiguous memory | Elements are stored next to each other in memory |
| Same name + index | One name, access each element by index (`scores[0]`, `scores[1]`, ...) |
| Loop-friendly | Process all elements with a simple `for` loop |

### 1.2 Array Concepts

An **array** is a collection of elements of the **same type** stored in **contiguous memory locations**, accessed by a single name and an **index**.

```
scores
┌──────┬──────┬──────┬──────┬──────┐
│  90  │  85  │  70  │  95  │  60  │   ← elements (values)
└──────┴──────┴──────┴──────┴──────┘
   [0]    [1]    [2]    [3]    [4]      ← index (starts from 0)
```

| Term | Meaning |
|:-----|:--------|
| Element | Each individual value stored in the array |
| Index | Integer position starting from **0** |
| Size | Total number of elements in the array |
| Contiguous | Elements occupy consecutive memory addresses |

> **Key Point:** Each element of an array is a **variable** — you can read from it and write to it just like any other variable.

### 1.3 Array Declaration

**Syntax:**

```c
type array_name[SIZE];
```

- `type` — the data type of each element (`int`, `double`, `char`, etc.).
- `array_name` — the identifier for the array.
- `SIZE` — must be a **positive integer constant** (known at compile time).

```c
int a[5];           // OK: integer literal
#define N 10
int b[N];           // OK: macro constant (#define)

const int size = 5;
int c[size];        // NOT OK in standard C: const variable is NOT a compile-time constant
```

**Rules for `SIZE`:**

| Rule | Detail |
|:-----|:-------|
| Must be positive integer constant | Literals (`5`), `#define` macros (`N`), or `enum` values |
| `const` variable NOT allowed | `const int n = 5;` is still a **variable** in C, not a constant expression |
| Compiler checks type | Ensures `SIZE` is an integer constant expression |
| Compiler does NOT check range | `int x[0];` or `int x[-1];` may compile but cause undefined behavior |

> **Warning:** The compiler checks whether the size is an integer constant, but it does **not** verify that the value is valid. Declaring `int arr[0];` or a negative size may compile without error but leads to undefined behavior.

### 1.4 `sizeof` with Arrays

The `sizeof` operator returns the total number of **bytes** occupied by its operand.

```c
int arr[5];

printf("Total bytes : %lu\n", sizeof(arr));        // 20 (5 * 4)
printf("Element bytes: %lu\n", sizeof(arr[0]));     // 4
printf("Element count: %lu\n", sizeof(arr) / sizeof(arr[0])); // 5
```

| Expression | Result | Meaning |
|:-----------|:-------|:--------|
| `sizeof(arr)` | `5 * sizeof(int)` = 20 | Total bytes of the entire array |
| `sizeof(arr[0])` | `sizeof(int)` = 4 | Bytes of one element |
| `sizeof(arr) / sizeof(arr[0])` | 5 | Number of elements |

> **Tip:** `sizeof(arr) / sizeof(arr[0])` is the standard idiom for computing the element count of an array without hard-coding the size.

### 1.5 Using `#define` and `sizeof` for Array Size

Using a **macro constant** to define the array size lets you change it in one place:

```c
#define SIZE 5

int main(void) {
    int arr[SIZE];

    for (int i = 0; i < SIZE; i++) {
        scanf("%d", &arr[i]);
    }
    // ...
}
```

If you later need 10 elements, you only change `#define SIZE 10` — every `SIZE` in the code updates automatically.

**Macro constant vs variable for size calculation:**

```c
#define SIZE 5
int arr[SIZE];

// OK: SIZE is a macro constant, replaced at preprocessing
int len1 = sizeof(arr) / sizeof(arr[0]);  // 5

// Also OK at runtime:
int len2 = sizeof(arr) / sizeof(arr[0]);  // 5 (sizeof is evaluated at compile time)
```

> **Key Point:** Prefer `#define` for array sizes. It makes your code maintainable and avoids magic numbers scattered throughout.

---

<br>

## 2. Array Initialization

### 2.1 Initializer List

Initialize an array at declaration with values in braces:

```c
int a[5] = {1, 2, 3, 4, 5};   // all 5 elements initialized
```

**Partial initialization** — remaining elements are automatically set to **0**:

```c
int b[5] = {1, 2, 3};          // b = {1, 2, 3, 0, 0}
int c[5] = {0};                // c = {0, 0, 0, 0, 0}  (all zeros)
```

**Errors:**

```c
int d[3] = {1, 2, 3, 4};       // Compile error: too many initializers
int e[3] = {};                  // Compile error: empty initializer list
```

| Initializer | Result | Notes |
|:------------|:-------|:------|
| `{1,2,3,4,5}` | All elements set | Exact match to size |
| `{1,2,3}` for size 5 | `{1,2,3,0,0}` | Remaining filled with 0 |
| `{0}` for size 5 | `{0,0,0,0,0}` | Idiomatic "all zeros" |
| Too many values | Compile error | More initializers than size |
| `{}` | Compile error | Empty braces not allowed in C |

### 2.2 Omitting Size

When you provide an initializer list, you can **omit the size** — the compiler infers it from the number of values:

```c
int z[] = {-1, 0, 1};   // size is 3 (inferred from 3 values)
```

You can then compute the size with `sizeof`:

```c
int len = sizeof(z) / sizeof(z[0]);  // 3
```

> **Tip:** Omitting the size is convenient for small, fixed lists. For large arrays or arrays that need a named constant size, use `#define`.

### 2.3 Without Initialization

If you declare an array **without initializing** it, the elements contain **garbage values** (whatever was previously in that memory):

```c
int arr[5];
printf("%d\n", arr[0]);  // garbage! Undefined behavior
```

> **Warning:** Always initialize arrays before reading from them. Uninitialized local arrays contain unpredictable values. Use `= {0}` to zero-initialize when you don't have specific values.

---

<br>

## 3. Array Usage

### 3.1 Element Access

Access individual elements using the **subscript operator** `[]`. The index can be any integer expression.

```c
int arr[5] = {10, 20, 30, 40, 50};

// Read
int x = arr[0];        // x = 10
int y = arr[2 + 1];    // y = arr[3] = 40

// Write
arr[4] = 99;           // arr = {10, 20, 30, 40, 99}

// Index with variable
int i = 2;
arr[i] = 77;           // arr = {10, 20, 77, 40, 99}
arr[i - 1] = 88;       // arr = {10, 88, 77, 40, 99}
```

> **Key Point:** The index can be a literal (`arr[3]`), a variable (`arr[i]`), or any integer expression (`arr[i-1]`, `arr[2+3]`).

### 3.2 Array with Loops

The `for` loop is the standard pattern for processing arrays:

**Input:**

```c
#define SIZE 5
int arr[SIZE];

printf("Enter %d integers:\n", SIZE);
for (int i = 0; i < SIZE; i++) {
    scanf("%d", &arr[i]);
}
```

**Output:**

```c
printf("Array contents:\n");
for (int i = 0; i < SIZE; i++) {
    printf("%d ", arr[i]);
}
printf("\n");
```

**Sum:**

```c
int sum = 0;
for (int i = 0; i < SIZE; i++) {
    sum += arr[i];
}
printf("Sum: %d\n", sum);
```

> **Tip:** Always use `i < SIZE` (not `i <= SIZE`) as the loop condition. Valid indices are `0` to `SIZE - 1`.

### 3.3 Index Out of Bounds

C does **not** perform bounds checking on array accesses. Accessing an index outside the valid range (`0` to `SIZE - 1`) causes **undefined behavior**.

```c
#define SIZE 5
int arr[SIZE] = {1, 2, 3, 4, 5};

int val = arr[5];    // OUT OF BOUNDS: reads garbage from memory after the array
arr[5] = 99;         // OUT OF BOUNDS: writes to memory after the array → corrupts data
arr[-1] = 0;         // OUT OF BOUNDS: writes before the array → corrupts data
```

| Action | Result |
|:-------|:-------|
| Read out of bounds (`arr[SIZE]`) | Returns garbage value (whatever is in that memory) |
| Write out of bounds (`arr[SIZE] = x`) | Corrupts adjacent memory — may crash at runtime |
| Compiler detection | **None** — the compiler does NOT catch out-of-bounds access |

> **Warning:** Out-of-bounds access is one of the most dangerous bugs in C. The compiler will not warn you. Always verify that your index is within `0` to `SIZE - 1`.

---

<br>

## 4. Multidimensional Arrays

### 4.1 2D Array Concept

A **2D array** is a table (matrix) with **rows** and **columns**. Think of it as an "array of arrays."

```
matrix[3][4]

        col 0   col 1   col 2   col 3
row 0 [  1   |   2   |   3   |   4  ]
row 1 [  5   |   6   |   7   |   8  ]
row 2 [  9   |  10   |  11   |  12  ]
```

In memory, 2D arrays are stored in **row-major order** — all elements of row 0 come first, then row 1, etc.

```
Memory: [1][2][3][4][5][6][7][8][9][10][11][12]
         ← row 0 →  ← row 1 →  ←  row 2   →
```

### 4.2 2D Declaration and Access

**Declaration:**

```c
#define ROWS 3
#define COLS 4

int matrix[ROWS][COLS];
```

**Access:** `matrix[i][j]` — row `i`, column `j`.

**Input with nested loops:**

```c
for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
        scanf("%d", &matrix[i][j]);
    }
}
```

**Output with nested loops:**

```c
for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
        printf("%4d", matrix[i][j]);
    }
    printf("\n");
}
```

**`sizeof` with 2D arrays:**

```c
int m[3][4];
printf("Total bytes: %lu\n", sizeof(m));                   // 48 (3*4*4)
printf("One row bytes: %lu\n", sizeof(m[0]));               // 16 (4*4)
printf("One element bytes: %lu\n", sizeof(m[0][0]));        // 4
printf("Rows: %lu\n", sizeof(m) / sizeof(m[0]));            // 3
printf("Cols: %lu\n", sizeof(m[0]) / sizeof(m[0][0]));      // 4
```

### 4.3 2D Initialization

**Row-by-row (with inner braces):**

```c
int m[2][3] = {
    {1, 2, 3},
    {4, 5, 6}
};
```

**Flat (without inner braces):**

```c
int m[2][3] = {1, 2, 3, 4, 5, 6};   // same as above
```

**Partial initialization** — remaining elements are filled with **0**:

```c
int m[2][3] = {
    {1, 2},       // row 0 = {1, 2, 0}
    {4}           // row 1 = {4, 0, 0}
};
```

**All zeros:**

```c
int m[3][4] = {0};    // all 12 elements are 0
```

> **Tip:** Using inner braces `{{...}, {...}}` makes the row structure clear and is the preferred style.

---

<br>

## 5. Array Applications

### 5.1 Finding Max / Min

Scan through the array, keeping track of the current maximum and minimum.

```c
#define SIZE 5
int arr[SIZE] = {34, 12, 78, 56, 23};

int max = arr[0];
int min = arr[0];

for (int i = 1; i < SIZE; i++) {
    if (arr[i] > max) {
        max = arr[i];
    }
    if (arr[i] < min) {
        min = arr[i];
    }
}

printf("Max: %d\n", max);  // 78
printf("Min: %d\n", min);  // 12
```

> **Key Point:** Initialize `max` and `min` to `arr[0]` (the first element), then loop from index **1**. This avoids using arbitrary initial values like `0` or `INT_MAX`.

### 5.2 Average and Standard Deviation

**Average:**

```c
#define SIZE 5
int arr[SIZE] = {90, 85, 70, 95, 60};

int sum = 0;
for (int i = 0; i < SIZE; i++) {
    sum += arr[i];
}
double avg = (double)sum / SIZE;
printf("Average: %.2f\n", avg);  // 80.00
```

**Standard deviation** (requires `<math.h>` for `sqrt`):

```c
#include <math.h>

// ... (avg computed as above)

double variance = 0.0;
for (int i = 0; i < SIZE; i++) {
    variance += (arr[i] - avg) * (arr[i] - avg);
}
variance /= SIZE;
double stddev = sqrt(variance);
printf("Standard Deviation: %.2f\n", stddev);
```

> **Tip:** Compile with `-lm` flag when using `<math.h>` functions: `gcc program.c -lm`

### 5.3 Reversing an Array

Swap elements from both ends, moving toward the center:

```c
#define SIZE 5
int arr[SIZE] = {1, 2, 3, 4, 5};

for (int i = 0; i < SIZE / 2; i++) {
    int temp = arr[i];
    arr[i] = arr[SIZE - 1 - i];
    arr[SIZE - 1 - i] = temp;
}
// arr = {5, 4, 3, 2, 1}
```

```
Before: [1] [2] [3] [4] [5]
         ↕               ↕       swap i=0 and i=4
After:  [5] [2] [3] [4] [1]
             ↕       ↕           swap i=1 and i=3
After:  [5] [4] [3] [2] [1]
                 ↑                i=2: middle element stays
```

### 5.4 UPC Barcode Check Digit

A **UPC barcode** has 12 digits. The 12th digit (check digit) is computed from the first 11:

1. Sum of digits at **odd** positions (1st, 3rd, 5th, ...) multiplied by **3**.
2. Add the sum of digits at **even** positions (2nd, 4th, 6th, ...).
3. Check digit = `(10 - total % 10) % 10`.

```c
#include <stdio.h>
#define SIZE 12

int main(void) {
    int upc[SIZE];

    printf("Enter the first 11 UPC digits:\n");
    for (int i = 0; i < SIZE - 1; i++) {
        scanf("%d", &upc[i]);
    }

    int sum = 0;
    for (int i = 0; i < SIZE - 1; i++) {
        if (i % 2 == 0) {
            sum += upc[i] * 3;   // odd positions (1st, 3rd, ...)
        } else {
            sum += upc[i];       // even positions (2nd, 4th, ...)
        }
    }
    upc[SIZE - 1] = (10 - sum % 10) % 10;

    printf("Check digit: %d\n", upc[SIZE - 1]);

    return 0;
}
```

> **Key Point:** Using an array + loop replaces 11 separate variables and makes the code scalable and readable.

### 5.5 Selection Sort

**Selection sort** repeatedly finds the minimum element from the unsorted portion and places it at the beginning.

**Algorithm (ascending order):**

1. For each position `i` from `0` to `SIZE - 2`:
   - Find the index of the **minimum** element in `arr[i..SIZE-1]`.
   - **Swap** `arr[i]` with `arr[min_idx]`.

```c
#define SIZE 5
int arr[SIZE] = {64, 25, 12, 22, 11};

for (int i = 0; i < SIZE - 1; i++) {
    int min_idx = i;
    for (int j = i + 1; j < SIZE; j++) {
        if (arr[j] < arr[min_idx]) {
            min_idx = j;
        }
    }
    // Swap arr[i] and arr[min_idx]
    int temp = arr[i];
    arr[i] = arr[min_idx];
    arr[min_idx] = temp;
}
```

**Step-by-step trace:**

```
Initial: [64] [25] [12] [22] [11]

Pass 0: min_idx=4 (11), swap arr[0]↔arr[4]
         [11] [25] [12] [22] [64]

Pass 1: min_idx=2 (12), swap arr[1]↔arr[2]
         [11] [12] [25] [22] [64]

Pass 2: min_idx=3 (22), swap arr[2]↔arr[3]
         [11] [12] [22] [25] [64]

Pass 3: min_idx=3 (25), no effective swap
         [11] [12] [22] [25] [64]
```

> **Key Point:** Selection sort has time complexity O(n^2). It is simple to implement and understand, but not efficient for large datasets.

### 5.6 Frequency Counting

Use the **array index** as a category to count how many values fall into each category.

```c
#define DATA_SIZE 20
#define RANGE 10      // count values 0..9

int data[DATA_SIZE] = {3, 7, 2, 3, 8, 5, 1, 3, 7, 2,
                       9, 0, 5, 3, 7, 1, 8, 2, 6, 4};
int freq[RANGE] = {0};

for (int i = 0; i < DATA_SIZE; i++) {
    freq[data[i]]++;    // data[i] is the category index
}

printf("Value  Frequency\n");
for (int i = 0; i < RANGE; i++) {
    printf("%3d    %d\n", i, freq[i]);
}
```

**Counting ranges (e.g., 150-199 in groups of 10):**

```c
#define SIZE 40
#define GROUPS 5

int freq[GROUPS] = {0};

for (int i = 0; i < SIZE; i++) {
    int group = (arr[i] - 150) / 10;   // 150-159→0, 160-169→1, ...
    freq[group]++;
}
```

> **Tip:** The key insight is mapping a value to an index: `index = (value - base) / interval`. This turns counting into a simple array increment.

### 5.7 Random Numbers (`rand`, `srand`, `time`)

The `<stdlib.h>` header provides `rand()` and `srand()`. The `<time.h>` header provides `time()`.

```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    srand((unsigned)time(NULL));   // seed with current time

    // Generate 10 random numbers in range [150, 199]
    for (int i = 0; i < 10; i++) {
        int r = rand() % 50 + 150;  // rand() % range + min
        printf("%d ", r);
    }
    printf("\n");

    return 0;
}
```

| Function | Header | Purpose |
|:---------|:-------|:--------|
| `rand()` | `<stdlib.h>` | Returns a pseudo-random integer in `[0, RAND_MAX]` |
| `srand(seed)` | `<stdlib.h>` | Sets the seed for `rand()`; same seed gives same sequence |
| `time(NULL)` | `<time.h>` | Returns current time as `time_t` (changes every second) |

**Generating a random number in `[min, max]`:**

```c
int r = rand() % (max - min + 1) + min;
```

> **Warning:** Without calling `srand()`, `rand()` uses the default seed (typically `1`), producing the **same sequence** every time. Always call `srand((unsigned)time(NULL))` once at the start of `main`.

---

<br>

## Summary

| Concept | Key Takeaway |
|:--------|:-------------|
| Why arrays | Replace many variables of the same type; enable loop processing |
| Array concepts | Elements, zero-based index, contiguous memory, each element is a variable |
| Declaration | `type name[SIZE];` — `SIZE` must be a positive integer constant; `#define` OK, `const` NOT OK |
| `sizeof` | `sizeof(arr) / sizeof(arr[0])` = element count |
| `#define` for size | Change size in one place; avoids magic numbers |
| Initializer list | `{1,2,3}` — partial init fills rest with 0; `{0}` for all zeros; `{}` is an error |
| Omitting size | `int z[] = {-1,0,1};` — size inferred from initializer count |
| Without init | Contains garbage values; must initialize before use |
| Element access | `arr[i]` for read/write; index can be any integer expression |
| Array with loops | `for` loop is the standard pattern; `scanf` with `&arr[i]` |
| Out of bounds | Valid: `0` to `SIZE-1`; compiler does NOT catch; write OOB corrupts memory |
| 2D array | `int m[ROWS][COLS];` — table with rows and columns; row-major order in memory |
| 2D access | `m[i][j]`; nested loops for traversal |
| 2D initialization | `{{1,2},{3,4}}` or flat `{1,2,3,4}`; partial init fills with 0 |
| Max / Min | Initialize with `arr[0]`, loop from index 1 |
| Average / Std Dev | Cast to `double` for average; `sqrt()` from `<math.h>` for std dev |
| Reverse array | Swap from both ends toward center; `SIZE / 2` iterations |
| UPC check digit | Array replaces 11 variables; loop + formula |
| Selection sort | Find min in unsorted portion, swap to front; O(n^2) |
| Frequency counting | Use array index as category; `freq[value]++` |
| Random numbers | `srand((unsigned)time(NULL))` once; `rand() % range + min` |

---
