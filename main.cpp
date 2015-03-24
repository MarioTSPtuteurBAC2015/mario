#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include "bibMario.h"


int main ( int argc, char** argv )
{
    Uint8 *keys;
    Uint32 timer, elapsed;
    int numkeys;
    float aX = 0, aY = 0, t1 = 0, t2 = 0, vD = 0;

    SDL_Init( SDL_INIT_VIDEO );
    SDL_Surface* screen = SDL_SetVideoMode(RESX, RESY, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);
    SDL_Surface* bmp = SDL_LoadBMP("cb.bmp");

    SDL_Rect dstrect;
    dstrect.x = 2*RESX / 3;
    dstrect.y = 2*RESY / 3;

    keys = SDL_GetKeyState(&numkeys);

    bool done = false;
    while (!keys[SDLK_ESCAPE]){

        timer = SDL_GetTicks();
        SDL_PumpEvents();
        keys = SDL_GetKeyState(&numkeys);

        MAJ( keys, &dstrect, &aX, &aY, &t1, &t2, &vD);

        SDL_FillRect(screen,NULL,0);
        SDL_BlitSurface(bmp, 0, screen, &dstrect);
        SDL_Flip(screen);

        elapsed = SDL_GetTicks() - timer;
        if (elapsed<TIMER)
            SDL_Delay(TIMER-elapsed);
    }

    SDL_FreeSurface(bmp);
    SDL_Quit();
    return 0;
}
