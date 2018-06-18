#pragma once

#include "./direction.hh"
#include "inttypes.h"

class AI {
    public:
        virtual Direction next(Direction currentDirection, uint64_t ticks, char surroundings[4], char selfLocation[2], char pacmanLocation[2]) = 0;
};
