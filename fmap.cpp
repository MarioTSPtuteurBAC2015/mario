#define _CRT_SECURE_NO_DEPRECATE   // pour visual C++ qui met des warning pour fopen et fscanf : aucun effet negatif pour les autres compilos.
#include <SDL/SDL_image.h>
#include <string.h>
#include "fmap.h"

#define CACHE_SIZE 5000

/*************************************************************/
SDL_Surface* LoadImage32(const char* fichier_image)
{
	SDL_Surface* image_result;
	SDL_Surface* image_ram = IMG_Load(fichier_image);	// charge l'image dans image_ram en RAM
	if (image_ram==NULL)
	{
		printf("Image %s introuvable !! \n",fichier_image);
		SDL_Quit();
		system("pause");
		exit(-1);
	}
	image_result = SDL_DisplayFormat(image_ram);
	SDL_FreeSurface(image_ram);
	return image_result;
}

/*************************************************************/
void ChargerMap_tileset(FILE* F,Map* m)
{
	int numtile,i,j;
	char buf[CACHE_SIZE];  // un buffer, petite mémoire cache
	char buf2[CACHE_SIZE];  // un buffer, petite mémoire cache
	fscanf(F,"%s",buf); // #tileset
	fscanf(F,"%s",buf); // nom du fichier
	m->tileset = LoadImage32(buf);
	fscanf(F,"%d %d",&m->nbtilesX,&m->nbtilesY);
	m->LARGEUR_TILE = m->tileset->w/m->nbtilesX;
	m->HAUTEUR_TILE = m->tileset->h/m->nbtilesY;
    m->props = (TileProp*)malloc( m->nbtilesX * m->nbtilesY * sizeof(TileProp));
	for(j=0,numtile=0;j<m->nbtilesY;j++)
	{
		for(i=0;i<m->nbtilesX;i++,numtile++)
		{
			m->props[numtile].R.w = m->LARGEUR_TILE;
			m->props[numtile].R.h = m->HAUTEUR_TILE;
			m->props[numtile].R.x = i*m->LARGEUR_TILE;
			m->props[numtile].R.y = j*m->HAUTEUR_TILE;
			fscanf(F,"%s %s",buf,buf2);
            m->props[numtile].dur = 0;
			if (strcmp(buf2,"mur")==0)
                m->props[numtile].dur = 1;
		}
	}
}

/*************************************************************/
void ChargerMap_level(FILE* F,Map* m)
{
	int i,j;
	char buf[CACHE_SIZE];  // un buffer, petite mémoire cache
	fscanf(F,"%s",buf); // #level
	fscanf(F,"%d %d",&m->nbtiles_largeur_monde,&m->nbtiles_hauteur_monde);
    m->schema = (Uint16**)malloc(m->nbtiles_largeur_monde*sizeof(Uint16*));
	for(i=0;i<m->nbtiles_largeur_monde;i++)
        m->schema[i] = (Uint16*)malloc(m->nbtiles_hauteur_monde*sizeof(Uint16));
	for(j=0;j<m->nbtiles_hauteur_monde;j++)
	{
		for(i=0;i<m->nbtiles_largeur_monde;i++)
		{
			int tmp;
			fscanf(F,"%d",&tmp);
            if (tmp >= m->nbtilesX * m->nbtilesY)
			{
				printf("level tile hors limite\n");
				SDL_Quit();
				system("pause");
				exit(-1);
			}
			m->schema[i][j] = tmp;
		}
	}
}

/*************************************************************/
Map* ChargerMap(const char* level,int largeur_fenetre,int hauteur_fenetre)
{
	FILE* F;
	Map* m;
	F = fopen(level,"r");
	if (!F)
	{
		printf("fichier %s introuvable !! \n",level);
		SDL_Quit();
		system("pause");
		exit(-1);
	}
    m = (Map*)malloc(sizeof(Map));
	ChargerMap_tileset(F,m);
	ChargerMap_level(F,m);
	m->largeur_fenetre = largeur_fenetre;
	m->hauteur_fenetre = hauteur_fenetre;
	m->xscroll = 0;
	m->yscroll = 0;
	fclose(F);
	return m;
}

/*************************************************************/
int AfficherMap(Map* m,SDL_Surface* screen)
{
	int i,j;
	SDL_Rect Rect_dest;
	int numero_tile;
	int minx,maxx,miny,maxy;
	minx = m->xscroll / m->LARGEUR_TILE;
	miny = m->yscroll / m->HAUTEUR_TILE;
	maxx = (m->xscroll + m->largeur_fenetre)/m->LARGEUR_TILE;
	maxy = (m->yscroll + m->hauteur_fenetre)/m->HAUTEUR_TILE;
    for(i=minx;i<=maxx;i++)
	{
		for(j=miny;j<=maxy;j++)
		{
			Rect_dest.x = i*m->LARGEUR_TILE - m->xscroll;
			Rect_dest.y = j*m->HAUTEUR_TILE - m->yscroll;
			if (i<0 || i>=m->nbtiles_largeur_monde || j<0 || j>=m->nbtiles_hauteur_monde)
				numero_tile = 0;
			else
				numero_tile = m->schema[i][j];
            SDL_BlitSurface(m->tileset,0,screen,&Rect_dest);

		}
	}
    return 0;
}

/*************************************************************/
int LibererMap(Map* m)
{
	int i;
	SDL_FreeSurface(m->tileset);
	for(i=0;i<m->nbtiles_hauteur_monde;i++)
		free(m->schema[i]);
	free(m->schema);
	free(m->props);
	free(m);
	return 0;
}
/*************************************************************/
void moveMap(Map* m,Uint8* toucheClavier,float* vX,float* vY)
{
    if (toucheClavier[SDLK_LEFT])
        m->xscroll -= *vX;
    if (toucheClavier[SDLK_RIGHT])
        m->xscroll += *vX;
    if (toucheClavier[SDLK_UP])
        m->yscroll -= *vY;
    if (toucheClavier[SDLK_DOWN])
        m->yscroll += *vY;
    // limitation
    if (m->xscroll<0)
        m->xscroll=0;
    if (m->yscroll<0)
        m->yscroll=0;
    if (m->xscroll>m->nbtiles_largeur_monde*m->LARGEUR_TILE-m->largeur_fenetre-1)
        m->xscroll=m->nbtiles_largeur_monde*m->LARGEUR_TILE-m->largeur_fenetre-1;
    if (m->yscroll>m->nbtiles_hauteur_monde*m->HAUTEUR_TILE-m->hauteur_fenetre-1)
        m->yscroll=m->nbtiles_hauteur_monde*m->HAUTEUR_TILE-m->hauteur_fenetre-1;
}
