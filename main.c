#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "student.h"
#include "list.h"
#include "file_util.h"

void printList(List* list)
{
    printf("%11s%10s%7s%6s%8s%8s%8s%7s\n", "ID", "Name", "Gender", "Math", "English", "Physics", "Average", "Sum");
    puts("----------- --------- ------ ----- ------- ------- ------- ------");
    Node* node = list->head->nxt;
    while (node->nxt != NULL)
    {
        Student *stu = node->stu;
        printf("%11s%10s%7s\n", stu->id, stu->name, gender_str[stu->gender]);

        node = node->nxt;
    }
}

void clear()
{
    system("cls");
}

int getOpt(int* pt)
{
    rewind(stdin);
    return scanf("%d", pt);
}

void initData(List* list)
{
    int opt;
    bool success = false;
    clear();
    puts("Welcome to Student Manager!");
    while (!success)
    {
        puts("Load student data from file?");
        puts("1. Yes");
        puts("2. No, create a new file to save student data");
        puts("0. Exit");

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
}

void newRecord(List* list)
{
    clear();
    Node* node = newNode();
    Student* stu = node->stu;

    rewind(stdin);
    printf("Student ID (less than %i characters): ", ID_LENGTH);
    fgets(stu->id, ID_LENGTH, stdin);
    stu->id[strlen(stu->id) - 1] = '\0';
    rewind(stdin);
    printf("Name (less than %i characters): ", NAME_LENGTH);
    fgets(stu->name, NAME_LENGTH, stdin);
    stu->name[strlen(stu->name) - 1] = '\0';
    while (true)
    {
        printf("Gender (1: male, 2: female, 0: other): ");
        rewind(stdin);
        if (scanf("%d", &stu->gender) == 1
                && stu->gender >= 0 && stu->gender <= 2)
            break;
    }
    while (true)
    {
        printf("Math score (between 0 and 100): ");
        rewind(stdin);
        if (scanf("%lf", &stu->score[math]) == 1
                && stu->score[math] >= 0 && stu->score[math] <= 100)
            break;
    }
    while (true)
    {
        printf("English score (between 0 and 100): ");
        rewind(stdin);
        if (scanf("%lf", &stu->score[english]) == 1
                && stu->score[english] >= 0 && stu->score[english] <= 100)
            break;
    }
    while (true)
    {
        printf("Physics score (between 0 and 100): ");
        rewind(stdin);
        if (scanf("%lf", &stu->score[physics]) == 1
                && stu->score[physics] >= 0 && stu->score[physics] <= 100)
            break;
    }
    push_back(list, node);
}

int main()
{
    List* list = newList();
    initData(list);
    printList(list);
    while (true)
    {
        int opt;
        puts("1. List all records");
        puts("2. List sorted records");
        puts("3. Search records");
        puts("4. Add a new record");
        puts("5. Save changes");
        puts("0. Exit");
        clear();

        if (getOpt(&opt) != 1)
            continue;
        switch (opt)
        {
        case 0:
            exit(0);
        case 1:
            printList(list);
            break;
        case 4:
            newRecord(list);
            puts("Record saved.\n");
            break;
        case 5:
            if (writeData(list) < 0)
                fputs("Failed to save data!\n\n", stderr);
            else
                puts("Saved!");
            break;
        }
    }
    return 0;
}
