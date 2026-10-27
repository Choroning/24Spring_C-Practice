# Chapter 8 Lab — Pointer Basics and Pointer Arithmetic

[Repository Guide](../../README.md) | [English](Concepts_Lab.md) | [한국어](Concepts_Lab.ko.md)

> **Last Updated:** 2026-10-27
>
> 문제풀이 중심의 C언어 연습, 김용일과 강문설, Ch 9

> **Learning Objectives:**
> 1. Explain with memory addresses why a variable cannot be changed through another variable that copies it
> 2. Print the address of a variable with `%p` and explain why the printed address differs by build setting and from run to run
> 3. Declare and initialize a pointer, and read and change the value of the variable it points to with the dereference operator
> 4. Explain that adding an integer to a pointer changes the address by the size of the pointed-to type, and access array elements through a pointer
> 5. Explain why a swap function written with call by value fails

---

## Table of Contents

- [1. Copying Variables and Memory Addresses](#1-copying-variables-and-memory-addresses)
  - [1.1 Can a Be Changed Through b](#11-can-a-be-changed-through-b)
  - [1.2 Printing Memory Addresses](#12-printing-memory-addresses)
- [2. Pointers](#2-pointers)
  - [2.1 A Variable That Stores an Address](#21-a-variable-that-stores-an-address)
  - [2.2 Changing a Value by Dereferencing](#22-changing-a-value-by-dereferencing)
  - [2.3 Pointer Types and Sizes](#23-pointer-types-and-sizes)
- [3. Pointer Arithmetic and Arrays](#3-pointer-arithmetic-and-arrays)
  - [3.1 Adding an Integer to a Pointer](#31-adding-an-integer-to-a-pointer)
  - [3.2 Pointers and Arrays](#32-pointers-and-arrays)
- [4. Pointer Practice](#4-pointer-practice)
  - [4.1 Predicting the Results of Pointer Expressions](#41-predicting-the-results-of-pointer-expressions)
  - [4.2 Swapping Two Variables in main](#42-swapping-two-variables-in-main)
  - [4.3 Swapping Two Variables with a Function](#43-swapping-two-variables-with-a-function)
- [Summary](#summary)
- [Self-Check Questions](#self-check-questions)

---

<br>

## 1. Copying Variables and Memory Addresses

### 1.1 Can a Be Changed Through b

With `int a = 3;` declared, consider whether the value of `a` can be changed to 5 using another variable `b`. The following code, which creates `b` with `int b = a;` and then executes `b = 5;`, does not change `a`. The code is [Example_VariableCopy.c](Example_VariableCopy.c).

```c
#include <stdio.h>

int main()
{
    int a = 3;
    int b = a;

    printf("[1] %d, %d \n", a, b); // expected: 3, 3
    printf("[1-1] %p, %p \n", &a, &b);

    // Can the value of a be changed through variable b?
    b = 5;

    printf("[2] %d, %d \n", a, b); // expected: 3, 5
}
```

```text
[1] 3, 3 
[1-1] 0x16ce8abbc, 0x16ce8abb8 
[2] 3, 5 
```

`int b = a;` only copies the value 3 stored in `a` into the memory of `b`, and `a` and `b` are different variables at different addresses. The two different addresses in the `[1-1]` line show this. So `b = 5;` changes only the memory of `b`, and `a` stays 3.

```text
 After b = 5;
   a                   b
┌───────┐           ┌───────┐
│   3   │           │   5   │
└───────┘           └───────┘
 0x16ce8abbc         0x16ce8abb8
```

*Figure 1. Variables a and b at different addresses*

### 1.2 Printing Memory Addresses

The address of a variable is obtained with the address operator `&` and printed with `%p`, the format specifier dedicated to addresses. As in the output above, `%p` in a 64-bit program on macOS prints a hexadecimal number starting with `0x`. The output format is up to the implementation; Visual Studio prints uppercase hexadecimal padded to a fixed number of digits without `0x`, as in `00D5FAEC`.

An address can also be printed with the hexadecimal integer format specifiers `%x` or `%#x`, but `%x` expects an `unsigned int`, so passing an address makes the format and argument types mismatch. In a 64-bit build only the lower 4 of the 8 address bytes may be printed, and compiling with `-Wall` gives the warning "format specifies type 'unsigned int' but the argument has type 'int \*'". The following is the output with `%#x` on the same computer, where only the lower 4 bytes (8 hexadecimal digits) of the address are printed. Printing the same address with both format specifiers in one run turns `0x16fd56be8` of `%p` into `0x6fd56be8` with `%#x`.

```text
[1] 3, 3 
[1-1] 0x6f55ebf8, 0x6f55ebf4 
[2] 3, 5 
```

> **Note:** **Length and value of printed addresses.** The size of an address is set by the target platform of the build. In a 32-bit (x86) build an address is 4 bytes, printed as 8 hexadecimal digits such as `00D5FAEC`, and in a 64-bit (x64, ARM64) build it is 8 bytes, printed as a longer value. The textbook explains addresses on a 32-bit basis, so switching Visual Studio's platform to x86 shows addresses of the same length as the textbook. Also, today's operating systems randomize the location of the stack on each run for security (ASLR, Address Space Layout Randomization), so the same program prints different addresses on each run. The addresses in this note come from one run, and only the differences between addresses (4 bytes, 8 bytes, and so on) are meaningful.

> **[Operating Systems]** The addresses a program prints belong to the virtual address space that the operating system gives each process, and the operating system maps these virtual addresses to physical addresses in memory. ASLR, which changes the addresses on every run, is one of the operating system's memory management and protection techniques; virtual memory is covered in Operating Systems.

---

<br>

## 2. Pointers

### 2.1 A Variable That Stores an Address

A **pointer**, or pointer variable, is a special variable that stores the memory address of another variable ([Chapter 8, Section 1.1](Concepts_Lecture.md#11-pointer-concept)). `int *p = &a;` declares a pointer `p` to `int` and initializes it with the address of `a`. Then `p` is said to **point to** `a` ([Chapter 8, Section 1.2](Concepts_Lecture.md#12-pointer-declaration)).

`*p`, the pointer `p` with the **dereference operator** `*` in front, means the memory at the address stored in `p`, that is, the variable `p` points to. Reading `*p` gives that variable's value, and assigning to `*p` changes that variable's value ([Chapter 8, Section 1.4](Concepts_Lecture.md#14-dereference-operator-)). The code is [Example_Dereference.c](Example_Dereference.c).

```c
#include <stdio.h>

int main()
{
    int a = 3;
    int* p = &a;

    printf("[1] a: %d \n", a);
    printf("[2] &a: %p \n", &a);

    printf("[3] p: %p \n", p);
    printf("[4] &p: %p \n", &p);

    // use the data at the place pointer p refers to: dereference
    printf("[5] *p: %d \n", *p);

    // *p is interpreted as the memory area that pointer p refers to,
    // that is, 5 is assigned to the memory area p refers to!
    *p = 5;
    printf("[6] a: %d \n", a);
    printf("[7] *p: %d \n", *p);
}
```

```text
[1] a: 3 
[2] &a: 0x16d732bbc 
[3] p: 0x16d732bbc 
[4] &p: 0x16d732bb0 
[5] *p: 3 
[6] a: 5 
[7] *p: 5 
```

- **`[2]` and `[3]`:** The value stored in `p` equals the address of `a`, `&a`.
- **`[4]`:** A pointer is also a variable, so it has its own address `&p`, which differs from the address of `a`.
- **`[5]`:** `*p` is the data at the place `p` points to, that is, the value 3 of `a`.
- **`[6]` and `[7]`:** `*p = 5;` assigns 5 to the memory area `p` points to, so `a` changes to 5. The value of `a`, which could not be changed through `b` in Section 1.1, can be changed through a pointer.

```text
   p (0x16d732bb0)             a (0x16d732bbc)
┌──────────────┐            ┌───────┐
│ 0x16d732bbc  │ ─────────▶ │ 3 → 5 │
└──────────────┘            └───────┘
                              *p
```

*Figure 2. Pointer p pointing to a, and its dereference*

### 2.2 Changing a Value by Dereferencing

A statement with `*p` on both sides of the assignment operator, such as `*p = 2 + *p;`, is interpreted as follows. The code is [Example_DereferenceUpdate.c](Example_DereferenceUpdate.c).

- **Left of the assignment operator:** `*p` is interpreted as the **memory area** `p` points to.
- **Right of the assignment operator:** `2 + *p` is the sum of the integer 2 and the **data** in the memory `p` points to, the value 3 of `a`, which is 5.
- So the statement equals `*p = 5;`, and 5 is assigned to the memory area `p` points to (`a`).

```c
#include <stdio.h>

int main()
{
    int a = 3;
    int* p = &a;

    printf("1. a: %d, &a: %p \n", a, &a);
    printf("2. p: %p, &p: %p \n", p, &p);
    printf("3. *p: %d \n", *p);

    *p = 2 + *p;
    printf("4. a: %d, &a: %p \n", a, &a);
    printf("5. p: %p, &p: %p \n", p, &p);
    printf("6. *p: %d \n", *p);
}
```

```text
1. a: 3, &a: 0x16b15abac 
2. p: 0x16b15abac, &p: 0x16b15aba0 
3. *p: 3 
4. a: 5, &a: 0x16b15abac 
5. p: 0x16b15abac, &p: 0x16b15aba0 
6. *p: 5 
```

The value of `a` changes from 3 to 5, but the address of `a`, the address stored in `p`, and the address of `p` itself all stay the same. Dereferencing changes only the value of the variable pointed to.

### 2.3 Pointer Types and Sizes

A pointer is declared to match the type of the variable it points to, as in `char *pc = &ch;`, `int *pi = &di;`, and `double *pd = &db;`; the pointer's type decides how many bytes, and in what format, memory is read when it is dereferenced. In contrast, the size of the pointer variable itself is the same regardless of the pointed-to type, because a pointer is a variable that stores an address. It is 4 bytes in a 32-bit environment and 8 bytes in a 64-bit environment ([Chapter 8, Section 1.2](Concepts_Lecture.md#12-pointer-declaration)).

```c
#include <stdio.h>

int main(void)
{
    char ch = 'a';
    int di = 3;
    double db = 3.2;

    char *pc = &ch;
    int *pi = &di;
    double *pd = &db;

    printf("pointer sizes: %zu, %zu, %zu\n", sizeof(pc), sizeof(pi), sizeof(pd));
    printf("pointee sizes: %zu, %zu, %zu\n", sizeof(*pc), sizeof(*pi), sizeof(*pd));

    return 0;
}
```

```text
pointer sizes: 8, 8, 8
pointee sizes: 1, 4, 8
```

This was run on 64-bit macOS, so all three pointers are 8 bytes. The sizes of the pointed-to objects differ: `char` 1, `int` 4, and `double` 8 bytes.

---

<br>

## 3. Pointer Arithmetic and Arrays

### 3.1 Adding an Integer to a Pointer

Adding 1 to a pointer increases the address not by 1 byte but by the size of the pointed-to type. That is, the address of `p + n` is the address of `p` + n × `sizeof(*p)` ([Chapter 8, Section 2.1](Concepts_Lecture.md#21-pointer-arithmetic)). The code is [Example_PointerArithmetic.c](Example_PointerArithmetic.c).

```c
#include <stdio.h>

int main()
{
    char ch = 'a';
    int di = 3;
    double db = 3.2;

    char* pc = &ch;
    int* pi = &di;
    double* pd = &db;

    printf("1. %p, %p, %p \n", pc, pi, pd);
    printf("2. %p, %p, %p \n", pc + 1, pi + 1, pd + 1);
}
```

```text
1. 0x16db32baf, 0x16db32ba8, 0x16db32ba0 
2. 0x16db32bb0, 0x16db32bac, 0x16db32ba8 
```

| Pointer | `p` | `p + 1` | Increase |
|:-----|:-----|:-----|-----:|
| `char *pc` | `...baf` | `...bb0` | 1 |
| `int *pi` | `...ba8` | `...bac` | 4 |
| `double *pd` | `...ba0` | `...ba8` | 8 |

*Table 1. Increase of the address when 1 is added to a pointer*

> **Caution:** `pc + 1`, `pi + 1`, and `pd + 1` add 1 to pointers that do not point to array elements. The C standard treats a non-array variable as an array of one element and allows computing the address just past it, but dereferencing that address is undefined behavior. Pointer arithmetic is used within arrays, as in Section 3.2.

### 3.2 Pointers and Arrays

An array name is converted to the address of its first element in expressions, so `int *p = arr;` equals `int *p = &arr[0];`. Then `p + i` is the address of `arr[i]`, `*(p + i)` is the value of `arr[i]`, and `p[i]`, a subscript on a pointer, also equals `*(p + i)` ([Chapter 8, Section 2.2](Concepts_Lecture.md#22-pointer-as-array), [Section 2.3](Concepts_Lecture.md#23-array-as-pointer)). The code is [Example_ArrayPointer.c](Example_ArrayPointer.c).

```c
#include <stdio.h>
#define MAX 5

int main()
{
    int i, arr[MAX] = { 1,3,5,7,9 };
    int* p = arr;

    printf("arr: %p \n", arr);

    for (i = 0; i < MAX; i++)
    {
        printf("[%d, %d, %d], ", arr[i], *(p + i), p[i]);
        printf("[%p, %p] \n", &arr[i], (p + i));
    }
    printf("====================\n");

    for (i = 0; i < MAX; i++)
    {
        printf("[%d, %d], ", *(arr + i), *p);
        p++;
        printf("[%p, %p] \n", &arr[i], p);
    }
}
```

```text
arr: 0x16bc1ab90 
[1, 1, 1], [0x16bc1ab90, 0x16bc1ab90] 
[3, 3, 3], [0x16bc1ab94, 0x16bc1ab94] 
[5, 5, 5], [0x16bc1ab98, 0x16bc1ab98] 
[7, 7, 7], [0x16bc1ab9c, 0x16bc1ab9c] 
[9, 9, 9], [0x16bc1aba0, 0x16bc1aba0] 
====================
[1, 1], [0x16bc1ab90, 0x16bc1ab94] 
[3, 3], [0x16bc1ab94, 0x16bc1ab98] 
[5, 5], [0x16bc1ab98, 0x16bc1ab9c] 
[7, 7], [0x16bc1ab9c, 0x16bc1aba0] 
[9, 9], [0x16bc1aba0, 0x16bc1aba4] 
```

- **First loop:** `arr[i]`, `*(p + i)`, and `p[i]` give the same value, and `&arr[i]` and `p + i` give the same address. `p` does not change, and the addresses of the elements increase by 4 bytes.
- **Second loop:** `*(arr + i)` dereferences the address of the array name plus an integer and gives the same value as `arr[i]`. `p++` moves the address stored in `p` itself to the next element, so right after `*p` is read, `p` points one element (4 bytes) past `&arr[i]`. The `p` of the last line is the position just past the end of the array; this address may be used in comparisons but must not be dereferenced.

```text
            arr[0]   arr[1]   arr[2]   arr[3]   arr[4]
          ┌────────┬────────┬────────┬────────┬────────┐
 arr      │   1    │   3    │   5    │   7    │   9    │
          └────────┴────────┴────────┴────────┴────────┘
           ...b90   ...b94   ...b98   ...b9c   ...ba0
             ▲
 p ──────────┘   p + 1 → ...b94,  p + 2 → ...b98, ...
```

*Figure 3. Pointer p pointing to the first element of the array arr*

> **Note:** The array name `arr` and the pointer `p` access elements in the same way, but `arr` is not a variable, so its value cannot be changed, as in `arr++`. `p`, on the other hand, is a variable, so `p++` makes it point to another element ([Chapter 8, Section 2.4](Concepts_Lecture.md#24-array-vs-pointer-comparison)).

---

<br>

## 4. Pointer Practice

The solution code of the following problems is the example files in this unit folder. Each file compiles with `gcc -std=c99 -Wall` without warnings, and the outputs are from actual runs.

### 4.1 Predicting the Results of Pointer Expressions

**Problem:** With the size-6 integer array `arr` initialized to `{ 1, -3, 5, -6, 12, 4 }` and `int *p = arr;`, predict the five lines of output.

**Solution:** The dereference operator `*` is a unary operator, so it binds before the binary operator `+`. This precedence makes the difference between `*p + 1` and `*(p + 1)` ([Chapter 4 Lab, Section 6](../Ch04_Operators/Concepts_Lab.md#6-operator-precedence-and-associativity)).

| Expression | Interpretation | Value |
|:-----|:-----|:---:|
| `p[2]` | `*(p + 2)`, that is, `arr[2]` | 5 |
| `*p + 1` | `(*p) + 1`, that is, `arr[0] + 1` | 2 |
| `*(p + 1)` | `arr[1]` | -3 |
| `*(p + 3)` | `arr[3]` | -6 |
| `arr[0]` after `*p = arr[2] - *p;` | 5 - 1 = 4 is assigned to `arr[0]` | 4 |

*Table 2. Interpretation and value of pointer expressions*

**Code:** [Example_PointerExpressions.c](Example_PointerExpressions.c)

```c
#include <stdio.h>

int main()
{
    int arr[6] = { 1,-3,5,-6,12,4 };
    int* p = arr;

    printf("1. %d \n", p[2]);       // result: 1. 5
    printf("2. %d \n", *p + 1);     // result: 2. 2
    printf("3. %d \n", *(p + 1));   // result: 3. -3
    printf("4. %d \n", *(p + 3));   // result: 4. -6

    *p = arr[2] - *p;
    printf("5. %d \n", arr[0]);     // result: 5. 4
}
```

```text
1. 5 
2. 2 
3. -3 
4. -6 
5. 4 
```

### 4.2 Swapping Two Variables in main

**Problem:** `int a = 3, b = 5;` is declared in `main`. Adding variables if needed, swap the values of `a` and `b` inside `main`.

**Solution:** Assigning directly, as in `a = b; b = a;`, loses the original value 3 of `a` in the first assignment, and both variables become 5. So the value of `a` is first kept in the temporary variable `temp`, then `b` is assigned to `a` and `temp` to `b`.

**Code:** [Example_SwapInline.c](Example_SwapInline.c)

```c
#include <stdio.h>

int main()
{
    int a = 3, b = 5, temp;
    printf("1. a, b: %d, %d \n", a, b);

    temp = a;
    a = b;
    b = temp;

    printf("2. a, b: %d, %d \n", a, b);
}
```

```text
1. a, b: 3, 5 
2. a, b: 5, 3 
```

### 4.3 Swapping Two Variables with a Function

**Problem:** Writing the swapping part of Section 4.2 as the function `void swap(int x, int y)` leaves `a` and `b` of `main` unchanged. Run it and analyze what the problem is.

**Solution:** Calling `swap(a, b)` copies the values 3 and 5 of `a` and `b` into the parameters `x` and `y`. `swap` swaps only its own local variables `x` and `y`, and when the function ends, `x`, `y`, and `temp` disappear. So `a` and `b` of `main` do not change ([Chapter 8, Section 3.1](Concepts_Lecture.md#31-pass-by-value-vs-pass-by-reference)). A C function can return only one result, so it cannot return the two changed values either. That is why the return type is `void`.

**Code:** [Example_SwapByValue.c](Example_SwapByValue.c)

```c
#include <stdio.h>      // Extra problem 1: rewrite the swap with a function
void swap(int x, int y)
{
    int temp;
    temp = x;
    x = y;
    y = temp;
}

int main()
{
    int a = 3, b = 5;
    printf("1. a, b: %d, %d \n", a, b);

    swap(a, b);

    printf("2. a, b: %d, %d \n", a, b);
}
```

```text
1. a, b: 3, 5 
2. a, b: 3, 5 
```

```text
   main                     swap (during the call)
┌──────────┐             ┌──────────┐
│ a = 3    │ ──copy───▶  │ x = 3→5  │
│ b = 5    │ ──copy───▶  │ y = 5→3  │
└──────────┘             │ temp = 3 │
 unchanged                └──────────┘
                          freed on return
```

*Figure 4. In call by value, swap changes only the copies*

There is also a way to swap using a single return value. `exchange()` of [Example_SwapReturn.c](Example_SwapReturn.c) returns the value of `y`, that is, the original value of `b`, and `main` recovers the other value by subtracting it from the sum of the two values computed beforehand.

```c
#include <stdio.h>      // Extra problem 1: rewrite the swap with a function
int exchange(int x, int y)
{
    int temp;
    temp = x;
    x = y;
    y = temp;

    return x;
}

int main()
{
    int a = 3, b = 5, temp;
    printf("1. a, b: %d, %d \n", a, b);

    temp = a + b;
    a = exchange(a, b);
    b = temp - a;

    printf("2. a, b: %d, %d \n", a, b);
}
```

```text
1. a, b: 3, 5 
2. a, b: 5, 3 
```

> **Note:** This method reassigns `a` and `b` in `main`, so the function does not change the caller's variables directly. Also, if `a + b` exceeds the range of `int`, overflow occurs. To change the caller's variables directly, the function must receive the addresses of the variables as parameters, as in `void swap(int *x, int *y)`, and swap `*x` and `*y`; this solution is in [HW08 Problem 1](../../Coursework/HW08_Pointers-I/Assignment-Explanation.md#1-swapping) ([Chapter 8, Section 3.2](Concepts_Lecture.md#32-modifying-a-variable-through-a-pointer)).

---

<br>

## Summary

| Concept | Key Summary |
|:-----|:-----|
| Copying variables | `int b = a;` copies only the value, so changing `b` does not change `a`, which is at a different address. |
| Printing addresses | An address is obtained with `&` and printed with `%p`; its length depends on the bitness of the build, and its value changes from run to run. |
| Pointer | A variable that stores the address of another variable, declared and initialized as in `int *p = &a;`. |
| Dereference | `*p` is the variable `p` points to; reading it gives the value, and assigning to it changes that variable. |
| Pointer size | Regardless of the pointed-to type, 4 bytes in a 32-bit environment and 8 bytes in a 64-bit environment. |
| Pointer arithmetic | `p + n` is the address of `p` plus n × `sizeof(*p)`. |
| Pointers and arrays | With `int *p = arr;`, `p[i]`, `*(p + i)`, `arr[i]`, and `*(arr + i)` are all the same element. |
| Call by value and swap | A parameter is a copy, so `swap(int x, int y)` cannot change the caller's variables. |

---

<br>

## Self-Check Questions

1. **Dereference:** Write the value of `x` after executing `int x = 10; int *q = &x; *q = *q * 3;`.

   <details>
   <summary>Answer</summary>

   The `*q` on the right is the value 10 of `x`, and the `*q` on the left is the memory area of `x`, so 30 is assigned to `x`.

   </details>

2. **Pointer arithmetic:** In `double d[4];`, if `&d[0]` is `0x1000`, what is the address of `&d[0] + 3`?

   <details>
   <summary>Answer</summary>

   A `double` is 8 bytes, so it is 0x1000 + 3 × 8 = 0x1018. This address equals `&d[3]`.

   </details>

3. **Precedence:** With `int a[3] = {10, 20, 30}; int *p = a;`, what are the values of `*p + 2` and `*(p + 2)`?

   <details>
   <summary>Answer</summary>

   `*` binds before `+`, so `*p + 2` is `a[0] + 2`, that is, 12. `*(p + 2)` is `a[2]`, that is, 30.

   </details>

4. **Pointer size:** In a 64-bit build, what are the `sizeof` values of `char *c;` and `double *d;`, and why?

   <details>
   <summary>Answer</summary>

   Both are 8. A pointer is a variable that stores an address, and in a 64-bit environment an address is 8 bytes regardless of the pointed-to type.

   </details>

5. **swap:** If `printf("%d %d\n", x, y);` is added at the very end of `swap(int x, int y)` in Section 4.3, what is printed? Why does this differ from the result in `main`?

   <details>
   <summary>Answer</summary>

   `5 3` is printed. Inside `swap` the copies `x` and `y` were swapped, but they are local variables in memory different from `a` and `b` of `main`, so back in `main`, `a` and `b` are still 3 and 5.

   </details>
