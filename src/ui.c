#include "ui.h"

#include "SDL2/SDL.h"
#include "SDL2/SDL_mouse.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_image.h"

#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

// UI elements

// text
void update_text(TextUIElement *element) {
    // nothing to do here by default
}

void destroy_text(TextUIElement *element) {
    free(element->text);
}

TextUIElement new_text_ui_element(SDL_Rect rect, char *text, SDL_Color text_color, TTF_Font *font) {
    TextUIElement element;
    element.rect = rect;
    element.text = text;
    element.text_color = text_color;
    element.font = font;
    element.update = update_text;
    element.destroy = destroy_text;
    return element;
}


void render_text(TextUIElement *element, SDL_Renderer *renderer) {
    SDL_Surface *surface = TTF_RenderUTF8_Blended(element->font, element->text, element->text_color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_RenderCopy(renderer, texture, NULL, &element->rect);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

void set_text(TextUIElement *element, char *text) {
    element->text = text;
}

void set_text_color(TextUIElement *element, SDL_Color text_color) {
    element->text_color = text_color;
}

void set_font(TextUIElement *element, TTF_Font *font) {
    element->font = font;
}


// button

void update_button(ButtonUIElement *element) {
    int mouse_x, mouse_y;
    SDL_GetMouseState(&mouse_x, &mouse_y);
    SDL_Point point = {mouse_x, mouse_y};
    element->hovered = SDL_PointInRect(&point, &element->rect);
}

void destroy_button(ButtonUIElement *element) {
    free(element->text);
}

ButtonUIElement new_button_ui_element(SDL_Rect rect, char *text, SDL_Color color, SDL_Color pressed_color) {
    ButtonUIElement element;
    element.rect = rect;
    element.text = text;
    element.color = color;
    element.pressed_color = pressed_color;
    element.pressed = false;
    element.hovered = false;
    element.update = update_button;
    element.destroy = destroy_button;
    return element;
}

void render_button(ButtonUIElement *element, SDL_Renderer *renderer) {
    if (element->hovered) {
        SDL_SetRenderDrawColor(renderer, element->color.r, element->color.g, element->color.b, element->color.a);
    } else {
        SDL_SetRenderDrawColor(renderer, element->pressed_color.r, element->pressed_color.g, element->pressed_color.b, element->pressed_color.a);
    }
    SDL_RenderFillRect(renderer, &element->rect);
}

void set_button_text(ButtonUIElement *element, char *text) {
    element->text = text;
}

void set_button_color(ButtonUIElement *element, SDL_Color color) {
    element->color = color;
}

void set_button_pressed(ButtonUIElement *element, bool pressed) {
    element->pressed = pressed;
}

void set_button_hovered(ButtonUIElement *element, bool hovered) {
    element->hovered = hovered;
}