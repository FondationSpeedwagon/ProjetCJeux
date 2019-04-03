/* Fichier morpion.c

Fondation Speedwagon

Fonctions du morpion
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL.h>
#include <SDL_image.h>
#include "structures.h"

int verif_morpion(int grille[3][3]); // Fonction de verification de victoire

int win_screen_morpion(SDL_Surface *, int); // Fonction qui affiche un ecran de victoire

int morpion(SDL_Surface *, int); // Fonction principale

int select_morpion(SDL_Surface *ecran) // Fonction de selection du mode de jeu
{
    surface menu;
    SDL_Event event;

    int continuer = 1;

    menu.surface = IMG_Load("ressources/menu_morpion.png");

    menu.rect.x = 0;
    menu.rect.y = 0;

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch (event.type) // Gestion des events
        {
        case SDL_QUIT:
            return 0;
        case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                if (event.button.x > 320 && event.button.x < 680) // Localistion du clic
                {
                    if (event.button.y > 210 && event.button.y < 280)
                    {
                        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
                        if (morpion(ecran, 1) == 0)
                            return 0;
                    }
                    else if (event.button.y > 310 && event.button.y < 380)
                    {
                        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
                        if (morpion(ecran, 2) == 0)
                            return 0;
                    }
                    else if (event.button.y > 410 && event.button.y < 480)
                    {
                        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
                        if (morpion(ecran, 0) == 0)
                            return 0;
                    }
                }
                else if (event.button.x > 630 + 43 && event.button.x < 630 + 53 + 264 && event.button.y > 552 &&
                         event.button.y < 552 + 56)
                {
                    return 1;
                }


            }

        }
        SDL_BlitSurface(menu.surface, NULL, ecran, &menu.rect);
        SDL_Flip(ecran);
    }


    SDL_FreeSurface(menu.surface);
    return 1;
}

int morpion(SDL_Surface *ecran, int ia)
{
    SDL_Surface *Croix = NULL, *Rond = NULL, *menu = NULL, *fond = NULL;
    SDL_Surface *grille_aff[3][3];  // Definition des surfaces
    SDL_Rect position[3][3], position_menu, position_fond;
    SDL_Event event;


    int grille[3][3] =
    {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };
    int continuer = 1;
    int tour = 0;

    int h = 0;
    int c = 0;

    int n_case[2];

    int iaactif = 0;
    int choix1;
    int choix2;

    int todo = 0; //Condition de retour de l'écrande victoire

    Croix = IMG_Load("ressources/croix.png");
    Rond = IMG_Load("ressources/rond.png");
    menu = IMG_Load("ressources/menu_vierge.png");
    fond = IMG_Load("ressources/grille_morpion.png");

    position_fond.x = 0;
    position_fond.y = 0;
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
        position[c][h].x = c * 215;
        position[c][h].y = h * 210;
        c++;
    }

    SDL_BlitSurface(menu, NULL, ecran, &position_menu);
    SDL_BlitSurface(fond, NULL, ecran, &position_fond);

    while (continuer)
    {

        SDL_WaitEvent(&event);
        switch (event.type) // Gestion des evenements
        {
        case SDL_QUIT:
            SDL_FreeSurface(ecran);
            SDL_Quit();

        case SDL_MOUSEBUTTONDOWN:
            n_case[0] = event.button.x / 210;
            n_case[1] = event.button.y / 210; // Localisation du clic


            if (event.button.button == SDL_BUTTON_LEFT && tour < 9 && event.button.x < 630 &&
                    grille[n_case[0]][n_case[1]] == 0)
            {
                if (tour % 2 == 0)
                {
                    SDL_BlitSurface(Croix, NULL, ecran, &position[n_case[0]][n_case[1]]);
                    grille[n_case[0]][n_case[1]] = 1;

                }
                else if (ia == 0)   // Si l'ia ne joue pas
                {
                    SDL_BlitSurface(Rond, NULL, ecran, &position[n_case[0]][n_case[1]]);
                    grille[n_case[0]][n_case[1]] = 2;

                }

                tour++;
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
                return 0;
            }
            else if (event.button.x > 650 + 43 && event.button.x < 650 + 53 + 264 && event.button.y > 460 &&
                     event.button.y < 520) // Nouvelle partie
            {
                SDL_BlitSurface(fond, NULL, ecran, &position_fond);
                for (int i = 0; i < 3; i++)
                {
                    for (int j = 0; j < 3; j++)
                    {
                        grille[i][j] = 0;
                    }
                }
                tour = 0;

            }

        }
        if (ia == 1 && tour % 2 != 0 && tour < 8 && verif_morpion(grille) == 0) // Ia mode aléatoire
        {

            iaactif = 1;
            while (iaactif == 1) // Tant que la case n'est pas vide
            {
                choix1 = rand() % 3;
                choix2 = rand() % 3;

                if (grille[choix1][choix2] == 0)
                {
                    SDL_BlitSurface(Rond, NULL, ecran, &position[choix1][choix2]);
                    grille[choix1][choix2] = 2;
                    iaactif = 0;
                    tour++;
                }

            }

        }
        else if (ia == 2 && tour % 2 != 0 && tour < 8 && verif_morpion(grille) == 0)   // Ia difficile
        {

            int temp;
            int compteur = 0;
            int resultx = 0;
            int resulty = 0;


            for (int i = 0; i < 3; i++)
            {

                temp = grille[0][i];
                if (temp == 0)
                {
                    temp = grille[1][i];

                }

                for (int j = 0; j < 3; j++)
                {
                    if (grille[j][i] == temp)
                    {
                        compteur++;
                    }
                    else
                    {
                        resultx = j;
                        resulty = i;
                    }


                }
                if (compteur == 2 && grille[resultx][resulty] == 0 && verif_morpion(grille) == 0 && tour % 2 == 1)
                {

                    SDL_BlitSurface(Rond, NULL, ecran, &position[resultx][resulty]);
                    grille[resultx][resulty] = 2;
                    tour++;
                }
                compteur = 0;

            }
            if (tour % 2 != 0 && verif_morpion(grille) == 0)
            {
                for (int i = 0; i < 3; i++)
                {
                    temp = grille[i][0];
                    if (temp == 0)
                    {
                        temp = grille[i][1];
                    }
                    for (int j = 0; j < 3; j++)
                    {
                        if (grille[i][j] == temp)
                        {
                            compteur++;
                        }
                        else
                        {
                            resultx = i;
                            resulty = j;
                        }
                    }
                    if (compteur == 2 && grille[resultx][resulty] == 0 && verif_morpion(grille) == 0)
                    {
                        SDL_BlitSurface(Rond, NULL, ecran, &position[resultx][resulty]);
                        grille[resultx][resulty] = 2;
                        tour++;
                    }
                    compteur = 0;
                }
            }
            if (tour % 2 != 0 && grille[1][1] == 0 && verif_morpion(grille) == 0)
            {
                SDL_BlitSurface(Rond, NULL, ecran, &position[1][1]);
                grille[1][1] = 2;
                tour++;

            }
            if (tour % 2 != 0 && grille[1][1] == 1 && verif_morpion(grille) == 0)
            {
                if (grille[0][0] == 1 && grille[2][2] == 0)
                {
                    SDL_BlitSurface(Rond, NULL, ecran, &position[2][2]);
                    grille[2][2] = 2;
                    tour++;
                }
                else if (grille[2][2] == 1 && grille[0][0] == 0)
                {
                    SDL_BlitSurface(Rond, NULL, ecran, &position[0][0]);
                    grille[0][0] = 2;
                    tour++;
                }
                else if (grille[0][2] == 1 && grille[2][0] == 0)
                {
                    SDL_BlitSurface(Rond, NULL, ecran, &position[2][0]);
                    grille[2][0] = 2;
                    tour++;
                }
                else if (grille[2][0] == 1 && grille[0][2] == 0)
                {
                    SDL_BlitSurface(Rond, NULL, ecran, &position[0][2]);
                    grille[0][2] = 2;
                    tour++;
                }
            }
            if (tour % 2 != 0 && verif_morpion(grille) == 0)
            {


                iaactif = 1;
                while (iaactif == 1)
                {
                    choix1 = rand() % 3;
                    choix2 = rand() % 3;
                    if (grille[choix1][choix2] == 0)
                    {
                        SDL_BlitSurface(Rond, NULL, ecran, &position[choix1][choix2]);
                        grille[choix1][choix2] = 2;
                        iaactif = 0;
                        tour++;
                    }
                }
            }
        }

        if (verif_morpion(grille) != 0) // Si on a un vainqueur
        {
            todo = win_screen_morpion(ecran, verif_morpion(grille));

            if (todo == 0)
                return 1;
            else if (todo == 1)
            {

                SDL_BlitSurface(menu, NULL, ecran, &position_menu);
                SDL_BlitSurface(fond, NULL, ecran, &position_fond);

                for (int i = 0; i < 3; i++)
                {
                    for (int j = 0; j < 3; j++)
                    {
                        grille[i][j] = 0;
                    }
                }
                tour = 0;
            }
            else if (todo == 2)
                return 0;

        }
        SDL_Flip(ecran);
    }
    return 0;
}

int verif_morpion(int grille[3][3]) // Verification des conditions de victoire
{
    if (grille[0][0] == grille[0][1] && grille[0][0] == grille[0][2] && grille[0][0] != 0)
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
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (grille[i][j] == 0)
                    return 0; // Aucun vainqueur
            }
        }
        return 3; // Egalité
    }

}

int win_screen_morpion(SDL_Surface *ecran, int joueur)
{

    int continuer = 1;
    SDL_Surface *Joueur = NULL, *state = NULL;
    SDL_Rect pos_joueur, pos_state;


    SDL_Event event;

    if (joueur == 1)
    {
        state = IMG_Load("ressources/victoire.png");
        Joueur = IMG_Load("ressources/croix.png");
        pos_joueur.x = 700;
        pos_state.x = 750;
        pos_joueur.y = 120;
        pos_state.y = 50;

        SDL_BlitSurface(Joueur, NULL, ecran, &pos_joueur);
        SDL_BlitSurface(state, NULL, ecran, &pos_state);
        SDL_Flip(ecran);

    }
    if (joueur == 2)
    {
        state = IMG_Load("ressources/victoire.png");
        Joueur = IMG_Load("ressources/rond.png");


        pos_joueur.x = 700;
        pos_state.x = 750;
        pos_joueur.y = 120;
        pos_state.y = 50;

        SDL_BlitSurface(Joueur, NULL, ecran, &pos_joueur);
        SDL_BlitSurface(state, NULL, ecran, &pos_state);
        SDL_Flip(ecran);

    }
    if (joueur == 3)
    {

        state = IMG_Load("ressources/draw.png");
        Joueur = IMG_Load("ressources/rond.png");

        pos_state.x = 750;
        pos_state.y = 50;

        SDL_BlitSurface(state, NULL, ecran, &pos_state);
        SDL_Flip(ecran);

    }
    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            return 2;

        case SDL_MOUSEBUTTONDOWN:
            if (event.button.x > 630 + 43 && event.button.x < 630 + 53 + 264 && event.button.y > 552 &&
                    event.button.y < 552 + 56)
            {
                return 0;
            }
            else if (event.button.x > 650 + 43 && event.button.x < 650 + 53 + 264 && event.button.y > 460 &&
                     event.button.y < 520) // Nouvelle partie
                return 1;
        }
    }
    return 0;
}
