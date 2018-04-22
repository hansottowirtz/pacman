#pragma once

#include "SDL.h"
#include "../sprites/sprite_clips.hh"

namespace SDLSpriteUtil {
    SDL_Rect clipToRect(SpriteClip clip);
}
