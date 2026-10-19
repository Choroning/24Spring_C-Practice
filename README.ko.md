# [2024학년도 봄학기] C 프로그래밍 연습

![Last Commit](https://img.shields.io/github/last-commit/Choroning/24Spring_C-Practice)
![Languages](https://img.shields.io/github/languages/top/Choroning/24Spring_C-Practice)

이 레포지토리는 컴퓨터언어Ⅰ과 컴퓨터언어실습Ⅰ 과목의 이중 언어 강의 노트와 수업 결과물을 정리한 아카이브입니다.

*작성자: 박철원 (고려대학교(세종), 컴퓨터소프트웨어학과) - 2024년 기준 1학년*
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

이 레포지토리에는 대학 수준의 C 프로그래밍 과목을 위해 작성한 강의 노트, 연습 문제, 과제 해설, C 코드가 담겨 있습니다.

- `Lecture-Notes/`에는 장마다 핵심 개념을 정리한 강의 노트(`Concepts_Lecture`)가 있고, 4장\~10장에는 컴퓨터언어Ⅰ의 장별 실습 문제를 옮긴 연습 문제(`Exercises`)와 그 풀이(`Solutions`)가 함께 있습니다. 컴퓨터언어Ⅰ의 교재인 Warming-Up C Programming의 장 번호(1장\~10장)를 따라 단원을 `Ch01`\~`Ch10`으로 나눴습니다.
- 모든 강의 노트, 연습 문제, 풀이는 영어 파일(`.md`)과 한국어 파일(`.ko.md`)이 같은 구성으로 짝을 이룹니다.
- `Coursework/`의 `HW01`\~`HW10`에는 컴퓨터언어실습Ⅰ의 1차\~10차 과제가 있습니다. 과제마다 문제와 풀이를 설명하는 과제 해설(`Assignment-Explanation`)과 풀이 코드(`Solution/`)가 있으며, 과제 해설도 영어 파일과 한국어 파일이 짝을 이룹니다.
- `Coursework/`의 `Lab04`\~`Lab10`에는 4장\~10장의 실습 문제를 직접 푼 C 코드가 있으며, 각 단원의 풀이(`Solutions`)가 이 코드를 해설합니다.
- 풀이 코드는 문제를 푸는 한 가지 방법이며 유일한 정답은 아닙니다.
- 코드 파일에는 문제 제목, 작성자, 작성일을 적은 **Doxygen 스타일 헤더**가 있습니다.
- 모든 C 코드는 GCC의 C99 표준으로 컴파일하여 확인했으며, 이때 Visual Studio 전용 함수는 표준 함수로 대신했습니다.

> **🤖 AI 에이전트 활용**
> 강의 노트와 연습 문제의 정리와 번역, 풀이와 과제 해설의 작성, 레포지토리 구조 정리에 [Claude Code](https://claude.ai/download)를 활용했습니다. 컴퓨터언어실습Ⅰ은 코드를 항상 스스로 작성하도록 했으며, 실습 코드와 과제 풀이 코드는 직접 작성했습니다. 다만 레포지토리에 빠져 있던 과제 문항(HW03 문제 1\~3, HW07 문제 4, HW08 문제 3, HW10 문제 1)의 풀이와 HW07 문제 4, HW08 문제 3의 문제는 Claude Code로 작성했습니다.

<br><a name="course-information"></a>
## 📚 강의 정보

- **학기:** 2024학년도 봄학기 (3월 - 6월)
- **소속:** 고려대학교(세종)

|학수번호      |강의명    |이수구분|교수자|개설학과|
|:----------:|:-------|:----:|:------:|:----------------|
|`DCCS101-04`|컴퓨터언어Ⅰ|교양|임영희 교수|컴퓨터소프트웨어학과|
|`DCCS103-03`|컴퓨터언어실습Ⅰ|교양|이종욱 교수|컴퓨터소프트웨어학과|

### 과목 개요

C 언어로 컴퓨터 프로그래밍의 기초를 배우는 두 교양 과목이다. 컴퓨터언어Ⅰ은 구조적 프로그래밍 언어인 C 언어를 통하여 컴퓨터 프로그래밍에 대한 기초적인 이론과 기술을 습득하는 이론 위주의 과목이며, 강의는 교재를 중심으로 프로그래밍 언어의 기본 개념, 컴퓨터에서 데이터가 표현되는 방식, C 언어의 연산자와 제어문 등을 이해하는 것을 목표로 한다. 교재의 1장\~10장을 따라 프로그래밍과 C 언어, C 프로그램의 기본, 데이터형과 변수, 연산자, 제어문, 함수, 배열, 포인터, 문자열, 구조체를 다루며, 수업은 이론 강의, 실습, 퀴즈로 이루어지고 장별 실습 과제와 이론 과제(교재 연습문제 풀이)를 수행한다. 컴퓨터언어실습Ⅰ은 컴퓨터언어Ⅰ과 연계된 실습 과목으로, C 언어의 기본 개념을 정확히 이해하고 다양한 예제를 실습하여 C 프로그래밍 능력을 기르는 것을 목표로 한다. 매주 지난 과제의 풀이, 교재 이론, 교재 문제 실습을 진행하며 1차\~10차 과제를 수행한다. 이 레포지토리의 강의 노트와 실습 코드는 컴퓨터언어Ⅰ의 강의자료와 실습 과제를, 과제 해설과 풀이 코드는 컴퓨터언어실습Ⅰ의 과제를 바탕으로 한다. 교수자, 수업 일정과 형식, 평가, 수업 운영 규정, 주차별 계획 및 진도, 참고 자료는 [강의 정보 문서](Course-Information.ko.md)에 정리했다.

<br><a name="prerequisites"></a>
## ✅ 사전 요구사항

- 프로그래밍 개념에 대한 기본적인 이해가 있어야 합니다. 두 과목의 강의계획서는 선수 과목을 지정하지 않았습니다.
- C/C++ 컴파일러(예: GCC)가 설치되어 있어야 합니다. 이 레포지토리의 코드는 C99 이상을 지원하는 컴파일러로 컴파일할 수 있으며, Visual Studio 전용 함수(`scanf_s`, `gets_s`)나 `<windows.h>`를 쓰는 파일은 다른 컴파일러에서 표준 함수로 바꾸어야 합니다.
- 커맨드 라인 툴 사용에 익숙해야 합니다.

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
├── Lecture-Notes               장별 강의 노트, 연습 문제, 풀이
├── Coursework                  컴퓨터언어실습Ⅰ 과제와 장별 C 실습 코드
├── images                      연습 문제와 과제의 그림
├── Course-Information.ko.md    수업 운영 정보
├── Course-Information.md
├── LICENSE                     문서 라이선스 (CC BY-NC-SA 4.0)
├── LICENSE-CODE                코드 라이선스 (PolyForm Noncommercial 1.0.0)
├── README.ko.md
└── README.md
```

단원 목록은 [`Lecture-Notes` 색인](Lecture-Notes/README.ko.md)에, 과제와 실습 코드는 [`Coursework` 색인](Coursework/README.ko.md)에 있습니다.

<br><a name="license"></a>
## 🤝 라이선스

이 레포지토리의 문서(강의 노트, 해설, 요약지)는 [CC BY-NC-SA 4.0](LICENSE), 코드는 [PolyForm Noncommercial 1.0.0](LICENSE-CODE)에 따라 배포됩니다. 강의자료와 교재에서 가져온 그림과 예제 코드, 강의가 배포한 과제 원본과 템플릿 코드는 원저작자에게 권리가 있으며 이 라이선스의 대상이 아닙니다.

---
