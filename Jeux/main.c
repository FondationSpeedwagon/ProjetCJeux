#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include "jeux.h"
#include "constantes.h"


int main(int argc, char *argv[])
{
    SDL_Surface *ecran = NULL, *menu = NULL;
    SDL_Rect position;
    SDL_Event event;

    int continuer = 1;

    SDL_Init(SDL_INIT_VIDEO);
    ecran = SDL_SetVideoMode(LARGEUR_ECRAN, HAUTEUR_ECRAN, 32, SDL_HWSURFACE);
    SDL_WM_SetCaption("Petits Jeux", NULL);

    menu = IMG_Load("ressources/menu.png");
    position.x = 0;
    position.y = 0;

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            continuer = 0;
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                if (event.button.x > 320 && event.button.x < 680)
                {
                    if (event.button.y > 210 && event.button.y < 280)
                    {
                        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0,0,0));
                        morpion(ecran);
                    }
                    else if (event.button.y > 350 && event.button.y < 430)
                    {
                        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255,255,255));
                        puissance4(ecran);
                    }
                }
            }

        }
        SDL_BlitSurface(menu, NULL, ecran, &position);
        SDL_Flip(ecran);
    }


    SDL_FreeSurface(menu);
    SDL_Quit();

    return EXIT_SUCCESS;
}

