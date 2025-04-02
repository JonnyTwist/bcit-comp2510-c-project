#include <stdio.h>
#include "list.h"
#include "patient.h"
#include "dsm.h"


int savePatientsInfo(const char* filename, struct list* ps, struct list* dps)
{
    FILE* f = fopen(filename, "wb");

    if (f == NULL)
    {
        printf("Failed to save the %s file\n", filename);
        return 1;
    }

    size_t patientListSize = list_length(ps);
    fwrite(&patientListSize, sizeof(size_t), 1, f);
    for (size_t i = 0; i < patientListSize; i++)
    {
        patient p = *(patient *)list_get(ps, i);
        fwrite(&p, sizeof (patient), 1, f);
    }

    size_t dischargedListSize = list_length(dps);
    fwrite(&dischargedListSize, sizeof(size_t), 1, f);
    for (size_t i = 0; i < dischargedListSize; i++)
    {
        patient p = *(patient *)list_get(dps, i);
        fwrite(&p, sizeof (patient), 1, f);
    }

    fclose(f);

    return 0;
}
int saveDsmInfo(const char* filename, struct list* doctors)
{
    FILE* f = fopen(filename, "wb");

    if (f == NULL)
    {
        printf("Failed to save the %s file\n", filename);
        return 1;
    }

    size_t l = list_length(doctors);
    fwrite(&l, sizeof(size_t), 1, f);
    for (size_t i = 0; i < l; i++)
    {
        doctor d = *(doctor *)list_get(doctors, i);
        fwrite(&d, sizeof (doctor), 1, f);
    }
    for(size_t i = 0; i < DAYS_IN_WEEK; i++)
        for(size_t j = 0; j < SHIFTS_PER_DAY; j++)
        {
            fwrite(&schedule[i][j], sizeof (int), 1, f);
        }
    fclose(f);

    return 0;
}

int loadPatientsInfo(const char* filename, struct list** ps, struct list** dps)
{
    FILE* f = fopen(filename, "rb");

    if (f == NULL)
    {
        printf("Failed to open the %s file\n", filename);
        return 1;
    }

    list_clear(ps);
    list_clear(dps);

    size_t l;
    fread(&l, sizeof(size_t), 1, f);
    for (size_t i = 0; i < l; i++)
    {
        patient patient;
        fread(&patient, sizeof(patient), 1, f);
        list_push_front(ps, &patient, sizeof(patient));
    }

    size_t m;
    fread(&m, sizeof(size_t), 1, f);
    for (size_t i = 0; i < m; i++)
    {
        patient patient;
        fread(&patient, sizeof(patient), 1, f);
        list_push_front(dps, &patient, sizeof(patient));
    }

    fclose(f);
    patientCount = (int) l;
    dischargedPatientCount = (int) m;
    return 0;
}

int loadDsmInfo(const char* filename, struct list** doctors)
{
    FILE* f = fopen(filename, "rb");

    if (f == NULL)
    {
        printf("Failed to open the %s file\n", filename);
        return 1;
    }

    list_clear(doctors);

    size_t l;
    fread(&l, sizeof(size_t), 1, f);
    for (size_t i = 0; i < l; i++)
    {
        doctor doctor;
        fread(&doctor, sizeof(doctor), 1, f);
        list_push_front(doctors, &doctor, sizeof(doctor));
    }
    for(size_t i = 0; i < DAYS_IN_WEEK; i++)
    {
        for(size_t j = 0; j < SHIFTS_PER_DAY; j++)
        {
            fread(&schedule[i][j], sizeof (int), 1, f);
        }
    }
    fclose(f);
    doctorCount = (int) l;
    return 0;
}