#include <sdl/sdl.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * \struct TileProp fmap.h
 * \brief les rectangles de tileset et le personnage peut y promener si pas mur
 */
 typedef struct
{
	SDL_Rect R;
	int mur;
	// tout ce que vous voulez...
} TileProp;

/**
 *\struct Map fmap.h
 *\brief la structure map qui permet de définir le map et le scrolling
 */
typedef struct
{
	int LARGEUR_TILE,HAUTEUR_TILE;
	int nbtilesX,nbtilesY;
	SDL_Surface* tileset;
	TileProp* props;
	Uint16** schema;
	int nbtiles_largeur_monde,nbtiles_hauteur_monde;
	int xscroll,yscroll;
	int largeur_fenetre,hauteur_fenetre;
} Map;

/**
 *\fn ChargerMap fic
 *\param [in] fic le fichier texte où les propriétés du map sont sauvegardés
 *\param [in] largeur_fenetre
 *\param [in] hauteur_fenetre
 *\param [out] Map
 */
Map* ChargerMap(const char* fic,int largeur_fenetre,int hauteur_fenetre);

/**
 *\fn AfficherMap
 *\param [in] m Pointeur sur Map
 *\param [in] screen Pointeur sur SDL_Surface
 *\param [out] 0 si le map est bien chargé
 */
int AfficherMap(Map* m,SDL_Surface* screen);

/**
 *\fn LibererMap
 *\param [in] m Pointeur sur Map
 *\param [out] 0 si le map a été bien libéré dans l'espace mémoire
 */
int LibererMap(Map* m);

#ifdef __cplusplus
}
#endif // __cplusplus
