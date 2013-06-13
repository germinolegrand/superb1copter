#include "GameResources.h"

void loadResources(GameResources *res)
{
    ///musiques
    res->bgMusic1 = audioLoadMusic(res->audio, "Ressources/Son/mainthemelife1.xm");
    res->bgMusic2 = audioLoadMusic(res->audio, "Ressources/Son/mainthemelife2.xm");
    res->bgMusic3 = audioLoadMusic(res->audio, "Ressources/Son/mainthemelife3.xm");
    res->loose = audioLoadMusic(res->audio, "Ressources/Son/loose.xm");
    res->win = audioLoadMusic(res->audio, "Ressources/Son/win.xm");
    res->menu = audioLoadMusic(res->audio, "Ressources/Son/menu.xm");

    ///polices
    res->font = TTF_OpenFont("Ressources/Fonts/arial.ttf", 20);

    ///images
    res->background = SDL_LoadBMP("Ressources/Images/back.bmp");
    res->helicoL = SDL_LoadBMP("Ressources/Images/copterL.bmp");
    res->helicoR = SDL_LoadBMP("Ressources/Images/copterR.bmp");
    res->base = SDL_LoadBMP("Ressources/Images/Hospital.bmp");
    res->building = SDL_LoadBMP("Ressources/Images/buld.bmp");
    res->buildingD = SDL_LoadBMP("Ressources/Images/buldD.bmp");
    res->bomb = SDL_LoadBMP("Ressources/Images/bomb.bmp");
    res->bullet = SDL_LoadBMP("Ressources/Images/bullet.bmp");

    res->hostage = SDL_LoadBMP("Ressources/Images/hostagee.bmp");

    res->tankL = SDL_LoadBMP("Ressources/Images/tankL.bmp");
    res->tankR = SDL_LoadBMP("Ressources/Images/tankR.bmp");

    //res->background = SDL_LoadBMP("Ressources/Images/background.bmp");

    ///transparence des images
    SDL_SetColorKey(res->helicoL,    SDL_SRCCOLORKEY, SDL_MapRGB(res->helicoL->format,    255, 0, 255));
    SDL_SetColorKey(res->helicoR,    SDL_SRCCOLORKEY, SDL_MapRGB(res->helicoR->format,    255, 0, 255));
    SDL_SetColorKey(res->base,       SDL_SRCCOLORKEY, SDL_MapRGB(res->base->format,       255, 0, 255));
    SDL_SetColorKey(res->building,   SDL_SRCCOLORKEY, SDL_MapRGB(res->building->format,   255, 0, 255));
    SDL_SetColorKey(res->buildingD,  SDL_SRCCOLORKEY, SDL_MapRGB(res->buildingD->format,  255, 0, 255));
    SDL_SetColorKey(res->bomb,       SDL_SRCCOLORKEY, SDL_MapRGB(res->bomb->format,       255, 0, 255));
    SDL_SetColorKey(res->bullet,     SDL_SRCCOLORKEY, SDL_MapRGB(res->bullet->format,     255, 0, 255));
    SDL_SetColorKey(res->tankL,      SDL_SRCCOLORKEY, SDL_MapRGB(res->tankL->format,      255, 0, 255));
    SDL_SetColorKey(res->tankR,      SDL_SRCCOLORKEY, SDL_MapRGB(res->tankR->format,      255, 0, 255));
    SDL_SetColorKey(res->hostage,    SDL_SRCCOLORKEY, SDL_MapRGB(res->hostage->format,    255, 0, 255));
    //SDL_SetColorKey(res->background, SDL_SRCCOLORKEY, SDL_MapRGB(res->background->format, 255, 0, 255));
}

void freeResources(GameResources *res)
{
    ///images
    SDL_FreeSurface(res->helicoL);
    SDL_FreeSurface(res->helicoR);
    SDL_FreeSurface(res->base);
    SDL_FreeSurface(res->building);
    SDL_FreeSurface(res->buildingD);
    SDL_FreeSurface(res->bomb);
    SDL_FreeSurface(res->bullet);
    SDL_FreeSurface(res->hostage);
    SDL_FreeSurface(res->tankL);
    SDL_FreeSurface(res->tankR);
    //SDL_FreeSurface(res->background);

    ///polices
    TTF_CloseFont(res->font);

    ///musiques
    audioFreeMusic(res->audio, res->bgMusic1);
}
