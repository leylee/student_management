#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include "student.h"
#include <stdlib.h>

typedef struct _Node {
    Student* stu;
    struct _Node *lst, *nxt;
} Node;

typedef struct _List {
    int length;
    Node *head, *tail;
} List;

Node* newNode();
void freeNode(Node* pt);
List* newList();
void freeList(List* pt);

#endif // LIST_H_INCLUDED
