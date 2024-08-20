#include "drawable.h"

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <stdio.h>

Drawable new_drawable(SDL_Texture *texture, SDL_Rect rect) {
    Drawable drawable;
    drawable.texture = texture;
    drawable.rect = rect;
    return drawable;
}

Drawable new_drawable_from_file(char path[], SDL_Rect rect, SDL_Renderer *renderer) {
    SDL_Surface *surface = IMG_Load(path);
    if (surface == NULL) {
        printf("Failed to load image: %s\n", IMG_GetError());
        printf("Image path: %s\n", path);
        exit(1);
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == NULL) {
        printf("Failed to create texture: %s\n", SDL_GetError());
        exit(1);
    }
    SDL_FreeSurface(surface);
    return new_drawable(texture, rect);
}

void render_drawable(Drawable *drawable, SDL_Renderer *renderer) {
    SDL_RenderCopy(renderer, drawable->texture, NULL, &drawable->rect);
}

void update_drawable(Drawable *drawable) {
}

void destroy_drawable(Drawable *drawable) {
    SDL_DestroyTexture(drawable->texture);
}