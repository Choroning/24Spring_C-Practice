# [Spring 2024] C Programming Practice

![Last Commit](https://img.shields.io/github/last-commit/Choroning/24Spring_C-Practice)
![Languages](https://img.shields.io/github/languages/top/Choroning/24Spring_C-Practice)

This repository archives bilingual lecture notes and coursework for the Computer Language Ⅰ and Computer Language and Training Ⅰ courses.

*Author: Cheolwon Park (Korea University Sejong, CSE) - Year 1 (Freshman) as of 2024*
<br><br>

## 📑 Table of Contents

- [About This Repository](#about-this-repository)
- [Course Information](#course-information)
- [Prerequisites](#prerequisites)
- [Repository Structure](#repository-structure)
- [License](#license)

---


<br><a name="about-this-repository"></a>
## 📝 About This Repository

This repository contains the lecture notes, exercises, assignment explanations, and C code written for a university-level C programming course.

- `Lecture-Notes/` holds, for each chapter, lecture notes that organize the key concepts (`Concepts_Lecture`), and Chapters 4-10 also hold exercises that transcribe the chapter lab problems of Computer Language Ⅰ (`Exercises`) and their solutions (`Solutions`). The units follow the chapter numbers (Chapters 1-10) of Warming-Up C Programming, the textbook of Computer Language Ⅰ, and are numbered `Ch01`-`Ch10`.
- Every lecture note, exercise set, and solution set comes as an English file (`.md`) and a Korean file (`.ko.md`) with the same structure.
- `HW01`-`HW10` in `Coursework/` hold Assignments 1-10 of Computer Language and Training Ⅰ. Each assignment has an assignment explanation that explains the problems and their solutions (`Assignment-Explanation`) and the author's own solution code (`Solution/`), and the assignment explanations also come as English and Korean file pairs.
- `Lab04`-`Lab10` in `Coursework/` hold the author's own C code that solves the lab problems of Chapters 4-10, and the solutions (`Solutions`) of each unit explain this code.
- The solution code shows one way to solve each problem and is not the only correct answer.
- The code files carry **Doxygen-style headers** that record the problem title, author, and date.
- All C code was compiled under the C99 standard with GCC, with standard functions standing in for the Visual Studio-specific functions.

> **🤖 AI Agent Usage**
> [Claude Code](https://claude.ai/download) was used to organize and translate the lecture notes and exercises, to write the solutions and assignment explanations, and to restructure the repository. Computer Language and Training Ⅰ required students to always write code on their own, and all lab code and assignment solution code was written by the author.

<br><a name="course-information"></a>
## 📚 Course Information

- **Semester:** Spring 2024 (March - June)
- **Affiliation:** Korea University Sejong

| Course&nbsp;Code| Course            | Type          | Instructor      | Department                              |
|:----------:|:------------------|:-------------:|:---------------:|:----------------------------------------|
|`DCCS101-04`|COMPUTER LANGUAGE Ⅰ|General Studies|Prof. Younghee&nbsp;Im|Department of Computer Science and Software Engineering|
|`DCCS103-03`|COMPUTER LANGUAGE AND TRAINING Ⅰ|General Studies|Prof. Jonguk&nbsp;Lee|Department of Computer Science and Software Engineering|

### Course Overview

Two general studies courses on the fundamentals of computer programming in C. Computer Language Ⅰ is a theory-oriented course in which students acquire the basic theory and skills of computer programming through C, a structured programming language, and the lectures, centered on the textbook, aim at an understanding of the basic concepts of programming languages, the way data is represented in a computer, and the operators and control statements of C, among others. Following Chapters 1-10 of the textbook, it covers programming and the C language, the basics of C programs, data types and variables, operators, control statements, functions, arrays, pointers, strings, and structures, and classes consist of theory lectures, labs, and quizzes, with chapter lab assignments and theory homework (solving the textbook exercises). Computer Language and Training Ⅰ is a lab course linked to Computer Language Ⅰ that aims at a precise understanding of the basic concepts of C and at building C programming skills through practice with a variety of examples. Each week covers the solutions to the previous assignment, textbook theory, and practice with textbook problems, and students complete Assignments 1-10. The lecture notes and lab code in this repository are based on the lecture slides and lab assignments of Computer Language Ⅰ, and the assignment explanations and solution code on the assignments of Computer Language and Training Ⅰ. The instructors, schedule and class format, assessment, course policies, weekly plan and progress, and references are in the [course information document](Course-Information.md).

<br><a name="prerequisites"></a>
## ✅ Prerequisites

- A basic understanding of programming concepts is required. The syllabi of the two courses designate no prerequisites.
- A C/C++ compiler (e.g., GCC) must be installed. The code in this repository compiles with a compiler that supports C99 or later, and files that use Visual Studio-specific functions (`scanf_s`, `gets_s`) or `<windows.h>` need standard functions in their place on other compilers.
- Familiarity with command-line tools is required.

- **💻 Development Environment**

| Tool | Company |  OS  | Notes |
|:-----|:-------:|:----:|:------|
|Visual Studio|Microsoft|Windows|C/C++ Extension Pack|
|Visual Studio Code|Microsoft|macOS|C/C++ Extension Pack|
|Xcode|Apple Inc.|macOS|Most used IDE|

<br><a name="repository-structure"></a>
## 🗂 Repository Structure

```plaintext
24Spring_C-Practice
├── Lecture-Notes               Lecture notes, exercises, and solutions by chapter
├── Coursework                  Computer Language and Training Ⅰ assignments and C lab code by chapter
├── images                      Figures in the exercises and assignments
├── Course-Information.ko.md    Course operations
├── Course-Information.md
├── LICENSE                     Documentation license (CC BY-NC-SA 4.0)
├── LICENSE-CODE                Code license (PolyForm Noncommercial 1.0.0)
├── README.ko.md
└── README.md
```

The units are listed in the [`Lecture-Notes` index](Lecture-Notes/README.md), and the assignments and lab code in the [`Coursework` index](Coursework/README.md).

<br><a name="license"></a>
## 🤝 License

The documents in this repository (lecture notes, explanations, and summary sheets) are licensed under [CC BY-NC-SA 4.0](LICENSE), and the code under [PolyForm Noncommercial 1.0.0](LICENSE-CODE). Figures and example code taken from lecture slides and textbooks, as well as assignment handouts and template code distributed by the course, belong to their original authors and are not covered by these licenses.

---
