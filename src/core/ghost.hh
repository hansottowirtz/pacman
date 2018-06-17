#pragma once

#include "entity.hh"
#include "stdint.h"
#include "./ghost_state.hh"
#include "./ghost_type.hh"
#include "./direction.hh"

class Ghost : public Entity {
    public:
        Ghost(GhostType type);
        GhostType type;
        GhostState state;
        Direction direction;
        Direction wantedDirection;
        virtual void visualize() = 0;
        virtual void initialize() = 0;
        void move();
};
