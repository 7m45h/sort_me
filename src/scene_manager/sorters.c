#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "../logger.h"
#include "sorters.h"

insertion_sort_state_t* insertion_sort_state_create(void)
{
    insertion_sort_state_t* state = malloc(sizeof(insertion_sort_state_t));
    if (!state)
    {
        LOGG_ERROR("malloc", errno, strerror(errno));
        return NULL;
    }

    state->current_index = 1;

    return state;
}

bool insertion_sort_step(struct int_array* iarr, void* _state)
{
    int temp                      = 0;
    size_t prev_index             = 0;
    bool sorted                   = false;
    insertion_sort_state_t* state = _state;

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
        sorted = true;

    return sorted;
}

bool insertion_sort_reset_state(void* _state)
{
    insertion_sort_state_t* state = _state;
    state->current_index          = 1;

    return false;
}
