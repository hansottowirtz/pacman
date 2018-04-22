#pragma once

#include "../core/level.hh"

class LevelFactory {
    public:
        LevelFactory();
        virtual Level *createLevel(MapRef ref) = 0;
};
