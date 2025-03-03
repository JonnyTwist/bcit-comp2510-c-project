#include "list.h"
#include <stdlib.h>

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
        printf("elt %zu: %d\n", i, *(int *) list_get(*test_list, i));
    if (list_get(*test_list, 13) == NULL && list_get(*test_list, -1) == NULL)
        printf("EDGE CASE, SUCCESSFULLY RETURNED NULL\n");


    printf("\n");
    list_print(*test_list);
    list_remove_at(test_list, 2);
    list_print(*test_list);
    list_remove_at(test_list, 0);
    list_print(*test_list);
    list_remove_at(test_list, 4);
    list_print(*test_list);
    list_remove_at(test_list, 5);
    list_print(*test_list);
    list_remove_at(test_list, 23);
    list_print(*test_list);
    list_remove_at(test_list, 7);
    list_print(*test_list);
    list_remove_at(test_list, 1);
    list_print(*test_list);
    list_remove_at(test_list, 1);
    list_print(*test_list);
    list_remove_at(test_list, 1);
    list_print(*test_list);
    list_remove_at(test_list, 1);
    list_print(*test_list);
    list_remove_at(test_list, 1);
    list_print(*test_list);
    list_remove_at(test_list, 1);
    list_print(*test_list);
    list_remove_at(test_list, 1);
    list_print(*test_list);
    list_remove_at(test_list, 0);
    list_print(*test_list);

    printf("\n");
    list_print(*test_list);
}