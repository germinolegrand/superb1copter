#include "GameShow.h"

void showGame(SDL_Surface *ecran, GameShowObjects *gso)
{
    for(unsigned int i = 0; i < gso->buildingsNb; ++i)
    {
        SDL_Rect bgRect = gso->buildingsPosition[i];
        bgRect.x += gso->backgroundPosition.x;
        bgRect.y += gso->backgroundPosition.y;

        SDL_BlitSurface(gso->buildings[i], NULL, ecran, &bgRect);
    }

    SDL_Rect baseRect = gso->basePosition;
    baseRect.x += gso->backgroundPosition.x;
    baseRect.y += gso->backgroundPosition.y;

    SDL_BlitSurface(gso->base, NULL, ecran, &baseRect);

    SDL_Rect helicoRect = gso->helicoPosition;
    helicoRect.y += gso->backgroundPosition.y;

    SDL_BlitSurface(gso->helico, NULL, ecran, &helicoRect);
}
