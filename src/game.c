#include "game.h"
#include "constants.h"

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_image.h"

#include <stdbool.h>
#include <stdio.h>

Game init_game() {
    Game game;
    game.running = true;
    game.fullscreen = false;

    game.delta_time = 0.0f;
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
        if (TTF_Init() == -1) {
            printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        }
    }
    game.ui_element_count = 0;
    game.drawable_count = 0;
    game.last_update_time = SDL_GetPerformanceCounter();
    return game;
}

void input(Game *game) {
    printf("Input\n");
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
    printf("Update\n");
    Uint64 current_time = SDL_GetPerformanceCounter();
    game->delta_time = (float)(current_time - game->last_update_time) / SDL_GetPerformanceFrequency();
    game->last_update_time = current_time;
    // do update stuff here 
    
    for (int i = 0; i < game->ui_element_count; i++) {
        if (game->ui_elements.text_elements[i] != NULL) {
            game->ui_elements.text_elements[i]->update(game->ui_elements.text_elements[i]);
        }
        if (game->ui_elements.button_elements[i] != NULL) {
            game->ui_elements.button_elements[i]->update(game->ui_elements.button_elements[i]);
        }
    }
    
}

void add_drawable(Game *game, Drawable *drawable) {
    game->drawables[game->drawable_count] = drawable;
    game->drawable_count++;
}

void add_text_element(Game *game, TextUIElement *text_ui) {
    game->ui_elements.text_elements[game->ui_element_count] = text_ui;
    game->ui_element_count++;
}

void add_button_element(Game *game, ButtonUIElement *button_ui) {
    game->ui_elements.button_elements[game->ui_element_count] = button_ui;
    game->ui_element_count++;
}

void render(Game *game) {
    printf("Render\n");
    SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
    SDL_RenderClear(game->renderer);
    for (int i = 0; i < game->drawable_count; i++) {
        render_drawable(game->drawables[i], game->renderer);
    }
    
    for (int i = 0; i < game->ui_element_count; i++) {
        if (game->ui_elements.text_elements[i] != NULL && game->ui_elements.text_elements[i]->font != NULL) {
            render_text(game->ui_elements.text_elements[i], game->renderer);
        }
        if (game->ui_elements.button_elements[i] != NULL) {
            render_button(game->ui_elements.button_elements[i], game->renderer);
        }
    }
    
    SDL_RenderPresent(game->renderer);
}

void destroy_game(Game *game) {
    printf("Destroying game..\n Goodbye!");
    for (int i = 0; i < game->ui_element_count; i++) {
        if (game->ui_elements.text_elements[i] != NULL) {
            game->ui_elements.text_elements[i]->destroy(game->ui_elements.text_elements[i]);
            free(game->ui_elements.text_elements[i]);
        }
        if (game->ui_elements.button_elements[i] != NULL) {
            game->ui_elements.button_elements[i]->destroy(game->ui_elements.button_elements[i]);
            free(game->ui_elements.button_elements[i]);
        }
    }
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