#include "drawable.h"
#include "ui.h"

#include "SDL2/SDL.h"

#include <stdbool.h>

#define MAX_DRAWABLES 255
#define MAX_UI_ELEMENTS 255

typedef struct UIElements {
    TextUIElement *text_elements[MAX_UI_ELEMENTS];
    ButtonUIElement *button_elements[MAX_UI_ELEMENTS];
} UIElements;

typedef struct Game {
    SDL_Window *window;
    SDL_Renderer *renderer;

    bool running;
    bool fullscreen;

    Drawable *drawables[MAX_DRAWABLES];
    int drawable_count;

    UIElements ui_elements;
    int ui_element_count;

    Uint64 last_update_time;
    float delta_time;
} Game;

Game init_game();
void input(Game *game);
void update(Game *game);
void render(Game *game);
void destroy_game(Game *game);
void add_drawable(Game *game, Drawable *drawable);
void add_text_element(Game *game, TextUIElement *element);
void add_button_element(Game *game, ButtonUIElement *element);

IntTuple get_resolution(Game *game);

void set_resolution(Game *game, int width, int height);
void set_fullscreen(Game *game, bool fullscreen);