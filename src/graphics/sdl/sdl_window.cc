#include <iostream>
#include <fstream>
#include "SDL.h"
#include "SDL_image.h"
#include "./sdl_window.hh"
#include "./sdl_pacman.hh"
#include "../../sprites/sprite_ref.hh"
#include "../../core/key_state.hh"
#include "../../maps/map_path_util.hh"
#include "./sdl_sprite_util.hh"

uint32_t timer_cb(uint32_t interval, void *param);

bool posEq(char layout[248 / 8 + 2][224 / 8 + 2], uint8_t i, uint8_t j, char up, char down, char left, char right) {
    return (
        layout[i - 1][j] == up &&
        layout[i + 1][j] == down &&
        layout[i][j - 1] == left &&
        layout[i][j + 1] == right
    );
}


SDLWindow::SDLWindow() {
    this->w = 224;
    this->h = 248;
    this->M = 2;
}

void SDLWindow::open() {
    //The window we'll be rendering to
    SDL_Window* window = NULL;

    //The surface contained by the window
    SDL_Surface* screenSurface = NULL;

    SDL_Renderer* renderer = NULL;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL_Init error: %s\n", SDL_GetError());
        return;
    }

    window = SDL_CreateWindow("Pacman",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        this->w * this->M,
        this->h * this->M,
        SDL_WINDOW_SHOWN);

    if (window == NULL) {
        printf("SDL_CreateWindow error: %s\n", SDL_GetError());
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

    if (renderer == NULL) {
        printf("SDL_CreateRenderer error: %s\n", SDL_GetError());
        return;
    }

    this->sdlWindow = window;
    this->sdlRenderer = renderer;
    this->sdlScreenSurface = SDL_GetWindowSurface(window);

    if (this->sdlScreenSurface == NULL) {
        printf("SDL_GetWindowSurface error: %s\n", SDL_GetError());
        return;
    }

    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    //Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if(!(IMG_Init(imgFlags) & imgFlags)) {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        return;
    }
}

void SDLWindow::initialize() {
    this->pacman = new SDLPacman(this);
    this->pacman->initialize();
}

// KeyState currentKeys;

void SDLWindow::loop(void (*f)(uint64_t time, KeyState keys)) {
    Uint32 delay = 20;  /* To round it down to the nearest 10 ms */
    SDL_TimerID timerId = SDL_AddTimer(delay, timer_cb, NULL);
    uint64_t tick = 0;

    SDL_Event e;
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_USEREVENT) {
                const Uint8 *state = SDL_GetKeyboardState(NULL);
                KeyState currentKeys = {
                    .up = state[SDL_SCANCODE_UP],
                    .down = state[SDL_SCANCODE_DOWN],
                    .left = state[SDL_SCANCODE_LEFT],
                    .right = state[SDL_SCANCODE_RIGHT],
                };
                f(tick++, currentKeys);
            }
        }
    }
}

void SDLWindow::setMap(MapRef mapRef) {
    SDL_Surface* optimizedSurface = NULL;

    std::string path = "./res/sprites/spritesheet.png";

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL) {
        printf("IMG_Load error: (%s) %s\n", path.c_str(), IMG_GetError());
        return;
    }

    //Convert surface to screen format
    optimizedSurface = SDL_ConvertSurface(loadedSurface, this->sdlScreenSurface->format, 0);
    if (optimizedSurface == NULL) {
        printf("SDL_ConvertSurface error: (%s) %s\n", path.c_str(), SDL_GetError());
        return;
    }

    //Get rid of old loaded surface
    SDL_FreeSurface(loadedSurface);

    SDL_Texture* spritesheet = SDL_CreateTextureFromSurface(this->sdlRenderer, optimizedSurface);
    SDL_FreeSurface(optimizedSurface);

    std::string layoutPath = MapPathUtil::getMapLayoutPath(mapRef);
    std::ifstream file;
    file.open(layoutPath);
    if (!file) {
        std::cout << "Layout file can't be opened" << std::endl;
    }

    std::string line;
    uint8_t i;
    uint8_t j;
    char layout[(248 / 8) + 2][(224 / 8) + 2];

    for (j = 0; j < (224 / 8) + 2; j++) {
        layout[0][j] = 'i';
        layout[(248 / 8) + 1][j] = 'i';
    }

    i = 1;
    while (file >> line) {
        layout[i][0] = 'i';
        layout[i][(224 / 8) + 1] = 'i';
        for (j = 1; j < (224 / 8) + 1; j++) {
            layout[i][j] = line.at(j - 1);
        }
        i++;
    }

    file.close();

    SpriteRef sprites[248 / 8][224 / 8];

    for (i = 1; i < (248 / 8) + 1; i++) {
        for (j = 1; j < (224 / 8) + 1; j++) {
            char c = layout[i][j];
            if (c == 'o') {
                sprites[i-1][j-1] = SPRITE_BULLET;
            } else if (c == 'n') {
                sprites[i-1][j-1] = SPRITE_EMPTY;
                layout[i][j] = 'o';
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
            if (sprite == SPRITE_EMPTY) continue;
            SDL_Rect clip = SDLSpriteUtil::clipToRect(SpriteClips::get(sprite));

            SDL_Rect dest;
            dest.x = j * 8 * this->M;
            dest.y = i * 8 * this->M;
            dest.w = 8 * this->M;
            dest.h = 8 * this->M;

            SDL_RenderCopy(
                this->sdlRenderer,
                spritesheet,
                &clip,
                &dest);
        }
    }

    SDL_UpdateWindowSurface(this->sdlWindow);
}

void SDLWindow::close() {
    // Close and destroy the window
    SDL_DestroyWindow(this->sdlWindow);

    // Clean up
    SDL_Quit();
}

Pacman* SDLWindow::getPacman() {
    return this->pacman;
}

uint32_t timer_cb(uint32_t interval, void *param) {
    SDL_Event event;
    SDL_UserEvent userevent;

    /* In this example, our callback pushes a function
    into the queue, and causes our callback to be called again at the
    same interval: */

    userevent.type = SDL_USEREVENT;
    userevent.code = 0;
    userevent.data1 = NULL;
    userevent.data2 = NULL;

    event.type = SDL_USEREVENT;
    event.user = userevent;

    SDL_PushEvent(&event);
    return(interval);
}
