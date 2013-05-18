#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <fmod.h>

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

    FMOD_SYSTEM *fmodSystem = NULL;

    FMOD_System_Create(&fmodSystem);
    FMOD_System_Init(fmodSystem, 32, FMOD_INIT_NORMAL, NULL);


    GameResources gResources;
    gResources.fmodSystem = fmodSystem;

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

                FMOD_CHANNELGROUP *channel = NULL;
                FMOD_System_GetMasterChannelGroup(fmodSystem, &channel);
                FMOD_ChannelGroup_SetPaused(channel, 1); // On met la musique en pause
            }
            else if(paused && event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_p)
            {
                pausedTime += SDL_GetTicks() - pauseBegin;
                paused = 0;

                FMOD_CHANNELGROUP *channel = NULL;
                FMOD_System_GetMasterChannelGroup(fmodSystem, &channel);
                FMOD_ChannelGroup_SetPaused(channel, 0); // On relance la musique
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

    FMOD_System_Close(fmodSystem);
    FMOD_System_Release(fmodSystem);

    TTF_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
}

