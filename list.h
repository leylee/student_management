/* list.h */

#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include "student.h"
#include <stdbool.h>

/** sortList 的 key 关键字定义 */
#define KEY_AVERAGE   -0x1
#define KEY_ID        -0x2
#define KEY_NAME      -0x3
#define KEY_RANK      -0x4

/** 双向链表节点 */
typedef struct _Node {
    Student* stu;               // 节点的学生信息
    struct _Node *lst, *nxt;    // 节点的双向指针
    struct _Node *ori;          // 用于复制节点时, 存储原节点的位置, 以实现从原链表中删除该节点的操作
} Node;

/** 双向链表 */
typedef struct _List {
    int length;         // 链表长度
    Node *head, *tail;  // 链表头尾各插入一个辅助节点,
} List;

/** 二叉堆, 一种树形数据结构, 用于O(nlgn)排序 */
typedef struct {
    Node** nodes;   // 堆中节点数组
    int size;       // 堆中元素个数
    int (*cmp)(const Student* a, const Student *b, int key); // 比较函数
    bool reverse;   // 是否逆序
    int key;        // 比较大小的关键字
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
