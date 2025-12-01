#include "arr.h"

#include <ccb.h>
#include <core.h>
#include <err.h>
#include <mem.h>

static Void _qsort_swap(Void **left, Void **right) {
    Void *temp = *left;
    *left = *right;
    *right = temp;
}

static U64 _qsort_part(Arr *arr, CompCb comp_cb, U64 low, U64 high) {
    Void        *pivot                  = get_arr_elem(arr, low, NIL);
    U64         pivot_index             = low;
    Void        *temp_scanned;
    Void        *temp_at_pivot_index;
    Void        *temp_last;
    for (U64 j = low; j <= high - 1; j++) {
        temp_scanned            = get_arr_elem(arr, j, NIL);
        temp_at_pivot_index     = get_arr_elem(arr, pivot_index, NIL); 
        if(comp_cb(temp_scanned, pivot) >= 0) {
            _qsort_swap(&temp_scanned, &temp_at_pivot_index);
            pivot_index++;
        }
    }
    temp_at_pivot_index     = get_arr_elem(arr, pivot_index, NIL);
    temp_last               = get_arr_elem(arr, high, NIL);
    _qsort_swap(&temp_at_pivot_index, &temp_last);
    return pivot_index;
}

static Void _qsort(Arr *arr, CompCb comp_cb, U64 low, U64 high) {
    if (low >= high)
        return;
    U64 pivot_index = _qsort_part(arr, comp_cb, low, high);
    _qsort(arr, comp_cb, low, pivot_index - 1);
    _qsort(arr, comp_cb, pivot_index + 1, high);
}

Void dim_arr(Arr *arr, U64 sz, Err *err) {
    arr->contents = alloc_mem(sz * sizeof(Void *), err);
    if (is_err(err))
        return;
    arr->sz = sz;
}

Void *get_arr_elem(Arr *arr, U64 index, Err *err) {
    if (index >= arr->sz) {
        THROW(err, ErrCode_BOUNDS, "Out of bounds array access at index %lld",
            index)
        return NIL;
    }
    Void **temp = arr->contents + index;
    return *temp;
}

Void init_arr(Arr *arr) {
    arr->sz             = 0;
    arr->contents       = NIL;
}

U64 search_arr(Arr *arr, Void *sample, CompCb comp_cb, Bool *is_found) {
    sort_arr(arr, comp_cb);
    U64     low         = 0;
    U64     high        = arr->sz - 1;
    U64     mid;
    Void    *temp_at_mid;
    while (low <= high) {
        mid = low + ((high - low) / 2);
        temp_at_mid = get_arr_elem(arr, mid, NIL);
        if (comp_cb(temp_at_mid, sample) < 0) {
            high = mid - 1;
        } else if (comp_cb(temp_at_mid, sample) > 0) {
            low = mid + 1;
        } else {
            *is_found = TRUE;
            return mid;
        }
    }
    *is_found = FALSE;
    return 0;
}

Void set_arr_elem(Arr *arr, U64 index, Void *val, Err *err) {
    if (index >= arr->sz) {
        THROW(err, ErrCode_BOUNDS, "Out of bounds array access at index %lld",
            index)
        return;
    }
    Void **temp = arr->contents + index;
    *temp = val;
}

Void sort_arr(Arr *arr, CompCb comp_cb) {
    if (arr->sz == 0)
        return;
    _qsort(arr, comp_cb, 0, arr->sz - 1); 
}


