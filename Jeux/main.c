/* Fichier main.c

Fondation Speedwagon


Fonction main
*/

#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include "jeux.h"
#include "constantes.h"


int main(int argc, char *argv[])
{
    SDL_Surface *ecran = NULL, *menu = NULL; // Initiallisation des surfaces
    SDL_Rect position;
    SDL_Event event;

    int continuer = 1;

    SDL_Init(SDL_INIT_VIDEO);
    ecran = SDL_SetVideoMode(LARGEUR_ECRAN, HAUTEUR_ECRAN, 32, SDL_HWSURFACE); // Initialisation de la SDL
    SDL_WM_SetCaption("Petits Jeux", NULL);

    menu = IMG_Load("ressources/menu.png"); // Chargement des images
    position.x = 0;
    position.y = 0;

    while (continuer)
    {
        SDL_WaitEvent(&event); //On attend un event utilisateur
        switch (event.type)
        {
        case SDL_QUIT:
            continuer = 0;
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                if (event.button.y > 285 && event.button.y < 285 + 61) // Coordonnées des bouttons
                {
                    if (event.button.x > 0 && event.button.x < 334)
                    {
                        SDL_FillRect(ecran, NULL, NOIR);
                        if (select_morpion(ecran) == 0)
                        {
                            continuer = 0;
                            break;
                        }

                        SDL_FillRect(ecran, NULL, NOIR); // Problemes de transparence
                    }
                    else if (event.button.x > 334 && event.button.x < 666)
                    {
                        SDL_FillRect(ecran, NULL, NOIR);
                        if (puissance4(ecran) == 0)
                        {
                            continuer = 0;
                            break;
                        }
                        SDL_FillRect(ecran, NULL, NOIR);

                    }
                    else if (event.button.x > 666 && event.button.x <= 1000)
                    {
                        SDL_FillRect(ecran, NULL, NOIR);
                        if (select_tronr(ecran) == 0)
                        {
                            continuer = 0;
                            break;
                        }
                        SDL_FillRect(ecran, NULL, NOIR);
                    }
                }
            }

        }
        SDL_BlitSurface(menu, NULL, ecran, &position); // On reblit le fond, problemes de transparence
        SDL_Flip(ecran);

    }


    SDL_FreeSurface(menu);
    SDL_FreeSurface(ecran);
    SDL_Quit();

    return EXIT_SUCCESS;
}
