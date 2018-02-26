#include "../core/pacman.hh"

class PacmanFactory {
    virtual Pacman* createPacman() = 0;
};