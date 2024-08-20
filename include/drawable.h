#include "SDL2/SDL.h"

typedef struct Drawable {
    SDL_Texture *texture;
    SDL_Rect rect;
} Drawable;

Drawable new_drawable(SDL_Texture *texture, SDL_Rect rect);
Drawable new_drawable_from_file(char path[], SDL_Rect rect, SDL_Renderer *renderer);

void render_drawable(Drawable *drawable, SDL_Renderer *renderer);
void update_drawable(Drawable *drawable);

void destroy_drawable(Drawable *drawable);