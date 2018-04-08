#pragma once

#include "../../factories/pacman_factory.hh"
#include "./sdl_window.hh"

class SDLPacmanFactory : public PacmanFactory {
    public:
        SDLPacmanFactory(SDLWindow window);
        Pacman* createPacman();
    private:
        SDLWindow window;
};
