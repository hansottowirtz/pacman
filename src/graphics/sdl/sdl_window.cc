#include <iostream>
#include <fstream>
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#include "./sdl_window.hh"
#include "./sdl_pacman.hh"
#include "./sdl_level.hh"
#include "./sdl_ghost.hh"
#include "../../sprites/sprite_ref.hh"
#include "../../sprites/sprite_path_util.hh"
#include "../../core/key_state.hh"
#include "../../core/level_ref.hh"
#include "../../core/ghost_type.hh"
#include "./sdl_sprite_util.hh"

uint32_t timer_cb(uint32_t interval, void *param);

SDLWindow::SDLWindow() {
    this->w = 224;
    this->h = 248 + 20;
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

    if (TTF_Init() < 0) {
        printf("TTF_Init error: %s\n", TTF_GetError());
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

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
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

    int gi;
    for (gi = 0; gi <= 3; gi++) {
        this->ghosts[gi] = new SDLGhost(this, static_cast<GhostType>(gi));
        this->ghosts[gi]->initialize();
    }

    this->loadSpritesheet(SpritePathUtil::getSpritesheetPath());
}

// KeyState currentKeys;

void SDLWindow::loop(void (*f)(uint64_t time, KeyState keys)) {
    Uint32 delay = 20;  /* To round it down to the nearest 10 ms */
    SDL_TimerID timerId = SDL_AddTimer(delay, timer_cb, NULL);
    uint64_t tick = 0;

    SDL_Event e;
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&e) && !quit) {
            if (e.type == SDL_QUIT) {
                std::cout << "Quitting" << std::endl;
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

void SDLWindow::setLevel(LevelRef levelRef) {
    SDLLevel* level = new SDLLevel(levelRef);
    level->setWindow(this);
    this->currentLevel = level;
    this->currentLevel->visualize();
}

Level* SDLWindow::getLevel() {
    return this->currentLevel;
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

Ghost* SDLWindow::getGhost(GhostType type) {
    return this->ghosts[type];
}

void SDLWindow::loadSpritesheet(std::string path) {
    //The final optimized image
    SDL_Surface* optimizedSurface = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL) {
        printf("IMG_Load error: (%s) %s\n", path.c_str(), IMG_GetError());
        return;
    }

    // SDL_SetColorKey(loadedSurface, 1, SDL_MapRGB(loadedSurface->format, 0, 0, 0));

    //Convert surface to screen format
    optimizedSurface = SDL_ConvertSurface(loadedSurface, this->sdlScreenSurface->format, 0);
    if (optimizedSurface == NULL) {
        printf("SDL_ConvertSurface error: (%s) %s\n", path.c_str(), SDL_GetError());
        return;
    }

    //Get rid of old loaded surface
    SDL_FreeSurface(loadedSurface);

    SDL_Texture* spritesheet = SDL_CreateTextureFromSurface(this->sdlRenderer, optimizedSurface);
    SDL_SetTextureBlendMode(spritesheet, SDL_BLENDMODE_BLEND);
    SDL_FreeSurface(optimizedSurface);

    this->sdlSpritesheet = spritesheet;
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
