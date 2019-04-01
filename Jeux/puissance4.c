#include <stdio.h>
#include <string.h>
#include <SDL.h>
#include <SDL_image.h>

void init_grille(int grille[6][7]);

void affichage(int grille[6][7], SDL_Surface *ecran, int*, int tour);

int verification(int grille[6][7], int position[2], int*);

int win_screen_p4(SDL_Surface*, int);


void puissance4(SDL_Surface *ecran)
{
    int tab_score[2] = {0,0};
    int tour = 1;
    int grille[7][7];
    int choix = 0;
    int verif = 0;
    SDL_Event event;
    int position[2];
    init_grille(grille);
    int continuer = 1;
    affichage(grille, ecran, tab_score, tour);

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

            if (event.button.button == SDL_BUTTON_LEFT )
            {
                if (event.button.x < 650)
                {
                    choix = (event.button.x - 40) / 84;
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
                            position[0] = choix;
                            position[1] = i++;
                            break;
                        }
                    }

                    verif = verification(grille, position, tab_score);
                    affichage(grille, ecran, tab_score, tour);

                    if (verif != 0)
                    {
                        if (win_screen_p4(ecran, verif) == 0)
                            return;
                        else
                        {
                            init_grille(grille);
                            tab_score[0]=0;
                            tab_score[1] = 0;
                            SDL_BlitSurface(img_grille, NULL, ecran, &rect_grille);
                            tour = 1;
                            affichage(grille, ecran, tab_score, tour);
                        }

                    }
                    SDL_Flip(ecran);
                }
                else if (event.button.x > 650+53 && event.button.x < 650+53 + 264 && event.button.y > 552 &&
                         event.button.y < 552 + 56) //Bouton quitter
                {
                    return;
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
            fprintf(stderr, "%d", grille[6][5]);
            break;

        }


    }


    return;
}

void init_grille(int grille[6][7])
{
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            grille[i][j] = 0;
        }
    }
}

void affichage(int grille[6][7], SDL_Surface *ecran, int *tab_score, int tour)
{
    SDL_Surface *pion_rouge = NULL, *pion_jaune = NULL, *un = NULL, *deux = NULL, *trois = NULL, *zero = NULL, *menu = NULL;
    SDL_Rect rect_rouge, rect_jaune, chiffre_1, chiffre_2, couleur_1, couleur_2, rect_menu, rect_actif;

    pion_rouge = IMG_Load("ressources/pionrouge.png");
    pion_jaune = IMG_Load("ressources/pionjaune.png");

    zero = IMG_Load("ressources/0.png");
    un = IMG_Load("ressources/1.png");
    deux = IMG_Load("ressources/2.png");
    trois = IMG_Load("ressources/3.png");

    menu = IMG_Load("ressources/menu_jeux.png");



    chiffre_1.x = 800;
    chiffre_2.x = 800;
    chiffre_1.y = 200;
    chiffre_2.y = 300;

    couleur_1.x = 700;
    couleur_2.x = 700;
    couleur_1.y = 200;
    couleur_2.y = 300;

    rect_menu.x = 650;
    rect_menu.y = 0;

    rect_actif.x = 750;
    rect_actif.y = 75;


    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            switch (grille[i][j])
            {
            case 1:
                rect_rouge.x = 40 + 84 * j;
                rect_rouge.y = 31 + 83 * i;
                SDL_BlitSurface(pion_rouge, NULL, ecran, &rect_rouge);
                break;
            case 2:
                rect_jaune.x = 40 + 84 * j;
                rect_jaune.y = 31 + 83 * i;
                SDL_BlitSurface(pion_jaune, NULL, ecran, &rect_jaune);
                break;
            }
        }
    }
    SDL_BlitSurface(menu, NULL, ecran, &rect_menu);
    if (tour == 1)
        SDL_BlitSurface(pion_rouge, NULL, ecran, &rect_actif);
    else
        SDL_BlitSurface(pion_jaune, NULL, ecran, &rect_actif);


    SDL_BlitSurface(pion_rouge, NULL, ecran, &couleur_1);
    SDL_BlitSurface(pion_jaune, NULL, ecran, &couleur_2);
    fprintf(stderr, "%d", tab_score[0]);
    switch (tab_score[0])
    {
    case 0:

        SDL_BlitSurface(zero, NULL, ecran, &chiffre_1);
        break;
    case 1:
        SDL_BlitSurface(un, NULL, ecran, &chiffre_1);
        break;
    case 2:
        SDL_BlitSurface(deux, NULL, ecran, &chiffre_1);
        break;
    case 3:
        SDL_BlitSurface(trois, NULL, ecran, &chiffre_1);
        break;

    }

    switch (tab_score[1])
    {
    case 0:
        SDL_BlitSurface(zero, NULL, ecran, &chiffre_2);
        break;
    case 1:
        SDL_BlitSurface(un, NULL, ecran, &chiffre_2);
        break;
    case 2:
        SDL_BlitSurface(deux, NULL, ecran, &chiffre_2);
        break;
    case 3:
        SDL_BlitSurface(trois, NULL, ecran, &chiffre_2);
        break;

    }




}

int verification(int grille[6][7], int position[2], int* tab_score)
{

    int temp = 0;
    int compteur = 1;

    temp = grille[position[1]][position[0]];
    if(tab_score[temp-1]==0)
        tab_score[temp-1] = 1;
    int verif1 = 1;
    int verif2 = 1;

    for (int i = 1; i<4; i++)
    {

        if(grille[position[1]+i][position[0]+i] == temp && verif1 && position[1]+i<6 && position[0]+i <7)
        {
            compteur +=1;
            if (compteur>tab_score[temp-1])
                tab_score[temp-1] = compteur;
        }
        else
            verif1 = 0;

        if(grille[position[1]-i][position[0]-i] == temp && verif2 && position[1]-i>=0 && position[0]-i >=0 )
        {
            compteur +=1;
            if (compteur>tab_score[temp-1])
                tab_score[temp-1] = compteur;

        }
        else
            verif2 = 0;
    }

    if (compteur >= 4)
        return temp;
    verif1 = 1;
    verif2 = 1;
    compteur = 1;

    for (int i = 1; i<4; i++)
    {

        if(grille[position[1]-i][position[0]+i] == temp && verif1 && position[1]-i>=0  && position[0]+i <7)
        {
            compteur +=1;
            if (compteur>tab_score[temp-1])
                tab_score[temp-1] = compteur;

        }
        else
            verif1 = 0;

        if(grille[position[1]+i][position[0]-i] == temp && verif2 && position[1]+i<6 && position[0]-i >=0 )
        {
            compteur +=1;
            if (compteur>tab_score[temp-1])
                tab_score[temp-1] = compteur;
        }
        else
            verif2 = 0;
    }


    ////////////////



    if (compteur >= 4)
        return temp;
    compteur = 1;
    temp = 0;
    for (int j = 5; j >= 0; j--)
    {
        if (grille[j][position[0]] == temp)
        {
            compteur++;

            if (compteur>tab_score[temp-1])
                tab_score[temp-1] = compteur;
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

    for (int j = 0; j < 7; j++)
    {
        if (grille[position[1]][j] == temp)
        {
            compteur++;
            if (compteur>tab_score[temp-1])
                tab_score[temp-1] = compteur;
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
    fprintf(stderr, "%d\n", joueur); // Écriture de l'erreur
    int continuer = 1;
    SDL_Event event;

    SDL_Surface *Rouge = NULL, *Jaune = NULL, *Gagne = NULL, *menu = NULL;
    SDL_Rect pos_couleur, pos_gagne, pos_menu;
    menu = IMG_Load("ressources/menu_vierge.png");
    Rouge = IMG_Load("ressources/pionrouge.png");
    Jaune = IMG_Load("ressources/pionjaune.png");
    Gagne = IMG_Load("ressources/Gagne.png");
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


