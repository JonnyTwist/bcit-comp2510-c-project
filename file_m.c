#include <stdio.h>
#include "list.h"
#include "patient.h"
#include "dsm.h"

int savePatientsInfo(const char* filename, struct list* ps)
{
    FILE* f = fopen(filename, "wb");
    size_t l = list_length(ps);
    fwrite(&l, sizeof(size_t), 1, f);
    for (size_t i = 0; i < l; i++)
    {
        patient p = *(patient *)list_get(ps, i);
        fwrite(&p, sizeof (patient), 1, f);
    }
    fclose(f);


    return 0;
}
int saveDsmInfo(const char* filename, struct list* doctors)
{
    FILE* f = fopen(filename, "wb");
    //fwrite(Str, Size, Count, File);
    return 0;
}
int loadPatientsInfo(const char* filename, struct list** ps)
{
    FILE* f = fopen(filename, "rb");
    size_t l;
    fread(&l, sizeof(size_t), 1, f);
    for (size_t i = 0; i < l; i++)
    {
        patient patient;
        fread(&patient, sizeof(patient), 1, f);
        list_push_front(ps, &patient, sizeof(patient));
    }

    fclose(f);
    return 0;
}
int loadDsmInfo(const char* filename, struct list** doctors)
{
    FILE* f = fopen(filename, "rb");
    //fseek(File, pos, SEEK_SET);
    //fread(DstBuff, EltSize, Count, File);
    return 0;
}