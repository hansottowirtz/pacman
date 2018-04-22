#pragma once

#include "entity.hh"
#include "stdint.h"
#include "./direction.hh"

class Pacman : public Entity {
    public:
        Pacman();
        uint16_t x;
        uint16_t y;
        bool open;
        Direction direction;
        virtual void visualize() = 0;
        virtual void initialize() = 0;
        void move();
};
