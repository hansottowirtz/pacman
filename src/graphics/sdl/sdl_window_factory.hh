#pragma once

#include "../../factories/window_factory.hh"

class SDLWindowFactory : public WindowFactory {
    public:
        SDLWindowFactory() {};
        Window* createWindow();
};
