#include <iostream>
#include "./game.hh"
#include "./level_ref.hh"
#include "../graphics/sdl/sdl_window_factory.hh"
#include "../sprites/sprite_ref.hh"
#include "../sprites/sprite_sizes.hh"
#include "../graphics/sprites/sprite_clips.hh"

Window* window;
Pacman* pacman;
Ghost* ghosts[4];

int gi;

void onTick(uint64_t time, KeyState keys);

int main(int argc, char* argv[]) {
    std::cout << "Starting Pacman" << std::endl;
    WindowFactory *windowFactory = new SDLWindowFactory();
    std::cout << "pc";
    window = windowFactory->createWindow();
    window->open(); // TODO: initialize can't be swapped with open
    window->initialize();
    window->setLevel(LEVEL_CLASSIC);
    pacman = window->getPacman();
    for (gi = 0; gi <= 3; gi++) ghosts[gi] = window->getGhost(static_cast<GhostType>(gi));
    window->loop(onTick);
    window->close();
    return 0;
}

void onTick(uint64_t time, KeyState keys) {
    if (keys.up) {
        pacman->wantedDirection = DIRECTION_UP;
    } else if (keys.down) {
        pacman->wantedDirection = DIRECTION_DOWN;
    } else if (keys.left) {
        pacman->wantedDirection = DIRECTION_LEFT;
    } else if (keys.right) {
        pacman->wantedDirection = DIRECTION_RIGHT;
    }

    if (time % 4 == 0) {
        pacman->state = static_cast<PacmanState>((pacman->state + 1) % 3);
        for (gi = 0; gi <= 3; gi++) ghosts[gi]->state = static_cast<GhostState>((ghosts[gi]->state + 1) % 2);
    }

    size_t cellX = (pacman->x + pacman->w/2)/8;
    size_t cellY = (pacman->y + pacman->h/2)/8;
    size_t wCellX = cellX;
    size_t wCellY = cellY;

    // std::cout << "Pacman is at (";
    // std::cout << pacman->x;
    // std::cout << ",";
    // std::cout << pacman->y;
    // std::cout << ")\t and in cell (";
    // std::cout << cellX;
    // std::cout << ",";
    // std::cout << cellY;
    // std::cout << ")\t with value ";
    // std::cout << window->getLevel()->layout[cellY + 1][cellX + 1];

    Level* level = window->getLevel();

    char currCell = level->layout[cellY + 1][cellX + 1];
    SpriteRef currSprite = level->sprites[cellY][cellX];
    bool onIntersection = pacman->x % 8 == 4 && pacman->y % 8 == 4;

    if (currSprite == SPRITE_BULLET && (pacman->x % 8 == 4 || pacman->y % 8 == 4)) {
        if (!level->captured[cellY][cellX]) {
            level->score++;
            level->captured[cellY][cellX] = true;
        }
    }
    switch (pacman->direction) {
        case DIRECTION_UP:
            cellY -= 1;
            break;
        case DIRECTION_DOWN:
            cellY += 1;
            break;
        case DIRECTION_LEFT:
            cellX -= 1;
            break;
        case DIRECTION_RIGHT:
            cellX += 1;
            break;
        case DIRECTION_NONE:
            break;
    }
    switch(pacman->wantedDirection) {
        case DIRECTION_UP:
            wCellY -= 1;
            break;
        case DIRECTION_DOWN:
            wCellY += 1;
            break;
        case DIRECTION_LEFT:
            wCellX -= 1;
            break;
        case DIRECTION_RIGHT:
            wCellX += 1;
            break;
        case DIRECTION_NONE:
            break;
    }
    char nextCell = level->layout[cellY + 1][cellX + 1];
    char wNextCell = level->layout[wCellY + 1][wCellX + 1];

    // std::cout << "\t and heading to cell with value ";
    // std::cout << level->layout[cellY + 1][cellX + 1];
    // if (onIntersection) std::cout << " and on an intersection";
    std::cout << " and score is ";
    std::cout << level->score;
    std::cout << std::endl;

    bool is180Turn =
        (pacman->direction == DIRECTION_UP && pacman->wantedDirection == DIRECTION_DOWN) ||
        (pacman->direction == DIRECTION_LEFT && pacman->wantedDirection == DIRECTION_RIGHT) ||
        (pacman->direction == DIRECTION_DOWN && pacman->wantedDirection == DIRECTION_UP) ||
        (pacman->direction == DIRECTION_RIGHT && pacman->wantedDirection == DIRECTION_LEFT);

    if (is180Turn || (onIntersection && wNextCell == 'o')) {
        pacman->direction = pacman->wantedDirection;
    }
    bool cornered = onIntersection && nextCell != 'o' && nextCell != 'i';
    if (!cornered) pacman->move();

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

    level->visualize();
    pacman->visualize();
    for (gi = 0; gi <= 3; gi++) ghosts[gi]->visualize();
    level->rerender();
}
