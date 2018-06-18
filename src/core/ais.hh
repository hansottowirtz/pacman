#pragma once

#include "./ai.hh"
#include "./ghost_type.hh"

class BlinkyAI : public AI {
    public:
        Direction next(Direction currentDirection, uint64_t ticks, char surroundings[4], char selfLocation[2], char pacmanLocation[2]);
};

class PinkyAI : public AI {
    public:
        Direction next(Direction currentDirection, uint64_t ticks, char surroundings[4], char selfLocation[2], char pacmanLocation[2]);
};

class InkyAI : public AI {
    public:
        Direction next(Direction currentDirection, uint64_t ticks, char surroundings[4], char selfLocation[2], char pacmanLocation[2]);
};

class ClydeAI : public AI {
    public:
        Direction next(Direction currentDirection, uint64_t ticks, char surroundings[4], char selfLocation[2], char pacmanLocation[2]);
};
