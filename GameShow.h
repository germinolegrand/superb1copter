#ifndef GAMESHOW_H
#define GAMESHOW_H

#include <SDL/SDL.h>
#include <SDL/SDL_TTF.h>

typedef struct Movement Movement;
struct Movement
{
    int x, y;
};

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
    unsigned int buildingHostagesNb;

    SDL_Surface *bombs[100];
    SDL_Rect bombsPosition[100];
    unsigned int bombsNb;

    SDL_Surface *bullets[100];
    SDL_Rect bulletsPosition[100];
    Movement bulletsMovement[100];
    unsigned int bulletsNb;

    SDL_Surface *ennemies[100];
    SDL_Rect ennemiesPosition[100];
    unsigned int ennemiesNb;

    SDL_Surface *hostages[100];
    SDL_Rect hostagesPosition[100];
    unsigned int hostagesNb;

    SDL_Surface *baseHostages[100];
    SDL_Rect baseHostagesPosition[100];
    unsigned int baseHostagesNb;

    SDL_Rect backgroundPosition;

    SDL_Surface *background;

    ///Interface
    SDL_Surface *interface_hostagesInHelico;
    SDL_Surface *interface_hostagesWaiting;
    SDL_Surface *interface_hostagesFree;
    ///VIES
    SDL_Surface *interface_lifeCount;
    ///Level
    SDL_Surface *interface_levelCount;
    ///WIN
    SDL_Surface *interface_winloose;
};

void showGame(SDL_Surface *ecran, GameShowObjects *gso, unsigned int currentTime);

SDL_Surface* updateCounter(SDL_Surface *surface, TTF_Font *font, const char* text, int count);
SDL_Surface* updateCounter2(SDL_Surface *surface, TTF_Font *font, const char* text, int count1, int count2);

SDL_Surface* updateAnnonce(SDL_Surface* surface, TTF_Font *font, const char* text,SDL_Color color);

#endif // GAMESHOW_H
