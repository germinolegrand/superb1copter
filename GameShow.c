#include "GameShow.h"

void showGame(SDL_Surface *ecran, GameShowObjects *gso, unsigned int currentTime)
{
    ///bâtiments
    for(unsigned int i = 0; i < gso->buildingsNb; ++i)
    {
        SDL_Rect bgRect = gso->buildingsPosition[i];
        bgRect.x += gso->backgroundPosition.x;
        bgRect.y += gso->backgroundPosition.y;

        SDL_BlitSurface(gso->buildings[i], NULL, ecran, &bgRect);
    }

    ///base
    {
        SDL_Rect baseRect = gso->basePosition;
        baseRect.x += gso->backgroundPosition.x;
        baseRect.y += gso->backgroundPosition.y;

        SDL_BlitSurface(gso->base, NULL, ecran, &baseRect);
    }

    ///hélicoptère
    {
        SDL_Rect helicoRect = gso->helicoPosition;
        helicoRect.y += gso->backgroundPosition.y;

        SDL_BlitSurface(gso->helico, NULL, ecran, &helicoRect);
    }

    ///bombes
    for(unsigned int i = 0; i < gso->bombsNb; ++i)
    {
        SDL_Rect bbRect = gso->bombsPosition[i];
        bbRect.x += gso->backgroundPosition.x;
        bbRect.y += gso->backgroundPosition.y;

        SDL_BlitSurface(gso->bombs[i], NULL, ecran, &bbRect);
    }

    ///bullets
    for(unsigned int i = 0; i < gso->bulletsNb; ++i)
    {
        SDL_Rect bbRect = gso->bulletsPosition[i];
        bbRect.x += gso->backgroundPosition.x;
        bbRect.y += gso->backgroundPosition.y;

        SDL_BlitSurface(gso->bullets[i], NULL, ecran, &bbRect);
    }

    ///ennemies
    for(unsigned int i = 0; i < gso->ennemiesNb; ++i)
    {
        SDL_Rect bbRect = gso->ennemiesPosition[i];
        bbRect.x += gso->backgroundPosition.x;
        bbRect.y += gso->backgroundPosition.y;

        SDL_BlitSurface(gso->ennemies[i], NULL, ecran, &bbRect);
    }

    ///otages
    for(unsigned int i = 0; i < gso->hostagesNb; ++i)
    {
        SDL_Rect bhRect = gso->hostagesPosition[i];
        bhRect.x += gso->backgroundPosition.x;
        bhRect.y += gso->backgroundPosition.y;

        SDL_Rect bhframeRect = gso->hostages[i]->clip_rect;
        bhframeRect.w = gso->hostages[i]->h;
        bhframeRect.x = (currentTime/500)%2*gso->hostages[i]->h;

        SDL_BlitSurface(gso->hostages[i], &bhframeRect, ecran, &bhRect);
    }

    ///otages dans la base
    for(unsigned int i = 0; i < gso->baseHostagesNb; ++i)
    {
        SDL_Rect bhRect = gso->baseHostagesPosition[i];
        bhRect.x += gso->backgroundPosition.x;
        bhRect.y += gso->backgroundPosition.y;

        SDL_Rect bhframeRect = gso->baseHostages[i]->clip_rect;
        bhframeRect.w = gso->baseHostages[i]->h;
        bhframeRect.x = (currentTime/500)%2*gso->baseHostages[i]->h;

        SDL_BlitSurface(gso->baseHostages[i], &bhframeRect, ecran, &bhRect);
    }

    ///Interface
    {
        SDL_Rect interface_hostageInHelicoRect = {0,0,0,0};
        SDL_BlitSurface(gso->interface_hostagesInHelico, NULL, ecran, &interface_hostageInHelicoRect);

        SDL_Rect interface_hostageWaitingRect = {0,20,0,0};
        SDL_BlitSurface(gso->interface_hostagesWaiting, NULL, ecran, &interface_hostageWaitingRect);

        SDL_Rect interface_hostageFreeRect = {0,40,0,0};
        SDL_BlitSurface(gso->interface_hostagesFree, NULL, ecran, &interface_hostageFreeRect);

        SDL_Rect interface_lifeCountRect = {700,0,0,0};
        SDL_BlitSurface(gso->interface_lifeCount, NULL, ecran, &interface_lifeCountRect);

        SDL_Rect interface_winlooseRect = {400,400,400,400};
        SDL_BlitSurface(gso->interface_winloose, NULL, ecran, &interface_winlooseRect);
    }
}


SDL_Surface* updateCounter(SDL_Surface* surface, TTF_Font *font, const char* text, int count)
{
    SDL_Color color = {255,255,255};
    char count_str[100];
    sprintf(count_str, text, count);

    if(surface)
        SDL_FreeSurface(surface);

    return TTF_RenderText_Blended(font, count_str, color);
}

SDL_Surface* updateCounter2(SDL_Surface *surface, TTF_Font *font, const char* text, int count1, int count2)
{
    SDL_Color color = {255,255,255};
    char count_str[100];
    sprintf(count_str, text, count1, count2);

    if(surface)
        SDL_FreeSurface(surface);

    return TTF_RenderText_Blended(font, count_str, color);
}
SDL_Surface* updateAnnonce(SDL_Surface* surface, TTF_Font *font, const char* text,SDL_Color color)
{
    if(surface)
        SDL_FreeSurface(surface);

    return TTF_RenderText_Blended(font, text, color);
}
