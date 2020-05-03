/* student.h */

#ifndef STUDENT_H_INCLUDED
#define STUDENT_H_INCLUDED

#define ID_LENGTH   20 // 定义学号的最大长度
#define ID_SIZE (ID_LENGTH + 2) // 存储学号的字符串的最大长度, 比学号长度多2, 因为fgets会读入'\n', 再加一个'\0', 共多出两个
#define NAME_LENGTH 20 // 定义姓名最大长度
#define NAME_SIZE (NAME_LENGTH + 2) // 存储姓名的字符串的最大长度, 与上面同理
#define COURSE_NUM  3  // 定义课程数量

/** 课程名, 性别名的字符串存储 */
static const char* const gender_str[3] = {"other", "male", "female"};
static const char* const course_str[COURSE_NUM] = {"math", "English", "physics"};

/** 枚举类型, 用作性别和课程的序号 */
typedef enum {
    math, english, physics
} Course;
typedef enum {
    other, male, female
} Gender;

/** Student 结构体, 存储学生信息 */
typedef struct _Student {
    char id[ID_SIZE];           // 学号
    char name[NAME_SIZE];       // 姓名
    int gender;                 // 性别
    int rank;                   // 排名
    double score[COURSE_NUM];   // 成绩
    double avg;                 // 平均成绩
    double sum;                 // 总成绩
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
