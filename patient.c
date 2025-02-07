// Patient
// Created by maxym on 31/01/2025.
//

#include <string.h>
#include <stdio.h>

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

patient patients[50];
int patientCount = 0;

int idExists(patient arr[], int size, int id);
void emptyRemainingInput();
void addPatient();
// void dischargePatient(int patient_id);
void viewAllPatients();
void searchPatient();
// patient searchPatient(const char* patient_name);

/**
 * Clears the remaining input when there is overflow.
 */
void emptyRemainingInput() {
    int c = '0';
    while (c != '\n') {
        c = getchar();
    }
}

int idExists(patient arr[], int size, int id) {
    for (int i = 0; i < size; i++) {
        if (arr[i].patient_id == id) {
            return i;
        }
    }
    return -1;
}

void addPatient() {

    //todo make sure all verifications were successfully found and implemented

    if (patientCount >= 50) {
        printf("Maximum number of patients reached!\n");
        return;
    }

    patient patientToAdd;
    int patientID = -10;
    char patientName[100];
    int patientAge = -10;
    char patientDiagnosis[100];
    int patientRoomNumber = -10;
    int valid;

    //todo add a sentinel value(s) that allows users to quit at any point
    valid = 0;
    while (!valid) {
        printf("Enter the patient ID: ");
        scanf("%d", &patientID);
        getchar();
        if (patientID > MIN_ID && idExists(patients, patientCount, patientID) == -1) {
            valid = 1;
        } else {
            printf("Invalid or duplicate ID!\n");
        }
    }

    valid = 0;
    while (!valid) {

        //assumes the input is valid right away
        valid = 1;

        printf("Enter the patients name: ");
        fgets(patientName, 100, stdin);

        //ensures the input didnt overflow
        if (patientName[strlen(patientName) - 1] != '\n') {
            printf("Name too long! Maximum 99 characters allowed.\n");
            emptyRemainingInput();
            //sets valid to false so the loop will start again
            valid = 0;
        }

        // removes the newline character
        patientName[strcspn(patientName, "\n")] = 0;

        //Doesnt allow blank names
        //todo figure out how to check if it is just whitespace and deny those
        if (strlen(patientName) == 0) {
            printf("Name cannot be blank!\n");
            //sets valid to false so the loop will start again
            valid = 0;
        }
    }

    while (patientAge < MIN_AGE) {
        printf("Enter the patients age: ");
        scanf("%d", &patientAge);
        getchar();
        if (patientAge < MIN_AGE) {
            printf("Patient age must not be negative!\n");
        }
    }

    //todo I changed the diagnosis to a set length character array so I could continue with
    // other methods. It might be better as a pointer but since I haven't learned those yet idk
    // how to implement that :)
    valid = 0;
    while (!valid) {

        //assumes the input is valid right away
        valid = 1;

        printf("Enter the patients diagnosis: ");
        fgets(patientDiagnosis, 100, stdin);

        //ensures the input didnt overflow
        if (patientDiagnosis[strlen(patientDiagnosis) - 1] != '\n') {
            printf("Diagnosis too long! Maximum 99 characters allowed.\n");
            emptyRemainingInput();
            //sets valid to false so the loop will start again
            valid = 0;
        }

        // removes the newline character
        patientDiagnosis[strcspn(patientDiagnosis, "\n")] = 0;

        //Doesnt allow blank names
        //todo figure out how to check if it is just whitespace and deny those
        if (strlen(patientDiagnosis) == 0) {
            printf("Diagnosis cannot be blank!\n");
            //sets valid to false so the loop will start again
            valid = 0;
        }
    }

    while (patientRoomNumber < MIN_ROOM_NUM) {
        printf("Enter the patients room number: ");
        scanf("%d", &patientRoomNumber);
        getchar();
        if (patientRoomNumber < MIN_ROOM_NUM) {
            printf("Room number must not be negative!\n");
        }
    }

    patientToAdd.patient_id = patientID;
    strcpy(patientToAdd.name, patientName);
    patientToAdd.age = patientAge;
    strcpy(patientToAdd.diagnosis, patientDiagnosis);
    patientToAdd.room_number = patientRoomNumber;

    patients[patientCount] = patientToAdd;
    patientCount++;
}

void viewAllPatients() {
    printf("All patient details:\n");
    printf("ID\tName\t\t\tAge\tRoom Num\tDiagnosis\n");
    for (int i = 0; i < patientCount; i++) {
        patient p = patients[i];
        printf("%d\t%-20s\t%d\t%-10d\t%s\n", p.patient_id, p.name, p.age, p.room_number, p.diagnosis);
    }
}

void searchPatient() {
    int id, index = -1;

    printf("Enter Patient ID: ");
    scanf("%d", &id);
    index = idExists(patients, patientCount, id);

    if (index != -1) {
        printf("Patient Found - ID: %d, Name: %s, Age: %d, Room Num: %d, Diagnosis: %s\n",
            patients[index].patient_id, patients[index].name, patients[index].age,
            patients[index].room_number, patients[index].diagnosis);
    } else {
        printf("Patient not found.\n");
    }
}

void main() {
    //just for testing purposes
    //todo copy loop from Lab 5
    addPatient();
    addPatient();
    viewAllPatients();
    searchPatient();
}
