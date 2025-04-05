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
#include "report.h"

//todo remove
#include <time.h>

int patientCount = 0;
int dischargedPatientCount = 0;
struct list* patientList;
struct list* dischargedPatientList;
struct list* doctor_list;
int doctorCount = 0;
int schedule[DAYS_IN_WEEK][SHIFTS_PER_DAY];
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
    //test3();

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
        printf("7. Restore Previous Backup Data\n");
        printf("8. Open Report Menu\n");
        printf("9. Exit\n");
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
                reportMenu();
                break;
            case 9:
                printf("Exiting...\n");
                break;
            default:
                printf("invalid choice! Try again.\n");
        }

    } while (choice != 9);
}

/**
 * Reads in the stored data when the program begins.
 */
void readStoredData()
{
    loadPatientsInfo(PATIENT_FILE, &patientList, &dischargedPatientList);
    loadDsmInfo(DOCTOR_FILE, &doctor_list);
}

/**
 * Saves all data when the program ends to both the frequent save files
 * and the backup save files
 */
void backupData()
{
    saveDsmInfo(DOCTOR_FILE, doctor_list);
    savePatientsInfo(PATIENT_FILE, patientList, dischargedPatientList);

    saveDsmInfo(DOCTOR_FILE_BACKUP, doctor_list);
    savePatientsInfo(PATIENT_FILE_BACKUP, patientList, dischargedPatientList);
}

/**
 * Overwrites all changes in the current session with the
 * backup save files effectively reverting to a previous save.
 */
void restoreToBackups()
{
    char input;

    printf("Are you sure you want to restore from backups? This will overwrite all unsaved changes. (y/n): ");
    scanf(" %c", &input);

    if (input == 'y' || input == 'Y')
    {
        loadPatientsInfo(PATIENT_FILE_BACKUP, &patientList, &dischargedPatientList);
        loadDsmInfo(DOCTOR_FILE_BACKUP, &doctor_list);
        printf("Backups restored successfully.\n");
    }
    else
    {
        printf("Restore cancelled.\n");
    }
    emptyRemainingInput();
}