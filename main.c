/* main.c */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include "list.h"
#include "file_util.h"
#include "ui.h"

int main()
{
    List* list = newList();
    initDataUi(list);
    clear();
    while (true)
    {
        int opt;
        do {
            puts("");
            puts("Choose option: ");
            puts("1. Add a new record");
            puts("2. Save changes");
            puts("3. View records");
            puts("0. Quit");
        } while (!getOpt(&opt) || opt < 0 || opt > 3);

        clear();
        switch (opt)
        {
        case 0:
            exit(0);
        case 1:
            newRecordUi(list);
            clear();
            puts("Record saved.\n");
            break;
        case 2:
            clear();
            if (writeData(list) < 0)
                fputs("Failed to save data!\n\n", stderr);
            else
                puts("Saved!");
            break;
        case 3:
            viewRecordsUi(list);
            clear();
            break;
        }
    }
    return 0;
}
