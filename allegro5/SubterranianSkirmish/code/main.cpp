#include "client/player/Player.h"

int main(int argc, char** argv)
{
    srandom(time(NULL)+getpid());

    Player player;

    try {

        player.mainLoop();

    } catch (const Error& err) {

        player.handleError(err);

    } catch (...) {

        player.handleError(Error(__FILE__, __LINE__, "Niezłapany wyjątek typu innego niż Error"));
    }

    player.mainLoop();

    return 0;
}
