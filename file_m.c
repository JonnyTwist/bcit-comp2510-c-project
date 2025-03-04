#include <stdio.h>

int savePatientsInfo(const char* filename, struct list* patients)
{
    FILE* f = fopen(filename, "wb");
    //fwrite(Str, Size, Count, File);

    return 0;
}
int saveDsmInfo(const char* filename, struct list* doctors, int** schedule)
{
    FILE* f = fopen(filename, "wb");
    //fwrite(Str, Size, Count, File);
    return 0;
}
int loadPatientsInfo(const char* filename, struct list* patients, int *patientCount)
{
    FILE* f = fopen(filename, "rb");
    //fseek(File, pos, SEEK_SET);
    //fread(DstBuff, EltSize, Count, File);
    return 0;
}
int loadDsmInfo(const char* filename, struct list* doctors, int** schedule, int *doctorCount)
{
    FILE* f = fopen(filename, "rb");
    //fseek(File, pos, SEEK_SET);
    //fread(DstBuff, EltSize, Count, File);
    return 0;
}