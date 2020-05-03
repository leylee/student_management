/* file_util.c */

#include "file_util.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 数据以 CSV 文件 (逗号分隔符文件) 存储, 无表头, 每行一条数据.
 * 数据格式为:
    学号
    姓名
    性别
    各科成绩;
 * 其中, 成绩的个数定义为 COURSE_NUM, 在 student.h中.
 */

const char* sep = ",";
const char* fileName = "data.csv";

/** 读取数据. 若文件不存在, 返回 -1. 否则返回读入数据条数. */
int readData(List* list)
{
    FILE* fin = fopen(fileName, "r");
    const int buf_size = 200;

    if (fin == NULL)
        return -1;

    char* buf = calloc(sizeof(char), buf_size); // 缓冲区动态分配, 防止爆栈
    char* tok;
    int cnt = 0;

    /* 一次读入一行数据 */
    while (fgets(buf, buf_size, fin) != NULL)
    {
        ++cnt;
        Node *node = newNode();
        Student* stu = node->stu;

        /* strtok 函数的用法, 参见 https://zh.cppreference.com/w/c/string/byte/strtok */
        tok = strtok(buf, sep);
        strcpy(stu->id, tok);
        tok = strtok(NULL, sep);
        strcpy(stu->name, tok);
        tok = strtok(NULL, sep);
        stu->gender = atoi(tok);
        for (int i = 0; i < COURSE_NUM; ++i)
        {
            tok = strtok(NULL, sep);
            stu->score[i] = atof(tok);
        }
        push_back(list, node);
    }

    free(buf);
    fclose(fin);
    return cnt;
}

/** 保存数据. 若文件打开失败, 返回 -1. 否则返回写入数据条数. */
int writeData(List* list)
{
    FILE* fout = fopen(fileName, "w");

    if (fout == NULL)
        return -1;

    Node* node = list->head->nxt;
    int cnt = 0;
    while (node->nxt)
    {
        ++cnt;

        Student *stu = node->stu;
        fprintf(fout, stu->id);
        fprintf(fout, sep);
        fprintf(fout, stu->name);
        fprintf(fout, sep);
        fprintf(fout, "%i", stu->gender);
        for (int i = 0; i < COURSE_NUM; ++i)
        {
            fprintf(fout, sep);
            fprintf(fout, "%.2f", stu->score[i]);
        }
        fputc('\n', fout);
        node = node->nxt;
        fflush(fout);  // 随时flush防止数据丢失
    }
    fclose(fout);
    return cnt;
}
