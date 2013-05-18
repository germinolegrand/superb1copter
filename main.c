#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "Audio.h"
#include "GameResources.h"
#include "GameShow.h"
#include "GameControl.h"


int main(int argc, char* argv[])
{
    int running = 1;
    int paused = 0;
    SDL_Surface* ecran = NULL;

    unsigned int pausedTime = 0;
    unsigned int pauseBegin = 0;

    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    ecran = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Supercopter", NULL);

    Audio audio;

    audioInit(&audio);


    GameResources gResources;
    gResources.audio = &audio;

    loadResources(&gResources);


    GameShowObjects gShowObjects;

    GameControl gControl;
    gControl.res = &gResources;
    gControl.gso = &gShowObjects;

    initGame(&gControl);


    loadLevel(1, &gControl);


    while(running)
    {
        SDL_Event event;
        SDL_Event* eventptr = NULL;

        if(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_F4 && event.key.keysym.mod == KMOD_LALT))
            {
                running = 0;
            }
            else if(!paused && event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_p)
            {
                pauseBegin = SDL_GetTicks();
                paused = 1;

                audioPause(&audio, paused);
            }
            else if(paused && event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_p)
            {
                pausedTime += SDL_GetTicks() - pauseBegin;
                paused = 0;

                audioPause(&audio, paused);
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

        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 0, 0));

        showGame(ecran, &gShowObjects, SDL_GetTicks());

        SDL_Flip(ecran);
    }

    freeResources(&gResources);

    audioQuit(&audio);

    TTF_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
}


