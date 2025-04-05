/**
 * Defines how our lists work
 * @author Nicolas Bertrand
 * @author Jonny Twist
 * @version 1.0
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.h"

/**
 * Adds a new element to the front of the list.
 * @param list Pointer to the pointer of the list head.
 * @param elt Pointer to the element to be inserted.
 * @param elt_size Size of the element in bytes.
 * @return 0 on success, -1 on failure.
 */
int list_push_front(struct list** list, void* elt, size_t elt_size)
{
    struct list* new = malloc(sizeof(struct list));
    if (new == NULL || list == NULL || elt == NULL)
    {
        return -1;
    }

    new->elt = malloc(elt_size);
    if (new->elt == NULL)
    {
        free(new);
        return -1;
    }
    memcpy(new->elt, elt, elt_size);
    new->next = *list;
    *list = new;

    return 0;
}

/**
 * Adds a new element to the end of the list.
 * @param list Pointer to the pointer of the list head.
 * @param elt Pointer to the element to be inserted.
 * @return 0 on success, -1 on failure (e.g., memory allocation error).
 */
int list_push_back(struct list** list, void* elt)
{
    struct list* new = malloc(sizeof(struct list));
    if (new == NULL || list == NULL || elt == NULL)
    {
        return -1;
    }

    new->elt = elt;
    new->next = NULL;

    if (*list == NULL)
    {
        *list = new;
        return 0;
    }

    struct list* cpy = *list;
    while (cpy->next)
    {
        cpy = cpy->next;
    }
    cpy->next = new;

    return 0;
}

/**
 * Clears the entire list, freeing all allocated memory.
 * @param list Pointer to the pointer of the list head.
 * @return 0 on success, -1 if the list pointer is NULL.
 */
int list_clear(struct list** list)
{
    if (list == NULL)
    {
        return -1;
    }

    struct list* head = *list;
    while (head)
    {
        struct list* cpy = head;
        head = head->next;
        free(cpy->elt);
        free(cpy);
    }

    *list = NULL;
    return 0;
}

/**
 * Retrieves an element at a specific index.
 * @param list Pointer to the list head.
 * @param index Index of the desired element.
 * @return Pointer to the element if found, otherwise NULL.
 */
void* list_get(struct list* list, size_t index)
{
    void* res = NULL;
    for (size_t i = 0; i < index && list; i++)
    {
        list = list->next;
    }
    if (list)
    {
        res = list->elt;
    }
    return res;
}

/**
 * Removes the first element from the list and returns it.
 * @param list Pointer to the pointer of the list head.
 * @return Pointer to the removed element, or NULL if the list is empty or invalid.
 */
void* list_pop_front(struct list** list)
{
    void* res = NULL;
    if (list == NULL)
    {
        return NULL;
    }
    struct list* head = *list;

    if (head == NULL)
    {
        return NULL;
    }

    *list = head->next;
    res = head->elt;
    free(head);
    return res;
}

/**
 * Removes an element at a specific index.
 * @param list Pointer to the pointer of the list head.
 * @param index Index of the element to be removed.
 * @return 0 on success, -1 if the list pointer is NULL or index is out of bounds.
 */
int list_remove_at(struct list** list, size_t index)
{
    if (list == NULL)
    {
        return -1;
    }

    if (index == 0)
    {
        free(list_pop_front(list));
        return 0;
    }

    struct list* head = *list;
    size_t i;
    for (i = 1; i < index && head && head->next; i++)
    {
        head = head->next;
    }

    if (head && head->next)
    {
        struct list* to_remove = head->next;
        head->next = head->next->next;
        free(to_remove->elt);
        free(to_remove);
    }
    if (head && i == index){}

    return 0;
}

/**
 * Prints the list.
 * @param list Pointer to the list head.
 * @return 0 on success.
 */
int list_print(struct list* list)
{
    printf("{ ");
    if(list)
    {
        printf("%d", *(int*)list->elt);
        list = list->next;
    }
    while (list)
    {
        printf(", %d", *(int*)list->elt);
        list = list->next;
    }
    printf(" }\n");
    return 0;
}

/**
 * Calculates the length of the list.
 * @param list Pointer to the list head.
 * @return Number of elements in the list.
 */
size_t list_length(struct list* list)
{
    size_t res = 0;
    while(list)
    {
        list = list->next;
        res++;
    }
    return res;
}