#include <SDL2/SDL.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_timer.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "../colors.h"
#include "../logger.h"
#include "scene_helpers.h"
#include "sorters.h"
#include "sorting_scene.h"

#define DEFAULT_GRAPH_COL_COUNT 32
#define DEFAULT_GRAPH_COL_H      8
#define DEFAULT_GRAPH_COL_W     16
#define DEFAULT_SORTING_SPEED    2

#define DEFAULT_TITLE "sort me"

#define FONT_PATH "./assets/terminus.ttf"
#define FONT_SIZE 32

#define ONE_SEC_IN_MILI 1000.0f

bool sscene_init(struct sorting_scene* sscene)
{
    sscene->window           = NULL;
    sscene->graph            = NULL;
    sscene->algo_state       = NULL;
    sscene->algo_step        = NULL;
    sscene->algo_state_reset = NULL;
    sscene->title            = NULL;

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

    sscene->title = textbox_create(FONT_PATH, FONT_SIZE, COLOR_WHITE);
    if (!sscene->title)
    {
        LOGG_FAILURE("textbox_create");
        return true;
    }

    bool error = sscene_set_current_algo(sscene, SALGO_SELECTION);
    if (error)
    {
        LOGG_FAILURE("sscene_set_current_algo");
        return true;
    }

    sscene->graph_base.x = 0;
    sscene->graph_base.y = 0;
    sscene->graph_base.w = sscene->graph->dimensions.w;
    sscene->graph_base.h = DEFAULT_GRAPH_COL_H;

    sscene->event_poll_interval = ONE_SEC_IN_MILI / sscene->window->refresh_rate;
    sscene->update_interval     = ONE_SEC_IN_MILI / DEFAULT_SORTING_SPEED;
    sscene->sorted              = false;
    sscene->runnig              = false;

    return false;
}

void sscene_deinit(struct sorting_scene* sscene)
{
    free(sscene->algo_state);
    textbox_destroy(sscene->title);

    window_destroy(sscene->window);
    iag_destroy(sscene->graph);

    sscene->window = NULL;
    sscene->graph  = NULL;
    sscene->runnig = false;
}

void sscene_exist(struct sorting_scene* sscene)
{
    bool error              = false;
    Uint64 frame_start_time = 0;
    Uint64 frame_duration   = 0;
    Uint64 event_ticker     = sscene->event_poll_interval;
    Uint64 update_ticker    = sscene->update_interval;

    sscene->runnig = true;

    while (sscene->runnig)
    {
        frame_start_time = SDL_GetTicks64();

        if (event_ticker > sscene->event_poll_interval)
        {
            event_ticker = 0;
            error = sscene_handle_events(sscene);
            if (error)
            {
                LOGG_FAILURE("sscene_handle_events");
                break;
            }
        }
        else
        {
            event_ticker += frame_duration;
        }

        if (update_ticker > sscene->update_interval)
        {
            update_ticker = 0;

            if (sscene->sorted)
            {
                sscene->sorted = sscene->algo_state_reset(sscene->algo_state);
                int_array_suffle(sscene->graph->array);
            }
            else
            {
                sscene->sorted = sscene->algo_step(sscene->graph->array, sscene->algo_state);
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
