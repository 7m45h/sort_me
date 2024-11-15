#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "../colors.h"
#include "../logger.h"
#include "scene_helpers.h"
#include "sorters.h"
#include "sorting_scene.h"

static const int salgo_count = SALGO_COUNT;

bool sscene_handle_events(struct sorting_scene* sscene)
{
    bool error = false;

    while (SDL_PollEvent(&sscene->window->event))
    {
        switch (sscene->window->event.type)
        {
            case SDL_QUIT:
            sscene->runnig = false;
            break;

            case SDL_KEYDOWN:
            switch (sscene->window->event.key.keysym.sym)
            {
                case SDLK_q:
                sscene->runnig = false;
                break;

                case SDLK_f:
                error = window_toggle_fullscreen(sscene->window);
                if (error)
                {
                    LOGG_FAILURE("window_toggle_fullscreen");
                }
                break;

                case SDLK_h:
                error = sscene_set_current_algo(sscene, ((sscene->current_algo - 1) + salgo_count) % salgo_count);
                if (error)
                {
                    LOGG_FAILURE("sscene_set_current_algo");
                }
                break;

                case SDLK_l:
                error = sscene_set_current_algo(sscene, ((sscene->current_algo + 1) + salgo_count) % salgo_count);
                if (error)
                {
                    LOGG_FAILURE("sscene_set_current_algo");
                }
                break;
            }
            break;

            case SDL_WINDOWEVENT:
            switch (sscene->window->event.window.event)
            {
                case SDL_WINDOWEVENT_RESIZED:
                case SDL_WINDOWEVENT_SIZE_CHANGED:
                sscene->window->dimensions.x = sscene->window->event.window.data1;
                sscene->window->dimensions.y = sscene->window->event.window.data2;

                sscene_alighn_items(sscene);
                break;
            }
            break;
        }
    }

    return error;
}

void sscene_update_screen(struct sorting_scene* sscene)
{
    SDL_SetRenderDrawColor(sscene->window->renderer, COLOR_BLACK);
    SDL_RenderClear(sscene->window->renderer);

    SDL_SetRenderDrawColor(sscene->window->renderer, COLOR_WHITE);
    SDL_RenderFillRectsF(sscene->window->renderer, sscene->graph->rects, sscene->graph->array->length);
    SDL_RenderFillRectF(sscene->window->renderer, &sscene->graph_base);
    SDL_RenderCopyF(sscene->window->renderer, sscene->title->texture, NULL, &sscene->title->dimensions);

    SDL_RenderPresent(sscene->window->renderer);
}

void sscene_alighn_items(struct sorting_scene* sscene)
{
    sscene->graph->dimensions.x = (sscene->window->dimensions.x - sscene->graph->dimensions.w) * 0.5;
    sscene->graph->dimensions.y = (sscene->window->dimensions.y - sscene->graph->dimensions.h) * 0.5;

    sscene->graph_base.x = (sscene->window->dimensions.x - sscene->graph_base.w) * 0.5;
    sscene->graph_base.y = sscene->graph->dimensions.y + sscene->graph->dimensions.h + sscene->graph->col_dimensions.y;

    sscene->title->dimensions.x = (sscene->window->dimensions.x - sscene->title->dimensions.w) * 0.5;
    sscene->title->dimensions.y = sscene->graph_base.y + sscene->graph_base.h + sscene->graph->col_dimensions.y;

    iag_update_rects(sscene->graph);
}

bool sscene_set_current_algo(struct sorting_scene* sscene, enum SORTING_ALGO algo)
{
    bool error = false;

    free(sscene->algo_state);

    sscene->algo_state       = NULL;
    sscene->algo_step        = NULL;
    sscene->algo_state_reset = NULL;

    switch (algo)
    {
        case SALGO_INSERTION:
        sscene->algo_state = insertion_sort_state_create();
        if (!sscene->algo_state)
        {
            LOGG_FAILURE("insertion_sort_state_create");
            error = true;
        }

        error = textbox_update(sscene->title, sscene->window->renderer, "insertion sort");
        if (error)
        {
            LOGG_FAILURE("textbox_update");
        }

        sscene->current_algo     = algo;
        sscene->algo_step        = &insertion_sort_step;
        sscene->algo_state_reset = &insertion_sort_reset_state;
        break;

        case SALGO_SELECTION:
        sscene->algo_state = selection_sort_state_create(sscene->graph->array->length);
        if (!sscene->algo_state)
        {
            LOGG_FAILURE("selection_sort_state_create");
            error = true;
        }

        error = textbox_update(sscene->title, sscene->window->renderer, "selection sort");
        if (error)
        {
            LOGG_FAILURE("textbox_update");
        }

        sscene->current_algo     = algo;
        sscene->algo_step        = &selection_sort_step;
        sscene->algo_state_reset = &selection_sort_reset_state;
        break;
    }

    return error;
}
