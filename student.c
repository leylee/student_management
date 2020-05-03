/* student.c */

#include <stdlib.h>
#include <stdio.h>
#include "student.h"
#include <string.h>

/** �γ���, �Ա������ַ����洢 */
const char* const gender_str[3] = {"other", "male", "female"};
const char* const course_str[COURSE_NUM] = {"math", "English", "physics"};

/** ���� Student �ṹ�� */
Student* newStudent()
{
    Student* pt = (Student*) malloc(sizeof(Student));
    pt->rank = 0;
    pt->gender = other;
    return pt;
}

/** ���� Student �ṹ�� */
void freeStudent(Student* pt)
{
    free(pt);
}

/** ����ѧ�����ܳɼ�, ƽ���ɼ� */
void calcStu(Student *stu)
{
    stu->sum = 0;
    for (int i = 0; i < COURSE_NUM; ++i)
        stu->sum += stu->score[i];
    stu->avg = stu->sum / COURSE_NUM;
}

/**
 * �����ǱȽϺ���, ��������
 * �� a < b, ���� -1; �� a = b, ���� 0; �� a > b, ���� 1
 * �����ȽϹؼ���Ϊ����ʱ, ���һ��������ʾ�γ����. ����Ϊ��Ч����.
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
