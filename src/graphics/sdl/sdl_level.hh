#pragma once

#include "../../core/level.hh"
#include "../../core/map_ref.hh"
#include "./sdl_window.hh"
#include <string>

class SDLLevel : public Level {
    public:
        SDLLevel(LevelRef ref);
        void setWindow(SDLWindow* window);
        void setLevel(MapRef mapRef);
        void visualize();
    private:
        SDLWindow* window;
};
