# Chapter 10 — Structures

> **Last Updated:** 2026-03-16

---

## Table of Contents

- [1. Structure Basics](#1-structure-basics)
  - [1.1 Structure Concept](#11-structure-concept)
  - [1.2 Structure Definition](#12-structure-definition)
  - [1.3 Structure Variable Declaration](#13-structure-variable-declaration)
  - [1.4 Structure Initialization](#14-structure-initialization)
  - [1.5 Member Access](#15-member-access)
  - [1.6 Structure Assignment](#16-structure-assignment)
  - [1.7 Structure Comparison](#17-structure-comparison)
- [2. Structure Applications](#2-structure-applications)
  - [2.1 Structure Arrays](#21-structure-arrays)
  - [2.2 Structure Pointers](#22-structure-pointers)
  - [2.3 Passing Structs to Functions](#23-passing-structs-to-functions)
  - [2.4 Nested Structures](#24-nested-structures)
- [3. Related Types](#3-related-types)
  - [3.1 `enum`](#31-enum)
  - [3.2 `union`](#32-union)
  - [3.3 `typedef`](#33-typedef)
- [Summary](#summary)

---

<br>

## 1. Structure Basics

### 1.1 Structure Concept

An **array** stores multiple values of the **same** type. A **structure** groups variables of **different** types under one name, forming a **user-defined data type**.

```
Array vs Structure
├── Array   : same type × N      → int scores[5];
└── Structure: different types × N → struct student { char name[20]; int age; double gpa; };
```

| Feature | Array | Structure |
|:--------|:------|:----------|
| Element types | All the same | Can be different |
| Access | Index `a[i]` | Member name `s.age` |
| User-defined | No (built-in) | Yes (`struct`) |
| Use case | Collection of same-type data | Record with mixed-type fields |

A structure is defined with the `struct` keyword. The definition must end with a **semicolon** after the closing brace `}`. Define structures **outside functions** (at file scope) so they are visible globally.

```c
struct content {
    char title[50];
    int price;
    double rate;
};              // <-- semicolon required!
```

### 1.2 Structure Definition

**Syntax:**

```c
struct tag_name {
    type1 member1;
    type2 member2;
    // ...
};
```

- **Tag name:** Distinguishes one struct from another. The **full type name** is `struct tag_name` — the `struct` keyword is mandatory.
- **Members** (component variables): The individual variables inside the struct.

```c
struct content {
    char title[50];    // member 1
    int price;         // member 2
    double rate;       // member 3
};
```

> **Warning:** Using just the tag name without `struct` causes a **compile error**:
> ```c
> content c1;          // compile error!
> struct content c1;   // correct
> ```

**Size and alignment:**

The size of a struct is **at least** the sum of its member sizes, but may be larger due to **padding/alignment** inserted by the compiler for efficient memory access.

```c
struct example {
    char c;      // 1 byte
    int n;       // 4 bytes
    double d;    // 8 bytes
};
// Sum = 13 bytes, but sizeof(struct example) may be 16 or 24 (with padding)

printf("Size: %zu\n", sizeof(struct example));  // likely 16 or 24
```

```
Memory layout (with possible padding):
┌─────┬─────────┬──────────┬──────────────────┐
│  c  │ padding │    n     │        d         │
│ 1B  │   3B    │    4B    │        8B        │
└─────┴─────────┴──────────┴──────────────────┘
sizeof(struct example) = 16  (not 13)
```

> **Key Point:** `sizeof(struct tag)` >= sum of member sizes. The compiler may insert padding bytes between members for alignment.

### 1.3 Structure Variable Declaration

Once a structure is defined, variables of that type can be declared:

```c
struct content c1, c2, c3;   // declare three variables
```

Variables can also be declared **together with the definition**:

```c
struct content {
    char title[50];
    int price;
    double rate;
} c1, c2;                    // define struct AND declare c1, c2
```

**Anonymous struct** (no tag name):

```c
struct {
    char title[50];
    int price;
    double rate;
} c1;                        // works, but cannot declare more variables of this type later
```

> **Warning:** An anonymous struct has no tag name, so you **cannot reuse** it to declare additional variables elsewhere.

**Memory allocation:** Members are allocated in **declaration order** in contiguous memory.

```
struct content c1;

┌────────────────────────┬──────────┬────────────────┐
│        c1.title        │ c1.price │     c1.rate    │
│        (50 bytes)      │ (4 bytes)│    (8 bytes)   │
└────────────────────────┴──────────┴────────────────┘
         (may include padding between members)
```

### 1.4 Structure Initialization

Use an **initializer list** in `{}` following the **member declaration order**:

```c
struct content c1 = {"Avengers", 11000, 8.8};
```

| Initializer | `title` | `price` | `rate` |
|:------------|:--------|:--------|:-------|
| `{"Avengers", 11000, 8.8}` | `"Avengers"` | `11000` | `8.8` |

**Partial initialization** — remaining members are filled with **0**:

```c
struct content c2 = {"Inception"};
// c2.title = "Inception", c2.price = 0, c2.rate = 0.0
```

**Too many initializers** — compile error:

```c
struct content c3 = {"Matrix", 9000, 9.1, 100};  // compile error!
```

**Initialize from another struct variable:**

```c
struct content c1 = {"Avengers", 11000, 8.8};
struct content c2 = c1;   // copies all members from c1 to c2
```

### 1.5 Member Access

Use the **dot operator** (`.`) to access members through a struct variable:

```c
struct content c1 = {"Avengers", 11000, 8.8};

c1.rate = 8.9;                      // modify a member
c1.price *= 0.8;                    // compound assignment on a member
strcat(c1.title, ": Endgame");      // string operation on a member
printf("Title: %s\n", c1.title);    // read a member
```

> **Key Point:** Members can **only** be accessed through a struct variable. You cannot use a member name on its own — `title` alone does not refer to `c1.title`.

```c
// title = "Test";       // compile error — title is not a standalone variable
c1.title;                // correct — access through the struct variable
```

### 1.6 Structure Assignment

After declaration, one struct can be **assigned** to another of the same type. This copies **all members** one-by-one:

```c
struct content c1 = {"Avengers", 11000, 8.8};
struct content c3;

c3 = c1;   // copies title, price, and rate from c1 to c3
```

**Restrictions:**

You **cannot** use an initializer list `{}` after declaration (only at the point of declaration):

```c
struct content c3;
c3 = {"Matrix", 9000, 9.1};    // compile error!
```

Array members **cannot** be assigned directly — use `strcpy` instead:

```c
struct content c1 = {"Avengers", 11000, 8.8};
struct content c3;

// c3.title = c1.title;         // compile error — arrays cannot be assigned!
strcpy(c3.title, c1.title);     // correct — use strcpy for strings
c3.price = c1.price;            // OK — non-array members can be assigned
c3.rate = c1.rate;              // OK
```

> **Tip:** Whole-struct assignment `c3 = c1` works and copies array members correctly (member-by-member byte copy). The restriction only applies to assigning **individual** array members like `c3.title = c1.title`.

### 1.7 Structure Comparison

You **cannot** use `==` or `!=` to compare two structs directly:

```c
struct content c1 = {"Avengers", 11000, 8.8};
struct content c2 = c1;

// if (c1 == c2) { ... }     // compile error!
```

Instead, compare **member by member**. For string members, use `strcmp`:

```c
if (strcmp(c1.title, c2.title) == 0 &&
    c1.price == c2.price &&
    c1.rate == c2.rate) {
    printf("c1 and c2 are equal\n");
}
```

> **Warning:** Comparing structs with `==` is a compile error in C. You **must** compare each member individually. Use `strcmp` for string (char array) members — do not use `==` on strings.

---

<br>

## 2. Structure Applications

### 2.1 Structure Arrays

An **array of structs** stores multiple records of the same structure type:

```c
struct content movies[10];
```

Access members using the array index and the dot operator:

```c
movies[0].price = 12000;
strcpy(movies[0].title, "Avengers");
movies[0].rate = 8.8;
```

**Initialization with nested braces:**

```c
struct content movies[3] = {
    {"Avengers", 11000, 8.8},
    {"Inception", 9000, 9.2},
    {"Parasite", 10000, 9.5}
};
```

**Looping through a struct array:**

```c
for (int i = 0; i < 3; i++) {
    printf("%-15s %6d %5.1f\n",
           movies[i].title, movies[i].price, movies[i].rate);
}
```

**Sorting a struct array (by rate, descending — selection sort):**

```c
for (int i = 0; i < n - 1; i++) {
    int max_idx = i;
    for (int j = i + 1; j < n; j++) {
        if (movies[j].rate > movies[max_idx].rate) {
            max_idx = j;
        }
    }
    if (max_idx != i) {
        struct content temp = movies[i];
        movies[i] = movies[max_idx];
        movies[max_idx] = temp;
    }
}
```

> **Tip:** To swap two struct variables, use a temporary variable of the same struct type. Whole-struct assignment copies all members.

### 2.2 Structure Pointers

A **pointer to a struct** stores the address of a struct variable:

```c
struct content c1 = {"Avengers", 11000, 8.8};
struct content *p = &c1;
```

Access members through a pointer using the **arrow operator** (`->`):

```c
printf("Title: %s\n", p->title);     // arrow operator
printf("Price: %d\n", p->price);
printf("Rate: %.1f\n", p->rate);
```

The arrow operator `->` is equivalent to dereferencing with `(*p).member`:

```c
p->title      // equivalent to (*p).title
p->price      // equivalent to (*p).price
p->rate       // equivalent to (*p).rate
```

> **Warning:** Parentheses are required in `(*p).title` because the dot `.` has higher precedence than `*`. Without parentheses, `*p.title` is interpreted as `*(p.title)`, which is wrong if `p` is a pointer to a struct.

```
 p ──────► ┌───────────────────────┐
           │ c1.title = "Avengers" │
           │ c1.price = 11000      │
           │ c1.rate  = 8.8        │
           └───────────────────────┘

p->title   ≡  (*p).title   ≡  c1.title
```

### 2.3 Passing Structs to Functions

**Pass by value** — the function receives a **copy**:

```c
void display(struct content c) {
    printf("%s %d %.1f\n", c.title, c.price, c.rate);
    c.price = 0;   // modifies the copy only — original unchanged
}

int main() {
    struct content c1 = {"Avengers", 11000, 8.8};
    display(c1);    // passes a copy
    printf("Price: %d\n", c1.price);  // still 11000
    return 0;
}
```

**Pass by pointer** — the function can **modify the original**:

```c
void discount(struct content *p, double rate) {
    p->price *= rate;   // modifies the original struct
}

int main() {
    struct content c1 = {"Avengers", 11000, 8.8};
    discount(&c1, 0.8);
    printf("Price: %d\n", c1.price);  // 8800
    return 0;
}
```

**Passing a struct array** — arrays always decay to pointers:

```c
void display_all(const struct content arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%-15s %6d %5.1f\n",
               arr[i].title, arr[i].price, arr[i].rate);
    }
}

int main() {
    struct content movies[3] = {
        {"Avengers", 11000, 8.8},
        {"Inception", 9000, 9.2},
        {"Parasite", 10000, 9.5}
    };
    display_all(movies, 3);
    return 0;
}
```

> **Key Point:** Use `const` in the parameter when the function should **not** modify the struct. This documents intent and prevents accidental changes.

**Input function using a pointer:**

```c
void input_content(struct content *p) {
    printf("Title: ");
    scanf("%s", p->title);
    printf("Price: ");
    scanf("%d", &p->price);
    printf("Rate: ");
    scanf("%lf", &p->rate);
}
```

### 2.4 Nested Structures

A structure can contain another structure as a member:

```c
struct date {
    int year;
    int month;
    int day;
};

struct student {
    char name[20];
    int id;
    struct date birthday;   // nested struct
};
```

**Initialization:**

```c
struct student s1 = {"Kim", 2024001, {2005, 3, 15}};
```

**Access nested members** with chained dot operators:

```c
printf("Name: %s\n", s1.name);
printf("Birthday: %d-%02d-%02d\n",
       s1.birthday.year, s1.birthday.month, s1.birthday.day);
```

**With pointers:**

```c
struct student *p = &s1;
printf("Year: %d\n", p->birthday.year);   // pointer->outer.inner
```

```
struct student s1

┌───────────────────────────────┐
│ name = "Kim"                  │
│ id = 2024001                  │
│ birthday ┌─────────────────┐  │
│          │ year  = 2005    │  │
│          │ month = 3       │  │
│          │ day   = 15      │  │
│          └─────────────────┘  │
└───────────────────────────────┘
```

---

<br>

## 3. Related Types

### 3.1 `enum`

An **enumeration** defines a set of named **integer constants**:

```c
enum color { RED, GREEN, BLUE };
```

By default, values start at **0** and increment by 1:

| Name | Default Value |
|:-----|:--------------|
| `RED` | `0` |
| `GREEN` | `1` |
| `BLUE` | `2` |

You can assign **custom values**:

```c
enum color { RED = 1, GREEN = 5, BLUE = 10 };
```

If only some values are assigned, subsequent ones continue from the last assigned value:

```c
enum level { LOW = 1, MEDIUM, HIGH };
// LOW = 1, MEDIUM = 2, HIGH = 3
```

**Usage:**

```c
enum color c = RED;

switch (c) {
case RED:
    printf("Red\n");
    break;
case GREEN:
    printf("Green\n");
    break;
case BLUE:
    printf("Blue\n");
    break;
}
```

> **Tip:** Use `enum` instead of `#define` for related constants. The compiler can provide better type checking and debugging support.

### 3.2 `union`

A **union** looks like a struct but **shares memory** among all members. Only **one member** is valid at a time, and the size of the union equals the size of its **largest member**.

```c
union data {
    int i;
    float f;
    char c;
};

printf("Size: %zu\n", sizeof(union data));  // 4 (size of int or float)
```

```
union data d;

┌──────────────────┐
│   i (4 bytes)    │  ← all three members
│   f (4 bytes)    │    share the same
│   c (1 byte)     │    memory location
└──────────────────┘
sizeof(union data) = 4  (largest member)
```

```c
union data d;
d.i = 42;
printf("i = %d\n", d.i);    // 42

d.f = 3.14;
printf("f = %.2f\n", d.f);  // 3.14
printf("i = %d\n", d.i);    // garbage — overwritten by d.f!
```

> **Warning:** Writing to one member of a union overwrites all other members. Only the **last written** member contains a valid value.

### 3.3 `typedef`

`typedef` creates an **alias** (alternative name) for an existing type:

```c
typedef unsigned int uint;
typedef int BOOL;

uint count = 100;     // same as: unsigned int count = 100;
BOOL flag = 1;        // same as: int flag = 1;
```

**Most common use — simplifying struct declarations:**

```c
typedef struct point {
    int x;
    int y;
} Point;

Point p1 = {10, 20};         // no need for "struct point"
Point p2 = {30, 40};
```

This is equivalent to:

```c
struct point {
    int x;
    int y;
};
typedef struct point Point;
```

Without `typedef`, you must always write `struct point`:

```c
struct point p1 = {10, 20};   // verbose
Point p1 = {10, 20};          // concise — with typedef
```

> **Key Point:** `typedef` does **not** create a new type — it creates a new **name** for an existing type. `Point` and `struct point` are the same type.

---

<br>

## Summary

| Concept | Key Takeaway |
|:--------|:-------------|
| Structure | Groups variables of **different types** under one name; user-defined type |
| `struct` vs Array | Array = same type; struct = different types |
| Definition | `struct tag { members };` — semicolon after `}`; define at file scope |
| Tag name | Full type name is `struct tag_name`; using tag alone without `struct` is a compile error |
| Size | `sizeof(struct tag)` >= sum of member sizes (padding/alignment) |
| Declaration | `struct tag var1, var2;` — members allocated in declaration order |
| Anonymous struct | No tag name; cannot reuse the type later |
| Initialization | `struct tag v = {val1, val2, ...};` in member order; partial init fills rest with 0 |
| Copy init | `struct tag c2 = c1;` copies all members |
| Member access | Dot operator: `c1.rate`, `c1.title`; only through struct variable |
| Assignment | `c3 = c1` copies all members; cannot use `{}` after declaration; individual array members need `strcpy` |
| Comparison | Cannot use `==`/`!=` on structs; compare member by member; use `strcmp` for strings |
| Struct arrays | `struct tag arr[N];` — access with `arr[i].member` |
| Struct pointers | `struct tag *p = &c1;` — access with `p->member` or `(*p).member` |
| Arrow operator | `p->member` equivalent to `(*p).member`; parentheses required in `(*p)` |
| Pass by value | Function gets a copy; original unchanged |
| Pass by pointer | Function can modify original; use `const` for read-only |
| Nested structs | Struct member inside another struct; access with `outer.inner.field` |
| `enum` | Named integer constants; default values start at 0, increment by 1 |
| `union` | Shared memory for all members; size = largest member; one valid at a time |
| `typedef` | Creates alias for a type; commonly used with structs to avoid `struct` keyword |

---
