#ifndef GAMECONTROL_H
#define GAMECONTROL_H

#include <SDL/SDL.h>

#include "GameResources.h"
#include "GameShow.h"

typedef struct Movement Movement;
struct Movement
{
    int x, y;
};

typedef struct GameControl GameControl;
struct GameControl
{
    const GameResources *res;
    GameShowObjects *gso;

    int previousTime;

    Movement mvt;
};

void initGame(GameControl *ctrl);
void loadLevel(unsigned int level, GameControl *ctrl);

SDL_Event* processEventsPaused(GameControl *ctrl, SDL_Event *event);
SDL_Event* processEvents(GameControl *ctrl, unsigned int currentTime, SDL_Event *event);


#endif // GAMECONTROL_H
