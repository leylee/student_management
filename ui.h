/* ui.h */

#ifndef UI_H_INCLUDED
#define UI_H_INCLUDED

#include "list.h"

void clear();
void printList(List* list);
void printTitle();
double getScore(const char* hint);
int getGender(const char* hint);
void getString(const char* hint, char* buf, int bufsize);
int getCourse(const char* hint);
int getRank(const char* hint);
char* captialize(char* str);
void viewRecordsUi(List* ori);
bool getOpt(int* pt);
void initDataUi(List* list);
void newRecordUi(List* list);

#endif // UI_H_INCLUDED
