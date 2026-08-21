#include "Game.h"

namespace factorycode {
    void debug(char *message) {
#ifdef DEBUG
        std::cout << "[DEBUG]: " << message << std::endl;
#endif
    }


}