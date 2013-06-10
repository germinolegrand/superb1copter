#ifndef GAMECONTROL_H
#define GAMECONTROL_H

#include <SDL/SDL.h>

#include "GameResources.h"
#include "GameShow.h"

typedef struct Collisions Collisions;
struct Collisions
{
    //unsigned int bullets[];
    unsigned int bulletsNb;
};

typedef struct GameControl GameControl;
struct GameControl
{
    const GameResources *res;
    GameShowObjects *gso;

    int previousTime;

    Movement mvt;

    float helicoSpeed,
          hostagesSpeed,
          bulletsSpeed,
          tanksSpeed;

    int tanksShotInterval;
    int tanksNextShot;

    unsigned int hostagesInHelico;

    unsigned int minimumHostagesFreeGoal;

    unsigned int lifeCount;

    //Collisions collisions;
};

void initGame(GameControl *ctrl);
void loadLevel(unsigned int level, GameControl *ctrl);

SDL_Event* processEventsPaused(GameControl *ctrl, SDL_Event *event);
SDL_Event* processEvents(GameControl *ctrl, unsigned int currentTime, SDL_Event *event);

void calculateCollisions();

#endif // GAMECONTROL_H
