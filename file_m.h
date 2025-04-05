#include "list.h"
#ifndef BCIT_COMP2510_C_PROJECT_FILE_M_H
#define BCIT_COMP2510_C_PROJECT_FILE_M_H

#include <time.h>
#define IN_DAY 1
#define IN_WEEK 2
#define IN_MONTH 3

int savePatientsInfo(const char* filename, struct list* patients, struct list* dischargedPatients);
int saveDsmInfo(const char* filename, struct list* doctors);
int loadPatientsInfo(const char* filename, struct list** patients, struct list** dischargedPatients);
int loadDsmInfo(const char* filename, struct list** doctors);
int saveReportDocUtil(const char* filename, struct list* doc_report);
int saveReportDischarged(const char* filename, int nb_discharged);
int saveReportAdmitted(const char* filename, int nb_admitted, int option);
int saveReportRoom(const char* filename, struct list* room_report);
int refreshBackup();
int restoreBackup();
int displayFiles();

#endif //BCIT_COMP2510_C_PROJECT_FILE_M_H
