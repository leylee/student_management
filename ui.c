/* ui.c */

#include "list.h"
#include <stdio.h>
#include "ui.h"
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "file_util.h"
#ifdef WIN32
#include <windows.h>
#endif // WIN32

/** 播放错误提示音 */
void errorSound()
{
    #ifdef WIN32
    PlaySound((LPCTSTR)SND_ALIAS_SYSTEMHAND, NULL, SND_ALIAS_ID | SND_ASYNC);
    #else
    putchar('\a');
    #endif // WIN32
}

/** 清屏函数 */
void clear()
{
    /* Windows 系统中的清屏和 *nix 的不同 */
    #ifdef WIN32
    system("cls");
    #else
    system("clear");
    #endif
}

/** 清空缓冲区函数 */
void purgeBuf()
{
    int ch;
    while ((ch=getchar()) != EOF && ch != '\n')
        ;
}

/** 获取选项, 成功返回 true, 失败返回 false */
bool getOpt(int* pt)
{
    if (scanf("%d", pt) == 1)
    {
        purgeBuf();
        return true;
    }
    else
    {
        purgeBuf();
        return false;
    }
}

/** 打印一条学生信息 */
static void printStu(Student *stu)
{
    printf("%4d%11s%10s%7s%6.2f%8.2f%8.2f%8.2f%7.2f\n", stu->rank, stu->id, stu->name, gender_str[stu->gender],
            stu->score[math], stu->score[english], stu->score[physics], stu->avg, stu->sum);
}

/** 打印表头 */
static void printTitle()
{
    printf("%4s%11s%10s%7s%6s%8s%8s%8s%7s\n", "Rank", "ID", "Name", "Gender", "Math", "English", "Physics", "Average", "Sum");
    puts("---- ---------- --------- ------ ----- ------- ------- ------- ------");
}

/** 打印链表 */
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

/** 以下的 getXxx 函数为读取信息的函数
 * hint 参数为读取时的提示语.
 * 使用scanf的每次读取后, 使用purgeBuf清空缓冲区.
 * 若读取失败, 发出提示音, 重新提示用户输入.
 */
/* 读入分数, 范围 0-100 */
static double getScore(const char* hint)
{
    double score;
    while (true)
    {
        if (hint)
            printf(hint);
        if (scanf("%lf", &score) == 1
                && score >= 0 && score <= 100)
            break;
        errorSound();
        purgeBuf();
    }
    purgeBuf();
    return score;
}

/* 读入性别, 范围 0-2 */
static Gender getGender(const char* hint)
{
    int gender;
    while (true)
    {
        if (hint)
            printf(hint);
        if (scanf("%d", &gender) == 1
                && gender >= 0 && gender <= 2)
            break;
        errorSound();
        purgeBuf();
    }
    purgeBuf();
    return gender;
}

/* 读入字符串, 缓冲区和字符串长度 (长度不包含空白符) 由参数给定 */
static void getString(const char* hint, char* str, int length)
{
    if (hint)
        printf(hint, length);
    fgets(str, length + 2, stdin);
    str[strlen(str) - 1] = '\0';
}

/* 读入课程, 范围0到COURSE_NUM */
static Course getCourse(const char* hint)
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
        if (scanf("%d", &course) == 1
                && course >= 0 && course < COURSE_NUM)
            break;
        errorSound();
        purgeBuf();
    }
    purgeBuf();
    return course;
}

/* 读入排名 */
static int getRank(const char* hint)
{
    int rank;
    while (true)
    {
        puts(hint);
        if (scanf("%d", &rank) == 1)
            break;
        errorSound();
        purgeBuf();
    }
    purgeBuf();
    return rank;
}

/** 改变字符串首字母为大写字母 */
static char* capitalize(char* str)
{
    str[0] = toupper(str[0]);
    return str;
}

/** 程序开始时, 询问数据来源的界面
 * 从文件读入, 或使用空白的链表
 */
void initDataUi(List* list)
{
    int opt;
    clear();
    puts("Welcome to Student Manager!");
    while (true)
    {
        do {
            puts("\nLoad student data from file?");
            puts("1. Yes");
            puts("2. No, create a new file to save student data");
            puts("0. Quit");

            if (getOpt(&opt) && opt >= 0 && opt <= 2)
                break;
            errorSound();
        } while (true);

        switch (opt)
        {
        case 0:
            exit(0);
        case 1:
            if (readData(list) < 0)
            {
                errorSound();
                fputs("No saved data file found!\n\n", stderr);
            }
            else
                return;
            break;
        case 2:
            return;
            break;
        }
    }
}

/** 添加新的学生记录界面 */
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

/** 查找记录界面 */
static List* searchUi(List* list)
{
    char id[ID_SIZE];
    char name[NAME_SIZE];
    double minScore, maxScore;
    int minRank, maxRank;
    int course;

    clear();
    int opt;
    do {
        puts("");
        puts("Search by:");
        puts("1. Student ID");
        puts("2. Name");
        puts("3. Average score");
        puts("4. Single course score");
        puts("5. Rank");

        if (getOpt(&opt) && opt >= 1 && opt <= 5)
            break;
        errorSound();
    } while (true);
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
    /* 加入 default 分支, 消除编译器的无返回值警告 */
    default:
        fputs("Error in searchUi!", stderr);
        return newList();
    }
}

/** 输出数据分析的界面, 如及格人数等 */
static void analyzeUi(List* list)
{
    double courseAvg[COURSE_NUM], sumAvg, avgAvg; // 单科平均成绩, 平均成绩的平均成绩, 总分的平均成绩
    int courseLetter[COURSE_NUM][5] = {0}, avgLetter[5] = {0}; // 单科和平均分各个字母评级的人数, 初始化为0
    const char letter_char[] = {'A', 'B', 'C', 'D', 'F'}; // 字母评级序号对应的字母
    for (int i = 0; i < COURSE_NUM; ++i)
    {
        courseAvg[i] = calcCourseAvg(list, i);
    }
    sumAvg = calcSumAvg(list);
    avgAvg = sumAvg / COURSE_NUM;
    calcCourseLetter(list, courseLetter);
    calcAvgLetter(list, avgLetter);

    clear();
    /* 输出平均成绩 */
    puts("Average score of:");
    for (int i = 0; i < COURSE_NUM; ++i)
    {
        char course[10];
        strcpy(course, course_str[i]);
        printf("\t%-7s:%6.2f\n", capitalize(course), courseAvg[i]);
    }
    printf("\t%-7s:%6.2f\n", "Average", avgAvg);
    printf("\t%-7s:%6.2f\n", "Sum", sumAvg);
    puts("");
    /* 输出字母评级人数及百分比 */
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

/** 排序界面 */
static void sortUi(List* list)
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

        if (getOpt(&opt) && opt >= 1 && opt <= 5)
            break;
        errorSound();
    } while(true);

    if (opt == 4)
    {
        course = getCourse("Select course: ");
    }

    do {
        puts("Order:");
        puts("0. Ascending");
        puts("1. Descending");

        if (getOpt(&reverseOpt) && reverseOpt >= 0 && reverseOpt <= 1)
            break;
        errorSound();
    } while (true);
    reverse = (bool) reverseOpt;

    switch (opt)
    {
    case 1:
        heapSortList(list, KEY_ID, reverse);
        break;
    case 2:
        heapSortList(list, KEY_NAME, reverse);
        break;
    case 3:
        heapSortList(list, KEY_AVERAGE, reverse);
        break;
    case 4:
        heapSortList(list, course, reverse);
        break;
    case 5:
        heapSortList(list, KEY_RANK, reverse);
        break;
    }
}

/** 查看并操作记录的界面
 * 此界面集成查找记录, 数据分析, 排序, 和删除功能.
 * 进入此菜单后, 会生成一份学生数据的拷贝.
 * 每次查找时, 将会更新当前的学生列表.
 * 统计数据, 排序, 删除记录时, 均在当前的列表内操作.
 * 排序后, 可以重新为记录排名. 只有当 Re-rank 时, 每个人的排名会变化.
 * 此种设计模式, 可以实现多轮查找, 更加精准.
 */
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
        do {
            puts("");
            puts("1. Back to main menu");
            puts("2. Search from result");
            puts("3. Analyze result");
            puts("4. Sort result");
            puts("5. Re-rank records");
            puts("6. Delete records in result and back to main menu");
            puts("0. Quit");

            if (getOpt(&opt) && opt >= 0 && opt <= 6)
                break;
            errorSound();
        } while (true);

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
