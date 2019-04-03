/* Fichier structures.c

Fondation Speedwagon

structures des surfaces
*/

#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED

typedef struct position position;
typedef struct surface surface;

struct position
{
    int x;
    int y;
};
struct surface
{
    SDL_Surface *surface;
    SDL_Rect rect;
    position pos;
    FILE *log;
};

#endif // STRUCTURES_H_INCLUDED
