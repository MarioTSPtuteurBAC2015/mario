#ifndef _BIBMARIO_H
#define _BIBMARIO_H 1

#include <SDL/SDL.h>
#include <math.h>

#define RESX 1400
#define RESY 800
#define TIMER 5

void initialisationFenetre ( SDL_Surface** fenetre );
void lireToucheClavier ( Uint8* toucheClavier );
void initialisationTimer ( Uint32 *temps );
void gestionTimer ( Uint32 temps, Uint32 tempsEcoule );
void effacerFenetre ( SDL_Surface* fenetre );
void MAJ( Uint8 *toucheClavier, float *pX, float *pY, float *vX, float *vY, float *tempsDec, float *tempsAcc, float *vD);

#endif

