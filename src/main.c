#include <stdio.h>
#include <stdbool.h>
#include "SDL2/SDL.h"

#include "game.h"
//#include "drawable.h"
#include "constants.h"

Game game;
SDL_Surface *screenSurface;

int main(int argc, char *argv[])
{
    game = init_game();
    screenSurface = SDL_GetWindowSurface(game.window);

    Drawable drawable = new_drawable_from_file("resources/grass.png", (SDL_Rect){0, 0, 100, 100}, game.renderer);
    add_drawable(&game, &drawable);

    //SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));


    while (game.running)
    {
        input(&game);
        update(&game);
        render(&game);
    }

    destroy_game(&game);
    return 0;
}