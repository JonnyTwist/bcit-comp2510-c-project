/**
 * Gives function to patient management.
 *@author Nicolas Bertrand
 *@author Jonny Twist
 *@version 1.0
 */

#include "patient.h"
#include <string.h>
#include <stdio.h>

#include "list.h"

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
 * @param patient_list the list to check for the ID.
 * @param size The expected size of the array.
 * @param id The ID we are looking for.
 * @return the index of the ID if it is found. Otherwise, return -1.
 */
int idExists(struct list* patient_list, int size, int id) {
    for (int i = 0; i < size; i++) {
        patient p = *(patient*)list_get(patient_list, i);
        if (p.patient_id == id) {
            return i;
        }
    }
    return ID_NOT_FOUND;
}

/**
 * Allows users to add new patients to the patients array.
 * Will request the user to input all the data required for a patient:
 * ID, Name, Age, Diagnosis, Room Number
 */
void addPatient() {

    if (patientCount >= 50) {
        printf("Maximum number of patients reached!\n");
        return;
    }

    //todo clarify this (see if -10 is removable)
    patient patientToAdd;
    int patientID = -10;
    char patientName[MAX_STRING_LENGTH];
    int patientAge = -10;
    char patientDiagnosis[MAX_STRING_LENGTH];
    int patientRoomNumber = -10;

    printf("\n");

    enterPatientId(&patientID);
    enterPatientName(patientName);
    enterPatientAge(&patientAge);
    enterPatientDiagnosis(patientDiagnosis);
    enterPatientRoom(&patientRoomNumber);

    patientToAdd.patient_id = patientID;
    strcpy(patientToAdd.name, patientName);
    patientToAdd.age = patientAge;
    strcpy(patientToAdd.diagnosis, patientDiagnosis);
    patientToAdd.room_number = patientRoomNumber;
    patientToAdd.date_admitted = getCurrentTime();
    patientToAdd.date_discharged = NULL;

    list_push_front(patientList, &patientToAdd, sizeof(patient));
    patientCount++;

    //todo save to file
}

/**
 * Stores the patient's id
 * @param id where the patient's id will be stored
 */
void enterPatientId(int* id)
{
    int valid = 0;
    while (!valid) {
        printf("Enter the patient ID: ");
        scanf("%d", id);
        getchar();
        if (*id > MIN_ID && idExists(patients, patientCount, *id) == ID_NOT_FOUND) {
            valid = 1;
        } else {
            printf("Invalid or duplicate ID!\n");
        }
    }
}
/**
 * Store the patient's id
 * @param name where the patient's id will be stored
 */
void enterPatientName(char* name)
{
    int valid = 0;
    while (!valid) {

        printf("Enter the patients name: ");
        fgets(name, MAX_STRING_LENGTH, stdin);

        valid = validateString(name);

        if (!valid){
            printf("Patient name must be less than %d characters and not blank\n", MAX_STRING_LENGTH);
        }
    }
}
/**
 * Store the patient's name
 * @param age where the patient's age will be stored
 */
void enterPatientAge(int* age)
{
    do {
        printf("Enter the patients age: ");
        scanf("%d", age);
        getchar();
        if (*age < MIN_AGE) {
            printf("Patient age must be an int and not be negative!\n");
        }
    }
    while (*age < MIN_AGE);
}
/**
 * Store the patient's age
 * @param diagnosis where the patient's age will be stored
 */
void enterPatientDiagnosis(char* diagnosis)
{
    int valid = 0;
    while (!valid) {

        //assumes the input is valid right away
        valid = 1;

        printf("Enter the patients diagnosis: ");
        fgets(diagnosis, MAX_STRING_LENGTH, stdin);

        valid = validateString(diagnosis);

        if (!valid){
            printf("Diagnosis must be less than %d characters and not blank\n", MAX_STRING_LENGTH);
        }
    }
}
/**
 * Store the room number
 * @param roomNumber where the room number will be stored
 */
void enterPatientRoom(int* roomNumber)
{
    do {
        printf("Enter the patients room number: ");
        scanf("%d", roomNumber);
        getchar();
        if (*roomNumber < MIN_ROOM_NUM) {
            printf("Room number must an int and not be negative!\n");
        }
    }
    while (*roomNumber < MIN_ROOM_NUM);
}

/**
 * Removes useless spaces of a string
 * @param string the string to be trimmed
 */
void stringTrim(char* string)
{
    char* end = string;

    //removes the left spaces
    char* cpy = string;
    while (*cpy == ' ')
        cpy++;
    while (*cpy)
    {
        *string = *cpy;
        cpy++;
        string++;
    }
    *string = 0;

    //removes the right spaces
    end += strlen(end) - 1;
    while (*end == ' ')
        end--;
    *(end+1) = 0;
}
/**
 * Validates the patients name and diagnosis since those were similar.
 * @param string the string to be validated.
 * @return 0 if it is not valid and 1 if it is valid.
 */
int validateString(char string[MAX_STRING_LENGTH]){
    //ensures the string ends with a newline character / no overflow
    if (string[strlen(string) - 1] != '\n') {
        emptyRemainingInput();
        return 0;
    }

    // removes the newline character
    string[strcspn(string, "\n")] = 0;

    //Doesnt allow blank strings
    if (*string == 0) { //return true if the length == 0, false if not
        return 0;
    }

    //Checks if a string only has white spaces
    stringTrim(string);
    if (strlen(string) == 0) {
        return 0;
    }

    return 1;
}

/**
 * Gets the current date time.
 * @return the current time.
 */
struct tm* getCurrentTime()
{
    time_t now = time(NULL);
    struct tm *local = localtime(&now);
    return local;
}

/**
 * Allows the user to view all the patients currently in the database.
 */
void viewAllPatients() {

    if (patientCount == 0){
        printf("There are no Patients!\n");
        return;
    }

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

    if (index != ID_NOT_FOUND) {
        printf("Patient Found - ");
        displayPatient(patients[index]);
    } else {
        printf("Patient not found.\n");
    }
}

/**
 * Allows users to search for patients by the patients name.
 */
void searchPatientByName() {
    char name[MAX_STRING_LENGTH];
    int index = ID_NOT_FOUND;

    printf("Enter the patients name: ");
    fgets(name, MAX_STRING_LENGTH, stdin);

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
                printf("Patient Found - ");
                       // "ID: %d, Name: %s, Age: %d, Room Num: %d, Diagnosis: %s\n",
                       // patients[i].patient_id, patients[i].name, patients[i].age,
                       // patients[i].room_number, patients[i].diagnosis);
                displayPatient(patients[i]);
                //just to make sure it doesn't say no patient found
                index = i;
            }
        }
        if (index == ID_NOT_FOUND) {
            printf("Patient not found.\n");
        }
    }
}

/**
 * @param patientID is the patients ID to discharge.
 * @return returns 0 if the patient has been discharged successfully, else 1
 * */
int dischargePatient(int patientID) {
    int index;
    index = idExists(patients, patientCount, patientID);

    if (index == ID_NOT_FOUND)
        return 1;

    for (int i = index; i < patientCount - 1; i++)
        patients[i] = patients[i + 1];

    patientCount--;

    return 0;
}

/**
 * Displays a patients details
 * @param patient the patient to be displayed.
 */
void displayPatient(patient patient) {
    printf("ID: %d\t Name: %s\t Age: %d\t Room Num: %d\t Diagnosis: %s\n",
            patient.patient_id, patient.name, patient.age,
            patient.room_number, patient.diagnosis);
}


