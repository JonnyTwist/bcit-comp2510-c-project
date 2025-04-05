#include "report.h"
#include "patient.h"
#include "dsm.h"
#include <string.h>

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

void docReport(struct list** doc_report)
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
        p_time.tm_mon = p.month_discharged;
        p_time.tm_year = p.year_discharged;

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
        p_time.tm_mon = p.month_admitted;
        p_time.tm_year = p.year_admitted;

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

    return y_diff*10000 + m_diff*100 + d_diff;
}