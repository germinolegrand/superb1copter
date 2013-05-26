#ifndef GAMECONTROL_H
#define GAMECONTROL_H

#include <SDL/SDL.h>

#include "GameResources.h"
#include "GameShow.h"

typedef struct GameControl GameControl;
struct GameControl
{
    const GameResources *res;
    GameShowObjects *gso;

    int previousTime;

    Movement mvt;

    int helicoSpeed,
        bulletsSpeed;

    unsigned int hostagesInHelico;

    unsigned int minimumHostagesFreeGoal;
};

void initGame(GameControl *ctrl);
void loadLevel(unsigned int level, GameControl *ctrl);

SDL_Event* processEventsPaused(GameControl *ctrl, SDL_Event *event);
SDL_Event* processEvents(GameControl *ctrl, unsigned int currentTime, SDL_Event *event);

SDL_Surface* updateCounter(SDL_Surface *surface, TTF_Font *font, const char* text, int count);
SDL_Surface* updateCounter2(SDL_Surface *surface, TTF_Font *font, const char* text, int count1, int count2);

#endif // GAMECONTROL_H
