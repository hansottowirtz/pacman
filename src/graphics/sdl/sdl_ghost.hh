#pragma once

#include "../../core/ghost.hh"
#include "./sdl_window.hh"

class SDLGhost : public Ghost {
    public:
        SDLGhost(SDLWindow* window, GhostType type);
        void initialize();
        void visualize();
    private:
        SDLWindow* window;
};
