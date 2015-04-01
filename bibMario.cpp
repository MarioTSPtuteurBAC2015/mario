/** \file bibMario.cpp 
\brief Toutes les fonctions permettant de faire bouger le personnage
\version 1.0


**/

#include "bibMario.h"


bool deceleration = false;
bool toucheEspaceEnfoncee = false;
bool toucheGaucheEnfoncee = false;
bool toucheDroiteEnfoncee = false;

float graviteReduite = 0.03, gravite = 0.1, vYSaut = 4.0, vXMax = 3.0, coeffAcc = 50.0, coeffDec = 100.0, coeffFrein = 50.0;

/*************************************************************/
/**
\fn bool estAuSOL ( float pY )
\brief Permet de savoir si le personnage touche le sol.
\param [in] pY Ordonnée du personnage
\return Revoit true si le personnage est à une ordonnée >= 2*RESY / 3 et false sinon
**/
bool estAuSOL ( float pY ){
    return (pY >= 2*RESY / 3);
}


/*************************************************************/
/**
\fn void gestionDeceleration ( Uint8* toucheClavier, float *vX, float *vD, float *tempsDec, float *tempsAcc )
\brief Permet de réduire la vitesse du personnage progressivement, afin de rendre le mouvement plus réaliste.
\param [in, out] toucheClavier Pointeur sur la touche enfoncée
\param [in, out] vX Pointeur sur la vitesse horizontale du personnage
\param [in, out] vD Pointeur sur la vitesse de décélération
\param [in, out] tempsDec Pointeur sur la durée de décélération
\param [in, out] tempsAcc Pointeur sur la durée d'accélération
**/
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
/**
\fn void gestionToucheGauche ( Uint8* toucheClavier, float *vX, float *vD, float *tempsDec, float *tempsAcc  )
\brief Déplacer le personnage vers la gauche à l'aide de la flèche gauche.
\param [in, out] toucheClavier Pointeur sur la touche enfoncée
\param [in, out] vX Pointeur sur la vitesse horizontale du personnage
\param [in, out] vD Pointeur sur la vitesse de décélération
\param [in, out] tempsDec Pointeur sur la durée de décélération
\param [in, out] tempsAcc Pointeur sur la durée d'accélération
**/
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
/**
\fn void gestionToucheDroite ( Uint8* toucheClavier, float *vX, float *vD, float *tempsDec, float *tempsAcc )
\brief Déplacer le personnage vers la droite à l'aide de la flèche droite.
\param [in, out] toucheClavier Pointeur sur la touche enfoncée
\param [in, out] vX Pointeur sur la vitesse horizontale du personnage
\param [in, out] vD Pointeur sur la vitesse de décélération
\param [in, out] tempsDec Pointeur sur la durée de décélération
\param [in, out] tempsAcc Pointeur sur la durée d'accélération
**/
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
/**
\fn void gestionToucheEspace ( Uint8* toucheClavier, float *pY, float *vY )
\brief Faire sauter le personnage.
\param [in, out] toucheClavier Pointeur sur la touche de clavier enfoncée
\param [in, out] pY Pointeur sur l'ordonnée du personnage
\param [in, out] vY Pointeur sur la vitesse verticale du personnage
**/
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
/**
\fn void gestionGravite ( Uint8* toucheClavier, float pY, float *vY )
\brief Faire retomber le personnage pour qu'il atteigne le sol.
\param [in,out] toucheClavier Pointeur sur la touche enfoncée
\param [in] pY Ordonnée  du personnage
\param [in, out] vY Pointeur sur la vitesse verticale du personnage
**/
void gestionGravite ( Uint8* toucheClavier, float pY, float *vY ){
    if ( !estAuSOL(pY) ){
        if(toucheClavier[SDLK_SPACE] || *vY > 0)
            *vY += graviteReduite;
        else
            *vY += gravite;
    }
}

/*************************************************************/
/**
\fn void lireToucheClavier ( Uint8* toucheClavier )
\brief Récupérer les entrées du clavier
\param [in, out] toucheClavier Pointeur sur la touche de clavier à récupérer
**/
void lireToucheClavier ( Uint8* toucheClavier ){
    int numkeys;
    SDL_PumpEvents();
    toucheClavier = SDL_GetKeyState(&numkeys);
}

/*************************************************************/
/**
\fn void initialisationFenetre ( SDL_Surface** fenetre )
\brief Initialisation de la fenêtre SDL
\param [in, out] fenetre Double pointeur sur la fenêtre de travail
**/
void initialisationFenetre ( SDL_Surface** fenetre ){
    SDL_Init( SDL_INIT_VIDEO );
    *fenetre = SDL_SetVideoMode(RESX, RESY, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);
}

/*************************************************************/
/**
\fn void initialisationTimer ( Uint32 *temps )
\brief Initialisation du temps
\param [in, out] temps Pointeur sur l'instant initial
**/
void initialisationTimer ( Uint32 *temps ){
    *temps = SDL_GetTicks();
}

/*************************************************************/
/**
\fn void gestionTimer ( Uint32 temps, Uint32 tempsEcoule )
\brief Compte à rebours
\param [in] temps Instant initial récupéré avec SDL_GetTicks
\param [in] tempsEcoule 
**/
void gestionTimer ( Uint32 temps, Uint32 tempsEcoule ){
    tempsEcoule = SDL_GetTicks() - temps;
    if (tempsEcoule<TIMER)
        SDL_Delay(TIMER-tempsEcoule);
}

/*************************************************************/
/**
\fn void effacerFenetre ( SDL_Surface* fenetre )
\brief Libérer la fenêtre
\param [in, out] fenetre Pointeur sur la fenêtre de travail
**/
void effacerFenetre ( SDL_Surface* fenetre ){
    SDL_FillRect(fenetre,NULL,0);
}

/*************************************************************/
/**
*\fn void MAJ( Uint8 *toucheClavier, float *pX, float *pY, float *vX, float *vY, float *tempsDec, float *tempsAcc, float *vD)
*\brief Déplacer le personnage.
*\param [in, out] toucheClavier Pointeur sur la touche enfoncée
*\param [in, out] pX Pointeur sur l'abscisse du personnage
*\param [in, out] pY Pointeur sur l'ordonnée du personnage
*\param	[in, out] vX Pointeur sur la vitesse horizontale du personnage
*\param	[in, out] vY Pointeur sur la vitesse verticale du personnage
*\param	[in, out] tempsDec Pointeur sur un nombre repésentant le temps de la décélération
*\param	[in, out] tempsDec Pointeur sur un nombre repésentant le temps de l'accélération
*\param	[in, out] vD Pointeur sur la vitesse de décélération
**/
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
