#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>

#include "../int_array/int_array.h"

struct iarr_graph
{
    SDL_FRect      dimensions;
    SDL_FPoint col_dimensions;
    int             col_count;
    struct int_array*   array;
    SDL_FRect*          rects;
};

struct iarr_graph* iag_create(int col_count, int col_w, int col_h_ratio);
void               iag_destroy(struct iarr_graph* iag);

void iag_update_rects(struct iarr_graph* iag);
