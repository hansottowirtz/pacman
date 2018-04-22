#include "./sdl_sprite_util.hh"

namespace SDLSpriteUtil {
    SDL_Rect clipToRect(SpriteClip clip) {
        SDL_Rect rect = {.x = clip.x, .y = clip.y, .w = clip.w, .h = clip.h};
        return rect;
    }
}
