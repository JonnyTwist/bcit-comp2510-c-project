#include <stdio.h>
#include <stdlib.h>
#include "patient.h"
#include "dsm.h"

int patientCount = 0;
patient patients[50];
doctor doctors[10];
int doctorCount = 0;
int schedule[7][3];
void menu();

//todo initialize 2D array to -1
int main(void) {
    menu();

    /*
    for (int i = 0; i < 50; i++) {
        patient patient;
        patient.age = 10;
        patient.diagnosis[0] = 'a';
        patient.name[0] = 'b';
        patient.patient_id = 50 - i;
        patient.room_number = 205;

        addPatient1(patient);
    }

    addPatient();

    viewAllPatients();

    dischargePatient(1);
    dischargePatient(10);
    dischargePatient(20);
    dischargePatient(30);
    dischargePatient(40);

    printf("Patient count after: %d\n", patientCount);

    viewAllPatients();

    addPatient();
    */
    // viewAllPatients();
    //just for testing purposes
    //todo copy loop from Lab 5 to wherever interface should be
    /*addPatient();
    addPatient();
    viewAllPatients();
    searchPatient();*/
}

void menu(){
    int choice;
    do {
        printf("\nPatient Management System\n");
        printf("1. Add a New Patient\n");
        printf("2. View All Patients\n");
        printf("3. Search Patient by ID\n");
        printf("4. Discharge Patient\n");
        printf("5. Manage Doctor Schedule\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); //consume newline

        switch (choice) {
            case 1:
                addPatient();
                break;
            case 2:
                viewAllPatients();
                break;
            case 3:
                searchPatient();
                break;
            case 4:
                int id;
                printf("Patient ID to Discharge: ");
                scanf("%d", &id);
                dischargePatient(id);
                break;
            case 5:
                manageDoctorsMenu();
                break;
            case 6:
                printf("Exiting...\n");
                break;
            default:
                printf("invalid choice! Try again.\n");
        }

    } while (choice != 6);
}
