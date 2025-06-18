/**
 * @file    A10104-1_C9Q1.c
 * @brief   Q1. 문자열 조작
 * @author  박철원 (Cheolwon Park)
 * @date    2024-05-14
 * 
 * @note	소스 코드에 사용된 gets_s는 Visual Studio 이외의
 * 			IDE에서 실행이 불가할 수 있음에 주의하시기 바랍니다.
 */

 #include <stdio.h>
#define SIZE 64

int my_strlen(const char* p);
void my_strcpy(char* p1, const char* p2);
int my_strcmp(const char* p1, const char* p2);
void makeUpper(char p[]);
void makeReverse(char p[]);
void strSwap(char* p1, char* p2);
void swap(char* a, char* b);

int main()
{
    char str1[SIZE], str2[SIZE], str3[SIZE];
    int result;

    printf("문자열(str1) 입력: ");
    gets_s(str1, SIZE);
    printf("\nstr1의 길이: %d\n", my_strlen(str1));

    my_strcpy(str2, str1);
    printf("\nstr2 = %s\n", str2);

    makeUpper(str2);
    printf("\nstr2를 대문자로 변환 = %s\n", str2);

    makeReverse(str2);
    printf("\nstr2를 역순으로 변환 = %s\n", str2);

    my_strcpy(str3, str1);
    if (!my_strcmp(str1, str3))
        printf("\n%s == %s\n", str1, str3);
    if (result = my_strcmp("abc", "abcd"))
        printf("\nstrcmp(\"abc\", \"abcd\") = %d\n", result);
    if (result = my_strcmp("C++", "C"))
        printf("\nstrcmp(\"C++\", \"C\") = %d\n\n", result);

    my_strcpy(str3, "C is powerful");

    printf("------ strSwap() 함수 호출 전 ------\n");
    printf("str1 = %s\nstr3 = %s\n", str1, str3);

    strSwap(str1, str3);
    printf("------ 첫 번째 strSwap() 함수 호출 후 ------\n");
    printf("str1 = %s\nstr3 = %s\n", str1, str3);

    strSwap(str1, str3);
    printf("------ 두 번째 strSwap() 함수 호출 후 ------\n");
    printf("str1 = %s\nstr3 = %s\n", str1, str3);

    return 0;
}

int my_strlen(const char* p)
{
    int len = 0;
    while (p[len])
        len++;
    return len;
}

void my_strcpy(char* p1, const char* p2)
{
    int i = 0;
    while (p2[i]) {
        p1[i] = p2[i];
        i++;
    }
    p1[i] = '\0';
}

int my_strcmp(const char* p1, const char* p2)
{
    int i, j, len1 = 0, len2 = 0;
    while (p1[len1]) len1++;
    while (p2[len2]) len2++;
    j = (len1 >= len2) ? len1 : len2;

    for (i = 0; i < j; i++) {
        if (p1[i] > p2[i]) return 1;
        else if (p1[i] < p2[i]) return -1;
    }
    return 0;
}

void makeUpper(char p[])
{
    while (*p) {
        if (*p >= 'a' && *p <= 'z')
            *p -= 32;
        p++;
    }
}

void makeReverse(char p[])
{
    int i, size = my_strlen(p);
    for (i = 0; i < size / 2; i++) {
        swap(&p[i], &p[size - i - 1]);
    }
}

void strSwap(char* p1, char* p2)
{
    int i, j, len1 = my_strlen(p1), len2 = my_strlen(p2);
    j = len1 > len2 ? len1 : len2;
    for (i = 0; i <= j; i++) {
        swap(&p1[i], &p2[i]);
    }
}

void swap(char* a, char* b)
{
    char temp = *a;
    *a = *b;
    *b = temp;
}
