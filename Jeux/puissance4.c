/* Fichier puissance4.c

Fondation Speedwagon

Fonction du puissance 4
*/


#include <stdio.h>
#include <string.h>
#include <SDL.h>
#include <SDL_image.h>
#include "constantes.h"
#include "structures.h"

void init_grille(int grille[TAILLE_GRILLE_P4][TAILLE_GRILLE_P4]);

void affichage(int grille[TAILLE_GRILLE_P4][TAILLE_GRILLE_P4], SDL_Surface *ecran, int *, int tour);

int verification(int grille[TAILLE_GRILLE_P4][TAILLE_GRILLE_P4], int position[2], int *);

int win_screen_p4(SDL_Surface *, int);

int puissance4(SDL_Surface *ecran)
{

    SDL_Event event;
    SDL_Surface *img_grille = NULL;
    SDL_Rect rect_grille;


    int tab_score[2] = {0, 0};
    int tour = 1;
    int grille[TAILLE_GRILLE_P4][TAILLE_GRILLE_P4];
    int choix = 0;
    int verif = 0;
    int todo = 0;
    int position[2];
    int continuer = 1;

    rect_grille.x = 0;
    rect_grille.y = 0;

    img_grille = IMG_Load("ressources/grille_p4.png");
    init_grille(grille);

    affichage(grille, ecran, tab_score, tour);
    SDL_BlitSurface(img_grille, NULL, ecran, &rect_grille);
    SDL_Flip(ecran);


    while (continuer == 1)
    {
        SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            return 0;
        case SDL_MOUSEBUTTONDOWN:

            if (event.button.button == SDL_BUTTON_LEFT) // Gestion et localisation du clic
            {
                if (event.button.x < 650)
                {
                    choix = (event.button.x - 40) / 84; // Localisation dans la colonne
                    for (int i = 5; i >= 0; i--) // Placement dans la colonne
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
                            position[0] = choix;
                            position[1] = i++;
                            break;
                        }
                    }

                    verif = verification(grille, position, tab_score); // Condition de victoire
                    affichage(grille, ecran, tab_score, tour);

                    if (verif != 0)
                    {
                        todo = win_screen_p4(ecran, verif); // Quoi faire quand on sort de l'écran
                        if (todo == 0)
                            return 1; // Retour au menu

                        else if (todo == 1)
                        {
                            init_grille(grille); // Rejouer une partie
                            tab_score[0] = 0;
                            tab_score[1] = 0;
                            SDL_BlitSurface(img_grille, NULL, ecran, &rect_grille);
                            tour = 1;
                            affichage(grille, ecran, tab_score, tour);
                        }
                        else
                            return 0; // quitter le jeu


                    }
                    SDL_Flip(ecran);
                }
                else if (event.button.x > 650 + 53 && event.button.x < 650 + 53 + 264 && event.button.y > 552 &&
                         event.button.y < 552 + 56) //Bouton quitter
                {
                    return 1;
                }
                else if (event.button.x > 650 + 43 && event.button.x < 650 + 53 + 264 && event.button.y > 460 &&
                         event.button.y < 520) // Nouvelle partie
                {
                    init_grille(grille);
                    tab_score[0] = 0;
                    tab_score[1] = 0;
                    SDL_BlitSurface(img_grille, NULL, ecran, &rect_grille);

                    tour = 1;
                    affichage(grille, ecran, tab_score, tour);
                    SDL_Flip(ecran);


                }

            }
            break;

        }


    }


    return 1;
}

void init_grille(int grille[TAILLE_GRILLE_P4][TAILLE_GRILLE_P4])
{
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            grille[i][j] = 0;
        }
    }
}

void affichage(int grille[TAILLE_GRILLE_P4][TAILLE_GRILLE_P4], SDL_Surface *ecran, int *tab_score, int tour)
{
    surface pion_rouge, pion_jaune, un, deux, trois, zero, menu;
    SDL_Rect chiffre_1, chiffre_2, couleur_1, couleur_2, rect_actif;  // Definition des surfaces

    pion_rouge.surface = IMG_Load("ressources/pionrouge.png");
    pion_jaune.surface = IMG_Load("ressources/pionjaune.png");

    zero.surface = IMG_Load("ressources/0.png");
    un.surface = IMG_Load("ressources/1.png");
    deux.surface = IMG_Load("ressources/2.png");
    trois.surface = IMG_Load("ressources/3.png");

    menu.surface = IMG_Load("ressources/menu_vierge.png");


    chiffre_1.x = 800;
    chiffre_2.x = 800;
    chiffre_1.y = 200;
    chiffre_2.y = 300;

    couleur_1.x = 700;
    couleur_2.x = 700;
    couleur_1.y = 200;
    couleur_2.y = 300;

    menu.rect.x = 650;
    menu.rect.y = 0;

    rect_actif.x = 750;
    rect_actif.y = 75;


    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            switch (grille[i][j]) // Placement des pions
            {
            case 1:
                pion_rouge.rect.x = 40 + 84 * j;
                pion_rouge.rect.y = 31 + 83 * i;
                SDL_BlitSurface(pion_rouge.surface, NULL, ecran, &pion_rouge.rect);
                break;
            case 2:
                pion_jaune.rect.x = 40 + 84 * j;
                pion_jaune.rect.y = 31 + 83 * i;
                SDL_BlitSurface(pion_jaune.surface, NULL, ecran, &pion_jaune.rect);
                break;
            }
        }
    }
    SDL_BlitSurface(menu.surface, NULL, ecran, &menu.rect);
    if (tour == 1)
        SDL_BlitSurface(pion_rouge.surface, NULL, ecran, &rect_actif);
    else
        SDL_BlitSurface(pion_jaune.surface, NULL, ecran, &rect_actif);


    SDL_BlitSurface(pion_rouge.surface, NULL, ecran, &couleur_1);
    SDL_BlitSurface(pion_jaune.surface, NULL, ecran, &couleur_2);
    switch (tab_score[0]) // Positionnement du plus gros alignement
    {
    case 0:

        SDL_BlitSurface(zero.surface, NULL, ecran, &chiffre_1);
        break;
    case 1:
        SDL_BlitSurface(un.surface, NULL, ecran, &chiffre_1);
        break;
    case 2:
        SDL_BlitSurface(deux.surface, NULL, ecran, &chiffre_1);
        break;
    case 3:
        SDL_BlitSurface(trois.surface, NULL, ecran, &chiffre_1);
        break;

    }

    switch (tab_score[1])
    {
    case 0:
        SDL_BlitSurface(zero.surface, NULL, ecran, &chiffre_2);
        break;
    case 1:
        SDL_BlitSurface(un.surface, NULL, ecran, &chiffre_2);
        break;
    case 2:
        SDL_BlitSurface(deux.surface, NULL, ecran, &chiffre_2);
        break;
    case 3:
        SDL_BlitSurface(trois.surface, NULL, ecran, &chiffre_2);
        break;

    }


}

int verification(int grille[TAILLE_GRILLE_P4][TAILLE_GRILLE_P4], int position[2], int *tab_score)
{

    int temp = 0;
    int compteur = 1;

    temp = grille[position[1]][position[0]];
    if (tab_score[temp - 1] == 0)
        tab_score[temp - 1] = 1;
    int verif1 = 1;
    int verif2 = 1;

    for (int i = 1; i < 4; i++)   //Diagonales
    {

        if (grille[position[1] + i][position[0] + i] == temp && verif1 && position[1] + i < 6 &&
                position[0] + i < TAILLE_GRILLE_P4)
        {
            compteur += 1;
            if (compteur > tab_score[temp - 1]) // Meilleur score
                tab_score[temp - 1] = compteur;
        }
        else
            verif1 = 0;

        if (grille[position[1] - i][position[0] - i] == temp && verif2 && position[1] - i >= 0 &&
                position[0] - i >= 0)
        {
            compteur += 1;
            if (compteur > tab_score[temp - 1]) // Meilleur score
                tab_score[temp - 1] = compteur;

        }
        else
            verif2 = 0;
    }

    if (compteur >= 4)
        return temp;
    verif1 = 1;
    verif2 = 1;
    compteur = 1;

    for (int i = 1; i < 4; i++)   // Diagonales
    {

        if (grille[position[1] - i][position[0] + i] == temp && verif1 && position[1] - i >= 0 &&
                position[0] + i < TAILLE_GRILLE_P4)
        {
            compteur += 1;
            if (compteur > tab_score[temp - 1]) // Meilleur score
                tab_score[temp - 1] = compteur;

        }
        else
            verif1 = 0;

        if (grille[position[1] + i][position[0] - i] == temp && verif2 && position[1] + i < 6 && position[0] - i >= 0)
        {
            compteur += 1;
            if (compteur > tab_score[temp - 1]) // Meilleur score
                tab_score[temp - 1] = compteur;
        }
        else
            verif2 = 0;
    }

    if (compteur >= 4)
        return temp;
    compteur = 1;
    temp = 0;
    for (int j = 5; j >= 0; j--)   //Colonnes
    {
        if (grille[j][position[0]] == temp)
        {
            compteur++;

            if (compteur > tab_score[temp - 1]) // Meilleur score
                tab_score[temp - 1] = compteur;
        }
        else
        {
            compteur = 1;
            temp = grille[j][position[0]];
        }
        if (temp == 0)
        {
            break;
        }

        if (compteur == 4)
            return temp;
    }
    temp = 0;
    compteur = 1;

    for (int j = 0; j < TAILLE_GRILLE_P4; j++)
    {
        //Lignes
        if (grille[position[1]][j] == temp)
        {
            compteur++;
            if (compteur > tab_score[temp - 1]) // Meilleur score
                tab_score[temp - 1] = compteur;
        }
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

int win_screen_p4(SDL_Surface *ecran, int joueur)
{
    int continuer = 1;
    SDL_Event event;
    SDL_Surface *Rouge = NULL, *Jaune = NULL, *Gagne = NULL, *menu = NULL;
    SDL_Rect pos_couleur, pos_gagne, pos_menu;
    menu = IMG_Load("ressources/menu_vierge.png");
    Rouge = IMG_Load("ressources/pionrouge.png");   // Definition des surfaces
    Jaune = IMG_Load("ressources/pionjaune.png");
    Gagne = IMG_Load("ressources/victoire.png");
    pos_menu.x = 650;
    pos_menu.y = 0;
    pos_couleur.x = 775;
    pos_gagne.x = 750;
    pos_couleur.y = 100;
    pos_gagne.y = 250;
    SDL_BlitSurface(menu, NULL, ecran, &pos_menu);
    if (joueur == 1)
    {
        SDL_BlitSurface(Rouge, NULL, ecran, &pos_couleur);
        SDL_BlitSurface(Gagne, NULL, ecran, &pos_gagne);
    }
    if (joueur == 2)
    {
        SDL_BlitSurface(Jaune, NULL, ecran, &pos_couleur);
        SDL_BlitSurface(Gagne, NULL, ecran, &pos_gagne);
    }
    SDL_Flip(ecran);

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            return 3;

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
