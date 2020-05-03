/* student.h */

#ifndef STUDENT_H_INCLUDED
#define STUDENT_H_INCLUDED

#define ID_LENGTH   20 // ����ѧ�ŵ���󳤶�
#define ID_SIZE (ID_LENGTH + 2) // �洢ѧ�ŵ��ַ�������󳤶�, ��ѧ�ų��ȶ�2, ��Ϊfgets�����'\n', �ټ�һ��'\0', ���������
#define NAME_LENGTH 20 // ����������󳤶�
#define NAME_SIZE (NAME_LENGTH + 2) // �洢�������ַ�������󳤶�, ������ͬ��
#define COURSE_NUM  3  // ����γ�����

/** �γ���, �Ա������ַ����洢 */
static const char* const gender_str[3] = {"other", "male", "female"};
static const char* const course_str[COURSE_NUM] = {"math", "English", "physics"};

/** ö������, �����Ա�Ϳγ̵���� */
typedef enum {
    math, english, physics
} Course;
typedef enum {
    other, male, female
} Gender;

/** Student �ṹ��, �洢ѧ����Ϣ */
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
