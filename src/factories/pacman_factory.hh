#pragma once

#include "../core/pacman.hh"

class PacmanFactory {
    public:
        PacmanFactory();
        virtual Pacman *createPacman() = 0;
};
