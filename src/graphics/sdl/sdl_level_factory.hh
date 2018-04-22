#pragma once

#include "../../factories/level_factory.hh"
#include "./sdl_level.hh"

class SDLLevelFactory : public LevelFactory {
    public:
        SDLLevelFactory(SDLWindow* window);
        Level* createLevel(MapRef ref);
    private:
        SDLWindow* window;
};
