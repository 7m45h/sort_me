#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../logger.h"
#include "int_array.h"

struct int_array* int_array_create(int capacity)
{
    struct int_array* iarr = NULL;

    iarr = malloc(sizeof(struct int_array));
    if (!iarr)
    {
        LOGG_ERROR("malloc", errno, strerror(errno));
        return NULL;
    }

    iarr->capacity = capacity;
    iarr->length   = 0;
    iarr->data     = NULL;

    iarr->data = malloc(sizeof(int) * capacity);
    if (!iarr->data)
    {
        LOGG_ERROR("malloc", errno, strerror(errno));
        int_array_destroy(iarr);
        return NULL;
    }

    return iarr;
}

void int_array_destroy(struct int_array* iarr)
{
    if (iarr)
        free(iarr->data);

    free(iarr);
}

void int_array_fill(struct int_array* iarr)
{
    for (size_t i = 0; i < iarr->capacity; i++)
        iarr->data[i] = i + 1;

    iarr->length = iarr->capacity;
}

void int_array_suffle(struct int_array* iarr)
{
    int temp         = 0;
    int random_index = 0;

    srand(time(NULL));

    for (size_t i = 0; i < iarr->length; i++)
    {
        random_index = rand() % iarr->length;

        temp                     = iarr->data[i];
        iarr->data[i]            = iarr->data[random_index];
        iarr->data[random_index] = temp;
    }
}
