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
void searchPatientByID();
void searchPatientByName();
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

/**
 * Checks if an ID exists inside a specified array.
 * @param arr The array to check the ID for.
 * @param size The expected size of the array.
 * @param id The ID we are looking for.
 * @return the index of the ID if it is found. Otherwise, return -1.
 */
int idExists(patient arr[], int size, int id) {
    for (int i = 0; i < size; i++) {
        if (arr[i].patient_id == id) {
            return i;
        }
    }
    return -1;
}

/**
 * Allows users to add new patients to the patients array.
 * Will request the user to input all the data required for a patient:
 * ID, Name, Age, Diagnosis, Room Number
 */
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

    printf("\n");

    //todo add a sentinel value(s)  that allows users to quit at any point
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

/**
 * Allows the user to view all the patients currently in the database.
 */
void viewAllPatients() {
    printf("\nAll patient details:\n");
    printf("ID\tName\t\t\tAge\tRoom Num\tDiagnosis\n");
    for (int i = 0; i < patientCount; i++) {
        patient p = patients[i];
        printf("%d\t%-20s\t%d\t%-10d\t%s\n", p.patient_id, p.name, p.age, p.room_number, p.diagnosis);
    }
}

/**
 * Allows users to choose how they want to search for a patient.
 * Options: By ID, By Name.
 */
void searchPatient() {
    int choice;

    printf("\nSearch by ID (1) or Name (2): ");
    scanf("%d", &choice);
    getchar();

    if (choice == 1) {
        searchPatientByID();
    } else if (choice == 2) {
        searchPatientByName();
    } else {
        printf("Invalid input!");
    }
}

/**
 * Allows users to search for a patient by the
 * patients ID.
 */
void searchPatientByID() {
    int id;
    int index;

    printf("Enter Patient ID: ");
    scanf("%d", &id);
    getchar();

    index = idExists(patients, patientCount, id);

    if (index != -1) {
        printf("Patient Found - ID: %d, Name: %s, Age: %d, Room Num: %d, Diagnosis: %s\n",
            patients[index].patient_id, patients[index].name, patients[index].age,
            patients[index].room_number, patients[index].diagnosis);
    } else {
        printf("Patient not found.\n");
    }
}

/**
 * Allows users to search for patients by the patients name.
 */
void searchPatientByName() {
    char name[100];
    int index = -1;

    printf("Enter the patients name: ");
    fgets(name, 100, stdin);

    //If the name is too long we will deny the search and empty the buffer.
    if (name[strlen(name) - 1] != '\n') {
        printf("Name too long! Maximum 99 characters allowed.\n");
        emptyRemainingInput();
    } else {
        //Remove the new line character from the end then search through the patients and print
        //all the names that match the search
        name[strcspn(name, "\n")] = 0;
        for (int i = 0; i < patientCount; i++) {
            if (strcmp(patients[i].name, name) == 0) {
                printf("Patient Found - ID: %d, Name: %s, Age: %d, Room Num: %d, Diagnosis: %s\n",
                       patients[i].patient_id, patients[i].name, patients[i].age,
                       patients[i].room_number, patients[i].diagnosis);
                //just to make sure it doesn't say no patient found
                index = i;
            }
        }
        if (index == -1) {
            printf("Patient not found.\n");
        }
    }
}



void main() {
    //just for testing purposes
    //todo copy loop from Lab 5 to wherever interface should be
    addPatient();
    addPatient();
    viewAllPatients();
    searchPatient();
}
