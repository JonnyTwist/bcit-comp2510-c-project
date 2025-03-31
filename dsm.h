/**
* Allows using the dsm.c file from other files
 *@author Nicolas Bertrand
 *@author Jonny Twist
 *@version 1.0
 */
#include "list.h"
#ifndef DSM_H
#define DSM_H

#define MIN_ID 0
#define DAYS_IN_WEEK 7
#define SHIFTS_PER_DAY 3
#define TABLE_FORMATTED_LENGTH 13
#define MAX_STRING_LENGTH 100
#define ID_NOT_FOUND (-1)


typedef struct doctor_struct
{
    int doctor_id; // not negative
    char name[100];
} doctor;

extern struct list* doctor_list;
extern int doctorCount;
extern int schedule[DAYS_IN_WEEK][SHIFTS_PER_DAY];

int docIdExists(struct list* doc_list, int size, int id);
void addDoc();
void enterDocId(int* id);
void enterDocName(char* name);
void manageDoctorsMenu();
void displayDoctors();
int removeDoctor(int doctorID);
void addDocToTimeSlot();
void printSchedule();
void printTableHeader();
void truncateStr(char str[], int newLength);
void clearTimeSlot();

#endif //DSM_H
