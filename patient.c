// Patient
// Created by maxym on 31/01/2025.
//

#include <string.h>
#include <stdio.h>

//todo ask if Diagnosis is intentionally capitalized
typedef struct patient_struct
{
    int patient_id;
    char name[100];
    int age;
    char* Diagnosis;
    int room_number;
} patient;

patient patients[50];
int patientCount = 0;

void emptyRemainingInput();
void addPatient();
// void dischargePatient(int patient_id);
// void viewAllPatientsRecord();
// patient searchPatient(int patient_id);
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

void addPatient() {

    if (patientCount >= 50) {
        printf("Maximum number of patients reached!\n");
        return;
    }

    patient patientToAdd;
    int patientID = -10;
    char patientName[100];
    int patientAge = -10;
    char* patientDiagnosis;
    int patientRoomNumber;

    int valid = 0;

    //todo add a sentinel value(s) that allows users to quit at any point
    while (patientID < 0) {
        printf("Enter the patient ID: ");
        scanf("%d", &patientID);
        getchar();
    }

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

    //todo get age, diagnosis, and roomNum then put everything in a struct and put the struct in the array

}

void main() {
    addPatient();
}
