#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_timer.h>
#include <stdbool.h>
#include <time.h>

#include "../logger.h"
#include "scene_helpers.h"
#include "sorters.h"
#include "sorting_scene.h"

#define DEFAULT_TITLE "sort me"

#define DEFAULT_GRAPH_COL_COUNT 32
#define DEFAULT_GRAPH_COL_W     16
#define DEFAULT_GRAPH_COL_H      8

#define ONE_SEC_IN_MILI 1000.0f

#define DEFAULT_SORTING_SPEED 2

bool sscene_init(struct sorting_scene* sscene)
{
    sscene->window = NULL;
    sscene->graph  = NULL;
    sscene->runnig = false;

    sscene->window = window_create(DEFAULT_TITLE);
    if (!sscene->window)
    {
        LOGG_FAILURE("window_create");
        return true;
    }

    sscene->graph = iag_create(DEFAULT_GRAPH_COL_COUNT, DEFAULT_GRAPH_COL_W, DEFAULT_GRAPH_COL_H);
    if (!sscene->graph)
    {
        LOGG_FAILURE("iag_create");
        return true;
    }

    insertion_sort_reset_state(&sscene->state);

    sscene->graph_base.x = 0;
    sscene->graph_base.y = 0;
    sscene->graph_base.w = sscene->graph->dimensions.w;
    sscene->graph_base.h = DEFAULT_GRAPH_COL_H;

    sscene->event_poll_interval = ONE_SEC_IN_MILI / sscene->window->refresh_rate;
    sscene->update_interval     = ONE_SEC_IN_MILI / DEFAULT_SORTING_SPEED;

    return false;
}

void sscene_deinit(struct sorting_scene* sscene)
{
    window_destroy(sscene->window);
    iag_destroy(sscene->graph);

    sscene->window = NULL;
    sscene->graph  = NULL;
    sscene->runnig = false;
}

void sscene_exist(struct sorting_scene* sscene)
{
    sscene->runnig = true;

    Uint64 frame_start_time = 0;
    Uint64 frame_duration   = 0;
    Uint64 event_ticker     = sscene->event_poll_interval;
    Uint64 update_ticker    = sscene->update_interval;

    while (sscene->runnig)
    {
        frame_start_time = SDL_GetTicks64();

        if (event_ticker > sscene->event_poll_interval)
        {
            event_ticker = 0;
            sscene_handle_events(sscene);
        }
        else
        {
            event_ticker += frame_duration;
        }

        if (update_ticker > sscene->update_interval)
        {
            update_ticker = 0;

            if (sscene->state.sorted)
            {
                insertion_sort_reset_state(&sscene->state);
                int_array_suffle(sscene->graph->array);
            }
            else
            {
                insertion_sort_step(sscene->graph->array, &sscene->state);
            }

            iag_update_rects(sscene->graph);
        }
        else
        {
            update_ticker += frame_duration;
        }

        sscene_update_screen(sscene);

        frame_duration = SDL_GetTicks64() - frame_start_time;
    }
}
