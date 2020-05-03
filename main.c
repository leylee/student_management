#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include "student.h"
#include "list.h"
#include "file_util.h"
#include "ui.h"

void clear()
{
    #ifdef WIN32
    system("cls");
    #else
    system("clear");
    #endif
}

int getOpt(int* pt)
{
    rewind(stdin);
    return scanf("%d", pt);
}

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

        if (getOpt(&opt) != 1)
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
    calcList(list);
}

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

    calcStu(stu);
    push_back(list, node);
}

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

void searchUi(List* ori)
{
    List* list = newListFromOri(ori);
    List* result = NULL;
    char id[ID_SIZE];
    char name[NAME_SIZE];
    double minScore, maxScore;
    int course;
    bool back = false;
    clear();

    while (true)
    {
        printList(list);
        while (true)
        {
            bool success;
            int opt;
            puts("");
            puts("Search by:");
            puts("1. Student ID");
            puts("2. Name");
            puts("3. Average core");
            puts("4. Single course score");
            puts("0. Quit");

            success = true;
            if (getOpt(&opt) != 1)
                continue;
            switch (opt)
            {
            case 0:
                exit(0);
            case 1:
                getString("Student ID (less than %i characters): ", id, ID_LENGTH);
                result = searchById(list, id);
                break;
            case 2:
                getString("Name (less than %i characters): ", name, NAME_LENGTH);
                result = searchByName(list, name);
                break;
            case 3:
                minScore = getScore("Min score (between 0 and 100): ");
                maxScore = getScore("Max score (between 0 and 100): ");
                result = searchByAvgScore(list, minScore, maxScore);
                break;
            case 4:
                course = getCourse("Select course");
                minScore = getScore("Min score (between 0 and 100): ");
                maxScore = getScore("Max score (between 0 and 100): ");
                result = searchByCourseScore(list, minScore, maxScore, course);
                break;
            default:
                success = false;
            }

            if (success)
                break;
        }

        printList(result);
        freeList(list);
        list = result;

        bool success = false;
        while (!back && !success)
        {
            int opt;
            puts("");
            puts("1. Back to main menu");
            puts("2. Searching from result");
            puts("3. Analyze result");
            puts("4. Delete records in result and back to main menu");
            puts("0. Quit");

            if (getOpt(&opt) != 1)
                continue;
            switch (opt)
            {
            case 0:
                exit(0);
            case 1:
                back = true;
                break;
            case 2:
                success = true;
                clear();
                break;
            case 3:
                analyzeUi(result);
                printList(result);
                break;
            case 4:
                deleteListFromOri(list, result);
                back = true;
                break;
            }
        }

        if (back)
            break;
    }

    freeList(list);
}

int main()
{
    List* list = newList();
    initDataUi(list);
    printList(list);
    clear();
    while (true)
    {
        int opt;
        puts("");
        puts("Choose option: ");
        puts("1. List all records");
        puts("2. List sorted records");
        puts("3. Search records");
        puts("4. Add a new record");
        puts("5. Analyze scores");
        puts("6. Save changes");
        puts("0. Exit");

        if (getOpt(&opt) != 1)
            continue;
        clear();
        switch (opt)
        {
        case 0:
            exit(0);
        case 1:
            clear();
            printList(list);
            break;
        case 3:
            searchUi(list);
            clear();
            break;
        case 4:
            newRecordUi(list);
            clear();
            puts("Record saved.\n");
            break;
        case 5:
            analyzeUi(list);
            break;
        case 6:
            clear();
            if (writeData(list) < 0)
                fputs("Failed to save data!\n\n", stderr);
            else
                puts("Saved!");
            break;
        }
    }
    return 0;
}
