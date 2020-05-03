#ifndef STUDENT_H_INCLUDED
#define STUDENT_H_INCLUDED

#define ID_LENGTH   20
#define ID_SIZE (ID_LENGTH + 2)
#define NAME_LENGTH 20
#define NAME_SIZE (NAME_LENGTH + 2)
#define COURSE_NUM  3

#define GENDER_MALE     0x1
#define GENDER_FEMALE   0x2
#define GENDER_OTHER    0x0

#define ORDER_AVERAGE   -0x1
#define ORDER_ID        -0x2
#define ORDER_NAME      -0x3
#define ORDER_RANK      -0x4

static const char* const gender_str[3] = {"other", "male", "female"};
static const char* const course_str[COURSE_NUM] = {"math", "English", "physics"};

typedef enum {
    math, english, physics
} Course;
typedef enum {
    other, male, female
} Gender;

typedef struct _Student {
    char id[ID_SIZE];           // ѧ��
    char name[NAME_SIZE];       // ����
    int gender;                 // �Ա�
    int rank;                   // ����
    double score[COURSE_NUM];   // �ɼ�
    double avg;                 // ƽ���ɼ�
    double sum;                 // �ܳɼ�
} Student;

Student* newStudent();
void freeStudent(Student* pt);
void calcStu(Student *stu);

int cmpId(const Student* a, const Student* b, int meaninglessArg);
int cmpName(const Student* a, const Student* b, int meaninglessArg);
int cmpAvg(const Student* a, const Student *b, int meaninglessArg);
int cmpCourse(const Student *a, const Student *b, int course);
int cmpRank(const Student *a, const Student *b, int meaninglessArg);

#endif // STUDENT_H_INCLUDED
