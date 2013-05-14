#ifndef GAMERESOURCES_H_INCLUDED
#define GAMERESOURCES_H_INCLUDED

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

typedef struct GameResources GameResources;
struct GameResources
{
    TTF_Font *font;

    SDL_Surface *helicoL,
                *helicoR,
                *base,
                *building,
                *buildingD,
                *bomb,
                *hostage;
};

void loadResources(GameResources *res);
void freeResources(GameResources *res);

#endif // GAMERESOURCES_H_INCLUDED
