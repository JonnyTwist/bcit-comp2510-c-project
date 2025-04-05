/**
 * Contains code that was used to speed up testing.
 * Is not used while the program runs normally but it
 * shows how we used code to test our code in some cases.
 * @author Nicolas Bertrand
 * @author Jonny Twist
 * @version 1.0
 */

#include "list.h"
#include "file_m.h"
#include "patient.h"
#include <stdlib.h>
#include "report.h"

 void print_report(struct list* report);
 void test()
 {
     struct list** test_list = malloc(sizeof(struct list*));
     *test_list = NULL;

     int e1 = 8;
     int e2 = 4;
     int e3 = 9;
     int e4 = 67;
     int e5 = 42;
     int e6 = 78;
     int e7 = 2;

     list_push_front(test_list,&e1,sizeof(int));
     list_push_front(test_list,&e2,sizeof(int));
     list_push_front(test_list,&e3,sizeof(int));
     list_push_front(test_list,&e4,sizeof(int));
     list_push_front(test_list,&e5,sizeof(int));
     list_push_front(test_list,&e2,sizeof(int));
     list_push_front(test_list,&e3,sizeof(int));
     list_push_front(test_list,&e6,sizeof(int));
     list_push_front(test_list,&e7,sizeof(int));
     list_push_front(test_list,&e1,sizeof(int));
     list_push_front(test_list,&e7,sizeof(int));
     list_push_front(test_list,&e3,sizeof(int));

     list_print(*test_list);

     printf("\n");
     for (size_t i = 0; i < 12; i++)
         printf("elt %zu: %d\n", i, *(int*)list_get(*test_list, i));

     if (list_get(*test_list, 13) == NULL && list_get(*test_list, -1) == NULL)
         printf("EDGE CASE, SUCCESSFULLY RETURNED NULL\n");


     printf("\n");
     list_print(*test_list);
     printf("removing 3rd elt\n");
     list_remove_at(test_list, 2);
     list_print(*test_list);
     printf("removing 1st elt\n");
     list_remove_at(test_list, 0);
     list_print(*test_list);
     printf("removing 5th elt\n");
     list_remove_at(test_list, 4);
     list_print(*test_list);
     printf("removing 6th elt\n");
     list_remove_at(test_list, 5);
     list_print(*test_list);
     printf("removing 24th elt(does not exist)\n");
     list_remove_at(test_list, 23);
     list_print(*test_list);
     printf("removing 8th elt\n");
     list_remove_at(test_list, 7);
     list_print(*test_list);
     printf("removing 2nd elt\n");
     list_remove_at(test_list, 1);
     list_print(*test_list);
     printf("removing 2nd elt\n");
     list_remove_at(test_list, 1);
     list_print(*test_list);
     printf("removing 2nd elt\n");
     list_remove_at(test_list, 1);
     list_print(*test_list);
     printf("removing 2nd elt\n");
     list_remove_at(test_list, 1);
     list_print(*test_list);
     printf("removing 2nd elt\n");
     list_remove_at(test_list, 1);
     list_print(*test_list);
     printf("removing 2nd elt\n");
     list_remove_at(test_list, 1);
     list_print(*test_list);
     printf("removing 2nd elt\n");
     list_remove_at(test_list, 1);
     list_print(*test_list);
     printf("removing 1st elt\n");
     list_remove_at(test_list, 0);
     list_print(*test_list);

     printf("\n");
     list_print(*test_list);

     list_push_front(test_list,&e1,sizeof(int));
     list_push_front(test_list,&e2,sizeof(int));
     list_push_front(test_list,&e3,sizeof(int));
     list_push_front(test_list,&e4,sizeof(int));
     list_push_front(test_list,&e5,sizeof(int));
     list_push_front(test_list,&e2,sizeof(int));
     list_push_front(test_list,&e3,sizeof(int));
     list_push_front(test_list,&e6,sizeof(int));
     list_push_front(test_list,&e7,sizeof(int));
     list_push_front(test_list,&e1,sizeof(int));
     list_push_front(test_list,&e7,sizeof(int));
     list_push_front(test_list,&e3,sizeof(int));

     printf("\n");
     while(*test_list)
     {
         list_print(*test_list);
         printf(" -> %d\n", *(int*)list_pop_front(test_list));
     }
     list_print(*test_list);
 }

 void print_patient(struct list* ps)
 {
     int i = 1;
     while (ps)
     {
         patient p = *(patient*)ps->elt;
         printf("patient %d:\n", i);
         printf("\tid: %d\n", p.patient_id);
         printf("\tage: %d\n", p.age);
         printf("\tdiagnosis: %s\n", p.diagnosis);
         printf("\tname: %s\n", p.name);
         ps = ps->next;
         i++;
     }
 }

 void test2()
 {
     struct list** patient_list = malloc(sizeof(struct list*));
     *patient_list = NULL;

     for(int i = 0; i < 23; i++)
     {
         patient p1;
         p1.age = i;
         p1.diagnosis[0] = 'A' + i;
         p1.diagnosis[1] = 0;
         p1.patient_id = i;
         p1.name[0] = 87 - i;
         p1.name[1] = 0;

         list_push_front(patient_list, &p1, sizeof(patient));
     }

     char* filename = "C:\\Users\\maxym\\OneDrive\\Documents\\GitHub\\bcit-comp2510-c-project\\test.bin";
     savePatientsInfo(filename, *patient_list, NULL);
     print_patient(*patient_list);
     list_clear(patient_list);
     printf("patients cleared\n------------------------\n");
     print_patient(*patient_list);
     printf("------------------------\n");
     loadPatientsInfo(filename, patient_list, NULL);
     print_patient(*patient_list);
 }

void test3()
{
    struct list** report = malloc(sizeof(struct list*));
    *report = NULL;
    struct list** patients = malloc(sizeof(struct list*));
    *patients = NULL;
    srand(time(NULL));
    for (int i = 0; i < 200; i++)
    {
        patient p;
        p.name[0] = 'A';
        p.name[1] = 0;
        p.diagnosis[0]= 'B';
        p.diagnosis[1] = 0;
        p.patient_id = i + 1;p.age = 20;
        p.room_number = rand()%20;
        p.date_discharged = (i % 10) + 1;
        p.month_discharged = 1;
        p.year_discharged = 1;
        p.date_admitted = (i % 25) + 1;
        p.month_admitted = 1;
        p.year_admitted = 1;
        list_push_front(patients, &p, sizeof(patient));
    }

    for (int i = 0; i < 20; i++){
        struct tm l;
        struct tm r;

        l.tm_mon = (i % 4) + 1;
        l.tm_year = (i % 8) + 1;
        l.tm_mday = 1;
        r.tm_mon = (i % 2) + 1;
        r.tm_year = (i % 8) + 1;
        r.tm_mday = 25 - i;

        printf("Admitted: %d\t discharged: %d\n",
            admitted_in_interval(*patients, l, r),
            discharged_in_interval(*patients, l, r));
    }

    room_report(*patients, report);
    print_report(*report);
    saveReportRoom("../testroomreport.txt", *report);
    list_clear(report);
    list_clear(patients);
    free(report);
    free(patients);
}

void print_report(struct list* report)
{
    while (report)
    {
        Key_value kv = *(Key_value*)report->elt;
        printf("Key: %d\tValue: %d\n", kv.key, kv.value);

        report = report->next;
    }
};