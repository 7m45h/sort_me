#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>

#include "../colors.h"
#include "scene_helpers.h"

void sscene_handle_events(struct sorting_scene* sscene)
{
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
}

void sscene_update_screen(struct sorting_scene* sscene)
{
    SDL_SetRenderDrawColor(sscene->window->renderer, COLOR_BLACK);
    SDL_RenderClear(sscene->window->renderer);

    SDL_SetRenderDrawColor(sscene->window->renderer, COLOR_WHITE);
    SDL_RenderFillRectsF(sscene->window->renderer, sscene->graph->rects, sscene->graph->array->length);
    SDL_RenderFillRectF(sscene->window->renderer, &sscene->graph_base);

    SDL_RenderPresent(sscene->window->renderer);
}

void sscene_alighn_items(struct sorting_scene* sscene)
{
    sscene->graph->dimensions.x = (sscene->window->dimensions.x - sscene->graph->dimensions.w) * 0.5;
    sscene->graph->dimensions.y = (sscene->window->dimensions.y - sscene->graph->dimensions.h) * 0.5;

    sscene->graph_base.x = (sscene->window->dimensions.x - sscene->graph_base.w) * 0.5;
    sscene->graph_base.y = sscene->graph->dimensions.y + sscene->graph->dimensions.h + sscene->graph->col_dimensions.y;

    iag_update_rects(sscene->graph);
}