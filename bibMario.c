#include "bibMario.h"

Booleen estSOL ( SDL_Rect *dstrect ){
    return (dstrect->y >= RESY / 2);
}

void MAJ(Uint8* keys, SDL_Rect *dstrect){

    if (keys[SDLK_LEFT])
        dstrect->x -= 5;

    if (keys[SDLK_RIGHT])
        dstrect->x += 5;

    if (keys[SDLK_SPACE] && estSOL(dstrect) )
        dstrect->y -= 300;

    if ( !estSOL(dstrect) ){
        if(keys[SDLK_SPACE])
            dstrect->y += 1;
        else
            dstrect->y += 3;
    }
}
