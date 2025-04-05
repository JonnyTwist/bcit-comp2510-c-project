#include <stdio.h>
#include "list.h"
#include "patient.h"
#include "dsm.h"
#include <time.h>
#include "report.h"

/**
 * Saves the patient information and discharged patient information to a file.
 * @param filename The name of the file to save the data to.
 * @param pList Pointer to the list of patients.
 * @param dList Pointer to the list of discharged patients.
 * @return 0 on success, 1 if the file could not be opened.
 */
int savePatientsInfo(const char* filename, struct list* pList, struct list* dList)
{
    FILE* file = fopen(filename, "wb");

    if (file == NULL)
    {
        printf("Failed to save the %s file\n", filename);
        return 1;
    }

    size_t pListLength = list_length(pList);
    fwrite(&pListLength, sizeof(size_t), 1, file);
    for (size_t i = 0; i < pListLength; i++)
    {
        patient p = *(patient *)list_get(pList, i);
        fwrite(&p, sizeof (patient), 1, file);
    }

    size_t dListLength = list_length(dList);
    fwrite(&dListLength, sizeof(size_t), 1, file);
    for (size_t i = 0; i < dListLength; i++)
    {
        patient p = *(patient *)list_get(dList, i);
        fwrite(&p, sizeof (patient), 1, file);
    }

    fclose(file);

    return 0;
}

/**
 * Saves the doctor information and schedule to a file.
 * @param filename The name of the file to save the data to.
 * @param doctors Pointer to the list of doctors.
 * @return 0 on success, 1 if the file could not be opened.
 */
int saveDsmInfo(const char* filename, struct list* doctors)
{
    FILE* file = fopen(filename, "wb");

    if (file == NULL)
    {
        printf("Failed to save the %s file\n", filename);
        return 1;
    }

    size_t doctorsLength = list_length(doctors);
    fwrite(&doctorsLength, sizeof(size_t), 1, file);
    for (size_t i = 0; i < doctorsLength; i++)
    {
        doctor d = *(doctor *)list_get(doctors, i);
        fwrite(&d, sizeof (doctor), 1, file);
    }
    for(size_t i = 0; i < DAYS_IN_WEEK; i++)
    {
        for(size_t j = 0; j < SHIFTS_PER_DAY; j++)
        {
            fwrite(&schedule[i][j], sizeof (int), 1, file);
        }
    }
    fclose(file);

    return 0;
}

/**
 * Loads patient information and discharged patient information from a file.
 * @param filename The name of the file to load the data from.
 * @param pList Pointer to the pointer of the list of patients.
 * @param dList Pointer to the pointer of the list of discharged patients.
 * @return 0 on success, 1 if the file could not be opened.
 */
int loadPatientsInfo(const char* filename, struct list** pList, struct list** dList)
{
    FILE* file = fopen(filename, "rb");

    if (file == NULL)
    {
        printf("Failed to open the %s file\n", filename);
        return 1;
    }

    list_clear(pList);
    list_clear(dList);

    size_t pListLength;
    fread(&pListLength, sizeof(size_t), 1, file);
    for (size_t i = 0; i < pListLength; i++)
    {
        patient patient;
        fread(&patient, sizeof(patient), 1, file);
        list_push_front(pList, &patient, sizeof(patient));
    }

    size_t dListLength;
    fread(&dListLength, sizeof(size_t), 1, file);
    for (size_t i = 0; i < dListLength; i++)
    {
        patient patient;
        fread(&patient, sizeof(patient), 1, file);
        list_push_front(dList, &patient, sizeof(patient));
    }

    fclose(file);
    patientCount = (int) pListLength;
    dischargedPatientCount = (int) dListLength;
    return 0;
}

/**
 * Loads doctor information and schedule from a file.
 * @param filename The name of the file to load the data from.
 * @param doctors Pointer to the pointer of the list of doctors.
 * @return 0 on success, 1 if the file could not be opened.
 */
int loadDsmInfo(const char* filename, struct list** doctors)
{
    FILE* file = fopen(filename, "rb");

    if (file == NULL)
    {
        printf("Failed to open the %s file\n", filename);
        return 1;
    }

    list_clear(doctors);

    size_t doctorsLength;
    fread(&doctorsLength, sizeof(size_t), 1, file);
    for (size_t i = 0; i < doctorsLength; i++)
    {
        doctor doctor;
        fread(&doctor, sizeof(doctor), 1, file);
        list_push_front(doctors, &doctor, sizeof(doctor));
    }

    for(size_t i = 0; i < DAYS_IN_WEEK; i++)
    {
        for(size_t j = 0; j < SHIFTS_PER_DAY; j++)
        {
            fread(&schedule[i][j], sizeof (int), 1, file);
        }
    }

    fclose(file);
    doctorCount = (int) doctorsLength;
    return 0;
}

int saveReportDocUtil(const char* filename, struct list* doc_report)
{
    FILE* file = fopen(filename, "w");

    if (file == NULL)
    {
        printf("Failed to open the %s file\n", filename);
        return 1;
    }

    fprintf(file, "Doctor utilisation:\n");
    while (doc_report)
    {
        Key_value kv = *(Key_value*)doc_report->elt;
        int index = docIdExists(doctor_list, (int)list_length(doctor_list),kv.key);
        printf("%d\n", index);

        if (index != -1)
        {
            doctor d = *(doctor*)list_get(doctor_list, index);

            fprintf(file,"Doctor: %-20s Number of shifts: %d\n", d.name, kv.value);
        }

        doc_report = doc_report->next;
    }

    fclose(file);

    return 0;
}

int saveReportRoom(const char* filename, struct list* room_report)
{
    FILE* file = fopen(filename, "w");

    if (file == NULL)
    {
        printf("Failed to open the %s file\n", filename);
        return 1;
    }

    fprintf(file, "Room utilisation:\n");
    while (room_report)
    {
        Key_value kv = *(Key_value*)room_report->elt;

        fprintf(file,"Room: %-12d Number of patients: %d\n", kv.key, kv.value);

        room_report = room_report->next;
    }

    fclose(file);

    return 0;
}