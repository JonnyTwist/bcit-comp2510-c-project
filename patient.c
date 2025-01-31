// Patient
// Created by maxym on 31/01/2025.
//
typedef struct patient_struct
{
    int patient_id;
    char name[100];
    int age;
    char* Diagnosis;
    int room_number;
} patient;

patient patients[50];

void addPatient(patient patient);
void dischargePatient(int patient_id);
void viewAllPatientsRecord();
patient searchPatient(int patient_id);
patient searchPatient(const char* patient_name);
