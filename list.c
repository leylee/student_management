#include "student.h"
#include "list.h"

Node* newNode()
{
    Node* pt = (Node*) malloc(sizeof(Node));
    pt->stu = NULL;
    pt->nxt = pt->lst = NULL;
    return pt;
}

void freeNode(Node* pt)
{
    freeStudent(pt->stu);
    free(pt);
}

List* newList()
{
    List* pt = (List*) malloc(sizeof(List));
    pt->length = 0;
    pt->head = (Node*) malloc(sizeof(Node));
    pt->tail = (Node*) malloc(sizeof(Node));
    pt->head->nxt = pt->tail;
    pt->tail->lst = pt->head;
    return pt;
}

void freeList(List* pt)
{
    freeNode(pt->head);
    freeNode(pt->tail);
    free(pt);
}
