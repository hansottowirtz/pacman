#pragma once

#include "stdint.h"
#include "./sprite_ref.hh"

typedef struct {
    uint16_t x, y, w, h;
} SpriteClip;

namespace SpriteClips {
    SpriteClip get(SpriteRef ref);
}
