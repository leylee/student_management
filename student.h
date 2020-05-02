#ifndef STUDENT_H_INCLUDED
#define STUDENT_H_INCLUDED

#define ID_LENGTH   20
#define NAME_LENGTH 20
#define COURSE_NUM  3

#define GENDER_MALE     0X1
#define GENDER_FEMALE   0X2
#define GENDER_OTHER    0X0

static const char* const gender_str[3] = {"other", "male", "female"};
enum {
    math, english, physics
};
enum {
    other, male, female
};

typedef struct _Student {
    char id[ID_LENGTH];        // 学号
    char name[NAME_LENGTH];    // 姓名
    int gender;                 // 性别
    double score[COURSE_NUM];   // 成绩
    double avg;                 // 平均成绩
    double sum;                 // 总成绩
} Student;

Student* newStudent();
void freeStudent(Student* pt);

void printTitle();
void printItem(Node *node);

#endif // STUDENT_H_INCLUDED
