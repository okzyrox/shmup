#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "stdbool.h"
#include "utils.h"

typedef struct TextUIElement TextUIElement;
typedef struct ButtonUIElement ButtonUIElement;

struct TextUIElement {
    SDL_Rect rect;
    char *text;
    SDL_Color text_color;
    TTF_Font *font;

    void (*update)(TextUIElement *element);
    void (*destroy)(TextUIElement *element);
};

struct ButtonUIElement {
    SDL_Rect rect;
    char *text;
    SDL_Color color;
    SDL_Color pressed_color;

    bool pressed;
    bool hovered;

    void (*update)(ButtonUIElement *element);
    void (*destroy)(ButtonUIElement *element);
};

// Text
TextUIElement new_text_ui_element(SDL_Rect rect, char *text, SDL_Color text_color, TTF_Font *font);

void render_text(TextUIElement *element, SDL_Renderer *renderer);
void set_text(TextUIElement *element, char *text);
void set_text_color(TextUIElement *element, SDL_Color text_color);
void set_font(TextUIElement *element, TTF_Font *font);

// Buttons
ButtonUIElement new_button_ui_element(SDL_Rect rect, char *text, SDL_Color color, SDL_Color pressed_color);

void render_button(ButtonUIElement *element, SDL_Renderer *renderer);
void set_button_text(ButtonUIElement *element, char *text);
void set_button_color(ButtonUIElement *element, SDL_Color color);
void set_button_pressed_color(ButtonUIElement *element, SDL_Color pressed_color);

void set_button_pressed(ButtonUIElement *element, bool pressed);
void set_button_hovered(ButtonUIElement *element, bool hovered);

bool is_button_pressed(ButtonUIElement *element);
bool is_button_hovered(ButtonUIElement *element);

