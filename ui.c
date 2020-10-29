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

/** ���Ŵ�����ʾ�� */
void errorSound()
{
    #ifdef WIN32
    PlaySound((LPCTSTR)SND_ALIAS_SYSTEMHAND, NULL, SND_ALIAS_ID | SND_ASYNC);
    #else
    putchar('\a');
    #endif // WIN32
}

/** �������� */
void clear()
{
    /* Windows ϵͳ�е������� *nix �Ĳ�ͬ */
    #ifdef WIN32
    system("cls");
    #else
    system("clear");
    #endif
}

/** ��ջ��������� */
void purgeBuf()
{
    int ch;
    while ((ch=getchar()) != EOF && ch != '\n')
        ;
}

/** ��ȡѡ��, �ɹ����� true, ʧ�ܷ��� false */
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

/** ��ӡһ��ѧ����Ϣ */
static void printStu(Student *stu)
{
    printf("%4d%11s%10s%7s%6.2f%8.2f%8.2f%8.2f%7.2f\n", stu->rank, stu->id, stu->name, gender_str[stu->gender],
            stu->score[math], stu->score[english], stu->score[physics], stu->avg, stu->sum);
}

/** ��ӡ��ͷ */
static void printTitle()
{
    printf("%4s%11s%10s%7s%6s%8s%8s%8s%7s\n", "Rank", "ID", "Name", "Gender", "Math", "English", "Physics", "Average", "Sum");
    puts("---- ---------- --------- ------ ----- ------- ------- ------- ------");
}

/** ��ӡ���� */
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

/** ���µ� getXxx ����Ϊ��ȡ��Ϣ�ĺ���
 * hint ����Ϊ��ȡʱ����ʾ��.
 * ʹ��scanf��ÿ�ζ�ȡ��, ʹ��purgeBuf��ջ�����.
 * ����ȡʧ��, ������ʾ��, ������ʾ�û�����.
 */
/* �������, ��Χ 0-100 */
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

/* �����Ա�, ��Χ 0-2 */
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

/* �����ַ���, ���������ַ������� (���Ȳ������հ׷�) �ɲ������� */
static void getString(const char* hint, char* str, int length)
{
    if (hint)
        printf(hint, length);
    fgets(str, length + 2, stdin);
    str[strlen(str) - 1] = '\0';
}

/* ����γ�, ��Χ0��COURSE_NUM */
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

/* �������� */
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

/** �ı��ַ�������ĸΪ��д��ĸ */
static char* capitalize(char* str)
{
    str[0] = toupper(str[0]);
    return str;
}

/** ����ʼʱ, ѯ��������Դ�Ľ���
 * ���ļ�����, ��ʹ�ÿհ׵�����
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

/** ����µ�ѧ����¼���� */
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

/** ���Ҽ�¼���� */
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
    /* ���� default ��֧, �������������޷���ֵ���� */
    default:
        fputs("Error in searchUi!", stderr);
        return newList();
    }
}

/** ������ݷ����Ľ���, �缰�������� */
static void analyzeUi(List* list)
{
    double courseAvg[COURSE_NUM], sumAvg, avgAvg; // ����ƽ���ɼ�, ƽ���ɼ���ƽ���ɼ�, �ֵܷ�ƽ���ɼ�
    int courseLetter[COURSE_NUM][5] = {0}, avgLetter[5] = {0}; // ���ƺ�ƽ���ָ�����ĸ����������, ��ʼ��Ϊ0
    const char letter_char[] = {'A', 'B', 'C', 'D', 'F'}; // ��ĸ������Ŷ�Ӧ����ĸ
    for (int i = 0; i < COURSE_NUM; ++i)
    {
        courseAvg[i] = calcCourseAvg(list, i);
    }
    sumAvg = calcSumAvg(list);
    avgAvg = sumAvg / COURSE_NUM;
    calcCourseLetter(list, courseLetter);
    calcAvgLetter(list, avgLetter);

    clear();
    /* ���ƽ���ɼ� */
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
    /* �����ĸ�����������ٷֱ� */
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

/** ������� */
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

/** �鿴��������¼�Ľ���
 * �˽��漯�ɲ��Ҽ�¼, ���ݷ���, ����, ��ɾ������.
 * ����˲˵���, ������һ��ѧ�����ݵĿ���.
 * ÿ�β���ʱ, ������µ�ǰ��ѧ���б�.
 * ͳ������, ����, ɾ����¼ʱ, ���ڵ�ǰ���б��ڲ���.
 * �����, ��������Ϊ��¼����. ֻ�е� Re-rank ʱ, ÿ���˵�������仯.
 * �������ģʽ, ����ʵ�ֶ��ֲ���, ���Ӿ�׼.
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
