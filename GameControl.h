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

    float helicoSpeed,
          hostagesSpeed,
          bulletsSpeed,
          tanksSpeed;

    int tanksShotInterval;
    int tanksNextShot;

    unsigned int hostagesInHelico;

    unsigned int minimumHostagesFreeGoal;

    unsigned int lifeCount;
    unsigned int level;
    int win;
};

void initGame(GameControl *ctrl);
void quitGame(GameControl* ctrl);

void loadLevel(GameControl *ctrl, unsigned int level);
void spawnEnnemies(GameControl *ctrl);

SDL_Event* processEventsPaused(GameControl *ctrl, SDL_Event *event);
SDL_Event* processEvents(GameControl *ctrl, unsigned int currentTime, SDL_Event *event);

void calculateBulletsCollisions(GameControl *ctrl);
void calculateBombsCollisions(GameControl* ctrl);

int intersect(const SDL_Rect *rect_a, const SDL_Rect *rest_b);

void looselife(GameControl *ctrl);

#endif // GAMECONTROL_H
