// Doctor schedule management(dsm)
// Created by maxym on 31/01/2025.
//
typedef struct doctor_struct
{
    int doctor_id; // not negative
    char name[100];
} doctor;

#include <stdio.h>
#include <string.h>
#define MIN_ID 0

doctor doctors[10];
int doctorCount = 0;
int schedule[7][3];
void docEmptyRemainingInput();
void addDoc();
void manageDoctorsMenu();
void validateDoctorID(int doctor_id);
void validateDoctorName(int doctor_name);
void displaySchedule();
void addDocToTime();
// inside addDocToTime ask for valid data if invalid

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

void addDoc(){

    if (doctorCount >= 10) {
        printf("Maximum number of doctors reached!\n");
        return;
    }

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
}

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
                //todo allow viewing doctors
                break;
            case 3:
                //todo allow remove doctor
                break;
            case 4:
                //todo allow adding doc to time
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