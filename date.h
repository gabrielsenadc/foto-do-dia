#ifndef date_h
#define date_h

#include <stdio.h>

typedef struct data Date;

typedef struct list DateList;

Date * createDate(int day, int month, int year);

void setDate(Date * date, int day, int month, int year);

Date * copyDate(Date * date);

void incDate(Date * date); 

void printDate(Date * date);

void printFileDate(Date * date, FILE * file);

void freeDate(Date * date);

int getDay(Date * date);

int getMonth(Date * date);

int getYear(Date * date);

DateList * createDateList();

void insertDate(DateList * list, Date * date);

void freeDateList(DateList * list);

void printDateList(DateList * list);

void printFileDateList(DateList * list, FILE * file);



#endif