#include "drawable.h"
#include "utils.h"

#include "SDL2/SDL.h"

#include <stdbool.h>

#define MAX_DRAWABLES 255

typedef struct Game {
    SDL_Window *window;
    SDL_Renderer *renderer;

    bool running;
    bool fullscreen;

    Drawable *drawables[MAX_DRAWABLES];
    int drawable_count;
} Game;

Game init_game();
void input(Game *game);
void update(Game *game);
void render(Game *game);
void destroy_game(Game *game);
void add_drawable(Game *game, Drawable *drawable);

IntTuple get_resolution(Game *game);

void set_resolution(Game *game, int width, int height);
void set_fullscreen(Game *game, bool fullscreen);