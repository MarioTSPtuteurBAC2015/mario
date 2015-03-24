#include "bibMario.h"

bool freine = false;
bool space = false;

bool estSOL ( SDL_Rect *dstrect ){
    return (dstrect->y >= 2*RESY / 3);
}

void MAJ(Uint8* keys, SDL_Rect *dstrect, float *vX, float *vY, float *t1, float *t2, float *vD){

    float gS = 0.15, g = 0.45, aS = 10, aXMax = 5, u = 50;

    if (!keys[SDLK_LEFT] && !keys[SDLK_RIGHT]){

        if( *vX < 1 && *vX > -1 ){
            *t1 = 0;
            *t2 = 0;
            *vX = 0;
        }

        if( freine == false ){
            freine = true;
            *vD = *vX;
        }

        if( *t1 == 0 && *t2 != 0){
            *t1 = 1/(*t2);
        }
        if( *vX >= 1 ){
            (*t1)++;
            *vX = *vD*exp(-*t1/u);
        }

        if( *vX <= -1 ){
            (*t1)++;
            *vX = *vD*exp(-*t1/u);
        }

    }

    if (keys[SDLK_LEFT]){
        *vX = -aXMax + aXMax*exp(-*t2/u);
        (*t2)++;
        freine = false;
    }

    if (keys[SDLK_RIGHT]){
        *vX = aXMax - aXMax*exp(-*t2/u);
        (*t2)++;
        freine = false;
    }

    if ( !estSOL(dstrect) ){
        if(keys[SDLK_SPACE] || *vY > 0)
            *vY += gS;
        else
            *vY += g;
    }
    else{
        *vY = 0;
        if (keys[SDLK_SPACE] && space == false){
            *vY = -aS;
            space = true;
        }
    }

    if (!keys[SDLK_SPACE])
        space = false;

    dstrect->x += *vX;
    dstrect->y += *vY;

}
