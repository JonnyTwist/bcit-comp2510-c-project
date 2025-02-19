//
// Created by jsatw on 2025-02-16.
//

#ifndef DSM_H
#define DSM_H

#define MIN_ID 0
#define DAYS_IN_WEEK 7
#define SHIFTS_PER_DAY 3
#define TABLE_FORMATTED_LENGTH 13

typedef struct doctor_struct
{
    int doctor_id; // not negative
    char name[100];
} doctor;

extern doctor doctors[10];
extern int doctorCount;
extern int schedule[DAYS_IN_WEEK][SHIFTS_PER_DAY];

int docIdExists(doctor arr[], int size, int id);
void addDoc();
void manageDoctorsMenu();
void displayDoctors();
int removeDoctor(int doctorID);
void addDocToTimeSlot();
void printSchedule();
void printTableHeader();
void truncateStr(char str[], int newLength);
void clearTimeSlot();

#endif //DSM_H
