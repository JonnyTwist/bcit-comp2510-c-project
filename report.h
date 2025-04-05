//
// Created by maxym on 03/04/2025.
//
#ifndef BCIT_COMP2510_C_PROJECT_REPORT_H
#define BCIT_COMP2510_C_PROJECT_REPORT_H
#include "list.h"
#include "time.h"

typedef struct key_value
{
    int key;
    int value;
} Key_value;

typedef struct room_use_struct
{
    int room_number;
    int nb_patients;
} Room_use;

typedef struct doc_use
{
    int doc_id;
    int nb_shift;
} Doc_use;

void room_report(struct list* patient_list, struct list** room_report);
int discharged_in_day(struct list* patient_list, struct tm left, struct tm right);
int admitted_in_mwd(struct list* patient_list, struct tm left, struct tm right);
void doctor_report(struct list* doctor_list, struct list** doc_report);
int admitted_in_interval(struct list* patient_list, struct tm left, struct tm right);
int discharged_in_interval(struct list* patient_list, struct tm left, struct tm right);
void reportMenu();
void prepareForPatientReport();
void request_month(int option);
void request_day(int intake, int option);
struct tm createTime(int date, int month, int year);

#endif //BCIT_COMP2510_C_PROJECT_REPORT_H
