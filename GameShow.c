#include "GameShow.h"

void showGame(SDL_Surface *ecran, GameShowObjects *gso)
{
    for(unsigned int i = 0; i < gso->buildingsNb; ++i)
    {
        SDL_BlitSurface(gso->buildings[i], NULL, ecran, &gso->buildingsPosition[i]);
    }

    SDL_BlitSurface(gso->helico, NULL, ecran, &gso->helicoPosition);
}
