#include "GameResources.h"

void loadResources(GameResources *res)
{
    res->helicoL = SDL_LoadBMP("helicopterL.bmp");
    res->helicoR = SDL_LoadBMP("helicopterR.bmp");
    res->base = SDL_LoadBMP("base.bmp");
    res->building = SDL_LoadBMP("building.bmp");
    res->buildingD = SDL_LoadBMP("buildingD.bmp");
    res->bomb = SDL_LoadBMP("bomb.bmp");
    res->hostage = SDL_LoadBMP("hostage.bmp");

    SDL_SetColorKey(res->helicoL, SDL_SRCCOLORKEY, SDL_MapRGB(res->helicoL->format, 255, 0, 255));
    SDL_SetColorKey(res->helicoR, SDL_SRCCOLORKEY, SDL_MapRGB(res->helicoR->format, 255, 0, 255));
    SDL_SetColorKey(res->base, SDL_SRCCOLORKEY, SDL_MapRGB(res->base->format, 255, 0, 255));
    SDL_SetColorKey(res->building, SDL_SRCCOLORKEY, SDL_MapRGB(res->building->format, 255, 0, 255));
    SDL_SetColorKey(res->buildingD, SDL_SRCCOLORKEY, SDL_MapRGB(res->buildingD->format, 255, 0, 255));
    SDL_SetColorKey(res->bomb, SDL_SRCCOLORKEY, SDL_MapRGB(res->bomb->format, 255, 0, 255));
    SDL_SetColorKey(res->hostage, SDL_SRCCOLORKEY, SDL_MapRGB(res->hostage->format, 255, 0, 255));
}

void freeResources(GameResources *res)
{
    SDL_FreeSurface(res->helicoL);
    SDL_FreeSurface(res->helicoR);
    SDL_FreeSurface(res->base);
    SDL_FreeSurface(res->building);
    SDL_FreeSurface(res->buildingD);
    SDL_FreeSurface(res->bomb);
    SDL_FreeSurface(res->hostage);
}
