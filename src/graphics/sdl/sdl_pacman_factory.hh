#include "../../factories/pacman_factory.hh"

#ifndef __SDLPACMANFACTORY_H__
#define __SDLPACMANFACTORY_H__

class SDLPacmanFactory : public PacmanFactory {
  public:
    Pacman* createPacman();
};

#endif