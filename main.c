/**
* Starting point of interacting with the hospital management system.
 *@author Nicolas Bertrand
 *@author Jonny Twist
 *@version 1.0
 */

#include <stdio.h>
#include "test.h"
#include "patient.h"
#include "dsm.h"
#include "list.h"
#include "file_m.h"

//todo remove
#include <time.h>

int patientCount = 0;
int dischargedPatientCount = 0;
//patient patients[50];
struct list* patientList;
struct list* dischargedPatientList;
struct list* doctor_list;
int doctorCount = 0;
int schedule[7][3];
void menu();
void readStoredData();
void backupData();
void restoreToBackups();

/**
 * Drives the program.
 * @return 0
 */
int main(void) {
    readStoredData();
    menu();
    backupData();
    //test();
    //test2();
    return 0;
}

/**
 * An interface for interacting with the patient.c
 * file or calling the dsm.
 */
void menu(){
    int choice;
    do {
        printf("\nPatient Management System\n");
        printf("1. Add a New Patient\n");
        printf("2. View All Patients\n");
        printf("3. Search For Patient\n");
        printf("4. Discharge Patient\n");
        printf("5. Manage Doctor Schedule\n");
        printf("6. View Discharged Patients\n");
        printf("7. Restore previous Backup Data\n");
        printf("8. Exit\n");
        //todo add options for new features
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
                viewAllDischargedPatients();
                break;
            case 7:
                restoreToBackups();
                break;
            case 8:
                printf("Exiting...\n");
                break;
            default:
                printf("invalid choice! Try again.\n");
        }

    } while (choice != 8);
}

void readStoredData()
{
    loadPatientsInfo("patientData.bin", &patientList, &dischargedPatientList);
    loadDsmInfo("doctorsData.bin", &doctor_list);
}

void backupData()
{
    saveDsmInfo("doctorsData.bin", doctor_list);
    savePatientsInfo("patientData.bin", patientList, dischargedPatientList);

    saveDsmInfo("doctorsDataBackup.bin", doctor_list);
    savePatientsInfo("patientDataBackup.bin", patientList, dischargedPatientList);
}

void restoreToBackups()
{
    loadPatientsInfo("patientDataBackup.bin", &patientList, &dischargedPatientList);
    loadDsmInfo("doctorsDataBackup.bin", &doctor_list);
}