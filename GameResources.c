#include "GameResources.h"

void loadResources(GameResources *res)
{
    res->helicoL = SDL_LoadBMP("helicopterL.bmp");
    res->helicoR = SDL_LoadBMP("helicopterR.bmp");
    res->building = SDL_LoadBMP("building.bmp");

    SDL_SetColorKey(res->helicoL, SDL_SRCCOLORKEY, SDL_MapRGB(res->helicoL->format, 255, 0, 255));
    SDL_SetColorKey(res->helicoR, SDL_SRCCOLORKEY, SDL_MapRGB(res->helicoR->format, 255, 0, 255));
}

void freeResources(GameResources *res)
{
    SDL_FreeSurface(res->helicoL);
    SDL_FreeSurface(res->helicoR);
    SDL_FreeSurface(res->building);
}
