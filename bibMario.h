#ifndef _BIBMARIO_H
#define _BIBMARIO_H 1

#include <SDL/SDL.h>
#include <math.h>

#define RESX 1200
#define RESY 720
#define TIMER 5

bool estSOL ( SDL_Rect *dstrect );
void MAJ(Uint8* keys, SDL_Rect *dstrect, float *vX, float *vY, float *t1, float *t2, float *vD);

#endif
