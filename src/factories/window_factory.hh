#include "../graphics/window.hh"

#ifndef WINDOWFACTORY_H
#define WINDOWFACTORY_H

class WindowFactory {
  public:
    virtual Window *createWindow() = 0;
};

#endif
