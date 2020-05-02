#include "student.h"
#include "list.h"
#include <stdlib.h>

/* ��������ڵ� */
Node* newNode()
{
    Node* pt = (Node*) malloc(sizeof(Node));
    pt->stu = newStudent();
    pt->nxt = pt->lst = NULL;
    return pt;
}

/* ��������ڵ� */
void freeNode(Node* pt)
{
    freeStudent(pt->stu);
    free(pt);
}

/* �������� */
List* newList()
{
    List* list = (List*) malloc(sizeof(List));
    list->length = 0;
    list->head = newNode();
    list->tail = newNode();
    list->head->nxt = list->tail;
    list->tail->lst = list->head;
    return list;
}

/* �������� */
void freeList(List* list)
{
    while (list->length)
        pop_back(list);
    freeNode(list->head);
    freeNode(list->tail);
    free(list);
}

/* ���������ӽڵ� */
void push_back(List* list, Node* node)
{
    list->length++;
    node->lst = list->tail->lst;
    node->nxt = list->tail;
    node->lst->nxt = node;
    node->nxt->lst = node;
}

/* ɾ�������еĽڵ� */
void deleteNode(List* list, Node* node)
{
    list->length--;
    node->lst->nxt = node->nxt;
    node->nxt->lst = node->lst;
    freeNode(node);
}

/* ɾ������β���ڵ� */
void pop_back(List *list)
{
    deleteNode(list, list->tail->lst);
}

/* ��ѧ�ž�׼���� */
Node* searchById(List *list, const char* id)
{
    Node* node = list->head->nxt;
    while (node->nxt != NULL)
    {
        if (strcpy(node->stu->id, id) == 0)
            return node;
    }
    return NULL;
}
