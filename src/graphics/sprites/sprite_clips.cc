#include "./sprite_clips.hh"
#include "../../sprites/sprite_sizes.hh"

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

    if (ref >= 200 && ref <= 231) {
        ref = static_cast<SpriteRef>(ref - 200);
        clip.x = o + (ref % 8) * 16;
        clip.y = 16 * 4 + (ref >> 3) * 16;
        return clip;
    }

    // others
    switch (ref) {
        case SPRITE_BULLET:
            clip.x = 8;
            clip.y = 8;
            return clip;
        case SPRITE_WALL_TOP:
            clip.x = 8 * 3;
            clip.y = 8 * 2;
            return clip;
        case SPRITE_WALL_LEFT:
            clip.x = 8 * 2;
            clip.y = 8 * 3;
            return clip;
        case SPRITE_WALL_DOWN:
            clip.x = 8 * 3;
            clip.y = 8 * 4;
            return clip;
        case SPRITE_WALL_RIGHT:
            clip.x = 8 * 5;
            clip.y = 8 * 3;
            return clip;
        case SPRITE_WALL_CORNER_TOP_LEFT:
            clip.x = 8 * 2;
            clip.y = 8 * 2;
            return clip;
        case SPRITE_WALL_CORNER_DOWN_LEFT:
            clip.x = 8 * 2;
            clip.y = 8 * 4;
            return clip;
        case SPRITE_WALL_CORNER_TOP_RIGHT:
            clip.x = 8 * 5;
            clip.y = 8 * 2;
            return clip;
        case SPRITE_WALL_CORNER_DOWN_RIGHT:
            clip.x = 8 * 5;
            clip.y = 8 * 4;
            return clip;
        case SPRITE_WALL_INNER_CORNER_TOP_LEFT:
            clip.x = 8 * 8;
            clip.y = 8 * 10;
            return clip;
        case SPRITE_WALL_INNER_CORNER_DOWN_LEFT:
            clip.x = 8 * 8;
            clip.y = 8 * 9;
            return clip;
        case SPRITE_WALL_INNER_CORNER_TOP_RIGHT:
            clip.x = 8 * 19;
            clip.y = 8 * 10;
            return clip;
        case SPRITE_WALL_INNER_CORNER_DOWN_RIGHT:
            clip.x = 8 * 19;
            clip.y = 8 * 9;
            return clip;
        case SPRITE_WALL_SIDE_TOP_TO_LEFT_CURVE:
            clip.x = 8 * 13;
            clip.y = 0;
            return clip;
        case SPRITE_WALL_SIDE_TOP_TO_RIGHT_CURVE:
            clip.x = 8 * 14;
            clip.y = 0;
            return clip;
        case SPRITE_WALL_SIDE_LEFT_TO_TOP_CURVE:
            clip.x = 0;
            clip.y = 8 * 24;
            return clip;
        case SPRITE_WALL_SIDE_LEFT_TO_DOWN_CURVE:
            clip.x = 0;
            clip.y = 8 * 25;
            return clip;
        case SPRITE_WALL_SIDE_RIGHT_TO_TOP_CURVE:
            clip.x = 8 * 27;
            clip.y = 8 * 24;
            return clip;
        case SPRITE_WALL_SIDE_RIGHT_TO_DOWN_CURVE:
            clip.x = 8 * 27;
            clip.y = 8 * 25;
            return clip;
        case SPRITE_PACMAN_TO_LEFT_OPEN:
            clip.x = o + 0;
            clip.y = 16;
            return clip;
        case SPRITE_PACMAN_TO_LEFT_HALF_OPEN:
            clip.x = o + 16;
            clip.y = 16;
            return clip;
        case SPRITE_PACMAN_TO_RIGHT_OPEN:
            clip.x = o + 0;
            clip.y = 0;
            return clip;
        case SPRITE_PACMAN_TO_RIGHT_HALF_OPEN:
            clip.x = o + 16;
            clip.y = 0;
            return clip;
        case SPRITE_PACMAN_TO_UP_OPEN:
            clip.x = o + 0;
            clip.y = 16 * 2;
            return clip;
        case SPRITE_PACMAN_TO_UP_HALF_OPEN:
            clip.x = o + 16;
            clip.y = 16 * 2;
            return clip;
        case SPRITE_PACMAN_TO_DOWN_OPEN:
            clip.x = o + 0;
            clip.y = 16 * 3;
            return clip;
        case SPRITE_PACMAN_TO_DOWN_HALF_OPEN:
            clip.x = o + 16;
            clip.y = 16 * 3;
            return clip;
        case SPRITE_PACMAN_IMMOBILE:
            clip.x = o + 16 * 2;
            clip.y = 0;
            return clip;
        case SPRITE_WALL_SIDE_TOP:
            clip.x = 8;
            clip.y = 0;
            return clip;
        case SPRITE_WALL_SIDE_LEFT:
            clip.x = 0;
            clip.y = 8;
            return clip;
        case SPRITE_WALL_SIDE_DOWN:
            clip.x = 8;
            clip.y = 248 - 8;
            return clip;
        case SPRITE_WALL_SIDE_RIGHT:
            clip.x = 224 - 8;
            clip.y = 8;
            return clip;
        case SPRITE_WALL_SIDE_TOP_LEFT:
            clip.x = 0;
            clip.y = 0;
            return clip;
        case SPRITE_WALL_SIDE_TOP_RIGHT:
            clip.x = 224 - 8;
            clip.y = 0;
            return clip;
        case SPRITE_WALL_SIDE_DOWN_LEFT:
            clip.x = 0;
            clip.y = 248 - 8;
            return clip;
        case SPRITE_WALL_SIDE_DOWN_RIGHT:
            clip.x = 224 - 8;
            clip.y = 248 - 8;
            return clip;
        case SPRITE_SPAWN_CORNER_TOP_LEFT:
            clip.x = 8 * 10;
            clip.y = 8 * 12;
            return clip;
        case SPRITE_SPAWN_CORNER_TOP_RIGHT:
            clip.x = 8 * 17;
            clip.y = 8 * 12;
            return clip;
        case SPRITE_SPAWN_CORNER_DOWN_LEFT:
            clip.x = 8 * 10;
            clip.y = 8 * 16;
            return clip;
        case SPRITE_SPAWN_CORNER_DOWN_RIGHT:
            clip.x = 8 * 17;
            clip.y = 8 * 16;
            return clip;
        case SPRITE_SPAWN_HORIZONTAL_EXIT:
            clip.x = 8 * 13;
            clip.y = 8 * 12;
            return clip;
        case SPRITE_SPAWN_LEFT:
            clip.x = 8 * 10;
            clip.y = 8 * 13;
            return clip;
        case SPRITE_SPAWN_TOP:
            clip.x = 8 * 11;
            clip.y = 8 * 12;
            return clip;
        case SPRITE_SPAWN_RIGHT:
            clip.x = 8 * 17;
            clip.y = 8 * 13;
            return clip;
        case SPRITE_SPAWN_DOWN:
            clip.x = 8 * 11;
            clip.y = 8 * 16;
            return clip;
        default:
            clip.x = 0;
            clip.y = 8 * 10;
            return clip;
    }
}
