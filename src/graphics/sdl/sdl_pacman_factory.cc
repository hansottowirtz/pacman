#include "./sdl_pacman_factory.hh"
#include "./sdl_pacman.hh"

Pacman* SDLPacmanFactory::createPacman() {
    return new SDLPacman;
}
