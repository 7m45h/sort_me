#pragma once

#include <stdbool.h>
#include <sys/types.h>

#include "../int_array/int_array.h"

enum SORTING_ALGO
{
    SALGO_NONE      = 0,
    SALGO_INSERTION = 1
};

typedef struct
{
    size_t current_index;
} insertion_sort_state_t;

insertion_sort_state_t* insertion_sort_state_create(void);
bool                    insertion_sort_step(struct int_array* iarr, void* _state);
bool                    insertion_sort_reset_state(void* _state);
