#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "./sdl_window.hh"
#include "./sdl_pacman.hh"
#include "../../core/key_state.hh"

const int M = 3;
uint32_t timer_cb(uint32_t interval, void *param);

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
        224 * M,
        248 * M,
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
