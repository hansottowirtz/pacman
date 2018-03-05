#include "../../factories/window_factory.hh"

#ifndef SDLWINDOWFACTORY_H
#define SDLWINDOWFACTORY_H

class SDLWindowFactory : public WindowFactory {
  public:
    SDLWindowFactory() {};
    Window* createWindow();
};

#endif
