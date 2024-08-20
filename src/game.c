#include "game.h"
#include "constants.h"

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include <stdbool.h>
#include <stdio.h>

Game init_game() {
    Game game;
    game.running = true;
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    }
    else {
        game.window = SDL_CreateWindow("shmup", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
        if (game.window == NULL)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        }
        game.renderer = SDL_CreateRenderer(game.window, -1, SDL_RENDERER_ACCELERATED);
        if (game.renderer == NULL)
        {
            printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        }
        int imgFlags = IMG_INIT_PNG;
        if( !( IMG_Init( imgFlags ) & imgFlags ) )
        {
            printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
        }
    }
    return game;
}

void input(Game *game) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            game->running = false;
        }
        else if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                game->running = false;
            }
        }
    }
}

void update(Game *game) {
}

void add_drawable(Game *game, Drawable *drawable) {
    game->drawables[game->drawable_count] = drawable;
    game->drawable_count++;
}

void render(Game *game) {
    for (int i = 0; i < game->drawable_count; i++) {
        render_drawable(game->drawables[i], game->renderer);
    }
    SDL_RenderPresent(game->renderer);
    //SDL_UpdateWindowSurface(game->window);
}

void destroy_game(Game *game) {
    printf("Destroying game..\n Goodbye!");
    SDL_DestroyRenderer(game->renderer);
    SDL_DestroyWindow(game->window);
    SDL_Quit();
}