#pragma once

#include "../../core/pacman.hh"
#include "./sdl_window.hh"

class SDLPacman : public Pacman {
    public:
        SDLPacman(SDLWindow window);
        void visualize() {};
};
