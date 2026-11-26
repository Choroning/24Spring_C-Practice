# Chapter 8 — Pointers

[Repository Guide](../../README.md) | [English](Concepts_Lecture.md) | [한국어](Concepts_Lecture.ko.md)

> **Last Updated:** 2026-11-27
>
> Warming-Up C Programming, 천정아, Ch 8

> **Learning Objectives:**
> 1. Declare pointers and access variables indirectly with the address-of and dereference operators
> 2. Explain the differences among the three `const` pointers determined by the position of `const`
> 3. Compute how far pointer arithmetic moves and convert between array notation and pointer notation
> 4. Explain the difference between an array name and a pointer variable in terms of `sizeof` and assignability
> 5. Use pointer parameters to modify the caller's variables or return multiple values
> 6. Explain why the size must be passed separately when an array is passed to a function

---

## Table of Contents

- [1. Pointer Basics](#1-pointer-basics)
  - [1.1 Pointer Concept](#11-pointer-concept)
  - [1.2 Pointer Declaration](#12-pointer-declaration)
  - [1.3 Pointer Initialization](#13-pointer-initialization)
  - [1.4 Dereference Operator `*`](#14-dereference-operator-)
  - [1.5 Pointer Usage](#15-pointer-usage)
  - [1.6 `const` Pointer](#16-const-pointer)
  - [1.7 Precautions When Using Pointers](#17-precautions-when-using-pointers)
  - [1.8 Step-by-Step Trace of Pointer Expressions](#18-step-by-step-trace-of-pointer-expressions)
  - [1.9 Memory Picture of a Pointer Variable](#19-memory-picture-of-a-pointer-variable)
- [2. Arrays and Pointers](#2-arrays-and-pointers)
  - [2.1 Pointer Arithmetic](#21-pointer-arithmetic)
  - [2.2 Pointer as Array](#22-pointer-as-array)
  - [2.3 Array as Pointer](#23-array-as-pointer)
  - [2.4 Array vs Pointer Comparison](#24-array-vs-pointer-comparison)
  - [2.5 Arrays of Pointers and Double Pointers](#25-arrays-of-pointers-and-double-pointers)
  - [2.6 Differences Among `arr`, `&arr[0]`, and `&arr`](#26-differences-among-arr-arr0-and-arr)
  - [2.7 Pointer Arithmetic by Element Type](#27-pointer-arithmetic-by-element-type)
  - [2.8 Various Pointer Declarations](#28-various-pointer-declarations)
  - [2.9 Traversing an Array with a Pointer](#29-traversing-an-array-with-a-pointer)
- [3. Functions and Pointers](#3-functions-and-pointers)
  - [3.1 Pass by Value vs Pass by Reference](#31-pass-by-value-vs-pass-by-reference)
  - [3.2 Modifying a Variable Through a Pointer](#32-modifying-a-variable-through-a-pointer)
  - [3.3 Returning Multiple Values](#33-returning-multiple-values)
  - [3.4 Passing Arrays to Functions](#34-passing-arrays-to-functions)
  - [3.5 Functions That Return Addresses](#35-functions-that-return-addresses)
  - [3.6 Memory Trace of a `swap` Call](#36-memory-trace-of-a-swap-call)
  - [3.7 Common Mistakes with Pointers](#37-common-mistakes-with-pointers)
- [Concept Applications](#concept-applications)
- [Summary](#summary)
- [Self-Check Questions](#self-check-questions)

---

<br>

## 1. Pointer Basics

### 1.1 Pointer Concept

Memory is a sequence of **contiguous bytes**, each with a unique **address**. A **pointer** is an address, and a **pointer variable** is a variable that stores an address. The range of values a memory address can take is called the **address space**.

```text
Memory Layout (simplified)
Address        Value
┌──────────┬──────────┐
│  0x1000  │    10    │  ← int a = 10;
├──────────┼──────────┤
│  0x1004  │    20    │  ← int b = 20;
├──────────┼──────────┤
│  0x1008  │  0x1000  │  ← int *p = &a;  (p stores a's address)
└──────────┴──────────┘
```

*Figure 1. Memory layout of variables a and b and pointer p pointing to a*

| Architecture | Pointer Size | Address Range |
|:-------------|:-------------|:--------------|
| 32-bit | 4 bytes | `0x00000000`-`0xFFFFFFFF` |
| 64-bit | 8 bytes | `0x0000000000000000`-`0xFFFFFFFFFFFFFFFF` |

*Table 1. Pointer size and address range by architecture*

> **Key Point:** A pointer provides access to a variable via its address, even without knowing the variable's name. This is what makes pointers powerful.

### 1.2 Pointer Declaration

**Syntax:**

```c
type *pointer_name;
```

The `type` specifies what type of variable the pointer will point to. The `*` is the pointer modifier indicating that the variable is a pointer. The type of the pointed-to variable determines the type of the pointer; for example, a pointer to an `int` variable has type `int*`.

```c
int *p;      // pointer to int
double *q;   // pointer to double
char *r;     // pointer to char
```

**The position of `*` does not matter; all three forms are identical.**

```c
int* p;    // OK
int *p;    // OK (recommended)
int * p;   // OK
```

> **Caution:** Use `int *p` style. With `int* p, q;`, only `p` is a pointer and `q` is a plain `int`. Writing `int *p, *q;` makes it clear both are pointers.

```c
int* p, q;    // p is int*, q is int   (misleading!)
int *p, *q;   // both p and q are int* (clear)
```

**Pointer size is the same regardless of the pointed-to type.**

```c
int *p;
double *q;
char *r;

printf("%zu\n", sizeof(p));  // 8 (on 64-bit)
printf("%zu\n", sizeof(q));  // 8 (on 64-bit)
printf("%zu\n", sizeof(r));  // 8 (on 64-bit)
```

Because a pointer stores an address, not the data itself, its size is determined by the platform, not by the pointed-to type. On common platforms, all pointers occupy **4 bytes** on a 32-bit system and **8 bytes** on a 64-bit system.

### 1.3 Pointer Initialization

**The `&` (address-of) operator** returns the memory address of a variable. The result of `&` is an address whose type is a pointer to the variable written after `&`; for an `int` variable `a`, `&a` has type `int*`.

```c wide-ok
int a = 10;
int *p = &a;   // p now holds the address of a

printf("Address of a: %p\n", (void *)&a);   // e.g., 0x7ffee3c0
printf("Value of p:   %p\n", (void *)p);    // same address
```

**Restrictions on `&`:** The `&` operator works **only on variables** (lvalues). It cannot be applied to constants or expressions such as the following.

```c
&10        // ERROR: literal (no address)
&(a + 1)   // ERROR: expression result (temporary, no address)
#define MAX 100
&MAX       // ERROR: macro (replaced at preprocessing, no address)
```

**NULL pointer:** A pointer that points to nothing. `NULL` is a macro constant defined in the standard C library headers with the value 0 (some implementations define it as `((void *)0)`). `NULL` does not mean memory address 0; it means the pointer points to no variable. When it is not known which variable's address a pointer should hold, initialize it with `NULL`.

```c
int *q = NULL;   // explicitly points to nothing
int *r = 0;      // same as NULL
```

> **Note:** **Tip.** Always initialize pointers. An uninitialized pointer holds a garbage address, and dereferencing it causes **undefined behavior** (crash, data corruption, etc.).

**Format specifier `%p`** prints an address in hexadecimal.

```c
int x = 42;
int *p = &x;
printf("p = %p\n", (void *)p);   // p = 0x7ffee4b8 (example)
```

### 1.4 Dereference Operator `*`

The **dereference** (indirection) operator `*` accesses the value stored at the address held by the pointer. It is also called the indirect reference operator and can both **read** and **write**. The result of `*` is the pointed-to variable itself.

```c
int a = 10;
int *p = &a;

printf("%d\n", *p);   // 10 (read: get value at p's address)

*p = 20;               // write: change value at p's address
printf("%d\n", a);     // 20 (a was modified through p)
```

When `p` points to `a`, `*p` and `a` are **interchangeable names** for the same memory location; writing `*p` is treated as if `a` were written there. The pointer variable `p` is itself a variable, so it has its own address `&p`.

```text
   p ──────► ┌───────┐
             │  20   │  ← *p and a refer to the same location
             └───────┘
             address: 0x1000
```

*Figure 2. Variable a pointed to by pointer p*

**Restrictions on `*`:** The `*` operator works **only on pointers**. It cannot be applied to ordinary variables or integer expressions.

```c
int a = 10;
*a         // ERROR: a is not a pointer
*(a + 1)   // ERROR: (a + 1) is not a pointer
```

> **Key Point:** The `*` symbol has two meanings in pointer context: (1) in a declaration `int *p;` it indicates that `p` is a pointer, and (2) in an expression `*p` it dereferences `p` to access the value at the address `p` holds.

### 1.5 Pointer Usage

Why use pointers? The textbook highlights two key situations.

| Situation | Explanation |
|:----------|:------------|
| Function needs to return 2+ values | C functions can only `return` one value. Pass addresses of variables so the function can modify them. |
| Passing arrays to functions | Arrays decay to pointers when passed. Pointers allow efficient array access without copying. |

*Table 2. Two situations that require pointers*

```c wide-ok
// Example: function returning multiple values via pointers
void divide(int a, int b, int *quotient, int *remainder) {
    *quotient = a / b;
    *remainder = a % b;
}

int main() {
    int q, r;
    divide(17, 5, &q, &r);
    printf("17 / 5 = %d remainder %d\n", q, r);  // 3 remainder 2
    return 0;
}
```

Pointers also make it possible to write code that works on the pointed-to variable even when it is not known in advance which variable the pointer will point to. In other words, one piece of code can serve several variables.

### 1.6 `const` Pointer

The `const` keyword can restrict what a pointer can modify. Its meaning depends on where `const` is placed.

| Declaration | Meaning | `*p` modifiable | `p` modifiable |
|:------------|:--------|:-----------------|:----------------|
| `const int *p` | Pointer to const int | No | Yes |
| `int *const p` | Const pointer to int | Yes | No |
| `const int *const p` | Const pointer to const int | No | No |

*Table 3. Three `const` pointers by the position of `const`*

```c
int a = 10, b = 20;

// Pointer to const int: cannot modify *p, but can reassign p
const int *p1 = &a;
// *p1 = 30;    // ERROR: cannot modify value through p1
p1 = &b;        // OK: p1 now points to b

// Const pointer to int: can modify *p, but cannot reassign p
int *const p2 = &a;
*p2 = 30;       // OK: modifies a to 30
// p2 = &b;     // ERROR: cannot change where p2 points

// Const pointer to const int: neither modification allowed
const int *const p3 = &a;
// *p3 = 40;    // ERROR
// p3 = &b;     // ERROR
```

`const int *p` is a **read-only pointer** that only reads the pointed-to variable as if it were a `const` variable, and `int *const p` is a **dedicated pointer** to one variable: it is initialized with that variable's address at declaration and cannot point to another variable afterward. `const int *const p` has both properties, so it must be initialized. Of the three, the read-only pointer is the one mainly used in practice.

> **Note:** **Tip.** Read declarations **right to left**: `const int *p` = "p is a pointer to int that is const" (value is const), and `int *const p` = "p is a const pointer to int" (pointer itself is const).

### 1.7 Precautions When Using Pointers

First, always make a pointer point to a specific variable or make it a null pointer. Dereferencing a null pointer causes a runtime error that usually terminates the program abnormally, so dereference a pointer that might be null only after checking that it is not `NULL`.

```c
int *q = NULL;
if (q != NULL) {
    printf("%d\n", *q);   // dereference only when q is not a null pointer
}
```

Second, the type of a pointer must match the type of the variable it points to. If the types differ, the compiler issues a warning (an error in recent compilers), and running the program while ignoring the warning interprets memory as a different type, so wrong values are read or written.

```c
double d = 3.14;
int *pi = &d;   // warning: incompatible pointer type
```

Third, do not dereference an uninitialized pointer. A local pointer declared only as `int *p;` contains a garbage address, so `*p = 5;` writes a value into unknown memory. Such a pointer is often called a **wild pointer**; with luck the program terminates abnormally at once, and without luck it silently corrupts the value of another variable. For the same reason, avoid putting an address value in directly, as in `int *p = (int *)0x1000;`. In a typical operating system, the locations of memory a program may use are decided by the operating system at each run, so there is no guarantee that an absolute address written in the source code points to a valid variable. Put only the address of a variable obtained with `&`, or `NULL`, into a pointer.

### 1.8 Step-by-Step Trace of Pointer Expressions

Code that handles pointers is traced by distinguishing statements that change "the value of the pointer itself (an address)" from statements that change "the value of the variable the pointer points to." The following code is executed one statement at a time while printing the variables.

```c
int a = 10, b = 20;
int *p = &a, *q = &b;

*p = *q + 5;
printf("1: a = %d, b = %d, *p = %d, *q = %d\n", a, b, *p, *q);
p = q;
printf("2: a = %d, b = %d, *p = %d, *q = %d\n", a, b, *p, *q);
*p = 1;
printf("3: a = %d, b = %d, *p = %d, *q = %d\n", a, b, *p, *q);
(*q)++;
printf("4: a = %d, b = %d, *p = %d, *q = %d\n", a, b, *p, *q);
printf("p == q is %d\n", p == q);
```

```text
1: a = 25, b = 20, *p = 25, *q = 20
2: a = 25, b = 20, *p = 20, *q = 20
3: a = 25, b = 1, *p = 1, *q = 1
4: a = 25, b = 2, *p = 2, *q = 2
p == q is 1
```

| Statement | What Changes | Variable `p` Points To | `a` | `b` |
|:-----|:-----|:-----|-----:|-----:|
| Initial state | Nothing | `a` | 10 | 20 |
| `*p = *q + 5;` | The value of `a`, which `p` points to | `a` | 25 | 20 |
| `p = q;` | The value (address) of the pointer `p` | `b` | 25 | 20 |
| `*p = 1;` | The value of `b`, which `p` points to | `b` | 25 | 1 |
| `(*q)++;` | The value of `b`, which `q` points to | `b` | 25 | 2 |

*Table 4. What changes when pointer expressions execute*

`p = q;` does not copy the value of `b` into `a`; it only makes `p` point to `b`, so `a` remains 25. From then on, `p` and `q` hold the same address, so `p == q` is true, and both `*p` and `*q` mean `b`. The parentheses in `(*q)++` are needed because postfix `++` has higher precedence than `*`; writing `*q++` would mean `*(q++)`, which increments the pointer `q` rather than `b`.

### 1.9 Memory Picture of a Pointer Variable

A pointer is also a variable that occupies a place in memory, so a pointer has "its own address" and "the value it stores (the address of another variable)" separately. The following code prints the addresses, values, and sizes of an `int` variable `a` and a pointer `p` that stores its address.

```c
int a = 10;
int *p = &a;

printf("&a = %p, a = %d\n", (void *)&a, a);
printf("&p = %p, p = %p, *p = %d\n", (void *)&p, (void *)p, *p);
printf("sizeof(a) = %zu, sizeof(p) = %zu\n", sizeof(a), sizeof(p));
```

```text
&a = 0x16f4feb18, a = 10
&p = 0x16f4feb10, p = 0x16f4feb18, *p = 10
sizeof(a) = 4, sizeof(p) = 8
```

```text
        address        contents
      ┌──────────────┬────────────────────┐
p     │ 0x16f4feb10  │ 0x16f4feb18 ───────┼──┐   value of p = address of a (8 bytes)
      ├──────────────┼────────────────────┤  │
a     │ 0x16f4feb18  │ 10                 │◄─┘   *p is this cell (4 bytes)
      └──────────────┴────────────────────┘
```

*Figure 3. Memory layout of the pointer p and the variable a*

In the output, the value of `p` equals `&a`, so `p` points to `a`. `&p` is a different address, the place where the pointer `p` itself sits. `*p` is the value 10 read by going to the address stored in `p`. `a` is 4 bytes, and `p` is 8 bytes, holding one 64-bit address. The actual address values change at each run, but the relationship that the value of `p` equals `&a` does not. The textbook's examples were built as 32-bit programs, so addresses print as 8 hexadecimal digits (4 bytes), but building for 64 bits makes pointers 8 bytes, so the output grows longer, as in this example.

`&` and `*` are operations in opposite directions: `&a` goes from a variable to an address, and `*p` from an address to a variable. Therefore `*&a` equals `a`, and if `p` points to a valid variable, `&*p` equals `p`. This relationship lets a complex expression be unwound one step at a time. For example, for the `p` above, `*p + 1` is `a + 1`, that is 11, `&a == p` is true, and `*&p` is `p` itself.

---

<br>

## 2. Arrays and Pointers

### 2.1 Pointer Arithmetic

When you add or subtract an integer to/from a pointer, the compiler scales by the **size of the pointed-to type**, not by 1 byte. That is, `p + N` is the address `N` elements of the pointed-to type beyond `p`, and `p++` and `++p` increase the address by the size of one element.

```c
int arr[5] = {10, 20, 30, 40, 50};
int *p = arr;    // p points to arr[0]
```

```text
p     p+1    p+2    p+3    p+4
│      │      │      │      │
▼      ▼      ▼      ▼      ▼
┌──────┬──────┬──────┬──────┬──────┐
│  10  │  20  │  30  │  40  │  50  │
└──────┴──────┴──────┴──────┴──────┘
0x1000  0x1004  0x1008  0x100C  0x1010
        (+4B)   (+4B)   (+4B)   (+4B)
```

*Figure 4. Addresses of int array elements reached by pointer arithmetic*

| Pointer Type | `p + 1` Advances By |
|:-------------|:--------------------|
| `int *` | 4 bytes (`sizeof(int)`) |
| `double *` | 8 bytes (`sizeof(double)`) |
| `char *` | 1 byte (`sizeof(char)`) |

*Table 5. How far `p + 1` moves for each pointer type*

**Supported operations:**

| Operation | Meaning |
|:----------|:--------|
| `p + n` | Move forward by `n` elements |
| `p - n` | Move backward by `n` elements |
| `p++` | Advance to next element |
| `p--` | Move to previous element |
| `p1 - p2` | Number of elements between two pointers (not bytes) |

*Table 6. Operations allowed on pointers*

```c
int arr[5] = {10, 20, 30, 40, 50};
int *p = arr;

printf("%d\n", *(p + 2));   // 30 (third element)

p++;
printf("%d\n", *p);         // 20 (second element)

int *q = &arr[4];
printf("%ld\n", q - p);     // 3 (distance in elements, not bytes)
```

> **Note:** The difference of two pointers has type `ptrdiff_t` from `<stddef.h>`, and the exact format specifier for printing it with `printf` is `%td`. The `%ld` above prints correctly on 64-bit Linux and macOS, where `long` and `ptrdiff_t` have the same size, but it does not match on 64-bit Windows, where `long` is 4 bytes.

> **Caution:** Pointer arithmetic is valid only within an array (or one past its end). Going beyond causes **undefined behavior**.

### 2.2 Pointer as Array

The operation `p + i` accesses memory as if an array existed at the address the pointer holds. Therefore a `type*` pointer can point not only to a `type` variable but also to an element of a `type` array, and a pointer can use the **subscript operator `[]`**. The expression `p[i]` is always processed as `*(p + i)`.

```c
int arr[5] = {10, 20, 30, 40, 50};
int *p = arr;

printf("%d\n", p[0]);       // 10  (same as *(p + 0))
printf("%d\n", p[2]);       // 30  (same as *(p + 2))
printf("%d\n", *(p + 4));   // 50  (same as p[4])
```

| Notation | Equivalent | Meaning |
|:---------|:-----------|:--------|
| `p[i]` | `*(p + i)` | Access i-th element from p |
| `&p[i]` | `p + i` | Address of i-th element from p |

*Table 7. Correspondence between subscript notation and pointer notation*

### 2.3 Array as Pointer

An **array name** used without an index is the starting address of the array, that is, the address of its first element. The array name therefore acts as a **pointer constant**, and `*(arr + i)` can be used instead of `arr[i]`.

```c
int arr[5] = {10, 20, 30, 40, 50};

printf("%p\n", (void *)arr);       // address of arr[0]
printf("%p\n", (void *)&arr[0]);   // same address

printf("%d\n", *arr);         // 10  (same as arr[0])
printf("%d\n", *(arr + 2));   // 30  (same as arr[2])
```

**Key equivalences:**

| Array Notation | Pointer Notation |
|:---------------|:-----------------|
| `arr` | `&arr[0]` |
| `arr[i]` | `*(arr + i)` |
| `&arr[i]` | `arr + i` |

*Table 8. Equivalences between array notation and pointer notation*

> **Caution:** The array name is a **constant**, so it cannot be modified. You **cannot** do the following.
> ```c
> arr++;          // ERROR: cannot increment a constant
> arr = other;    // ERROR: cannot reassign array name
> ```

### 2.4 Array vs Pointer Comparison

| Feature | Array (`int arr[5]`) | Pointer (`int *p`) |
|:--------|:---------------------|:-------------------|
| Address | **Fixed** (cannot change) | **Variable** (can reassign) |
| `sizeof` | Total array size (`5 * 4 = 20`) | Pointer size (`4` or `8`) |
| Memory allocation | Allocated at declaration | Must point to existing memory |
| `++` operator | Not allowed (`arr++` is error) | Allowed (`p++` moves to next element) |
| Identity | `arr` is the array itself | `p` is an independent variable |

*Table 9. Comparison of an array and a pointer (with a 4-byte `int`)*

```c
int arr[5] = {1, 2, 3, 4, 5};
int *p = arr;

printf("%zu\n", sizeof(arr));   // 20 (5 * sizeof(int))
printf("%zu\n", sizeof(p));     // 8  (pointer size on 64-bit)

// arr++;   // ERROR
p++;        // OK: p now points to arr[1]
```

> **Key Point:** Although `arr` and `p` can be used interchangeably in many expressions (like `arr[i]` and `p[i]`), they are fundamentally different: an array name is a fixed starting address, like a pointer dedicated to one array, while `p` is a variable that can hold a different address at run time.

### 2.5 Arrays of Pointers and Double Pointers

A pointer is also a variable, so an array whose elements are pointers can be made, and so can a pointer that stores the address of a pointer. An **array of pointers** `int *list[3]` is an array of 3 elements of type `int*`, and a **double pointer** `int **pp` is a pointer that stores the address of an `int*` variable.

```c
int x = 1, y = 2, z = 3;
int *list[3] = { &x, &y, &z };      // array of pointers
int *p = &x;
int **pp = &p;                      // double pointer
int i;

for (i = 0; i < 3; i++)
    *list[i] *= 10;                 // multiply each pointed-to variable by 10
printf("x = %d, y = %d, z = %d\n", x, y, z);

**pp = 99;                          // pp → p → x
printf("x = %d, *p = %d, **pp = %d\n", x, *p, **pp);
*pp = &y;                           // make p point to y
printf("*p = %d\n", *p);
printf("sizeof list = %zu, sizeof pp = %zu\n", sizeof(list), sizeof(pp));
```

```text
x = 10, y = 20, z = 30
x = 99, *p = 99, **pp = 99
*p = 20
sizeof list = 24, sizeof pp = 8
```

`*list[i]` binds `[]` before `*`, so it is `*(list[i])`, the variable that the `i`th element points to. Arrays of pointers are used to process several separate variables with one loop, and the arrays of string pointers in Chapter 9 are a typical example. `**pp` dereferences `pp` once to get `p` and again to reach `x`, so `**pp = 99` changes `x`. `*pp = &y` changes `p` itself, which `pp` points to, so a double pointer is used as a parameter when a function must change a pointer variable of its caller. On a 64-bit platform a pointer is 8 bytes, so the size of `list` is 3 × 8 = 24 bytes. The uses of arrays of pointers and double pointers, and the difference from pointers to arrays, are treated in detail in Chapter 11.

### 2.6 Differences Among `arr`, `&arr[0]`, and `&arr`

The array name `arr`, the address of the first element `&arr[0]`, and the address of the whole array `&arr` print the same address value, but their types differ, and therefore so does the amount they move when 1 is added.

```c
int arr[5] = { 1, 2, 3, 4, 5 };

printf("arr     = %p, arr + 1     = %p\n", (void *)arr, (void *)(arr + 1));
printf("&arr[0] = %p, &arr[0] + 1 = %p\n", (void *)&arr[0], (void *)(&arr[0] + 1));
printf("&arr    = %p, &arr + 1    = %p\n", (void *)&arr, (void *)(&arr + 1));
printf("sizeof arr = %zu, sizeof &arr[0] = %zu, sizeof *&arr = %zu\n",
       sizeof arr, sizeof &arr[0], sizeof *&arr);
```

```text
arr     = 0x16f0eeaf0, arr + 1     = 0x16f0eeaf4
&arr[0] = 0x16f0eeaf0, &arr[0] + 1 = 0x16f0eeaf4
&arr    = 0x16f0eeaf0, &arr + 1    = 0x16f0eeb04
sizeof arr = 20, sizeof &arr[0] = 8, sizeof *&arr = 20
```

| Expression | Type | What It Points To | Movement of `+ 1` |
|:-----|:-----|:-----|-----:|
| `arr` (in most expressions) | `int *` | The first element `arr[0]` | 4 bytes |
| `&arr[0]` | `int *` | The first element `arr[0]` | 4 bytes |
| `&arr` | `int (*)[5]` | The whole array of 5 elements | 20 bytes |

*Table 10. Comparison of the array name and two kinds of addresses*

When `arr` is used in an expression, it turns into an `int *` pointing to the first element, so it equals `&arr[0]`, and adding 1 points 4 bytes later, the size of one `int`, at `arr[1]`. `&arr` is an address that points to the whole array as one object, so adding 1 moves 20 bytes later, the size of one array, that is, to the position right after the end of the array: 0xaf0 + 0x14 (20) = 0xb04. There are exceptions where an array name does not turn into an address: `sizeof arr` is the size of the whole array, 20, and the `&` of `&arr` also applies to the whole array. A pointer to an array, such as `int (*)[5]`, is the type actually used when a 2D array is passed to a function, and it is treated in detail in Chapter 11.

### 2.7 Pointer Arithmetic by Element Type

The rule of Section 2.1, that `p + 1` moves by the size of the pointed-to type, is checked with four types. The number of bytes moved is the difference of the two addresses converted to `char *`; since `char` is 1 byte, the difference of `char *` values is a number of bytes.

```c
char c[4];
short s[4];
int i[4];
double d[4];
char *pc = c;
short *ps = s;
int *pi = i;
double *pd = d;

printf("char:   %p -> %p (+%td)\n", (void *)pc, (void *)(pc + 1), (char *)(pc + 1) - (char *)pc);
printf("short:  %p -> %p (+%td)\n", (void *)ps, (void *)(ps + 1), (char *)(ps + 1) - (char *)ps);
printf("int:    %p -> %p (+%td)\n", (void *)pi, (void *)(pi + 1), (char *)(pi + 1) - (char *)pi);
printf("double: %p -> %p (+%td)\n", (void *)pd, (void *)(pd + 1), (char *)(pd + 1) - (char *)pd);
printf("pi + 3 - pi = %td\n", (pi + 3) - pi);
```

```text
char:   0x16b1b6ac8 -> 0x16b1b6ac9 (+1)
short:  0x16b1b6b00 -> 0x16b1b6b02 (+2)
int:    0x16b1b6af0 -> 0x16b1b6af4 (+4)
double: 0x16b1b6ad0 -> 0x16b1b6ad8 (+8)
pi + 3 - pi = 3
```

The same `+ 1` moves 1 byte for `char *`, 2 bytes for `short *`, 4 bytes for `int *`, and 8 bytes for `double *`. In general, for a pointer p of type T, the address of `p + n` is p + n × `sizeof(T)`. Conversely, the difference of two pointers of the same type is the number of bytes divided by the element size, that is, a number of elements, so `(pi + 3) - pi` is 3, not 12 bytes. `%td` is the format specifier for `ptrdiff_t`, the integer type that holds pointer differences. Because the type of the pointer decides the amount of movement, pointing to an `int` variable with a `short *`, as in Section 1.7, changes even the number of bytes read when it is dereferenced.

> **Note:** **Byte order.** Converting the address of `int n = 0x11223344;` to `unsigned char *` and printing its four bytes in order gives `44 33 22 11` in this environment. This arrangement, in which the least significant byte is placed at the lowest address, is called little endian, and some CPUs use the opposite order, big endian. Precautions for code that depends on byte order are treated in Chapter 13.

### 2.8 Various Pointer Declarations

Pointers can be declared to point to many kinds of targets: elements, arrays, pointers, and functions. The textbook explains that while first learning, one need not use all of these features; it is enough to be able to read the meaning of a declaration. A declaration is read starting from the variable name, reading the `[]` and `()` on the right first and the `*` on the left later, but reading inside parentheses first when they are present.

| Declaration | How to Read It | Meaning |
|:-----|:-----|:-----|
| `int *p;` | p is a pointer, to an `int` | A pointer to an `int` variable |
| `int *arr[3];` | arr is an array of 3 elements, each an `int` pointer | An array of pointers (Section 2.5) |
| `int (*pa)[3];` | pa is a pointer, to an array of 3 `int` | A pointer to an array (the type of `&arr` in Section 2.6) |
| `int **pp;` | pp is a pointer, to an `int` pointer | A double pointer (Section 2.5) |
| `int (*fp)(int);` | fp is a pointer, to a function taking an `int` and returning an `int` | A function pointer |

*Table 11. Various pointer declarations and how to read them*

`int *arr[3]` and `int (*pa)[3]` differ completely in meaning by one pair of parentheses. In the first, `[]` binds before `*`, so it is an array; in the second, the parentheses make `*` bind first, so it is a pointer. Checking with `sizeof` in a 64-bit environment, `arr` is 24 bytes for 3 pointers, and `pa` is 8 bytes for one pointer. The uses of pointers to arrays and function pointers are treated in Chapter 11.

### 2.9 Traversing an Array with a Pointer

An array can also be processed by moving a pointer one slot at a time instead of using indices. The following code increments `p`, which points to the first element, until it reaches the end of the array `end` (= `arr + 5`), computing the sum.

```c
int arr[5] = { 3, 1, 4, 1, 5 };
int *p, *end = arr + 5, sum = 0;

for (p = arr; p < end; p++) {
    sum += *p;
    printf("p - arr = %td, *p = %d, sum = %d\n", p - arr, *p, sum);
}
printf("p == end: %d\n", p == end);

p = arr;
printf("%d ", *p++);
printf("%d ", *p++);
printf("%d\n", *p);
```

```text
p - arr = 0, *p = 3, sum = 3
p - arr = 1, *p = 1, sum = 4
p - arr = 2, *p = 4, sum = 8
p - arr = 3, *p = 1, sum = 9
p - arr = 4, *p = 5, sum = 14
p == end: 1
3 1 4
```

`p - arr` equals the index of the element currently pointed to, so this loop does the same job as `for (i = 0; i < 5; i++) sum += arr[i];`. `end` points to the position after the last element `arr[4]`. C allows creating and comparing a pointer to the position just past an array, but not dereferencing that position. That is why the condition is `p < end`, not `p <= end`, and after the loop `p` equals `end`, but `*p` is not read.

The `*p++` in the last three lines is an idiom often seen in code that handles strings and arrays. Postfix `++` binds first, so it is `*(p++)`, meaning "use the value at the current position and move the pointer to the next." Hence the first two outputs are the 3 of `arr[0]` and the 1 of `arr[1]`, after which `p` points to `arr[2]` and prints 4.

---

<br>

## 3. Functions and Pointers

### 3.1 Pass by Value vs Pass by Reference

| Method | Mechanism | Original modifiable |
|:-------|:----------|:---------------------|
| Pass by value | Function receives a **copy** of the argument | No |
| Pass by reference | Function receives the **address** via a pointer | Yes |

*Table 12. Pass by value and pass by reference*

In pass by value, a function parameter is a local variable created when the function is called and initialized with the value of the argument. In pass by reference, the parameter is declared as a pointer to the argument, and the address of the variable to pass is given when the function is called.

```c
void by_value(int x) {
    x = 100;   // modifies local copy only
}

void by_reference(int *x) {
    *x = 100;  // modifies the original variable
}

int main() {
    int a = 10;

    by_value(a);
    printf("%d\n", a);     // 10 (unchanged)

    by_reference(&a);
    printf("%d\n", a);     // 100 (modified)

    return 0;
}
```

```text
Pass by Value              Pass by Reference
┌──────────────┐           ┌───────────────┐
│ main         │           │ main          │
│  a = 10      │           │  a = 10 → 100 │
└──────┬───────┘           └───────┬───────┘
       │ copy                      │ address
       ▼                           ▼
┌──────────────┐           ┌───────────────┐
│ by_value     │           │ by_reference  │
│  x = 10→100  │           │  x = &a       │
│  (local copy)│           │  *x = 100     │
└──────────────┘           └───────────────┘
   a unchanged                 a changed!
```

*Figure 5. Comparison of pass by value and pass by reference*

> **Note:** Strictly speaking, C passes every argument by value; pass by reference is implemented by passing a pointer (address) by value. The textbook calls this method call by reference.

### 3.2 Modifying a Variable Through a Pointer

Why pass by reference is necessary can be seen from a function that adds 10 to the caller's variable.

**Wrong: pass by value (does NOT work)**

```c
void addTen_wrong(int x) {
    x = x + 10;
    // x is a local copy: original unchanged
}

int main() {
    int score = 85;
    addTen_wrong(score);
    printf("score = %d\n", score);   // score = 85 (not modified!)
    return 0;
}
```

```text
Before addTen_wrong:      Inside addTen_wrong:      After addTen_wrong:
  main: score=85           x=85→95                   main: score=85
         │                 (local copy)               (unchanged!)
         ▼
        copy
         │
         ▼
        x=85
```

*Figure 6. Behavior of addTen_wrong called by value*

**Correct: pass by reference (works)**

```c
void addTen(int *p) {
    *p = *p + 10;   // modify the original variable through the pointer
}

int main() {
    int score = 85;
    addTen(&score);
    printf("score = %d\n", score);   // score = 95 (modified!)
    return 0;
}
```

```text
Before addTen:            Inside addTen:            After addTen:
  main: score=85           *p=85→95                  main: score=95
         │                 (modify via address)       (modified!)
         ▼
       &score
         │
         ▼
        p=&score
       *p=85
```

*Figure 7. Behavior of addTen called by reference*

> **Note:** **Classic exercise.** Swapping two values is the most well-known application of this pattern, and it cannot be implemented with pass by value. It requires two pointer parameters so the function can modify both caller variables.

A swap function declares its parameters as pointers to the arguments, and the caller passes the addresses of the two variables to swap.

```c
void swap(int *px, int *py) {
    int temp = *px;
    *px = *py;
    *py = temp;
}

int main() {
    int a = 3, b = 5;
    swap(&a, &b);
    printf("a = %d, b = %d\n", a, b);   // a = 5, b = 3
    return 0;
}
```

### 3.3 Returning Multiple Values

Since C functions can only `return` a single value, pointer parameters are used to give back additional values.

```c wide-ok
void sec_to_hms(int sec, int *h, int *m, int *s) {
    *h = sec / 3600;
    *m = (sec % 3600) / 60;
    *s = sec % 60;
}

int main() {
    int hours, minutes, seconds;
    int total_sec = 3723;

    sec_to_hms(total_sec, &hours, &minutes, &seconds);
    printf("%d seconds = %dh %dm %ds\n", total_sec, hours, minutes, seconds);
    // 3723 seconds = 1h 2m 3s

    return 0;
}
```

> **Key Point:** The caller passes **addresses** of its variables. The function writes results through those addresses using `*`.

Parameters fall into three kinds according to their role inside the function, and the role determines how the argument is passed.

| Kind | Role | Example | Passing Method |
|:-----|:-----|:--------|:---------------|
| Input parameter | Its value is used in the function but not changed. | `int add(int x, int y);` | Pass by value |
| Output parameter | Its value is not used in the function but is changed before the function returns. | `void get_sum_product(int x, int y, int *sum, int *product);` | Pass by reference |
| Input/output parameter | Its value is both used in the function and changed before the function returns. | `void swap(int *px, int *py);` | Pass by reference |

*Table 13. Argument passing method by parameter role*

A function that returns its results through output parameters is written in the following order. (1) In the prototype, declare each output parameter as a pointer to the variable that will store the result. (2) When calling the function, prepare the variables that will receive the results and pass their addresses. (3) In the function definition, store the results where the pointer parameters point.

```c wide-ok
void get_sum_product(int x, int y, int *psum, int *pproduct) {
    *psum = x + y;        // store the sum where psum points
    *pproduct = x * y;    // store the product where pproduct points
}

int main() {
    int sum, product;     // variables that receive the results
    get_sum_product(4, 5, &sum, &product);
    printf("sum: %d, product: %d\n", sum, product);   // sum: 9, product: 20
    return 0;
}
```

### 3.4 Passing Arrays to Functions

When an array is passed to a function, the array name **decays** to a pointer to its first element. The function receives a pointer, not a copy of the array. Passing an array by value would require copying the whole array, which costs both time and space, so an array is always passed by its address.

**Two equivalent function signatures:**

```c
void print_array(int *arr, int size);    // pointer syntax
void print_array(int arr[], int size);   // array syntax (same thing)
```

Both are identical: `int arr[]` in a function parameter is treated as `int *arr`.

```c
void print_array(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);   // arr[i] same as *(arr + i)
    }
    printf("\n");
}

int main() {
    int data[5] = {10, 20, 30, 40, 50};
    print_array(data, 5);   // array name decays to pointer
    return 0;
}
```

> **Caution:** Inside the function, `sizeof(arr)` returns the **pointer size** (4 or 8), **not** the total array size. This is why the size must be passed as a separate parameter.

```c
void func(int arr[]) {
    printf("%zu\n", sizeof(arr));    // 8 (pointer size, NOT array size!)
}

int main() {
    int arr[5] = {1, 2, 3, 4, 5};
    printf("%zu\n", sizeof(arr));    // 20 (total array size)
    func(arr);
    return 0;
}
```

**Modifying array elements through a pointer parameter:**

```c
void double_elements(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        arr[i] *= 2;   // modifies the original array
    }
}

int main() {
    int nums[4] = {1, 2, 3, 4};
    double_elements(nums, 4);
    // nums is now {2, 4, 6, 8}
    return 0;
}
```

> **Note:** **Tip.** If the function should **not** modify the array, that is, if the array is an input parameter, declare the parameter as `const int *arr`. The compiler will prevent accidental writes.

Passing an array as a function argument can be summarized as follows. (1) In the prototype, declare the parameter as an array without a size (`int arr[]`) or as a pointer to the element type (`int *arr`). (2) If the function needs the array size, receive the size as a parameter too. (3) If the array is an input parameter, add `const`. (4) When calling the function, pass the array name as the argument. (5) In the function definition, use the pointer parameter like an array.

In a parameter declaration, `int arr[]`, `int arr[10]`, and `int *arr` are all treated as the same type, `int *`. Therefore the prototype `void f(int arr[]);` and the prototype `void f(int *arr);` written together in one file declare the same function without conflict, and the size 10 written in `int arr[10]` is ignored. However, under `-Wall`, when a declaration with a written size such as `int arr[10]` is followed by an array-notation declaration with a different size such as `int arr[]`, Clang issues the warning `argument 'arr' of type 'int[]' with mismatched bound`, even though the types are the same. The only difference is that the array notation reveals the intent that "an array comes through this parameter" while the pointer notation reveals the actual type, so one notation is used consistently within a program. It is also because the parameter `arr` is a pointer variable, not an array, that `arr++` is allowed inside the function.

### 3.5 Functions That Return Addresses

A function can also return a pointer. In that case it must be checked that the returned address remains valid after the function ends. A local variable is destroyed when the function returns, so if its address is returned, the caller receives a pointer to a variable that no longer exists. Such a pointer is called a **dangling pointer**, and dereferencing it is undefined behavior.

```c
int *bad(void)
{
    int local = 42;

    return &local;              // local is destroyed when the function ends
}
```

```text
warning: address of stack memory associated with local variable 'local' returned [-Wreturn-stack-address]
```

In contrast, the address of an element of an array passed in by the caller remains valid after the function ends. The following function returns the address of the largest element of an array, and the caller can change that element directly through the address.

```c
int *largest(int arr[], int size)
{
    int *best = &arr[0];
    int i;

    for (i = 1; i < size; i++)
        if (arr[i] > *best)
            best = &arr[i];
    return best;
}

int main(void)
{
    int data[5] = { 4, 9, 2, 9, 7 };
    int *m = largest(data, 5);

    *m = 0;
    printf("%d %d %d %d %d, index %d\n", data[0], data[1], data[2], data[3], data[4], (int)(m - data));
    return 0;
}
```

```text
4 0 2 9 7, index 1
```

The maximum 9 appears twice, but since the comparison is `>`, the address of the earlier `data[1]` is returned, and `*m = 0` changes that element to 0. The difference `m - data` of two pointers into the same array is the number of elements between the two positions, so it gives the index 1 (Section 2.1). In summary, the addresses a function may return are the addresses of arrays or variables received as arguments, addresses of global variables, and addresses of dynamically allocated memory, learned in Chapter 11; the address of a local variable of the function is not returned.

### 3.6 Memory Trace of a `swap` Call

Pass-by-address of Section 3.1 is checked with addresses. `swap` receives the addresses of two `int` variables and exchanges `*x` and `*y`.

```c
void swap(int *x, int *y)
{
    int t;

    printf("in swap: x = %p, y = %p, *x = %d, *y = %d\n", (void *)x, (void *)y, *x, *y);
    t = *x;
    *x = *y;
    *y = t;
}

int main(void)
{
    int a = 3, b = 7;

    printf("in main: &a = %p, &b = %p\n", (void *)&a, (void *)&b);
    swap(&a, &b);
    printf("a = %d, b = %d\n", a, b);
    return 0;
}
```

```text
in main: &a = 0x16d982b08, &b = 0x16d982b04
in swap: x = 0x16d982b08, y = 0x16d982b04, *x = 3, *y = 7
a = 7, b = 3
```

```text
area of main                         area of swap
┌─────────────────────────┐         ┌──────────────────────────┐
│ a  @...b08 : 3 → 7      │◄────────┤ x : 0x...b08             │
│ b  @...b04 : 7 → 3      │◄────────┤ y : 0x...b04             │
└─────────────────────────┘         │ t : 3                    │
                                    └──────────────────────────┘
```

*Figure 8. Variables of main and swap during the call to swap*

The parameters `x` and `y` of `swap` receive copies of `&a` and `&b` of `main`, so the printed addresses are the same. The parameters themselves are still copies passed by value, but because their values are addresses, `*x` reaches `a` of `main`. Following the three statements in order, `t = *x` makes `t` 3, `*x = *y` makes `a` 7, and `*y = t` makes `b` 3. When `swap` ends, `x`, `y`, and `t` disappear, but the values written to `a` and `b` remain. If values were passed instead, as in `swap(a, b)`, 3 and 7 would be used as addresses, and the compiler reports that `int` cannot be converted to `int *`.

### 3.7 Common Mistakes with Pointers

Pointer mistakes appear as warnings at compile time and as abnormal termination at run time. The following code contains three mistakes that produce warnings.

```c
int a = 5, *p, *q = &a;

*p = 3;                 // dereferences p without initializing it
if (q == 5)             // compares a pointer with an integer
    printf("five\n");
printf("%d\n", q);      // prints a pointer with %d
```

```text
warning: comparison between pointer and integer ('int *' and 'int') [-Wpointer-integer-compare]
warning: format specifies type 'int' but the argument has type 'int *' [-Wformat]
warning: variable 'p' is uninitialized when used here [-Wuninitialized]
```

All three warnings come from a missing or misplaced `*`. If `q == 5` and `printf("%d", q)` meant the value `q` points to, they must be written `*q == 5` and `printf("%d", *q)`. `*p = 3` is the wild pointer of Section 1.7. Omitting `*` in an assignment, as in `q = 7;`, is not a warning but the error `incompatible integer to pointer conversion`.

Dereferencing a null pointer shows up at run time without a compile warning. A program that executed `int *p = NULL; *p = 1;` terminated abnormally on arm64 macOS with a segmentation fault (SIGSEGV), and the exit status reported to the shell was 139. Such errors are found by placing an `if (p != NULL)` check before the dereferencing line, or by inspecting the pointer's value with a debugger just before it is used.

---

<br>

## Concept Applications

**True/False Check:**

| Statement | Judgment and Reason |
|:-----|:-----|
| `int *p, q;` declares two pointers. | **F.** The `*` attaches only to `p`, so `q` is an `int` variable. |
| When `double` is 8 bytes, `d + 1` for `double *d` increases the address by 8. | **T.** Pointer arithmetic moves in units of the size of the pointed-to type. |
| The size of a pointer depends on the data type it points to. | **F.** On typical platforms every pointer has the same size, 8 bytes on 64-bit. |
| An array name can be incremented, as in `arr++`. | **F.** An array name is an unchangeable starting address, so it cannot be incremented; only pointer variables can. |
| With `const int *p`, the value `p` points to cannot be changed, but `p` itself can. | **T.** To fix the pointer itself, declare it as `int *const p`. |
| The address of a function's local variable can be used safely right after it is returned. | **F.** A local variable is destroyed when the function returns, so the returned address is a dangling pointer. |
| `*p++` increments the value `p` points to by 1. | **F.** Postfix `++` binds first, giving `*(p++)`, so the pointer is incremented. To increment the value, write `(*p)++`. |
| The difference of two pointers into the same array is the number of bytes between the two addresses. | **F.** The difference of pointers is not a number of bytes but the number of elements between the two positions. |

---

<br>

## Summary

| Concept | Key Summary |
|:--------|:------------|
| Pointer | A pointer is an address, and a pointer variable is a variable that stores an address. |
| Pointer declaration | A pointer is declared as `type *p;`, where the type is that of the variable being pointed to. |
| Pointer size | On common platforms, a pointer is 4 bytes on 32-bit and 8 bytes on 64-bit, regardless of the pointed-to type. |
| `&` (address-of) | It returns the address of a variable and cannot be used on literals, expressions, or macros. |
| `*` (dereference) | It reads or writes the value at the address a pointer holds and works only on pointers. |
| NULL pointer | `int *p = NULL;` is a pointer that points to nothing, and pointers should always be initialized. |
| `%p` | It is the format specifier that prints an address in hexadecimal. |
| `const` pointer | `const int *p` is a read-only pointer whose value is const, `int *const p` is a dedicated pointer that is itself const, and both can be combined. |
| Pointer precautions | A pointer that may be null is checked before dereferencing, and the pointer type must match the pointed-to variable's type. |
| Pointer arithmetic | `p + 1` moves by `sizeof(*p)` bytes, not by 1 byte. |
| `p[i]` vs `*(p+i)` | Subscript notation and pointer arithmetic mean the same thing and are interchangeable. |
| Array name | An array name is the address of the first element and acts as a pointer **constant** that cannot be modified. |
| Array vs pointer | An array has a fixed address and `sizeof` gives the total size, while a pointer can change its address and `sizeof` gives 4 or 8. |
| Pass by value | The function gets a copy, so the original cannot be changed. |
| Pass by reference | The function gets the address via a pointer, so it can modify the original. |
| Modify via pointer | To modify the caller's variable, its address must be passed (`int *p`); pass by value cannot modify it. |
| Multiple return values | The caller passes the addresses of the variables that receive results, and the function writes the values via `*`. |
| Parameter roles | Input parameters are passed by value, while output and input/output parameters are passed by address. |
| Array to function | An array decays to a pointer, so `sizeof(arr)` in the function is the pointer size and the size must be passed separately. |
| Wild pointers | An uninitialized pointer or a hand-picked absolute address is not guaranteed to point to a valid variable, so it is not dereferenced. |
| Tracing pointer expressions | `p = q` changes what the pointer points to, `*p = ...` changes the value of the pointed-to variable, and `(*q)++` differs from `*q++`. |
| Arrays of pointers and double pointers | `int *list[3]` is an array whose elements are pointers, and `int **pp` stores the address of a pointer so that `*pp` can change the pointer itself. |
| Returning addresses | Returning the address of a local variable creates a dangling pointer, while addresses of array elements received as arguments or of global variables may be returned. |
| Memory of a pointer variable | A pointer has its own address (`&p`) apart from the stored address (`p`) and is 8 bytes on 64-bit. |
| `arr`, `&arr[0]`, `&arr` | Their values are equal, but `arr` and `&arr[0]` are `int *` and `&arr` is `int (*)[5]`, so `+ 1` moves 4 bytes and 20 bytes respectively. |
| Pointer arithmetic by type | `p + n` moves n × `sizeof(T)` bytes, and the difference of two pointers is a number of elements. |
| Reading pointer declarations | Start from the name, read the `[]` and `()` on the right first and the `*` on the left later, and read inside parentheses first. |
| Common pointer mistakes | A missing `*` and an uninitialized pointer appear as warnings, and dereferencing a null pointer as abnormal termination at run time. |
| Traversing with a pointer | Traverse with `for (p = arr; p < arr + n; p++)`; a pointer just past the array may be compared but not dereferenced. |

---

<br>

## Self-Check Questions

1. **Pointer arithmetic:** Given `int arr[5] = {10, 20, 30, 40, 50}; int *p = arr + 1;`, find the values of `*(p + 2)`, `p[-1]`, and `&arr[4] - p`.

   <details>
   <summary>Answer</summary>

   `p` points to `arr[1]`. `*(p + 2)` is `arr[3]`, so it is 40, and `p[-1]` is `*(p - 1)`, that is, `arr[0]`, so it is 10. `&arr[4] - p` is the number of elements between the two pointers, so it is 4 - 1 = 3 (not 12 bytes).

   </details>

2. **`const` pointers:** After `int a = 1, b = 2; const int *p = &a; int *const q = &a;`, which of the four statements `*p = 5;`, `p = &b;`, `*q = 5;`, and `q = &b;` cause a compile error? Explain why.

   <details>
   <summary>Answer</summary>

   `*p = 5;` and `q = &b;` are errors. `p` is a read-only pointer, so the value cannot be changed through `p`, although `p` can be made to point to another variable. `q` is a dedicated pointer to `a`, so `a` can be changed through `*q`, but another address cannot be assigned to `q`.

   </details>

3. **Swap function:** Explain why trying to swap two values with `void swap(int x, int y)` does not change the variables in `main`, and write the correct prototype and call.

   <details>
   <summary>Answer</summary>

   In pass by value, `x` and `y` are local variables initialized with the argument values, so swapping the two parameters inside the function does not change the originals in `main`. The correct prototype is `void swap(int *px, int *py);`, and the call passes the addresses of the two variables, as in `swap(&a, &b);`. Inside the function, `*px` and `*py` are swapped using a temporary variable.

   </details>

4. **Arrays and `sizeof`:** On a 64-bit system, what are printed by `sizeof(data)` in `main`, where `int data[10];` is declared, and by `sizeof(arr)` inside `void f(int arr[])`? Assume a 4-byte `int`.

   <details>
   <summary>Answer</summary>

   In `main`, the total array size 10 × 4 = 40 is printed. The function parameter `int arr[]` is treated as `int *arr`, so inside `f` the pointer size 8 is printed. This is why a function that takes an array must receive the number of elements as a separate parameter.

   </details>

5. **Output parameters:** After calling `sec_to_hms(7384, &h, &m, &s)` from Section 3.3, what are the values of `h`, `m`, and `s`?

   <details>
   <summary>Answer</summary>

   `h = 7384 / 3600 = 2`, `m = (7384 % 3600) / 60 = 184 / 60 = 3`, and `s = 7384 % 60 = 4`. That is, 7384 seconds is 2 hours, 3 minutes, and 4 seconds.

   </details>

6. **Pointer trace:** Write the values of `a`, `b`, `*p`, and `*q` after executing `int a = 3, b = 7; int *p = &a, *q = &b; *q = *p * 2; q = p; *q += 1;`.

   <details>
   <summary>Answer</summary>

   `*q = *p * 2` makes `b` 6. `q = p` makes `q` point to `a`, and `*q += 1` makes `a` 4. Therefore `a` is 4, `b` is 6, and `*p` and `*q` both point to `a`, so they are 4.

   </details>

7. **Double pointer:** For `int x = 5, y = 8; int *p = &x; int **pp = &p;`, write the values of `x`, `y`, and `*p` after executing `**pp = **pp + 1; *pp = &y; **pp = 0;` in order.

   <details>
   <summary>Answer</summary>

   The first statement goes through `pp → p → x` and makes `x` 6. The second statement makes `p` point to `y`, and the third goes through `pp → p → y` and makes `y` 0. Therefore `x` is 6, `y` is 0, and `*p` is 0, the value of `y`.

   </details>

8. **Dangling pointer:** Explain why the following function is wrong, and correct it to do the same job. `int *make_ten(void) { int n = 10; return &n; }`

   <details>
   <summary>Answer</summary>

   `n` is a local variable, so it is destroyed when the function returns, and the returned address becomes a dangling pointer. If the purpose is to give back one value, return the value, as in `int make_ten(void) { return 10; }`; if the result must be placed in a variable of the caller, use an output parameter, as in `void make_ten(int *out) { *out = 10; }`.

   </details>
