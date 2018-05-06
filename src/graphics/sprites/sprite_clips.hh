#pragma once

#include "stdint.h"
#include "../../sprites/sprite_ref.hh"

typedef struct {
    uint16_t x, y, w, h;
} SpriteClip;

namespace SpriteClips {
    SpriteClip get(SpriteRef ref);
}
