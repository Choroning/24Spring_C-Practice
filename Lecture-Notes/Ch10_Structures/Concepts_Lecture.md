# Chapter 10 — Structures

[Repository Guide](../../README.md) | [English](Concepts_Lecture.md) | [한국어](Concepts_Lecture.ko.md)

> **Last Updated:** 2026-10-19
>
> Warming-Up C Programming, 천정아, Ch 10

> **Learning Objectives:**
> 1. Define a structure and declare, initialize, and assign structure variables
> 2. Explain why padding and alignment can make a structure larger than the sum of its member sizes
> 3. Access the members of structure variables and structure pointers with the dot and arrow operators
> 4. Traverse, search, and sort structure arrays and pass structures to functions by value or by pointer
> 5. Explain the uses and characteristics of nested structures, `enum`, `union`, and `typedef`

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
- [Self-Check Questions](#self-check-questions)

---

<br>

## 1. Structure Basics

### 1.1 Structure Concept

An **array** stores multiple values of the **same** type. A **structure** groups variables of **different** types under one name, forming a **user-defined data type**. In C, the structure is the way to create user-defined types.

```text
Array vs Structure
├── Array   : same type × N      → int scores[5];
└── Structure: different types × N → struct student { char name[20]; int age; double gpa; };
```

*Figure 1. An array grouping one type and a structure grouping different types*

| Feature | Array | Structure |
|:--------|:------|:----------|
| Element types | All the same | Can be different |
| Access | Index `a[i]` | Member name `s.age` |
| User-defined | No (built-in) | Yes (`struct`) |
| Use case | Collection of same-type data | Record with mixed-type fields |

*Table 1. Comparison of arrays and structures*

A structure is defined with the `struct` keyword. The definition must end with a **semicolon** after the closing brace `}`. To use a structure in several functions, define it **outside functions** (at file scope), preferably at the beginning of the source file.

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

- **Tag name:** It distinguishes one struct from another. The **full type name** is `struct tag_name`, and the `struct` keyword is mandatory.
- **Members** (component variables): They are the individual variables that make up the struct.

```c
struct content {
    char title[50];    // member 1
    int price;         // member 2
    double rate;       // member 3
};
```

Defining a structure only creates a new data type; it does not create a structure variable. A structure variable is allocated in memory only when a variable of the structure type is declared.

> **Caution:** Using just the tag name without `struct` causes a **compile error**, because the compiler cannot tell that `content` is a structure name.
> ```c
> content c1;          // compile error!
> struct content c1;   // correct
> ```

**Size and alignment:**

The size of a struct is **at least** the sum of its member sizes, but may be larger due to **padding/alignment** bytes inserted by the compiler between or after members for efficient memory access.

```c
struct example {
    char c;      // 1 byte
    int n;       // 4 bytes
    double d;    // 8 bytes
};
// Sum = 13 bytes, but sizeof(struct example) may be 16 or 24 (with padding)

printf("Size: %zu\n", sizeof(struct example));  // likely 16 or 24
```

```text
Memory layout (with possible padding):
┌─────┬─────────┬──────────┬──────────────────┐
│  c  │ padding │    n     │        d         │
│ 1B  │   3B    │    4B    │        8B        │
└─────┴─────────┴──────────┴──────────────────┘
sizeof(struct example) = 16  (not 13)
```

*Figure 2. Memory layout of `struct example` including padding (typical 64-bit system)*

On a typical 64-bit system, an `int` is placed at an address that is a multiple of 4 and a `double` at a multiple of 8, so 3 bytes are filled after `c` and the size becomes 16. If the members are reordered as `char c; double d; int n;`, 7 bytes are filled after `c` and 4 bytes after `n`, giving a size of 24; the same members can thus yield different sizes depending on the declaration order.

> **Key Point:** `sizeof(struct tag)` >= sum of member sizes. The compiler may insert padding bytes between members for alignment.

### 1.3 Structure Variable Declaration

Once a structure is defined, variables of that type can be declared.

```c
struct content c1, c2, c3;   // declare three variables
```

Variables can also be declared **together with the definition**.

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

> **Caution:** An anonymous struct has no tag name, so you **cannot reuse** it to declare additional variables elsewhere.

**Memory allocation:** Members are allocated one after another in memory in **declaration order**.

```text
struct content c1;

┌────────────────────────┬──────────┬────────────────┐
│        c1.title        │ c1.price │     c1.rate    │
│        (50 bytes)      │ (4 bytes)│    (8 bytes)   │
└────────────────────────┴──────────┴────────────────┘
         (may include padding between members)
```

*Figure 3. Members of structure variable c1 allocated in declaration order*

### 1.4 Structure Initialization

Use an **initializer list** in `{}` following the **member declaration order**.

```c
struct content c1 = {"Avengers", 11000, 8.8};
```

| Initializer | `title` | `price` | `rate` |
|:------------|:--------|:--------|:-------|
| `{"Avengers", 11000, 8.8}` | `"Avengers"` | `11000` | `8.8` |

*Table 2. Members matched by the values of the initializer list*

**Partial initialization:** If there are too few initializers, the remaining members are filled with **0**.

```c
struct content c2 = {"Inception"};
// c2.title = "Inception", c2.price = 0, c2.rate = 0.0
```

**Too many initializers:** There must not be more initializers than members. Such code violates the standard, so the compiler issues a diagnostic; Visual Studio treats it as a compile error, while gcc and clang by default issue a warning and discard the extra values.

```c
struct content c3 = {"Matrix", 9000, 9.1, 100};  // compile error!
```

**Initialize from another struct variable:** The members are copied one-to-one.

```c
struct content c1 = {"Avengers", 11000, 8.8};
struct content c2 = c1;   // copies all members from c1 to c2
```

### 1.5 Member Access

Use the **dot operator** (`.`, the member access operator) to access members through a struct variable.

```c
struct content c1 = {"Avengers", 11000, 8.8};

c1.rate = 8.9;                      // modify a member
c1.price *= 0.8;                    // compound assignment on a member
strcat(c1.title, ": Endgame");      // string operation on a member
printf("Title: %s\n", c1.title);    // read a member
```

> **Key Point:** Members can **only** be accessed through a struct variable. You cannot use a member name on its own, and `title` alone does not refer to `c1.title`. If there is an ordinary variable with the same name, `title` refers to that variable.

```c
// title = "Test";       // compile error — title is not a standalone variable
c1.title;                // correct — access through the struct variable
```

When several structure variables are declared, they are allocated in different memory, and the members are allocated separately for each structure variable. Because members are always accessed through a structure variable, it is clear whose member is being used.

### 1.6 Structure Assignment

After declaration, one struct can be **assigned** to another of the same type. This copies **all members** one-to-one.

```c
struct content c1 = {"Avengers", 11000, 8.8};
struct content c3;

c3 = c1;   // copies title, price, and rate from c1 to c3
```

**Restrictions:**

You **cannot** use an initializer list `{}` after declaration (only at the point of declaration).

```c
struct content c3;
c3 = {"Matrix", 9000, 9.1};    // compile error!
```

Array members **cannot** be assigned to each other directly, so `strcpy` must be used for strings.

```c
struct content c1 = {"Avengers", 11000, 8.8};
struct content c3;

// c3.title = c1.title;         // compile error — arrays cannot be assigned!
strcpy(c3.title, c1.title);     // correct — use strcpy for strings
c3.price = c1.price;            // OK — non-array members can be assigned
c3.rate = c1.rate;              // OK
```

> **Note:** **Tip.** Whole-struct assignment `c3 = c1` works and copies array members correctly (the whole struct is copied byte by byte). The restriction only applies to assigning **individual** array members like `c3.title = c1.title`.

### 1.7 Structure Comparison

Relational operators cannot be applied to structure variables, so you **cannot** use `==` or `!=` to compare two structs directly.

```c
struct content c1 = {"Avengers", 11000, 8.8};
struct content c2 = c1;

// if (c1 == c2) { ... }     // compile error!
```

Instead, compare **member by member**. For string members, use `strcmp`.

```c
if (strcmp(c1.title, c2.title) == 0 &&
    c1.price == c2.price &&
    c1.rate == c2.rate) {
    printf("c1 and c2 are equal\n");
}
```

> **Caution:** Comparing structs with `==` is a compile error in C. You **must** compare each member individually. Use `strcmp` for string (char array) members, and do not use `==` on strings. The values of padding bytes and of bytes after a string's null character are unspecified, so comparing whole structs with `memcmp` is not reliable either.

---

<br>

## 2. Structure Applications

### 2.1 Structure Arrays

An **array of structs** stores multiple records of the same structure type. The elements of a structure array are also allocated contiguously in memory.

```c
struct content movies[10];
```

Access members using the array index and the dot operator. Since `movies[i]` is a structure variable, write `movies[i].member`.

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

**Searching a struct array:** The program reads the title to search for and leaves the `for` loop with `break` when it finds an element with the same title. After the loop, if `i` is less than the array size, `i` is the index of the found element; if it equals the array size, the search failed.

```c
char title[50];
int i;

printf("Title to search: ");
scanf("%s", title);
for (i = 0; i < 3; i++) {
    if (strcmp(movies[i].title, title) == 0)
        break;                    // leave the loop when found (i is the index found)
}
if (i < 3)
    printf("Price: %d, Rate: %.1f\n", movies[i].price, movies[i].rate);
else
    printf("No matching content.\n");
```

**Sorting a struct array (by rate, descending, selection sort):**

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

> **Note:** **Tip.** To swap two struct variables, use a temporary variable of the same struct type. Whole-struct assignment copies all members.

### 2.2 Structure Pointers

A **pointer to a struct** stores the address of a struct variable.

```c
struct content c1 = {"Avengers", 11000, 8.8};
struct content *p = &c1;
```

Access members through a pointer using the **arrow operator** (`->`, the indirect member access operator).

```c
printf("Title: %s\n", p->title);     // arrow operator
printf("Price: %d\n", p->price);
printf("Rate: %.1f\n", p->rate);
```

The arrow operator `->` is equivalent to dereferencing with `(*p).member`.

```c
p->title      // equivalent to (*p).title
p->price      // equivalent to (*p).price
p->rate       // equivalent to (*p).rate
```

> **Caution:** Parentheses are required in `(*p).title` because the dot `.` has higher precedence than `*`. Without parentheses, `*p.title` is interpreted as `*(p.title)`, which is wrong if `p` is a pointer to a struct.

```text
 p ──────► ┌───────────────────────┐
           │ c1.title = "Avengers" │
           │ c1.price = 11000      │
           │ c1.rate  = 8.8        │
           └───────────────────────┘

p->title   ≡  (*p).title   ≡  c1.title
```

*Figure 4. Structure pointer p pointing to structure variable c1*

To access a structure variable read-only, declare a `const` pointer such as `const struct content *p = &c1;`. Through this pointer, `p->price` can only be read, and changing a member, as in `p->price = 0;`, is a compile error.

### 2.3 Passing Structs to Functions

A structure can be passed to a function either by value or by pointer.

**Pass by value:** The function receives a **copy**.

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

**Pass by pointer:** The function can **modify the original**.

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

Passing a structure by value copies the whole structure, which costs time and memory. A small structure, such as a coordinate structure of two `int` values, can be passed by value with almost no performance loss, but a large structure such as `content` is better passed by address. Pass a structure by pointer when it is an output or input/output parameter or when it should be passed without copying, and pass it by `const` pointer when it is an input parameter.

**Passing a struct array:** Arrays always decay to pointers.

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

Passing a structure as a function argument can be summarized as follows. (1) Declare the function parameter as a structure pointer. (2) If the structure variable is an input parameter, add `const`. (3) When calling the function, pass the address of the structure variable as the argument. (4) In the function definition, access the members through the structure pointer with `->`.

### 2.4 Nested Structures

A structure can contain another structure as a member. The structure used as a member (`date`) must be defined before the structure that contains it (`student`).

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

**Accessing nested members:** Use the dot operator repeatedly.

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

```text
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

*Figure 5. Structure variable s1 containing a `struct date` member*

`s1.birthday` can itself be used like a variable of type `struct date`.

---

<br>

## 3. Related Types

### 3.1 `enum`

An **enumeration** defines a set of named **integer constants**. When an integer variable takes one of a few specific values, those values are defined as enumeration constants, and an enumeration is also a kind of user-defined type.

```c
enum color { RED, GREEN, BLUE };
```

By default, values start at **0** and increment by 1.

| Name | Default Value |
|:-----|:--------------|
| `RED` | `0` |
| `GREEN` | `1` |
| `BLUE` | `2` |

*Table 3. Default values of enumeration constants*

You can assign **custom values**.

```c
enum color { RED = 1, GREEN = 5, BLUE = 10 };
```

If only some values are assigned, subsequent ones increase by 1 from the last assigned value.

```c
enum level { LOW = 1, MEDIUM, HIGH };
// LOW = 1, MEDIUM = 2, HIGH = 3
```

The C compiler treats an enumeration as type `int` and defines the enumeration constants as integer constants. So printing the value of an enumeration variable with `%d` prints an integer, and enumeration constants can be used in the `case` labels of a `switch` statement. Like a structure, an enumeration must be used as `enum tag_name`, and the tag name can be omitted to define only the enumeration constants.

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

> **Note:** **Tip.** Use `enum` instead of `#define` for related constants. A macro constant is replaced by its value by the preprocessor, so the compiler and the debugger never see its name, whereas an enumeration constant is a name the compiler handles. Enumeration constants in C are `int` constants, so type checking is not strict, but `enum` groups related constants in one place to show their meaning, lets the debugger show names instead of values, and allows gcc and clang to warn about enumeration constants not handled in a `switch` statement (`-Wswitch`).

### 3.2 `union`

A **union** looks like a struct but **shares memory** among all members. All members of a union are allocated at the same address, so changing the value of one member changes the others as well. Only **one member** holds a meaningful value at a time, and the size of the union is large enough to hold its **largest member**.

```c
union data {
    int i;
    float f;
    char c;
};

printf("Size: %zu\n", sizeof(union data));  // 4 (size of int or float)
```

```text
union data d;

┌──────────────────┐
│   i (4 bytes)    │  ← all three members
│   f (4 bytes)    │    share the same
│   c (1 byte)     │    memory location
└──────────────────┘
sizeof(union data) = 4  (largest member)
```

*Figure 6. Union variable d whose three members share the same memory*

The size of a union usually equals the size of its largest member, but alignment can make it larger. For example, `union { char s[5]; int i; }` has a largest member of 5 bytes, but its size is 8 to satisfy the alignment of `int`. When initializing a union, give only the initial value of the first member in `{}` (`union data d = {42};` initializes `d.i`). Members are accessed with `.` as in a structure, and with `->` through a union pointer.

```c
union data d;
d.i = 42;
printf("i = %d\n", d.i);    // 42

d.f = 3.14;
printf("f = %.2f\n", d.f);  // 3.14
printf("i = %d\n", d.i);    // garbage — overwritten by d.f!
```

The last line prints a meaningless value, but not a random one. It prints `1078523331`, the IEEE 754 single-precision bit pattern `0x4048F5C3` of `3.14f` stored in `d.f`, reinterpreted as an `int` (on typical systems where `int` and `float` are both 4 bytes). The C standard specifies that reading a member other than the one last written reinterprets those bytes as the new type.

> **Caution:** Writing to one member of a union overwrites all other members. Only the **last written** member holds a meaningful value.

### 3.3 `typedef`

`typedef` creates an **alias** (alternative name) for an existing type.

```c
typedef unsigned int uint;
typedef int BOOL;

uint count = 100;     // same as: unsigned int count = 100;
BOOL flag = 1;        // same as: int flag = 1;
```

**The most common use is simplifying struct declarations.** Preparing a name with `typedef` to use instead of `struct tag_name` when defining a structure makes the structure convenient to use.

```c
typedef struct point {
    int x;
    int y;
} Point;

Point p1 = {10, 20};         // no need for "struct point"
Point p2 = {30, 40};
```

This is equivalent to the following.

```c
struct point {
    int x;
    int y;
};
typedef struct point Point;
```

Without `typedef`, you must always write `struct point`. Even after the `typedef` is defined, the original type name `struct point` can still be used.

```c
struct point p1 = {10, 20};   // verbose
Point p1 = {10, 20};          // concise — with typedef
```

> **Key Point:** `typedef` does **not** create a new type; it creates a new **name** for an existing type. `Point` and `struct point` are the same type.

---

<br>

## Summary

| Concept | Key Summary |
|:--------|:------------|
| Structure | It is a user-defined type that groups variables of **different types** under one name. |
| `struct` vs Array | An array groups values of the same type, while a struct groups different types. |
| Definition | A structure is defined as `struct tag { members };`, the semicolon after `}` is required, and it is usually defined at file scope. |
| Tag name | The full type name is `struct tag_name`, and using the tag alone without `struct` is a compile error. |
| Size | Because of padding and alignment, `sizeof(struct tag)` is at least the sum of the member sizes. |
| Declaration | Variables are declared as `struct tag var1, var2;`, and members are allocated in declaration order. |
| Anonymous struct | It has no tag name, so the type cannot be reused later. |
| Initialization | A structure is initialized in member order, as in `struct tag v = {val1, val2, ...};`, and partial initialization fills the rest with 0. |
| Copy init | `struct tag c2 = c1;` initializes `c2` by copying all members. |
| Member access | Members are accessed with the dot operator, as in `c1.rate` and `c1.title`, and only through a struct variable. |
| Assignment | `c3 = c1` copies all members, but `{}` cannot be used after declaration and individual array members need `strcpy`. |
| Comparison | `==` and `!=` cannot be used on structs, so they are compared member by member, with `strcmp` for string members. |
| Struct arrays | They are declared as `struct tag arr[N];`, accessed with `arr[i].member`, and used for searching and sorting. |
| Struct pointers | A pointer is declared as `struct tag *p = &c1;` and members are accessed with `p->member` or `(*p).member`. |
| Arrow operator | `p->member` is equivalent to `(*p).member`, and the parentheses in `(*p)` are required. |
| Pass by value | The function gets a copy, so the original is unchanged, but copying a large structure is costly. |
| Pass by pointer | The function can modify the original, and a `const` pointer is used for read-only access. |
| Nested structs | A structure holds another structure as a member, accessed with `outer.inner.field`. |
| `enum` | It is a set of named `int` constants whose default values start at 0 and increase by 1. |
| `union` | All members share the same memory, so its size is enough for the largest member and only the last written member holds a meaningful value. |
| `typedef` | It gives an alias to an existing type, and with structs it lets the `struct` keyword be omitted. |

---

<br>

## Self-Check Questions

1. **Padding:** On a typical 64-bit system, what are the `sizeof` values of `struct A { char c; int n; double d; };` and `struct B { char c; double d; int n; };`? Explain why.

   <details>
   <summary>Answer</summary>

   `struct A` is 16 and `struct B` is 24. In `A`, 3 bytes are filled after `c` (1 byte) to place the `int` at a multiple of 4, and `d` is placed at offset 8 where `n` ends, giving 1 + 3 + 4 + 8 = 16. In `B`, 7 bytes are filled after `c` to place `d` at a multiple of 8, and 4 bytes are filled after `n` to make the whole size a multiple of the largest alignment, 8, giving 1 + 7 + 8 + 4 + 4 = 24.

   </details>

2. **Arrow operator:** Given `struct content c1; struct content *p = &c1;`, explain why `*p.price` is an error and write two correct expressions that access `c1.price`.

   <details>
   <summary>Answer</summary>

   `.` has higher precedence than `*`, so `*p.price` is interpreted as `*(p.price)`, and `p.price` is invalid because `p` is a pointer, not a structure. The correct expressions are `(*p).price` and `p->price`.

   </details>

3. **Union:** For `union data { int i; float f; char c; } d;`, what is `sizeof(union data)`, and why is `d.i` not 42 when read after `d.i = 42; d.f = 3.14;`?

   <details>
   <summary>Answer</summary>

   The size is 4 bytes, the size of the largest members `int` and `float`. Because the three members share the same memory, writing `d.f` overwrites the 4 bytes that `d.i` occupied with the bit pattern of `3.14f`. So `d.i` becomes 1078523331, that bit pattern (`0x4048F5C3`) read as an integer, and the only member holding a meaningful value is `d.f`, the one written last.

   </details>

4. **Enumeration values:** Write the values of the four enumeration constants in `enum level { LOW = 1, MEDIUM, HIGH = 10, MAX };`.

   <details>
   <summary>Answer</summary>

   `LOW = 1`, `MEDIUM = 2`, `HIGH = 10`, and `MAX = 11`. An enumeration constant without an assigned value is 1 greater than the constant just before it.

   </details>

5. **Passing structures:** For `c1` with `price` 11000, what is `c1.price` after calling `void f(struct content c) { c.price *= 0.8; }` and, separately, `void g(struct content *p) { p->price *= 0.8; }`? What parameter type suits a function that does not modify the structure?

   <details>
   <summary>Answer</summary>

   `f(c1)` modifies a copy, so `c1.price` stays 11000, while `g(&c1)` modifies the original, so it becomes 11000 × 0.8 = 8800. A function that does not modify the structure should take a `const` structure pointer such as `const struct content *p`, which avoids the copy cost and prevents changes.

   </details>
