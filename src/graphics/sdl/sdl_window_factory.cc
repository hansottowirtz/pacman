#include "sdl_window_factory.hh"
#include "sdl_window.hh"

Window *SDLWindowFactory::createWindow() {
    return new SDLWindow;
}
