#include <iostream>
#include <SDL2/SDL.h>
#include "../graphics/sdl/sdl_pacman_factory.hh"

void displayPacman(PacmanFactory *pacmanFactory) {
    Pacman *pacman = pacmanFactory->createPacman();
}

int main() {
    std::cout << "oi m8" << std::endl;
    PacmanFactory *pacmanFactory = new SDLPacmanFactory();
    displayPacman(pacmanFactory);
}
