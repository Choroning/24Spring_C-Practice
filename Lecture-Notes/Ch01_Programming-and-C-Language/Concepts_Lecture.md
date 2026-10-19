# Chapter 1 — Programming and C Language

[Repository Guide](../../README.md) | [English](Concepts_Lecture.md) | [한국어](Concepts_Lecture.ko.md)

> **Last Updated:** 2026-10-19
>
> Warming-Up C Programming, 천정아, Ch 1

> **Learning Objectives:**
> 1. Explain the concepts of software, programs, instructions, and programming
> 2. Distinguish low-level from high-level languages and machine-dependent from machine-independent languages
> 3. Explain the history, features, and applications of C and the reasons for learning it
> 4. Explain the build process of preprocessing, compiling, assembling, and linking and the output of each stage
> 5. Distinguish compile errors, link errors, and runtime errors and apply basic debugging techniques

---

## Table of Contents

- [1. Programming](#1-programming)
  - [1.1 Software and Programs](#11-software-and-programs)
  - [1.2 Programming Languages](#12-programming-languages)
  - [1.3 Machine-Dependent vs Machine-Independent](#13-machine-dependent-vs-machine-independent)
- [2. C Language](#2-c-language)
  - [2.1 History](#21-history)
  - [2.2 Features](#22-features)
  - [2.3 Applications](#23-applications)
  - [2.4 Why Learn C](#24-why-learn-c)
- [3. C Program Development](#3-c-program-development)
  - [3.1 Development Process](#31-development-process)
  - [3.2 Build Process](#32-build-process)
  - [3.3 Errors](#33-errors)
  - [3.4 Debugging](#34-debugging)
  - [3.5 Integrated Development Environments](#35-integrated-development-environments)
- [Summary](#summary)
- [Self-Check Questions](#self-check-questions)

---

<br>

## 1. Programming

### 1.1 Software and Programs

**Hardware** refers to the physical components of a computer (CPU, memory, storage, peripherals, etc.). **Software** is the collection of programs that run on the hardware and tell it what to do; software that runs on a smartphone is commonly called an **app**.

```text
Computer System
├── Hardware
│   ├── CPU (Central Processing Unit)
│   ├── Memory (RAM)
│   ├── Storage (HDD/SSD)
│   └── I/O Devices (keyboard, monitor, etc.)
└── Software
    ├── System Software (OS, drivers, utilities)
    └── Application Software (word processors, games, etc.)
```

*Figure 1. Hardware and software that make up a computer system*

A **program** is a set of instructions written in a programming language to perform a specific task; it describes a sequence of operations for the computer hardware to carry out. The **instructions** that the hardware ultimately executes are binary codes the CPU can process, also called CPU instructions. **Programming** is the activity or process of designing and writing these instructions.

> **Key Point:** Without software, hardware is just an expensive collection of electronic components. Software gives hardware purpose.

### 1.2 Programming Languages

A **programming language** is a formal language used to describe the tasks a computer must perform in a program. Languages are classified as low-level or high-level by how close they are to machine hardware.

| Level | Language | Example | Readability | Portability |
|:------|:---------|:--------|:----------:|:-----------:|
| Low-level | Machine Language | `10110000 01100001` | Very low | None |
| Low-level | Assembly Language | `MOV AL, 61h` | Low | None |
| High-level | C, Java, Python | `printf("Hello");` | High | High |

*Table 1. Classification of programming languages by level*

The machine code `10110000 01100001` in the table is the binary code that corresponds, on an x86 CPU, to the assembly instruction `MOV AL, 61h` (load hexadecimal 61 into register AL).

**Machine Language** (1st generation):
- Consists of binary codes (`0`s and `1`s) that the CPU directly executes.
- Each instruction corresponds to a specific CPU operation.
- Because it is written in binary, it is very inconvenient for people to use and error-prone.
- It is different for every CPU architecture and therefore completely **machine-dependent**.

**Assembly Language** (2nd generation):
- Uses human-readable **mnemonics** (e.g., `MOV`, `ADD`, `JMP`) instead of binary.
- Has a one-to-one correspondence with machine instructions.
- An **assembler** translates an assembly program to machine code.
- It is still machine-dependent, so an assembly program for x86 cannot run on ARM.

**High-Level Languages** (3rd generation and above):
- Use syntax close to the natural language people speak (`if`, `while`, `return`).
- One high-level statement may translate to many machine instructions.
- A **compiler** or **interpreter** translates them to machine code.
- They are generally **machine-independent**, so the same source code can run on different platforms once it is translated for each platform.

```text
Source Code (High-Level)
        │
        ▼
   ┌──────────┐
   │ Compiler │  ← translates entire program at once
   └──────────┘
        │
        ▼
Machine Code (Binary)
        │
        ▼
   ┌──────────┐
   │   CPU    │  ← executes
   └──────────┘
```

*Figure 2. A high-level program translated by a compiler and executed by the CPU*

> **Note:** **Compilers and interpreters.** A **compiler** translates the entire source code into machine code before execution (C, C++). An **interpreter** translates and executes line by line at runtime (Python, JavaScript). Java combines both approaches: its compiler translates source code into bytecode, and the JVM executes that bytecode.

### 1.3 Machine-Dependent vs Machine-Independent

| Property | Machine-Dependent | Machine-Independent |
|:---------|:-----------------:|:-------------------:|
| Tied to specific CPU? | Yes | No |
| Examples | Machine language, Assembly | C, Java, Python |
| Portability | Cannot move between architectures | Same source runs on different systems |
| Performance | Maximum (direct hardware control) | Usually slightly lower (limits of compiler optimization, runtime translation in interpreters) |
| Development speed | Very slow | Fast |

*Table 2. Comparison of machine-dependent and machine-independent languages*

Machine language and assembly are **machine-dependent**. Code written for one CPU architecture cannot run on another without rewriting, so the program must be rewritten when the CPU type changes. Writing such programs also requires a good understanding of how the CPU works.

High-level languages are **machine-independent**. Programs can be written without being tied to a CPU type or hardware characteristics, and the same C source code can be compiled on different platforms (Windows, Linux, macOS) using the appropriate compiler for each system.

> **Key Point:** "Machine-independent" does not mean zero effort to port. Platform-specific features (e.g., system calls) may still differ. But the core language and logic remain the same.

---

<br>

## 2. C Language

### 2.1 History

C was created in **1972** by **Dennis Ritchie** at Bell Labs, building on the B language developed by **Ken Thompson**; the two developed UNIX together. Its primary purpose was to rewrite the UNIX operating system in a high-level language. C went on to strongly influence languages such as C++, C#, Objective-C, Java, JavaScript, and Perl.

```text
Timeline of C
──────────────────────────────────────────────────────────────
1969    B Language (Ken Thompson) — for early UNIX on PDP-7
1972    C Language (Dennis Ritchie) — Bell Labs, for UNIX on PDP-11
1978    K&R C — "The C Programming Language" book (Kernighan & Ritchie)
1989    ANSI C (C89) — first official standard (ANSI X3.159-1989)
1990    C90 — ISO adoption of ANSI C (ISO/IEC 9899:1990)
1999    C99 — inline functions, variable-length arrays, // comments
2011    C11 — multi-threading, _Generic, bounds-checking
2018    C18 — bug fixes for C11 (no new features)
2023    C23 — latest standard (nullptr, #embed, auto type inference)
──────────────────────────────────────────────────────────────
```

*Figure 3. Timeline of the C language and its standards*

The bounds-checking interfaces of C11 (the `_s` functions such as `scanf_s`) belong to Annex K, an optional part of the standard, so not every compiler provides them.

> **Key Point:** "ANSI C" usually means C89/C90. It is the most widely supported baseline, and most modern compilers support at least C99. Source code written in **standard C** can be compiled by any C compiler and behaves the same way. Each C compiler adds its own extensions to the standard C features, so avoid extensions when portability matters.

### 2.2 Features

C has endured for over 50 years because of the following combination of strengths.

| Feature | Description |
|:--------|:------------|
| **Concise syntax** | It has few keywords (32 in C89) and a lean, minimal language design |
| **Procedural programming** | A program is divided into functions, and statements are executed in a defined order to carry out the task |
| **Flexibility** | It has few restrictions, so the programmer has fine-grained control |
| **Performance** | It compiles to efficient machine code with minimal runtime overhead |
| **Portability** | Standard C code compiles on virtually any platform with a C compiler |
| **High-level support** | Control statements, functions, and user-defined types such as structures let programs be written in a structured way |
| **Low-level support** | It supports direct memory access via pointers, bitwise operations, and hardware control |
| **Efficiency** | It has a small memory footprint and suits resource-constrained environments |
| **Foundation of modern languages** | C++, Java, C#, Python, Go, Rust, and others were influenced by C syntax and concepts |

*Table 3. Features of the C language*

On the other hand, its low-level features and few restrictions make C hard to learn and hard to use. The following is the simplest program written in C.

```c
#include <stdio.h>

int main(void) {
    printf("Hello, World!\n");
    return 0;
}
```

> **Note:** **Control and responsibility.** C gives you maximum control, but with that power comes responsibility. There is no garbage collector, no bounds checking, and no built-in exception handling. The programmer must manage everything explicitly.

### 2.3 Applications

C is widely used where performance-oriented development or portability is needed and where low-level hardware access matters. The table below also includes domains where C is used together with C++.

| Domain | Examples |
|:-------|:--------|
| Operating Systems | UNIX, Linux kernel, Windows kernel, macOS kernel |
| Language Implementations | CPython (the reference implementation of Python), Perl interpreter, early GCC |
| Databases | Oracle, MySQL, PostgreSQL, SQLite |
| Embedded Systems | Microcontrollers, IoT devices, smart TVs, automotive ECUs, satellites |
| High-Performance Applications | Microsoft Office, web browsers, high-performance libraries |
| Game Engines | Unreal Engine (C/C++), id Tech engines |
| Networking | TCP/IP stacks, Apache, Nginx |
| Scientific Computing | MATLAB internals, R internals, numerical libraries |

*Table 4. Application domains of C with examples*

An **embedded system** is a device that contains a special-purpose computer, and an **embedded program** is a program that runs on an embedded system. Today's compilers such as GCC, Clang, and MSVC are written mainly in C++, but they remain the core tools for compiling C programs.

> **Key Point:** The Linux kernel (over 30 million lines of code) is written almost entirely in C. This demonstrates that C scales from tiny embedded systems to massive, complex software.

### 2.4 Why Learn C

1. **Fundamentals:** C teaches how computers actually work. Along with control structures, functions, and user-defined types, you deal directly with memory layout, pointers, stack vs heap, and manual resource management, so you can understand the inner workings of programs that other languages hide. These concepts apply everywhere.

2. **Lingua franca:** C is the common language of systems programming. OS APIs, hardware interfaces, and countless algorithms and libraries are developed and published in C. Understanding C lets you make easy use of this programming knowledge and interact with the entire software ecosystem.

3. **Foundation for other languages:** Learning C makes it significantly easier to learn C++, Java, C#, JavaScript, Go, Rust, and others, since they borrow heavily from C's syntax and semantics.

```text
C (1972)
├── C++ (1979) — adds OOP, templates, STL
├── Objective-C (1984) — adds Smalltalk-style OOP
├── Java (1995) — C-like syntax, garbage collection, JVM
├── C# (2000) — Microsoft's answer to Java
├── Go (2009) — simplicity of C + concurrency
└── Rust (2010) — C-level performance + memory safety
```

*Figure 4. Languages influenced by C*

> **Note:** **Tip for users of high-level languages.** Even if you plan to work primarily in Python or JavaScript, knowing C gives you a deeper understanding of what happens inside a language, such as memory allocation, CPU-level behavior, and why certain operations are fast or slow.

---

<br>

## 3. C Program Development

### 3.1 Development Process

The overall process of creating a C program follows four main phases, and when an error occurs, the program is debugged and the process returns to an earlier phase.

```text
┌──────────────┐    ┌──────────────┐    ┌──────────────┐    ┌──────────────┐
│  1. Design   │───▶│ 2. Write     │───▶│ 3. Compile   │───▶│ 4. Execute   │
│  (algorithm) │    │ (source code)│    │ (build)      │    │ (run & test) │
└──────────────┘    └──────────────┘    └──────────────┘    └──────────────┘
                                               │
                                          errors?
                                               │
                                               ▼
                                        ┌──────────────┐
                                        │  5. Debug    │
                                        │  (fix errors)│
                                        └──────────────┘
                                               │
                                               └──── go back to step 2 or 3
```

*Figure 5. Development process of a C program*

| Phase | Activity | Output |
|:------|:---------|:-------|
| Design | Analyze the problem, plan the algorithm and data structures | Pseudocode, flowchart |
| Write | Type the source code in a text editor or IDE | `.c` source file |
| Compile | Translate source code to machine code, fix any build errors | Executable binary |
| Execute | Run the program, verify it produces correct output | Program output |
| Debug | Identify and fix errors, repeat the compile-execute cycle | Corrected source code |

*Table 5. Activities and outputs of each development phase*

An **algorithm**, planned in the design phase, is a procedure or method for solving a problem logically, and it can be described in natural language, a flowchart, or pseudocode. In the writing phase, the task or algorithm the program must perform is described in a particular programming language, and a **source file** is created with a text editor or source code editor.

### 3.2 Build Process

When you "compile" a C program, multiple stages happen behind the scenes. The full build pipeline is as follows.

```text
  hello.c          stdio.h
     │                │
     ▼                │
┌────────────┐        │
│Preprocessor│◀───────┘   (#include, #define expansion)
└────────────┘
     │
     ▼
  hello.i          (preprocessed source — all macros expanded)
     │
     ▼
┌────────────┐
│  Compiler  │             (C code → assembly code)
└────────────┘
     │
     ▼
  hello.s          (assembly source)
     │
     ▼
┌────────────┐
│ Assembler  │             (assembly → object code)
└────────────┘
     │
     ▼
  hello.o          (object file — machine code, not yet executable)
     │
     ▼
┌────────────┐
│   Linker   │◀─── library files (libc.a, etc.)
└────────────┘
     │
     ▼
  hello.exe        (final executable)
```

*Figure 6. Building an executable through preprocessing, compiling, assembling, and linking*

| Stage | Input | Output | What It Does |
|:------|:------|:-------|:-------------|
| **Preprocessor** | `.c` source | `.i` preprocessed | Expands `#include`, `#define`, `#ifdef`, removes comments |
| **Compiler** | `.i` preprocessed | `.s` assembly | Translates C to assembly, checks syntax and types |
| **Assembler** | `.s` assembly | `.o` object | Converts assembly to binary machine code |
| **Linker** | `.o` object(s) + libraries | executable | Combines object files, resolves external references (e.g., `printf`) |

*Table 6. Input, output, and role of each build stage*

One object file is produced per source file, and the linker combines the object files and libraries into a single executable. Visual Studio (Visual C++) uses the `.obj` extension for object files and `.exe` for executables (`first.c` → `first.obj` → `first.exe`), and it runs everything from preprocessing to linking with a single build command.

> **Key Point:** The preprocessor runs **before** actual compilation. It performs textual substitution and does not understand C syntax. This is why `#define` macros can cause subtle bugs.

In practice, the compiler driver (e.g., `gcc`) handles all stages automatically.

```bash
gcc hello.c -o hello      ← preprocessor + compiler + assembler + linker
gcc -E hello.c             ← preprocessor only (outputs .i)
gcc -S hello.c             ← preprocessor + compiler only (outputs .s)
gcc -c hello.c             ← preprocessor + compiler + assembler (outputs .o)
```

The text after `←` in the block above is an explanation, not part of the command. `gcc -E` writes its result to the screen (standard output), so to save a `.i` file, name the output file as in `gcc -E hello.c -o hello.i`.

> **Note:** **C/C++ compilers.** Compilers such as GCC, Visual C++, and C++ Builder provide both a C compiler and a C++ compiler, and they compile a source file as C if its extension is `.c` and as C++ if it is `.cpp`. C and C++ are different languages, but because of these compilers they are often used together, so a C program must be saved with the `.c` extension.

### 3.3 Errors

Errors in C programs fall into three categories based on **when** they are detected.

| Error Type | When Detected | Cause | Example |
|:-----------|:-------------|:------|:--------|
| **Compile Error** | Compilation | Syntax mistakes, type mismatches, undeclared variables | Missing `;`, wrong type |
| **Link Error** | Linking | Missing function definitions, unresolved symbols | Calling a function that does not exist |
| **Runtime Error** | Execution | Logic errors, illegal operations | Division by zero, null pointer access |

*Table 7. Classification of errors by detection time*

A compile error occurs at the faulty part when the compiler parses the code, and no object code is produced until all compile errors are gone. An executable is produced only when there are no link errors, and finding the cause of a link error requires examining how several source files relate to each other. A runtime error (execution error) means the program produces wrong results or terminates abnormally during execution.

**Compile errors** (syntax errors):
```c
#include <stdio.h>

int main(void) {
    printf("Hello\n")   // ← missing semicolon → compile error
    return 0;
}
```

**Link errors:**
```c
// main.c
void myFunction(void);  // declared but never defined anywhere

int main(void) {
    myFunction();        // ← linker cannot find the definition → link error
    return 0;
}
```

**Runtime errors** (logic errors):
```c
#include <stdio.h>

int main(void) {
    int a = 10, b = 0;
    printf("%d\n", a / b);  // ← division by zero → runtime error (crash)
    return 0;
}
```

Integer division by zero is undefined behavior in the C standard. On x86 systems it usually raises an exception that terminates the program abnormally, but other platforms may give different results.

> **Caution:** Compile errors are the easiest to fix because the compiler tells you the line number and what went wrong. Runtime errors are the hardest because the program compiles and runs, but produces wrong results or crashes unexpectedly.

### 3.4 Debugging

**Debugging** is the process of finding and fixing errors (bugs) in a program. Its core is checking whether the program runs in the correct order and whether the values of expressions used during execution are correct. The story of Grace Hopper's team finding an actual moth (bug) trapped in a relay of the Harvard Mark II computer in 1947 is often told in connection with the term, but the word bug was already used for machine defects before then.

**Common debugging strategies:**

| Strategy | Description |
|:---------|:------------|
| Read the error message | Compiler messages include the file name, line number, and error type, so always read them carefully |
| `printf` debugging | Insert `printf` statements to print variable values at key points in the program |
| Rubber duck debugging | Explain your code line by line to someone (or a rubber duck). The act of explaining often reveals the bug |
| Use a debugger | Use tools like `gdb` (GNU Debugger) to step through code, set breakpoints, and inspect variables |
| Divide and conquer | Comment out sections of code to narrow down where the error occurs |

*Table 8. Common debugging strategies*

**Basic debugging with `printf`:**

```c
#include <stdio.h>

int main(void) {
    int x = 10, y = 3;
    int result = x / y;

    printf("[DEBUG] x = %d, y = %d\n", x, y);       // check values
    printf("[DEBUG] result = %d\n", result);           // expected 3 (integer division)

    // ... rest of program
    return 0;
}
```

> **Note:** **Tip on compiling habits.** Develop the habit of compiling frequently. Compile after every few lines, not after writing the entire program. The sooner you catch errors, the easier they are to fix.

> **Note:** **Tip on warning options.** Enable all warnings during compilation with `gcc -Wall -Wextra`. The compiler can catch many potential bugs before you even run the program.

### 3.5 Integrated Development Environments

An **integrated development environment (IDE)** is a development tool that bundles a source code editor, compiler, linker, and debugger into one program. On Windows, Microsoft Visual Studio is widely used; when installing the free Visual Studio Community edition, selecting the "Desktop development with C++" workload installs the C and C++ development tools together.

| Concept | File | Contents |
|:--------|:-----|:---------|
| Project | `*.vcxproj` | All the information needed to build one program: the source and header files it uses, compile options, and link options |
| Solution | `*.sln` | A workspace that groups related projects that must be worked on together. Every project belongs to a solution, and creating a project creates a solution along with it |

*Table 9. Projects and solutions in Visual Studio*

The steps for making a C program in Visual Studio are: create an empty project, add a source file (`first.c`), write the code, build ([Build] → [Build Solution]), and run ([Debug] → [Start Without Debugging]). Even if "C++ File" is chosen when adding a new item, the file is compiled as C if its name ends in `.c`. The Solution Explorer window shows the list of projects in the solution and the source and header files in each project.

---

<br>

## Summary

| Concept | Key Summary |
|:--------|:-------------|
| Software and Programs | Software is a collection of programs, and a program is a set of instructions describing the work the computer must do. |
| Programming Languages | Machine language (binary), assembly (mnemonics), and high-level languages (C, Java, Python) get progressively closer to human language. |
| Machine-Dependent | Machine and assembly languages are tied to a specific CPU architecture and must be rewritten when the CPU changes. |
| Machine-Independent | High-level languages can be ported to many platforms by recompiling for each platform. |
| C History | Dennis Ritchie created C at Bell Labs in 1972, and the standards continued as K&R C, ANSI C (C89), C99, C11, and C23. |
| C Features | C is concise and flexible, offers performance and portability, and supports both high-level features and low-level access. |
| C Applications | C is used in operating systems, language implementations, databases, embedded systems, game engines, and more. |
| Why Learn C | C builds fundamentals, teaches the lingua franca of systems programming, and lays the foundation for C++, Java, Go, and Rust. |
| Development Process | Development proceeds through design, writing, compiling, and execution, and repeats with debugging when errors occur. |
| Build Process | An executable is produced through the preprocessor, compiler, assembler, and linker. |
| Compile Error | Syntax or type mistakes are caught during compilation. |
| Link Error | Missing definitions of functions or variables are caught during linking. |
| Runtime Error | Logic errors or illegal operations show up during execution. |
| Debugging | Read error messages, use `printf` debugging and `gdb`, and compile with `-Wall`. |
| Integrated Development Environment | An IDE bundles an editor, compiler, and debugger, and Visual Studio manages projects grouped into solutions. |

---

<br>

## Self-Check Questions

1. **Machine dependence and independence:** What must be done to run an assembly program and a C program written for an x86 CPU on an ARM CPU?

   <details>
   <summary>Answer</summary>

   Assembly is machine-dependent, so the x86 mnemonics cannot be used as they are, and the program must be rewritten with ARM instructions. C is machine-independent, so the same source code only needs to be recompiled with a compiler for ARM. However, any parts that use platform-specific features such as system calls may need changes.

   </details>

2. **Build stages:** Which stages run, and which file is produced, when you execute `gcc -c hello.c`? Why can that file not be executed directly?

   <details>
   <summary>Answer</summary>

   Preprocessing, compiling, and assembling run, producing the object file `hello.o`. The object file is in machine code, but its external references to functions defined elsewhere (in libraries), such as `printf`, are unresolved, so the linker must combine it with the libraries into an executable before it can run.

   </details>

3. **Classifying errors:** Name the type of error in each case. (a) The semicolon at the end of a statement is missing. (b) A function that is declared but never defined is called. (c) When computing an average, the last value instead of the total is divided by the count, and a wrong result is printed.

   <details>
   <summary>Answer</summary>

   (a) is a syntax mistake, so it is a compile error. (b) is a link error because the linker cannot find the function's definition. (c) is a runtime error (logic error) because compiling and linking succeed and the program runs, but it produces a wrong result.

   </details>

4. **Preprocessor:** List three things the preprocessor does, and explain how the preprocessor differs from the compiler.

   <details>
   <summary>Answer</summary>

   The preprocessor inserts the contents of header files named by `#include`, replaces macros defined by `#define`, and removes comments (it also handles conditional compilation such as `#ifdef`). The preprocessor runs before actual compilation and performs only textual substitution without understanding C syntax, whereas the compiler checks syntax and types and translates C code into assembly code.

   </details>
