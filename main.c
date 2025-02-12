#include <stdio.h>
#include <stdlib.h>
#include "patient.h"

int patientCount = 0;
patient patients[50];


int main(void) {

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

    viewAllPatients();
    //just for testing purposes
    //todo copy loop from Lab 5 to wherever interface should be
    /*addPatient();
    addPatient();
    viewAllPatients();
    searchPatient();*/


}