#include "student.h"
#include "list.h"

Node* newNode()
{
    Node* pt = (Node*) malloc(sizeof(Node));
    pt->stu = pt->nxt = pt->lst = NULL;
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
    return pt;
}

void freeList(List* pt)
{
    freeStudent(pt->head);
    freeStudent(pt->tail);
    free(pt);
}
