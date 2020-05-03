/* ui.h */

#ifndef UI_H_INCLUDED
#define UI_H_INCLUDED

#include "list.h"

void clear();
void printList(List* list);
void viewRecordsUi(List* ori);
bool getOpt(int* pt);
void initDataUi(List* list);
void newRecordUi(List* list);

#endif // UI_H_INCLUDED
