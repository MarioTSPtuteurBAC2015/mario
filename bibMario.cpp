#include "bibMario.h"


bool deceleration = false;
bool toucheEspaceEnfoncee = false;
bool toucheGaucheEnfoncee = false;
bool toucheDroiteEnfoncee = false;
bool auSol = false;

float graviteReduite = 0.03, gravite = 0.1, vYSaut = 4.0, vXMax = 3.0, coeffAcc = 50.0, coeffDec = 100.0, coeffFrein = 50.0;

/*************************************************************/
bool collisionMur( SDL_Rect* mur, SDL_Rect* perso){
    if(mur->x <= perso->x + perso->w || mur->x + mur->w >= perso->x)
    {
        return true;
    }
    return false;
}

/*************************************************************/

bool collisionSol(SDL_Rect* mur, SDL_Rect* perso){
    auSol=(mur->y = perso -> y + perso ->h);
    if(mur->y >= perso->y + perso->h || mur->y + mur->h <= perso->y)
    {
        return true;
    }
    return false;
}

/*************************************************************/

void gestionDeceleration ( Uint8* toucheClavier, float *vX, float *vD, float *tempsDec, float *tempsAcc ){
    if ( toucheClavier[SDLK_LEFT] || toucheClavier[SDLK_RIGHT] )
        deceleration = false;

    if ( !toucheClavier[SDLK_LEFT] && !toucheClavier[SDLK_RIGHT] ){

        if( deceleration == false ){
            deceleration = true;
            *tempsDec = 0;
            *tempsAcc = 0;
            *vD = *vX;
        }

        *vX = (*vD)*exp(-((*tempsDec)/coeffDec));
        (*tempsDec)++;
    }
}

/*************************************************************/

void testDeplacement(SDL_Rect *persoAvance, SDL_Rect *mur, float vX, float vY){
    SDL_Rect *test;
    *test=*persoAvance;
    test->x+=vX;
    test->y+=vY;
    if(collisionMur(mur, persoAvance)==0 && collisionSol(mur, persoAvance)==0)          //on peut déplacer le perso
    {
        *persoAvance=*test;
    }
}





/*************************************************************/

void gestionToucheGauche ( Uint8* toucheClavier, float *vX, float *vD, float *tempsDec, float *tempsAcc  ){
    if ( toucheClavier[SDLK_LEFT] && toucheDroiteEnfoncee == false ){
        if ( (int) *vX <= 0 ){
            *vX = -vXMax + vXMax*exp(-*tempsAcc/coeffAcc);
            (*tempsAcc)++;
        }
        else{
            if ( toucheGaucheEnfoncee == false ){
                *vD = *vX;
                *tempsAcc = 0;
                *tempsDec = 0;
            }

            *vX = (*vD)*exp(-((*tempsDec)/coeffFrein));
            (*tempsDec)++;
        }
        toucheGaucheEnfoncee = true;
    }

    if ( !toucheClavier[SDLK_LEFT] )
        toucheGaucheEnfoncee = false;
}

/*************************************************************/

void gestionToucheDroite ( Uint8* toucheClavier, float *vX, float *vD, float *tempsDec, float *tempsAcc ){
    if ( toucheClavier[SDLK_RIGHT] && toucheGaucheEnfoncee == false ){
        if ( (int) *vX >= 0 ){
            *vX = vXMax - vXMax*exp(-*tempsAcc/coeffAcc);
            (*tempsAcc)++;
        }
        else{
            if ( toucheDroiteEnfoncee == false ){
                *vD = *vX;
                *tempsAcc = 0;
                *tempsDec = 0;
            }
            *vX = (*vD)*exp(-((*tempsDec)/coeffFrein));
            (*tempsDec)++;
        }
        toucheDroiteEnfoncee = true;
    }

    if ( !toucheClavier[SDLK_RIGHT] )
        toucheDroiteEnfoncee = false;
}

/*************************************************************/

void gestionToucheEspace ( Uint8* toucheClavier, float *pY, float *vY, SDL_Rect *sol ){
    if ( auSol ){
        *pY = sol -> y;
        *vY = 0;
        if (toucheClavier[SDLK_SPACE] && toucheEspaceEnfoncee == false){
            *vY = -vYSaut;
            toucheEspaceEnfoncee = true;
        }
    }
    if (!toucheClavier[SDLK_SPACE])
        toucheEspaceEnfoncee = false;
}

/*************************************************************/

void gestionGravite ( Uint8* toucheClavier, float pY, float *vY ){
    while ( !auSol || ! collisionSol(mur, perso) ){
        if(toucheClavier[SDLK_SPACE] || *vY > 0)
            *vY += graviteReduite;
        else
            *vY += gravite;
    }
}

/*************************************************************/

void lireToucheClavier ( Uint8* toucheClavier ){
    int numkeys;
    SDL_PumpEvents();
    toucheClavier = SDL_GetKeyState(&numkeys);
}

/*************************************************************/

void initialisationFenetre ( SDL_Surface** fenetre ){
    SDL_Init( SDL_INIT_VIDEO );
    *fenetre = SDL_SetVideoMode(RESX, RESY, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);
}

/*************************************************************/

void initialisationTimer ( Uint32 *temps ){
    *temps = SDL_GetTicks();
}

/*************************************************************/

void gestionTimer ( Uint32 temps, Uint32 tempsEcoule ){
    tempsEcoule = SDL_GetTicks() - temps;
    if (tempsEcoule<TIMER)
        SDL_Delay(TIMER-tempsEcoule);
}

/*************************************************************/

void effacerFenetre ( SDL_Surface* fenetre ){
    SDL_FillRect(fenetre,NULL,0);
}

/*************************************************************/

void MAJ( Uint8 *toucheClavier, float *pX, float *pY, float *vX, float *vY, float *tempsDec, float *tempsAcc, float *vD){

    lireToucheClavier ( toucheClavier );

    gestionDeceleration ( toucheClavier, vX, vD, tempsDec, tempsAcc );

    gestionToucheGauche ( toucheClavier, vX, vD, tempsDec, tempsAcc );

    gestionToucheDroite ( toucheClavier, vX, vD, tempsDec, tempsAcc );

    gestionGravite ( toucheClavier, *pY, vY );

    gestionToucheEspace( toucheClavier, pY, vY );

    *pX += *vX;
    *pY += *vY;
}
