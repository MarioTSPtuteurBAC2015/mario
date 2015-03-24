#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include "bibMario.h"

int main ( int argc, char** argv )
{
    Uint32 temps, tempsEcoule;
    int numkeys;
    Uint8 *toucheClavier;
    float positionX = 3*RESX/4, positionY = 3*RESY/4;
    float vitesseX = 0, vitesseY = 0;
    float tempsDeceleration = 0, tempsAcceleration = 0;
    float vitesseDeceleration = 0;

    SDL_Surface* fenetre;
    initialisationFenetre( &fenetre );

    SDL_Surface* bmp = SDL_LoadBMP("cb.bmp");

    SDL_Rect dstrect;

    toucheClavier = SDL_GetKeyState(&numkeys);

    while ( !toucheClavier[SDLK_ESCAPE] ){

        initialisationTimer ( &temps );

        MAJ( toucheClavier, &positionX, &positionY, &vitesseX, &vitesseY, &tempsDeceleration, &tempsAcceleration, &vitesseDeceleration);

        dstrect.x = (int) positionX;
        dstrect.y = (int) positionY;

        effacerFenetre ( fenetre );

        SDL_BlitSurface(bmp, 0, fenetre, &dstrect);

        SDL_Flip(fenetre);

        gestionTimer(temps, tempsEcoule);
    }

    SDL_FreeSurface(bmp);
    SDL_Quit();
    return 0;
}
