#include "student.h"
#include "list.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

/* 构造链表节点 */
Node* newNode()
{
    Node* pt = (Node*) malloc(sizeof(Node));
    pt->stu = newStudent();
    pt->nxt = pt->lst = NULL;
    pt->ori = pt;
    return pt;
}

/* 从原节点构造新链表中的节点 */
Node* newNodeFromOri(Node* ori)
{
    Node* node = newNode();
    *node->stu = *ori->stu;
    node->ori = ori->ori;
    return node;
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

/* 从原链表复制一个新链表 */
List* newListFromOri(List* ori)
{
    List* list = newList();
    Node* node = ori->head->nxt;
    while (node->nxt)
    {
        push_back(list, newNodeFromOri(node));
        node = node->nxt;
    }
    return list;
}

/* 析构链表 */
void freeList(List* list)
{
    if (!list)
        return;
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
            push_back(result, newNodeFromOri(node));
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
            push_back(result, newNodeFromOri(node));
        }
        node = node->nxt;
    }
    return result;
}

/* 按平均分搜索 */
List* searchByAvgScore(List* list, double minScore, double maxScore)
{
    List* result = newList();
    Node* node = list->head->nxt;
    while (node->nxt)
    {
        if (node->stu->avg >= minScore && node->stu->avg <= maxScore)
        {
            push_back(result, newNodeFromOri(node));
        }
        node = node->nxt;
    }
    return result;
}

/* 按单科成绩搜索 */
List* searchByCourseScore(List* list, double minScore, double maxScore, int course)
{
    List* result = newList();
    Node* node = list->head->nxt;
    while (node->nxt)
    {
        if (node->stu->score[course] >= minScore && node->stu->score[course] <= maxScore)
        {
            push_back(result, newNodeFromOri(node));
        }
        node = node->nxt;
    }
    return result;
}

/* 按排名查找 */
List* searchByRank(List* list, int minRank, int maxRank)
{
    List* result = newList();
    Node* node = list->head->nxt;
    while (node->nxt)
    {
        if (node->stu->rank >= minRank && node->stu->rank <= maxRank)
        {
            push_back(result, newNodeFromOri(node));
        }
        node = node->nxt;
    }
    return result;
}

/* 计算链表分数数据 */
void calcList(const List *list)
{
    Node* node = list->head->nxt;
    while (node->nxt)
    {
        calcStu(node->stu);
        node = node->nxt;
    }
}

/* 计算单科平均分 */
double calcCourseAvg(const List* list, int course)
{
    double sum = 0;
    Node* node = list->head->nxt;
    while (node->nxt)
    {
        sum += node->stu->score[course];
        node = node->nxt;
    }
    return sum / list->length;
}

/* 计算总分的平均分 */
double calcSumAvg(const List* list)
{
    double sum = 0;
    Node* node = list->head->nxt;
    while (node->nxt)
    {
        sum += node->stu->sum;
        node = node->nxt;
    }
    return sum / list->length;
}

void calcCourseLetter(const List* list, int cnt[COURSE_NUM][5])
{
    const Node* node = list->head->nxt;
    while (node->nxt)
    {
        for (int i = 0; i < COURSE_NUM; ++i)
        {
            if (node->stu->score[i] >= 90)
                ++cnt[i][0];
            else if (node->stu->score[i] >= 80)
                ++cnt[i][1];
            else if (node->stu->score[i] >= 70)
                ++cnt[i][2];
            else if (node->stu->score[i] >= 60)
                ++cnt[i][3];
            else
                ++cnt[i][4];
        }
        node = node->nxt;
    }
}

void calcAvgLetter(const List* list, int cnt[5])
{
    const Node* node = list->head->nxt;
    while (node->nxt)
    {
        if (node->stu->avg >= 90)
            ++cnt[0];
        else if (node->stu->avg >= 80)
            ++cnt[1];
        else if (node->stu->avg >= 70)
            ++cnt[2];
        else if (node->stu->avg >= 60)
            ++cnt[3];
        else
            ++cnt[4];
        node = node->nxt;
    }
}

/* 删除所有存在于新链表中的原链表节点 */
void deleteListFromOri(List* ori, List* tar)
{
    Node* node = tar->head->nxt;
    while (node->nxt)
    {
        deleteNode(ori, node->ori);
        node = node->nxt;
    }
}

/* 交换两个节点的顺序 */
void swapNode(Node* a, Node *b)
{
    a->lst->nxt = b;
    b->nxt->lst = a;
    b->lst = a->lst;
    a->nxt = b->nxt;
    a->lst = b;
    b->nxt = a;
}

/* 对链表进行排序, 采用冒泡排序, 时间复杂度 O(n^2) */
/* order 为搜索关键字, 若为非负整数, 则使用该数代表的课程为关键字比较.
 * 若为其他常量, 则按照给定的关键字排序.
 */
void sortList(List* list, int order, bool reverse)
{
    int (*cmp) (const Student* a, const Student* b, int order) = NULL;

    switch (order)
    {
    case ORDER_AVERAGE:
        cmp = cmpAvg;
        break;
    case ORDER_ID:
        cmp = cmpId;
        break;
    case ORDER_NAME:
        cmp = cmpName;
        break;
    case ORDER_RANK:
        cmp = cmpRank;
        break;
    default:
        cmp = cmpCourse;
        break;
    }

    int times = list->length;
    while (--times)
    {
        Node* node = list->head->nxt;
        while (node->nxt && node->nxt->nxt)
        {
            if ((cmp(node->stu, node->nxt->stu, order) > 0) != reverse)
            {
                swapNode(node, node->nxt);
            }
            else
            {
                node = node->nxt;
            }
        }
    }
}

void rankList(List* list)
{
    Node* node = list->head->nxt;
    int rank = 1;
    while (node->nxt)
    {
        node->stu->rank = rank++;
        node = node->nxt;
    }
}
