#include "sorters.h"
#include <stdbool.h>

void insertion_sort_step(struct int_array* iarr, insertion_sort_state_t* state)
{
    int temp          = 0;
    size_t prev_index = 0;

    for (size_t j = state->current_index; j > 0; j--)
    {
        prev_index = j - 1;
        if (iarr->data[j] < iarr->data[prev_index])
        {
            temp                   = iarr->data[j];
            iarr->data[j]          = iarr->data[prev_index];
            iarr->data[prev_index] = temp;
        }
    }

    state->current_index++;

    if (state->current_index >= iarr->length)
        state->sorted = true;
}

void insertion_sort_reset_state(insertion_sort_state_t* state)
{
    state->current_index = 1;
    state->sorted        = false;
}
