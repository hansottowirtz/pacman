#include "sdl_ghost.hh"
#include "sdl_sprite_util.hh"
#include "../sprites/sprite_clips.hh"
#include "../../sprites/sprite_ref.hh"
#include "../../sprites/sprite_path_util.hh"
#include <string>
#include <iostream>

SDLGhost::SDLGhost(SDLWindow* window, GhostType type) : Ghost::Ghost(type) {
    this->window = window;
    // this->loadTexture();
}

void SDLGhost::initialize() {
}

void SDLGhost::visualize() {
    SDL_Rect clip;
    SpriteRef sprite;

    switch (this->wantedDirection) {
        case DIRECTION_LEFT:
            sprite = SPRITE_GHOST_BLINKY_TO_LEFT_LEGS_OPEN;
            break;
        case DIRECTION_RIGHT:
            sprite = SPRITE_GHOST_BLINKY_TO_RIGHT_LEGS_OPEN;
            break;
        case DIRECTION_UP:
            sprite = SPRITE_GHOST_BLINKY_TO_UP_LEGS_OPEN;
            break;
        case DIRECTION_DOWN:
        case DIRECTION_NONE:
            sprite = SPRITE_GHOST_BLINKY_TO_DOWN_LEGS_OPEN;
            break;
    }
    if (this->confused) sprite = SPRITE_GHOST_CONFUSED_LEGS_OPEN;
    if (this->state == GHOST_LEGS_CLOSED) {
        sprite = static_cast<SpriteRef>(static_cast<int>(sprite + 1));
    }
    if (!this->confused) sprite = static_cast<SpriteRef>(static_cast<int>(sprite + this->type * 8));

    clip = SDLSpriteUtil::clipToRect(SpriteClips::get(sprite));

    SDL_Rect dest;
    dest.x = this->x * this->window->M;
    dest.y = this->y * this->window->M;
    dest.w = clip.w * this->window->M;
    dest.h = clip.h * this->window->M;

    SDL_RenderCopy(
        this->window->sdlRenderer,
        this->window->sdlSpritesheet,
        &clip,
        &dest);
}
