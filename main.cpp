#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include <SDL/SDL.h>
#include <stdio.h>
#include <SDL/SDL_image.h>

#include "bibMario.h"
#include "jeu.h"

int main(int argc, char *argv[])
{
    SDL_Surface *fenetre = NULL, *menu = NULL;
    SDL_Rect positionMenu;
    SDL_Event event;

    int continuer = 1;

    initialisationFenetre( &fenetre );
    SDL_WM_SetCaption("Mario TSP", NULL);

    menu = IMG_Load("menu.jpg"); // Charge l'image du menu
    positionMenu.x = 0;
    positionMenu.y = 0;

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE: // on arrête le jeu en appuyant sur echarp
                        continuer = 0;
                        break;
                    case SDLK_1: // demande à jouer en appuyant sur 1
                        jouer(fenetre);
                        break;
                    case SDLK_KP1:
                        jouer(fenetre);
                        break;
                    case SDLK_RETURN:
                        jouer(fenetre);
                        break;
                    /*case SDLK_2: // demande à afficher les meilleurs scores
                        scores(fenetre);
                        break;
                    case SDLK_KP2:
                        scores(fenetre);
                        break;*/
                }
                break;
        }

        // Effacement de l'écran
        effacerFenetre ( fenetre );
        SDL_BlitSurface(menu, NULL, fenetre, &positionMenu);
        SDL_Flip(fenetre);
    }

    SDL_FreeSurface(menu);
    SDL_Quit();

    return EXIT_SUCCESS;
}
