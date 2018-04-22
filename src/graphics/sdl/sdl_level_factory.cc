#include "sdl_level_factory.hh"
#include "sdl_level.hh"
#include "sdl_window.hh"

SDLLevelFactory::SDLLevelFactory(SDLWindow* window) {
    this->window = window;
}

Level* SDLLevelFactory::createLevel(MapRef ref) {
    return new SDLLevel(this->window, ref);
}
