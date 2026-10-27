# Chapter 1 Exercises — Programming and C Language

[Repository Guide](../../README.md) | [English](Exercises.md) | [한국어](Exercises.ko.md)

> **Last Updated:** 2026-10-27
>
> Warming-Up C Programming, 천정아, Ch 1

Exercises 1-11 are exercises 1-11 of Chapter 1 of the textbook, and Exercises 12 and 13 are programming assignments 1 and 2 of Chapter 1.

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

**Problem:** Write all the terms that refer to software.

**[Solution](Solutions.md#exercise-1-terms-that-refer-to-software)**

---

<br>

## Exercise 2: Statements About Programming Languages

**Textbook Problem:** Chapter 1 exercise 2

**Problem:** Choose all the incorrect statements about programming languages.

- ① A program written in machine language can run on many kinds of CPUs without conversion.
- ② Assembly language is the language that uses mnemonic symbols, each corresponding one to one to an instruction made of 0s and 1s.
- ③ Assembly language makes it possible to write machine-independent programs.
- ④ A high-level language makes it possible to write programs that are not tied to the kind of CPU or the characteristics of the hardware.
- ⑤ C, C++, Java, and Python are high-level languages.
- ⑥ A compiler translates a program written in a high-level language into machine language.
- ⑦ Machine language and assembly language are high-level languages.

**[Solution](Solutions.md#exercise-2-statements-about-programming-languages)**

---

<br>

## Exercise 3: The Program That Translates a Source File into Machine Language

**Textbook Problem:** Chapter 1 exercise 3

**Problem:** What is the program that translates a source file written in a high-level language into machine language called?

**[Solution](Solutions.md#exercise-3-the-program-that-translates-a-source-file-into-machine-language)**

---

<br>

## Exercise 4: Reasons to Learn C

**Textbook Problem:** Chapter 1 exercise 4

**Problem:** Choose all the statements that are not reasons to learn the C language.

- ① C serves as a kind of common language among programmers.
- ② Knowing C helps you use a wide range of programming information.
- ③ If you know C, you do not need to learn other languages.
- ④ C also helps you understand the basic concepts of programming.
- ⑤ If you use C, you do not need to know how a program works internally.

**[Solution](Solutions.md#exercise-4-reasons-to-learn-c)**

---

<br>

## Exercise 5: Application Areas of C

**Textbook Problem:** Chapter 1 exercise 5

**Problem:** Choose the incorrect statement about the application areas of the C language.

- ① C is suitable for developing system programs for which portability is essential.
- ② C is suitable for developing programs for which performance is the top priority.
- ③ C is mainly used to develop programs in environments with ample system resources, such as embedded systems.
- ④ C is mainly used to develop high-performance libraries such as graphics or numerical analysis libraries.
- ⑤ C/C++ is mainly used to develop games and game engines.

**[Solution](Solutions.md#exercise-5-application-areas-of-c)**

---

<br>

## Exercise 6: Advantages of C

**Textbook Problem:** Chapter 1 exercise 6

**Problem:** Choose all the statements that are not advantages of the C language.

- ① C has a concise syntax and provides the core features essential for program development.
- ② C supports object-oriented programming.
- ③ C provides assembly-level features while still allowing machine-independent programs.
- ④ C is easy to learn and needs no particular care when used.
- ⑤ C gives developers the greatest possible freedom.
- ⑥ C makes it possible to develop programs with excellent performance.

**[Solution](Solutions.md#exercise-6-advantages-of-c)**

---

<br>

## Exercise 7: Programs Running on Special-Purpose Devices

**Textbook Problem:** Chapter 1 exercise 7

**Problem:** What is a program that runs on a device with a built-in special-purpose computer, such as a home appliance, a car, or network equipment, called?

**[Solution](Solutions.md#exercise-7-programs-running-on-special-purpose-devices)**

---

<br>

## Exercise 8: The C and C++ Languages

**Textbook Problem:** Chapter 1 exercise 8

**Problem:** Choose the incorrect statement about the C and C++ languages.

- ① C++ is the language that inherits C and adds object orientation.
- ② C provides compatibility with C++. That is, a valid C++ program is a C program.
- ③ A simple way to turn a program written in C into C++ is to change the extension of the source file from `c` to `cpp`.
- ④ Most C compilers are C/C++ compilers.
- ⑤ A library developed in C can be used in a C++ program.

**[Solution](Solutions.md#exercise-8-the-c-and-c-languages)**

---

<br>

## Exercise 9: The Development Process of a C Program

**Textbook Problem:** Chapter 1 exercise 9

**Problem:** The following is the general development process of a C program. Write the steps that belong in blanks (A) and (B).

```mermaid
flowchart LR
    A["(A)"] --> B["Write the source code"] --> C["(B)"] --> D["Run"]
```

*Figure 1. The development process of a C program with blanks*

**[Solution](Solutions.md#exercise-9-the-development-process-of-a-c-program)**

---

<br>

## Exercise 10: Statements About the Development Process

**Textbook Problem:** Chapter 1 exercise 10

**Problem:** Choose all the incorrect statements about the development process of a C program.

- ① The algorithm is derived in the program design step.
- ② In the program design step, the algorithm is expressed in a specific programming language.
- ③ A text editor is used to write the source code.
- ④ The preprocessor prepares a source file so that it can be compiled.
- ⑤ When there are several source files, they are all merged into one and compiled.
- ⑥ When there is only one object file, there is no need to link.
- ⑦ In the link step, libraries are connected with the object files.

**[Solution](Solutions.md#exercise-10-statements-about-the-development-process)**

---

<br>

## Exercise 11: Projects and Solutions in Visual Studio

**Textbook Problem:** Chapter 1 exercise 11

**Problem:** Choose all the incorrect statements about projects and solutions in Visual Studio.

- ① A solution contains the information on source files and header files, and the compile and link options.
- ② Creating a project creates a file with the `.vcxproj` extension.
- ③ When a project is created, a solution is created with it by default.
- ④ A project must belong to a solution.
- ⑤ Several related projects can be grouped and managed in a solution.
- ⑥ Solutions and projects correspond one to one. That is, there is one project per solution.

**[Solution](Solutions.md#exercise-11-projects-and-solutions-in-visual-studio)**

---

<br>

## Exercise 12: A Program That Prints Version Information

**Textbook Problem:** Chapter 1 programming assignment 1

**Problem:** In Visual Studio, write a C program under the following conditions, build it, and run it.

1. Project name: `second`
2. Project location: `C:\work\chap01`
3. Project type: Empty Project (C++, Windows, Console)
4. Source file name: `second.c`
5. Source file contents:

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

**Sample Run:**

```text
Second C Program
Date    : 2022.1.1
Version : 1.0
```

**[Solution](Solutions.md#exercise-12-a-program-that-prints-version-information)**

---

<br>

## Exercise 13: A Program That Prints the Results of the Four Arithmetic Operations

**Textbook Problem:** Chapter 1 programming assignment 2

**Problem:** In Visual Studio, write a C program under the following conditions, build it, and run it.

1. Project name: `calculator`
2. Project location: `C:\work\chap01`
3. Project type: Empty Project (C++, Windows, Console)
4. Source file name: `calculator.c`
5. Source file contents:

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

**Sample Run:**

```text
55 + 33 = 88
55 - 33 = 22
55 * 33 = 1815
55 / 33 = 1
```

**[Solution](Solutions.md#exercise-13-a-program-that-prints-the-results-of-the-four-arithmetic-operations)**
