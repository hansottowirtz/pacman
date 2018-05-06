#include "SDL_image.h"
#include "./sdl_level.hh"
#include "./sdl_window.hh"
#include "../../sprites/sprite_path_util.hh"
#include <string>

SDLLevel::SDLLevel(SDLWindow* window, MapRef mapRef) : Level::Level(mapRef) {
    this->window = window;
}

void SDLLevel::visualize() {
    SDL_Surface* optimizedSurface = NULL;

    std::string path = SpritePathUtil::getMapSpritePath(this->mapRef);

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL) {
        printf("IMG_Load error: (%s) %s\n", path.c_str(), IMG_GetError());
        return;
    }

    //Convert surface to screen format
    optimizedSurface = SDL_ConvertSurface(loadedSurface, this->window->sdlScreenSurface->format, 0);
    if (optimizedSurface == NULL) {
        printf("SDL_ConvertSurface error: (%s) %s\n", path.c_str(), SDL_GetError());
        return;
    }

    SDL_FreeSurface(loadedSurface);
    SDL_Texture* background = SDL_CreateTextureFromSurface(this->window->sdlRenderer, optimizedSurface);
    SDL_FreeSurface(optimizedSurface);

    SDL_Rect dest;
    dest.x = 0;
    dest.y = 0;
    dest.w = 224 * this->window->M;
    dest.h = 248 * this->window->M;

    SDL_RenderCopy(
        this->window->sdlRenderer,
        background,
        &dest,
        &dest);

    SDL_UpdateWindowSurface(this->window->sdlWindow);
}
