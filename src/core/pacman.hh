#pragma once

#include "entity.hh"
#include "stdint.h"
#include "./pacman_state.hh"
#include "./direction.hh"

class Pacman : public Entity {
    public:
        Pacman();
        PacmanState state;
        Direction direction;
        Direction wantedDirection;
        virtual void visualize() = 0;
        virtual void initialize() = 0;
        void move();
};
