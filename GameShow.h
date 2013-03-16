#ifndef GAMESHOW_H
#define GAMESHOW_H

#include <SDL/SDL.h>

typedef struct GameShowObjects GameShowObjects;
struct GameShowObjects
{
    SDL_Surface *helico;
    SDL_Rect helicoPosition;

    SDL_Surface *buildings[100];
    SDL_Rect buildingsPosition[100];
    unsigned int buildingsNb;
};

void showGame(SDL_Surface *ecran, GameShowObjects *gso);

#endif // GAMESHOW_H
