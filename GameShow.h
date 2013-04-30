#ifndef GAMESHOW_H
#define GAMESHOW_H

#include <SDL/SDL.h>

typedef struct GameShowObjects GameShowObjects;
struct GameShowObjects
{
    SDL_Surface *helico;
    SDL_Rect helicoPosition;

    SDL_Surface *base;
    SDL_Rect basePosition;

    SDL_Surface *buildings[100];
    SDL_Rect buildingsPosition[100];
    unsigned int buildingHostages[100];
    unsigned int buildingsNb;

    SDL_Surface *bombs[100];
    SDL_Rect bombsPosition[100];
    unsigned int bombsNb;

    SDL_Surface *hostages[100];
    SDL_Rect hostagesPosition[100];
    unsigned int hostagesFrame;
    unsigned int hostagesNb;

    SDL_Rect backgroundPosition;
};

void showGame(SDL_Surface *ecran, GameShowObjects *gso);

#endif // GAMESHOW_H
