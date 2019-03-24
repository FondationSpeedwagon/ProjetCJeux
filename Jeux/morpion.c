#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>

int verif_morpion(int grille[3][3]);

void win_screen(SDL_Surface*, int);


void morpion(SDL_Surface *ecran)
{
    SDL_Surface *Croix = NULL, *Rond = NULL, *menu = NULL;
    SDL_Surface *grille_aff[3][3];
    SDL_Rect position[3][3], position_menu;
    SDL_Event event;


    int grille[3][3] = {{0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };
    int continuer = 1;
    int tour = 0;

    int h = 0;
    int c = 0;

    int n_case[2];

    Croix = SDL_LoadBMP("ressources/croix.bmp");
    Rond = SDL_LoadBMP("ressources/rond.bmp");
    menu = IMG_Load("ressources/menu_morpion.png");
    position_menu.x = 630;
    position_menu.y = 0;


    for (int i = 0; i < 9; i++)
    {
        if (i == 3 || i == 6)
        {
            h++;
            c = 0;

        }
        grille_aff[c][h] = SDL_CreateRGBSurface(SDL_HWSURFACE, 205, 205, 32, 0, 0, 0, 0);
        SDL_FillRect(grille_aff[c][h], NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
        position[c][h].x = c * 210;
        position[c][h].y = h * 210;
        SDL_BlitSurface(grille_aff[c][h], NULL, ecran, &position[c][h]);
        c++;
    }
    SDL_BlitSurface(menu, NULL, ecran, &position_menu);


    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            SDL_FreeSurface(ecran);
            SDL_Quit();

        case SDL_MOUSEBUTTONDOWN:
            n_case[0] = event.button.x / 210;
            n_case[1] = event.button.y / 210;
            if (event.button.button == SDL_BUTTON_LEFT && tour < 9 && event.button.x < 630 &&
                    grille[n_case[0]][n_case[1]] == 0)
            {
                if (tour % 2 == 0)
                {
                    SDL_BlitSurface(Croix, NULL, ecran, &position[n_case[0]][n_case[1]]);
                    grille[n_case[0]][n_case[1]] = 1;
                }
                else
                {
                    SDL_BlitSurface(Rond, NULL, ecran, &position[n_case[0]][n_case[1]]);
                    grille[n_case[0]][n_case[1]] = 2;

                }

                tour += 1;
            }
            else if (event.button.x > 630 + 43 && event.button.x < 630 + 53 + 264 && event.button.y > 552 &&
                     event.button.y < 552 + 56)
            {
                SDL_FreeSurface(menu);
                for (int i = 0; i < 3; i++)
                {
                    for (int j = 0; j < 3; j++)
                    {
                        SDL_FreeSurface(grille_aff[i][j]);
                    }
                }
                SDL_FreeSurface(Croix);
                SDL_FreeSurface(Rond);
                return;
            }

        }

        SDL_Flip(ecran);
        if(verif_morpion(grille) != 0)
        {
            win_screen(ecran, verif_morpion(grille));
            return;
        }
    }


}

int verif_morpion(int grille[3][3])
{
    if (grille[0][0] == grille[0][1] && grille[0][0] == grille[0][2])
        return grille[0][0];
    else if (grille[1][0] == grille[1][1] && grille[1][0] == grille[1][2] && grille[1][0] != 0)
        return grille[1][0];
    else if (grille[2][0] == grille[2][1] && grille[2][0] == grille[2][2] && grille[2][0] != 0)
        return grille[2][0];
    else if (grille[0][0] == grille[1][1] && grille[0][0] == grille[2][2] && grille[0][0] != 0)
        return grille[0][0];
    else if (grille[0][2] == grille[1][1] && grille[0][2] == grille[2][0] && grille[0][2] != 0)
        return grille[0][2];
    else if (grille[0][0] == grille[1][0] && grille[0][0] == grille[2][0] && grille[0][0] != 0)
        return grille[0][0];
    else if (grille[0][1] == grille[1][1] && grille[0][1] == grille[2][1] && grille[0][1] != 0)
        return grille[0][1];
    else if (grille[0][2] == grille[1][2] && grille[0][2] == grille[2][2] && grille[0][2] != 0)
        return grille[0][2];
    else
        return 0;
}

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
