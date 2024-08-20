#include <stdio.h>
#include <stdbool.h>
#include "SDL2/SDL.h"

#include "game.h"
//#include "drawable.h"
#include "constants.h"

Game game;
SDL_Surface *screenSurface;
TTF_Font *font;

int main(int argc, char *argv[])
{
    game = init_game();
    screenSurface = SDL_GetWindowSurface(game.window);

    font = TTF_OpenFont("resources/Roboto-Regular.ttf", 24);
    if (font == NULL) {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        return 1;
    }

    Drawable drawable = new_drawable_from_file("resources/grass.png", (SDL_Rect){0, 0, 100, 100}, game.renderer);
    add_drawable(&game, &drawable);

    //TextUIElement text = new_text_ui_element((SDL_Rect){0, 0, 100, 100}, "Hello, World!", (SDL_Color){0, 0, 0, 255}, font);
    //add_text_element(&game, &text);

    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));


    while (game.running)
    {
        input(&game);
        update(&game);
        render(&game);
        
    }

    TTF_CloseFont(font);
    destroy_game(&game);
    return 0;
}