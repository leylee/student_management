#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include "student.h"
#include <stdbool.h>

typedef struct _Node {
    Student* stu;
    struct _Node *lst, *nxt, *ori;
} Node;

typedef struct _List {
    int length;
    Node *head, *tail;
} List;

Node* newNode();
List* newList();
List* newListFromOri(List* ori);
void freeNode(Node* pt);
void freeList(List* pt);

void push_back(List* list, Node* node);
void deleteNode(List* list, Node* node);
void deleteListFromOri(List* ori, List* tar);
void pop_back(List *list);

List* searchById(List *list, const char* id);
List* searchByName(List *list, const char* name);
List* searchByAvgScore(List* list, double minScore, double maxScore);
List* searchByCourseScore(List* list, double minScore, double maxScore, int course);
List* searchByRank(List* list, int minRank, int maxRank);

void calcList(const List *list);
double calcCourseAvg(const List* list, int course);
double calcSumAvg(const List* list);
void calcCourseLetter(const List* list, int cnt[COURSE_NUM][5]);
void calcAvgLetter(const List* list, int cnt[5]);

void sortList(List* list, int order, bool reverse);
void rankList(List* list);

#endif // LIST_H_INCLUDED
