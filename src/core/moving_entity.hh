#pragma once

#include "./entity.hh"
#include "./direction.hh"

class MovingEntity : public Entity {
    public:
        void move();
        Direction direction;
        Direction wantedDirection;
};
