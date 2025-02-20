//
// Created by maxym on 11/02/2025.
//

#ifndef PATIENT_H
#define PATIENT_H

#define MIN_AGE 0
#define MIN_ID 0
#define MIN_ROOM_NUM 0

typedef struct patient_struct
{
    int patient_id;
    char name[100];
    int age;
    char diagnosis[100];
    int room_number;
} patient;

extern patient patients[50];
extern int patientCount;

int idExists(patient arr[], int size, int id);
int dischargePatient(int patient_id);
void displayPatient(patient patient);
void emptyRemainingInput();
void addPatient();
void enterPatientId(int* id);
void enterPatientName(char* name);
void enterPatientAge(int* age);
void enterPatientDiagnosis(char* diagnosis);
void enterPatientRoom(int* roomNumber);
void addPatient1(patient patientToAdd);
void viewAllPatients();
void searchPatient();
void searchPatientByID();
void searchPatientByName();
void stringTrim(char* string);
int validateString(char string[100]);

#endif //PATIENT_H
