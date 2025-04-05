#include "report.h"
#include "patient.h"
#include "dsm.h"
#include <string.h>
#include <stdlib.h>
#include "dsm.h"
#include "file_m.h"
#include "string.h"
#include "ctype.h"

int compTm(struct tm l, struct tm r);
int contains_key(int key, struct list* kv_list);
int get_value(int key, struct list* kv_list, int* value);
void put(Key_value kv, struct list** kv_list);

void room_report(struct list* patient_list, struct list** room_report)
{
    while (patient_list)
    {
        patient p = *(patient*)patient_list->elt;
        if (contains_key(p.room_number, *room_report))
        {
            int value;
            get_value(p.room_number, *room_report, &value);
            Key_value kv = {p.room_number, value + 1};
            put(kv, room_report);
        }
        else
        {
            Key_value kv = {p.room_number, 1};
            put(kv, room_report);
        }
        patient_list = patient_list->next;
    }
}

void doc_report(struct list** doc_report)
{
    for (int i = 0; i < DAYS_IN_WEEK; i++)
        for (int j = 0; j < SHIFTS_PER_DAY; j++)
        {
            if (contains_key(schedule[i][j], *doc_report))
            {
                int value;
                get_value(schedule[i][j], *doc_report, &value);
                Key_value kv = {schedule[i][j], value + 1};
                put(kv, doc_report);
            }
            else
            {
                Key_value kv = {schedule[i][j], 1};
                put(kv, doc_report);
            }
        }
}

void put(Key_value kv, struct list** kv_list)
{
    if (kv_list == NULL)
    {
        return;
    }

    if (!contains_key(kv.key, *kv_list))
    {
        list_push_front(kv_list, &kv, sizeof(Key_value));
    }
    else
    {
        struct list* cpy = *kv_list;
        int set = 0;
        while (cpy && set == 0)
        {
            Key_value elt = *(Key_value*)cpy->elt;
            if (kv.key == elt.key)
            {
                elt.value = kv.value;
                memcpy(cpy->elt, &elt, sizeof(Key_value));
                set = 1;
            }

            cpy = cpy->next;
        }
    }
}

int contains_key(int key, struct list* kv_list)
{
    int res = 0;
    while(res == 0 && kv_list)
    {
        Key_value kv= *(Key_value*)kv_list->elt;
        res = kv.key == key;

        kv_list = kv_list->next;
    }
    return res;
}

/*
 * returns 1 if the has been found else returns 0
 * @param key
 * @param kv_list
 * @param value where the value will be stored
 * @return
 */
int get_value(int key, struct list* kv_list, int* value)
{
    int res = 0;
    while(kv_list && res == 0)
    {
        Key_value elt = *(Key_value*)kv_list->elt;
        if (elt.key == key)
        {
            res = 1;
            *value = elt.value;
        }

        kv_list = kv_list->next;
    }
    return res;
}

/**
 * Counts the number of patient discharged between two dates
 * left tm is smaller than right tm
 * @param patient_list the patients to be counted
 * @param left the first date (small one)
 * @param right the second date (big one)
 * @return the number of patient discharged between left and right
 */
int discharged_in_interval(struct list* patient_list, struct tm left, struct tm right)
{
    int count = 0;
    while(patient_list)
    {
        patient p = *(patient*)patient_list->elt;
        struct tm p_time;
        p_time.tm_mday = p.date_discharged;
        p_time.tm_mon = p.month_discharged - 1;
        p_time.tm_year = p.year_discharged - 1900;

        int dl = compTm(left,p_time);
        int dr = compTm(p_time, right);

        count += dl <= 0 && dr <= 0;

        patient_list = patient_list->next;
    }
    return count;
}

/**
 * Counts the number of patient admitted between two dates
 * left tm is smaller than right tm
 * @param patient_list the patients to be counted
 * @param left the first date (small one)
 * @param right the second date (big one)
 * @return the number of patient admitted between left and right
 */
int admitted_in_interval(struct list* patient_list, struct tm left, struct tm right)
{
    int count = 0;
    while(patient_list)
    {
        patient p = *(patient*)patient_list->elt;
        struct tm p_time;
        p_time.tm_mday = p.date_admitted;
        p_time.tm_mon = p.month_admitted - 1;
        p_time.tm_year = p.year_admitted - 1900;

        printf("%d-%d-%d\n", p_time.tm_mday, p_time.tm_mon, p_time.tm_year);

        int dl = compTm(left,p_time);
        int dr = compTm(p_time, right);

        count += dl <= 0 && dr <= 0;

        patient_list = patient_list->next;
    }
    return count;
}

int compTm(struct tm l, struct tm r)
{
    int d_diff = l.tm_mday - r.tm_mday;
    int m_diff = l.tm_mon - r.tm_mon;
    int y_diff = l.tm_year - r.tm_year;

    printf("d_diff: %d, m_diff: %d, y_diff: %d\n", d_diff, m_diff, y_diff);

    return y_diff*10000 + m_diff*100 + d_diff;
}

void request_month(int option)
{
    int year;
    int month;

    //todo fix this - it is failing to parse the string
    printf("Enter a date in YYYY-MM format: ");
    if (scanf("%d-%d", &year, &month) == 2)
    {
        char message[100];
        message[0] = 0;

        int returnedCount;

        struct tm leftTime = createTime(1, month, year);
        struct tm rightTime = createTime(1, month + 1, year);

        returnedCount = admitted_in_interval(patientList, leftTime, rightTime);
        createMessage(message, option, leftTime, rightTime, returnedCount);
        saveReportSpecific("admittedReport.txt", message);
    }
    else
    {
        printf("Error parsing date string.\n");
        emptyRemainingInput();
    }

}

void createMessage(char* message, int option, struct tm leftTime, struct tm rightTime, int count)
{
    if (option == 0)
    {
        //discharged patients message
        sprintf(message, "There were %d patients discharged on %d-%d-%d",
            count, leftTime.tm_year + 1900, leftTime.tm_mon + 1, leftTime.tm_mday);
    }
    else if (option == 1)
    {
        //month message
        sprintf(message, "There were %d patients admitted between %d-%d-%d and %d-%d-%d",
            count, leftTime.tm_year + 1900, leftTime.tm_mon + 1, leftTime.tm_mday,
            rightTime.tm_year + 1900, rightTime.tm_mon + 1, rightTime.tm_mday);

    }
    else if (option == 2)
    {
        //week message
        sprintf(message, "There were %d patients admitted between %d-%d-%d and %d-%d-%d",
            count, leftTime.tm_year + 1900, leftTime.tm_mon + 1, leftTime.tm_mday,
            rightTime.tm_year + 1900, rightTime.tm_mon + 1, rightTime.tm_mday);
    }
    else if (option == 3)
    {
        //day message
        sprintf(message, "There were %d patients admitted on %d-%d-%d",
            count, leftTime.tm_year + 1900, leftTime.tm_mon + 1, leftTime.tm_mday);
    }
    else
    {
        printf("UNREACHABLE CODE REACHED!!!");
    }
}

void request_day(int intake, int option)
{
    int year;
    int month;
    int day;

    //todo fix this - it is failing to parse the string
    printf("Enter a date in YYYY-MM-DD format: ");
    if (scanf("%d-%d-%d", &year, &month, &day) == 3)
    {
        char message[100];
        message[0] = 0;

        int returnedCount;

        struct tm leftTime = createTime(day, month, year);

        if (intake == 1)
        {
            //if intake is 1 we are generating a discharged patient report
            //todo call something like admitted_in_interval
            returnedCount = discharged_in_interval(dischargedPatientList, leftTime, leftTime);
            createMessage(message, option, leftTime, leftTime, returnedCount);
            saveReportSpecific("dischargedReport.txt", message);
        }
        else if (intake == 2)
        {
            //if intake is not 1 we are generating a patient admitted report
            // based on either week or day according to option (2 = week, 3 = day)
            if (option == 2)
            {
                // Convert to time_t
                time_t date_time = mktime(&leftTime);

                // Add one week (7 days * 24 hours * 60 minutes * 60 seconds)
                date_time += 7 * 24 * 60 * 60;

                // Convert back to struct tm
                struct tm *rightTime = localtime(&date_time);

                //todo catch the return value and print it
                returnedCount = admitted_in_interval(patientList, leftTime, *rightTime);
                createMessage(message, option, leftTime, *rightTime, returnedCount);
                saveReportSpecific("admittedReport.txt", message);
            }
            else if (option == 3)
            {
                //todo catch the number of stuff admitted patients and print that to file
                returnedCount = admitted_in_interval(patientList, leftTime, leftTime);
                createMessage(message, option, leftTime, leftTime, returnedCount);
                saveReportSpecific("admittedReport.txt", message);
            }
        }
        else
        {
            printf("ERROR: Reached unreachable code!!");
        }
    }
    else
    {
        printf("Error parsing date string.\n");
        emptyRemainingInput();
    }
}

struct tm createTime(int date, int month, int year)
{
    struct tm newTime = {0};

    newTime.tm_mday = date;
    newTime.tm_mon = month - 1;
    newTime.tm_year = year - 1900;

    return newTime;
}

void prepareForPatientReport()
{
    int choice;
    do {
        printf("\nWhat timespan would you like to generate your report across?\n");
        printf("1. Generate Month Report\n");
        printf("2. Generate Week Report\n");
        printf("3. Generate Day Report\n");
        printf("4. Cancel\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); //consume newline

        switch (choice) {
            case 1:
                request_month(choice);
                break;
            case 2:
            case 3:
                request_day(2, choice);
                break;
            case 4:
                printf("Cancelling...\n");
                break;
            default:
                printf("invalid choice! Try again.\n");
        }
    } while (choice != 4);
}

void reportMenu()
{
    struct list** report = malloc(sizeof(struct list*));
    *report = NULL;

    int choice;
    do {
        printf("\nReport Generator System\n");
        printf("1. Generate report for patients admitted in a day, week, or month\n");
        printf("2. Generate report for patients discharged on specified day\n");
        printf("3. Generate doctor utilization report\n");
        printf("4. Generate room usage report\n");
        printf("5. Return\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); //consume newline

        switch (choice) {
            case 1:
                prepareForPatientReport();
                break;
            case 2:
                request_day(1, 0);
                break;
            case 3:
                doc_report(report);
                saveReportDocUtil("doctorUtilReport.txt", *report);
                break;
            case 4:
                room_report(patientList, report);
                saveReportRoom("roomUtilReport.txt", *report);
                break;
            case 5:
                printf("Returning...\n");
                break;
            default:
                printf("invalid choice! Try again.\n");
        }

        list_clear(report);

    } while (choice != 5);

    free(report);
}