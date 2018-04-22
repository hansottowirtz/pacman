#include "./pacman.hh"
#include "./direction.hh"
#include <iostream>

Pacman::Pacman() {
    this->x = 0;
    this->y = 0;
    this->direction = DIRECTION_NONE;
    this->open = false;
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
