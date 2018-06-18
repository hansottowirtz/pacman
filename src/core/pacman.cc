#include "./pacman.hh"
#include "./direction.hh"
#include "../sprites/sprite_sizes.hh"
#include <iostream>

Pacman::Pacman() {
    this->x = 13 * 8;
    this->y = 4 + 22 * 8;
    SpriteSize size = SpriteSizes::get(SPRITE_PACMAN_IMMOBILE);
    this->w = size.w;
    this->h = size.h;
    this->direction = DIRECTION_NONE;
    this->wantedDirection = DIRECTION_NONE;
    this->state = PACMAN_STATE_CLOSED;
}

void Pacman::die() {
    this->x = 13 * 8;
    this->y = 4 + 22 * 8;
    this->direction = DIRECTION_NONE;
    this->wantedDirection = DIRECTION_NONE;
}
