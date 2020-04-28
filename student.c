#include <stdio.h>
#include <stdlib.h>
#include "student.h"

Student* newStudent()
{
    return (Student*) malloc(sizeof(Student));
}
