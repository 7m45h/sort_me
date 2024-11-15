#include <SDL2/SDL_rect.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>

#include "../logger.h"
#include "iarr_graph.h"

static void iag_first_use(struct iarr_graph* iag)
{
    int_array_fill(iag->array);
    int_array_suffle(iag->array);

    iag->dimensions.x = 0;
    iag->dimensions.y = 0;
    iag->dimensions.w = iag->col_dimensions.x * iag->col_count;
    iag->dimensions.h = iag->col_dimensions.y * iag->col_count;

    for (size_t i = 0; i < iag->array->length; i++)
        iag->rects[i].w = iag->col_dimensions.x;

    iag_update_rects(iag);
}

struct iarr_graph* iag_create(int col_count, int col_w, int col_h_ratio)
{
    struct iarr_graph* iag = NULL;

    iag = malloc(sizeof(struct iarr_graph));
    if (!iag)
    {
        LOGG_ERROR("malloc", errno, strerror(errno));
        return NULL;
    }

    iag->array = NULL;
    iag->rects = NULL;

    iag->array = int_array_create(col_count);
    if (!iag->array)
    {
        LOGG_FAILURE("int_array_create");
        iag_destroy(iag);
        return NULL;
    }

    iag->rects = malloc(sizeof(SDL_FRect) * col_count);
    if (!iag->rects)
    {
        LOGG_ERROR("malloc", errno, strerror(errno));
        iag_destroy(iag);
        return NULL;
    }

    iag->col_dimensions.x = col_w;
    iag->col_dimensions.y = col_h_ratio;
    iag->col_count        = col_count;

    iag_first_use(iag);

    return iag;
}

void iag_destroy(struct iarr_graph* iag)
{
    if (iag)
    {
        int_array_destroy(iag->array);
        free(iag->rects);
    }

    free(iag);
}

void iag_update_rects(struct iarr_graph* iag)
{
    SDL_FRect* current_rect = NULL;

    for (size_t i = 0; i < iag->array->length; i++)
    {
        current_rect = &iag->rects[i];

        current_rect->h = iag->col_dimensions.y * iag->array->data[i];
        current_rect->x = iag->dimensions.x + iag->col_dimensions.x * i;
        current_rect->y = iag->dimensions.y + (iag->dimensions.h - current_rect->h);
    }
}
