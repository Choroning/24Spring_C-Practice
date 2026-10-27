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

- `Lecture-Notes/`에는 장별 강의 노트와 실습 노트가 있고, 1장\~10장에는 교재와 실습의 문제로 이루어진 연습 문제와 풀이가 함께 있습니다.
- `Coursework/`에는 컴퓨터언어실습Ⅰ의 과제(`HW01`\~`HW10`)와 장별 실습 코드(`Lab04`\~`Lab10`)가 있습니다.
- 단원은 교재의 장 번호(`Ch01`\~`Ch10`)를 따르며, 모든 문서는 영어(`.md`)와 한국어(`.ko.md`) 파일이 짝을 이룹니다.
- 모든 C 코드는 GCC(C99)로 컴파일됩니다.

> **🤖 AI 에이전트 활용**
> 컴퓨터언어실습Ⅰ은 코드를 스스로 작성하도록 했습니다.
> [Claude Code](https://claude.ai/download)를 노트 정리와 번역, 레포지토리 정리에 활용했습니다.

<br><a name="course-information"></a>
## 📚 강의 정보

- **학기:** 2024학년도 봄학기 (3월 - 6월)
- **소속:** 고려대학교(세종)

|학수번호      |강의명    |이수구분|교수자|개설학과|
|:----------:|:-------|:----:|:------:|:----------------|
|`DCCS101-04`|컴퓨터언어Ⅰ|교양|임영희 교수|컴퓨터소프트웨어학과|
|`DCCS103-03`|컴퓨터언어실습Ⅰ|교양|이종욱 교수|컴퓨터소프트웨어학과|

### 과목 개요

C 언어로 컴퓨터 프로그래밍의 기초를 배우는 두 교양 과목이다. 컴퓨터언어Ⅰ은 교재를 따라 C 언어의 기본 개념을 배우는 이론 과목이고, 컴퓨터언어실습Ⅰ은 이와 연계된 실습 과목이다. 교수자, 수업 일정, 평가, 수업 운영 규정, 진도는 [강의 정보 문서](Course-Information.ko.md)에 정리했다.

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
├── Lecture-Notes               장별 강의 노트, 실습 노트, 연습 문제, 풀이, 예제 코드
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
