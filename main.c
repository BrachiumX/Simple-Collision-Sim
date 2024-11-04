#ifdef _WIN64
#include <SDL.h>
#endif
#ifdef __linux__
#include <SDL2/SDL.h>
#endif
#include "init.h"
#include <stdlib.h>

int main(int argc, char **argv) {

    SDL_Init(SDL_INIT_EVERYTHING);

    if (argc < 3) {
        init(-1, -1, -1, -1);
    } else if (argc < 5) {
        init(atoi(argv[1]), atoi(argv[2]), -1, -1);
    } else {
        init(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4]));
    }

    SDL_Quit();

    return 0;
}
