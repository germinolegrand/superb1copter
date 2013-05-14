#include "GameResources.h"

void loadResources(GameResources *res)
{
    res->font = TTF_OpenFont("Ressources/Fonts/arial.ttf", 20);

    res->helicoL = SDL_LoadBMP("Ressources/Images/copterL.bmp");
    res->helicoR = SDL_LoadBMP("Ressources/Images/copterR.bmp");
    res->base = SDL_LoadBMP("Ressources/Images/Hospital.bmp");
    res->building = SDL_LoadBMP("Ressources/Images/buld.bmp");
    res->buildingD = SDL_LoadBMP("Ressources/Images/buldD.bmp");
    res->bomb = SDL_LoadBMP("Ressources/Images/bomb.bmp");
    res->hostage = SDL_LoadBMP("Ressources/Images/hostagee.bmp");

    SDL_SetColorKey(res->helicoL, SDL_SRCCOLORKEY, SDL_MapRGB(res->helicoL->format, 0, 0, 0));
    SDL_SetColorKey(res->helicoR, SDL_SRCCOLORKEY, SDL_MapRGB(res->helicoR->format, 0, 0, 0));
    SDL_SetColorKey(res->base, SDL_SRCCOLORKEY, SDL_MapRGB(res->base->format, 0, 0, 0));
    SDL_SetColorKey(res->building, SDL_SRCCOLORKEY, SDL_MapRGB(res->building->format, 0, 0, 0));
    SDL_SetColorKey(res->buildingD, SDL_SRCCOLORKEY, SDL_MapRGB(res->buildingD->format, 0, 0, 0));
    SDL_SetColorKey(res->bomb, SDL_SRCCOLORKEY, SDL_MapRGB(res->bomb->format, 0, 0, 0));
    SDL_SetColorKey(res->hostage, SDL_SRCCOLORKEY, SDL_MapRGB(res->hostage->format, 0, 0, 0));
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

    TTF_CloseFont(res->font);
}
