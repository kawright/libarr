/* Array data type */

#ifndef ARR_H
#define ARR_H

#include <ccb.h>
#include <core.h>
#include <err.h>

/* A generic array. */
typedef struct STRUCT_ARR {
    U32     sz;
    Void    **contents;
} Arr;

/* Allocate memory to an 'Arr'. Throws MEM. */
Void dim_arr(Arr *arr, U64 sz, Err *err);

/* Get a specific element from an 'Arr'. Throws BOUNDS. */
Void *get_arr_elem(Arr *arr, U64 index, Err *err);

/* Initialize an 'Arr'. */
Void init_arr(Arr *arr);

/* Search an 'Arr' for an element. If found, 'is_found' is set to 'TRUE' and the
element where it was found is returned. Otherwise, 'is_found' is set to 'FALSE' 
and 0 is returned. */
U64 search_arr(Arr *arr, Void *sample, CompCb comp_cb, Bool *is_found);

/* Set a specific element of an 'Arr'. Throws BOUNDS. */
Void set_arr_elem(Arr *arr, U64 index, Void *val, Err *err);

/* Sort an 'Arr'. */
Void sort_arr(Arr *arr, CompCb comp_cb);

#endif
