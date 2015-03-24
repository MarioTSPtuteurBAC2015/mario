#include "bibMario.h"

bool deceleration = false;
bool toucheEspaceEnfoncee = false;
bool toucheGaucheEnfoncee = false;
bool toucheDroiteEnfoncee = false;

float graviteReduite = 0.03, gravite = 0.1, vYSaut = 4.0, vXMax = 3.0, coeffAcc = 50.0, coeffDec = 100.0, coeffFrein = 50.0;

/*************************************************************/
bool estAuSOL ( float pY ){
    return (pY >= 2*RESY / 3);
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
void gestionToucheEspace ( Uint8* toucheClavier, float *pY, float *vY ){
    if ( estAuSOL(*pY) ){
        *pY = 2*RESY / 3;
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
    if ( !estAuSOL(pY) ){
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
