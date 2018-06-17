#include "SDL_image.h"
#include "./sdl_level.hh"
#include "./sdl_window.hh"
#include "./sdl_sprite_util.hh"
#include "../../core/level_ref.hh"
#include "../../sprites/sprite_ref.hh"
#include "../../sprites/sprite_path_util.hh"
#include "../../maps/map_path_util.hh"
#include "../sprites/sprite_clips.hh"
#include <string>
#include <fstream>
#include <iostream>

bool posEq(char layout[248 / 8 + 2][224 / 8 + 2], uint8_t i, uint8_t j, char up, char down, char left, char right) {
    return (
        layout[i - 1][j] == up &&
        layout[i + 1][j] == down &&
        layout[i][j - 1] == left &&
        layout[i][j + 1] == right
    );
}

SDLLevel::SDLLevel(LevelRef ref) : Level::Level(ref) {}

void SDLLevel::setWindow(SDLWindow* window) {
    this->window = window;
}

void SDLLevel::visualize() {
    std::string layoutPath = MapPathUtil::getMapLayoutPath(MAP_PACMAN);
    std::ifstream file;
    file.open(layoutPath);
    if (!file) {
        std::cout << "Layout file can't be opened" << std::endl;
    }

    std::string line;
    uint8_t i;
    uint8_t j;

    for (j = 0; j < (224 / 8) + 2; j++) {
        this->layout[0][j] = 'i';
        this->layout[(248 / 8) + 1][j] = 'i';
    }

    i = 1;
    while (file >> line) {
        this->layout[i][0] = 'i';
        this->layout[i][(224 / 8) + 1] = 'i';
        for (j = 1; j < (224 / 8) + 1; j++) {
            this->layout[i][j] = line.at(j - 1);
        }
        i++;
    }

    file.close();

    for (i = 1; i < (248 / 8) + 1; i++) {
        for (j = 1; j < (224 / 8) + 1; j++) {
            char c = this->layout[i][j];
            if (c == 'o') {
                sprites[i-1][j-1] = SPRITE_BULLET;
            } else if (c == 'n') {
                sprites[i-1][j-1] = SPRITE_EMPTY;
                this->layout[i][j] = 'o';
            } else if (c == 'i') {
                sprites[i-1][j-1] = SPRITE_EMPTY;
            }
        }
    }

    for (i = 1; i < (248 / 8) + 1; i++) {
        for (j = 1; j < (224 / 8) + 1; j++) {
            char c = layout[i][j];
            uint8_t li = i - 1;
            uint8_t lj = j - 1;

            if (c == 'x') {
                // Contained between 4 walls
                if (posEq(layout, i, j, 'x', 'x', 'x', 'x')) {
                    if (layout[i - 1][j - 1] == 'o') {
                        sprites[li][lj] = SPRITE_WALL_INNER_CORNER_DOWN_RIGHT;
                    } else if (layout[i - 1][j + 1] == 'o') {
                        sprites[li][lj] = SPRITE_WALL_INNER_CORNER_DOWN_LEFT;
                    } else if (layout[i + 1][j - 1] == 'o') {
                        sprites[li][lj] = SPRITE_WALL_INNER_CORNER_TOP_RIGHT;
                    } else if (layout[i + 1][j + 1] == 'o') {
                        sprites[li][lj] = SPRITE_WALL_INNER_CORNER_TOP_LEFT;
                    } else {
                        sprites[li][lj] = SPRITE_EMPTY;
                    }
                }
                // Corners of the map
                else if (posEq(layout, i, j, 'i', 'x', 'i', 'x')) {
                    sprites[li][lj] = SPRITE_WALL_SIDE_TOP_LEFT;
                } else if (posEq(layout, i, j, 'i', 'x', 'x', 'i')) {
                    sprites[li][lj] = SPRITE_WALL_SIDE_TOP_RIGHT;
                } else if (posEq(layout, i, j, 'x', 'i', 'i', 'x')) {
                    sprites[li][lj] = SPRITE_WALL_SIDE_DOWN_LEFT;
                } else if (posEq(layout, i, j, 'x', 'i', 'x', 'i')) {
                    sprites[li][lj] = SPRITE_WALL_SIDE_DOWN_RIGHT;
                }
                // Side to wall curves
                else if (layout[i - 1][j] == 'i' &&
                layout[i + 1][j] == 'x' &&
                layout[i + 1][j + 1] == 'x') {
                    sprites[li][lj] = SPRITE_WALL_SIDE_TOP_TO_LEFT_CURVE;
                } else if (layout[i - 1][j] == 'i' &&
                layout[i + 1][j] == 'x' &&
                layout[i + 1][j - 1] == 'x') {
                    sprites[li][lj] = SPRITE_WALL_SIDE_TOP_TO_RIGHT_CURVE;
                } else if (layout[i][j - 1] == 'i' &&
                layout[i][j + 1] == 'x' &&
                layout[i + 1][j + 1] == 'x') {
                    sprites[li][lj] = SPRITE_WALL_SIDE_LEFT_TO_TOP_CURVE;
                } else if (layout[i][j - 1] == 'i' &&
                layout[i][j + 1] == 'x' &&
                layout[i - 1][j + 2] == 'x') {
                    sprites[li][lj] = SPRITE_WALL_SIDE_LEFT_TO_DOWN_CURVE;
                } else if (layout[i][j + 1] == 'i' &&
                layout[i][j - 1] == 'x' &&
                layout[i + 1][j - 1] == 'x') {
                    sprites[li][lj] = SPRITE_WALL_SIDE_RIGHT_TO_TOP_CURVE;
                } else if (layout[i][j + 1] == 'i' &&
                layout[i][j - 1] == 'x' &&
                layout[i - 1][j - 2] == 'x') {
                    sprites[li][lj] = SPRITE_WALL_SIDE_RIGHT_TO_DOWN_CURVE;
                }
                // Sides (edges) of the map
                else if (layout[i - 1][j] == 'i' &&
                layout[i][j - 1] != 'o' &&
                layout[i][j + 1] != 'o') {
                    sprites[li][lj] = SPRITE_WALL_SIDE_TOP;
                } else if (layout[i + 1][j] == 'i' &&
                layout[i][j - 1] != 'o' &&
                layout[i][j + 1] != 'o') {
                    sprites[li][lj] = SPRITE_WALL_SIDE_DOWN;
                } else if (layout[i][j - 1] == 'i' &&
                layout[i - 1][j] != 'o' &&
                layout[i + 1][j] != 'o') {
                    sprites[li][lj] = SPRITE_WALL_SIDE_LEFT;
                } else if (layout[i][j + 1] == 'i' &&
                layout[i - 1][j] != 'o' &&
                layout[i + 1][j] != 'o') {
                    sprites[li][lj] = SPRITE_WALL_SIDE_RIGHT;
                }
                // In-map walls
                else if (posEq(layout, i, j, 'o', 'x', 'o', 'x')) {
                    sprites[li][lj] = SPRITE_WALL_CORNER_TOP_LEFT;
                } else if (posEq(layout, i, j, 'x', 'o', 'o', 'x')) {
                    sprites[li][lj] = SPRITE_WALL_CORNER_DOWN_LEFT;
                } else if (posEq(layout, i, j, 'o', 'x', 'x', 'o')) {
                    sprites[li][lj] = SPRITE_WALL_CORNER_TOP_RIGHT;
                } else if (posEq(layout, i, j, 'x', 'o', 'x', 'o')) {
                    sprites[li][lj] = SPRITE_WALL_CORNER_DOWN_RIGHT;
                } else if (posEq(layout, i, j, 'x', 'x', 'o', 'x')) {
                    sprites[li][lj] = SPRITE_WALL_LEFT;
                } else if (posEq(layout, i, j, 'o', 'x', 'x', 'x')) {
                    sprites[li][lj] = SPRITE_WALL_TOP;
                } else if (posEq(layout, i, j, 'x', 'o', 'x', 'x')) {
                    sprites[li][lj] = SPRITE_WALL_DOWN;
                } else if (posEq(layout, i, j, 'x', 'x', 'x', 'o')) {
                    sprites[li][lj] = SPRITE_WALL_RIGHT;
                }
                // All others
                else {
                    sprites[li][lj] = SPRITE_EMPTY;
                }
            } else if (c == 's') {
                // Spawn
                if (posEq(layout, i, j, 's', 's', 's', 's') ||
                    posEq(layout, i, j, 'e', 's', 's', 's')) {
                    sprites[li][lj] = SPRITE_EMPTY;
                } else if (posEq(layout, i, j, 'o', 's', 'o', 's')) {
                    sprites[li][lj] = SPRITE_SPAWN_CORNER_TOP_LEFT;
                } else if (posEq(layout, i, j, 'o', 's', 's', 'o')) {
                    sprites[li][lj] = SPRITE_SPAWN_CORNER_TOP_RIGHT;
                } else if (posEq(layout, i, j, 's', 'o', 'o', 's')) {
                    sprites[li][lj] = SPRITE_SPAWN_CORNER_DOWN_LEFT;
                } else if (posEq(layout, i, j, 's', 'o', 's', 'o')) {
                    sprites[li][lj] = SPRITE_SPAWN_CORNER_DOWN_RIGHT;
                } else if (posEq(layout, i, j, 'o', 's', 's', 's') ||
                    posEq(layout, i, j, 'o', 's', 'e', 's') ||
                    posEq(layout, i, j, 'o', 's', 's', 'e')) {
                    sprites[li][lj] = SPRITE_SPAWN_TOP;
                } else if (posEq(layout, i, j, 's', 'o', 's', 's')) {
                    sprites[li][lj] = SPRITE_SPAWN_DOWN;
                } else if (posEq(layout, i, j, 's', 's', 'o', 's')) {
                    sprites[li][lj] = SPRITE_SPAWN_LEFT;
                } else if (posEq(layout, i, j, 's', 's', 's', 'o')) {
                    sprites[li][lj] = SPRITE_SPAWN_RIGHT;
                }
            } else if (c == 'e') {
                // Spawn exit
                sprites[li][lj] = SPRITE_SPAWN_HORIZONTAL_EXIT;
            }
        }
    }

    for (i = 0; i < 248 / 8 + 1; i++) {
        for (j = 0; j < 224 / 8 + 1; j++) {
            SpriteRef sprite = sprites[i][j];

            if (this->captured[i][j]) sprite = SPRITE_EMPTY;
            // if (sprite == SPRITE_EMPTY) continue;
            SDL_Rect clip = SDLSpriteUtil::clipToRect(SpriteClips::get(sprite));

            SDL_Rect dest;
            dest.x = j * 8 * this->window->M;
            dest.y = i * 8 * this->window->M;
            dest.w = 8 * this->window->M;
            dest.h = 8 * this->window->M;

            SDL_RenderCopy(
                this->window->sdlRenderer,
                this->window->sdlSpritesheet,
                &clip,
                &dest);
        }
    }
}

void SDLLevel::rerender() {
    SDL_UpdateWindowSurface(this->window->sdlWindow);
}
