#include <collisions.h>


int collisionMur( SDL_Rect* mur, SDL_Rect* perso){
    if(mur->x <= perso->x + perso->w || mur->x + mur->w >= perso->x)
    {
        return 1;
    }
    return 0;
}

int collisionSol(SDL_Rect* mur, SDL_Rect* perso){
    if(mur->y <= perso->y + perso->h || mur->y + mur->h >= perso->y)
    {
        return 1;
    }
    return 0;
}
