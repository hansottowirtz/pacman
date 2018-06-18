#pragma once

#include "moving_entity.hh"
#include "stdint.h"
#include "./pacman_state.hh"
#include "./direction.hh"

class Pacman : public MovingEntity {
    public:
        Pacman();
        PacmanState state;
        Direction wantedDirection;
        virtual void visualize() = 0;
        virtual void initialize() = 0;
};
