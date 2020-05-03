/* list.c */

#include "student.h"
#include "list.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

/** 构造链表节点 */
Node* newNode()
{
    Node* node = (Node*) malloc(sizeof(Node));
    node->stu = newStudent();
    node->nxt = node->lst = NULL;
    node->ori = node; // 初始时, ori 指向自己
    return node;
}

/** 从原节点构造新链表中的节点 */
Node* newNodeFromOri(Node* ori)
{
    Node* node = newNode();
    *node->stu = *ori->stu;
    node->ori = ori->ori; // 此处, 令新节点与源节点的祖先相同, 即可实现多次复制, 以达到连续查找并删除结果的目的
    return node;
}

/** 析构链表节点 */
void freeNode(Node* node)
{
    freeStudent(node->stu);
    free(node);
}

/** 构造链表 */
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

/** 从原链表复制一个新链表 */
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

/** 析构链表 */
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

/** 向链表后部追加节点 */
void push_back(List* list, Node* node)
{
    list->length++;
    node->lst = list->tail->lst;
    node->nxt = list->tail;
    node->lst->nxt = node;
    node->nxt->lst = node;
}

/** 删除链表中的节点 */
void deleteNode(List* list, Node* node)
{
    list->length--;
    node->lst->nxt = node->nxt;
    node->nxt->lst = node->lst;
    freeNode(node);
}

/** 删除链表尾部节点 */
void pop_back(List *list)
{
    deleteNode(list, list->tail->lst);
}

/**
 * 以下为链表的搜索函数.
 * 搜索函数会为搜索结果分配空间, 并返回搜索结果.
 * 返回的结果必须调用析构函数, 否则会造成内存泄漏.
 */
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
List* searchByCourseScore(List* list, double minScore, double maxScore, Course course)
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

/* 按排名搜索 */
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

/** 计算链表中学生总分, 平均分数据 */
void calcList(const List *list)
{
    Node* node = list->head->nxt;
    while (node->nxt)
    {
        calcStu(node->stu);
        node = node->nxt;
    }
}

/** 计算单科平均分. */
double calcCourseAvg(const List* list, Course course)
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

/** 计算总分的平均分 */
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

/** 计算单科的字母等级所包含的人数.
 * 其中, A: 90+; B: 80+; C: 70+ D: 60+; F: 不及格.
 */
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

/** 计算平均分字母等级 */
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

/** 删除所有 ori 链表中, 存在于 tar 中的节点
 * 不可使用此函数删除一次以上的同一节点.
 */
void deleteListFromOri(List* ori, List* tar)
{
    Node* node = tar->head->nxt;
    while (node->nxt)
    {
        deleteNode(ori, node->ori);
        node = node->nxt;
    }
}

/** 交换两个节点的顺序 */
void swapNode(Node* a, Node *b)
{
    a->lst->nxt = b;
    b->nxt->lst = a;
    b->lst = a->lst;
    a->nxt = b->nxt;
    a->lst = b;
    b->nxt = a;
}

/** 对链表进行排序, 采用冒泡排序, 时间复杂度 O(n^2)
 * key 为搜索关键字, 若为非负整数, 则使用该数代表的课程为关键字比较.
 * 若为其他常量, 则按照给定的关键字排序.
 * reverse 为排序顺序. false 为升序, true 为降序
 */
void sortList(List* list, int key, bool reverse)
{
    // cmp 是个函数指针, 用于存储函数. 如果这里看不懂, 可以上网查找相关资料
    int (*cmp) (const Student* a, const Student* b, int key) = NULL;

    /* 根据key的值, 决定排序的关键字.
    如果key为负值, 则按照定义确定函数; 否则, 将key看做course的序号, 按照course查找.*/
    switch (key)
    {
    case KEY_AVERAGE:
        cmp = cmpAvg;
        break;
    case KEY_ID:
        cmp = cmpId;
        break;
    case KEY_NAME:
        cmp = cmpName;
        break;
    case KEY_RANK:
        cmp = cmpRank;
        break;
    default:
        cmp = cmpCourse;
        break;
    }

    /* 冒泡法排序 */
    int times = list->length;
    while (--times)
    {
        Node* node = list->head->nxt;
        while (node->nxt && node->nxt->nxt)
        {
            /* 如果发生了交换, 则node指向的节点已经被后移了一位, 因此无需改变node的值. */
            if ((cmp(node->stu, node->nxt->stu, key) > 0) != reverse) // 若降序排列, 则取异或
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

/** 将链表中学生的 Rank 从新从 1 编号 */
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
