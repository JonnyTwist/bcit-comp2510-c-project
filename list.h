//
// Created by maxym on 27/02/2025.
//
#include <stdio.h>

#ifndef LIST_H
#define LIST_H

struct list
{
    void* elt;
    struct list* next;
};

int list_push_front(struct list** list, void* elt, size_t elt_size);
int list_push_back(struct list** list, void* elt);
int list_insert(struct list** list, size_t index, void* elt);
int list_remove_at(struct list** list, size_t index);
int list_clear(struct list** list);
int list_print(struct list* list);
void* list_pop_back(struct list** list);
void* list_pop_front(struct list** list);
void* list_get(struct list* list, size_t index);
size_t list_length(struct list* list);


#endif LIST_H
