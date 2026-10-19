# Chapter 8 — Pointers

[Repository Guide](../../README.md) | [English](Concepts_Lecture.md) | [한국어](Concepts_Lecture.ko.md)

> **Last Updated:** 2026-10-19
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
- [2. Arrays and Pointers](#2-arrays-and-pointers)
  - [2.1 Pointer Arithmetic](#21-pointer-arithmetic)
  - [2.2 Pointer as Array](#22-pointer-as-array)
  - [2.3 Array as Pointer](#23-array-as-pointer)
  - [2.4 Array vs Pointer Comparison](#24-array-vs-pointer-comparison)
- [3. Functions and Pointers](#3-functions-and-pointers)
  - [3.1 Pass by Value vs Pass by Reference](#31-pass-by-value-vs-pass-by-reference)
  - [3.2 Modifying a Variable Through a Pointer](#32-modifying-a-variable-through-a-pointer)
  - [3.3 Returning Multiple Values](#33-returning-multiple-values)
  - [3.4 Passing Arrays to Functions](#34-passing-arrays-to-functions)
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

```c
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

```c
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

| Declaration | Meaning | Can change `*p`? | Can change `p`? |
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

*Figure 3. Addresses of int array elements reached by pointer arithmetic*

| Pointer Type | `p + 1` Advances By |
|:-------------|:--------------------|
| `int *` | 4 bytes (`sizeof(int)`) |
| `double *` | 8 bytes (`sizeof(double)`) |
| `char *` | 1 byte (`sizeof(char)`) |

*Table 4. How far `p + 1` moves for each pointer type*

**Supported operations:**

| Operation | Meaning |
|:----------|:--------|
| `p + n` | Move forward by `n` elements |
| `p - n` | Move backward by `n` elements |
| `p++` | Advance to next element |
| `p--` | Move to previous element |
| `p1 - p2` | Number of elements between two pointers (not bytes) |

*Table 5. Operations allowed on pointers*

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

*Table 6. Correspondence between subscript notation and pointer notation*

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

*Table 7. Equivalences between array notation and pointer notation*

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

*Table 8. Comparison of an array and a pointer (with a 4-byte `int`)*

```c
int arr[5] = {1, 2, 3, 4, 5};
int *p = arr;

printf("%zu\n", sizeof(arr));   // 20 (5 * sizeof(int))
printf("%zu\n", sizeof(p));     // 8  (pointer size on 64-bit)

// arr++;   // ERROR
p++;        // OK: p now points to arr[1]
```

> **Key Point:** Although `arr` and `p` can be used interchangeably in many expressions (like `arr[i]` and `p[i]`), they are fundamentally different: an array name is a fixed starting address, like a pointer dedicated to one array, while `p` is a variable that can hold a different address at run time.

---

<br>

## 3. Functions and Pointers

### 3.1 Pass by Value vs Pass by Reference

| Method | Mechanism | Can modify original? |
|:-------|:----------|:---------------------|
| Pass by value | Function receives a **copy** of the argument | No |
| Pass by reference | Function receives the **address** via a pointer | Yes |

*Table 9. Pass by value and pass by reference*

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

*Figure 4. Comparison of pass by value and pass by reference*

> **Note:** Strictly speaking, C passes every argument by value; pass by reference is implemented by passing a pointer (address) by value. The textbook calls this method call by reference.

### 3.2 Modifying a Variable Through a Pointer

Why pass by reference is necessary can be seen from a function that adds 10 to the caller's variable.

**Wrong: pass by value (does NOT work)**

```c
void addTen_wrong(int x) {
    x = x + 10;
    // x is a local copy — original unchanged
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

*Figure 5. Behavior of addTen_wrong called by value*

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

*Figure 6. Behavior of addTen called by reference*

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

```c
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

*Table 10. Argument passing method by parameter role*

A function that returns its results through output parameters is written in the following order. (1) In the prototype, declare each output parameter as a pointer to the variable that will store the result. (2) When calling the function, prepare the variables that will receive the results and pass their addresses. (3) In the function definition, store the results where the pointer parameters point.

```c
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
