#pragma once

#include "stdint.h"
#include "./sprite_ref.hh"

typedef struct {
    uint16_t w, h;
} SpriteSize;

namespace SpriteSizes {
    SpriteSize get(SpriteRef ref);
}

