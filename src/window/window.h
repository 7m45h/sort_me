#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>

struct window
{
    int       refresh_rate;
    SDL_Point   dimensions;
    SDL_Window*     window;
    SDL_Renderer* renderer;
    SDL_Event        event;
    bool          windowed;
};

struct window* window_create(const char* title);
void           window_destroy(struct window* window);

bool window_toggle_fullscreen(struct window* window);
