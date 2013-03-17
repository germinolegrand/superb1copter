#include "GameShow.h"

void showGame(SDL_Surface *ecran, GameShowObjects *gso)
{
    SDL_Rect bgRect;
    for(unsigned int i = 0; i < gso->buildingsNb; ++i)
    {
        bgRect = gso->buildingsPosition[i];
        bgRect.x += gso->backgroundPosition.x;
        bgRect.y += gso->backgroundPosition.y;

        SDL_BlitSurface(gso->buildings[i], NULL, ecran, &bgRect);
    }

    SDL_Rect helicoRect = gso->helicoPosition;

    SDL_BlitSurface(gso->helico, NULL, ecran, &helicoRect);
}
