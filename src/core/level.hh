#pragma once

#include "./map_ref.hh"
#include <string>

class Level {
    public:
        MapRef mapRef;
        Level(MapRef mapRef);
        virtual void visualize() = 0;
};
