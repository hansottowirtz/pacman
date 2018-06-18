#include "./ais.hh"
#include "inttypes.h"
#include <cstdlib>

char cellInDirection(Direction direction, char surroundings[4]) {
    return direction == DIRECTION_NONE ? 'x' : surroundings[direction];
}

Direction BlinkyAI::next(Direction currentDirection, uint64_t ticks, char surroundings[4], char selfLocation[2], char pacmanLocation[2]) {
    if (ticks % 20) return currentDirection;
    char c = cellInDirection(currentDirection, surroundings);
    int n = std::rand() % 2 + 1;
    return c != 'o' && c != 'n' ? static_cast<Direction>((currentDirection + n) % 4) : currentDirection;
}

Direction PinkyAI::next(Direction currentDirection, uint64_t ticks, char surroundings[4], char selfLocation[2], char pacmanLocation[2]) {
    if (ticks % 33) return currentDirection;
    char c = cellInDirection(currentDirection, surroundings);
    int n = std::rand() % 2 + 1;
    return c != 'o' && c != 'n' ? static_cast<Direction>((currentDirection + n) % 4) : currentDirection;
}

Direction InkyAI::next(Direction currentDirection, uint64_t ticks, char surroundings[4], char selfLocation[2], char pacmanLocation[2]) {
    if (ticks % 49) return currentDirection;
    char c = cellInDirection(currentDirection, surroundings);
    int n = std::rand() % 2 + 1;
    return c != 'o' && c != 'n' ? static_cast<Direction>((currentDirection + n) % 4) : currentDirection;
}

Direction ClydeAI::next(Direction currentDirection, uint64_t ticks, char surroundings[4], char selfLocation[2], char pacmanLocation[2]) {
    if (ticks % 27) return currentDirection;
    char c = cellInDirection(currentDirection, surroundings);
    int n = std::rand() % 2 + 1;
    return c != 'o' && c != 'n' ? static_cast<Direction>((currentDirection + n) % 4) : currentDirection;
}
