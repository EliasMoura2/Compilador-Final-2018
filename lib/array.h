#ifndef ARRAY_H
#define ARRAY_H

#include "cya.h"

struct array_item
{
    struct array_item* prev;
    struct array_item* next;

    unsigned int index;
    void* data;
};

struct array
{
    struct array_item *item;
    struct array_item *_current;
    unsigned char end;
    unsigned int length;
};

/**
 * Crea un nuevo arreglo vacío
 * 
 * @return
 */
struct array* array_new();

/**
 * Agrega un item al final de un arreglo
 * El item SIEMPRE se agrega por REFERENCIA.
 * 
 * @param  arr  el arreglo al que agregar el item
 * @param  item el item a agregar
 * @return      el índice del nuevo item dentro del arreglo
 */
int array_add_item(struct array* arr, void* item);

/**
 * Resetea el iterador de un arreglo, apuntandolo al primer item
 * @param arr el arreglo cuyo iterador se desea reiniciar
 */
void array_reset(struct array* arr);

/**
 * Devuelve el item actual del iterador del arreglo
 * 
 * @param arr
 */
void* array_current(struct array* arr);

/**
 * Devuelve el índice del item atual del iterador del arreglo, o -1 si no hay item actual
 * 
 * @param  arr
 * @return
 */
int array_current_index(struct array* arr);

/**
 * Avanza el iterador del arreglo y devuelve el nuevo item, o NULL si se llegó al final del arreglo
 * 
 * @param arr 
 */
void* array_next(struct array* arr);

/**
 * Devuelve la longitud del arreglo, esto es, la cantidad de items
 * 
 * @param  arr
 * @return
 */
int array_length(struct array* arr);

/**
 * Devuelve un item en función de un índice
 * Si el item no se encuentra, devuelve NULL
 * 
 * @param arr
 * @param index
 */
void* array_get_item(struct array* arr, int index);

#endif /* ARRAY_H */