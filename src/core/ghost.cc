#include "./ghost.hh"
#include "./direction.hh"
#include "./ai_factory.hh"
#include "../sprites/sprite_sizes.hh"
#include <iostream>

Ghost::Ghost(GhostType type) {
    this->x = 4 + 8 * 11 + 8 * type;
    this->y = 4 + 8 * 13;
    SpriteSize size = SpriteSizes::get(SPRITE_GHOST_BLINKY_TO_DOWN_LEGS_CLOSED);
    this->w = size.w;
    this->h = size.h;
    this->direction = DIRECTION_DOWN;
    this->wantedDirection = DIRECTION_DOWN;
    this->state = GHOST_LEGS_CLOSED;
    this->type = type;
    AIFactory* factory = new AIFactory;
    this->ai = factory->createAI(type);
    this->confused = false;
    this->lastDeadTime = 0;
}

void Ghost::decideDirection(Direction currentDirection, uint64_t ticks, char surroundings[4], char selfLocation[2], char pacmanLocation[2]) {
    // if (this->confused) {
    //     if (ticks % 100) {
    //         int r = std::rand() % 4;
    //         this->wantedDirection = static_cast<Direction>(r);
    //     }
    // } else {
        this->wantedDirection = this->ai->next(currentDirection, ticks, surroundings, selfLocation, pacmanLocation);
    // }
}

void Ghost::escape() {
    this->y -= 8 * 4;
}

void Ghost::die() {
    this->x = 4 + 8 * 11 + 8 * type;
    this->y = 4 + 8 * 13;
}
