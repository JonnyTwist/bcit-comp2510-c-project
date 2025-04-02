/**
* Allows using the patient.c file from other files
 *@author Nicolas Bertrand
 *@author Jonny Twist
 *@version 1.0
 */

#ifndef PATIENT_H
#define PATIENT_H

#include <time.h>
#include "list.h"

#define MIN_AGE 0
#define MIN_ID 0
#define MIN_ROOM_NUM 0
#define MAX_STRING_LENGTH 100
#define ID_NOT_FOUND (-1)

typedef struct patient_struct
{
    int patient_id;
    char name[100];
    int age;
    char diagnosis[100];
    int room_number;
    struct tm* date_admitted;
    struct tm* date_discharged;
} patient;

//extern patient patients[50];
extern int patientCount;
extern int dischargedPatientCount;
extern struct list* patientList;
extern struct list* dischargedPatientList;

int idExists(struct list* patient_list, int size, int id);
int dischargePatient(int patient_id);
void displayPatient(patient patient);
void emptyRemainingInput();
void addPatient();
void enterPatientId(int* id);
void enterPatientName(char* name);
void enterPatientAge(int* age);
void enterPatientDiagnosis(char* diagnosis);
void enterPatientRoom(int* roomNumber);
void viewAllPatients();
void viewAllDischargedPatients();
void searchPatient();
void searchPatientByID();
void searchPatientByName();
void stringTrim(char* string);
int validateString(char string[100]);
struct tm* getCurrentTime();

#endif //PATIENT_H
