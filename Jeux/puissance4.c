#include <stdio.h>
#include <string.h>
#include <SDL.h>
#include <SDL_image.h>
#include "fonctions.h"

typedef struct joueur
{
    int score;
} joueur;

void init_grille(int grille[6][7]);

void affichage(int grille[6][7], SDL_Surface* ecran);

int verification(int grille[6][7], int position[2]);

void puissance4(SDL_Surface *ecran)
{
    joueur rouge;
    joueur jaune;
    int tour = 1;
    int grille[6][7];
    int choix;
    int verif = 0;
    SDL_Event event;
    int position[2];
    init_grille(grille);
    int continuer = 1;
    affichage(grille, ecran);
    rouge.score = 0;
    jaune.score = 0;
    SDL_Surface *img_grille = NULL;
    SDL_Rect rect_grille;
    rect_grille.x = 0;
    rect_grille.y = 0;
    img_grille = IMG_Load("ressources/grille_p4.png");
    SDL_BlitSurface(img_grille, NULL, ecran, &rect_grille);
    SDL_Flip(ecran);
    while (continuer == 1)
    {
        SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            SDL_FreeSurface(ecran);
            SDL_Quit();
        case SDL_MOUSEBUTTONDOWN:

            if(event.button.button == SDL_BUTTON_LEFT)
            {
                choix = (event.button.x - 40)/84;
                for (int i = 5; i >= 0; i--)
                {
                    if (grille[i][choix] == 0)
                    {
                        if (tour == 1)
                        {
                            grille[i][choix] = 1;
                            tour = 2;
                        }
                        else
                        {
                            grille[i][choix] = 2;
                            tour = 1;
                        }
                        position[0]=choix;
                        position[1]=i++;
                        break;
                    }
                    if (i == 0)
                        printf("Colonne deja pleine !\n");
                }
                affichage(grille, ecran);
                verif = verification(grille, position);
                if (verif!=0 )
                    win_screen(ecran,verif);
                SDL_Flip(ecran);
            }
            break;
        }


    }


    return;
}

void init_grille(int grille[6][7])
{
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            grille[i][j] = 0;
        }
    }
}

void affichage(int grille[6][7], SDL_Surface* ecran)
{
    SDL_Surface *pion_rouge = NULL, *pion_jaune = NULL;
    SDL_Rect rect_rouge, rect_jaune;
    pion_rouge = IMG_Load("ressources/pionrouge.png");
    pion_jaune = IMG_Load("ressources/pionjaune.png");
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            switch (grille[i][j])
            {
            case 1:
                rect_rouge.x = 40+84*j;
                rect_rouge.y = 31+83*i;
                SDL_BlitSurface(pion_rouge, NULL, ecran, &rect_rouge);
                break;
            case 2:
                rect_jaune.x = 40+84*j;
                rect_jaune.y = 31+83*i;
                SDL_BlitSurface(pion_jaune, NULL, ecran, &rect_jaune);
                break;
            }
        }
    }
}

int verification(int grille[6][7], int position[2])
{

    int temp = 0;
    int compteur = 1;

    /////


    temp = grille[position[1]][position[0]];
    int verif1 = 1;
    int verif2 = 1;

    for (int i = 1; i<4; i++)
    {

        if(grille[position[1]+i][position[0]+i] == temp && verif1)
        {
            compteur +=1;
        }
        else
            verif1 = 0;

        if(grille[position[1]-i][position[0]-i] == temp && verif2)
        {
            compteur +=1;

        }
        else
            verif2 = 0;
    }

    if (compteur == 4)
        return temp;
    verif1 = 1;
    verif2 = 1;
    compteur = 1;

    for (int i = 1; i<4; i++)
    {

        if(grille[position[1]-i][position[0]+i] == temp && verif1)
        {
            compteur +=1;

        }
        else
            verif1 = 0;

        if(grille[position[1]+i][position[0]-i] == temp && verif2)
        {
            compteur +=1;
        }
        else
            verif2 = 0;
    }


    ////////////////



    if (compteur == 4)
        return temp;
    compteur = 1;
    temp =0;
    for (int j = 5; j >= 0; j--)
    {
        if (grille[j][position[0]] == temp)
            compteur++;
        else
        {
            compteur = 1;
            temp = grille[j][position[0]];
        }
        if (temp == 0)
            break;
        if (compteur == 4)
            return temp;
    }
    temp = 0;
    compteur = 1;

    for (int j = 0; j < 7; j++)
    {
        if (grille[position[1]][j] == temp)
            compteur++;
        else
        {
            compteur = 1;
            temp = grille[position[1]][j];
        }
        if (compteur == 4)
            return temp;
    }


    return 0;
}
