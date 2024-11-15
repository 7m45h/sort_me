#pragma once

#include <stdbool.h>
#include <sys/types.h>

#include "../int_array/int_array.h"

typedef struct
{
    size_t current_index;
    bool          sorted;
} insertion_sort_state_t;

void insertion_sort_step(struct int_array* iarr, insertion_sort_state_t* state);
void insertion_sort_reset_state(insertion_sort_state_t* state);
