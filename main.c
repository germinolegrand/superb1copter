#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "fmod.h"

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
    TTF_Init();

    ecran = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Supercopter", NULL);
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 17, 206, 112));

    loadResources(&gResources);
    initGame(&gControl);
    loadLevel(1, &gControl);

	//Intialisation de Fmod
	FMOD_SYSTEM *system;
    FMOD_SOUND *musique;
    FMOD_RESULT resultat;

	FMOD_System_Create(&system);
    FMOD_System_Init(system, 1, FMOD_INIT_NORMAL, NULL);

	/* On ouvre la musique */
    resultat = FMOD_System_CreateSound(system, "Ressources/Son/tro.xm", FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &musique);

    /* On vérifie si elle a bien été ouverte (IMPORTANT) */
    if (resultat != FMOD_OK)
    {
        fprintf(stderr, "Impossible de lire le fichier mp3\n");
        return 3;
    }

    /* On active la répétition de la musique à l'infini */
    FMOD_Sound_SetLoopCount(musique, -1);

	/* On joue la musique */
    FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, musique, 0, NULL);

	FMOD_CHANNELGROUP *canal;
	FMOD_BOOL etat;
	FMOD_System_GetMasterChannelGroup(system, &canal);
	FMOD_ChannelGroup_GetPaused(canal, &etat);



    while(running)
    {
        SDL_Event event;
        SDL_Event *eventptr = NULL;

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

                FMOD_ChannelGroup_SetPaused(canal, 1); // On met la musique en pause
            }
            else if(paused && event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_p)
            {
                pausedTime += SDL_GetTicks() - pauseBegin;
                paused = 0;

                FMOD_ChannelGroup_SetPaused(canal, 0); // On relance la musique
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

        showGame(ecran, &gShowObjects, SDL_GetTicks());

        SDL_Flip(ecran);
    }

    freeResources(&gResources);

    TTF_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
}

