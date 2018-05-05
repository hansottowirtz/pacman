#pragma once

#include "SDL.h"
#include "../window.hh"

class SDLWindow : public Window {
    public:
        SDLWindow();
        void open();
        void initialize();
        void setMap(MapRef mapRef);
        void loop(void (*f)(uint64_t time, KeyState keys));
        void close();
        Pacman* getPacman();
        SDL_Window* sdlWindow;
        SDL_Renderer* sdlRenderer;
        SDL_Surface* sdlScreenSurface;
    private:
        Pacman* pacman;
};
