#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include "student.h"

typedef struct _Node {
    Student* stu;
    struct _Node *lst, *nxt, *ori;
} Node;

typedef struct _List {
    int length;
    Node *head, *tail;
} List;

Node* newNode();
void freeNode(Node* pt);
List* newList();
void freeList(List* pt);
void push_back(List* list, Node* node);
void deleteNode(List* list, Node* node);
void pop_back(List *list);
List* searchById(List *list, const char* id);
List* searchByName(List *list, const char* name);
void calcList(List *list);
void deleteListFromOri(List* ori, List* tar);

#endif // LIST_H_INCLUDED
