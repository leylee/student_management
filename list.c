/* list.c */

#include "student.h"
#include "list.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

/** ��������ڵ� */
Node* newNode()
{
    Node* node = (Node*) malloc(sizeof(Node));
    node->stu = newStudent();
    node->nxt = node->lst = NULL;
    node->ori = node; // ��ʼʱ, ori ָ���Լ�
    return node;
}

/** ��ԭ�ڵ㹹���������еĽڵ� */
Node* newNodeFromOri(Node* ori)
{
    Node* node = newNode();
    *node->stu = *ori->stu;
    node->ori = ori->ori; // �˴�, ���½ڵ���Դ�ڵ��������ͬ, ����ʵ�ֶ�θ���, �Դﵽ�������Ҳ�ɾ�������Ŀ��
    return node;
}

/** ��������ڵ� */
void freeNode(Node* node)
{
    freeStudent(node->stu);
    free(node);
}

/** �������� */
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

/** ��ԭ������һ�������� */
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

/** �������� */
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

/** �������׷�ӽڵ� */
void push_back(List* list, Node* node)
{
    list->length++;
    node->lst = list->tail->lst;
    node->nxt = list->tail;
    node->lst->nxt = node;
    node->nxt->lst = node;
}

/** ɾ�������еĽڵ� */
void deleteNode(List* list, Node* node)
{
    list->length--;
    node->lst->nxt = node->nxt;
    node->nxt->lst = node->lst;
    freeNode(node);
}

/** ɾ������β���ڵ� */
void pop_back(List *list)
{
    deleteNode(list, list->tail->lst);
}

/**
 * ����Ϊ�������������.
 * ����������Ϊ�����������ռ�, �������������.
 * ���صĽ�����������������, ���������ڴ�й©.
 */
/* ��ѧ��ģ������ */
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

/* ������ģ������ */
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

/* ��ƽ�������� */
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

/* �����Ƴɼ����� */
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

/* ���������� */
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

/** ����������ѧ���ܷ�, ƽ�������� */
void calcList(const List *list)
{
    Node* node = list->head->nxt;
    while (node->nxt)
    {
        calcStu(node->stu);
        node = node->nxt;
    }
}

/** ���㵥��ƽ����. */
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

/** �����ֵܷ�ƽ���� */
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

/** ���㵥�Ƶ���ĸ�ȼ�������������.
 * ����, A: 90+; B: 80+; C: 70+ D: 60+; F: ������.
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

/** ����ƽ������ĸ�ȼ� */
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

/** ɾ������ ori ������, ������ tar �еĽڵ�
 * ����ʹ�ô˺���ɾ��һ�����ϵ�ͬһ�ڵ�.
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

/** ���������ڵ��˳�� */
void swapNode(Node* a, Node *b)
{
    a->lst->nxt = b;
    b->nxt->lst = a;
    b->lst = a->lst;
    a->nxt = b->nxt;
    a->lst = b;
    b->nxt = a;
}

/** �������������, ����ð������, ʱ�临�Ӷ� O(n^2)
 * key Ϊ�����ؼ���, ��Ϊ�Ǹ�����, ��ʹ�ø�������Ŀγ�Ϊ�ؼ��ֱȽ�.
 * ��Ϊ��������, ���ո����Ĺؼ�������.
 * reverse Ϊ����˳��. false Ϊ����, true Ϊ����
 */
void sortList(List* list, int key, bool reverse)
{
    // cmp �Ǹ�����ָ��, ���ڴ洢����. ������￴����, �������������������
    int (*cmp) (const Student* a, const Student* b, int key) = NULL;

    /* ����key��ֵ, ��������Ĺؼ���.
    ���keyΪ��ֵ, ���ն���ȷ������; ����, ��key����course�����, ����course����.*/
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

    /* ð�ݷ����� */
    int times = list->length;
    while (--times)
    {
        Node* node = list->head->nxt;
        while (node->nxt && node->nxt->nxt)
        {
            /* ��������˽���, ��nodeָ��Ľڵ��Ѿ���������һλ, �������ı�node��ֵ. */
            if ((cmp(node->stu, node->nxt->stu, key) > 0) != reverse) // ����������, ��ȡ���
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

/** ��������ѧ���� Rank ���´� 1 ��� */
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
