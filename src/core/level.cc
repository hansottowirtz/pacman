#include "./level.hh"

Level::Level(LevelRef ref) {
    this->ref = ref;
    this->score = 0;

    int i, j;
    for (i = 0; i < 248 / 8; i++) {
        for (j = 0; j < 224 / 8; j++) {
            this->captured[i][j] = false;
        }
    }
    for (i = 0; i < 248 / 8; i++) {
        for (j = 0; j < 224 / 8; j++) {
            this->sprites[i][j] = SPRITE_EMPTY;
        }
    }
}
