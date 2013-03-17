#include "GameControl.h"

void initGame(GameControl* ctrl)
{
    ctrl->previousTime = SDL_GetTicks();
}


void loadLevel(unsigned int level, GameControl *ctrl)
{
    const GameResources *res = ctrl->res;
    GameShowObjects *gso = ctrl->gso;

    if(level == 1)
    {
        gso->backgroundPosition.x = -200;
        gso->backgroundPosition.y = 400;
        gso->buildingsNb = 3;

        gso->buildings[0] = res->building;
        gso->buildingsPosition[0].x = 0;
        gso->buildingsPosition[0].y = -gso->buildings[0]->h;

        gso->buildings[1] = res->building;
        gso->buildingsPosition[1].x = 500;
        gso->buildingsPosition[1].y = -gso->buildings[1]->h;

        gso->buildings[2] = res->building;
        gso->buildingsPosition[2].x = 900;
        gso->buildingsPosition[2].y = -gso->buildings[2]->h;

        gso->helicoPosition.x = 400;
        gso->helicoPosition.y = 300;
        gso->helico = res->helicoR;
    }
}

SDL_Event* processEventsPaused(GameControl *ctrl, SDL_Event *event)
{
    if(event)
    {
        switch(event->type)
        {
            case SDL_KEYDOWN:
                if(event->key.keysym.sym == SDLK_RIGHT)
                {
                    ctrl->mvt.x += 1;
                }
                else if(event->key.keysym.sym == SDLK_LEFT)
                {
                    ctrl->mvt.x -= 1;
                }
                else if(event->key.keysym.sym == SDLK_DOWN)
                {
                    ctrl->mvt.y += 1;
                }
                else if(event->key.keysym.sym == SDLK_UP)
                {
                    ctrl->mvt.y -= 1;
                }
                break;
            case SDL_KEYUP:
                if(event->key.keysym.sym == SDLK_RIGHT)
                {
                    ctrl->mvt.x -= 1;
                }
                else if(event->key.keysym.sym == SDLK_LEFT)
                {
                    ctrl->mvt.x += 1;
                }
                else if(event->key.keysym.sym == SDLK_DOWN)
                {
                    ctrl->mvt.y -= 1;
                }
                else if(event->key.keysym.sym == SDLK_UP)
                {
                    ctrl->mvt.y += 1;
                }
                break;
            default:
                break;
        }
    }

    return event;
}

SDL_Event* processEvents(GameControl *ctrl, unsigned int currentTime, SDL_Event *event)
{
    event = processEventsPaused(ctrl, event);

    if(currentTime - ctrl->previousTime > 10)
    {
        ctrl->gso->backgroundPosition.x -= ctrl->mvt.x * 6;
        ctrl->gso->helicoPosition.y += ctrl->mvt.y * 5;

        ctrl->gso->helico = !ctrl->mvt.x ? ctrl->gso->helico : (ctrl->mvt.x > 0 ? ctrl->res->helicoR : ctrl->res->helicoL);

        ctrl->previousTime = currentTime;
    }

    return event;
}
