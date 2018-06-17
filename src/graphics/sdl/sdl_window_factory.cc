#include "sdl_window_factory.hh"
#include "sdl_window.hh"
#include <iostream>

Window *SDLWindowFactory::createWindow() {
    std::cout << "creating window";
    return new SDLWindow;
}
