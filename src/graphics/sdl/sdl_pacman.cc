#include "SDL_image.h"
#include "sdl_pacman.hh"
#include "sdl_sprite_util.hh"
#include "../sprites/sprite_clips.hh"
#include "../../sprites/sprite_ref.hh"
#include <string>
#include <iostream>

SDLPacman::SDLPacman(SDLWindow* window) : Pacman::Pacman() {
    this->window = window;
    // this->loadTexture();
}

void SDLPacman::initialize() {
    //The final optimized image
    SDL_Surface* optimizedSurface = NULL;

    std::string path = "./res/sprites/spritesheet.png";

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

    //Get rid of old loaded surface
    SDL_FreeSurface(loadedSurface);

    SDL_Texture* spritesheet = SDL_CreateTextureFromSurface(this->window->sdlRenderer, optimizedSurface);
    SDL_FreeSurface(optimizedSurface);

    this->spritesheet = spritesheet;
}

SDL_Rect clip;
SpriteRef sprite = SPRITE_PACMAN_IMMOBILE;

void SDLPacman::visualize() {
    if (this->direction == DIRECTION_NONE) {
        sprite = SPRITE_PACMAN_IMMOBILE;
    } else {
        if (this->state == PACMAN_STATE_CLOSED) {
            sprite = SPRITE_PACMAN_IMMOBILE;
        } else {
            switch (this->direction) {
                case DIRECTION_LEFT:
                    sprite = SPRITE_PACMAN_TO_LEFT_OPEN;
                    break;
                case DIRECTION_RIGHT:
                    sprite = SPRITE_PACMAN_TO_RIGHT_OPEN;
                    break;
                case DIRECTION_UP:
                    sprite = SPRITE_PACMAN_TO_UP_OPEN;
                    break;
                case DIRECTION_DOWN:
                    sprite = SPRITE_PACMAN_TO_DOWN_OPEN;
                    break;
                case DIRECTION_NONE:
                    break;
            }
            if (this->state == PACMAN_STATE_HALF_OPEN) {
                sprite = static_cast<SpriteRef>(static_cast<int>(sprite + 1));
            }
        }
    }

    clip = SDLSpriteUtil::clipToRect(SpriteClips::get(sprite));

    SDL_Rect dest;
    dest.x = this->x * this->window->M;
    dest.y = this->y * this->window->M;
    dest.w = clip.w * this->window->M;
    dest.h = clip.h * this->window->M;

    // for(int i = 0; i < 10; i++) {
    //     SDL_Rect clip = SDLSpriteUtil::clipToRect(SpriteClips::get((SpriteRef) i));
    //     SDL_RenderCopy(
    //         this->window->sdlRenderer,
    //         texture,
    //         &clip,
    //         &dest);
    //     dest.x += 12;
    // }

    SDL_RenderCopy(
        this->window->sdlRenderer,
        this->spritesheet,
        &clip,
        &dest);

    // SDL_BlitScaled(optimizedSurface, NULL, this->window->sdlScreenSurface, &stretchRect);
    SDL_UpdateWindowSurface(this->window->sdlWindow);
}
