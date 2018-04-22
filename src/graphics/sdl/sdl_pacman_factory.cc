#include "sdl_pacman_factory.hh"
#include "sdl_pacman.hh"
#include "sdl_window.hh"

SDLPacmanFactory::SDLPacmanFactory(SDLWindow* window) {
    this->window = window;
}

Pacman* SDLPacmanFactory::createPacman() {
    return new SDLPacman(this->window);
}
