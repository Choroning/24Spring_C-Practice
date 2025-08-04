# [2024학년도 봄학기] C언어 연습

![Last Commit](https://img.shields.io/github/last-commit/Choroning/24Spring_C-Practice)
![Languages](https://img.shields.io/github/languages/top/Choroning/24Spring_C-Practice)

이 레포지토리는 대학 강의 및 과제를 위해 작성된 C언어 예제 및 실습 코드를 체계적으로 정리하고 보관합니다. 

*작성자: 박철원 (고려대학교(세종), 컴퓨터융합소프트웨어학과) - 2024년 기준 1학년*
<br><br>

## 📑 목차

- [레포지토리 소개](#about-this-repository)
- [강의 정보](#course-information)
- [사전 요구사항](#prerequisites)
- [레포지토리 구조](#repository-structure)
- [라이선스](#license)

---


<br><a name="about-this-repository"></a>
## 📝 레포지토리 소개

이 레포지토리에는 대학 수준의 C언어 프로그래밍 과목을 위해 작성된 코드가 포함되어 있습니다:

- 강의에서 소개한 코드
- 각 과제의 솔루션
- 추가적인 연습 문제

<br><a name="course-information"></a>
## 📚 강의 정보

- **학기:** 2024학년도 봄학기 (3월 - 6월)
- **소속:** 고려대학교(세종)

|학수번호      |강의명    |이수구분|교수자|개설학과|
|:----------:|:-------|:----:|:------:|:----------------|
|`DCCS101-04`|컴퓨터언어Ⅰ|교양|임영희 교수|컴퓨터융합소프트웨어학과|
|`DCCS103-03`|컴퓨터언어실습Ⅰ|교양|이종욱 교수|컴퓨터융합소프트웨어학과|


- **📖 참고 자료**
  
| 유형 | 내용 |
|:----:|:---------|
|교재|Warming-Up C Programming 2판(천정아)|
|교재|문제풀이 중심의 C언어 연습(김용일 외 1인)|
|기타|교수자 제공 강의자료|

<br><a name="prerequisites"></a>
## ✅ 사전 요구사항

- 프로그래밍 개념에 대한 기본적인 이해
- C/C++ 컴파일러 설치(예: GCC)
- 커맨드 라인 툴 사용에 익숙함

- **💻 개발 환경**

| 도구 | 회사 |  운영체제  | 비고 |
|:-----|:-------:|:----:|:------|
|Visual Studio|Microsoft|Windows|C/C++ Extension Pack|
|Visual Studio Code|Microsoft|macOS|C/C++ Extension Pack|
|Xcode|Apple Inc.|macOS|가장 많이 사용한 IDE|

<br><a name="repository-structure"></a>
## 🗂 레포지토리 구조

```plaintext
24Spring_C-Practice
├── Chapter03_Data-Types-and-Variables
│   ├── A10303-1_C03-Problems.md
│   ├── A10303-1_C03Q1.c
│   ├── A10303-1_C03Q2.c
│   ├── A10303-1_C03Q3.c
│   └── A10303-1_C03Q4.c
├── Chapter04_Operators
│   ├── A10104-1_C04-Problems.md
│   ├── A10104-1_C04Q1.c
│   ├── A10104-1_C04Q2.c
│   ├── A10104-1_C04Q3.c
│   ├── A10104-1_C04Q4.c
│   ├── A10303-1_C04-Problems.md
│   ├── A10303-1_C04Q1.c
│   ├── A10303-1_C04Q2.c
│   └── A10303-1_C04Q3.c
├── Chapter05_Control-Statements
│   ├── A10104-1_C05-Problems.md
│   ├── A10104-1_C05Q1.c
│   ├── A10104-1_C05Q2.c
│   ├── A10104-1_C05Q3.c
│   ├── A10104-2_C05-Problems.md
│   ├── A10104-2_C05Q1.c
│   ├── A10104-2_C05Q2.c
│   ├── A10303-1_C05-Problems.md
│   ├── A10303-1_C05Q1.c
│   ├── A10303-2_C05-Problems.md
│   ├── A10303-2_C05Q1.c
│   ├── A10303-2_C05Q2.c
│   ├── A10303-2_C05Q3.c
│   ├── A10303-2_C05Q4.c
│   ├── A10303-2_C05Q5.c
│   ├── A10303-3_C05-Problems.md
│   ├── A10303-3_C05Q1.c
│   ├── A10303-3_C05Q2.c
│   ├── A10303-3_C05Q3.c
│   └── A10303-3_C05Q4.c
├── Chapter06_Functions
│   ├── A10104-1_C06-Problems.md
│   ├── A10104-1_C06Q1.c
│   ├── A10104-1_C06Q2.c
│   ├── A10104-1_C06Q3.c
│   ├── A10303-1_C06-Problems.md
│   ├── A10303-1_C06Q1.c
│   └── A10303-1_C06Q2.c
├── Chapter07_Arrays
│   ├── A10104-1_C07-Problems.md
│   ├── A10104-1_C07Q1.c
│   ├── A10104-1_C07Q2.c
│   ├── A10104-1_C07Q3.c
│   ├── A10303-1_C07-Problems.md
│   ├── A10303-1_C07Q1.c
│   ├── A10303-1_C07Q2.c
│   └── A10303-1_C07Q3.c
├── Chapter08_Pointers
│   ├── A10104-1_C08-Problems.md
│   ├── A10104-1_C08Q1.c
│   ├── A10104-1_C08Q2.c
│   ├── A10303-1_C08-Problems.md
│   ├── A10303-1_C08Q1.c
│   ├── A10303-1_C08Q2.c
│   ├── A10303-2_C08-Problems.md
│   ├── A10303-2_C08Q1.c
│   ├── A10303-2_C08Q2.c
│   └── A10303-2_C08Q3.c
├── Chapter09_Strings
│   ├── A10104-1_C09-Problems.md
│   ├── A10104-1_C09Q1.c
│   ├── A10303-1_C09-Problems.md
│   ├── A10303-1_C09Q1.c
│   ├── A10303-1_C09Q2.c
│   └── A10303-1_C09Q3.c
├── Chapter10_Structures
│   ├── A10104-1_C10-Problems.md
│   ├── A10104-1_C10Q1.c
│   └── A10104-1_C10Q2.c
├── LICENSE
├── README.ko.md
├── README.md
└── src
    └── images
        ├── C03_A10303-1_1.png
        ├── C04_A10104-1_1.png
        ├── C05_A10104-1_1.png
        ├── C05_A10104-1_2.png
        ├── C07_A10104-1_1.png
        ├── C07_A10303-1_1.png
        ├── C08_A10104-1_1.png
        └── C10_A10104-1_1.png

11개의 디렉토리, 79개의 파일
```

<br><a name="license"></a>
## 🤝 라이선스

이 레포지토리는 [Apache License 2.0](LICENSE) 하에 배포됩니다.

---
