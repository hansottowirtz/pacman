#pragma once

#include "../core/map_ref.hh"
#include "../core/key_state.hh"
#include "../core/pacman.hh"
#include "../core/level.hh"
#include "stdint.h"

class Window {
    public:
        uint16_t w;
        uint16_t h;
        uint8_t M;
        virtual void open() = 0;
        virtual void initialize() = 0;
        virtual void setLevel(LevelRef levelRef) = 0;
        virtual void loop(void (*f)(uint64_t time, KeyState keys)) = 0;
        virtual void close() = 0;
        virtual Pacman* getPacman() = 0;
        // virtual void onUpdate(void (*f)(int)) = 0;
};
