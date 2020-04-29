#include <stdlib.h>
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
