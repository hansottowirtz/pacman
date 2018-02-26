#include "entity.hh"

class Pacman : public Entity
{
    public:
        Pacman();
        virtual void visualize() = 0;
};