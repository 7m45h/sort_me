#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>

struct textbox
{
    SDL_Color      color;
    TTF_Font*       font;
    SDL_Texture* texture;
    SDL_FRect dimensions;
};

struct textbox* textbox_create(const char* font_path, int font_size, int r, int g, int b, int a);
void            textbox_destroy(struct textbox* textbox);

bool textbox_update(struct textbox* textbox, SDL_Renderer* renderer, const char* text);
