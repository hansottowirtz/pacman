#include "./ai_factory.hh"

AI* AIFactory::createAI(GhostType type) {
    switch (type) {
        case GHOST_BLINKY:
            return new BlinkyAI;
        case GHOST_PINKY:
            return new PinkyAI;
        case GHOST_INKY:
            return new InkyAI;
        case GHOST_CLYDE:
            return new ClydeAI;
    }
}
