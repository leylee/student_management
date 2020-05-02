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

void printTitle()
{
    printf("%11s%10s%7s%6s%8s%8s%8s%7s\n", "ID", "Name", "Gender", "Math", "English", "Physics", "Average", "Sum");
    puts("----------- --------- ------ ----- ------- ------- ------- ------");
}

void printItem(Node *node)
{
    Student* stu = node->stu;
    printf("%11s%10s%7s\n", stu->id, stu->name, gender_str[stu->gender]);
}
