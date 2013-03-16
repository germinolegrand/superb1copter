#ifndef GAMERESOURCES_H_INCLUDED
#define GAMERESOURCES_H_INCLUDED

#include <SDL/SDL.h>

typedef struct GameResources GameResources;
struct GameResources
{
    SDL_Surface *helicoL,
                *helicoR,
                *building;
};

void loadResources(GameResources *res);
void freeResources(GameResources *res);

#endif // GAMERESOURCES_H_INCLUDED
