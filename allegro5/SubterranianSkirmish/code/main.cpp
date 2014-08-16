#include "client/player/Player.h"

int main(int argc, char** argv)
{
    srandom(time(NULL)+getpid());

    try {
        Player player;
        player.mainLoop();
    } catch (...) {
        Error e(__FILE__, __LINE__, "Niezłapany wyjątek");
    }

    return 0;
}
