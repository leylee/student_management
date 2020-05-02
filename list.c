#include "student.h"
#include "list.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* 构造链表节点 */
Node* newNode()
{
    Node* pt = (Node*) malloc(sizeof(Node));
    pt->stu = newStudent();
    pt->nxt = pt->lst = pt->ori = NULL;
    return pt;
}

/* 析构链表节点 */
void freeNode(Node* pt)
{
    freeStudent(pt->stu);
    free(pt);
}

/* 构造链表 */
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

/* 析构链表 */
void freeList(List* list)
{
    while (list->length)
        pop_back(list);
    freeNode(list->head);
    freeNode(list->tail);
    free(list);
}

/* 向链表后部添加节点 */
void push_back(List* list, Node* node)
{
    list->length++;
    node->lst = list->tail->lst;
    node->nxt = list->tail;
    node->lst->nxt = node;
    node->nxt->lst = node;
}

/* 删除链表中的节点 */
void deleteNode(List* list, Node* node)
{
    list->length--;
    node->lst->nxt = node->nxt;
    node->nxt->lst = node->lst;
    freeNode(node);
}

/* 删除链表尾部节点 */
void pop_back(List *list)
{
    deleteNode(list, list->tail->lst);
}

/* 按学号模糊搜索 */
List* searchById(List *list, const char* id)
{
    List* result = newList();
    Node* node = list->head->nxt;
    while (node->nxt != NULL)
    {
        if (strstr(node->stu->id, id) != NULL)
        {
            Node* target = newNode();
            *target->stu = *node->stu;
            target->ori = node;
            push_back(result, target);
        }
        node = node->nxt;
    }
    return result;
}

/* 按姓名模糊搜索 */
List* searchByName(List *list, const char* name)
{
    List* result = newList();
    Node* node = list->head->nxt;
    while (node->nxt != NULL)
    {
        if (strstr(node->stu->name, name) != NULL)
        {
            Node* target = newNode();
            *target->stu = *node->stu;
            target->ori = node;
            push_back(result, target);
        }
        node = node->nxt;
    }
    return result;
}

/* 计算链表分数数据 */
void calcList(List *list)
{
    Node* node = list->head->nxt;
    while (node->nxt)
    {
        calcStu(node->stu);
        node = node->nxt;
    }
}

void deleteListFromOri(List* ori, List* tar)
{
    Node* node = tar->head->nxt;
    while (node->nxt)
    {
        deleteNode(ori, node->ori);
        node = node->nxt;
    }
}
