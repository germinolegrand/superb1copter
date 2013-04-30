#include "GameControl.h"

#include <string.h>

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
        gso->buildingsNb = 3;

        gso->buildings[0] = res->building;
        gso->buildingsPosition[0].x = 0;
        gso->buildingsPosition[0].y = -gso->buildings[0]->h;
        gso->buildingHostages[0] = 5;

        gso->buildings[1] = res->building;
        gso->buildingsPosition[1].x = 1200;
        gso->buildingsPosition[1].y = -gso->buildings[1]->h;
        gso->buildingHostages[1] = 5;

        gso->buildings[2] = res->building;
        gso->buildingsPosition[2].x = 900;
        gso->buildingsPosition[2].y = -gso->buildings[2]->h;
        gso->buildingHostages[2] = 5;

        gso->base = res->base;
        gso->basePosition.x = 500;
        gso->basePosition.y = -gso->base->h;

        gso->helico = res->helicoR;
        gso->helicoPosition.x = 400 - gso->helico->w/2;
        gso->helicoPosition.y = gso->basePosition.y - gso->helico->h;

        gso->bombsNb = 0;

        gso->hostagesFrame = 0;
        gso->hostagesNb = 0;

        gso->backgroundPosition.x = 400 - gso->basePosition.x - gso->base->w/2;
        gso->backgroundPosition.y = 400;
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

SDL_Event* processEventsNotPaused(GameControl *ctrl, SDL_Event *event)
{
    if(event)
    {
        switch(event->type)
        {
            case SDL_KEYDOWN:
                if(event->key.keysym.sym == SDLK_z)
                {
                    ctrl->gso->bombs[ctrl->gso->bombsNb] = ctrl->res->bomb;
                    ctrl->gso->bombsPosition[ctrl->gso->bombsNb].x = -ctrl->gso->backgroundPosition.x + ctrl->gso->helicoPosition.x + ctrl->gso->helico->w/2 - ctrl->res->bomb->w/2;
                    ctrl->gso->bombsPosition[ctrl->gso->bombsNb].y = ctrl->gso->helicoPosition.y + ctrl->gso->helico->h;
                    ++ctrl->gso->bombsNb;
                }
                break;
            case SDL_KEYUP:
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
    event = processEventsNotPaused(ctrl, event);

    if(currentTime - ctrl->previousTime > 10)
    {
        ctrl->gso->backgroundPosition.x -= ctrl->mvt.x * 6;

        ctrl->gso->helicoPosition.y += ctrl->mvt.y * 5;

        ///Si on a touché le sol
        if(ctrl->gso->helicoPosition.y + ctrl->gso->helico->h >= 0)
        {
            ctrl->gso->helicoPosition.y = -ctrl->gso->helico->h;

            ///activer la montée des otages
        }
        ///Si on sort de l'écran
        else if(ctrl->gso->helicoPosition.y + ctrl->gso->backgroundPosition.y <= 0)
        {
            ctrl->gso->helicoPosition.y = - ctrl->gso->backgroundPosition.y;
        }

        for(int i = 0; i < ctrl->gso->bombsNb; ++i)
        {
            ctrl->gso->bombsPosition[i].y += 5;

            ///Si la bombe touche le sol
            if(ctrl->gso->bombsPosition[i].y >= 0)
            {
                ctrl->gso->bombsPosition[i].y = 0;

                for(int j = 0; j < ctrl->gso->buildingsNb; ++j)
                {
                    ///Si elle touche un bâtiment non détruit
                    if(ctrl->gso->buildings[j] == ctrl->res->building
                       && ctrl->gso->bombsPosition[i].x > ctrl->gso->buildingsPosition[j].x
                          && ctrl->gso->bombsPosition[i].x < ctrl->gso->buildingsPosition[j].x + ctrl->gso->buildings[j]->w)
                    {
                        ctrl->gso->buildings[j] = ctrl->res->buildingD;

                        for(int k = 0; k < ctrl->gso->buildingHostages[j]; ++k)
                        {
                            ctrl->gso->hostages[ctrl->gso->hostagesNb + k] = ctrl->res->hostage;
                            ctrl->gso->hostagesPosition[ctrl->gso->hostagesNb + k].x = ctrl->gso->buildingsPosition[j].x + k*ctrl->res->hostage->h + 5;
                            ctrl->gso->hostagesPosition[ctrl->gso->hostagesNb + k].y = -ctrl->res->hostage->h;
                        }

                        ctrl->gso->hostagesNb += ctrl->gso->buildingHostages[j];
                    }
                }

                memmove(ctrl->gso->bombs + i, ctrl->gso->bombs + i + 1, (ctrl->gso->bombsNb - i - 1)*sizeof(SDL_Surface*));
                memmove(ctrl->gso->bombsPosition + i, ctrl->gso->bombsPosition + i + 1, (ctrl->gso->bombsNb - i - 1)*sizeof(SDL_Rect));
                --ctrl->gso->bombsNb;
                --i;
            }
        }

        ctrl->gso->helico = !ctrl->mvt.x ? ctrl->gso->helico : (ctrl->mvt.x > 0 ? ctrl->res->helicoR : ctrl->res->helicoL);

        ctrl->gso->hostagesFrame = (currentTime/500)%2;

        for(int i = 0; i < ctrl->gso->hostagesNb; ++i)
        {
            ctrl->gso->hostagesPosition[i].x += (ctrl->gso->hostagesPosition[i].x < -ctrl->gso->backgroundPosition.x + ctrl->gso->helicoPosition.x + ctrl->gso->helico->w/2) ? +1 : -1;
        }

        ctrl->previousTime = currentTime;
    }

    return event;
}
