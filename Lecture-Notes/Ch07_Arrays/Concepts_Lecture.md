# Chapter 7 — Arrays

[Repository Guide](../../README.md) | [English](Concepts_Lecture.md) | [한국어](Concepts_Lecture.ko.md)

> **Last Updated:** 2026-11-27
>
> Warming-Up C Programming, 천정아, Ch 7

> **Learning Objectives:**
> 1. Declare an array and initialize it with an initializer list
> 2. Use `sizeof` to find the total byte size and the element count of an array
> 3. Process an array with loops and explain the danger of an out-of-bounds index
> 4. Declare and initialize a 2D array and traverse it with nested loops
> 5. Implement finding the maximum, average and standard deviation, reversal, sequential search, selection sort, and frequency counting with arrays

---

## Table of Contents

- [1. Array Basics](#1-array-basics)
  - [1.1 The Need for Arrays](#11-the-need-for-arrays)
  - [1.2 Array Concepts](#12-array-concepts)
  - [1.3 Array Declaration](#13-array-declaration)
  - [1.4 `sizeof` with Arrays](#14-sizeof-with-arrays)
  - [1.5 Using `#define` and `sizeof` for Array Size](#15-using-define-and-sizeof-for-array-size)
  - [1.6 Memory Layout of an Array and Element Addresses](#16-memory-layout-of-an-array-and-element-addresses)
- [2. Array Initialization](#2-array-initialization)
  - [2.1 Initializer List](#21-initializer-list)
  - [2.2 Omitting Size](#22-omitting-size)
  - [2.3 Without Initialization](#23-without-initialization)
- [3. Array Usage](#3-array-usage)
  - [3.1 Element Access](#31-element-access)
  - [3.2 Array with Loops](#32-array-with-loops)
  - [3.3 Index Out of Bounds](#33-index-out-of-bounds)
  - [3.4 Copying and Comparing Arrays](#34-copying-and-comparing-arrays)
  - [3.5 Common Mistakes with Arrays](#35-common-mistakes-with-arrays)
- [4. Multidimensional Arrays](#4-multidimensional-arrays)
  - [4.1 2D Array Concept](#41-2d-array-concept)
  - [4.2 2D Declaration and Access](#42-2d-declaration-and-access)
  - [4.3 2D Initialization](#43-2d-initialization)
  - [4.4 Using 2D Arrays: Row and Column Totals](#44-using-2d-arrays-row-and-column-totals)
  - [4.5 Memory of a 2D Array and Position Computation](#45-memory-of-a-2d-array-and-position-computation)
- [5. Array Applications](#5-array-applications)
  - [5.1 Finding Max / Min](#51-finding-max--min)
  - [5.2 Average and Standard Deviation](#52-average-and-standard-deviation)
  - [5.3 Reversing an Array](#53-reversing-an-array)
  - [5.4 UPC Barcode Check Digit](#54-upc-barcode-check-digit)
  - [5.5 Sequential Search](#55-sequential-search)
  - [5.6 Selection Sort](#56-selection-sort)
  - [5.7 Frequency Counting](#57-frequency-counting)
  - [5.8 Random Numbers (`rand`, `srand`, `time`)](#58-random-numbers-rand-srand-time)
  - [5.9 Passing Arrays as Function Arguments](#59-passing-arrays-as-function-arguments)
  - [5.10 Inserting and Deleting Elements](#510-inserting-and-deleting-elements)
  - [5.11 Matrix Addition and Transposition](#511-matrix-addition-and-transposition)
- [Concept Applications](#concept-applications)
- [Summary](#summary)
- [Self-Check Questions](#self-check-questions)

---

<br>

## 1. Array Basics

### 1.1 The Need for Arrays

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
- The code does not scale when the values grow to 100 or 1000.

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

*Table 1. Advantages of arrays*

### 1.2 Array Concepts

An **array** is a collection of elements of the **same type** stored in **contiguous memory locations**, accessed by a single name and an **index**.

```text
scores
┌──────┬──────┬──────┬──────┬──────┐
│  90  │  85  │  70  │  95  │  60  │   ← elements (values)
└──────┴──────┴──────┴──────┴──────┘
   [0]    [1]    [2]    [3]    [4]      ← index (starts from 0)
```

*Figure 1. Elements and indices of the array scores*

| Term | Meaning |
|:-----|:--------|
| Element | Each individual value stored in the array |
| Index | Integer position starting from **0** |
| Size | Total number of elements in the array |
| Contiguous | Elements occupy consecutive memory addresses |

*Table 2. Array terminology*

> **Key Point:** Each element of an array is a **variable**, so you can read from it and write to it just like any other variable.

### 1.3 Array Declaration

**Syntax:**

```c
type array_name[SIZE];
```

- `type`: the data type of each element (`int`, `double`, `char`, etc.).
- `array_name`: the identifier for the array.
- `SIZE`: must be an **integer constant greater than 0** and is fixed at compile time.

Declaring an array of N elements of `type` allocates N variables of `type` contiguously in memory.

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
| A `const` variable is not a constant expression | `const int n = 5;` is still a **variable** in C, not a constant expression |
| Compiler checks type | Ensures `SIZE` is an integer constant expression |
| Size must be greater than 0 | A negative size `int x[-1];` is a compile error, and a zero size `int x[0];` violates the standard but gcc and clang accept it as an extension |

*Table 3. Rules for the array size*

> **Caution:** The size of an array must be greater than 0. A negative size is a compile error (gcc reports `size of array 'x' is negative`), and a size of 0 is not allowed in standard C, but gcc and clang accept it as an extension and warn only with `-pedantic`. What the compiler does not check is not the size in a declaration but the index used when accessing the array (Section 3.3).

> **Note:** **Variable length arrays.** C99 allows a **variable length array (VLA)**, whose size is determined at run time, inside a function. So if `int c[size];` in the example above is inside a function, a C99 compiler treats it as a VLA rather than an error, while it cannot be used outside functions (at file scope). VLAs are optional since C11 and through C17 cannot be initialized with an initializer list, so this chapter follows the practice of fixing array sizes with constants.

### 1.4 `sizeof` with Arrays

The `sizeof` operator returns the total number of **bytes** occupied by its operand. The values in the comments below assume an environment where `int` is 4 bytes.

```c wide-ok
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

*Table 4. Results of `sizeof` expressions on an array*

`sizeof(arr) / sizeof(arr[0])` is the standard idiom for computing the element count of an array without hard-coding the size.

> **Note:** **Format specifier for `sizeof`.** The result of `sizeof` has the unsigned integer type `size_t`, so since C99 the correct way to print it is `%zu`. The `%lu` in the code above works on 64-bit Linux and macOS, where `size_t` is the same as `unsigned long`, but not in environments such as 64-bit Windows, where the two types have different sizes.

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

If you later need 10 elements, you only change `#define SIZE 10`, and every `SIZE` in the code is replaced with the new value during preprocessing.

**Macro constant and variable for size calculation:**

```c
#define SIZE 5
int arr[SIZE];

// OK: SIZE is a macro constant, replaced at preprocessing
int len1 = sizeof(arr) / sizeof(arr[0]);  // 5

// Also OK at runtime:
int len2 = sizeof(arr) / sizeof(arr[0]);  // 5 (sizeof is evaluated at compile time)
```

The two expressions compute the same value. Instead of a macro constant, you can store the element count obtained with `sizeof` in a variable (`len1`, `len2`) and use it in loop conditions and elsewhere; unless the array is a VLA, `sizeof` is computed at compile time, so it has no run-time cost.

> **Key Point:** Prefer `#define` for array sizes. It makes your code maintainable and avoids magic numbers scattered throughout.

### 1.6 Memory Layout of an Array and Element Addresses

That the elements of an array are placed in "contiguous memory" can be confirmed by printing their addresses directly. `&a[i]` is the address of the i-th element, and the format specifier `%p` prints an address in hexadecimal. The operating system decides the actual address values at each run, so they change from run to run, but the spacing between elements is always the same.

```c
int a[5] = { 10, 20, 30, 40, 50 };
int i;

for (i = 0; i < 5; i++)
    printf("a[%d] = %d, address %p\n", i, a[i], (void *)&a[i]);
printf("a = %p, sizeof(a) = %zu\n", (void *)a, sizeof(a));
```

```text
a[0] = 10, address 0x16b256af0
a[1] = 20, address 0x16b256af4
a[2] = 30, address 0x16b256af8
a[3] = 40, address 0x16b256afc
a[4] = 50, address 0x16b256b00
a = 0x16b256af0, sizeof(a) = 20
```

The addresses of neighboring elements increase by 4, the size of `int`. In hexadecimal, `...af0`, `...af4`, `...af8`, and `...afc` are followed by `...b00`, since 0xafc + 4 = 0xb00. Drawn as a memory picture, it looks as follows.

```text
address     0x...af0  0x...af4  0x...af8  0x...afc  0x...b00
          ┌─────────┬─────────┬─────────┬─────────┬─────────┐
a         │   10    │   20    │   30    │   40    │   50    │
          └─────────┴─────────┴─────────┴─────────┴─────────┘
index         [0]       [1]       [2]       [3]       [4]
```

*Figure 2. Elements and addresses of the array a*

In general, when the element type is T and the address of the first element is base, the address of `a[i]` is base + i × `sizeof(T)`. Given an index, the compiler computes the address with this formula and reads that position directly, so accessing one `a[i]` takes the same time however many elements there are. This formula is also why indices start at 0: the first element is 0 slots away from the starting address. The last line shows that the array name `a`, written without an index, equals the address of the first element; this relationship is treated in detail with pointers in Chapter 8. By the rules of the standard, an address passed to `%p` is cast to `(void *)`.

---

<br>

## 2. Array Initialization

### 2.1 Initializer List

Initialize an array at declaration with values in braces. The listed initial values are assigned in order starting from element 0:

```c
int a[5] = {1, 2, 3, 4, 5};   // all 5 elements initialized
```

In **partial initialization**, the remaining elements without initial values are automatically set to **0**:

```c
int b[5] = {1, 2, 3};          // b = {1, 2, 3, 0, 0}
int c[5] = {0};                // c = {0, 0, 0, 0, 0}  (all zeros)
```

**Errors:**

```c
int d[3] = {1, 2, 3, 4};       // Compile error: too many initializers
int e[3] = {};                  // Compile error: empty initializer list
```

Both lines violate the standard through C17, but compilers react differently. With too many initial values, gcc and clang issue the warning `excess elements in array initializer` and discard the extra values. Empty braces `{}` do not fit the grammar through C17, but gcc and clang accept them as an extension and warn only with `-pedantic`, and since C23 they are the standard syntax for initializing all elements to 0.

| Initializer | Result | Notes |
|:------------|:-------|:------|
| `{1,2,3,4,5}` | All elements set | Exact match to size |
| `{1,2,3}` for size 5 | `{1,2,3,0,0}` | Remaining filled with 0 |
| `{0}` for size 5 | `{0,0,0,0,0}` | Idiom for setting every element to 0 |
| Too many values | Standard violation (gcc and clang warn and discard the extra values) | More initializers than size |
| `{}` | Standard violation through C17, all zeros since C23 | gcc and clang accept it as an extension |

*Table 5. Result of each initialization form*

### 2.2 Omitting Size

When you provide an initializer list, you can **omit the size**, and the compiler infers it from the number of values:

```c
int z[] = {-1, 0, 1};   // size is 3 (inferred from 3 values)
```

You can then compute the size with `sizeof`:

```c
int len = sizeof(z) / sizeof(z[0]);  // 3
```

Omitting the size is convenient for small, fixed lists. For large arrays or arrays that need a named constant size, `#define` is used.

### 2.3 Without Initialization

If you declare an array inside a function **without initializing** it, the elements contain **garbage values** (whatever was previously in that memory). A global array declared outside functions is automatically initialized to 0, like a global variable (Chapter 6, Section 3.2).

```c
int arr[5];
printf("%d\n", arr[0]);  // garbage! Undefined behavior
```

> **Caution:** Always initialize arrays before reading from them. Uninitialized local arrays contain unpredictable values. Use `= {0}` to zero-initialize when you do not have specific values.

> **Note:** **Designated initializers.** From C99 on, specific elements can be initialized by writing indices in brackets, as in `int a[6] = { [2] = 7, [4] = 9 };`. Elements not designated become 0, so this array is `0 0 7 0 9 0`. The feature is not part of the ANSI C syntax of the textbook, so the initializer list written in order from the front remains the default.

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

The index can be a literal (`arr[3]`), a variable (`arr[i]`), or any integer expression (`arr[i-1]`, `arr[2+3]`).

### 3.2 Array with Loops

The `for` loop is the standard pattern for processing arrays:

**Input:**

```c wide-ok
#define SIZE 5
int arr[SIZE];

printf("Enter %d integers:\n", SIZE);
for (int i = 0; i < SIZE; i++) {
    scanf("%d", &arr[i]);
}
```

**Output:**

```c wide-ok
printf("Array contents:\n");
for (int i = 0; i < SIZE; i++) {
    printf("%d ", arr[i]);
}
printf("\n");
```

**Sum:**

```c wide-ok
int sum = 0;
for (int i = 0; i < SIZE; i++) {
    sum += arr[i];
}
printf("Sum: %d\n", sum);
```

The loop condition uses `i < SIZE`, not `i <= SIZE`. Valid indices are `0` to `SIZE - 1`.

A problem that computes each element from the preceding ones is also solved simply with an array and a loop. The Fibonacci sequence has 0 and 1 as its first two terms, and each later term is the sum of the two terms just before it, so after initializing the first two elements, `fib[i] = fib[i - 1] + fib[i - 2]` is computed from index 2.

```c
#define SIZE 10

int fib[SIZE] = { 0, 1 };       // remaining elements are initialized to 0
int i;

for (i = 2; i < SIZE; i++)
    fib[i] = fib[i - 1] + fib[i - 2];
for (i = 0; i < SIZE; i++)
    printf("%d ", fib[i]);
printf("\n");
```

```text
0 1 1 2 3 5 8 13 21 34
```

When `i` is 2, `fib[2] = fib[1] + fib[0]` = 1 + 0 = 1; when `i` is 3, `fib[3]` = 1 + 1 = 2; and in the last iteration, when `i` is 9, `fib[9]` = 21 + 13 = 34. Starting the loop at 0 would read an out-of-range element such as `fib[-1]`, so when an index expression contains `i - 1` or `i - 2`, the loop must start from the value at which that expression becomes 0 or more. Unlike the recursive `fib` of Chapter 6, this keeps values already computed in the array and reuses them, so each term is computed only once.

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
| Write out of bounds (`arr[SIZE] = x`) | Corrupts adjacent memory; another variable may change or the program may crash at runtime |
| Compiler detection | **Not guaranteed**; the standard requires no check, and only some compilers warn in obvious cases such as a constant index |

*Table 6. Results of out-of-bounds access*

> **Caution:** Out-of-bounds access is one of the most dangerous bugs in C. Compilers usually do not warn, and even a compiler such as clang that warns about a constant index like `arr[5]` cannot catch an out-of-bounds variable index. Always verify that your index is within `0` to `SIZE - 1`.

An out-of-range constant index can be compared with the array size by the compiler, so Clang issues the following warning under `-Wall`. However, when the index is a variable, as in `for (i = 0; i <= SIZE; i++) arr[i] = 0;`, its value is unknown before execution, so the code compiles without a warning. The last iteration of this loop writes 0 to `arr[5]`, the memory right after the array, and can change another variable that was there. A tool that catches such accesses at run time (AddressSanitizer) is treated in Chapter 11.

```text
warning: array index 5 is past the end of the array (that has type 'int[5]') [-Warray-bounds]
```

### 3.4 Copying and Comparing Arrays

An array name written without an index means the starting address of the array. This address is a value that cannot be changed, so even for arrays of the same data type and size, the assignment operator cannot copy a whole array. To copy an array, assign its elements one by one.

```c
int x[5] = {10, 20, 30, 40, 50};
int y[5] = {0};

// y = x;              // compile error: cannot assign a whole array
for (int i = 0; i < 5; i++) {
    y[i] = x[i];       // copy element by element
}
```

`x == y` compiles, but it compares the starting addresses of the two arrays, not their contents. The starting addresses of two different arrays can never be equal, so this expression is always false regardless of the contents, and gcc and clang warn about it with `-Wall`. To compare the contents, compare the elements one by one.

```c wide-ok
int i;
for (i = 0; i < 5; i++) {
    if (x[i] != y[i]) {
        break;         // no need to compare further once a difference is found
    }
}
if (i == 5) {
    printf("The two arrays are equal.\n");
}
```

If the loop ends without `break`, `i` becomes 5, so `i == 5` means all elements are equal. Another way is to set a flag variable (for example, `is_equal`) to 1 and change it to 0 when a different element is found.

The rule that an array name is used as a starting address, and how to pass an array to a function, are covered together with pointers in Chapter 8.

### 3.5 Common Mistakes with Arrays

The compiler reports many array mistakes as errors or warnings. The following code contains four mistakes.

```c
#define SIZE 3

int a[SIZE], b[SIZE] = { 1, 2, 3 };
int sum, i;

a = { 4, 5, 6 };                // assigns an initializer list after declaration
printf("%d\n", b);              // prints an array name with %d
for (i = 0; i < SIZE; i++)
    sum += b[i];                // sum is not initialized
if (a == b)                     // compares arrays with ==
    printf("same\n");
```

```text
error: expected expression
warning: format specifies type 'int' but the argument has type 'int *' [-Wformat]
warning: variable 'sum' is uninitialized when used here [-Wuninitialized]
warning: array comparison always evaluates to false [-Wtautological-compare]
```

| Mistake | Cause | Correction |
|:-----|:-----|:-----|
| Initializer list after declaration | A brace list can be used only for initialization in a declaration | Assign each element, or assign with a loop |
| Printing an array name | An array name without an index is the address of the first element (`int *`) | Print `b[i]` with a loop |
| Uninitialized accumulator | The initial value of the local variable `sum` is undetermined | Declare `int sum = 0;` |
| Comparing arrays with `==` | It compares the starting addresses of the two arrays, so it is always false | Compare element by element as in Section 3.4 |

*Table 7. Common mistakes with arrays*

The error on the first line means that a brace list cannot be an expression. The `int *` of the second warning shows that the array name has turned into an address. The third mistake is especially hard to find because each run may give a different sum. As the fourth warning shows, Clang reports that comparing arrays with `==` is meaningless, but it is only a warning and the code compiles, so warnings must always be read.

---

<br>

## 4. Multidimensional Arrays

### 4.1 2D Array Concept

A **multidimensional array** is an array that uses two or more indices to access an element, and it is used to represent matrices, tables, image data with width and height, and so on. There is no limit on the number of dimensions, but arrays of three or more dimensions take a lot of memory and should be used with care.

A **2D array** is a table (matrix) with **rows** and **columns**. It can be viewed as an array whose elements are 1D arrays, that is, an array of arrays.

```text
matrix[3][4]

        col 0   col 1   col 2   col 3
row 0 [  1   |   2   |   3   |   4  ]
row 1 [  5   |   6   |   7   |   8  ]
row 2 [  9   |  10   |  11   |  12  ]
```

*Figure 3. 2D array matrix with 3 rows and 4 columns*

In memory, 2D arrays are stored in **row-major order**. That is, all elements of row 0 come first, followed by row 1.

```text
Memory: [1][2][3][4][5][6][7][8][9][10][11][12]
         ← row 0 →  ← row 1 →  ←  row 2   →
```

*Figure 4. Row-major memory layout of a 2D array*

### 4.2 2D Declaration and Access

**Declaration:**

```c
#define ROWS 3
#define COLS 4

int matrix[ROWS][COLS];
```

The part in the `[]` immediately after the array name is the array's size, and the rest is the element type. So `int matrix[3][4];` is an array of 3 elements of type `int[4]`, and the number of `int` elements is rows × columns, or 12.

**Access:** `matrix[i][j]` is the element at row `i`, column `j`.

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

Increasing the row index in the outer loop and the column index in the inner loop accesses the elements in the order in which they are allocated in memory.

**`sizeof` with 2D arrays (assuming a 4-byte `int`):**

```c wide-ok
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

Values listed flat are assigned in the order in which the elements are allocated in memory, starting from `m[0][0]`. gcc with `-Wall` warns that inner braces are missing (`missing braces around initializer`).

In **partial initialization**, the remaining elements without initial values are filled with **0**:

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

**Omitting the row size:** With an initializer list, the row size can be omitted, but the column size cannot. Without the column size, the compiler cannot know the size of one row.

```c
int w[][3] = {{1, 2}, {3}, {4, 5}};   // int w[3][3] = {{1,2,0}, {3,0,0}, {4,5,0}}
int z[][2] = {1, 2, 3, 4, 5, 6, 7};   // int z[4][2] = {{1,2}, {3,4}, {5,6}, {7,0}}
// int v[2][] = {{1, 2}, {3, 4}};    // compile error: the column size cannot be omitted
```

Using inner braces `{{...}, {...}}` makes the row structure clear and is the preferred style.

### 4.4 Using 2D Arrays: Row and Column Totals

Two-dimensional arrays are used to process tabular data. The following program stores the scores of 3 students in 3 subjects in `score[student][subject]` and computes the total and average of each student (the row sums) and the average of each subject (the column sums).

```c
#define ROWS 3
#define COLS 3

int score[ROWS][COLS] = { { 90, 85, 70 }, { 60, 75, 95 }, { 80, 80, 80 } };
int col_sum[COLS] = { 0 };
int i, j, row_sum;

for (i = 0; i < ROWS; i++) {
    row_sum = 0;                          // restart from 0 for each row
    for (j = 0; j < COLS; j++) {
        row_sum += score[i][j];           // sum of row i
        col_sum[j] += score[i][j];        // accumulate the sum of column j
    }
    printf("student %d: total = %d, average = %.2f\n", i, row_sum, row_sum / (double)COLS);
}
for (j = 0; j < COLS; j++)
    printf("subject %d: average = %.2f\n", j, col_sum[j] / (double)ROWS);
```

```text
student 0: total = 245, average = 81.67
student 1: total = 230, average = 76.67
student 2: total = 240, average = 80.00
subject 0: average = 76.67
subject 1: average = 80.00
subject 2: average = 81.67
```

A row sum is complete each time one pass of the inner loop ends, so one variable (`row_sum`) suffices, and it must be reset to 0 at the start of the outer loop. A column sum is complete only after all rows have been visited, so each column needs its own slot for accumulation, and the one-dimensional array `col_sum` is used. The sum for subject 0 is 90 + 60 + 80 = 230, so its average is 230 / 3 = 76.67. Without the `(double)` cast when computing an average, the division becomes integer division and the fractional part is lost (Chapter 3, Section 6).

### 4.5 Memory of a 2D Array and Position Computation

Checking the row-major order of Section 4.1 with addresses gives the following. The six elements of `int m[2][3]` continue at 4-byte intervals from `m[0][0]` to `m[1][2]`, and the first element of row 1, `m[1][0]`, comes right after the last element of row 0, `m[0][2]`.

```c
int m[2][3] = { { 1, 2, 3 }, { 4, 5, 6 } };
int i, j;

for (i = 0; i < 2; i++)
    for (j = 0; j < 3; j++)
        printf("m[%d][%d] = %d, address %p\n", i, j, m[i][j], (void *)&m[i][j]);
printf("%zu %zu %zu\n", sizeof(m), sizeof(m[0]), sizeof(m[0][0]));
```

```text
m[0][0] = 1, address 0x16f65eaf0
m[0][1] = 2, address 0x16f65eaf4
m[0][2] = 3, address 0x16f65eaf8
m[1][0] = 4, address 0x16f65eafc
m[1][1] = 5, address 0x16f65eb00
m[1][2] = 6, address 0x16f65eb04
24 12 4
```

```text
          ┌──────────── m[0] ─────────────┐ ┌──────────── m[1] ─────────────┐
address end   af0        af4        af8        afc        b00        b04
          ┌──────────┬──────────┬──────────┬──────────┬──────────┬──────────┐
value     │    1     │    2     │    3     │    4     │    5     │    6     │
          └──────────┴──────────┴──────────┴──────────┴──────────┴──────────┘
position     [0][0]     [0][1]     [0][2]     [1][0]     [1][1]     [1][2]
order          0          1          2          3          4          5
```

*Figure 5. Elements and addresses of the 2D array m*

`sizeof(m)` is 24 bytes for 6 elements, `sizeof(m[0])` is 12 bytes for one row of type `int[3]`, and `sizeof(m[0][0])` is 4 bytes for one element. Hence the number of rows is `sizeof(m) / sizeof(m[0])` = 2, and the number of columns is `sizeof(m[0]) / sizeof(m[0][0])` = 3.

In a two-dimensional array with C columns, `m[i][j]` is element number i × C + j from the start of memory. `m[1][1]` is number 1 × 3 + 1 = 4 (counting from 0), so it is at b00, 4 × 4 = 16 bytes from the starting address af0. This formula contains the number of columns C but not the number of rows. That is why the column size of a 2D array parameter, treated in Section 5.9, cannot be omitted: to compute the position of `m[i][j]`, the function must know C, while the number of rows may be received as a separate parameter.

---

<br>

## 5. Array Applications

### 5.1 Finding Max / Min

Scan through the array, keeping track of the current maximum and minimum.

```c wide-ok
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

```c wide-ok
#define SIZE 5
int arr[SIZE] = {90, 85, 70, 95, 60};

int sum = 0;
for (int i = 0; i < SIZE; i++) {
    sum += arr[i];
}
double avg = (double)sum / SIZE;
printf("Average: %.2f\n", avg);  // 80.00
```

The **standard deviation** is the square root of the mean of the squared differences between each value and the mean $\mu$ (the variance). For $N$ values $x_1, \ldots, x_N$, it is as follows.

$$\sigma = \sqrt{\frac{1}{N}\sum_{i=1}^{N}(x_i - \mu)^2}$$

The square root is computed with `sqrt` from `<math.h>`:

```c wide-ok
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

For the values in the example, the differences from the mean are 10, 5, -10, 15, and -20, and the sum of their squares is 850, so the variance is 850 / 5 = 170 and the standard deviation is $\sqrt{170} \approx 13.04$.

> **Note:** **Tip.** With gcc on Linux, add the `-lm` option, which links the math library, when using `<math.h>` functions (`gcc program.c -lm`). On macOS the math functions are in the default C library, so it can be omitted.

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

```text
Before: [1] [2] [3] [4] [5]
         ↕               ↕       swap i=0 and i=4
After:  [5] [2] [3] [4] [1]
             ↕       ↕           swap i=1 and i=3
After:  [5] [4] [3] [2] [1]
                 ↑                i=2: middle element stays
```

*Figure 6. Swaps in reversing an array*

### 5.4 UPC Barcode Check Digit

A **UPC barcode** has 12 digits. The 12th digit (check digit) is computed from the first 11:

1. Sum of digits at **odd** positions (1st, 3rd, 5th, ...) multiplied by **3**.
2. Add the sum of digits at **even** positions (2nd, 4th, 6th, ...).
3. Check digit = `(10 - total % 10) % 10`.

For example, if the first 11 digits are 0 3 6 0 0 0 2 9 1 4 5, the sum at odd positions is 0 + 6 + 0 + 2 + 1 + 5 = 14, which times 3 is 42, and the sum at even positions is 3 + 0 + 0 + 9 + 4 = 16, so the total is 58. The check digit is (10 - 8) % 10 = 2.

```c wide-ok
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

Using an array and a loop replaces 11 separate variables and makes the code scalable and readable.

### 5.5 Sequential Search

**Searching** is finding data that satisfies a condition in a given data set, and **sorting** is arranging data items in a specified order. The simplest way to find an element whose value equals the **search key** in an array is **sequential search**, which compares the elements with the key in turn, starting from element 0.

```c wide-ok
#define SIZE 8
int data[SIZE] = {23, 45, 12, 67, 34, 89, 21, 56};
int key = 34;
int index = -1;          // -1 if not found

for (int i = 0; i < SIZE; i++) {
    if (data[i] == key) {
        index = i;       // record the position and stop searching
        break;
    }
}

if (index >= 0)
    printf("%d is at data[%d].\n", key, index);   // 34 is at data[4].
else
    printf("%d was not found.\n", key);
```

If several elements equal the key, this code finds the first position. If the key is absent or in the last position, all $n$ elements are compared, so the time complexity is $O(n)$.

To find **all** elements equal to the key, keep comparing to the end instead of stopping after a match, and print the position or count each time one is found.

```c
int data[SIZE] = { 7, 3, 9, 3, 5, 1, 3, 8, 2, 9 };
int key = 3, count = 0, i;

for (i = 0; i < SIZE; i++) {
    if (data[i] == key) {
        printf("found at index %d\n", i);
        count++;
    }
}
printf("count = %d\n", count);
```

```text
found at index 1
found at index 3
found at index 6
count = 3
```

In this case the number of comparisons is always n, whether the key is present or not. When only the first position is needed, end the loop with `break` as soon as it is found, and if the index is n after the loop, conclude that the key is absent. When this is made into a function, the convention is to return the found index and to return -1, which cannot be a valid index, when the key is not found.

> **Note:** **Binary search in a sorted array.** If an array is sorted in ascending order, **binary search** can be used, which compares with the middle element and halves the search range each time. Searching `{3, 8, 15, 21, 30, 42, 57}` for 30: the middle of the initial range 0-6 is index 3, whose 21 is less than 30, so the range shrinks to 4-6; the middle of that range is index 5, whose 42 is greater than 30, so the range shrinks to 4-4; then 30 is found at index 4. That is 3 comparisons, fewer than the 5 of sequential search. With n elements the number of comparisons drops to about log₂ n, but the method cannot be used on an unsorted array.

### 5.6 Selection Sort

**Selection sort** repeatedly finds the minimum element from the unsorted portion and places it at the beginning. Arranging elements in increasing order is called **ascending order**, and in decreasing order **descending order**.

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

```text
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

*Figure 7. Array state after each pass of selection sort*

Example 7-11 in the textbook works the same way and skips the swap when `i` equals the index of the minimum.

Selection sort has time complexity $O(n^2)$. It is simple to implement and understand, but not efficient for large datasets.

The number of comparisons can be counted directly. With n elements, the first pass compares against the remaining n - 1, the next pass against n - 2, and so on. The total number of comparisons is therefore (n - 1) + (n - 2) + ... + 1 = n(n - 1)/2: 4 + 3 + 2 + 1 = 10 for 5 elements, 45 for 10, and 4950 for 100. The number of comparisons is the same regardless of the initial order, and there is at most one swap per pass, so at most n - 1 swaps. That the comparisons grow about a hundredfold when n grows tenfold is what $O(n^2)$ means.

> **[Algorithms]** Analyzing running time with asymptotic notation such as $O(n)$ and $O(n^2)$, merge sort, which sorts in $O(n \log n)$ time and is faster than selection sort, and binary search, which finds a key in a sorted array in $O(\log n)$ time, are covered in Algorithms. The sequential search of Section 5.5 and the selection sort of this section are the simplest search and sort and serve as the starting point for that analysis and comparison.

### 5.7 Frequency Counting

Use the **array index** as a category to count how many values fall into each category.

```c wide-ok
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

**Counting ranges (e.g., grouping 150-199 in units of 10):**

```c
#define SIZE 40
#define GROUPS 5

int freq[GROUPS] = {0};

for (int i = 0; i < SIZE; i++) {
    int group = (arr[i] - 150) / 10;   // 150-159→0, 160-169→1, ...
    freq[group]++;
}
```

The key to frequency counting is mapping a value to an index (`index = (value - base) / interval`). This turns counting into a simple array increment.

### 5.8 Random Numbers (`rand`, `srand`, `time`)

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
| `time(NULL)` | `<time.h>` | Returns current time as `time_t` (usually changes every second) |

*Table 8. Functions for generating random numbers*

**Generating a random number in `[min, max]`:**

```c
int r = rand() % (max - min + 1) + min;
```

> **Caution:** Without calling `srand()`, `rand()` produces, as the standard specifies, the same sequence as after calling `srand(1)`, so every run yields the **same sequence**. Always call `srand((unsigned)time(NULL))` once at the start of `main`.

### 5.9 Passing Arrays as Function Arguments

Code that processes an array can be made into a function and reused for many arrays. A parameter that receives an array is declared with brackets only and no size, as in `int arr[]`, and the number of elements is received as a separate parameter. When calling, only the name of the array, without an index, is passed as the argument.

```c
#define SIZE 5

void print_array(const int arr[], int size)
{
    int i;

    for (i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void double_all(int arr[], int size)
{
    int i;

    for (i = 0; i < size; i++)
        arr[i] *= 2;
}

int sum_array(const int arr[], int size)
{
    int i, sum = 0;

    for (i = 0; i < size; i++)
        sum += arr[i];
    return sum;
}

int main(void)
{
    int scores[SIZE] = { 3, 1, 4, 1, 5 };

    print_array(scores, SIZE);
    double_all(scores, SIZE);
    print_array(scores, SIZE);
    printf("sum = %d\n", sum_array(scores, SIZE));
    printf("first three: sum = %d\n", sum_array(scores, 3));
    return 0;
}
```

```text
3 1 4 1 5
6 2 8 2 10
sum = 28
first three: sum = 16
```

This result shows that an array argument behaves differently from an ordinary variable. Under pass-by-value in Chapter 6, changing a parameter did not change the argument, but after `double_all(scores, SIZE)` is called, every element of `scores` has doubled. The name of an array is its starting address, so what is passed to the function is not a copy of all the elements but that address, and the function reads and changes the elements of the original array through it. A function that does not change the elements declares its parameter with `const`, as in `const int arr[]`, and assigning to an element of an array declared this way causes the compile error `read-only variable is not assignable`. Passing a value smaller than the whole array as `size` processes only the front part, so `sum_array(scores, 3)` returns 6 + 2 + 8 = 16.

Inside a function, the number of elements cannot be obtained with `sizeof` of the parameter. In the following code, `sizeof(data)` in `main` is the whole array, 40 bytes, but `sizeof(arr)` inside the function is the size of one address, 8 bytes. Clang issues the warning `sizeof on array function parameter will return size of 'int *' instead of 'int[]'` for this use. This is why the number of elements is passed as a separate parameter.

```c
void show_size(int arr[])
{
    printf("in function: %zu\n", sizeof(arr));
}

int main(void)
{
    int data[10];

    printf("in main: %zu\n", sizeof(data));
    show_size(data);
    return 0;
}
```

```text
in main: 40
in function: 8
```

When a two-dimensional array is received as a parameter, the number of rows may be omitted but the number of columns must be written. As seen in Section 4.5, the compiler must know the size of one row to compute the position of `m[i][j]`. Declare it as `int total(int m[][COLS], int rows)`; omitting the column size as well, as in `int m[][]`, causes the error `array has incomplete element type 'int[]'`. Why passing an array means passing an address is treated in Chapter 8 together with pointers.

### 5.10 Inserting and Deleting Elements

An array has a fixed size, so inserting or removing an element in the middle requires moving the later elements one slot at a time by hand. The following code treats only the first `n` slots of an array of size `CAP` as in use and defines `insert_at`, which puts a value at position `pos`, and `delete_at`, which removes the element at position `pos`. Both functions return the new number of elements.

```c
#define CAP 8

int insert_at(int arr[], int n, int pos, int value)
{
    int i;

    if (n >= CAP || pos < 0 || pos > n)     // full, or invalid position
        return n;
    for (i = n; i > pos; i--)               // move back one slot, from the end
        arr[i] = arr[i - 1];
    arr[pos] = value;
    return n + 1;
}

int delete_at(int arr[], int n, int pos)
{
    int i;

    if (pos < 0 || pos >= n)
        return n;
    for (i = pos; i < n - 1; i++)           // move forward one slot, from the front
        arr[i] = arr[i + 1];
    return n - 1;
}

int main(void)
{
    int a[CAP] = { 10, 20, 30, 40 };
    int n = 4;

    n = insert_at(a, n, 1, 15);
    print_array(a, n);
    n = delete_at(a, n, 3);
    print_array(a, n);
    n = insert_at(a, n, 9, 99);
    print_array(a, n);
    return 0;
}
```

```text
10 15 20 30 40 (n = 5)
10 15 20 40 (n = 4)
10 15 20 40 (n = 4)
```

`print_array` is a function that prints n elements followed by `(n = ...)`. Following the insertion: `n` is 4 and `pos` is 1, so the loop runs with `i` = 4, 3, and 2.

```text
start            [10][20][30][40][ 0]
i = 4: a[4]=a[3] [10][20][30][40][40]
i = 3: a[3]=a[2] [10][20][30][30][40]
i = 2: a[2]=a[1] [10][20][20][30][40]
a[1] = 15        [10][15][20][30][40]
```

*Figure 8. Array states when inserting 15 at position 1*

The direction of the moves matters. If insertion moved from the front, `a[2] = a[1]` would run first and overwrite the 30 in `a[2]` before it was saved, so the moves go from the end, never overwriting a value not yet moved. Deletion, in contrast, must fill the removed slot with the following values, so it moves from the front. The third call has `pos` 9, greater than `n`, so it changes nothing. Inserting or removing one element may require moving up to n elements, so data with frequent insertions and deletions in the middle uses other data structures, such as the linked list of Chapter 11.

### 5.11 Matrix Addition and Transposition

Matrix addition adds elements at the same positions, and **transposition** swaps rows and columns, producing `t[j][i] = x[i][j]`. Both operations are written as functions that take two-dimensional arrays as parameters.

```c
#define N 3

void add_matrix(int x[][N], int y[][N], int z[][N])
{
    int i, j;

    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
            z[i][j] = x[i][j] + y[i][j];
}

void transpose(int x[][N], int t[][N])
{
    int i, j;

    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
            t[j][i] = x[i][j];
}

void print_matrix(int m[][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++)
            printf("%4d", m[i][j]);
        printf("\n");
    }
}

int main(void)
{
    int x[N][N] = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
    int y[N][N] = { { 10, 20, 30 }, { 40, 50, 60 }, { 70, 80, 90 } };
    int z[N][N], t[N][N];

    add_matrix(x, y, z);
    print_matrix(z);
    transpose(x, t);
    print_matrix(t);
    return 0;
}
```

```text
  11  22  33
  44  55  66
  77  88  99
   1   4   7
   2   5   8
   3   6   9
```

The arrays `z` and `t` that receive the results are also passed as parameters, and since the starting addresses of the arrays are passed, the functions fill the arrays of `main`. In the transpose, the 2 of `x[0][1]` goes to `t[1][0]` and the 4 of `x[1][0]` to `t[0][1]`, so row 0 of the result is the original column 0: 1, 4, 7. The diagonal elements `x[i][i]` stay in place. Writing the transpose back into `x` itself would overwrite elements not yet read, so the result is stored in a separate array.

---

<br>

## Concept Applications

**True/False Check:**

| Statement | Judgment and Reason |
|:-----|:-----|
| In `int a[5] = {1, 2};`, `a[4]` holds a garbage value. | **F.** When initial values run short, the remaining elements are initialized to 0, so `a[4]` is 0. |
| For `int a[] = {1, 2, 3};`, `sizeof(a) / sizeof(a[0])` is 3. | **T.** With the size omitted, the number of initial values sets the size, and dividing the total size by the size of one element gives the element count. |
| If an index falls outside the array, the compiler always reports an error. | **F.** C does not check bounds at run time, and out-of-range access is undefined behavior. A warning may appear only for constant indices. |
| Two arrays of the same size can be copied with `b = a;`. | **F.** An array name cannot be assigned, so the elements are copied one by one with a loop. |
| A two-dimensional array is stored in contiguous memory in row-major order. | **T.** All elements of row 0 are placed first, followed by those of row 1. |
| `int m[][3] = {1, 2, 3, 4};` creates an array of 2 rows and 3 columns. | **T.** Filling 4 values 3 per row needs 2 rows, and `m[1][1]` and `m[1][2]` become 0. |
| When an array is passed to a function, its elements are copied, so changes inside the function do not affect the original array. | **F.** The starting address of the array is passed, so the function changes the elements of the original array. |
| Selection sort swaps the minimum of the unsorted part with the first position of that part in each pass. | **T.** n elements are sorted in ascending order in n - 1 passes. |

---

<br>

## Summary

| Concept | Key Summary |
|:-----|:-----|
| The need for arrays | An array replaces many variables of the same type with one name so that they can be processed with loops. |
| Array concepts | An array stores elements of the same type in contiguous memory and accesses them by a zero-based index, and each element is a variable. |
| Declaration | The size in `type name[SIZE];` must be an integer constant greater than 0; a `#define` constant can be used, but a `const` variable is not a constant expression. |
| `sizeof` | `sizeof(arr) / sizeof(arr[0])` is the element count of the array. |
| `#define` for size | Fixing the size with a macro constant lets you change it in one place and avoids magic numbers. |
| Initializer list | Missing initial values leave the remaining elements at 0, `{0}` sets all elements to 0, and empty `{}` became standard in C23. |
| Omitting size | With an initializer list, as in `int z[] = {-1, 0, 1};`, the size can be omitted, and the number of initial values becomes the size. |
| Without init | An uninitialized local array contains garbage values, so it must be initialized before use. |
| Element access | Elements are read and written with `arr[i]`, and any integer expression can be used as the index. |
| Array with loops | Processing an array with a `for` loop is the standard pattern, and `&arr[i]` is passed to `scanf`. |
| Out of bounds | Valid indices run from `0` to `SIZE-1`, and since C does not check bounds, writing outside the range can corrupt memory. |
| Copying and comparing arrays | Arrays cannot be copied or compared at once with assignment or `==`, so their elements are handled one by one. |
| 2D array | `int m[ROWS][COLS];` is a table of rows and columns stored in row-major order in memory. |
| 2D access | An element of a 2D array is accessed with `m[i][j]`, and the array is traversed with nested loops. |
| 2D initialization | A 2D array is initialized with `{{1,2},{3,4}}` or flat `{1,2,3,4}`; missing elements become 0, and only the row size can be omitted. |
| Max / Min | Initialize with `arr[0]` and compare from index 1. |
| Average / Std Dev | The average is computed by dividing after converting to `double`, and the standard deviation is obtained by applying `sqrt()` from `<math.h>` to the variance. |
| Reverse array | Elements are swapped from both ends toward the center, and the swap happens `SIZE / 2` times. |
| UPC check digit | An array and a loop replace 11 variables to compute the check digit by the formula. |
| Sequential search | The elements are compared with the key in turn from element 0, and in the worst case all elements are compared, which is $O(n)$. |
| Selection sort | The minimum of the unsorted portion is repeatedly found and moved to the front, and the time complexity is $O(n^2)$. |
| Frequency counting | Counting uses the array index as the category, as in `freq[value]++`. |
| Random numbers | After calling `srand((unsigned)time(NULL))` once, `rand() % range + min` produces a random number in the desired range. |
| Computing from earlier elements | A loop that uses earlier elements, as in `fib[i] = fib[i - 1] + fib[i - 2]`, starts where the index expressions become 0 or more. |
| Row and column totals | Row sums use one variable reset in each outer iteration, and column sums accumulate in an array with a slot for each column. |
| Finding all positions | Keep comparing to the end after a match, printing positions or counting, and a function that finds the first position returns -1 when absent. |
| Array parameters | They take `int arr[]` together with the element count; since the starting address is passed, the function can change the original array, which `const` prevents. |
| 2D array parameters | The column size cannot be omitted, so they are declared as `int m[][COLS]`. |
| Element addresses | The address of `a[i]` is the starting address plus i × the element size, and neighboring addresses differ by the element size. |
| Position in a 2D array | With C columns, `m[i][j]` is element number i × C + j, so a function must know the number of columns. |
| Inserting and deleting | Insertion moves elements one slot from the end, and deletion from the front. |
| Matrix addition and transposition | Addition adds elements at the same positions, and the transpose `t[j][i] = x[i][j]` is built in a separate array. |
| Binary search | In a sorted array, it compares with the middle element and halves the range, taking about log₂ n comparisons. |

---

<br>

## Self-Check Questions

1. **`sizeof`:** In an environment where `double` is 8 bytes, what are `sizeof(d)`, `sizeof(d[0])`, and `sizeof(d) / sizeof(d[0])` for `double d[6];`?

   <details>
   <summary>Answer</summary>

   `sizeof(d)` is 6 × 8 = 48, `sizeof(d[0])` is 8, and `sizeof(d) / sizeof(d[0])` is 48 / 8 = 6. The last expression always gives the element count even if the element type changes.

   </details>

2. **2D array initialization:** For `int m[3][2] = {1, 2, 3};`, what are the values of `m[0][1]`, `m[1][0]`, `m[1][1]`, and `m[2][1]`?

   <details>
   <summary>Answer</summary>

   Values listed flat are assigned in row-major order to `m[0][0]`, `m[0][1]`, and `m[1][0]`, so `m[0][1]` is 2 and `m[1][0]` is 3. The remaining elements without initial values are filled with 0, so `m[1][1]` and `m[2][1]` are 0.

   </details>

3. **Out of bounds:** What is wrong with `int arr[5]; for (int i = 0; i <= 5; i++) arr[i] = 0;`?

   <details>
   <summary>Answer</summary>

   The valid indices are 0-4, but the loop condition is `i <= 5`, so the last iteration writes to `arr[5]`. This is undefined behavior that overwrites the memory after the array, and another variable may change or the program may terminate abnormally. Because the index is a variable, the compiler usually does not warn. The condition must be changed to `i < 5`.

   </details>

4. **Selection sort trace:** When the array `{29, 10, 14, 37, 13}` is sorted with the ascending selection sort of Section 5.6, write the array after each pass.

   <details>
   <summary>Answer</summary>

   Pass 0 swaps the minimum 10 (index 1) with `arr[0]`, giving `{10, 29, 14, 37, 13}`. Pass 1 swaps the minimum of the rest, 13 (index 4), with `arr[1]`, giving `{10, 13, 14, 37, 29}`. In pass 2 the minimum 14 is already at index 2, so nothing changes. Pass 3 swaps 29 (index 4) with `arr[3]`, giving `{10, 13, 14, 29, 37}`.

   </details>

5. **Comparing arrays:** For `int x[3] = {1, 2, 3}, y[3] = {1, 2, 3};`, is the condition of `if (x == y)` true?

   <details>
   <summary>Answer</summary>

   It is false. An array name written without an index means the starting address of the array, so `x == y` compares the starting addresses of two different arrays rather than their contents, and the two addresses can never be equal. To check whether the contents are equal, compare the elements one by one as in Section 3.4.

   </details>

6. **Array parameters:** Write the elements of `a` after running the following code, and explain why `n` does not change while `a` does.

   ```c
   void f(int x, int arr[]) { x = 0; arr[0] = 0; }
   int n = 5, a[3] = { 5, 6, 7 };
   f(n, a);
   ```

   <details>
   <summary>Answer</summary>

   `a` becomes `{0, 6, 7}`, and `n` stays 5. `x` is a local variable holding a copy of the value of `n`, so `x = 0` does not affect `n`. In contrast, `arr` receives the starting address of the array `a`, so `arr[0] = 0` changes the first element of the original array.

   </details>

7. **Column totals:** For `int m[2][3] = { {1, 2, 3}, {4, 5, 6} };`, write the sum of each column and the sum of each row.

   <details>
   <summary>Answer</summary>

   The column sums are 1 + 4 = 5, 2 + 5 = 7, and 3 + 6 = 9, and the row sums are 1 + 2 + 3 = 6 and 4 + 5 + 6 = 15. Both kinds of sums add up to the same total of 21.

   </details>

8. **Starting index of a loop:** For `int d[6] = { 2, 5, 9, 14, 20, 27 };`, write a loop that prints every difference `d[i] - d[i - 1]` between neighboring elements, and give the output.

   <details>
   <summary>Answer</summary>

   `for (i = 1; i < 6; i++) printf("%d ", d[i] - d[i - 1]);`. Since `i - 1` must be 0 or more, the loop starts at 1, and the output is `3 4 5 6 7`. Starting at 0 would read `d[-1]`, an out-of-range access.

   </details>
