#include "list.h"
#include <stdio.h>
#include "ui.h"
#include <stdbool.h>
#include <string.h>

/* ��ӡ�ڵ� */
void printStu(Student *stu)
{
    printf("%11s%10s%7s%6.2f%8.2f%8.2f%8.2f%7.2f\n", stu->id, stu->name, gender_str[stu->gender],
            stu->score[math], stu->score[english], stu->score[physics], stu->avg, stu->sum);
}

/* ��ӡ���� */
void printList(List* list)
{
    printTitle();
    Node* node = list->head->nxt;
    while (node->nxt != NULL)
    {
        printStu(node->stu);
        node = node->nxt;
    }
}

/* ��ӡ��ͷ */
void printTitle()
{
    printf("%11s%10s%7s%6s%8s%8s%8s%7s\n", "ID", "Name", "Gender", "Math", "English", "Physics", "Average", "Sum");
    puts("----------- --------- ------ ----- ------- ------- ------- ------");
}

/* �������, ��Χ 0-100 */
double getScore(const char* hint)
{
    double score;
    while (true)
    {
        if (hint)
            printf(hint);
        rewind(stdin);
        if (scanf("%lf", &score) == 1
                && score >= 0 && score <= 100)
            break;
    }
    return score;
}

/* �����Ա�, ��Χ 0-2 */
int getGender(const char* hint)
{
    int gender;
    while (true)
    {
        if (hint)
            printf(hint);
        rewind(stdin);
        if (scanf("%d", &gender) == 1
                && gender >= 0 && gender <= 2)
            break;
    }
    return gender;
}

/* �����ַ���, ���������ַ������� (���Ȳ������հ׷�) �ɲ������� */
void getString(const char* hint, char* str, int length)
{
    if (hint)
        printf(hint, length);
    rewind(stdin);
    fgets(str, length + 2, stdin);
    str[strlen(str) - 1] = '\0';
}

/* ����γ� */
int getCourse(const char* hint)
{
    int course;
    while (true)
    {
        puts(hint);
        for (int i = 0; i < COURSE_NUM; ++i)
            printf("%s: %i, ", course_str[i], i);
        rewind(stdin);
        if (scanf("%d", &course) == 1
                && course >= 0 && course < COURSE_NUM)
            break;
    }
    return course;
}
