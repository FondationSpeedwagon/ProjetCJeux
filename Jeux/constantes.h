/* Fichier constantes.h

Fondation Speedwagon

Constantes
*/


#ifndef CONSTANTES_H_INCLUDED
#define CONSTANTES_H_INCLUDED

#define LARGEUR_ECRAN  1000
#define HAUTEUR_ECRAN  630

//////////////////////////////////////////////////
#define NOIR SDL_MapRGB(ecran->format, 0,0,0)
#define ROUGE SDL_MapRGB(ecran->format, 220, 20, 60)
#define BLEU SDL_MapRGB(ecran->format, 109, 179, 205)
#define GRIS SDL_MapRGB(ecran->format, 14, 13, 15)

//////////////////////////////////////////////////
#define TAILLE_GRILLE_P4 7

//////////////////////////////////////////////////

#define CARRE SDL_CreateRGBSurface(SDL_HWSURFACE, 30, 30, 32, 0, 0, 0, 0)

#endif // CONSTANTES_H_INCLUDED
