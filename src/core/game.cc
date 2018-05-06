#include <iostream>
#include "./game.hh"
#include "../graphics/sdl/sdl_window_factory.hh"
#include "../graphics/sdl/sdl_level_factory.hh"
#include "../graphics/sdl/sdl_pacman_factory.hh"
#include "../graphics/sprites/sprite_ref.hh"
#include "../graphics/sprites/sprite_sizes.hh"
#include "../graphics/sprites/sprite_clips.hh"

Window* window;
Pacman* pacman;

void onTick(uint64_t time, KeyState keys);

int main(int argc, char* argv[]) {
    std::cout << "Starting Pacman" << std::endl;
    WindowFactory *windowFactory = new SDLWindowFactory();
    window = windowFactory->createWindow();
    window->open(); // TODO: initialize can't be swapped with open
    window->initialize();
    window->setMap(MAP_PACMAN);
    // levelFactory->createLevel(MAP_PACMAN)->visualize();
    // Pacman *pacman = pacmanFactory->createPacman();
    // pacman->visualize();
    pacman = window->getPacman();
    window->loop(onTick);
    window->close();
    return 0;
}

void onTick(uint64_t time, KeyState keys) {
    if (keys.up) {
        pacman->direction = DIRECTION_UP;
    } else if (keys.down) {
        pacman->direction = DIRECTION_DOWN;
    } else if (keys.left) {
        pacman->direction = DIRECTION_LEFT;
    } else if (keys.right) {
        pacman->direction = DIRECTION_RIGHT;
    }

    if (time % 4 == 0) {
        pacman->state = static_cast<PacmanState>((pacman->state + 1) % 3);
    }

    pacman->move();

    if (pacman->x <= -pacman->w) {
        pacman->x = window->w;
    } else if (pacman->x >= window->w) {
        pacman->x = -pacman->w;
    }
    if (pacman->y <= -pacman->h) {
        pacman->y = window->h;
    } else if (pacman->y >= window->h) {
        pacman->y = -pacman->h;
    }

    pacman->visualize();
}
