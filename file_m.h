/**
 * Allows the file management (file_m) to be used in other files
 * @author Nicolas Bertrand
 * @author Jonny Twist
 * @version 1.0
 */


#ifndef BCIT_COMP2510_C_PROJECT_FILE_M_H
#define BCIT_COMP2510_C_PROJECT_FILE_M_H
#include "list.h"
#include <time.h>

#define IN_DAY 1
#define IN_WEEK 2
#define IN_MONTH 3

int savePatientsInfo(const char* filename, struct list* patients, struct list* dischargedPatients);
int saveDsmInfo(const char* filename, struct list* doctors);
int loadPatientsInfo(const char* filename, struct list** patients, struct list** dischargedPatients);
int loadDsmInfo(const char* filename, struct list** doctors);
int saveReportDocUtil(const char* filename, struct list* doc_report);
int saveReportRoom(const char* filename, struct list* room_report);
int saveReportSpecific(const char* filename, const char* message);
int refreshBackup();
int restoreBackup();
int displayFiles();

#endif //BCIT_COMP2510_C_PROJECT_FILE_M_H
