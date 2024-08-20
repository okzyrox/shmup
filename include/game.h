#include "drawable.h"

#include "SDL2/SDL.h"

#include <stdbool.h>

#define MAX_DRAWABLES 255

typedef struct Game {
    SDL_Window *window;
    SDL_Renderer *renderer;

    bool running;

    Drawable *drawables[MAX_DRAWABLES];
    int drawable_count;
} Game;

Game init_game();
void input(Game *game);
void update(Game *game);
void render(Game *game);
void destroy_game(Game *game);
void add_drawable(Game *game, Drawable *drawable);