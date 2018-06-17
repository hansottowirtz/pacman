#include "./ghost.hh"
#include "./direction.hh"
#include "../sprites/sprite_sizes.hh"
#include <iostream>

Ghost::Ghost(GhostType type) {
    this->x = 4 + 8 * 11 + 8 * type;
    this->y = 4 + 8 * 13;
    SpriteSize size = SpriteSizes::get(SPRITE_GHOST_BLINKY_TO_DOWN_LEGS_CLOSED);
    this->w = size.w;
    this->h = size.h;
    this->direction = DIRECTION_NONE;
    this->wantedDirection = DIRECTION_NONE;
    this->state = GHOST_LEGS_CLOSED;
    this->type = type;
}

void Ghost::move() {
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
