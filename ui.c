#include "list.h"
#include <stdio.h>
#include "ui.h"
#include <stdbool.h>
#include <string.h>

/* 打印节点 */
void printStu(Student *stu)
{
    printf("%11s%10s%7s%6.2f%8.2f%8.2f%8.2f%7.2f\n", stu->id, stu->name, gender_str[stu->gender],
            stu->score[math], stu->score[english], stu->score[physics], stu->avg, stu->sum);
}

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

/* 打印标题 */
void printTitle()
{
    printf("%11s%10s%7s%6s%8s%8s%8s%7s\n", "ID", "Name", "Gender", "Math", "English", "Physics", "Average", "Sum");
    puts("----------- --------- ------ ----- ------- ------- ------- ------");
}

/* 获取分数, 范围 0-100 */
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

/* 获取性别, 范围 0-2 */
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

/* 获取字符串, 缓冲区和缓冲区大小由参数给定 */
void getString(const char* hint, char* buf, int bufsize)
{
    if (hint)
        printf(hint, bufsize);
    rewind(stdin);
    fgets(buf, bufsize, stdin);
    buf[strlen(buf) - 1] = '\0';
}
