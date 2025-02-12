// User interface(ui)
// Created by maxym on 31/01/2025.
//


#include <stdio.h>
#include <stdlib.h>
#include "patient.h"

void displayPatient(patient patient) {
    printf("ID: %d\t Name: %s\t Age: %d\t Room Num: %d\t Diagnosis: %s\n",
            patient.patient_id, patient.name, patient.age,
            patient.room_number, patient.diagnosis);
}

