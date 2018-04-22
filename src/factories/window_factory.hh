#pragma once

#include "../graphics/window.hh"


class WindowFactory {
    public:
        virtual Window *createWindow() = 0;
};
