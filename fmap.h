#ifndef FMAP_H
#define FMAP_H
#include <SDL/SDL.h>
#include "structures.h"


/**
 *\fn ChargerMap fic
 *\param [in] fic le fichier texte où les propriétés du map sont sauvegardées
 *\param [in] largeur_fenetre
 *\param [in] hauteur_fenetre
 *\param [out] Map
 */
Map* ChargerMap(const char* fic,int largeur_fenetre,int hauteur_fenetre);

/**
 *\fn AfficherMap
 *\param [in] m Pointeur sur Map
 *\param [in] screen Pointeur sur SDL_Surface
 *\param [out] 0 si la map est bien chargée
 */
int AfficherMap(Map* m,SDL_Surface* screen);

/**
 *\fn LibererMap
 *\param [in] m Pointeur sur Map
 *\param [out] 0 si la map a été bien libérée dans l'espace mémoire
 */
int LibererMap(Map* m);

/**
* @brief fait bouger la map
* @param m La map sur laquelle on travaille
* @param in
*/
void moveMap(Map *m,Uint8* toucheClavier,float* vX,float* vY);

#endif
