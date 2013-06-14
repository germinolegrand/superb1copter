#include "GameControl.h"

#include <string.h>

void initGame(GameControl* ctrl)
{
    ctrl->mvt.x = 0;
    ctrl->mvt.y = 0;

    ///Interface
    ctrl->gso->interface_hostagesInHelico = NULL;
    ctrl->gso->interface_hostagesWaiting = NULL;
    ctrl->gso->interface_hostagesFree = NULL;
    ctrl->gso->interface_lifeCount = NULL;
    ctrl->gso->interface_levelCount = NULL;
    ctrl->gso->interface_winloose = NULL;
}

void quitGame(GameControl* ctrl)
{
    ///Interface
    SDL_FreeSurface(ctrl->gso->interface_hostagesInHelico);
    SDL_FreeSurface(ctrl->gso->interface_hostagesWaiting);
    SDL_FreeSurface(ctrl->gso->interface_hostagesFree);
    SDL_FreeSurface(ctrl->gso->interface_lifeCount);
    SDL_FreeSurface(ctrl->gso->interface_levelCount);
    SDL_FreeSurface(ctrl->gso->interface_winloose);
}


void loadLevel(unsigned int level, GameControl *ctrl)
{
    const GameResources *res = ctrl->res;
    GameShowObjects *gso = ctrl->gso;

    ctrl->previousTime = SDL_GetTicks();

    ctrl->hostagesInHelico = 0;

    ctrl->helicoSpeed = 6;
    ctrl->hostagesSpeed = 1;
    ctrl->bulletsSpeed = 9;
    ctrl->tanksSpeed = 1;

    ctrl->tanksShotInterval = 1000;
    ctrl->tanksNextShot = ctrl->previousTime + ctrl->tanksShotInterval;

    ctrl->lifeCount = 3;
    ctrl->win = 0;

    ///Interface
    ctrl->gso->interface_lifeCount = updateCounter(ctrl->gso->interface_lifeCount, ctrl->res->font, "Vies : %d", ctrl->lifeCount);
    ctrl->gso->interface_levelCount = updateCounter(ctrl->gso->interface_levelCount, ctrl->res->font, "Niveau : %d", level);
    SDL_Color annonce_color = {255,255,255};
    ctrl->gso->interface_winloose = updateAnnonce(ctrl->gso->interface_winloose, ctrl->res->font, "", annonce_color);

    ///Niveau 1
    if(level == 1)
    {
        gso->buildingsNb = 3;
        gso->buildingHostagesNb = gso->buildingsNb*16;

        gso->buildings[0] = res->building;
        gso->buildingsPosition[0].x = 500;
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
        gso->basePosition.x = 0;
        gso->basePosition.y = -gso->base->h;

        gso-> helico = res->helicoR;
        gso->helicoPosition.x = 400 - gso->helico->w/2;
        gso->helicoPosition.y = gso->basePosition.y - gso->helico->h;

        gso->bombsNb = 0;

        gso->bulletsNb = 0;

        gso->ennemiesNb = 2;

        gso->ennemies[0] = res->tankL;
        gso->ennemiesPosition[0].x = 3000;
        gso->ennemiesPosition[0].y = -gso->ennemies[0]->h;

        gso->ennemies[1] = res->tankL;
        gso->ennemiesPosition[1].x = 2000;
        gso->ennemiesPosition[1].y = -gso->ennemies[1]->h;

        gso->hostagesNb = 0;

        gso->baseHostagesNb = 0;

        gso->backgroundPosition.x = 400 - gso->basePosition.x - gso->base->w/2;
        gso->backgroundPosition.y = 400;

        ctrl->minimumHostagesFreeGoal = 25;

        ///Interface
        gso->interface_hostagesInHelico = updateCounter(gso->interface_hostagesInHelico, res->font, "Otages dans l'helico : %d/16", ctrl->hostagesInHelico);
        gso->interface_hostagesWaiting = updateCounter(gso->interface_hostagesWaiting, res->font, "Otages a sauver : %d", gso->hostagesNb);
        gso->interface_hostagesFree = updateCounter2(gso->interface_hostagesFree, res->font, "Otages libres : %d/%d", gso->baseHostagesNb, ctrl->minimumHostagesFreeGoal);

        ///Audio
        audioPlayBackgroundMusic(res->audio, res->bgMusic3);
    }

    ///Niveau 2
    else if(level == 2)
    {
        gso->buildingsNb = 3;
        gso->buildingHostagesNb = gso->buildingsNb*16;

        gso->buildings[0] = res->building;
        gso->buildingsPosition[0].x = 500;
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
        gso->basePosition.x = 0;
        gso->basePosition.y = -gso->base->h;

        gso->helico = res->helicoR;
        gso->helicoPosition.x = 400 - gso->helico->w/2;
        gso->helicoPosition.y = gso->basePosition.y - gso->helico->h;

        gso->bombsNb = 0;

        gso->bulletsNb = 0;

        gso->ennemiesNb = 2;

        gso->ennemies[0] = res->tankL;
        gso->ennemiesPosition[0].x = 3000;
        gso->ennemiesPosition[0].y = -gso->ennemies[0]->h;

        gso->ennemies[1] = res->tankL;
        gso->ennemiesPosition[1].x = 2000;
        gso->ennemiesPosition[1].y = -gso->ennemies[1]->h;

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
        audioPlayBackgroundMusic(res->audio, res->bgMusic3);
    }

    ///Niveau 3
    else if(level == 3)
    {
        gso->buildingsNb = 3;
        gso->buildingHostagesNb = gso->buildingsNb*16;

        gso->buildings[0] = res->building;
        gso->buildingsPosition[0].x = 500;
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
        gso->basePosition.x = 0;
        gso->basePosition.y = -gso->base->h;

        gso->helico = res->helicoR;
        gso->helicoPosition.x = 400 - gso->helico->w/2;
        gso->helicoPosition.y = gso->basePosition.y - gso->helico->h;

        gso->bombsNb = 0;

        gso->bulletsNb = 0;

        gso->ennemiesNb = 2;

        gso->ennemies[0] = res->tankL;
        gso->ennemiesPosition[0].x = 3000;
        gso->ennemiesPosition[0].y = -gso->ennemies[0]->h;

        gso->ennemies[1] = res->tankL;
        gso->ennemiesPosition[1].x = 2000;
        gso->ennemiesPosition[1].y = -gso->ennemies[1]->h;

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
        audioPlayBackgroundMusic(res->audio, res->bgMusic3);
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
                    ctrl->gso->bulletsPosition[ctrl->gso->bulletsNb].x = -ctrl->gso->backgroundPosition.x + ctrl->gso->helicoPosition.x + ctrl->gso->helico->w*(ctrl->gso->helico == ctrl->res->helicoR) + ctrl->res->bullet->w*(ctrl->gso->helico == ctrl->res->helicoR);
                    ctrl->gso->bulletsPosition[ctrl->gso->bulletsNb].y = ctrl->gso->helicoPosition.y + ctrl->gso->helico->h/2;

                    ctrl->gso->bulletsMovement[ctrl->gso->bulletsNb].x = (ctrl->gso->helico == ctrl->res->helicoR) ? +1 : -1;
                    ctrl->gso->bulletsMovement[ctrl->gso->bulletsNb].y = 0;
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
        ctrl->gso->helicoPosition.y += ctrl->mvt.y * ctrl->helicoSpeed;

        ///Si l'hélico n'est pas au sol
        if(ctrl->gso->helicoPosition.y + ctrl->gso->helico->h < 0)
        {
            ///On autorise le mouvement horizontal
            ctrl->gso->backgroundPosition.x -= ctrl->mvt.x * ctrl->helicoSpeed;

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
                    ctrl->gso->baseHostages[ctrl->gso->baseHostagesNb] = ctrl->res->hostageL;
                    ctrl->gso->baseHostagesPosition[ctrl->gso->baseHostagesNb].x = ctrl->gso->basePosition.x + ctrl->res->hostageL->h*(ctrl->gso->baseHostagesNb%(ctrl->gso->base->w/ctrl->res->hostageL->h));
                    ctrl->gso->baseHostagesPosition[ctrl->gso->baseHostagesNb].y = ctrl->res->hostageL->h*(-((ctrl->gso->baseHostagesNb/(ctrl->gso->base->w/ctrl->res->hostageL->h)) + 1));
                }

                ctrl->hostagesInHelico = 0;

                ctrl->gso->interface_hostagesFree = updateCounter2(ctrl->gso->interface_hostagesFree, ctrl->res->font, "Otages libres : %d/%d", ctrl->gso->baseHostagesNb, ctrl->minimumHostagesFreeGoal);
                ctrl->gso->interface_hostagesInHelico = updateCounter(ctrl->gso->interface_hostagesInHelico, ctrl->res->font, "Otages dans l'helico : %d/16", ctrl->hostagesInHelico);
            }
            ///Si l'hélico s'est posé en terrain ennemi
            else
            {
                ///Les otages se rapprochent de l'hélico
                for(int i = 0; i < ctrl->gso->hostagesNb; ++i)
                {
                    ///Si l'otage est à gauche de l'hélico
                    if(ctrl->gso->hostagesPosition[i].x < helicoRealPosition_x)
                    {
                        ///Il va à droite
                        ctrl->gso->hostages[i] = ctrl->res->hostageR;
                        ctrl->gso->hostagesPosition[i].x += ctrl->hostagesSpeed;
                    }
                    ///Si l'otage est à droite de l'hélico
                    else if(ctrl->gso->hostagesPosition[i].x > helicoRealPosition_x)
                    {
                        ///Il va à gauche
                        ctrl->gso->hostages[i] = ctrl->res->hostageL;
                        ctrl->gso->hostagesPosition[i].x -= ctrl->hostagesSpeed;
                    }

                    ///S'il y a suffisamment de place et que l'otage est proche de l'hélico
                    if(ctrl->hostagesInHelico < 16 //TODO CONST
                       && ctrl->gso->hostagesPosition[i].x + ctrl->gso->hostages[i]->h/2 > helicoRealPosition_x - ctrl->gso->helico->w/2 - 10 //TODO CONST
                       && ctrl->gso->hostagesPosition[i].x + ctrl->gso->hostages[i]->h/2 < helicoRealPosition_x + ctrl->gso->helico->w/2 + 10)//TODO CONST
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
            ctrl->gso->bombsPosition[i].y += 5;//TODO CONST

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
                            ctrl->gso->hostages[ctrl->gso->hostagesNb + k] = ctrl->res->hostageL;
                            ctrl->gso->hostagesPosition[ctrl->gso->hostagesNb + k].x = ctrl->gso->buildingsPosition[j].x + k*ctrl->res->hostageL->h + 5;
                            ctrl->gso->hostagesPosition[ctrl->gso->hostagesNb + k].y = -ctrl->res->hostageL->h;
                        }

                        ctrl->gso->hostagesNb += ctrl->gso->buildingHostages[j];
                        ctrl->gso->buildingHostagesNb -= ctrl->gso->buildingHostages[j];
                    }
                }

                memmove(ctrl->gso->bombs + i, ctrl->gso->bombs + i + 1, (ctrl->gso->bombsNb - i - 1)*sizeof(SDL_Surface*));
                memmove(ctrl->gso->bombsPosition + i, ctrl->gso->bombsPosition + i + 1, (ctrl->gso->bombsNb - i - 1)*sizeof(SDL_Rect));
                --ctrl->gso->bombsNb;
                --i;
            }
        }

        ///Les bullets se déplacent
        for(int i = 0; i < ctrl->gso->bulletsNb; ++i)
        {
            ctrl->gso->bulletsPosition[i].x += ctrl->bulletsSpeed*ctrl->gso->bulletsMovement[i].x;
            ctrl->gso->bulletsPosition[i].y += ctrl->bulletsSpeed*ctrl->gso->bulletsMovement[i].y;

            int helicoRealPosition_x = -ctrl->gso->backgroundPosition.x + ctrl->gso->helicoPosition.x + ctrl->gso->helico->w/2;

            ///Si les bullets sortent du jeu
            if(ctrl->gso->bulletsPosition[i].y + ctrl->gso->backgroundPosition.y <= 0
               //TODO c'est buggé
               || ctrl->gso->bulletsPosition[i].x - helicoRealPosition_x > 500 || ctrl->gso->bulletsPosition[i].x - helicoRealPosition_x < -500)//TODO CONST
            {
                memmove(ctrl->gso->bullets + i, ctrl->gso->bullets + i + 1, (ctrl->gso->bulletsNb - i - 1)*sizeof(SDL_Surface*));
                memmove(ctrl->gso->bulletsPosition + i, ctrl->gso->bulletsPosition + i + 1, (ctrl->gso->bulletsNb - i - 1)*sizeof(SDL_Rect));
                memmove(ctrl->gso->bulletsMovement + i, ctrl->gso->bulletsMovement + i + 1, (ctrl->gso->bulletsNb - i - 1)*sizeof(SDL_Rect));
                --ctrl->gso->bulletsNb;
                --i;
            }
        }

        ///Les ennemis se déplacent
        for(int i = 0; i < ctrl->gso->ennemiesNb; ++i)
        {
            int helicoRealPosition_x = -ctrl->gso->backgroundPosition.x + ctrl->gso->helicoPosition.x + ctrl->gso->helico->w/2;

            ///Si c'est un tank
            if(ctrl->gso->ennemies[i] == ctrl->res->tankL
               || ctrl->gso->ennemies[i] == ctrl->res->tankR)
            {
                int tank_helico_position_difference = ctrl->gso->ennemiesPosition[i].x - helicoRealPosition_x;

                if(tank_helico_position_difference != 0)
                {
                    ctrl->gso->ennemiesPosition[i].x += (tank_helico_position_difference < 0 ? +1 : -1)*ctrl->tanksSpeed;
                    ctrl->gso->ennemies[i] = (tank_helico_position_difference < 0 ? ctrl->res->tankR : ctrl->res->tankL);
                }

                ///Si le tank est assez proche de l'hélico
                if(abs(tank_helico_position_difference) < 300 && ctrl->gso->helicoPosition.y > -300)//TODO CONST
                {
                    if(currentTime > ctrl->tanksNextShot)
                    {
                        ctrl->tanksNextShot = currentTime + ctrl->tanksShotInterval;

                        ctrl->gso->bullets[ctrl->gso->bulletsNb] = ctrl->res->bomb;
                        ctrl->gso->bulletsPosition[ctrl->gso->bulletsNb].x = ctrl->gso->ennemiesPosition[i].x + (ctrl->gso->ennemies[i] == ctrl->res->tankR)*ctrl->gso->ennemies[i]->w + (ctrl->gso->ennemies[i] == ctrl->res->tankL ? -1 : 0)*ctrl->gso->bullets[ctrl->gso->bulletsNb]->w;
                        ctrl->gso->bulletsPosition[ctrl->gso->bulletsNb].y = -ctrl->gso->ennemies[i]->h;

                        ctrl->gso->bulletsMovement[ctrl->gso->bulletsNb].x = (ctrl->gso->ennemies[i] == ctrl->res->tankL ? -1 : 1)*1.f;
                        ctrl->gso->bulletsMovement[ctrl->gso->bulletsNb].y = 0.5f;

                        ++ctrl->gso->bulletsNb;
                    }
                }
            }
        }

        calculateBulletsCollisions(ctrl);
        calculateBombsCollisions(ctrl);

        if(ctrl->hostagesInHelico == 0 && ctrl->gso->buildingHostagesNb == 0 && ctrl->gso->hostagesNb == 0)
        {
            ///Si on a gagné
            if(ctrl->gso->baseHostagesNb >= ctrl->minimumHostagesFreeGoal)
            {
                ///Audio
                audioPlayBackgroundMusic(ctrl->res->audio, ctrl->res->win);
                SDL_Color annonce_color = {0,255,0};
                ctrl->gso->interface_winloose = updateAnnonce(ctrl->gso->interface_winloose, ctrl->res->font, "Vous avez gagne !", annonce_color);
                ctrl->win = 1;
            }
            ///Si on a perdu
            else
            {
                ///Audio
                audioPlayBackgroundMusic(ctrl->res->audio, ctrl->res->loose);
                SDL_Color annonce_color = {255,0,0};
                ctrl->gso->interface_winloose = updateAnnonce(ctrl->gso->interface_winloose, ctrl->res->font, "Vous avez perdu !", annonce_color);
                ctrl->win = -1;
            }
        }

        ///Si l'hélico est en mouvement
        if(ctrl->mvt.x)
        {
            ///L'hélico est tourné dans le bon sens
            ctrl->gso->helico = ctrl->mvt.x > 0 ? ctrl->res->helicoR : ctrl->res->helicoL;
        }

        ctrl->previousTime = currentTime;
    }

    return event;
}

void calculateBulletsCollisions(GameControl *ctrl)
{
    SDL_Rect helicoRect =
    {
        -ctrl->gso->backgroundPosition.x + ctrl->gso->helicoPosition.x,
        ctrl->gso->helicoPosition.y,
        ctrl->gso->helico->w,
        ctrl->gso->helico->h
    };

    ///Pour chaque bullet
    for(int i = 0; i < ctrl->gso->bulletsNb; ++i)
    {
        SDL_Rect bulletRect =
        {
            ctrl->gso->bulletsPosition[i].x,
            ctrl->gso->bulletsPosition[i].y,
            ctrl->gso->bullets[i]->w,
            ctrl->gso->bullets[i]->h
        };

        ///Si collision avec l'hélico
        if(intersect(&helicoRect, &bulletRect))
        {
            ///On perd une vie !
            looselife(ctrl);
            ///Exploser la bullet
            memmove(ctrl->gso->bullets + i, ctrl->gso->bullets + i + 1, (ctrl->gso->bulletsNb - i - 1)*sizeof(SDL_Surface*));
            memmove(ctrl->gso->bulletsPosition + i, ctrl->gso->bulletsPosition + i + 1, (ctrl->gso->bulletsNb - i - 1)*sizeof(SDL_Rect));
            --ctrl->gso->bulletsNb;
            --i;

            return;
        }

        ///Pour chaque ennemi
        for(int j = 0; j < ctrl->gso->ennemiesNb; ++j)
        {
            SDL_Rect ennemyRect =
            {
                ctrl->gso->ennemiesPosition[j].x,
                ctrl->gso->ennemiesPosition[j].y,
                ctrl->gso->ennemies[j]->w,
                ctrl->gso->ennemies[j]->h
            };

            ///Si collision avec un ennemi
            if(intersect(&ennemyRect, &bulletRect))
            {
                ///Il est détruit !
                memmove(ctrl->gso->ennemies + j, ctrl->gso->ennemies + j + 1, (ctrl->gso->ennemiesNb - j - 1)*sizeof(SDL_Surface*));
                memmove(ctrl->gso->ennemiesPosition + j, ctrl->gso->ennemiesPosition + j + 1, (ctrl->gso->ennemiesNb - j - 1)*sizeof(SDL_Rect));
                --ctrl->gso->ennemiesNb;
                --j;

                ///Exploser la bullet
                memmove(ctrl->gso->bullets + i, ctrl->gso->bullets + i + 1, (ctrl->gso->bulletsNb - i - 1)*sizeof(SDL_Surface*));
                memmove(ctrl->gso->bulletsPosition + i, ctrl->gso->bulletsPosition + i + 1, (ctrl->gso->bulletsNb - i - 1)*sizeof(SDL_Rect));
                --ctrl->gso->bulletsNb;
                --i;
            }
        }

        ///Pour chaque otage
        for(int j = 0; j < ctrl->gso->hostagesNb; ++j)
        {
            SDL_Rect ennemyRect =
            {
                ctrl->gso->hostagesPosition[j].x,
                ctrl->gso->hostagesPosition[j].y,
                ctrl->gso->hostages[j]->w,
                ctrl->gso->hostages[j]->h
            };

            ///Si collision avec un otage
            if(intersect(&ennemyRect, &bulletRect))
            {
                ///Il est détruit !
                memmove(ctrl->gso->hostages + j, ctrl->gso->hostages + j + 1, (ctrl->gso->hostagesNb - j - 1)*sizeof(SDL_Surface*));
                memmove(ctrl->gso->hostagesPosition + j, ctrl->gso->hostagesPosition + j + 1, (ctrl->gso->hostagesNb - j - 1)*sizeof(SDL_Rect));
                --ctrl->gso->hostagesNb;
                --j;

                ctrl->gso->interface_hostagesWaiting = updateCounter(ctrl->gso->interface_hostagesWaiting, ctrl->res->font, "Otages a sauver : %d", ctrl->gso->hostagesNb);

                ///Exploser la bullet
                memmove(ctrl->gso->bullets + i, ctrl->gso->bullets + i + 1, (ctrl->gso->bulletsNb - i - 1)*sizeof(SDL_Surface*));
                memmove(ctrl->gso->bulletsPosition + i, ctrl->gso->bulletsPosition + i + 1, (ctrl->gso->bulletsNb - i - 1)*sizeof(SDL_Rect));
                --ctrl->gso->bulletsNb;
                --i;
            }
        }
    }
}

void calculateBombsCollisions(GameControl* ctrl)
{
    SDL_Rect helicoRect =
    {
        -ctrl->gso->backgroundPosition.x + ctrl->gso->helicoPosition.x,
        ctrl->gso->helicoPosition.y,
        ctrl->gso->helico->w,
        ctrl->gso->helico->h
    };

    ///Pour chaque bombe
    for(int i = 0; i < ctrl->gso->bombsNb; ++i)
    {
        SDL_Rect bombRect =
        {
            ctrl->gso->bombsPosition[i].x,
            ctrl->gso->bombsPosition[i].y,
            ctrl->gso->bombs[i]->w,
            ctrl->gso->bombs[i]->h
        };

        ///Si collision avec l'hélico
        if(intersect(&helicoRect, &bombRect))
        {
            ///On perd une vie !
            looselife(ctrl);
            ///Exploser la bombe
            memmove(ctrl->gso->bombs + i, ctrl->gso->bombs + i + 1, (ctrl->gso->bombsNb - i - 1)*sizeof(SDL_Surface*));
            memmove(ctrl->gso->bombsPosition + i, ctrl->gso->bombsPosition + i + 1, (ctrl->gso->bombsNb - i - 1)*sizeof(SDL_Rect));
            --ctrl->gso->bombsNb;
            --i;

            return;
        }

        ///Pour chaque ennemi
        for(int j = 0; j < ctrl->gso->ennemiesNb; ++j)
        {
            SDL_Rect ennemyRect =
            {
                ctrl->gso->ennemiesPosition[j].x,
                ctrl->gso->ennemiesPosition[j].y,
                ctrl->gso->ennemies[j]->w,
                ctrl->gso->ennemies[j]->h
            };

            ///Si collision avec un ennemi
            if(intersect(&ennemyRect, &bombRect))
            {
                ///Il est détruit !
                memmove(ctrl->gso->ennemies + j, ctrl->gso->ennemies + j + 1, (ctrl->gso->ennemiesNb - j - 1)*sizeof(SDL_Surface*));
                memmove(ctrl->gso->ennemiesPosition + j, ctrl->gso->ennemiesPosition + j + 1, (ctrl->gso->ennemiesNb - j - 1)*sizeof(SDL_Rect));
                --ctrl->gso->ennemiesNb;

                ///Exploser la bombe
                memmove(ctrl->gso->bombs + i, ctrl->gso->bombs + i + 1, (ctrl->gso->bombsNb - i - 1)*sizeof(SDL_Surface*));
                memmove(ctrl->gso->bombsPosition + i, ctrl->gso->bombsPosition + i + 1, (ctrl->gso->bombsNb - i - 1)*sizeof(SDL_Rect));
                --ctrl->gso->bombsNb;

                return;
            }
        }

        ///Pour chaque otage
        for(int j = 0; j < ctrl->gso->hostagesNb; ++j)
        {
            SDL_Rect hostageRect =
            {
                ctrl->gso->hostagesPosition[j].x,
                ctrl->gso->hostagesPosition[j].y,
                ctrl->gso->hostages[j]->h,
                ctrl->gso->hostages[j]->h
            };

            ///Si collision avec un otage
            if(intersect(&hostageRect, &bombRect))
            {
                ///Il est détruit !
                memmove(ctrl->gso->hostages + j, ctrl->gso->hostages + j + 1, (ctrl->gso->hostagesNb - j - 1)*sizeof(SDL_Surface*));
                memmove(ctrl->gso->hostagesPosition + j, ctrl->gso->hostagesPosition + j + 1, (ctrl->gso->hostagesNb - j - 1)*sizeof(SDL_Rect));
                --ctrl->gso->hostagesNb;

                ctrl->gso->interface_hostagesWaiting = updateCounter(ctrl->gso->interface_hostagesWaiting, ctrl->res->font, "Otages a sauver : %d", ctrl->gso->hostagesNb);

                ///Exploser la bombe
                memmove(ctrl->gso->bombs + i, ctrl->gso->bombs + i + 1, (ctrl->gso->bombsNb - i - 1)*sizeof(SDL_Surface*));
                memmove(ctrl->gso->bombsPosition + i, ctrl->gso->bombsPosition + i + 1, (ctrl->gso->bombsNb - i - 1)*sizeof(SDL_Rect));
                --ctrl->gso->bombsNb;

                return;
            }
        }
    }
}

int intersect(const SDL_Rect *rect_a, const SDL_Rect *rect_b)
{
    return rect_a->x < rect_b->x + rect_b->w // ok
        && rect_a->x + rect_a->w > rect_b->x // ok
        && rect_a->y < rect_b->y + rect_b->h //ok
        && rect_a->y + rect_a->h > rect_b->y; // ok
}



void looselife(GameControl *ctrl)
{
    --ctrl->lifeCount;
    ctrl->gso->interface_lifeCount = updateCounter(ctrl->gso->interface_lifeCount, ctrl->res->font, "Vies : %d", ctrl->lifeCount);

    if(ctrl->lifeCount == 2)
    {
                ///Audio
        audioPlayBackgroundMusic(ctrl->res->audio, ctrl->res->bgMusic2);
    }
    else if(ctrl->lifeCount == 1)
    {
                ///Audio
        audioPlayBackgroundMusic(ctrl->res->audio, ctrl->res->bgMusic1);
    }
    else if(ctrl->lifeCount == 0) /// On perd !
    {
        ///Audio
        audioPlayBackgroundMusic(ctrl->res->audio, ctrl->res->loose);
        SDL_Color annonce_color = {255,0,0};
        ctrl->gso->interface_winloose = updateAnnonce(ctrl->gso->interface_winloose, ctrl->res->font, "Vous avez perdu !", annonce_color);
        ctrl->win=-1;
    }
}




