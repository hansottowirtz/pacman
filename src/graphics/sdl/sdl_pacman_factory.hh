#include "../../factories/pacman_factory.hh"

#ifndef SDLPACMANFACTORY_H
#define SDLPACMANFACTORY_H

class SDLPacmanFactory : public PacmanFactory {
  public:
    SDLPacmanFactory() {};
    Pacman* createPacman();
};

#endif
