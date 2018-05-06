#include "./pacman.hh"
#include "./direction.hh"
#include "../graphics/sprites/sprite_sizes.hh"
#include <iostream>

Pacman::Pacman() {
    this->x = 4;
    this->y = 4;
    SpriteSize size = SpriteSizes::get(SPRITE_PACMAN_IMMOBILE);
    this->w = size.w;
    this->h = size.h;
    this->direction = DIRECTION_NONE;
    this->wantedDirection = DIRECTION_NONE;
    this->state = PACMAN_STATE_CLOSED;
}

void Pacman::move() {
    switch (this->direction) {
        case DIRECTION_LEFT:
            this->x -= 1;
            break;
        case DIRECTION_RIGHT:
            this->x += 1;
            break;
        case DIRECTION_UP:
            this->y -= 1;
            break;
        case DIRECTION_DOWN:
            this->y += 1;
            break;
        case DIRECTION_NONE:
            break;
    }

}
