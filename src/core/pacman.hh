#include "entity.hh"

#ifndef PACMAN_H
#define PACMAN_H

class Pacman : public Entity
{
  public:
    virtual void visualize() = 0;
};

#endif
