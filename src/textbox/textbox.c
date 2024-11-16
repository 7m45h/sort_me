#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../logger.h"
#include "textbox.h"

struct textbox* textbox_create(const char* font_path, int font_size, int r, int g, int b, int a)
{
    struct textbox* textbox = malloc(sizeof(struct textbox));
    if (!textbox)
    {
        LOGG_ERROR("malloc", errno, strerror(errno));
        return NULL;
    }

    textbox->color.r = r;
    textbox->color.g = g;
    textbox->color.b = b;
    textbox->color.a = a;

    textbox->font    = NULL;
    textbox->texture = NULL;

    textbox->dimensions.x = 0;
    textbox->dimensions.y = 0;
    textbox->dimensions.w = 0;
    textbox->dimensions.h = 0;

    textbox->font = TTF_OpenFont(font_path, font_size);
    if (!textbox->font)
    {
        LOGG_ERROR("TTF_OpenFont", LOGG_UNKNOWN_CODE, TTF_GetError());
        textbox_destroy(textbox);
        return NULL;
    }

    return textbox;
}

void textbox_destroy(struct textbox* textbox)
{
    if (textbox)
    {
        SDL_DestroyTexture(textbox->texture);
        TTF_CloseFont(textbox->font);
    }

    free(textbox);
}

bool textbox_update(struct textbox* textbox, SDL_Renderer* renderer, const char* text)
{
    SDL_Surface* surface = NULL;

    SDL_DestroyTexture(textbox->texture);
    textbox->texture = NULL;

    surface = TTF_RenderText_Solid(textbox->font, text, textbox->color);
    if (!surface)
    {
        LOGG_ERROR("TTF_RenderText_Solid", LOGG_UNKNOWN_CODE, TTF_GetError());
        return true;
    }

    textbox->texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!textbox->texture)
    {
        SDL_FreeSurface(surface);
        LOGG_ERROR("SDL_CreateTextureFromSurface", LOGG_UNKNOWN_CODE, SDL_GetError());
        return true;
    }

    textbox->dimensions.w = surface->w;
    textbox->dimensions.h = surface->h;

    SDL_FreeSurface(surface);

    return false;
}
