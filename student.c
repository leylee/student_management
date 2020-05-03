#include <stdlib.h>
#include <stdio.h>
#include "student.h"

Student* newStudent()
{
    Student* pt = (Student*) malloc(sizeof(Student));
    pt->gender = GENDER_OTHER;
    return pt;
}

void freeStudent(Student* pt)
{
    free(pt);
}

void calcStu(Student *stu)
{
    stu->sum = 0;
    for (int i = 0; i < COURSE_NUM; ++i)
        stu->sum += stu->score[i];
    stu->avg = stu->sum / COURSE_NUM;
}

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
