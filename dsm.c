// Doctor schedule management(dsm)
// Created by maxym on 31/01/2025.
//

#include "dsm.h"
#include <stdio.h>
#include <string.h>

//todo this may conflict with patient.c similar method (diff arr)
int docIdExists(doctor arr[], int size, int id) {
    for (int i = 0; i < size; i++) {
        if (arr[i].doctor_id == id) {
            return i;
        }
    }
    return -1;
}

//todo this may conflict with patient.c same method
// maybe find way to merge function with other function
void docEmptyRemainingInput() {
    int c = '0';
    while (c != '\n') {
        c = getchar();
    }
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
    int valid;
    int doctorID;
    char doctorName[100];

    valid = 0;
    while (!valid) {
        printf("Enter the doctor's ID: ");
        scanf("%d", &doctorID);
        getchar();
        if (doctorID > MIN_ID && docIdExists(doctors, doctorCount, doctorID) == -1) {
            valid = 1;
        } else {
            printf("Invalid or duplicate ID!\n");
        }
    }

    valid = 0;
    while (!valid) {

        //assumes the input is valid right away
        valid = 1;

        printf("Enter the doctor's name: ");
        fgets(doctorName, 100, stdin);

        //ensures the input didnt overflow
        if (doctorName[strlen(doctorName) - 1] != '\n') {
            printf("Name too long! Maximum 99 characters allowed.\n");
            docEmptyRemainingInput();
            //sets valid to false so the loop will start again
            valid = 0;
        }

        // removes the newline character
        doctorName[strcspn(doctorName, "\n")] = 0;

        //Doesnt allow blank names
        //todo figure out how to check if it is just whitespace and deny those
        if (strlen(doctorName) == 0) {
            printf("Name cannot be blank!\n");
            //sets valid to false so the loop will start again
            valid = 0;
        }
    }

    doctorToAdd.doctor_id = doctorID;
    strcpy(doctorToAdd.name, doctorName);

    doctors[doctorCount] = doctorToAdd;
    doctorCount++;
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
                //todo I am thinking of setting empty time slots to -1
                schedule[i][j] = -1;
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
        printf("Monday Shift = 1\n");
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
        printf("6. Return\n");
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
                //todo allow clearing a time slot
                break;
            case 6:
                printf("Returning...\n");
                break;
            default:
                printf("invalid choice! Try again.\n");
        }

    } while (choice != 6);
}