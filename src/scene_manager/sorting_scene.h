#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <stdbool.h>

#include "../textbox/textbox.h"
#include "../iarr_graph/iarr_graph.h"
#include "../window/window.h"
#include "sorters.h"

struct sorting_scene
{
    struct window*    window;
    struct iarr_graph* graph;

    enum SORTING_ALGO              current_algo;
    void*                            algo_state;
    bool (*algo_step)(struct int_array*, void*);
    bool             (*algo_state_reset)(void*);
    struct textbox*                       title;

    SDL_FRect graph_base;

    float event_poll_interval;
    float     update_interval;
    bool               sorted;
    bool               runnig;
};

bool sscene_init(struct sorting_scene* sscene);
void sscene_deinit(struct sorting_scene* sscene);

void sscene_exist(struct sorting_scene* sscene);
