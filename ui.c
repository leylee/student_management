#include "list.h"
#include <stdio.h>
#include "ui.h"
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "file_util.h"

/* 清屏函数 */
void clear()
{
    #ifdef WIN32
    system("cls");
    #else
    system("clear");
    #endif
}

/* 获取选项, 成功返回 true, 失败返回 false */
bool getOpt(int* pt)
{
    rewind(stdin);
    return scanf("%d", pt) == 1;
}

/* 打印节点 */
void printStu(Student *stu)
{
    printf("%4d%11s%10s%7s%6.2f%8.2f%8.2f%8.2f%7.2f\n", stu->rank, stu->id, stu->name, gender_str[stu->gender],
            stu->score[math], stu->score[english], stu->score[physics], stu->avg, stu->sum);
}

/* 打印链表 */
void printList(List* list)
{
    printTitle();
    Node* node = list->head->nxt;
    while (node->nxt != NULL)
    {
        printStu(node->stu);
        node = node->nxt;
    }
}

/* 打印表头 */
void printTitle()
{
    printf("%4s%11s%10s%7s%6s%8s%8s%8s%7s\n", "Rank", "ID", "Name", "Gender", "Math", "English", "Physics", "Average", "Sum");
    puts("---- ---------- --------- ------ ----- ------- ------- ------- ------");
}

/* 读入分数, 范围 0-100 */
double getScore(const char* hint)
{
    double score;
    while (true)
    {
        if (hint)
            printf(hint);
        rewind(stdin);
        if (scanf("%lf", &score) == 1
                && score >= 0 && score <= 100)
            break;
    }
    return score;
}

/* 读入性别, 范围 0-2 */
int getGender(const char* hint)
{
    int gender;
    while (true)
    {
        if (hint)
            printf(hint);
        rewind(stdin);
        if (scanf("%d", &gender) == 1
                && gender >= 0 && gender <= 2)
            break;
    }
    return gender;
}

/* 读入字符串, 缓冲区和字符串长度 (长度不包含空白符) 由参数给定 */
void getString(const char* hint, char* str, int length)
{
    if (hint)
        printf(hint, length);
    rewind(stdin);
    fgets(str, length + 2, stdin);
    str[strlen(str) - 1] = '\0';
}

/* 读入课程 */
int getCourse(const char* hint)
{
    int course;
    while (true)
    {
        puts(hint);
        for (int i = 0; i < COURSE_NUM; ++i)
        {
            if (i)
                printf(", ");
            printf("%s: %i", course_str[i], i);
        }
        putchar('\n');
        rewind(stdin);
        if (scanf("%d", &course) == 1
                && course >= 0 && course < COURSE_NUM)
            break;
    }
    return course;
}

/* 读入排名 */
int getRank(const char* hint)
{
    int rank;
    while (true)
    {
        puts(hint);
        if (scanf("%d", &rank) == 1)
            break;
    }
    return rank;
}

/* 改变字符串首字母为大写字母 */
char* captialize(char* str)
{
    str[0] = toupper(str[0]);
    return str;
}

/* 程序开始时, 询问数据来源的界面 */
void initDataUi(List* list)
{
    int opt;
    bool success = false;
    clear();
    puts("Welcome to Student Manager!");
    while (!success)
    {
        puts("\nLoad student data from file?");
        puts("1. Yes");
        puts("2. No, create a new file to save student data");
        puts("0. Quit");

        if (!getOpt(&opt))
            continue;
        switch (opt)
        {
        case 0:
            exit(0);
        case 1:
            if (readData(list) < 0)
                fputs("No saved data file found!\n\n", stderr);
            else
                success = true;
            break;
        case 2:
            success = true;
            break;
        }
    }
}

/* 添加新记录界面 */
void newRecordUi(List* list)
{
    clear();
    Node* node = newNode();
    Student* stu = node->stu;

    getString("Student ID (less than %i characters): ", stu->id, ID_LENGTH);
    getString("Name (less than %i characters): ", stu->name, NAME_LENGTH);
    stu->gender = getGender("Gender (1: male, 2: female, 0: other): ");
    for (int i = 0; i < COURSE_NUM; ++i)
    {
        char hint[80] = "";
        strcat(hint, course_str[i]);
        strcat(hint, " score (between 0 and 100): ");
        hint[0] = toupper(hint[0]);
        stu->score[i] = getScore(hint);
    }

    push_back(list, node);
}

/* 查找界面 */
List* searchUi(List* ori)
{
    List* list = newListFromOri(ori);
    char id[ID_SIZE];
    char name[NAME_SIZE];
    double minScore, maxScore;
    int minRank, maxRank;
    int course;

    clear();
    while (true)
    {
        int opt;
        puts("");
        puts("Search by:");
        puts("1. Student ID");
        puts("2. Name");
        puts("3. Average score");
        puts("4. Single course score");
        puts("5. Rank");

        if (!getOpt(&opt))
            continue;
        switch (opt)
        {
        case 1:
            getString("Student ID (less than %i characters): ", id, ID_LENGTH);
            return searchById(list, id);
        case 2:
            getString("Name (less than %i characters): ", name, NAME_LENGTH);
            return searchByName(list, name);
        case 3:
            minScore = getScore("Min score (between 0 and 100): ");
            maxScore = getScore("Max score (between 0 and 100): ");
            return searchByAvgScore(list, minScore, maxScore);
        case 4:
            course = getCourse("Select course: ");
            minScore = getScore("Min score (between 0 and 100): ");
            maxScore = getScore("Max score (between 0 and 100): ");
            return searchByCourseScore(list, minScore, maxScore, course);
        case 5:
            minRank = getRank("Rank from: ");
            maxRank = getRank("To: ");
            return searchByRank(list, minRank, maxRank);
        }
    }
}

/* 输出数据分析的界面, 如及格人数等 */
void analyzeUi(List* list)
{
    double courseAvg[COURSE_NUM], sumAvg, avgAvg;
    int courseLetter[COURSE_NUM][5] = {0}, avgLetter[5] = {0};
    const char letter_char[] = {'A', 'B', 'C', 'D', 'F'};
    for (int i = 0; i < COURSE_NUM; ++i)
    {
        courseAvg[i] = calcCourseAvg(list, i);
    }
    sumAvg = calcSumAvg(list);
    avgAvg = sumAvg / COURSE_NUM;
    calcCourseLetter(list, courseLetter);
    calcAvgLetter(list, avgLetter);

    clear();
    puts("Average score of:");
    for (int i = 0; i < COURSE_NUM; ++i)
    {
        char course[10];
        strcpy(course, course_str[i]);
        printf("\t%-7s:%6.2f\n", captialize(course), courseAvg[i]);
    }
    printf("\t%-7s:%6.2f\n", "Average", avgAvg);
    printf("\t%-7s:%6.2f\n", "Sum", sumAvg);
    puts("");
    puts("Letter score number and percentage of:");
    puts("(A: 90+; B: 80+; C: 70+; D: 60+; F: 60-)");
    for (int i = 0; i < COURSE_NUM; ++i)
    {
        printf("\t%-7s:\n", course_str[i]);
        for (int j = 0; j < 5; ++j)
        {
            printf("\t\t%c:%3i,%6.2f%%\n", letter_char[j],
                   courseLetter[i][j], courseLetter[i][j] * 100. / list->length);
        }
    }
    printf("\t%-7s:\n", "Average");
    for (int i = 0; i < 5; ++i)
        printf("\t\t%c:%3i,%6.2f%%\n", letter_char[i],
               avgLetter[i], (double) avgLetter[i] * 100. / list->length);
}

/* 排序界面 */
void sortUi(List* list)
{
    int course;
    int opt;
    int reverseOpt;
    bool reverse;
    clear();
    do {
        puts("Sort by:");
        puts("1. ID");
        puts("2. Name");
        puts("3. Average / sum score");
        puts("4. Single course score");
        puts("5. rank");
    } while(!getOpt(&opt) && opt >= 1 && opt <= 5);

    if (opt == 4)
    {
        course = getCourse("Select course: ");
    }

    do {
        puts("Order:");
        puts("0. Ascending");
        puts("1. Descending");
    } while (!getOpt(&reverseOpt) && opt >= 0 && opt <= 1);
    reverse = (bool) reverseOpt;

    switch (opt)
    {
    case 1:
        sortList(list, ORDER_ID, reverse);
        break;
    case 2:
        sortList(list, ORDER_NAME, reverse);
        break;
    case 3:
        sortList(list, ORDER_AVERAGE, reverse);
        break;
    case 4:
        sortList(list, course, reverse);
        break;
    case 5:
        sortList(list, ORDER_RANK, reverse);
        break;
    }
}

/* 查看并操作记录的界面 */
void viewRecordsUi(List* ori)
{
    List* list = newListFromOri(ori);
    List* searchResult;
    bool back = false;

    clear();
    rankList(list);
    calcList(list);
    while (!back)
    {
        printList(list);
        int opt;
        puts("");
        puts("1. Back to main menu");
        puts("2. Search from result");
        puts("3. Analyze result");
        puts("4. Sort result");
        puts("5. Re-rank records");
        puts("6. Delete records in result and back to main menu");
        puts("0. Quit");

        if (!getOpt(&opt))
            continue;
        switch (opt)
        {
        case 0:
            exit(0);
        case 1:
            back = true;
            break;
        case 2:
            searchResult = searchUi(list);
            freeList(list);
            list = searchResult;
            clear();
            break;
        case 3:
            clear();
            analyzeUi(list);
            break;
        case 4:
            sortUi(list);
            clear();
            break;
        case 5:
            rankList(list);
            clear();
            break;
        case 6:
            deleteListFromOri(ori, list);
            clear();
            puts("Deleted!");
            back = true;
            break;
        }
    }

    freeList(list);
}
