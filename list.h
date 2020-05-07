/* list.h */

#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include "student.h"
#include <stdbool.h>

/** sortList �� key �ؼ��ֶ��� */
#define KEY_AVERAGE   -0x1
#define KEY_ID        -0x2
#define KEY_NAME      -0x3
#define KEY_RANK      -0x4

/** ˫������ڵ� */
typedef struct _Node {
    Student* stu;               // �ڵ��ѧ����Ϣ
    struct _Node *lst, *nxt;    // �ڵ��˫��ָ��
    struct _Node *ori;          // ���ڸ��ƽڵ�ʱ, �洢ԭ�ڵ��λ��, ��ʵ�ִ�ԭ������ɾ���ýڵ�Ĳ���
} Node;

/** ˫������ */
typedef struct _List {
    int length;         // ������
    Node *head, *tail;  // ����ͷβ������һ�������ڵ�,
} List;

/** �����, һ���������ݽṹ, ����O(nlgn)���� */
typedef struct {
    Node** nodes;   // ���нڵ�����
    int size;       // ����Ԫ�ظ���
    int (*cmp)(const Student* a, const Student *b, int key); // �ȽϺ���
    bool reverse;   // �Ƿ�����
    int key;        // �Ƚϴ�С�Ĺؼ���
} Heap;

Node* newNode();
List* newList();
List* newListFromOri(List* ori);
void freeList(List* pt);

void push_back(List* list, Node* node);
void pop_back(List *list);
void deleteListFromOri(List* ori, List* tar);

List* searchById(List *list, const char* id);
List* searchByName(List *list, const char* name);
List* searchByAvgScore(List* list, double minScore, double maxScore);
List* searchByCourseScore(List* list, double minScore, double maxScore, Course course);
List* searchByRank(List* list, int minRank, int maxRank);

void calcList(const List *list);
double calcCourseAvg(const List* list, Course course);
double calcSumAvg(const List* list);
void calcCourseLetter(const List* list, int cnt[COURSE_NUM][5]);
void calcAvgLetter(const List* list, int cnt[5]);

void sortList(List* list, int key, bool reverse);
void heapSortList(List* list, int key, bool reverse);
void rankList(List* list);

#endif // LIST_H_INCLUDED
