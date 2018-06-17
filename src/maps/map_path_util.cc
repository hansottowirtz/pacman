#include "./map_path_util.hh"

namespace MapPathUtil {
    std::string getMapLayoutPath(MapRef ref) {
        switch (ref) {
            case MAP_PACMAN:
                return "res/maps/level-1.txt";
            case MAP_CUSTOM:
                return "res/maps/level-2.txt";
        }
    }
}
