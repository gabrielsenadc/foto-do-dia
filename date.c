#include <stdlib.h>
#include <string.h>
#include "date.h"

struct data{
    int day;
    int month;
    int year;
};

typedef struct cell Cell;

struct list{
    Cell * first;
    Cell * last;
};

struct cell{
    Date * date;
    Cell * next;
};



Date * createDate(int day, int month, int year){
    Date * date = malloc(sizeof(Date));

    date->day = day;
    date->month = month;
    date->year = year;

    return date;
}

void setDate(Date * date, int day, int month, int year){
    date->day = day;
    date->month = month;
    date->year = year;
}

Date * copyDate(Date * date){
    Date * dateNew = malloc(sizeof(Date));

    dateNew->day = date->day;
    dateNew->month = date->month;
    dateNew->year = date->year;

    return dateNew;
}

void incDate(Date * date){
    date->day++;

    if(date->month == 1 || date->month == 3 || date->month == 5 || date->month == 7 || date->month == 8 || date->month == 10 || date->month == 12){
        if(date->day > 31){
            date->day = 1;
            date->month++;
        } 
    } else if(date->month == 2){
        if(date->year % 4 == 0){
            if(date->day > 29){
                date->day = 1;
                date->month++;
            } 
        } else {
            if(date->day > 28){
                date->day = 1;
                date->month++;
            }
        }
    } else {
        if(date->day > 30){
            date->day = 1;
            date->month++;
        }
    }

    if(date->month > 12){
        date->month = 1;
        date->year++;
    }
}

void freeDate(Date * date){
    free(date);
}

void printDate(Date * date){
    printf("%02d/%02d/%04d\n", date->day, date->month, date->year);
}

void printFileDate(Date * date, FILE * file){
    fprintf(file, "%02d/%02d/%04d\n", date->day, date->month, date->year);
}

int getDay(Date * date){
    return  date->day;
}

int getMonth(Date * date){
    return  date->month;
}

int getYear(Date * date){
    return  date->year;
}

DateList * createDateList(){
    DateList * list = malloc(sizeof(DateList));

    list->first = list->last = NULL;

    return list;
}

void insertDate(DateList * list, Date * date){
    Cell * cell = malloc(sizeof(Cell));

    cell->date = date;
    cell->next = NULL;

    if(list->last) list->last->next = cell;
    list->last = cell;

    if(!list->first) {
        list->first = cell;
        list->last = cell;
    }
}

void freeCell(Cell * cell){
    if(cell == NULL) return;

    freeDate(cell->date);
    freeCell(cell->next);

    free(cell);
}

void freeDateList(DateList * list){
    freeCell(list->first);

    free(list);
}

void printCell(Cell * cell){
    if(cell == NULL) return;

    printDate(cell->date);
    printCell(cell->next);
}

void printFileCell(Cell * cell, FILE * file){
    if(cell == NULL) return;

    printFileDate(cell->date, file);
    printFileCell(cell->next, file);
}

void printDateList(DateList * list){
    printCell(list->first);
}

void printFileDateList(DateList * list, FILE * file){
    printFileCell(list->first, file);
}   

int isBefore(Date * date, Date * end){
    if(date->year < end->year) return 1;
    if(date->year == end->year){
        if(date->month < end->month) return 1;
        if(date->month == end->month){
            if(date->day <= end->day) return 1;
        }
    }
    return 0;
}

int isAfter(Date * date, Date * start){
    if(date->year > start->year) return 1;
    if(date->year == start->year){
        if(date->month > start->month) return 1;
        if(date->month == start->month){
            if(date->day >= start->day) return 1;
        }
    }
    return 0;
}

int isBetween(Date * date, Date * start, Date * end){  
    if(isAfter(date, start) && isBefore(date, end)) return 1;

    return 0;
}

DateList * filterList(DateList * list, Date * start, Date * end){
    DateList * new = createDateList();

    for(Cell * cell = list->first; cell; cell = cell->next){
        if(isBetween(cell->date, start, end)) insertDate(new, copyDate(cell->date));
    }

    return new;
}

int getListQtt(DateList * list){
    int total = 0;
    for(Cell * cell = list->first; cell; cell = cell->next) total++;
    return total;
}