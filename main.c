#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "Configuration.h"
#include "Audio.h"
#include "GameResources.h"
#include "GameShow.h"
#include "GameControl.h"

/**
abbreviations importantes :
ctrl : game control
res : resources
gso : game show object
**/

int game(int level,GameControl* ctrl,SDL_Surface* ecran);

int main(int argc, char* argv[])
{
    printf("Hello B1 world!\n");

    ///Chargement de la configuration
    Configuration config;

    loadConfiguration(&config, "Config.txt");


    ///Initialisation de la vidéo
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    SDL_Surface* ecran = NULL;

    ecran = SDL_SetVideoMode(config.windowWidth, config.windowHeight, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Supercopter", NULL);


    ///Initialisation de l'audio
    Audio audio;
    audio.conf = &config;

    audioInit(&audio);


    ///Chargement des ressources du jeu
    GameResources gResources;
    gResources.audio = &audio;

    loadResources(&gResources);


    ///Initialisation du jeu
    GameShowObjects gShowObjects;

    GameControl gControl;
    gControl.res = &gResources;
    gControl.gso = &gShowObjects;

    initGame(&gControl);

    int gameLvl = 1;
    while(game(gameLvl++, &gControl, ecran));

    quitGame(&gControl);

    ///Libération des ressources
    freeResources(&gResources);

    audioQuit(&audio);

    TTF_Quit();
    SDL_Quit();

    ///Sauvegarde de la configuration
    saveConfiguration(&config, "Config.txt");

    return EXIT_SUCCESS;
}

int game(int level,GameControl* ctrl,SDL_Surface* ecran)
{
    ///Chargement du niveau
    loadLevel(ctrl, level);

    ///Début du jeu
    int running = 1;
    int paused = 0;

    unsigned int pausedTime = 0;
    unsigned int pauseBegin = 0;

    ///Boucle principale
    while(running)
    {
        SDL_Event event;
        SDL_Event* eventptr = NULL;

        ///Gestion des évennements
        if(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_F4 && event.key.keysym.mod == KMOD_LALT))
            {
                ///On arrête le jeu
                running = 0;
            }
            else if(!paused && event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_p)
            {
                ///On met en pause
                pauseBegin = SDL_GetTicks();
                paused = 1;

                audioPause(ctrl->res->audio, paused);
            }
            else if(paused && event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_p)
            {
                ///On enlève la pause
                pausedTime += SDL_GetTicks() - pauseBegin;
                paused = 0;

                audioPause(ctrl->res->audio, paused);
            }
            else if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_PAGEDOWN)
            {
                ///On baisse le son
                audioChangeGlobalVolume(ctrl->res->audio, -0.05f);
            }
            else if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_PAGEUP)
            {
                ///On monte le son
                audioChangeGlobalVolume(ctrl->res->audio, +0.05f);
            }
            else
            {
                eventptr = &event;
            }
        }

        ///Si le jeu est actuellement en pause
        if(paused)
        {
            processEventsPaused(ctrl, eventptr);
        }
        ///Sinon le jeu est en cours
        else
        {
            ///Si le joueur n'a pas encore gagné ou perdu
            if(!ctrl->win)
            {
                processEvents(ctrl, SDL_GetTicks() - pausedTime, eventptr);
            }
            else
            {
                processEventsPaused(ctrl, eventptr);

                if(eventptr)
                {
                    switch(eventptr->type)
                    {
                        case SDL_KEYDOWN:
                            if(eventptr->key.keysym.sym == SDLK_ESCAPE)
                            {
                                return 0;
                            }

                            running = 0;
                            break;
                        default:
                            break;
                    }
                }
            }
        }

        ///Affichage du jeu
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));

        showGame(ecran, ctrl->gso, SDL_GetTicks());

        SDL_Flip(ecran);
    }

    return ctrl->win == 1;
}

