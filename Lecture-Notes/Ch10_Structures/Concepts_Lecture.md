# Chapter 10 — Structures

[Repository Guide](../../README.md) | [English](Concepts_Lecture.md) | [한국어](Concepts_Lecture.ko.md)

> **Last Updated:** 2026-11-27
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
  - [1.8 Structure Layout Checked with `offsetof`](#18-structure-layout-checked-with-offsetof)
  - [1.9 Structures with Only Some Members Initialized](#19-structures-with-only-some-members-initialized)
- [2. Structure Applications](#2-structure-applications)
  - [2.1 Structure Arrays](#21-structure-arrays)
  - [2.2 Structure Pointers](#22-structure-pointers)
  - [2.3 Passing Structs to Functions](#23-passing-structs-to-functions)
  - [2.4 Nested Structures](#24-nested-structures)
  - [2.5 Functions That Return Structures](#25-functions-that-return-structures)
  - [2.6 Bit Fields](#26-bit-fields)
  - [2.7 Arithmetic on Structure Arrays and Structure Pointers](#27-arithmetic-on-structure-arrays-and-structure-pointers)
  - [2.8 Reading Input into Structure Members](#28-reading-input-into-structure-members)
  - [2.9 Memory Layout of Nested Structures and Unions](#29-memory-layout-of-nested-structures-and-unions)
- [3. Related Types](#3-related-types)
  - [3.1 `enum`](#31-enum)
  - [3.2 `union`](#32-union)
  - [3.3 `typedef`](#33-typedef)
  - [3.4 Other Uses of `typedef`](#34-other-uses-of-typedef)
  - [3.5 Handling Directions with Enumerations and `switch`](#35-handling-directions-with-enumerations-and-switch)
  - [3.6 Common Mistakes with Structures and Related Types](#36-common-mistakes-with-structures-and-related-types)
  - [3.7 Comprehensive Example: A Grade Processing Program](#37-comprehensive-example-a-grade-processing-program)
  - [3.8 Printing Enumeration Names and Checking Values](#38-printing-enumeration-names-and-checking-values)
- [Concept Applications](#concept-applications)
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

```c wide-ok
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

```c wide-ok
struct content c1 = {"Avengers", 11000, 8.8};

c1.rate = 8.9;                      // modify a member
c1.price *= 0.8;                    // compound assignment on a member
strcat(c1.title, ": Endgame");      // string operation on a member
printf("Title: %s\n", c1.title);    // read a member
```

> **Key Point:** Members can **only** be accessed through a struct variable. You cannot use a member name on its own, and `title` alone does not refer to `c1.title`. If there is an ordinary variable with the same name, `title` refers to that variable.

```c
// title = "Test";       // compile error: title is not a standalone variable
c1.title;                // correct: access through the struct variable
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

// c3.title = c1.title;         // compile error: arrays cannot be assigned!
strcpy(c3.title, c1.title);     // correct: use strcpy for strings
c3.price = c1.price;            // OK: non-array members can be assigned
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

```c wide-ok
if (strcmp(c1.title, c2.title) == 0 &&
    c1.price == c2.price &&
    c1.rate == c2.rate) {
    printf("c1 and c2 are equal\n");
}
```

> **Caution:** Comparing structs with `==` is a compile error in C. You **must** compare each member individually. Use `strcmp` for string (char array) members, and do not use `==` on strings. The values of padding bytes and of bytes after a string's null character are unspecified, so comparing whole structs with `memcmp` is not reliable either.

### 1.8 Structure Layout Checked with `offsetof`

The padding of Section 1.2 can be checked directly with the macro `offsetof(structure type, member)` of `<stddef.h>`. `offsetof` reports how many bytes a member lies from the start of the structure. The following two structures hold the same members, two `char` and one `int`, in different orders.

```c
#include <stdio.h>
#include <stddef.h>

struct A {
    char c;
    int n;
    char d;
};

struct B {
    int n;
    char c;
    char d;
};

int main(void)
{
    printf("A: size %zu, c %zu, n %zu, d %zu\n", sizeof(struct A),
           offsetof(struct A, c), offsetof(struct A, n), offsetof(struct A, d));
    printf("B: size %zu, n %zu, c %zu, d %zu\n", sizeof(struct B),
           offsetof(struct B, n), offsetof(struct B, c), offsetof(struct B, d));
    return 0;
}
```

```text
A: size 12, c 0, n 4, d 8
B: size 8, n 0, c 4, d 5
```

```text
struct A (12 bytes)
offset   0     1     2     3     4     5     6     7     8     9    10    11
      ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
      │  c  │ /// │ /// │ /// │  n  │  n  │  n  │  n  │  d  │ /// │ /// │ /// │
      └─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘
struct B (8 bytes)
offset   0     1     2     3     4     5     6     7
      ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
      │  n  │  n  │  n  │  n  │  c  │  d  │ /// │ /// │
      └─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘
```

*Figure 4. Member offsets and padding of struct A and struct B, with padding shown as ///*

In this environment, a 4-byte `int` must be placed at an address that is a multiple of 4. `struct A` fills 3 bytes after the `c` at offset 0 so that `n` comes at offset 4, a multiple of 4, and fills 3 more bytes after the `d` at offset 8. The padding at the end ensures that, in an array of `struct A`, the `n` of the next element also lands at a multiple of 4, so the size of a structure is a multiple of its largest alignment unit (4 here). The members add up to 1 + 4 + 1 = 6 bytes, but `struct A` is 12 bytes. Putting the large member first and grouping the small ones, as in `struct B`, places `c` and `d` together at offsets 4 and 5 and fills only 2 bytes at the end, reducing the size to 8 bytes. Alignment rules are set by the platform, so the size of a structure is obtained with `sizeof` rather than guessed by adding numbers.

### 1.9 Structures with Only Some Members Initialized

As with arrays, when a structure's initializer list runs short of initial values, the remaining members are initialized to 0. Every element of a character-array member becomes the null character, giving an empty string. Hence `{ 0 }` is an idiom that starts a whole structure at 0, however many members it has.

```c
struct item {
    char name[8];
    int price;
    int stock;
};

struct item a = { "pen", 1500 };
struct item b = { 0 };

printf("[%s] %d %d\n", a.name, a.price, a.stock);
printf("[%s] %d %d\n", b.name, b.price, b.stock);
```

```text
[pen] 1500 0
[] 0 0
```

`a` has no initial value for `stock`, so it becomes 0, and `b` specifies only the first member as 0, yet every member is 0. Given `-Wextra`, Clang issues the warning `missing field 'stock' initializer` for the initialization of `a`. It warns that the omission may have been accidental rather than deliberate, and it is not issued for `{ 0 }`. In contrast, a structure variable declared inside a function without an initializer list, `struct item c;`, has garbage values in every member, so each member must be assigned a value before use.

> **Note:** **Designated initializers.** From C99 on, members can be initialized in any order by naming them, as in `struct item c = { .price = 900, .name = "clip" };`. The unnamed `stock` becomes 0. In a structure with many members this makes clear which value goes into which member, but it is not part of the ANSI C syntax of the textbook.

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

```c wide-ok
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

```c wide-ok
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

*Figure 5. Structure pointer p pointing to structure variable c1*

To access a structure variable read-only, declare a `const` pointer such as `const struct content *p = &c1;`. Through this pointer, `p->price` can only be read, and changing a member, as in `p->price = 0;`, is a compile error.

### 2.3 Passing Structs to Functions

A structure can be passed to a function either by value or by pointer.

**Pass by value:** The function receives a **copy**.

```c wide-ok
void display(struct content c) {
    printf("%s %d %.1f\n", c.title, c.price, c.rate);
    c.price = 0;   // modifies the copy only: original unchanged
}

int main() {
    struct content c1 = {"Avengers", 11000, 8.8};
    display(c1);    // passes a copy
    printf("Price: %d\n", c1.price);  // still 11000
    return 0;
}
```

**Pass by pointer:** The function can **modify the original**.

```c wide-ok
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

```c wide-ok
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

The difference between pass-by-value and pass-by-pointer can be seen in the number of bytes copied. Functions that pass the `struct content` of Section 1.2 in the two ways and print the size of the parameter each receives give the following.

```c
void by_value(struct content c)
{
    printf("by value: %zu bytes copied\n", sizeof c);
}

void by_pointer(const struct content *p)
{
    printf("by pointer: %zu bytes copied\n", sizeof p);
}
```

```text
by value: 64 bytes copied
by pointer: 8 bytes copied
```

`struct content` is 64 bytes: the 50-byte `title`, then 2 bytes of padding to align the `int` at a multiple of 4, the 4-byte `price`, and the 8-byte `rate`. Passing it by value copies these 64 bytes into the parameter at every call, while passing it by pointer copies only an 8-byte address. The difference grows with the size of the structure and the number of calls, so a large structure is passed by pointer, and when the function does not change the structure, `const` is attached to protect the original as pass-by-value would.

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

```c wide-ok
printf("Name: %s\n", s1.name);
printf("Birthday: %d-%02d-%02d\n",
       s1.birthday.year, s1.birthday.month, s1.birthday.day);
```

**With pointers:**

```c wide-ok
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

*Figure 6. Structure variable s1 containing a `struct date` member*

`s1.birthday` can itself be used like a variable of type `struct date`.

### 2.5 Functions That Return Structures

Unlike arrays, structures can be assigned, so they can also serve as the return type of a function. When a function returns a structure, all its members are copied and delivered to the caller, so several values can be bundled into one structure and returned at once. The following code compares a function that returns the midpoint of two points as a structure with a function that changes the coordinates of a point through a pointer.

```c
struct point {
    int x, y;
};

struct point midpoint(struct point a, struct point b)
{
    struct point m;

    m.x = (a.x + b.x) / 2;
    m.y = (a.y + b.y) / 2;
    return m;                       // all members of m are copied and returned
}

void move(struct point *p, int dx, int dy)
{
    p->x += dx;                     // changes the caller's structure directly
    p->y += dy;
}

int main(void)
{
    struct point a = { 0, 0 }, b = { 10, 6 }, m;

    m = midpoint(a, b);
    printf("m = (%d, %d)\n", m.x, m.y);
    move(&m, 1, -1);
    printf("m = (%d, %d)\n", m.x, m.y);
    printf("sizeof(struct point) = %zu\n", sizeof(struct point));
    return 0;
}
```

```text
m = (5, 3)
m = (6, 2)
sizeof(struct point) = 8
```

`midpoint` returns the local variable `m`, but what is returned is not the address of `m` but a structure holding copies of the member values, so the dangling-pointer problem of Chapter 8, Section 3.5 does not arise. Since (0 + 10) / 2 = 5 and (0 + 6) / 2 = 3, the midpoint is (5, 3), and `move(&m, 1, -1)` changes `m` to (6, 2) through its address. It is natural to give a structure return type to a function that builds a result as a new value, and a structure-pointer parameter to a function that modifies an existing structure. `struct point` is 8 bytes, so copying it is cheap, but a large structure with character-array members is more efficiently received through a `const` pointer, as in Section 2.3.

### 2.6 Bit Fields

A **bit field** is syntax that specifies directly the number of bits a structure member occupies. It stores several members with small value ranges inside one integer, divided bit by bit, which reduces memory. A colon and the number of bits are written after the member name, and it is used in the same way as an ordinary structure.

```c
struct date_bits {
    unsigned int day : 5;       /* 1~31: 5 bits */
    unsigned int month : 4;     /* 1~12: 4 bits */
    unsigned int year : 12;     /* 0~4095: 12 bits */
};

struct date_ints {
    unsigned int day, month, year;
};

int main(void)
{
    struct date_bits d = { 19, 11, 2026 };

    printf("%u-%u-%u\n", d.year, d.month, d.day);
    printf("sizeof bits = %zu, sizeof ints = %zu\n", sizeof(struct date_bits), sizeof(struct date_ints));
    d.month = 13;
    printf("month = %u\n", d.month);
    d.month = 17;
    printf("month = %u\n", d.month);
    return 0;
}
```

```text
2026-11-19
sizeof bits = 4, sizeof ints = 12
month = 13
month = 1
```

5 + 4 + 12 = 21 bits, so the three members fit in one `unsigned int` (32 bits), and the structure is 4 bytes, while a structure with the same members as separate `unsigned int` values is 12 bytes. In exchange, the values each member can hold are limited by its number of bits. The 4-bit `month` holds only 0-15, so 13 is stored but is not a valid month, and 17 (`10001`) keeps only its low 4 bits `0001` and becomes 1. Clang issues the warning `implicit truncation from 'int' to bit-field changes value from 17 to 1` for the assignment of the constant 17. A bit-field member has no address, so `&d.month` and `scanf("%u", &d.month)` cannot be used, and the order in which the bits are laid out is decided by the implementation. Precautions for data whose bit layout is fixed, such as hardware registers, are treated in Chapter 13.

### 2.7 Arithmetic on Structure Arrays and Structure Pointers

The pointer arithmetic of Chapter 8 applies to structure pointers as it is. Adding 1 to a `struct point *p` moves by `sizeof(struct point)`, that is, by one structure, so a structure array can be traversed with a pointer.

```c
struct point {
    int x, y;
};

int main(void)
{
    struct point pts[3] = { { 1, 2 }, { 3, 4 }, { 5, 6 } };
    struct point *p;
    int sum = 0;

    for (p = pts; p < pts + 3; p++) {
        sum += p->x * p->y;
        printf("p = %p, p->x = %d, p->y = %d\n", (void *)p, p->x, p->y);
    }
    printf("sum = %d\n", sum);
    p = pts;
    printf("%d %d %d\n", (p + 1)->x, pts[1].x, (*(p + 2)).y);
    return 0;
}
```

```text
p = 0x16f442af0, p->x = 1, p->y = 2
p = 0x16f442af8, p->x = 3, p->y = 4
p = 0x16f442b00, p->x = 5, p->y = 6
sum = 44
3 3 6
```

```text
          pts[0]                pts[1]                pts[2]
address   af0        af4        af8        afc        b00        b04
        ┌──────────┬──────────┬──────────┬──────────┬──────────┬──────────┐
        │  x = 1   │  y = 2   │  x = 3   │  y = 4   │  x = 5   │  y = 6   │
        └──────────┴──────────┴──────────┴──────────┴──────────┴──────────┘
          ▲ p                   ▲ p + 1               ▲ p + 2
```

*Figure 7. The structure array pts and the movement of the pointer p*

The value of `p` grows by 8, the size of `struct point`, in each iteration. The sum is 1 × 2 + 3 × 4 + 5 × 6 = 2 + 12 + 30 = 44. The three expressions in the last line write the same elements differently: `(p + 1)->x` and `pts[1].x` are both the `x` of the second element, 3, and `(*(p + 2)).y` is the `y` of the third element, 6. In general, `pts[i].member`, `(pts + i)->member`, and `(*(pts + i)).member` are the same. Any notation may be used as long as the rule is kept that the left side of `->` is the address of a structure and the left side of `.` is a structure itself.

`->` is among the operators that bind first, together with `.`, `[]`, and postfix `++`, so when it is mixed with increment operators, care is needed about what is incremented. With `pts = { {1, 2}, {5, 6} }` and `p = pts`, executing the following three expressions in order gives different results.

```c
a = ++p->x;         // ++(p->x): pts[0].x becomes 2 and a is 2
printf("%d %d\n", a, pts[0].x);
a = (++p)->x;       // p moves to pts[1] and a is 5
printf("%d %d\n", a, (int)(p - pts));
a = p->x++;         // (p->x)++: a is 5, pts[1].x becomes 6
printf("%d %d\n", a, pts[1].x);
```

```text
2 2
5 1
5 6
```

In the first line, `->` binds before prefix `++`, so the member `x` is incremented. In the second line, the parentheses make the pointer `p` increment first so that it points to the next element, and `p - pts` is 1. The third line uses postfix `++`, so the value before the increment, 5, goes into `a`, and the member becomes 6. Write the parentheses clearly according to whether the pointer is to be moved or the member changed.

### 2.8 Reading Input into Structure Members

Structure members are passed to `scanf` by the same rules as ordinary variables. An `int` member is passed by address, as in `&s.score`, and a character-array member is passed without `&`, as in `s.name`, because the array name is already an address. Members of a nested structure are written with `.` from the outside in. `.` binds before `&`, so `&s.birthday.year` is `&(s.birthday.year)`, the address of the `year` member.

```c
struct date {
    int year, month, day;
};

struct student {
    char name[20];
    int score;
    struct date birthday;
};

int main(void)
{
    struct student s;

    printf("name score year month day? ");
    if (scanf("%19s %d %d %d %d", s.name, &s.score, &s.birthday.year,
              &s.birthday.month, &s.birthday.day) != 5)
        return 1;
    printf("%s (%d) born %d-%d-%d\n", s.name, s.score, s.birthday.year,
           s.birthday.month, s.birthday.day);
    return 0;
}
```

```text
name score year month day? Kim 91 2005 3 14
Kim (91) born 2005-3-14
```

`%19s` reads at most 19 characters, leaving room for the null character in the 20 bytes of `name`. Placing `&` the wrong way makes Clang warn as follows: the first warning is for `scanf("%d", v.score)`, which omits `&` for an `int` member, and the second for `scanf("%19s", &v.name)`, which adds `&` to a character-array member.

```text
warning: format specifies type 'int *' but the argument has type 'int' [-Wformat]
warning: format specifies type 'char *' but the argument has type 'char (*)[20]' [-Wformat]
```

In the second case, `&v.name` is the address of the whole array (`char (*)[20]`), like `&arr` in Chapter 8, Section 2.6. Its address value equals that of `v.name`, so it may happen to work, but the type does not match, so it is written without `&`.

### 2.9 Memory Layout of Nested Structures and Unions

In the nested structure of Section 2.4, the whole inner structure goes into the outer structure as one member. Measuring the `struct student` of Section 2.8 with `offsetof` gives the following. A nested member such as `birthday.year` may also be written as the second argument of `offsetof`.

```c
printf("student: size %zu, name %zu, score %zu, birthday %zu\n", sizeof(struct student),
       offsetof(struct student, name), offsetof(struct student, score),
       offsetof(struct student, birthday));
printf("birthday.year %zu, birthday.day %zu, sizeof(struct date) %zu\n",
       offsetof(struct student, birthday.year), offsetof(struct student, birthday.day),
       sizeof(struct date));
printf("value: size %zu, i %zu, d %zu, c %zu\n", sizeof(union value),
       offsetof(union value, i), offsetof(union value, d), offsetof(union value, c));
```

```text
student: size 36, name 0, score 20, birthday 24
birthday.year 24, birthday.day 32, sizeof(struct date) 12
value: size 8, i 0, d 0, c 0
```

```text
struct student (36 bytes)
offset  0                   20         24         28         32         36
      ┌───────────────────┬──────────┬──────────┬──────────┬──────────┐
      │ name[20]          │ score    │ year     │ month    │ day      │
      └───────────────────┴──────────┴──────────┴──────────┴──────────┘
                                     └──────── birthday (12 bytes) ─────┘
```

*Figure 8. Member offsets of the nested structure struct student*

`name` is 20 bytes, and since 20 is a multiple of 4, `score` is placed at offset 20 without padding. `birthday` then occupies the 12 bytes of `struct date` from offset 24, and its `year`, `month`, and `day` are at 24, 28, and 32. Since 20 + 4 + 12 = 36, this structure has no padding. Measuring the union `union value { int i; double d; char c[4]; }` the same way shows that all three members have offset 0, and the size is 8 bytes, that of the largest member `double`. The difference that a structure lays its members out one after another while a union overlays all members at the same starting address shows up in the numbers.

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

```c wide-ok
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

```c wide-ok
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

*Figure 9. Union variable d whose three members share the same memory*

The size of a union usually equals the size of its largest member, but alignment can make it larger. For example, `union { char s[5]; int i; }` has a largest member of 5 bytes, but its size is 8 to satisfy the alignment of `int`. When initializing a union, give only the initial value of the first member in `{}` (`union data d = {42};` initializes `d.i`). Members are accessed with `.` as in a structure, and with `->` through a union pointer.

```c
union data d;
d.i = 42;
printf("i = %d\n", d.i);    // 42

d.f = 3.14;
printf("f = %.2f\n", d.f);  // 3.14
printf("i = %d\n", d.i);    // garbage: overwritten by d.f!
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
Point p1 = {10, 20};          // concise: with typedef
```

> **Key Point:** `typedef` does **not** create a new type; it creates a new **name** for an existing type. `Point` and `struct point` are the same type.

### 3.4 Other Uses of `typedef`

`typedef` can also be used for types other than structures. First, it attaches a name that reveals meaning. `BYTE`, defined by `typedef unsigned char BYTE;`, shows by its name that the data is byte-oriented rather than a number. Second, it shortens complex types. Naming a structure pointer lets `StudentPtr` be written instead of `Student *`. Third, it hides types that vary by platform. The standard library's `size_t` is also a name defined with `typedef`, and its actual type differs by platform. When the type must change, only the one `typedef` line needs to be edited, which improves portability.

```c
typedef unsigned char BYTE;
typedef struct student {
    char name[20];
    int score;
} Student;
typedef Student *StudentPtr;

int main(void)
{
    BYTE b = 255;
    Student s = { "Kim", 91 };
    StudentPtr p = &s;

    b++;
    printf("b = %u, %s %d\n", b, p->name, p->score);
    printf("%zu %zu\n", sizeof(BYTE), sizeof(size_t));
    return 0;
}
```

```text
b = 0, Kim 91
1 8
```

`BYTE` is only another name for `unsigned char`, so adding 1 to 255 gives 0 by the unsigned wraparound of Chapter 3. In this environment, `size_t` is 8 bytes. However, using `typedef` for a pointer type hides the `*` from declarations, making it easy to miss that the variable is a pointer, so it is best used only where the name is used often and its meaning is clear, as with structure names.

### 3.5 Handling Directions with Enumerations and `switch`

Enumerations are used to express by name data that takes one of a few fixed values. The following code defines the four directions up, down, left, and right as `enum direction` and moves the coordinates of a point by one step with `switch` according to the direction.

```c
enum direction { UP, DOWN, LEFT, RIGHT };

struct point {
    int x, y;
};

void move(struct point *p, enum direction d)
{
    switch (d) {
    case UP:
        p->y++;
        break;
    case DOWN:
        p->y--;
        break;
    case LEFT:
        p->x--;
        break;
    case RIGHT:
        p->x++;
        break;
    }
}

int main(void)
{
    enum direction path[5] = { UP, UP, RIGHT, DOWN, RIGHT };
    struct point pos = { 0, 0 };
    int i;

    for (i = 0; i < 5; i++) {
        move(&pos, path[i]);
        printf("step %d: dir = %d, pos = (%d, %d)\n", i + 1, path[i], pos.x, pos.y);
    }
    return 0;
}
```

```text
step 1: dir = 0, pos = (0, 1)
step 2: dir = 0, pos = (0, 2)
step 3: dir = 3, pos = (1, 2)
step 4: dir = 1, pos = (1, 1)
step 5: dir = 3, pos = (2, 1)
```

The enumeration constants are, in order, `UP` = 0, `DOWN` = 1, `LEFT` = 2, and `RIGHT` = 3, so printing them with `%d` gives these integers. Following the path, the point goes from (0, 0) up twice to (0, 2), right to (1, 2), down to (1, 1), and right to (2, 1). Using enumeration constants instead of numbers in the `case` labels of a `switch` reveals what the code compares, and the compiler finds missing cases. Compiling, with `-Wall`, a `switch` whose `case` labels for `LEFT` and `RIGHT` have been deleted makes Clang issue the warning `enumeration values 'LEFT' and 'RIGHT' not handled in switch`. This warning does not appear when there is a `default`, so in a `switch` that must handle every enumeration value, writing all the `case` labels instead of `default` makes mistakes easier to find.

### 3.6 Common Mistakes with Structures and Related Types

Errors that often appear when first using structures are confusing `.` with `->` and omitting the `struct` keyword. Each of the three lines in the following code is an error in Clang.

```c
struct point { int x, y; };

struct point pt = { 1, 2 }, *p = &pt;
int a = p.x;            // uses . on a pointer
int b = pt->y;          // uses -> on a structure variable
point q;                // uses only the tag name without struct
```

```text
error: member reference type 'struct point *' is a pointer; did you mean to use '->'?
error: member reference type 'struct point' is not a pointer; did you mean to use '.'?
error: must use 'struct' tag to refer to type 'point'
```

| Mistake | Correction |
|:-----|:-----|
| Using `.` on a pointer | `p->x` or `(*p).x` |
| Using `->` on a structure variable | `pt.y` |
| Using only the tag name without `struct` | Write `struct point q;`, or define an alias with the `typedef` of Section 3.3 |
| Missing semicolon at the end of a structure definition | End it with `};` (Section 1.2) |
| Assigning a string to a character-array member with `=` | `strcpy(s.name, "Kim");` (Section 1.6) |
| Comparing structures with `==` | Compare member by member (Section 1.7) |
| Reading a union member that was not written last | Record which member was written in a separate variable (Section 3.2) |

*Table 4. Common mistakes with structures and related types*

For the first two errors, Clang even suggests the correct operator. The third error arises because in C the tag names of structures live in a different name space from type names. `struct point` as a whole is the type name, and to write just `point`, an alias of the same name must be defined separately, as in `typedef struct point point;`.

The choice between `.` and `->` is decided by the type of what comes on the left: `.` for a structure variable and `->` for a structure pointer. When a function's parameter is a structure pointer, `->` is used throughout the function, while `.` is used on the structure variable in `main`, so the operator for the same member changes with the place in the code. When in doubt, first check the type of the expression on the left, and use `->` if it is a pointer and `.` if it is a structure. The array element `pts[i]` is a structure, so it takes `.`, and `pts + i` is an address, so it takes `->`.

### 3.7 Comprehensive Example: A Grade Processing Program

The contents of this chapter are combined into one program. The Korean, English, and math scores of three students are stored in an array of the `Student` structure defined with `typedef`, and a function that computes the total and a function that finds the student with the highest total are written with structure pointers.

```c
typedef struct {
    char name[20];
    int kor, eng, math;
} Student;

int total(const Student *s)
{
    return s->kor + s->eng + s->math;
}

const Student *find_best(const Student list[], int n)
{
    const Student *best = &list[0];
    int i;

    for (i = 1; i < n; i++)
        if (total(&list[i]) > total(best))
            best = &list[i];
    return best;
}

int main(void)
{
    Student list[3] = {
        { "Kim", 90, 80, 70 }, { "Lee", 85, 95, 90 }, { "Park", 70, 75, 100 }
    };
    const Student *best;
    int i;

    for (i = 0; i < 3; i++)
        printf("%-5s total = %3d, average = %.2f\n", list[i].name,
               total(&list[i]), total(&list[i]) / 3.0);
    best = find_best(list, 3);
    printf("best: %s (%d)\n", best->name, total(best));
    return 0;
}
```

```text
Kim   total = 240, average = 80.00
Lee   total = 270, average = 90.00
Park  total = 245, average = 81.67
best: Lee (270)
```

- **Defining the type:** The untagged structure is given the name `Student` with `typedef`, so from then on only `Student` is written, without `struct` (Section 3.3).
- **`total`:** It does not change the structure, so it takes a `const Student *` and adds the three members with `->`. Instead of copying the whole structure, only an 8-byte address is passed.
- **`find_best`:** It starts the pointer `best`, which points to the best student so far, at the first element, and changes it to the address of any element with a larger total. The returned address is an element of the caller's array, so it remains valid after the function ends (Chapter 8, Section 3.5). The totals are 240, 270, and 245, so `best` changes to `&list[1]` when `i` is 1 and does not change when `i` is 2.
- **`main`:** `%-5s` left-aligns the name in 5 columns to line up the columns. The average is divided by `3.0` to make it a floating-point division, and Park's average 245 / 3 = 81.666... becomes 81.67 with `%.2f`.

### 3.8 Printing Enumeration Names and Checking Values

Enumeration constants remain only as integers after compilation, so a name such as `UP` cannot be printed with `printf`. When names are needed, keep an array of string pointers (Chapter 9, Section 7.2) indexed by the values of the enumeration constants. Putting `DIR_COUNT` at the end of the list makes its value equal the number of preceding constants, 4, so it can serve as the array size and as the end of a loop.

```c
enum direction { UP, DOWN, LEFT, RIGHT, DIR_COUNT };

const char *names[DIR_COUNT] = { "UP", "DOWN", "LEFT", "RIGHT" };

const char *dir_name(enum direction d)
{
    if (d < UP || d >= DIR_COUNT)       // filter out out-of-range values
        return "?";
    return names[d];
}

int main(void)
{
    enum direction d;
    enum direction bad = 7;

    for (d = UP; d < DIR_COUNT; d++)
        printf("%d %s\n", d, dir_name(d));
    printf("%d %s\n", bad, dir_name(bad));
    return 0;
}
```

```text
0 UP
1 DOWN
2 LEFT
3 RIGHT
7 ?
```

An enumeration variable can also store integers other than its defined constants. `enum direction bad = 7;` compiled in Clang without a warning even with `-Wall -Wextra`. An enumeration is merely treated as an integer type and its range is not checked, so a function that uses enumeration constants as array indices must check the range first, as `dir_name` does. Without the check, `names[7]` would be an access beyond an array of 4 elements. Incrementing an enumeration variable, as in `d++`, to visit the constants in order is correct only when the constants increase by 1 from 0.

---

<br>

## Concept Applications

**True/False Check:**

| Statement | Judgment and Reason |
|:-----|:-----|
| The size of a structure always equals the sum of the member sizes. | **F.** It can be larger than the sum because of padding for alignment. |
| Structures of the same type can be assigned with `=`, and array members are copied as well. | **T.** Structure assignment copies every member as it is. |
| Structures can be compared with `==`. | **F.** `==` cannot be used on structures, so they are compared member by member. |
| For a structure pointer `p`, `p->x` and `(*p).x` are the same. | **T.** `->` is an operator that dereferences and accesses a member at once. |
| `*p.x` is the same as `(*p).x`. | **F.** `.` binds before `*`, giving `*(p.x)`, so it is a compile error when `p` is a pointer. |
| Returning a local structure variable from a function causes a dangling-pointer problem. | **F.** What is returned is not an address but a value with the members copied, so it is safe. |
| The address of a bit-field member can be obtained with `&`. | **F.** A bit-field member has no byte address, so `&` cannot be used on it. |
| `typedef` creates a new data type. | **F.** It only gives a new name to an existing data type. |
| `p->x` abbreviates `(*p).x`, and if `p` points to an element of a structure array, `p + 1` points to the next element. | **T.** Pointer arithmetic moves in units of the size of one structure. |
| The size of a structure does not depend on the order in which its members are declared. | **F.** The amount of padding for alignment depends on the order, so the size can differ. |
| In `scanf("%s", s.name)`, `&` must be attached to `s.name`. | **F.** The name of a character-array member is already the address of its first element. |
| Every member of a union has offset 0. | **T.** All members share the same starting address. |
| Storing an undefined value in an enumeration variable, as in `enum direction d = 7;`, causes a compile error. | **F.** An enumeration is treated as an integer type and its range is not checked, so it compiles. |
| `++p->x` moves the pointer `p` to the next element. | **F.** `->` binds first, so the member `x` is incremented; to move the pointer, write `(++p)->x`. |
| Passing a large structure by value copies the whole structure. | **T.** For `struct content`, 64 bytes are copied at every call, while passing a pointer copies only 8 bytes. |

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
| Returning structures | Structures can be assigned, so they can be return types, and since what is returned is a copy of the members, returning a local variable is safe. |
| Bit fields | Specifying the number of bits of a member, as in `unsigned int day : 5;`, reduces memory; out-of-range values are truncated, and a member's address cannot be taken. |
| Uses of `typedef` | It gives meaningful names, abbreviates complex types, and hides types that differ by platform (`size_t`). |
| `offsetof` and padding | `offsetof` reveals member positions, and placing large members first and grouping small ones reduces padding. |
| Arithmetic on structure pointers | `p + 1` moves by one structure, and `pts[i].x`, `(pts + i)->x`, and `(*(pts + i)).x` are the same. |
| Input into structure members | An `int` member is passed as `&s.score` and a character-array member as `s.name`, and `&s.birthday.year` is the address of a nested member. |
| Enumerations and `switch` | Enumeration constants in `case` labels reveal meaning, and without `default` the compiler warns about unhandled values. |
| Common structure mistakes | Use `->` for pointers and `.` for variables, and write tag names together with `struct`. |
| Initializing some members | When initial values run short, the remaining members become 0, and `{ 0 }` is the idiom that starts a whole structure at 0. |
| Functions taking structure pointers | A function that only reads takes a `const` structure pointer to avoid copying, and it may return the address of an array element. |
| Layout of nested structures and unions | A nested structure holds the whole inner structure as one member, and every member of a union has offset 0. |
| Names of enumeration constants | Names are printed with a string array indexed by the constants, and since an enumeration variable is not range-checked, it is checked before being used as an index. |

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

6. **Returning a structure:** For the `midpoint` of Section 2.5, what point does `midpoint(a, b)` return when a is (3, 9) and b is (8, 2)? Pay attention to integer division.

   <details>
   <summary>Answer</summary>

   x is (3 + 8) / 2 = 11 / 2 = 5 and y is (9 + 2) / 2 = 11 / 2 = 5, so the point is (5, 5). Integer division discards the fractional part 0.5. If the exact midpoint (5.5, 5.5) is needed, declare the members as `double`.

   </details>

7. **Bit fields:** For `struct flags { unsigned int a : 1; unsigned int b : 3; };`, what is the value of `f.b` after `f.b = 9;` executes? Also list all the values `f.a` can hold.

   <details>
   <summary>Answer</summary>

   9 is `1001` in binary, and a 3-bit member keeps only the low 3 bits `001`, so `f.b` is 1. The 1-bit unsigned member `f.a` can hold only 0 and 1.

   </details>

8. **Choosing return types:** When writing a function that raises a student's score by 10 and a function that gives back the information of whichever of two students has the higher score, how should the parameters and return type of each be chosen?

   <details>
   <summary>Answer</summary>

   The function that raises the score must change the caller's structure, so it uses a pointer parameter, as in `void raise(struct student *s)`. The function that gives back the higher-scoring student does not change its inputs, so it can take two `const struct student *` and return the pointer to the higher one, or, for a small structure, return a `struct student` by value. For a large structure, the pointer approach is more efficient because of the copying cost.

   </details>
