# Chapter 08 — Pointers

> **Last Updated:** 2026-03-16

---

## Table of Contents

- [1. Pointer Basics](#1-pointer-basics)
  - [1.1 Pointer Concept](#11-pointer-concept)
  - [1.2 Pointer Declaration](#12-pointer-declaration)
  - [1.3 Pointer Initialization](#13-pointer-initialization)
  - [1.4 Dereference Operator `*`](#14-dereference-operator-)
  - [1.5 Pointer Usage](#15-pointer-usage)
  - [1.6 `const` Pointer](#16-const-pointer)
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

---

<br>

## 1. Pointer Basics

### 1.1 Pointer Concept

Memory is a sequence of **contiguous bytes**, each with a unique **address**. A **pointer** is an address, and a **pointer variable** is a variable that stores an address.

```
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

| Architecture | Pointer Size | Address Range |
|:-------------|:-------------|:--------------|
| 32-bit | 4 bytes | `0x00000000` ~ `0xFFFFFFFF` |
| 64-bit | 8 bytes | `0x0000000000000000` ~ `0xFFFFFFFFFFFFFFFF` |

> **Key Point:** A pointer provides access to a variable via its address, even without knowing the variable's name. This is what makes pointers powerful.

### 1.2 Pointer Declaration

**Syntax:**

```c
type *pointer_name;
```

The `type` specifies what type of variable the pointer will point to. The `*` indicates it is a pointer variable.

```c
int *p;      // pointer to int
double *q;   // pointer to double
char *r;     // pointer to char
```

**`*` position does not matter — all three forms are identical:**

```c
int* p;    // OK
int *p;    // OK (recommended)
int * p;   // OK
```

> **Warning:** Use `int *p` style. With `int* p, q;`, only `p` is a pointer — `q` is a plain `int`. Writing `int *p, *q;` makes it clear both are pointers.

```c
int* p, q;    // p is int*, q is int   (misleading!)
int *p, *q;   // both p and q are int* (clear)
```

**Pointer size is the same regardless of the pointed-to type:**

```c
int *p;
double *q;
char *r;

printf("%zu\n", sizeof(p));  // 8 (on 64-bit)
printf("%zu\n", sizeof(q));  // 8 (on 64-bit)
printf("%zu\n", sizeof(r));  // 8 (on 64-bit)
```

All pointers occupy **4 bytes** on a 32-bit system and **8 bytes** on a 64-bit system, because they store an address, not the data itself.

### 1.3 Pointer Initialization

**The `&` (address-of) operator** returns the memory address of a variable.

```c
int a = 10;
int *p = &a;   // p now holds the address of a

printf("Address of a: %p\n", (void *)&a);   // e.g., 0x7ffee3c0
printf("Value of p:   %p\n", (void *)p);    // same address
```

**Restrictions on `&`:** The `&` operator works **only on variables** (lvalues). It cannot be applied to:

```c
&10        // ERROR: literal (no address)
&(a + 1)   // ERROR: expression result (temporary, no address)
#define MAX 100
&MAX       // ERROR: macro (replaced at preprocessing, no address)
```

**NULL pointer:** A pointer that points to nothing.

```c
int *q = NULL;   // explicitly points to nothing
int *r = 0;      // same as NULL
```

> **Tip:** Always initialize pointers. An uninitialized pointer holds a garbage address — dereferencing it causes **undefined behavior** (crash, data corruption, etc.).

**Format specifier `%p`** prints an address in hexadecimal:

```c
int x = 42;
int *p = &x;
printf("p = %p\n", (void *)p);   // p = 0x7ffee4b8 (example)
```

### 1.4 Dereference Operator `*`

The **dereference** (indirection) operator `*` accesses the value stored at the address held by the pointer. It can both **read** and **write**.

```c
int a = 10;
int *p = &a;

printf("%d\n", *p);   // 10 (read: get value at p's address)

*p = 20;               // write: change value at p's address
printf("%d\n", a);     // 20 (a was modified through p)
```

When `p` points to `a`, `*p` and `a` are **interchangeable names** for the same memory location:

```
   p ──────► ┌───────┐
             │  20   │  ← *p and a refer to the same location
             └───────┘
             address: 0x1000
```

**Restrictions on `*`:** The `*` operator works **only on pointer variables**. It cannot be applied to:

```c
int a = 10;
*a         // ERROR: a is not a pointer
*(a + 1)   // ERROR: (a + 1) is not a pointer
```

> **Key Point:** The `*` symbol has two meanings in pointer context: (1) in a declaration `int *p;` it means "p is a pointer", (2) in an expression `*p` it means "dereference p" (access the value at p's address).

### 1.5 Pointer Usage

Why use pointers? The textbook highlights two key situations:

| Situation | Explanation |
|:----------|:------------|
| Function needs to return 2+ values | C functions can only `return` one value. Pass addresses of variables so the function can modify them. |
| Passing arrays to functions | Arrays decay to pointers when passed. Pointers allow efficient array access without copying. |

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

### 1.6 `const` Pointer

The `const` keyword can restrict what a pointer can modify.

| Declaration | Meaning | Can change `*p`? | Can change `p`? |
|:------------|:--------|:-----------------|:----------------|
| `const int *p` | Pointer to const int | No | Yes |
| `int *const p` | Const pointer to int | Yes | No |
| `const int *const p` | Const pointer to const int | No | No |

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

> **Tip:** Read declarations **right to left**: `const int *p` = "p is a pointer to int that is const" (value is const). `int *const p` = "p is a const pointer to int" (pointer itself is const).

---

<br>

## 2. Arrays and Pointers

### 2.1 Pointer Arithmetic

When you add or subtract an integer to/from a pointer, the compiler scales by the **size of the pointed-to type**, not by 1 byte.

```c
int arr[5] = {10, 20, 30, 40, 50};
int *p = arr;    // p points to arr[0]
```

```
p     p+1    p+2    p+3    p+4
│      │      │      │      │
▼      ▼      ▼      ▼      ▼
┌──────┬──────┬──────┬──────┬──────┐
│  10  │  20  │  30  │  40  │  50  │
└──────┴──────┴──────┴──────┴──────┘
0x1000  0x1004  0x1008  0x100C  0x1010
        (+4B)   (+4B)   (+4B)   (+4B)
```

| Pointer Type | `p + 1` Advances By |
|:-------------|:--------------------|
| `int *` | 4 bytes (`sizeof(int)`) |
| `double *` | 8 bytes (`sizeof(double)`) |
| `char *` | 1 byte (`sizeof(char)`) |

**Supported operations:**

| Operation | Meaning |
|:----------|:--------|
| `p + n` | Move forward by `n` elements |
| `p - n` | Move backward by `n` elements |
| `p++` | Advance to next element |
| `p--` | Move to previous element |
| `p1 - p2` | Number of elements between two pointers |

```c
int arr[5] = {10, 20, 30, 40, 50};
int *p = arr;

printf("%d\n", *(p + 2));   // 30 (third element)

p++;
printf("%d\n", *p);         // 20 (second element)

int *q = &arr[4];
printf("%ld\n", q - p);     // 3 (distance in elements, not bytes)
```

> **Warning:** Pointer arithmetic is valid only within an array (or one past its end). Going beyond causes **undefined behavior**.

### 2.2 Pointer as Array

A pointer can use the **subscript operator `[]`** just like an array. The expression `p[i]` is identical to `*(p + i)`.

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

### 2.3 Array as Pointer

The **array name** is equivalent to the address of its first element. It acts as a **pointer constant**.

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

> **Warning:** The array name is a **constant** — it cannot be modified. You **cannot** do:
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

```c
int arr[5] = {1, 2, 3, 4, 5};
int *p = arr;

printf("%zu\n", sizeof(arr));   // 20 (5 * sizeof(int))
printf("%zu\n", sizeof(p));     // 8  (pointer size on 64-bit)

// arr++;   // ERROR
p++;        // OK: p now points to arr[1]
```

> **Key Point:** Although `arr` and `p` can be used interchangeably in many expressions (like `arr[i]` vs `p[i]`), they are fundamentally different: `arr` is a compile-time constant address, while `p` is a runtime variable that holds an address.

---

<br>

## 3. Functions and Pointers

### 3.1 Pass by Value vs Pass by Reference

| Method | Mechanism | Can modify original? |
|:-------|:----------|:---------------------|
| Pass by value | Function receives a **copy** of the argument | No |
| Pass by reference | Function receives the **address** via a pointer | Yes |

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

```
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

### 3.2 Modifying a Variable Through a Pointer

A simple demonstration of why pass-by-reference is necessary: a function that adds 10 to the caller's variable.

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

```
Before addTen_wrong:      Inside addTen_wrong:      After addTen_wrong:
  main: score=85           x=85→95                   main: score=85
         │                 (local copy)               (unchanged!)
         ▼
        copy
         │
         ▼
        x=85
```

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

```
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

> **Classic exercise:** Swapping two values is the most well-known application of this pattern. It requires two pointer parameters so the function can modify both caller variables. Try implementing it as practice!

### 3.3 Returning Multiple Values

Since C functions can only `return` a single value, use pointer parameters to "return" additional values.

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

### 3.4 Passing Arrays to Functions

When an array is passed to a function, the array name **decays** to a pointer to its first element. The function receives a pointer, not a copy of the array.

**Two equivalent function signatures:**

```c
void print_array(int *arr, int size);    // pointer syntax
void print_array(int arr[], int size);   // array syntax (same thing)
```

Both are identical — `int arr[]` in a function parameter is treated as `int *arr`.

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

> **Warning:** Inside the function, `sizeof(arr)` returns the **pointer size** (4 or 8), **not** the total array size. This is why the size must be passed as a separate parameter.

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

> **Tip:** If the function should **not** modify the array, declare the parameter as `const int *arr`. The compiler will prevent accidental writes.

---

<br>

## Summary

| Concept | Key Takeaway |
|:--------|:-------------|
| Pointer | An address; a pointer variable stores an address |
| Pointer declaration | `type *p;` — type = type of the variable being pointed to |
| Pointer size | Always 4 bytes (32-bit) or 8 bytes (64-bit), regardless of pointed type |
| `&` (address-of) | Returns address of a variable; cannot use on literals, expressions, macros |
| `*` (dereference) | Reads/writes the value at the address; only works on pointer variables |
| NULL pointer | `int *p = NULL;` — points to nothing; always initialize pointers |
| `%p` | Format specifier to print an address in hexadecimal |
| `const` pointer | `const int *p` (value const), `int *const p` (pointer const), or both |
| Pointer arithmetic | `p + 1` moves by `sizeof(*p)` bytes, not 1 byte |
| `p[i]` vs `*(p+i)` | Identical — subscript notation and pointer arithmetic are interchangeable |
| Array name | Address of first element; acts as a pointer **constant** (cannot be modified) |
| Array vs pointer | Array: fixed address, `sizeof` = total; Pointer: variable address, `sizeof` = 4/8 |
| Pass by value | Function gets a copy; original unchanged |
| Pass by reference | Function gets address via pointer; can modify original |
| Modify via pointer | Must pass address (`int *p`) — pass-by-value cannot modify the caller's variable |
| Multiple return values | Pass addresses to function; function writes via `*` |
| Array to function | Array decays to pointer; `sizeof(arr)` in function = pointer size; pass size separately |

---
