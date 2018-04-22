#include "../../../src/core/map_ref.hh"
#include <string>

namespace SpritePathUtil {
    std::string getMapSpritePath(MapRef ref) {
        switch (ref) {
            case MAP_PACMAN:
                return "res/sprites/backgrounds/pacman.png";
            case MAP_PENNY_LANE:
                return "res/sprites/backgrounds/penny_lane.png";
        }
    }
}
