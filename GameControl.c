#include "GameControl.h"

#include <string.h>

void initGame(GameControl* ctrl)
{
    ctrl->previousTime = SDL_GetTicks();
    ctrl->hostagesInHelico = 0;
    ctrl->mvt.x = 0;
    ctrl->mvt.y = 0;
}


void loadLevel(unsigned int level, GameControl *ctrl)
{
    const GameResources *res = ctrl->res;
    GameShowObjects *gso = ctrl->gso;

    ///Niveau 1
    if(level == 1)
    {
        gso->buildingsNb = 3;

        gso->buildings[0] = res->building;
        gso->buildingsPosition[0].x = 0;
        gso->buildingsPosition[0].y = -gso->buildings[0]->h;
        gso->buildingHostages[0] = 16;

        gso->buildings[1] = res->building;
        gso->buildingsPosition[1].x = 1200;
        gso->buildingsPosition[1].y = -gso->buildings[1]->h;
        gso->buildingHostages[1] = 16;

        gso->buildings[2] = res->building;
        gso->buildingsPosition[2].x = 900;
        gso->buildingsPosition[2].y = -gso->buildings[2]->h;
        gso->buildingHostages[2] = 16;

        gso->base = res->base;
        gso->basePosition.x = 500;
        gso->basePosition.y = -gso->base->h;

        gso->helico = res->helicoR;
        gso->helicoPosition.x = 400 - gso->helico->w/2;
        gso->helicoPosition.y = gso->basePosition.y - gso->helico->h;

        gso->bombsNb = 0;

        gso->bulletsNb = 0;

        gso->hostagesNb = 0;

        gso->baseHostagesNb = 0;

        gso->backgroundPosition.x = 400 - gso->basePosition.x - gso->base->w/2;
        gso->backgroundPosition.y = 400;

        ctrl->minimumHostagesFreeGoal = 25;

        ///Interface
        gso->interface_hostagesInHelico = updateCounter(NULL, res->font, "Otages dans l'helico : %d/16", ctrl->hostagesInHelico);
        gso->interface_hostagesWaiting = updateCounter(NULL, res->font, "Otages a sauver : %d", gso->hostagesNb);
        gso->interface_hostagesFree = updateCounter2(NULL, res->font, "Otages libres : %d/%d", gso->baseHostagesNb, ctrl->minimumHostagesFreeGoal);

        ///Audio
        audioPlayBackgroundMusic(res->audio, res->bgMusic1);
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
                if(event->key.keysym.sym == SDLK_x)
                {
                    ///L'hélico lache une bombe
                    ctrl->gso->bombs[ctrl->gso->bombsNb] = ctrl->res->bomb;
                    ctrl->gso->bombsPosition[ctrl->gso->bombsNb].x = -ctrl->gso->backgroundPosition.x + ctrl->gso->helicoPosition.x + ctrl->gso->helico->w/2 - ctrl->res->bomb->w/2;
                    ctrl->gso->bombsPosition[ctrl->gso->bombsNb].y = ctrl->gso->helicoPosition.y + ctrl->gso->helico->h;
                    ++ctrl->gso->bombsNb;
                }
                else if(event->key.keysym.sym == SDLK_z)
                {
                    ///L'hélico lance une bullet
                    ctrl->gso->bullets[ctrl->gso->bulletsNb] = ctrl->res->bullet;
                    ctrl->gso->bulletsPosition[ctrl->gso->bulletsNb].x = -ctrl->gso->backgroundPosition.x + ctrl->gso->helicoPosition.x + ctrl->gso->helico->w*(ctrl->gso->helico == ctrl->res->helicoR) - ctrl->res->bomb->w/2;
                    ctrl->gso->bulletsPosition[ctrl->gso->bulletsNb].y = ctrl->gso->helicoPosition.y + ctrl->gso->helico->h/2;
                    ++ctrl->gso->bulletsNb;
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
        ctrl->gso->helicoPosition.y += ctrl->mvt.y * 5;

        ///Si l'hélico n'est pas au sol
        if(ctrl->gso->helicoPosition.y + ctrl->gso->helico->h < 0)
        {
            ///On autorise le mouvement horizontal
            ctrl->gso->backgroundPosition.x -= ctrl->mvt.x * 6;

            ///On interdit la sortie de l'écran par le haut
            if(ctrl->gso->helicoPosition.y + ctrl->gso->backgroundPosition.y <= 0)
            {
                ctrl->gso->helicoPosition.y = - ctrl->gso->backgroundPosition.y;
            }
        }
        ///Si on a touché le sol
        else if(ctrl->gso->helicoPosition.y + ctrl->gso->helico->h >= 0)
        {
            ctrl->gso->helicoPosition.y = -ctrl->gso->helico->h;

            int helicoRealPosition_x = -ctrl->gso->backgroundPosition.x + ctrl->gso->helicoPosition.x + ctrl->gso->helico->w/2;

            ///Si l'hélico s'est posé dans la base
            if(helicoRealPosition_x > ctrl->gso->basePosition.x
               && helicoRealPosition_x < ctrl->gso->basePosition.x + ctrl->gso->base->w)
            {
                ///Les otages descendent
                for(int k = 0; k < ctrl->hostagesInHelico; ++k, ++ctrl->gso->baseHostagesNb)
                {
                    ctrl->gso->baseHostages[ctrl->gso->baseHostagesNb] = ctrl->res->hostage;
                    ctrl->gso->baseHostagesPosition[ctrl->gso->baseHostagesNb].x = ctrl->gso->basePosition.x + ctrl->res->hostage->h*(ctrl->gso->baseHostagesNb%(ctrl->gso->base->w/ctrl->res->hostage->h));
                    ctrl->gso->baseHostagesPosition[ctrl->gso->baseHostagesNb].y = ctrl->res->hostage->h*(-((ctrl->gso->baseHostagesNb/(ctrl->gso->base->w/ctrl->res->hostage->h)) + 1));

                    ctrl->gso->interface_hostagesFree = updateCounter2(ctrl->gso->interface_hostagesFree, ctrl->res->font, "Otages libres : %d/%d", ctrl->gso->baseHostagesNb, ctrl->minimumHostagesFreeGoal);
                }

                ctrl->hostagesInHelico = 0;

                ctrl->gso->interface_hostagesInHelico = updateCounter(ctrl->gso->interface_hostagesInHelico, ctrl->res->font, "Otages dans l'helico : %d/16", ctrl->hostagesInHelico);
            }
            ///Si l'hélico s'est posé en terrain ennemi
            else
            {
                ///Les otages se rapprochent de l'hélico
                for(int i = 0; i < ctrl->gso->hostagesNb; ++i)
                {
                    ctrl->gso->hostagesPosition[i].x += (ctrl->gso->hostagesPosition[i].x < helicoRealPosition_x) ? +1 : -1;

                    ///S'il y a suffisamment de place et que l'otage est proche de l'hélico
                    if(ctrl->hostagesInHelico < 16
                       && ctrl->gso->hostagesPosition[i].x > helicoRealPosition_x - 10
                       && ctrl->gso->hostagesPosition[i].x < helicoRealPosition_x + 10)
                    {
                        ///L'otage monte dans l'hélico
                        memmove(ctrl->gso->hostages + i, ctrl->gso->hostages + i + 1, (ctrl->gso->hostagesNb - i - 1)*sizeof(SDL_Surface*));
                        memmove(ctrl->gso->hostagesPosition + i, ctrl->gso->hostagesPosition + i + 1, (ctrl->gso->hostagesNb - i - 1)*sizeof(SDL_Rect));
                        --ctrl->gso->hostagesNb;
                        ++ctrl->hostagesInHelico;

                        ctrl->gso->interface_hostagesInHelico = updateCounter(ctrl->gso->interface_hostagesInHelico, ctrl->res->font, "Otages dans l'helico : %d/16", ctrl->hostagesInHelico);
                        ctrl->gso->interface_hostagesWaiting = updateCounter(ctrl->gso->interface_hostagesWaiting, ctrl->res->font, "Otages a sauver : %d", ctrl->gso->hostagesNb);
                    }
                }
            }
        }

        ///Les bombes tombent
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
                        ///Le bâtiment est détruit
                        ctrl->gso->buildings[j] = ctrl->res->buildingD;

                        ///Les otages sortent
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

        if(ctrl->mvt.x)
        {
            ///L'hélico est tourné dans le bon sens
            ctrl->gso->helico = ctrl->mvt.x > 0 ? ctrl->res->helicoR : ctrl->res->helicoL;
        }

        ctrl->previousTime = currentTime;
    }

    return event;
}


SDL_Surface* updateCounter(SDL_Surface* surface, TTF_Font *font, const char* text, int count)
{
    SDL_Color color = {0,0,0};
    char count_str[100];
    sprintf(count_str, text, count);

    if(surface)
        SDL_FreeSurface(surface);

    return TTF_RenderText_Blended(font, count_str, color);
}

SDL_Surface* updateCounter2(SDL_Surface *surface, TTF_Font *font, const char* text, int count1, int count2)
{
    SDL_Color color = {0,0,0};
    char count_str[100];
    sprintf(count_str, text, count1, count2);

    if(surface)
        SDL_FreeSurface(surface);

    return TTF_RenderText_Blended(font, count_str, color);
}
