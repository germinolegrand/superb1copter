#ifndef GAMERESOURCES_H_INCLUDED
#define GAMERESOURCES_H_INCLUDED

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "Audio.h"
/**
    Les ressources du jeu
**/
typedef struct GameResources GameResources;
struct GameResources
{
    Audio *audio;

    FMOD_SOUND *bgMusic1;

    TTF_Font *font;

    SDL_Surface *helicoL,
                *helicoR,
                *base,
                *building,
                *buildingD,
                *bomb,
                *bullet,
                *hostage,
                *tankL,
                *tankR,
                *background;
};

void loadResources(GameResources *res);
void freeResources(GameResources *res);

#endif // GAMERESOURCES_H_INCLUDED
