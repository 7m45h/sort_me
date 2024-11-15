#pragma once

#include <SDL2/SDL_rect.h>
#include <stdbool.h>

#include "../iarr_graph/iarr_graph.h"
#include "../window/window.h"
#include "sorters.h"

struct sorting_scene
{
    struct window*        window;
    struct iarr_graph*     graph;
    insertion_sort_state_t state;
    SDL_FRect         graph_base;
    float    event_poll_interval;
    float        update_interval;
    bool                  runnig;
};

bool sscene_init(struct sorting_scene* sscene);
void sscene_deinit(struct sorting_scene* sscene);

void sscene_exist(struct sorting_scene* sscene);
