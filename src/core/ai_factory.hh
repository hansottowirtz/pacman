#pragma once

#include "./ais.hh"

class AIFactory {
    public:
        AI* createAI(GhostType);
};
