#ifndef _BIBMARIO_H
#define _BIBMARIO_H 1

#include <SDL/SDL.h>
#include <math.h>

#define RESX 800
#define RESY 600
#define TIMER 5


/**
* @brief collisionMur detecte les collisions latérales
* @param mur Pointeur sur l'élément de décor
* @param perso Pointeur sur la case du personnage
* @return 0 s'il n'y a pas contact ni pénétration 1 sinon
*/
bool collisionMur( SDL_Rect* mur, SDL_Rect* perso;
/**
 * @brief collisionSol detecte les collisions au sol et au plafond
 * @param mur Pointeur sur l'élément de décor
 * @param perso Pointeur sur la case du personnage
 * @return 0 s'il n'y a pas contact ni pénétration 1 sinon
 */
bool collisionSol(SDL_Rect* mur, SDL_Rect* perso);
/**
\fn void gestionDeceleration ( Uint8* toucheClavier, float *vX, float *vD, float *tempsDec, float *tempsAcc )
\brief Permet de réduire la vitesse du personnage progressivement, afin de rendre le mouvement plus réaliste.
\param [in, out] toucheClavier Pointeur sur la touche enfoncée
\param [in, out] vX Pointeur sur la vitesse horizontale du personnage
\param [in, out] vD Pointeur sur la vitesse de décélération
\param [in, out] tempsDec Pointeur sur la durée de décélération
\param [in, out] tempsAcc Pointeur sur la durée d'accélération
**/
void gestionDeceleration ( Uint8* toucheClavier, float *vX, float *vD, float *tempsDec, float *tempsAcc );
/**
\fn void gestionToucheGauche ( Uint8* toucheClavier, float *vX, float *vD, float *tempsDec, float *tempsAcc  )
\brief Déplacer le personnage vers la gauche à l'aide de la flèche gauche.
\param [in, out] toucheClavier Pointeur sur la touche enfoncée
\param [in, out] vX Pointeur sur la vitesse horizontale du personnage
\param [in, out] vD Pointeur sur la vitesse de décélération
\param [in, out] tempsDec Pointeur sur la durée de décélération
\param [in, out] tempsAcc Pointeur sur la durée d'accélération
**/
void gestionToucheGauche ( Uint8* toucheClavier, float *vX, float *vD, float *tempsDec, float *tempsAcc  );
/**
\fn void gestionToucheDroite ( Uint8* toucheClavier, float *vX, float *vD, float *tempsDec, float *tempsAcc )
\brief Déplacer le personnage vers la droite à l'aide de la flèche droite.
\param [in, out] toucheClavier Pointeur sur la touche enfoncée
\param [in, out] vX Pointeur sur la vitesse horizontale du personnage
\param [in, out] vD Pointeur sur la vitesse de décélération
\param [in, out] tempsDec Pointeur sur la durée de décélération
\param [in, out] tempsAcc Pointeur sur la durée d'accélération
**/
void gestionToucheDroite ( Uint8* toucheClavier, float *vX, float *vD, float *tempsDec, float *tempsAcc );
/**
\fn void gestionToucheEspace ( Uint8* toucheClavier, float *pY, float *vY )
\brief Faire sauter le personnage.
\param [in, out] toucheClavier Pointeur sur la touche de clavier enfoncée
\param [in, out] pY Pointeur sur l'ordonnée du personnage
\param [in, out] vY Pointeur sur la vitesse verticale du personnage
**/
void gestionToucheEspace ( Uint8* toucheClavier, float *pY, float *vY, SDL_Rect *sol );
/**
\fn void gestionGravite ( Uint8* toucheClavier, float pY, float *vY )
\brief Faire retomber le personnage pour qu'il atteigne le sol.
\param [in,out] toucheClavier Pointeur sur la touche enfoncée
\param [in] pY Ordonnée  du personnage
\param [in, out] vY Pointeur sur la vitesse verticale du personnage
**/
void gestionGravite ( Uint8* toucheClavier, float pY, float *vY );
/**
\fn void initialisationFenetre ( SDL_Surface** fenetre )
\brief Initialisation de la fenêtre SDL
\param [in, out] fenetre Double pointeur sur la fenêtre de travail
**/
void initialisationFenetre ( SDL_Surface** fenetre );
/**
\fn void lireToucheClavier ( Uint8* toucheClavier )
\brief Récupérer les entrées du clavier
\param [in, out] toucheClavier Pointeur sur la touche de clavier à récupérer
**/
void lireToucheClavier ( Uint8* toucheClavier );
/**
\fn void initialisationTimer ( Uint32 *temps )
\brief Initialisation du temps
\param [in, out] temps Pointeur sur l'instant initial
**/
void initialisationTimer ( Uint32 *temps );
/**
\fn void gestionTimer ( Uint32 temps, Uint32 tempsEcoule )
\brief Compte à rebours
\param [in] temps Instant initial récupéré avec SDL_GetTicks
\param [in] tempsEcoule
**/
void gestionTimer ( Uint32 temps, Uint32 tempsEcoule );
/**
\fn void effacerFenetre ( SDL_Surface* fenetre )
\brief Libérer la fenêtre
\param [in, out] fenetre Pointeur sur la fenêtre de travail
**/
void effacerFenetre ( SDL_Surface* fenetre );
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
void MAJ( Uint8 *toucheClavier, float *pX, float *pY, float *vX, float *vY, float *tempsDec, float *tempsAcc, float *vD);

#endif
