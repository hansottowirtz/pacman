#pragma once

#include "moving_entity.hh"
#include "stdint.h"
#include "./ghost_state.hh"
#include "./ghost_type.hh"
#include "./direction.hh"
#include "./ai.hh"

class Ghost : public MovingEntity {
    public:
        Ghost(GhostType type);
        GhostType type;
        GhostState state;
        AI* ai;
        bool confused;
        void decideDirection(Direction currentDirection, uint64_t ticks, char surroundings[4], char selfLocation[2], char pacmanLocation[2]);
        void escape();
        void die();
        virtual void visualize() = 0;
        virtual void initialize() = 0;
        uint64_t lastDeadTime;
};
