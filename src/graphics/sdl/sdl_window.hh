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
        Level* getLevel();
        Ghost* getGhost(GhostType type);
        SDL_Window* sdlWindow;
        SDL_Renderer* sdlRenderer;
        SDL_Surface* sdlScreenSurface;
        SDL_Texture* sdlSpritesheet;
    private:
        Pacman* pacman;
        Level* currentLevel;
        Ghost* ghosts[4];
        void loadSpritesheet(std::string path);
};
