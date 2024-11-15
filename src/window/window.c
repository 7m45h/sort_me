#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../logger.h"
#include "window.h"

struct window* window_create(const char* title)
{
    SDL_DisplayMode display_mode;
    int sdl_error            = 0;
    struct window* window = NULL;

    window = malloc(sizeof(struct window));
    if (!window)
    {
        LOGG_ERROR("malloc", errno, strerror(errno));
        return NULL;
    }

    window->window   = NULL;
    window->renderer = NULL;

    sdl_error = SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_EVENTS);
    if (sdl_error)
    {
        LOGG_ERROR("SDL_Init", sdl_error, SDL_GetError());
        window_destroy(window);
        return NULL;
    }

    sdl_error = SDL_GetDesktopDisplayMode(0, &display_mode);
    if (sdl_error)
    {
        LOGG_ERROR("SDL_GetDesktopDisplayMode", sdl_error, SDL_GetError());
        window_destroy(window);
        return NULL;
    }

    window->refresh_rate = display_mode.refresh_rate;
    window->dimensions.x = display_mode.w;
    window->dimensions.y = display_mode.h;

    window->window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window->dimensions.x, window->dimensions.y, SDL_WINDOW_RESIZABLE);
    if (!window->window)
    {
        LOGG_ERROR("SDL_CreateWindow", LOGG_UNKNOWN_CODE, SDL_GetError());
        window_destroy(window);
        return NULL;
    }

    window->renderer = SDL_CreateRenderer(window->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!window->renderer)
    {
        LOGG_ERROR("SDL_CreateRenderer", LOGG_UNKNOWN_CODE, SDL_GetError());
        window_destroy(window);
        return NULL;
    }

    return window;
}

void window_destroy(struct window* window)
{
    SDL_DestroyRenderer(window->renderer);
    SDL_DestroyWindow(window->window);

    free(window);

    SDL_Quit();
}
