#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

typedef struct Movement Movement;
struct Movement
{
    int x, y;
};

int main(int argc, char* argv[])
{
    int continuer = 1;
    SDL_Event event;
    SDL_Surface *ecran = NULL, *helicoL = NULL, *helicoR = NULL;
    SDL_Rect position = {50, 100};
    SDL_Surface *helico = NULL;

    Movement mvt = {0,0};
    int tempsPrecedent = 0, tempsActuel = 0;

    SDL_Init(SDL_INIT_VIDEO);

    ecran = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Supercopter", NULL);
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 17, 206, 112));

    helicoL = SDL_LoadBMP("helicopterL.bmp");
    helicoR = SDL_LoadBMP("helicopterR.bmp");

    helico = helicoR;

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

        tempsActuel = SDL_GetTicks();

        if(tempsActuel - tempsPrecedent > 10)
        {
            position.x += mvt.x * 5;
            position.y += mvt.y * 5;

            helico = !mvt.x ? helico : (mvt.x > 0 ? helicoR : helicoL);

            tempsPrecedent = tempsActuel;
        }

        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 17, 206, 112));

        SDL_SetColorKey(helico, SDL_SRCCOLORKEY, SDL_MapRGB(helico->format, 255, 0, 255));
        SDL_BlitSurface(helico, NULL, ecran, &position);

        SDL_Flip(ecran);
    }

    SDL_FreeSurface(helicoL);
    SDL_FreeSurface(helicoR);

    SDL_Quit();

    return EXIT_SUCCESS;
}
