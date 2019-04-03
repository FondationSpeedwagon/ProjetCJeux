/* Fichier tronr.c

Fondation Speedwagon

Fonction du tron race
*/

#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <string.h>

#include "structures.h"
#include "constantes.h"

int win_screen_tronr(SDL_Surface *, int); // ecran de victoire

int tronr(SDL_Surface *, int); // Fonction principale

int select_tronr(SDL_Surface *ecran) // Selection du mode
{
    surface menu;
    SDL_Event event; //Initialisation des surfaces

    int continuer = 1;

    menu.surface = IMG_Load("ressources/menu_tronr.png");

    menu.rect.x = 0;
    menu.rect.y = 0;

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            return 0;
        case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                if (event.button.x > 320 && event.button.x < 680)
                {
                    if (event.button.y > 210 && event.button.y < 280)
                    {
                        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
                        if (tronr(ecran, 0) == 0)
                            continuer = 0;
                    }
                    else if (event.button.y > 310 && event.button.y < 380)
                    {
                        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
                        if (tronr(ecran, 1) == 0)
                            continuer = 0;
                    }
                }
                else if (event.button.x > 630 + 43 && event.button.x < 630 + 53 + 264 && event.button.y > 552 &&
                         event.button.y < 552 + 56)

                    return 1;

            }

        }

        SDL_BlitSurface(menu.surface, NULL, ecran, &menu.rect);
        SDL_Flip(ecran);
    }
    SDL_FreeSurface(menu.surface);
    return 0;
}


int tronr(SDL_Surface *ecran, int replay)
{
    SDL_Event event;
    surface J_1, J_2, menu, joueur, touches_1, touches_2, tourDe;

    FILE *save = NULL;
    char chaine[1000];

    int direction = 0;
    int tableau[23][23];
    int tour = 1; // Le tour du joueur
    if (replay == 0) // Ouverture des fichiers de sauvegarde en fonction du mode
        save = fopen("sauvegardes/tron", "w");
    else
    {
        save = fopen("sauvegardes/tron", "r");
        if (fgets(chaine, 1000, save) == NULL)
            return 1;

        fclose(save);
    }
    int boucle = 0; // Compteur de boucle

    SDL_FillRect(ecran, NULL, GRIS);

    J_1.pos.y = 11;
    J_1.pos.x = 6;
    J_2.pos.x = 11;
    J_2.pos.y = 16;

    J_1.rect.y = 10 * 30;
    J_1.rect.x = 5 * 30;
    J_1.surface = CARRE;
    SDL_FillRect(J_1.surface, NULL, ROUGE);

    J_2.rect.y = 10 * 30;
    J_2.rect.x = 15 * 30;
    J_2.surface = CARRE;
    SDL_FillRect(J_2.surface, NULL, BLEU);

    tourDe.surface = IMG_Load("ressources/tour_tron.png");
    tourDe.rect.x = 680;
    tourDe.rect.y = 150;

    menu.surface = IMG_Load("ressources/menu_tronr_jeu.png");
    menu.rect.x = 630;
    menu.rect.y = 0;

    joueur.surface = NULL;
    joueur.rect.x = 800;
    joueur.rect.y = 200;

    touches_1.surface = IMG_Load("ressources/touches_J1.png");
    touches_1.rect.x = 700;
    touches_1.rect.y = 300;

    touches_2.surface = IMG_Load("ressources/touches_J2.png");
    touches_2.rect.x = 700;
    touches_2.rect.y = 300;

    SDL_BlitSurface(menu.surface, NULL, ecran, &menu.rect);

    if (replay == 0)
    {
        SDL_BlitSurface(tourDe.surface, NULL, ecran, &tourDe.rect);
        SDL_BlitSurface(J_1.surface, NULL, ecran, &joueur.rect);
        SDL_BlitSurface(touches_1.surface, NULL, ecran, &touches_1.rect);
    }


    for (int i = 0; i < 23; i++)
    {
        for (int j = 0; j < 23; j++)
        {
            if (i == 0 || i == 22 || j == 0 || j == 22)
            {
                tableau[i][j] = 3; // Remplissage du tableau

            }
            else
            {
                tableau[i][j] = 0;
            }
        }
    }

    tableau[J_1.pos.y][J_1.pos.x] = 1; //Positions initiales
    tableau[J_2.pos.x][J_2.pos.y] = 2;


    while (tour != 0)
    {
        for (int i = 0; i < 23; i++)
        {
            for (int j = 0; j < 23; j++)
            {
                switch (tableau[i][j])
                {

                case 1:

                    SDL_BlitSurface(J_1.surface, NULL, ecran, &J_1.rect);
                    break;

                case 2:

                    SDL_BlitSurface(J_2.surface, NULL, ecran, &J_2.rect);
                    break;
                }
            }

        }


        if (replay == 1)
        {
            //Simulation d'un event pour ne pas rester bloque
            SDL_Event sdlevent;
            sdlevent.type = SDL_KEYDOWN;
            sdlevent.key.keysym.sym = SDLK_1;
            SDL_PushEvent(&sdlevent);
            SDL_Delay(50);
        }

        SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            return 0;

        case SDL_KEYDOWN:  // Gestion des events J1
            if (tour == 1 && replay == 0)
            {
                switch (event.key.keysym.sym)
                {
                case SDLK_s:
                    direction = 2;
                    break;
                case SDLK_w:
                    direction = 3;
                    break;
                case SDLK_a:
                    direction = 1;
                    break;
                case SDLK_d:
                    direction = 4;
                    break;
                default:
                    direction = 0;
                    break;
                }

            }
            else if (tour == 2 && replay == 0)
            {
                // Gestion des events J2
                switch (event.key.keysym.sym)
                {
                case SDLK_DOWN:
                    direction = 2;
                    break;
                case SDLK_UP:
                    direction = 3;
                    break;
                case SDLK_LEFT:
                    direction = 1;
                    break;
                case SDLK_RIGHT:
                    direction = 4;
                    break;
                default:
                    direction = 0;
                    break;

                }
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                if (event.button.x > 630 + 43 && event.button.x < 630 + 53 + 264 && event.button.y > 552 &&
                        event.button.y < 552 + 56) // Bouton retour
                {
                    if (replay == 0)
                        fclose(save);
                    tour = 0;
                }
            }

        default :
            direction = 0; // Si aucun event on ne déplace personne
            break;
        }

        if (replay == 1) // mode replay
        {
            direction = chaine[boucle] - 48; // Transformation du caractère en entier ( '1' = 48 en ASCII)
            boucle++;
        }


        if (tour == 1)
        {
            switch (direction)
            {
            case 4: // Gestion des deplacements Joueur 1

                if (replay == 1 || tableau[J_1.pos.y][J_1.pos.x + 1] == 0)
                {
                    tableau[J_1.pos.y][J_1.pos.x + 1] = 1;
                    J_1.rect.x += 30;
                    J_1.pos.x++;
                    tour = 2;
                    if (replay == 0)
                    {
                        SDL_BlitSurface(menu.surface, NULL, ecran, &menu.rect);
                        SDL_BlitSurface(J_2.surface, NULL, ecran, &joueur.rect);
                        SDL_BlitSurface(touches_2.surface, NULL, ecran, &touches_2.rect);
                        fprintf(save, "%d", direction);
                    }
                }
                else if (replay == 1 || tableau[J_1.pos.y][J_1.pos.x + 1] != 0)
                {
                    if (replay == 0)
                        fclose(save);
                    if (win_screen_tronr(ecran, 1) == 0)
                        return 0;
                    else
                        return 1;
                }
                break;


            case 2:

                if (replay == 1 || tableau[J_1.pos.y - 1][J_1.pos.x] == 0)
                {
                    tableau[J_1.pos.y - 1][J_1.pos.x] = 1;
                    J_1.pos.y--;
                    J_1.rect.y += 30;
                    tour = 2;
                    if (replay == 0)
                    {
                        SDL_BlitSurface(menu.surface, NULL, ecran, &menu.rect);
                        SDL_BlitSurface(J_2.surface, NULL, ecran, &joueur.rect);
                        SDL_BlitSurface(touches_2.surface, NULL, ecran, &touches_2.rect);
                        fprintf(save, "%d", direction);
                    }
                }
                else if (replay == 1 || tableau[J_1.pos.y - 1][J_1.pos.x] != 0)
                {
                    if (replay == 0)
                        fclose(save);
                    if (win_screen_tronr(ecran, 1) == 0)
                        return 0;
                    else
                        return 1;
                }
                break;
            case 3:

                if (replay == 1 || tableau[J_1.pos.y + 1][J_1.pos.x] == 0)
                {
                    tableau[J_1.pos.y + 1][J_1.pos.x] = 1;
                    J_1.pos.y++;
                    J_1.rect.y -= 30;
                    tour = 2;
                    if (replay == 0)
                    {
                        SDL_BlitSurface(menu.surface, NULL, ecran, &menu.rect);
                        SDL_BlitSurface(J_2.surface, NULL, ecran, &joueur.rect);
                        SDL_BlitSurface(touches_2.surface, NULL, ecran, &touches_2.rect);
                        fprintf(save, "%d", direction);
                    }
                }
                else if (replay == 1 || tableau[J_1.pos.y + 1][J_1.pos.x] != 0)
                {
                    if (replay == 0)
                        fclose(save);
                    if (win_screen_tronr(ecran, 1) == 0)
                        return 0;
                    else
                        return 1;
                }
                break;
            case 1:

                if (replay == 1 || tableau[J_1.pos.y][J_1.pos.x - 1] == 0)
                {
                    tableau[J_1.pos.y][J_1.pos.x - 1] = 1;
                    J_1.pos.x--;
                    J_1.rect.x -= 30;
                    tour = 2;
                    if (replay == 0)
                    {
                        SDL_BlitSurface(menu.surface, NULL, ecran, &menu.rect);
                        SDL_BlitSurface(J_2.surface, NULL, ecran, &joueur.rect);
                        SDL_BlitSurface(touches_2.surface, NULL, ecran, &touches_2.rect);
                        fprintf(save, "%d", direction);
                    }
                }
                else if (replay == 1 || tableau[J_1.pos.y][J_1.pos.x - 1] != 0)
                {
                    if (replay == 0)
                        fclose(save);
                    if (win_screen_tronr(ecran, 1) == 0)
                        return 0;
                    else
                        return 1;
                }
                break;

            }
        }
        else if (tour == 2)       // Deplacement joueur 2
        {
            switch (direction)
            {
            case 4:

                if (replay == 1 || tableau[J_2.pos.x][J_2.pos.y + 1] == 0)
                {
                    tableau[J_2.pos.x][J_2.pos.y + 1] = 2;
                    J_2.pos.y++;
                    J_2.rect.x += 30;
                    tour = 1;
                    if (replay == 0)
                    {
                        SDL_BlitSurface(menu.surface, NULL, ecran, &menu.rect);
                        SDL_BlitSurface(J_1.surface, NULL, ecran, &joueur.rect);
                        SDL_BlitSurface(touches_1.surface, NULL, ecran, &touches_1.rect);
                        fprintf(save, "%d", direction);
                    }
                }
                else if (replay == 1 || tableau[J_2.pos.x][J_2.pos.y + 1] != 0)
                {
                    if (replay == 0)
                        fclose(save);
                    if (win_screen_tronr(ecran, 2) == 0)
                        return 0;
                    else
                        return 1;
                }
                break;
            case 2:

                if (replay == 1 || tableau[J_2.pos.x - 1][J_2.pos.y] == 0)
                {
                    tableau[J_2.pos.x - 1][J_2.pos.y] = 2;
                    J_2.pos.x--;
                    J_2.rect.y += 30;
                    tour = 1;
                    if (replay == 0)
                    {
                        SDL_BlitSurface(menu.surface, NULL, ecran, &menu.rect);
                        SDL_BlitSurface(J_1.surface, NULL, ecran, &joueur.rect);
                        SDL_BlitSurface(touches_1.surface, NULL, ecran, &touches_1.rect);
                        fprintf(save, "%d", direction);
                    }
                }
                else if (replay == 1 || tableau[J_2.pos.x - 1][J_2.pos.y] != 0)
                {
                    if (replay == 0)
                        fclose(save);
                    if (win_screen_tronr(ecran, 2) == 0)
                        return 0;
                    else
                        return 1;
                }
                break;
            case 3:

                if (replay == 1 || tableau[J_2.pos.x + 1][J_2.pos.y] == 0)
                {
                    tableau[J_2.pos.x + 1][J_2.pos.y] = 2;
                    J_2.pos.x++;
                    J_2.rect.y -= 30;
                    tour = 1;
                    if (replay == 0)
                    {
                        SDL_BlitSurface(menu.surface, NULL, ecran, &menu.rect);
                        SDL_BlitSurface(J_1.surface, NULL, ecran, &joueur.rect);
                        SDL_BlitSurface(touches_1.surface, NULL, ecran, &touches_1.rect);
                        fprintf(save, "%d", direction);
                    }
                }
                else if (replay == 1 || tableau[J_2.pos.x + 1][J_2.pos.y] != 0)
                {
                    if (replay == 0)
                        fclose(save);
                    if (win_screen_tronr(ecran, 2) == 0)
                        return 0;
                    else
                        return 1;
                }
                break;
            case 1:

                if (replay == 1 || tableau[J_2.pos.x][J_2.pos.y - 1] == 0)
                {
                    tableau[J_2.pos.x][J_2.pos.y - 1] = 2;
                    J_2.pos.y--;
                    J_2.rect.x -= 30;
                    tour = 1;
                    if (replay == 0)
                    {
                        SDL_BlitSurface(menu.surface, NULL, ecran, &menu.rect);
                        SDL_BlitSurface(J_1.surface, NULL, ecran, &joueur.rect);
                        SDL_BlitSurface(touches_1.surface, NULL, ecran, &touches_1.rect);
                        fprintf(save, "%d", direction);
                    }
                }
                else if (replay == 1 || tableau[J_2.pos.x][J_2.pos.y - 1] != 0)
                {
                    if (replay == 0)
                        fclose(save);
                    if (win_screen_tronr(ecran, 2) == 0)
                        return 0;
                    else
                        return 1;
                }
                break;
            }
        }
        if (replay == 0)
            SDL_BlitSurface(tourDe.surface, NULL, ecran, &tourDe.rect);
        SDL_Flip(ecran);
    }

    return 1;
}


int win_screen_tronr(SDL_Surface *ecran, int joueur)
{
    int continuer = 1;
    SDL_Event event;

    surface J_1, J_2, menu;

    menu.surface = IMG_Load("ressources/tronr_victoire.png");
    J_1.surface = CARRE;
    J_2.surface = CARRE;
    SDL_FillRect(J_1.surface, NULL, SDL_MapRGB(ecran->format, 109, 179, 205));
    SDL_FillRect(J_2.surface, NULL, SDL_MapRGB(ecran->format, 220, 20, 60));

    menu.rect.x = 630;
    menu.rect.y = 0;
    J_1.rect.x = 790;
    J_2.rect.x = 790;
    J_1.rect.y = 225;
    J_2.rect.y = 225;
    SDL_BlitSurface(menu.surface, NULL, ecran, &menu.rect);
    if (joueur == 1)
    {
        SDL_BlitSurface(J_1.surface, NULL, ecran, &J_1.rect);
    }
    if (joueur == 2)
    {
        SDL_BlitSurface(J_2.surface, NULL, ecran, &J_2.rect);
    }
    SDL_Flip(ecran);

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            continuer = 0;

        case SDL_MOUSEBUTTONDOWN:
            if (event.button.x > 650 + 43 && event.button.x < 650 + 53 + 264 && event.button.y > 552 &&
                    event.button.y < 552 + 56)

                return 2; // Bouton retour


        }
    }
    return 0;
}
