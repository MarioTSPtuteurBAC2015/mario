#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include "bibMario.h"
#include "jeu.h"

void jouer ( SDL_Surface *fenetre )
{
    printf("jeu");
    Uint32 temps, tempsEcoule;

    int numkeys;
    Uint8 *toucheClavier;
    float positionX = 3*RESX/4, positionY = 3*RESY/4;
    float vitesseX = 0, vitesseY = 0;
    float tempsDeceleration = 0, tempsAcceleration = 0;
    float vitesseDeceleration = 0;
    SDL_Rect mur;
    SDL_Rect perso;
    SDL_Rect sol;

    sol.x = 0;
    sol.y = 0;
    mur.x = 0;
    mur.y = 0;
    perso.x = 50;
    perso.y = 50;

    SDL_Surface* bmp = SDL_LoadBMP("mario.bmp");

    SDL_BlitSurface(bmp, 0, fenetre, &perso);

    SDL_Flip(fenetre);

    SDL_Rect dstrect;

    toucheClavier = SDL_GetKeyState(&numkeys);

    while ( !toucheClavier[SDLK_ESCAPE] ){
        initialisationTimer ( &temps );

        MAJ( toucheClavier, &positionX, &positionY, &vitesseX, &vitesseY, &tempsDeceleration, &tempsAcceleration, &vitesseDeceleration, &mur, &perso, &sol);

        dstrect.x = (int) positionX;
        dstrect.y = (int) positionY;
        effacerFenetre ( fenetre );

        SDL_BlitSurface(bmp, 0, fenetre, &dstrect);

        SDL_Flip(fenetre);

        gestionTimer(temps, tempsEcoule);
    }

    SDL_FreeSurface(bmp);

}
