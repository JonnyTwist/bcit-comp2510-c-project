// Doctor schedule management(dsm)
// Created by maxym on 31/01/2025.
//
typedef struct doctor_struct
{
    int doctor_id; // not negative
    char name[100];
} doctor;

doctor doctors[10];
int schedule[7][3];
void validateDoctorID(int doctor_id);
void validateDoctorName(int doctor_name);
void displaySchedule();
void addDocToTime();
// inside addDocToTime ask for valid data if invalid