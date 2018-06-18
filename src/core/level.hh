#pragma once

#include "./map_ref.hh"
#include "./level_ref.hh"
#include "../sprites/sprite_ref.hh"
#include <string>

class Level {
    public:
        LevelRef ref;
        Level(LevelRef ref);
        virtual void visualize() = 0;
        virtual void rerender() = 0;
        char layout[248 / 8 + 2][224 / 8 + 2];
        SpriteRef sprites[248 / 8][224 / 8];
        int score;
        bool captured[248 / 8][224 / 8];
        char livesLeft;
};
