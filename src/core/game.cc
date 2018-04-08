#include <iostream>
#include "../graphics/sdl/sdl_pacman_factory.hh"

void displayPacman(PacmanFactory *pacmanFactory) {
    Pacman *pacman = pacmanFactory->createPacman();
    pacman->visualize();
}

int main(int argc, char* argv[]) {
    std::cout << "Starting Pacman" << std::endl;
    SDLWindow *window = new SDLWindow();
    SDLPacmanFactory *pacmanFactory = new SDLPacmanFactory(*window);
    window->open();
    displayPacman(pacmanFactory);
    return 0;
}
