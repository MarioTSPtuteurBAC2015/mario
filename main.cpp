#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

//#include <SDL/SDL.h>
#include <stdio.h>
#include <SDL/SDL_image.h>
#include "bibMario.h"
#include "jeu.h"

int main(int argc, char *argv[])
{
    SDL_Surface *fenetre = NULL, *menu = NULL;
    SDL_Rect positionMenu;
    SDL_Event event;
    printf("debut");
    int continuer = 1;
    int choixMenu = -1;
    initialisationFenetre( &fenetre );
    SDL_WM_SetCaption("Mario TSP", NULL);

    menu = IMG_Load("menumario.jnp"); // Charge l'image du menu


    positionMenu.x = 0;
    positionMenu.y = 0;
    SDL_BlitSurface(menu, NULL, fenetre, &positionMenu);
    SDL_Flip(fenetre);

    while (continuer)
    {
        SDL_WaitEvent(&event);

        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                choixMenu = 0;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE: // on arrête le jeu en appuyant sur echap
                        continuer = 0;
                        choixMenu = 0;
                        break;
                    case SDLK_1: // demande à jouer en appuyant sur 1
                        choixMenu = 1;
                        continuer = 0;
                        break;
                    case SDLK_KP1:
                        choixMenu = 1;
                        continuer = 0;
                        break;
                    case SDLK_RETURN:
                        choixMenu = 1;
                        continuer = 0;
                        break;
                    /*case SDLK_2: // demande à afficher les meilleurs scores
                        jeu = 2;
                        break;
                    case SDLK_KP2:
                        jeu = 2;
                        break;*/
                }
                break;
             default:
                break;
        }
    }
    printf("%d",choixMenu);
    switch(choixMenu)
    {
        case 0:
            break;
        case 1:
            // Effacement de l'écran
            effacerFenetre ( fenetre );
            jouer(fenetre);
            break;
        case 2:
            //score(fenetre);
            break;
        default:
            break;
    }

    SDL_FreeSurface(menu);
    SDL_Quit();

    return EXIT_SUCCESS;
}
