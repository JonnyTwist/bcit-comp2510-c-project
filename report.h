//
// Created by maxym on 03/04/2025.
//

#ifndef BCIT_COMP2510_C_PROJECT_REPORT_H
#define BCIT_COMP2510_C_PROJECT_REPORT_H
#include "list.h"

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
int discharged_in_day(struct list* patient_list);
int admitted_in_mwd(struct list* patient_list);
void doctor_report(struct list* doctor_list, struct list** doc_report);

#endif //BCIT_COMP2510_C_PROJECT_REPORT_H
