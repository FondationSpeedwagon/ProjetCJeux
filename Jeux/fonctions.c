#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>

int verif_morpion(int grille[3][3]) {
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
