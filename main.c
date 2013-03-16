#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

#include "GameResources.h"
#include "GameShow.h"

typedef struct Movement Movement;
struct Movement
{
    int x, y;
};







void loadLevel(unsigned int level, GameResources *res, GameShowObjects *gso)
{
    if(level == 1)
    {
        gso->buildingsNb = 0;

        gso->helicoPosition.x = 400;
        gso->helicoPosition.y = 100;
        gso->helico = res->helicoR;
    }
}




int main(int argc, char* argv[])
{
    int continuer = 1;
    SDL_Event event;
    SDL_Surface *ecran = NULL;
    SDL_Rect positionBackground = {0, 0};

    Movement mvt = {0,0};
    int tempsPrecedent = 0, tempsActuel = 0;

    GameResources gResources;
    GameShowObjects gShowObjects;

    SDL_Init(SDL_INIT_VIDEO);

    ecran = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Supercopter", NULL);
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 17, 206, 112));

    loadResources(&gResources);
    loadLevel(1, &gResources, &gShowObjects);

    while(continuer)
    {
        if(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    continuer = 0;
                    break;
                case SDL_KEYDOWN:
                    if(event.key.keysym.sym == SDLK_RIGHT)
                    {
                        mvt.x += 1;
                    }
                    else if(event.key.keysym.sym == SDLK_LEFT)
                    {
                        mvt.x -= 1;
                    }
                    else if(event.key.keysym.sym == SDLK_DOWN)
                    {
                        mvt.y += 1;
                    }
                    else if(event.key.keysym.sym == SDLK_UP)
                    {
                        mvt.y -= 1;
                    }
                    break;
                case SDL_KEYUP:
                    if(event.key.keysym.sym == SDLK_RIGHT)
                    {
                        mvt.x -= 1;
                    }
                    else if(event.key.keysym.sym == SDLK_LEFT)
                    {
                        mvt.x += 1;
                    }
                    else if(event.key.keysym.sym == SDLK_DOWN)
                    {
                        mvt.y -= 1;
                    }
                    else if(event.key.keysym.sym == SDLK_UP)
                    {
                        mvt.y += 1;
                    }
                    break;
                default:
                    break;
            }
        }

//        tempsActuel = SDL_GetTicks();
//
//        if(tempsActuel - tempsPrecedent > 10)
//        {
//            positionBackground.x += mvt.x * 5;
//            helicoPosition.y += mvt.y * 5;
//
//            helico = !mvt.x ? helico : (mvt.x > 0 ? helicoR : helicoL);
//
//            tempsPrecedent = tempsActuel;
//        }

        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 17, 206, 112));

        showGame(ecran, &gShowObjects);

        SDL_Flip(ecran);
    }

    freeResources(&gResources);

    SDL_Quit();

    return EXIT_SUCCESS;
}

