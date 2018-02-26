#include <iostream>
#include <SDL.h>
#include "../graphics/sdl/sdl_pacman_factory.hh"

int main() {
    std::cout << "oi m8" << std::endl;
    PacmanFactory* pacmanFactory = new SDLPacmanFactory;
}