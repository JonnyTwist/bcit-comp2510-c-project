// Doctor schedule management(dsm)
// Created by maxym on 31/01/2025.
//

#include "patient.h"
#include "dsm.h"
#include <stdio.h>
#include <string.h>

/**
 * Searches through an array of doctors to see if a doctor with a specified ID exists.
 * @param arr the array of doctors.
 * @param size the size of the array.
 * @param id the ID we are looking for.
 * @return the index of the found ID, else -1
 */
int docIdExists(doctor arr[], int size, int id) {
    for (int i = 0; i < size; i++) {
        if (arr[i].doctor_id == id) {
            return i;
        }
    }
    return -1;
}

/**
 * Allows adding a doctor to the array of doctors.
 */
void addDoc(){

    if (doctorCount >= 10) {
        printf("Maximum number of doctors reached!\n");
        return;
    }

    doctor doctorToAdd;
    int doctorID;
    char doctorName[100];

    enterDocId(&doctorID);
    enterDocName(doctorName);

    doctorToAdd.doctor_id = doctorID;
    strcpy(doctorToAdd.name, doctorName);

    doctors[doctorCount] = doctorToAdd;
    doctorCount++;
}
/**
 * Store the doctor's id
 * @param id
 */
void enterDocId(int* id)
{
    int valid = 0;
    while (!valid) {
        printf("Enter the doctor's ID: ");
        scanf("%d", id);
        getchar();
        if (*id > MIN_ID && docIdExists(doctors, doctorCount, *id) == -1) {
            valid = 1;
        } else {
            printf("Invalid or duplicate ID!\n");
        }
    }
}
/**
 * Store the doctor's name
 * @param name
 */
void enterDocName(char* name)
{
    int valid = 0;
    while (!valid) {

        //assumes the input is valid right away
        valid = 1;

        printf("Enter the doctor's name: ");
        fgets(name, 100, stdin);

        //ensures the input didnt overflow
        if (name[strlen(name) - 1] != '\n') {
            printf("Name too long! Maximum 99 characters allowed.\n");
            emptyRemainingInput();
            //sets valid to false so the loop will start again
            valid = 0;
        }

        // removes the newline character
        name[strcspn(name, "\n")] = 0;

        //Doesnt allow blank names
        stringTrim(name);
        if (strlen(name) == 0) {
            printf("Name cannot be blank!\n");
            //sets valid to false so the loop will start again
            valid = 0;
        }
    }

}

/**
 * Displays all the doctors in the doctors array.
 */
void displayDoctors(){

    if (doctorCount == 0){
        printf("There are no Doctors!\n");
        return;
    }

    printf("\nAll Doctors:\n");
    printf("ID\tName\n");
    for (int i = 0; i < doctorCount; i++) {
        doctor d = doctors[i];
        printf("%d\t%s\n", d.doctor_id, d.name);
    }
}

/**
 * Removes a doctor from the array.
 * @param doctorID the doctor to remove
 * @return returns 0 if the removal was successful and 1 if the doctor ID does not exist.
 */
int removeDoctor(int doctorID){
    int index;
    index = docIdExists(doctors, doctorCount, doctorID);

    if (index == -1)
        return 1;

    for (int i = index; i < doctorCount - 1; i++)
        doctors[i] = doctors[i + 1];

    doctorCount--;

    return 0;
}

/**
 * Removes a doctor who was removed from the array from the schedule as well.
 * @param id The ID of the doctor to remove.
 */
void removeDoctorFromSchedule(int id){
    for (int i = 0; i < DAYS_IN_WEEK; i++){
        for (int j = 0; j < SHIFTS_PER_DAY; j++){
            if (id == schedule[i][j]){
                //Empty time slots store a doctor ID of 0
                schedule[i][j] = 0;
            }
        }
    }
}

/**
 * Allows adding a doctors ID to a timeslot on the schedule.
 */
void addDocToTimeSlot(){
    int docID;
    int weekDay;
    int shift;

    printf("Enter ID of doctor to be assigned: ");
    scanf("%d", &docID);

    if (docIdExists(doctors, doctorCount, docID) == -1) {
        printf("Doctor not found.\n");
        return;
    }

    do {
        printf("\nSunday = 0\n");
        printf("Monday = 1\n");
        printf("Tuesday = 2\n");
        printf("Wednesday = 3\n");
        printf("Thursday = 4\n");
        printf("Friday = 5\n");
        printf("Saturday = 6\n");
        printf("Cancel = -1\n");
        printf("Enter day of the week to assign doctor to: ");
        scanf("%d", &weekDay);

        if (weekDay == -1){
            printf("Canceling...");
            return;
        }

        if (weekDay < 0 || weekDay > 6){
            printf("Invalid week day. Try again.");
        }

    } while (weekDay < 0 || weekDay > 6);

    do {
        printf("\nMorning Shift = 0\n");
        printf("Afternoon Shift = 1\n");
        printf("Evening Shift = 2\n");
        printf("Cancel = -1\n");

        printf("Enter day of the week to assign doctor to: ");
        scanf("%d", &shift);

        if (shift == -1){
            printf("Canceling...");
            return;
        }

        if (shift < 0 || shift > 2){
            printf("Invalid Shift. Try again.\n");
        }
    } while (shift < 0 || shift > 2);

    schedule[weekDay][shift] = docID;
}

/**
 * Prints the doctors schedule for the week.
 */
void printSchedule(){
    printTableHeader();
    for (int j = 0; j < SHIFTS_PER_DAY; j++){
        switch (j){
            case 0:
                printf("%-12s", "MORNING");
                break;
            case 1:
                printf("%-12s", "AFTERNOON");
                break;
            case 2:
                printf("%-12s", "EVENING");
                break;
            default:
                //big message to tell me if I messed up
                printf("HOW DID WE GET HERE!!!!");
        }

        for (int i = 0; i < DAYS_IN_WEEK; i ++){
            if (schedule[i][j] == 0){
                printf("%-15s", "Empty");
            }
            else{
                int index;
                int id = schedule[i][j];
                index = docIdExists(doctors, doctorCount, id);
                char doctorName[100];

                strcpy(doctorName, doctors[index].name);
                truncateStr(doctorName, TABLE_FORMATTED_LENGTH);
                printf("%-15s", doctorName);
            }
        }
        printf("\n");
    }

}

/**
 * Truncates a string to a specified length.
 * Used to truncate doctor names that are too long for table display.
 * @param str the name to be truncated
 * @param newLength the new length of the String
 */
void truncateStr(char str[], int newLength) {
    if (newLength < strlen(str)) {
        str[newLength ] = '\0';
        str[newLength -1] = '.';
        str[newLength -2] = '.';
        str[newLength -3] = '.';
    }
}

/**
 * Prints the header of the doctors schedule table.
 */
void printTableHeader() {
    printf("%-12s", "");
    printf("%-15s", "SUNDAY");
    printf("%-15s", "MONDAY");
    printf("%-15s", "TUESDAY");
    printf("%-15s", "WEDNESDAY");
    printf("%-15s", "THURSDAY");
    printf("%-15s", "FRIDAY");
    printf("%-15s", "SATURDAY");
    printf("\n");
}

/**
 * Clears a specified time slot of the schedule.
 */
void clearTimeSlot()
{
    int weekDay;
    int shift;

    do {
        printf("\nSunday = 0\n");
        printf("Monday = 1\n");
        printf("Tuesday = 2\n");
        printf("Wednesday = 3\n");
        printf("Thursday = 4\n");
        printf("Friday = 5\n");
        printf("Saturday = 6\n");
        printf("Cancel = -1\n");
        printf("Enter day of the week to clear: ");
        scanf("%d", &weekDay);

        if (weekDay == -1){
            printf("Canceling...");
            return;
        }

        if (weekDay < 0 || weekDay > 6){
            printf("Invalid week day. Try again.");
        }

    } while (weekDay < 0 || weekDay > 6);

    do {
        printf("\nMorning Shift = 0\n");
        printf("Afternoon Shift = 1\n");
        printf("Evening Shift = 2\n");
        printf("Cancel = -1\n");

        printf("Enter day of the week to clear: ");
        scanf("%d", &shift);

        if (shift == -1){
            printf("Canceling...");
            return;
        }

        if (shift < 0 || shift > 2){
            printf("Invalid Shift. Try again.\n");
        }
    } while (shift < 0 || shift > 2);

    schedule[weekDay][shift] = 0;
}

/**
 * Displays a text based menu and takes in user inputer related to
 * the doctor management system.
 */
void manageDoctorsMenu(){
    int choice;
    do {
        printf("\nDoctor Management System\n");
        printf("1. Add a New Doctor\n");
        printf("2. View All Doctors\n");
        printf("3. Remove Doctor\n");
        printf("4. Add Doctor to Time\n");
        printf("5. Clear Time Slot\n");
        printf("6. Display Schedule\n");
        printf("7. Return\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); //consume newline

        switch (choice) {
            case 1:
                addDoc();
                break;
            case 2:
                displayDoctors();
                break;
            case 3:
                int id;
                printf("Doctor ID to remove: ");
                scanf("%d", &id);
                removeDoctor(id);
                removeDoctorFromSchedule(id);
                break;
            case 4:
                addDocToTimeSlot();
                break;
            case 5:
                clearTimeSlot();
                break;
            case 6:
                printSchedule();
                break;
            case 7:
                printf("Returning...\n");
                break;
            default:
                printf("invalid choice! Try again.\n");
        }

    } while (choice != 7);
}