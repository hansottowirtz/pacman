#include "./sprite_sizes.hh"

SpriteSize SpriteSizes::get(SpriteRef ref) {
    switch (ref) {
        case SPRITE_NUMBER_0:
        case SPRITE_NUMBER_1:
        case SPRITE_NUMBER_2:
        case SPRITE_NUMBER_3:
        case SPRITE_NUMBER_4:
        case SPRITE_NUMBER_5:
        case SPRITE_NUMBER_6:
        case SPRITE_NUMBER_7:
        case SPRITE_NUMBER_8:
        case SPRITE_NUMBER_9:
            return (SpriteSize) {.w = 8, .h = 8};
        case SPRITE_PACMAN_TO_LEFT_OPEN:
        case SPRITE_PACMAN_TO_LEFT_CLOSED:
        case SPRITE_PACMAN_TO_RIGHT_OPEN:
        case SPRITE_PACMAN_TO_RIGHT_CLOSED:
        case SPRITE_PACMAN_TO_UP_OPEN:
        case SPRITE_PACMAN_TO_UP_CLOSED:
        case SPRITE_PACMAN_TO_DOWN_OPEN:
        case SPRITE_PACMAN_TO_DOWN_CLOSED:
        case SPRITE_PACMAN_IMMOBILE:
            return (SpriteSize) {.w = 16, .h = 16};
        default:
            return (SpriteSize) {};
    }
}
