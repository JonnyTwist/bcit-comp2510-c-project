#include "report.h"
#include "patient.h"
#include <string.h>

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