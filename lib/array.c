#include "array.h"

struct array* array_new()
{
    struct array* arr = (struct array*)malloc(sizeof(struct array));
    arr->length = 0;
    arr->item = NULL;
    arr->_current = NULL;

    return arr;
}

int array_add_item(struct array* arr, void* item)
{
    struct array_item* p = arr->item;
    struct array_item* q = NULL;
    struct array_item* new_item = (struct array_item*)malloc(sizeof(struct array_item));

    new_item->data = item;
    new_item->index = arr->length++;

    while(p != NULL) {
        q = p;
        p = p->next;
    }
    if (q == NULL) {
        arr->item = new_item;
    } else {
        new_item->prev = q;
        q->next = new_item;
    }

    return new_item->index;
}

void array_reset(struct array* arr)
{
    arr->end = 0;
    arr->_current = NULL;
}

void* array_current(struct array* arr)
{
    if (arr->end) {
        return NULL;
    }
    return arr->_current == NULL ? NULL : arr->_current->data;
}

int array_current_index(struct array* arr)
{
    if (arr->end) {
        return -1;
    }
    return arr->_current == NULL ? -1 : arr->_current->index;
}

void* array_next(struct array* arr)
{
    if (arr->end) {
        return NULL;
    }
    if (arr->_current == NULL) {
        arr->_current = arr->item;
    } else {
        arr->_current = arr->_current->next;
    }
    if (arr->_current == NULL) {
        arr->end = 1;
    }

    return array_current(arr);
}

int array_length(struct array* arr)
{
    return arr->length;
}

void* array_get_item(struct array* arr, int index)
{
    struct array_item* item = arr->item;
    while (item != NULL) {
        if (item->index == index) {
            break;
        }
        item = item->next;
    }
    return item == NULL ? NULL : item->data;
}
