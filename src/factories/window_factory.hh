#pragma once

#include "../graphics/window.hh"


class WindowFactory {
    public:
        WindowFactory();
        virtual Window *createWindow() = 0;
};
