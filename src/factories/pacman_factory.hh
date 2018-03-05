#include "../core/pacman.hh"

#ifndef PACMANFACTORY_H
#define PACMANFACTORY_H

class PacmanFactory {
  public:
    PacmanFactory() {};
    virtual Pacman *createPacman() = 0;
};

#endif
