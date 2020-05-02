#ifndef UI_H_INCLUDED
#define UI_H_INCLUDED

#include "list.h"

void printList(List* list);
void printTitle();
double getScore(const char* hint);
int getGender(const char* hint);
void getString(const char* hint, char* buf, int bufsize);

#endif // UI_H_INCLUDED