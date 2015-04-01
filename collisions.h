#include <stdio.h>
#include <stdlib.h>
#include <bibMario.h>
#include <booleen.h>
#include <SDL/SDL.h>


/**
 * @brief collisionMur: détecte si le personnage est contre le mur
 * @param mur
 * @param perso
 * @return 1 si collision 0 sinon
 */
int collisionMur( SDL_Rect* mur, SDL_Rect* perso);
/**
 * @brief collisionSol: détecte si le personnage touche le sol ou un plafond
 * @param mur
 * @param perso
 * @return 1 si collision 0 sinon
 */
int collisionSol(SDL_Rect* mur, SDL_Rect* perso);
