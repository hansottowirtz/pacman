#include "./sprite_sizes.hh"

SpriteSize SpriteSizes::get(SpriteRef ref) {
    if (ref >= 200 && ref <= 231) {
        return (SpriteSize) {.w = 16, .h = 16};
    }
    switch (ref) {
        case SPRITE_PACMAN_TO_LEFT_OPEN:
        case SPRITE_PACMAN_TO_LEFT_HALF_OPEN:
        case SPRITE_PACMAN_TO_RIGHT_OPEN:
        case SPRITE_PACMAN_TO_RIGHT_HALF_OPEN:
        case SPRITE_PACMAN_TO_UP_OPEN:
        case SPRITE_PACMAN_TO_UP_HALF_OPEN:
        case SPRITE_PACMAN_TO_DOWN_OPEN:
        case SPRITE_PACMAN_TO_DOWN_HALF_OPEN:
        case SPRITE_PACMAN_IMMOBILE:
            return (SpriteSize) {.w = 16, .h = 16};
        default:
            return (SpriteSize) {.w = 8, .h = 8};
    }
}
