#pragma once

#include <stdbool.h>
#include <sys/types.h>

#include "../int_array/int_array.h"

enum SORTING_ALGO
{
    SALGO_NONE      = 0,
    SALGO_INSERTION = 1,
    SALGO_SELECTION = 2
};

typedef struct
{
    size_t current_index;
} insertion_sort_state_t;

insertion_sort_state_t* insertion_sort_state_create(void);
bool                    insertion_sort_step(struct int_array* iarr, void* _state);
bool                    insertion_sort_reset_state(void* _state);

typedef struct
{
    size_t current_index;
    size_t       i_limit;
} selection_sort_state_t;

selection_sort_state_t* selection_sort_state_create(size_t iarr_length);
bool                    selection_sort_step(struct int_array* iarr, void* _state);
bool                    selection_sort_reset_state(void* _state);
