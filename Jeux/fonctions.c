#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>

void win_screen(SDL_Surface* ecran, int joueur)
{
    fprintf(stderr, "%d\n", joueur); // Écriture de l'erreur
    int continuer = 1;
    SDL_Event event;

    if(joueur == 1)
    {
        SDL_Surface *Joueur = NULL, *Un = NULL, *Gagne = NULL;
        SDL_Rect pos_joueur, pos_un, pos_gagne;
        Joueur = IMG_Load("ressources/Joueur.png");
        Un = IMG_Load("ressources/1.png");
        Gagne = IMG_Load("ressources/Gagne.png");

        pos_joueur.x = 700;
        pos_un.x = 750;
        pos_gagne.x = 700;
        pos_joueur.y = 50;
        pos_un.y = 100;
        pos_gagne.y = 150;

        SDL_BlitSurface(Joueur, NULL, ecran, &pos_joueur);
        SDL_BlitSurface(Un, NULL, ecran, &pos_un);
        SDL_BlitSurface(Gagne, NULL, ecran, &pos_gagne);
        SDL_Flip(ecran);

    }
    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            SDL_FreeSurface(ecran);
            SDL_Quit();

        case SDL_MOUSEBUTTONDOWN:
            if (event.button.x > 630 + 43 && event.button.x < 630 + 53 + 264 && event.button.y > 552 &&
                    event.button.y < 552 + 56)
            {
                return;
            }
        }
    }
}

