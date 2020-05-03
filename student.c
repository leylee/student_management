/* student.c */

#include <stdlib.h>
#include <stdio.h>
#include "student.h"
#include <string.h>

/** 课程名, 性别名的字符串存储 */
const char* const gender_str[3] = {"other", "male", "female"};
const char* const course_str[COURSE_NUM] = {"math", "English", "physics"};

/** 构造 Student 结构体 */
Student* newStudent()
{
    Student* pt = (Student*) malloc(sizeof(Student));
    pt->rank = 0;
    pt->gender = other;
    return pt;
}

/** 析构 Student 结构体 */
void freeStudent(Student* pt)
{
    free(pt);
}

/** 计算学生的总成绩, 平均成绩 */
void calcStu(Student *stu)
{
    stu->sum = 0;
    for (int i = 0; i < COURSE_NUM; ++i)
        stu->sum += stu->score[i];
    stu->avg = stu->sum / COURSE_NUM;
}

/**
 * 以下是比较函数, 用于排序
 * 若 a < b, 返回 -1; 若 a = b, 返回 0; 若 a > b, 返回 1
 * 仅当比较关键字为单科时, 最后一个参数表示课程序号. 否则为无效参数.
 */
int cmpId(const Student* a, const Student* b, int meaninglessArg)
{
    return strcmp(a->id, b->id);
}

int cmpName(const Student* a, const Student* b, int meaninglessArg)
{
    return strcmp(a->name, b->name);
}

int cmpAvg(const Student* a, const Student *b, int meaninglessArg)
{
    return a->avg < b->avg ? -1 : a->avg > b->avg ? 1 : 0;
}

int cmpCourse(const Student *a, const Student *b, int course)
{
    return a->score[course] < b->score[course] ? -1 :
        a->score[course] > b->score[course] ? 1: 0;
}

int cmpRank(const Student *a, const Student *b, int meaninglessArg)
{
    return a->rank < b->rank ? -1 : a->rank > b->rank ? 1 : 0;
}
