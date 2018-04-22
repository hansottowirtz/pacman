#include <iostream>
#include "./map_ref.hh"
#include "./key_state.hh"
#include "../graphics/sdl/sdl_window_factory.hh"
#include "../graphics/sdl/sdl_level_factory.hh"
#include "../graphics/sdl/sdl_pacman_factory.hh"
#include "../graphics/sprites/sprite_ref.hh"
#include "../graphics/sprites/sprite_sizes.hh"
#include "../graphics/sprites/sprite_clips.hh"

void onTick(uint64_t time, KeyState keys);

Pacman* pacman;

int main(int argc, char* argv[]) {
    std::cout << "Starting Pacman" << std::endl;
    WindowFactory *windowFactory = new SDLWindowFactory();
    Window *window = windowFactory->createWindow();
    window->open(); // TODO: initialize can't be swapped with open
    window->initialize();
    // window->setMap(MAP_PACMAN);
    // LevelFactory *levelFactory = new SDLLevelFactory(window);
    // PacmanFactory *pacmanFactory = new SDLPacmanFactory(window);
    // levelFactory->createLevel(MAP_PACMAN)->visualize();
    // Pacman *pacman = pacmanFactory->createPacman();
    // pacman->visualize();
    pacman = window->getPacman();
    window->loop(onTick);
    window->close();
    return 0;
}

void onTick(uint64_t time, KeyState keys) {
    std::cout << time << std::endl;
    if (keys.up) {
        pacman->direction = DIRECTION_UP;
    } else if (keys.down) {
        pacman->direction = DIRECTION_DOWN;
    } else if (keys.left) {
        pacman->direction = DIRECTION_LEFT;
    } else if (keys.right) {
        pacman->direction = DIRECTION_RIGHT;
    }

    if (time % 4 == 0) pacman->open = !pacman->open;

    pacman->move();
    pacman->visualize();
}
