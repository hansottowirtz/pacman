#include "./sprite_clips.hh"
#include "./sprite_sizes.hh"

SpriteClip SpriteClips::get(SpriteRef ref) {
    SpriteSize size = SpriteSizes::get(ref);
    SpriteClip clip = {.w = size.w, .h = size.h};

    // SPRITE_NUMBER_X
    if (ref < 10) {
        clip.x = ref * 12;
        clip.y = 0;
        return clip;
    }

    uint16_t o = 456;

    // others
    switch (ref) {
        case SPRITE_PACMAN_TO_LEFT_OPEN:
            clip.x = o + 0;
            clip.y = 16;
            return clip;
        case SPRITE_PACMAN_TO_LEFT_CLOSED:
            clip.x = o + 16;
            clip.y = 16;
            return clip;
        case SPRITE_PACMAN_TO_RIGHT_OPEN:
            clip.x = o + 0;
            clip.y = 0;
            return clip;
        case SPRITE_PACMAN_TO_RIGHT_CLOSED:
            clip.x = o + 16;
            clip.y = 0;
            return clip;
        case SPRITE_PACMAN_TO_UP_OPEN:
            clip.x = o + 0;
            clip.y = 16 * 2;
            return clip;
        case SPRITE_PACMAN_TO_UP_CLOSED:
            clip.x = o + 16;
            clip.y = 16 * 2;
            return clip;
        case SPRITE_PACMAN_TO_DOWN_OPEN:
            clip.x = o + 0;
            clip.y = 16 * 3;
            return clip;
        case SPRITE_PACMAN_TO_DOWN_CLOSED:
            clip.x = o + 16;
            clip.y = 16 * 3;
            return clip;
        case SPRITE_PACMAN_IMMOBILE:
            clip.x = o + 16 * 2;
            clip.y = 0;
            return clip;
        default:
            // TODO: error
            return clip;
    }
}
