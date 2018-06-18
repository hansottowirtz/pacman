#include "./moving_entity.hh"

void MovingEntity::move() {
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
