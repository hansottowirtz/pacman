#pragma once

#include "SDL.h"
#include "../window.hh"

class SDLWindow : public Window {
    public:
        SDLWindow();
        void open();
        void initialize();
        void setLevel(LevelRef levelRef);
        void loop(void (*f)(uint64_t time, KeyState keys));
        void close();
        Pacman* getPacman();
        SDL_Window* sdlWindow;
        SDL_Renderer* sdlRenderer;
        SDL_Surface* sdlScreenSurface;
        SDL_Texture* sdlSpritesheet;
        Level* currentLevel;
    private:
        Pacman* pacman;
        void loadSpritesheet(std::string path);
};
