#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

#include "GameResources.h"
#include "GameShow.h"
#include "GameControl.h"

int main(int argc, char* argv[])
{
    int running = 1;
    int paused = 0;
    SDL_Surface *ecran = NULL;

    GameResources gResources;
    GameShowObjects gShowObjects;
    GameControl gControl = {&gResources, &gShowObjects};

    unsigned int pausedTime = 0;
    unsigned int pauseBegin = 0;

    SDL_Init(SDL_INIT_VIDEO);

    ecran = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Supercopter", NULL);
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 17, 206, 112));

    loadResources(&gResources);
    initGame(&gControl);
    loadLevel(1, &gControl);

    while(running)
    {
        SDL_Event event;
        SDL_Event *eventptr = NULL;

        if(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                running = 0;
            }
            else if(!paused && event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_p)
            {
                pauseBegin = SDL_GetTicks();
                paused = 1;
            }
            else if(paused && event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_p)
            {
                pausedTime += SDL_GetTicks() - pauseBegin;
                paused = 0;
            }
            else
            {
                eventptr = &event;
            }
        }

        if(paused)
        {
            processEventsPaused(&gControl, eventptr);
        }
        else
        {
            processEvents(&gControl, SDL_GetTicks() - pausedTime, eventptr);
        }

        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 17, 206, 112));

        showGame(ecran, &gShowObjects);

        SDL_Flip(ecran);
    }

    freeResources(&gResources);

    SDL_Quit();

    return EXIT_SUCCESS;
}

