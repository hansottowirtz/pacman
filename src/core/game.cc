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
uint64_t CONFUSION_DELAY = 500;

int ei;
int gi;
uint64_t confusionTime = 0;
bool stop = false;

void onTick(uint64_t time, KeyState keys);
void checkWrapAround(Entity* entity, Window* window);
bool is180Turn(Direction d1, Direction d2);

int main(int argc, char* argv[]) {
    std::cout << "Starting Pacman" << std::endl;
    WindowFactory *windowFactory = new SDLWindowFactory();
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
    if (stop) return;

    Level* level = window->getLevel();

    // Keyboard event handling
    if (keys.up) {
        pacman->wantedDirection = DIRECTION_UP;
    } else if (keys.down) {
        pacman->wantedDirection = DIRECTION_DOWN;
    } else if (keys.left) {
        pacman->wantedDirection = DIRECTION_LEFT;
    } else if (keys.right) {
        pacman->wantedDirection = DIRECTION_RIGHT;
    }

    // State changes (visual)
    if (time % 4 == 0) {
        pacman->state = static_cast<PacmanState>((pacman->state + 1) % 3);
        for (gi = 0; gi <= 3; gi++) ghosts[gi]->state = static_cast<GhostState>((ghosts[gi]->state + 1) % 2);
    }

    // Ghost escaping
    for (gi = 0; gi <= 3; gi++) {
        Ghost* ghost = ghosts[gi];
        if (ghost->lastDeadTime == 0) {
            if (time == 100 * (gi + 2)) ghost->escape();
        } else {
            if (time - ghost->lastDeadTime == 200) ghost->escape();
        }
    }

    size_t cellX = (pacman->x + pacman->w/2)/8;
    size_t cellY = (pacman->y + pacman->h/2)/8;
    size_t wCellX = cellX;
    size_t wCellY = cellY;

    // char currCell = level->layout[cellY + 1][cellX + 1];
    SpriteRef currSprite = level->sprites[cellY][cellX];
    bool onIntersection = pacman->x % 8 == 4 && pacman->y % 8 == 4;

    if (pacman->x % 8 == 4 || pacman->y % 8 == 4) {
        if (!level->captured[cellY][cellX]) {
            if (currSprite == SPRITE_BULLET) {
                level->score += 10;
                level->captured[cellY][cellX] = true;
            } else if (currSprite == SPRITE_POWERUP) {
                std::cout << "powerup" << std::endl;
                level->captured[cellY][cellX] = true;
                confusionTime = time;
                for (gi = 0; gi <= 3; gi++) ghosts[gi]->confused = true;
            }
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
    // std::cout << "\t and heading to cell with value ";
    // std::cout << level->layout[cellY + 1][cellX + 1];
    // if (onIntersection) std::cout << " and on an intersection";
    // std::cout << " and score is ";
    // std::cout << level->score;
    // std::cout << std::endl;

    if (is180Turn(pacman->direction, pacman->wantedDirection) || ((onIntersection || pacman->direction == DIRECTION_NONE) && wNextCell == 'o')) {
        pacman->direction = pacman->wantedDirection;
    }
    bool cornered = onIntersection && nextCell != 'o' && nextCell != 'i';
    if (!cornered) pacman->move();

    checkWrapAround(pacman, window);

    for (gi = 0; gi <= 3; gi++) {
        Ghost* ghost = ghosts[gi];

        if (ghost->confused) {
            ghost->confused = (time - confusionTime) < CONFUSION_DELAY && confusionTime > 0;
        }

        size_t cellX = (ghost->x + ghost->w/2)/8;
        size_t cellY = (ghost->y + ghost->h/2)/8;
        size_t wCellX = cellX;
        size_t wCellY = cellY;

        char currCell = level->layout[cellY + 1][cellX + 1];
        bool onIntersection = ghost->x % 8 == 4 && ghost->y % 8 == 4;

        switch (ghost->direction) {
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
        switch(ghost->wantedDirection) {
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

        char surroundings[4];
        surroundings[0] = level->layout[cellY + 1][cellX];
        surroundings[1] = level->layout[cellY + 1][cellX + 2];
        surroundings[2] = level->layout[cellY][cellX + 1];
        surroundings[3] = level->layout[cellY + 2][cellX + 1];

        char ghostLocation[2] = {ghost->x, ghost->y};
        char pacmanLocation[2] = {pacman->x, pacman->y};
        ghost->decideDirection(ghost->wantedDirection, time, surroundings, ghostLocation, pacmanLocation);

        if (is180Turn(ghost->direction, ghost->wantedDirection) || ((onIntersection || ghost->direction == DIRECTION_NONE) && wNextCell == 'o')) {
            ghost->direction = ghost->wantedDirection;
        }
        bool cornered = onIntersection && nextCell != 'o' && nextCell != 'i';
        if (!cornered) ghost->move();

        checkWrapAround(ghost, window);

        if (abs(ghost->x - pacman->x) <= 8 && abs(ghost->y - pacman->y) <= 8) {
            if (ghost->confused) {
                ghost->die();
                ghost->lastDeadTime = time;

                int s = 100;
                for (gi = 0; gi <= 3; gi++) {
                    if (time - ghosts[gi]->lastDeadTime < 200) s = s << 1;
                }
                level->score += s;
            } else {
                pacman->die();
                level->livesLeft--;
                if (level->livesLeft == 0) stop = true;
            }
        }

    }

    level->visualize();
    pacman->visualize();
    for (gi = 0; gi <= 3; gi++) ghosts[gi]->visualize();
    level->rerender();
}

void checkWrapAround(Entity* entity, Window* window) {
    if (entity->x <= -entity->w) {
        entity->x = window->w;
    } else if (entity->x >= window->w) {
        entity->x = -entity->w;
    }
    if (entity->y <= -entity->h) {
        entity->y = window->h;
    } else if (entity->y >= window->h) {
        entity->y = -entity->h;
    }
}

bool is180Turn(Direction d1, Direction d2) {
    if (d1 > d2) return is180Turn(d2, d1);
    return (d1 == DIRECTION_UP && d2 == DIRECTION_DOWN) || (d1 == DIRECTION_LEFT && d2 == DIRECTION_RIGHT);
}
