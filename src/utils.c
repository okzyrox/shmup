#include "utils.h"
#include "stdbool.h"
#include "SDL2/SDL.h"

// used for uibutton stuff
// hover, etc
bool point_in_rect(SDL_Point point, SDL_Rect rect) {
    return (
        point.x >= rect.x && 
        point.x <= rect.x + rect.w && 
        point.y >= rect.y && 
        point.y <= rect.y + rect.h
    );
}