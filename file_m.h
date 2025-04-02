#include "list.h"
#ifndef BCIT_COMP2510_C_PROJECT_FILE_M_H
#define BCIT_COMP2510_C_PROJECT_FILE_M_H

int savePatientsInfo(const char* filename, struct list* patients, struct list* dischargedPatients);
int saveDsmInfo(const char* filename, struct list* doctors);
int loadPatientsInfo(const char* filename, struct list** patients, struct list** dischargedPatients);
int loadDsmInfo(const char* filename, struct list** doctors);
int refreshBackup();
int restoreBackup();
int displayFiles();

#endif //BCIT_COMP2510_C_PROJECT_FILE_M_H
