#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <fmod.h>

#include "GameResources.h"
#include "GameShow.h"
#include "GameControl.h"
#include "Configuration.h"

int main(int argc, char* argv[])
{


//on Recup la conf
    int resolution[3] = {0};
    int son = {1};
    FILE* fichier = NULL;

    fichier = fopen("Config.txt", "r");

    fscanf(fichier, "%d:%d:%d:%d", &resolution[0], &resolution[1], &resolution[2], &son);
    fclose(fichier);

    if(resolution[0] == 0)
    {
        FILE* file;
        file = fopen("Config.txt", "w"); /* Ecris ou creer le fichier si il n'existe pas */
        fprintf(file, "%s", "800:600:32:1"); // Config par defaut
        fclose(file);

        FILE* fichier = NULL;

        fichier = fopen("Config.txt", "r");

        fscanf(fichier, "%d:%d:%d:%d", &resolution[0], &resolution[1], &resolution[2], &son);
        fclose(fichier);
    }


// on recup la conf



    int running = 1;
    int paused = 0;
    SDL_Surface* ecran = NULL;

    GameResources gResources;
    GameShowObjects gShowObjects;
    GameControl gControl = {&gResources, &gShowObjects};

    unsigned int pausedTime = 0;
    unsigned int pauseBegin = 0;

    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    ecran = SDL_SetVideoMode(resolution[0], resolution[1], resolution[2], SDL_HWSURFACE | SDL_DOUBLEBUF); // On recupere la resolution et le nombre de couleurs dans le fichier de conf
    SDL_WM_SetCaption("Supercopter", NULL); // On recupere la variable name dans le fichier de config




    //SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 17, 206, 112));

    loadResources(&gResources);
    initGame(&gControl);
    loadLevel(1, &gControl);



    //Intialisation de Fmod
    FMOD_SYSTEM* system;
    FMOD_SOUND* musique;
    FMOD_RESULT resultat;

    FMOD_System_Create(&system);
    FMOD_System_Init(system, 1, FMOD_INIT_NORMAL, NULL);

    if(son == 1) // Si le son est activé
    {
        /* On ouvre la musique */
        resultat = FMOD_System_CreateSound(system, "Ressources/Son/tro.xm", FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &musique);

        /* On vérifie si elle a bien été ouverte (IMPORTANT) */
        if(resultat != FMOD_OK)
        {
            fprintf(stderr, "Impossible de lire le fichier xm\n");
            return 3;
        }

        /* On active la répétition de la musique à l'infini */
        FMOD_Sound_SetLoopCount(musique, -1);

        /* On joue la musique */
        FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, musique, 0, NULL);
    }
    FMOD_CHANNELGROUP* canal;
    FMOD_BOOL etat;
    FMOD_System_GetMasterChannelGroup(system, &canal);
    FMOD_ChannelGroup_GetPaused(canal, &etat);



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

                if(son == 1) // Si le son est activé
                {
                    FMOD_ChannelGroup_SetPaused(canal, 1); // On met la musique en pause
                }
            }
            else if(paused && event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_p)
            {
                pausedTime += SDL_GetTicks() - pauseBegin;
                paused = 0;

                if(son == 1) // Si le son est activé
                {
                    FMOD_ChannelGroup_SetPaused(canal, 0); // On relance la musique
                }

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

        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
        SDL_Surface* bmp = SDL_LoadBMP("Ressources/Images/back.bmp");
        if(!bmp)
        {
            printf("Unable to load bitmap: %s\n", SDL_GetError());
            return 1;
        }

        // centre the bitmap on screen
        SDL_Rect dstrect;

        dstrect.y = (ecran->h - bmp->h) / 2;

        SDL_BlitSurface(bmp, 0, ecran, &dstrect);
        showGame(ecran, &gShowObjects, SDL_GetTicks());

        SDL_Flip(ecran);
    }

    freeResources(&gResources);

    FMOD_System_Close(system);
    FMOD_System_Release(system);
    TTF_Quit();
    SDL_Quit();


    // on save la conf
    FILE* file;
    file = fopen("Config.txt", "w"); /* Ecris ou creer le fichier si il n'existe pas */
    fprintf(file, "%d:%d:%d:%d", resolution[0], resolution[1], resolution[2], son); // On enregistre notre fichier de conf
    fclose(file);

    return EXIT_SUCCESS;
}

