#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <string.h>
#include "structures.h"


int win_screen_tronr(SDL_Surface*, int);

void tronr(SDL_Surface *ecran, int replay)
{
    SDL_Event event;
    surface J_1, J_2, menu, joueur, touches_1, touches_2;

    FILE* save = NULL;
    char chaine[1000];

    int direction = 0;
    int tableau[25][25];
    int tour = 1;
    if (replay == 0)
        save = fopen("sauvegardes/tron", "w");
    else
    {
        save = fopen("sauvegardes/tron", "r");
        fgets(chaine, 1000, save);
        fclose(save);
        fprintf(stderr, "%d", strlen(chaine));
    }
    int boucle = 0;

    J_1.pos.x = 12;
    J_1.pos.y = 7;
    J_2.pos.x = 12;
    J_2.pos.y = 17;

    J_1.rect.y = 9 * 30;
    J_1.rect.x = 4 * 30;
    J_1.surface = SDL_CreateRGBSurface(SDL_HWSURFACE, 30, 30, 32, 0, 0, 0, 0);
    SDL_FillRect(J_1.surface, NULL, SDL_MapRGB(ecran->format, 255, 0, 0));

    J_2.rect.y = 9 * 30;
    J_2.rect.x = 14 * 30;
    J_2.surface = SDL_CreateRGBSurface(SDL_HWSURFACE, 30, 30, 32, 0, 0, 0, 0);
    SDL_FillRect(J_2.surface, NULL, SDL_MapRGB(ecran->format, 0, 255, 0));

    menu.surface = IMG_Load("ressources/menu_jeux.png");
    menu.rect.x = 630;
    menu.rect.y = 0;

    joueur.surface = NULL;
    joueur.rect.x = 900;
    joueur.rect.y = 50;

    touches_1.surface = IMG_Load("ressources/touches_J1.png");
    touches_1.rect.x = 700;
    touches_1.rect.y = 300;

    touches_2.surface = IMG_Load("ressources/touches_J2.png");
    touches_2.rect.x = 700;
    touches_2.rect.y = 300;

    SDL_BlitSurface(menu.surface, NULL, ecran, &menu.rect);

    if (replay == 0)
    {

        SDL_BlitSurface(J_1.surface, NULL, ecran, &joueur.rect);
        SDL_BlitSurface(touches_1.surface, NULL, ecran, &touches_1.rect);
    }


    for (int i = 0; i < 23; i++)
    {
        for (int j = 0; j < 24; j++)
        {
            if (i == 0 || i == 22 || j == 0 || j == 2)
            {
                tableau[i][j] = 3;
            }
            else
            {
                tableau[i][j] = 0;
            }
        }
    }
    tableau[12][7] = 1;

    tableau[12][17] = 2;

    while (tour != 0)
    {
        for (int i = 0; i < 24; i++)
        {
            for (int j = 0; j < 24; j++)
            {

                if (tableau[i][j] == 1)
                {
                    SDL_BlitSurface(J_1.surface, NULL, ecran, &J_1.rect);

                }
                else if (tableau[i][j] == 2)
                {
                    SDL_BlitSurface(J_2.surface, NULL, ecran, &J_2.rect);
                }
            }

        }


        if (tableau[J_1.pos.x][J_1.pos.y + 1] != 0 && tableau[J_1.pos.x][J_1.pos.y - 1] != 0 &&
                tableau[J_1.pos.x - 1][J_1.pos.y] != 0 && tableau[J_1.pos.x + 1][J_1.pos.y] != 0)
        {
            win_screen_tronr(ecran, 2);
            break;

        }
        else if (tableau[J_2.pos.x][J_2.pos.y + 1] != 0 && tableau[J_2.pos.x][J_2.pos.y - 1] != 0 &&
                 tableau[J_2.pos.x - 1][J_2.pos.y] != 0 && tableau[J_2.pos.x + 1][J_2.pos.y] != 0)
        {
            win_screen_tronr(ecran, 1);
            break;

        }
        if (replay == 1)
        {
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
            SDL_FreeSurface(ecran);
            SDL_Quit();

        case SDL_KEYDOWN:
            if (tour == 1 && replay == 0)
            {
                if (event.key.keysym.sym == SDLK_s)
                    direction = 2;
                else if (event.key.keysym.sym == SDLK_w)
                    direction = 3;
                else if (event.key.keysym.sym == SDLK_a)
                    direction = 1;
                else if (event.key.keysym.sym == SDLK_d)
                    direction = 4;
                else
                    direction = 0;



            }
            else if (tour == 2 && replay == 0)
            {

                if (event.key.keysym.sym == SDLK_DOWN)
                    direction = 2;
                else if (event.key.keysym.sym == SDLK_UP)
                    direction = 3;
                else if (event.key.keysym.sym == SDLK_LEFT)
                    direction = 1;
                else if (event.key.keysym.sym == SDLK_RIGHT)
                    direction = 4;
                else
                    direction = 0;

            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                if (event.button.x > 630 + 43 && event.button.x < 630 + 53 + 264 && event.button.y > 552 &&
                        event.button.y < 552 + 56)
                {
                    return;
                }
            }

        default :
            direction = 0;
            break;
        }

        if (replay == 1)
        {
            direction = chaine[boucle] - 48;
            boucle++;
        }


        if (tour == 1)
        {

            if (direction == 4)
            {
                if (replay == 1 || tableau[J_1.pos.x][J_1.pos.y + 1] == 0)
                {
                    tableau[J_1.pos.x][J_1.pos.y + 1] = 1;
                    J_1.rect.x += 30;
                    J_1.pos.y++;
                    tour = 2;
                    if (replay == 0)
                    {
                        SDL_BlitSurface(menu.surface, NULL, ecran, &menu.rect);
                        SDL_BlitSurface(J_2.surface, NULL, ecran, &joueur.rect);
                        SDL_BlitSurface(touches_2.surface, NULL, ecran, &touches_2.rect);
                        fprintf(save, "%d", direction);
                    }
                }

            }
            else if (direction == 2)
            {
                if (replay == 1 || tableau[J_1.pos.x - 1][J_1.pos.y] == 0)
                {
                    tableau[J_1.pos.x - 1][J_1.pos.y] = 1;
                    J_1.pos.x--;
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
            }
            else if (direction == 3)
            {
                if (replay == 1 || tableau[J_1.pos.x + 1][J_1.pos.y] == 0)
                {
                    tableau[J_1.pos.x + 1][J_1.pos.y] = 1;
                    J_1.pos.x++;
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
            }
            else if (direction == 1)
            {
                if (replay == 1 || tableau[J_1.pos.x][J_1.pos.y - 1] == 0)
                {
                    tableau[J_1.pos.x][J_1.pos.y - 1] = 1;
                    J_1.pos.y--;
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
            }


        }
        else if (tour == 2)
        {

            if (direction == 4)
            {
                if (replay == 1 ||tableau[J_2.pos.x][J_2.pos.y + 1] == 0)
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
            }
            else if (direction == 2)
            {
                if (replay == 1 ||tableau[J_2.pos.x - 1][J_2.pos.y] == 0)
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
            }
            else if (direction == 3)
            {
                if (replay == 1 ||tableau[J_2.pos.x + 1][J_2.pos.y] == 0)
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
            }
            else if (direction == 1)
            {
                if (replay == 1 ||tableau[J_2.pos.x][J_2.pos.y - 1] == 0)
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
            }

        }
        SDL_Flip(ecran);


    }
    if (replay == 0)
        fclose(save);
    return;
}


void select_tronr(SDL_Surface* ecran)
{
    SDL_Surface *menu = NULL;
    SDL_Rect position;
    SDL_Event event;

    int continuer = 1;

    menu = IMG_Load("ressources/menu_tronr.png");

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
                        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255,255,255));
                        tronr(ecran, 0);
                    }
                    else if (event.button.y > 310 && event.button.y < 380)
                    {
                        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255,255,255));
                        tronr(ecran, 1);
                    }
                }
                else if (event.button.x > 630 + 43 && event.button.x < 630 + 53 + 264 && event.button.y > 552 &&
                         event.button.y < 552 + 56)
                {
                    return;
                }


            }

        }
        SDL_BlitSurface(menu, NULL, ecran, &position);
        SDL_Flip(ecran);
    }


    SDL_FreeSurface(menu);
    SDL_Quit();
}

int win_screen_tronr(SDL_Surface *ecran, int joueur)
{
    int continuer = 1;
    SDL_Event event;

    surface J_1, J_2, menu, victoire;

    menu.surface = IMG_Load("ressources/menu_vierge.png");
    victoire.surface = IMG_Load("ressources/victoire.png");
    J_1.surface = SDL_CreateRGBSurface(SDL_HWSURFACE, 30, 30, 32, 0, 0, 0, 0);
    J_2.surface = SDL_CreateRGBSurface(SDL_HWSURFACE, 30, 30, 32, 0, 0, 0, 0);
    SDL_FillRect(J_1.surface, NULL, SDL_MapRGB(ecran->format, 255, 0, 0));
    SDL_FillRect(J_2.surface, NULL, SDL_MapRGB(ecran->format, 0, 255, 0));

    menu.rect.x = 630;
    menu.rect.y = 0;
    J_1.rect.x = 775;
    J_2.rect.x = 775;
    J_1.rect.y = 300;
    J_2.rect.y = 300;
    victoire.rect.x = 750;
    victoire.rect.y = 250;
    SDL_BlitSurface(menu.surface, NULL, ecran, &menu.rect);
    if (joueur == 1)
    {
        SDL_BlitSurface(J_1.surface, NULL, ecran, &J_1.rect);
    }
    if (joueur == 2)
    {
        SDL_BlitSurface(J_2.surface, NULL, ecran, &J_2.rect);
    }
    SDL_BlitSurface(victoire.surface, NULL, ecran, &victoire.rect);
    SDL_Flip(ecran);

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            SDL_FreeSurface(ecran);
            SDL_Quit();

        case SDL_MOUSEBUTTONDOWN:
            if (event.button.x > 650 + 43 && event.button.x < 650 + 53 + 264 && event.button.y > 552 &&
                    event.button.y < 552 + 56)

                return 0;

            else if (event.button.x > 650 + 43 && event.button.x < 650 + 53 + 264 && event.button.y > 460 &&
                     event.button.y < 520)

                return 1;


        }
    }
    return 0;
}


