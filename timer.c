/**
 * \file timer.c
 * \brief Programme pour afficher le temps passé
 * \author Hee Sang Shin
 * \version 1.0
 * \date 8 mai 2015
 *
 * Programme qui affiche en haut à gauche le temps joué
 *
 */

#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

/**
 * \fn main
 * \brief Tout pour le temps
 *
 * \param rien
 * \return 0 si ça marche, 1 sinon
 */

int main ( int argc, char** argv )
{
    SDL_Surface *ecran = NULL, *texte = NULL;
    SDL_Rect position;
    SDL_Event event;
    TTF_Font *police = NULL;
    SDL_Color couleurNoire = {0, 0, 0}, couleurBlanche = {255, 255, 255};
    int continuer = 1;
    int tempsActuel = 0, tempsPrecedent = 0;
    double compteur = 0;
    char temps[20] = "";

    if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    };

    if (TTF_Init() == -1)
    {
        fprintf(stderr, "Erreur d'initialisation TTF : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    };

    ecran = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Gestion du texte avec SDL_ttf", NULL);

    /*changement de la police */
    police = TTF_OpenFont("angelina.ttf",64);

    /* Initialisation du temps et du texte */
    tempsActuel = SDL_GetTicks();
    sprintf(temps, "Temps : %0.1lf", compteur);
    texte = TTF_RenderText_Shaded(police, temps, couleurNoire, couleurBlanche);

    /* Pour la pause du programme et la sortie */
    while (continuer)
    {
        SDL_PollEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
            continuer = 0;
            break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_ESCAPE: /* Appui sur la touche Echap, on arrêtet le programme */
                    continuer = 0;
                    break;
                }
                break;
        }

        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));

        /* Pour gérer le temps */
        tempsActuel = SDL_GetTicks();
        if (tempsActuel - tempsPrecedent >= 100) /* Si 100 ms au moins se sont écoulées */
        {
            compteur += 0.1; /* On rajoute 0.1s au compteur */
            sprintf(temps, "Temps : %.1lf", compteur); /* On écrit dans la chaîne "temps le nouveau temps */
            SDL_FreeSurface(texte); /* On supprime la surface précédente */
            texte = TTF_RenderText_Shaded(police, temps, couleurNoire, couleurBlanche); /* On écrit la chaîne temps dans la SDL_Surfqce */
            tempsPrecedent = tempsActuel; /* On met à jour le tempsPrecedent */
        }

        position.x = 0;
        position.y = 0;
        SDL_BlitSurface(texte, NULL, ecran, &position); /* Blit du texte */
        SDL_Flip(ecran);
    }

    TTF_CloseFont(police);
    TTF_Quit();

    SDL_FreeSurface(texte);
    SDL_Quit();

    return EXIT_SUCCESS;
}
