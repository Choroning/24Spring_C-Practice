# Chapter 1 Solutions — Programming and C Language

[Repository Guide](../../README.md) | [English](Solutions.md) | [한국어](Solutions.ko.md)

> **Last Updated:** 2026-10-27
>
> Warming-Up C Programming, 천정아, Ch 1

---

<br>

## Table of Contents

- [Exercise 1: Terms That Refer to Software](#exercise-1-terms-that-refer-to-software)
- [Exercise 2: Statements About Programming Languages](#exercise-2-statements-about-programming-languages)
- [Exercise 3: The Program That Translates a Source File into Machine Language](#exercise-3-the-program-that-translates-a-source-file-into-machine-language)
- [Exercise 4: Reasons to Learn C](#exercise-4-reasons-to-learn-c)
- [Exercise 5: Application Areas of C](#exercise-5-application-areas-of-c)
- [Exercise 6: Advantages of C](#exercise-6-advantages-of-c)
- [Exercise 7: Programs Running on Special-Purpose Devices](#exercise-7-programs-running-on-special-purpose-devices)
- [Exercise 8: The C and C++ Languages](#exercise-8-the-c-and-c-languages)
- [Exercise 9: The Development Process of a C Program](#exercise-9-the-development-process-of-a-c-program)
- [Exercise 10: Statements About the Development Process](#exercise-10-statements-about-the-development-process)
- [Exercise 11: Projects and Solutions in Visual Studio](#exercise-11-projects-and-solutions-in-visual-studio)
- [Exercise 12: A Program That Prints Version Information](#exercise-12-a-program-that-prints-version-information)
- [Exercise 13: A Program That Prints the Results of the Four Arithmetic Operations](#exercise-13-a-program-that-prints-the-results-of-the-four-arithmetic-operations)

---

<br>

## Exercise 1: Terms That Refer to Software

**Textbook Problem:** Chapter 1 exercise 1

**Problem:** Write all the terms that refer to software. The full problem is in [Exercise 1](Exercises.md#exercise-1-terms-that-refer-to-software).

### Solution

**Answer:** Program, application program (application), app

**Explanation:** Software is the set of programs that run on hardware and tell the hardware what to do ([Chapter 1, Section 1.1](Concepts_Lecture.md#11-software-and-programs)). Software is therefore also referred to as programs, software that handles a user's tasks is called an application program (application), and an application that runs on a smartphone is commonly called an app.

- **Program:** A set of instructions written in a programming language to perform a specific task.
- **Application program:** Software that runs on top of system software such as the operating system to serve the user's purpose (writing documents, games, and so on).
- **App:** Short for application, it mainly refers to application programs used on smartphones and tablets.

---

<br>

## Exercise 2: Statements About Programming Languages

**Textbook Problem:** Chapter 1 exercise 2

**Problem:** Of seven statements about machine language, assembly language, high-level languages, and compilers, choose all the incorrect ones. The options are in [Exercise 2](Exercises.md#exercise-2-statements-about-programming-languages).

### Solution

**Answer:** ①, ③, ⑦

**Explanation:** Machine language and assembly language are low-level languages tied to a specific CPU, and high-level languages are machine-independent ([Chapter 1, Section 1.2](Concepts_Lecture.md#12-programming-languages), [Section 1.3](Concepts_Lecture.md#13-machine-dependent-vs-machine-independent)).

- **① (incorrect):** Machine instructions are binary codes that a specific CPU executes directly, and each CPU architecture has a different instruction set. A machine language program runs only on that CPU, so it must be rewritten when the CPU changes.
- **② (correct):** Assembly language represents machine instructions with mnemonics such as `MOV` and `ADD`, and each mnemonic corresponds to one machine instruction.
- **③ (incorrect):** Because assembly language corresponds one to one to machine language, it is machine-dependent just like machine language. An assembly program for x86 cannot run on an ARM CPU.
- **④ (correct):** Source code written in a high-level language can run on many platforms when translated by each system's compiler.
- **⑤ (correct):** C, C++, Java, and Python are all high-level languages whose syntax is close to human language.
- **⑥ (correct):** A compiler is the program that translates source code written in a high-level language into machine language all at once before execution (Exercise 3).
- **⑦ (incorrect):** Machine language and assembly language are low-level languages close to the hardware.

---

<br>

## Exercise 3: The Program That Translates a Source File into Machine Language

**Textbook Problem:** Chapter 1 exercise 3

**Problem:** Write the name of the program that translates a source file written in a high-level language into machine language. The full problem is in [Exercise 3](Exercises.md#exercise-3-the-program-that-translates-a-source-file-into-machine-language).

### Solution

**Answer:** Compiler

**Explanation:** A compiler translates the entire source code into machine language all at once before execution ([Chapter 1, Section 1.2](Concepts_Lecture.md#12-programming-languages)). It is distinguished from an interpreter, which translates and executes one line at a time at run time. C is a typical language that uses a compiler.

> **Note:** **Compilation in the broad and narrow senses.** The compiler in this problem refers to the whole translator that turns source code into machine language. When the build of a C program is divided into steps, the compiler in the narrow sense translates the preprocessed C code into assembly code, the assembler turns it into an object file in machine language, and the linker combines object files and libraries into an executable file ([Chapter 1, Section 3.2](Concepts_Lecture.md#32-build-process)). A compiler driver such as `gcc` performs these steps at once.

---

<br>

## Exercise 4: Reasons to Learn C

**Textbook Problem:** Chapter 1 exercise 4

**Problem:** Of five statements about reasons to learn the C language, choose all the ones that are not reasons. The options are in [Exercise 4](Exercises.md#exercise-4-reasons-to-learn-c).

### Solution

**Answer:** ③, ⑤

**Explanation:** The reasons to learn C come down to three: foundational strength, the common language of systems programming, and the foundation for other languages ([Chapter 1, Section 2.4](Concepts_Lecture.md#24-why-learn-c)).

- **① (a reason):** OS APIs, hardware interfaces, and countless algorithms and libraries are developed and published in C, so C serves as a common language among programmers.
- **② (a reason):** Since much material and many libraries are written in C, knowing C makes it easy to use such programming information.
- **③ (not a reason):** Each kind of application has a language suited to it, so C alone cannot solve every problem. Knowing C only makes it easier to learn other languages such as C++, Java, and C# that borrow C's syntax and semantics.
- **④ (a reason):** C makes you work directly with basic programming concepts such as control structures, functions, and user-defined types.
- **⑤ (not a reason):** The opposite is true. C deals directly with the memory layout, pointers, and manual resource management, so it helps you understand how programs work internally, which other languages hide.

---

<br>

## Exercise 5: Application Areas of C

**Textbook Problem:** Chapter 1 exercise 5

**Problem:** Of five statements about the application areas of the C language, choose the incorrect one. The options are in [Exercise 5](Exercises.md#exercise-5-application-areas-of-c).

### Solution

**Answer:** ③

**Explanation:** An embedded system is not an environment with ample system resources but one with limited resources. The computers built into home appliances and car control units have limited memory, processing power, and electric power, and C suits such environments because it uses little memory and compiles into efficient machine code ([Chapter 1, Section 2.2](Concepts_Lecture.md#22-features), [Section 2.3](Concepts_Lecture.md#23-applications)).

- **① (correct):** Code written in standard C can be compiled on almost any platform, so C is used to develop system programs such as operating systems.
- **② (correct):** C has little run-time overhead, so it suits programs for which performance is the top priority.
- **④ (correct):** High-performance libraries for graphics, numerical analysis, and similar areas are often developed in C.
- **⑤ (correct):** Game engines (for example, Unreal Engine) are mainly developed in C/C++.

---

<br>

## Exercise 6: Advantages of C

**Textbook Problem:** Chapter 1 exercise 6

**Problem:** Of six statements about the features of the C language, choose all the ones that are not advantages. The options are in [Exercise 6](Exercises.md#exercise-6-advantages-of-c).

### Solution

**Answer:** ②, ④

**Explanation:** The advantages of C are its concise syntax, flexibility, high performance, portability, and support for both high-level and low-level features, and its drawback is that it is hard to learn and to use ([Chapter 1, Section 2.2](Concepts_Lecture.md#22-features)).

- **① (an advantage):** C is a concise language with few keywords and a minimal language design.
- **② (not an advantage):** C is a procedural language in which a program is written as functions, and it does not support object-oriented programming. Object-oriented programming is supported by C++, C#, Java, Python, and others.
- **③ (an advantage):** C provides assembly-level low-level features such as direct memory access through pointers and bitwise operations, yet as a high-level language its programs written in standard C are machine-independent. Having both properties is a representative advantage of C.
- **④ (not an advantage):** Because of its low-level features and few restrictions, C is hard both to learn and to use. With no array bounds checking or garbage collector, the programmer must take particular care when handling pointers and memory.
- **⑤ (an advantage):** C is a flexible language with few restrictions, letting the programmer exercise fine control.
- **⑥ (an advantage):** C compiles into efficient machine code, so it can produce programs with excellent performance.

---

<br>

## Exercise 7: Programs Running on Special-Purpose Devices

**Textbook Problem:** Chapter 1 exercise 7

**Problem:** Write the name of a program that runs on a device with a built-in special-purpose computer, such as a home appliance, a car, or network equipment. The full problem is in [Exercise 7](Exercises.md#exercise-7-programs-running-on-special-purpose-devices).

### Solution

**Answer:** Embedded program

**Explanation:** The device with a built-in special-purpose computer is itself an embedded system, and a program that runs on that device is an embedded program ([Chapter 1, Section 2.3](Concepts_Lecture.md#23-applications)). The problem asks for the program, not the device, so the two terms must be distinguished. Because embedded programs run in environments with limited system resources, they are often written in C (Exercise 5).

---

<br>

## Exercise 8: The C and C++ Languages

**Textbook Problem:** Chapter 1 exercise 8

**Problem:** Of five statements about the relationship between C and C++, choose the incorrect one. The options are in [Exercise 8](Exercises.md#exercise-8-the-c-and-c-languages).

### Solution

**Answer:** ②

**Explanation:** The direction of compatibility is reversed. C++ was created by inheriting C, so it is C++ that provides compatibility with C, and C programs fall within the category of C++ programs. A valid C program can therefore be treated as a C++ program, but a C++ program that uses features found only in C++, such as classes, is not a C program.

- **① (correct):** C++ is the language that adds object-oriented features such as classes and inheritance to C.
- **③ (correct):** Compilers such as GCC and Visual C++ compile a source file as C if its extension is `.c` and as C++ if it is `.cpp`, so changing the extension makes the same code compile as a C++ program ([Chapter 1, Section 3.2](Concepts_Lecture.md#32-build-process)).
- **④ (correct):** Most C compilers serve as both a C compiler and a C++ compiler.
- **⑤ (correct):** A library developed in C can also be called from a C++ program.

> **Note:** **The limits of compatibility between C and C++.** The textbook describes C as if it were a subset of C++, but the two languages are standardized separately and differ in some places. For example, C allows a `void *` to be assigned implicitly to another pointer type, as in `int *p = malloc(sizeof(int));`, whereas C++ requires a cast, and C code that uses `class` or `new` as a variable name does not compile in C++. Also, calling a C library function from C++ requires the `extern "C"` linkage specification on the function declarations, which the standard C headers already provide. So the extension change in ③ is a simple method that works for most C code, but not every piece of C code becomes C++ code unchanged.

---

<br>

## Exercise 9: The Development Process of a C Program

**Textbook Problem:** Chapter 1 exercise 9

**Problem:** In the general development process of a C program, write step (A), which comes before writing the source code, and step (B), which comes before running. The full problem and figure are in [Exercise 9](Exercises.md#exercise-9-the-development-process-of-a-c-program).

### Solution

**Answer:** (A) Program design, (B) Compilation (build)

**Explanation:** A C program is developed in the order design, code writing, compilation, and execution, and when an error occurs it goes back to an earlier step through debugging ([Chapter 1, Section 3.1](Concepts_Lecture.md#31-development-process)).

- **(A) Program design:** The step in which the problem is analyzed and an algorithm, the procedure for solving it, is devised. The algorithm is described in natural language, flowcharts, or pseudocode.
- **(B) Compilation:** The step in which the source code is translated into machine language to make an executable file. This step is in fact the build process made of preprocessing, compiling, assembling, and linking, and in Visual Studio it is performed by the single Build Solution command ([Chapter 1, Section 3.2](Concepts_Lecture.md#32-build-process)).

---

<br>

## Exercise 10: Statements About the Development Process

**Textbook Problem:** Chapter 1 exercise 10

**Problem:** Of seven statements about the development process of a C program, choose all the incorrect ones. The options are in [Exercise 10](Exercises.md#exercise-10-statements-about-the-development-process).

### Solution

**Answer:** ②, ⑤, ⑥

**Explanation:** The product of the design step is an algorithm that is not tied to a particular language, compilation is done per source file, and making an executable file always requires linking ([Chapter 1, Section 3.1](Concepts_Lecture.md#31-development-process), [Section 3.2](Concepts_Lecture.md#32-build-process)).

- **① (correct):** In the design step, the problem is analyzed and an algorithm is derived.
- **② (incorrect):** In the design step, the algorithm is expressed in natural language, flowcharts, or pseudocode. Describing the algorithm in a specific programming language is the next step, code writing.
- **③ (correct):** The source code is written with a text editor or the source code editor of an IDE.
- **④ (correct):** Before compilation, the preprocessor includes the header files named by `#include`, replaces `#define` macros, and removes comments, preparing the source file so that it can be compiled.
- **⑤ (incorrect):** Source files are not merged into one; each file is compiled separately, producing one object file per source file. Combining several object files into one executable file is the linker's job.
- **⑥ (incorrect):** Even with only one object file, the external references to functions defined in libraries, such as `printf`, are still unresolved, so the object file must be linked with the libraries to make an executable file.
- **⑦ (correct):** In the link step, the linker connects the object files with the libraries to make an executable file.

---

<br>

## Exercise 11: Projects and Solutions in Visual Studio

**Textbook Problem:** Chapter 1 exercise 11

**Problem:** Of six statements about projects and solutions in Visual Studio, choose all the incorrect ones. The options are in [Exercise 11](Exercises.md#exercise-11-projects-and-solutions-in-visual-studio).

### Solution

**Answer:** ①, ⑥

**Explanation:** A project holds the information needed to build one program, and a solution is a workspace that groups and manages related projects ([Chapter 1, Section 3.5](Concepts_Lecture.md#35-integrated-development-environments)).

- **① (incorrect):** The list of source and header files and the compile and link options are stored not in the solution but in the project (the `.vcxproj` file). The solution (the `.sln` file) records which projects are managed together.
- **② (correct):** Creating a Visual C++ project creates a project file with the `.vcxproj` extension.
- **③ (correct):** Creating a new project also creates, by default, a solution that contains it.
- **④ (correct):** In Visual Studio, a project is always contained in and managed through a solution.
- **⑤ (correct):** Several related projects can be added to one solution and managed together.
- **⑥ (incorrect):** One solution can hold several projects, so the two do not correspond one to one.

---

<br>

## Exercise 12: A Program That Prints Version Information

**Textbook Problem:** Chapter 1 programming assignment 1

**Problem:** In Visual Studio, create an empty project `second` in `C:\work\chap01`, add the source file `second.c` with the given contents, then build and run it. The full problem and source code are in [Exercise 12](Exercises.md#exercise-12-a-program-that-prints-version-information).

### Solution

**Approach:** Since the problem gives all the source code, the goal is to practice creating, building, and running a project in Visual Studio ([Chapter 1, Section 3.5](Concepts_Lecture.md#35-integrated-development-environments)).

1. **Create the project:** In [Create a new project], choose Empty Project with the C++, Windows, and Console conditions, and enter `second` as the project name and `C:\work\chap01` as the location. A solution is created along with it.
2. **Add the source file:** Add a new item to [Source Files] in Solution Explorer and name it `second.c`. Because the extension is `.c`, the file is compiled as C even if the C++ File item is chosen.
3. **Build:** [Build] → [Build Solution] performs preprocessing, compiling, assembling, and linking at once and produces the executable file `second.exe`.
4. **Run:** [Debug] → [Start Without Debugging] runs the program, and the result appears in a console window.

Each line of the source code does the following ([Chapter 2, Section 1.1](../Ch02_C-Program-Basics/Concepts_Lecture.md#11-program-structure)).

- **`#include <stdio.h>`:** The preprocessor includes the contents of the standard input/output header file, which provides the declaration of the `printf` function.
- **`int main(void)`:** The entry point function, called first when the program starts.
- **`printf(...)`:** Prints the string inside the double quotes as it is and moves to a new line at `\n`. The four spaces after `Date` line its colon up with the one in the `Version` line.
- **`return 0;`:** `main` returns 0 to tell the operating system that the program terminated normally.

**Code:**

```c
#include <stdio.h>

int main(void)
{
    printf("Second C Program\n");
    printf("Date    : 2022.1.1\n");
    printf("Version : 1.0\n");

    return 0;
}
```

**Output:** With gcc, compile and run the same code with `gcc -std=c99 -Wall second.c -o second`.

```text
Second C Program
Date    : 2022.1.1
Version : 1.0
```

---

<br>

## Exercise 13: A Program That Prints the Results of the Four Arithmetic Operations

**Textbook Problem:** Chapter 1 programming assignment 2

**Problem:** In Visual Studio, create an empty project `calculator` in `C:\work\chap01`, add the source file `calculator.c`, which prints the results of the four arithmetic operations on 55 and 33, then build and run it. The full problem and source code are in [Exercise 13](Exercises.md#exercise-13-a-program-that-prints-the-results-of-the-four-arithmetic-operations).

### Solution

**Approach:** Creating, building, and running the project follows the same procedure as Exercise 12. This program shows that `printf` converts the value of each following argument to a decimal integer and prints it in place of a `%d` in the format string ([Chapter 2, Section 2.2](../Ch02_C-Program-Basics/Concepts_Lecture.md#22-printf)).

- **Format string:** In `"55 + 33 = %d\n"`, the characters other than `%d`, `55 + 33 = `, are printed as they are. That part is a string, so it is not computed.
- **Argument:** The second argument `55 + 33` is an expression, so it is evaluated before the function is called and 88 goes in place of `%d`.
- **Integer division:** Since both operands of `55 / 33` are integers, the result is 1, the quotient with the fractional part discarded ([Chapter 4, Section 2.2](../Ch04_Operators/Concepts_Lecture.md#22-integer-division-vs-float-division)). Because 55 = 33 × 1 + 22, the remainder 22 can be obtained with `55 % 33`.

**Code:**

```c
#include <stdio.h>

int main(void)
{
    printf("55 + 33 = %d\n", 55 + 33);
    printf("55 - 33 = %d\n", 55 - 33);
    printf("55 * 33 = %d\n", 55 * 33);
    printf("55 / 33 = %d\n", 55 / 33);

    return 0;
}
```

**Output:**

```text
55 + 33 = 88
55 - 33 = 22
55 * 33 = 1815
55 / 33 = 1
```
