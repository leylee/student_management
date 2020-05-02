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
