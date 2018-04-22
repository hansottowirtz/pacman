#pragma once

#include "../core/map_ref.hh"
#include "../core/key_state.hh"
#include "../core/pacman.hh"
#include "stdint.h"

class Window {
    public:
        virtual void open() = 0;
        virtual void initialize() = 0;
        virtual void setMap(MapRef mapRef) = 0;
        virtual void loop(void (*f)(uint64_t time, KeyState keys)) = 0;
        virtual void close() = 0;
        virtual Pacman* getPacman() = 0;
        // virtual void onUpdate(void (*f)(int)) = 0;
};
