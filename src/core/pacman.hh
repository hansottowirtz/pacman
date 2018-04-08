#pragma once

#include "entity.hh"

class Pacman : public Entity
{
  public:
    virtual void visualize() = 0;
};
