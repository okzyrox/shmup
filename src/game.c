#include "game.h"
#include "constants.h"

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include <stdbool.h>
#include <stdio.h>

Game init_game() {
    Game game;
    game.running = true;
    game.fullscreen = false;
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    }
    else {
        game.window = SDL_CreateWindow("shmup", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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
            else if (event.key.keysym.sym == SDLK_F11) {
                set_fullscreen(game, !game->fullscreen);
                printf("Fullscreen: %d\n", game->fullscreen);
            }
            else if (event.key.keysym.sym == SDLK_UP) {
                IntTuple resolution = get_resolution(game);
                set_resolution(game, resolution.x + 100, resolution.y + 100);
                printf("New resolution: %d %d\n", resolution.x + 100, resolution.y + 100);
            }
            else if (event.key.keysym.sym == SDLK_DOWN) {
                IntTuple resolution = get_resolution(game);
                set_resolution(game, resolution.x - 100, resolution.y - 100);
                printf("New resolution: %d %d\n", resolution.x - 100, resolution.y - 100);
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

// Util funcs

IntTuple get_resolution(Game *game) {
    IntTuple resolution;
    SDL_GetWindowSize(game->window, &resolution.x, &resolution.y);
    return resolution;
}

void set_resolution(Game *game, int width, int height) {
    SDL_SetWindowSize(game->window, width, height);
}

void set_fullscreen(Game *game, bool fullscreen) {
    bool new_fullscreen = fullscreen ? SDL_WINDOW_FULLSCREEN : 0;
    SDL_SetWindowFullscreen(game->window, new_fullscreen);
    game->fullscreen = fullscreen;
}