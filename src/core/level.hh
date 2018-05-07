#pragma once

#include "./map_ref.hh"
#include "./level_ref.hh"
#include <string>

class Level {
    public:
        LevelRef ref;
        Level(LevelRef ref);
        virtual void visualize() = 0;
};
