#include "Audio.h"

#include <stdlib.h>
#include <stdio.h>

void audioInit(Audio* aud)
{
    FMOD_System_Create(&aud->system);
    FMOD_System_Init(aud->system, 32, FMOD_INIT_NORMAL, NULL);

    aud->backgroundMusic = NULL;
    aud->backgroundMusicChannel = NULL;

    audioSetGlobalVolume(aud, aud->conf->audioVolume);
}

void audioQuit(Audio* aud)
{
    FMOD_System_Close(aud->system);
    FMOD_System_Release(aud->system);
}


void audioPause(Audio *aud, int paused)
{
    FMOD_CHANNELGROUP *channelMaster = NULL;
    FMOD_System_GetMasterChannelGroup(aud->system, &channelMaster);
    FMOD_ChannelGroup_SetPaused(channelMaster, paused);
}

void audioSetGlobalVolume(Audio* aud, float volume)
{
    FMOD_CHANNELGROUP *channelMaster = NULL;
    FMOD_System_GetMasterChannelGroup(aud->system, &channelMaster);
    FMOD_ChannelGroup_SetVolume(channelMaster, volume);

    aud->conf->audioVolume = volume;
}

void audioChangeGlobalVolume(Audio *aud, float volumeAdded)
{
    FMOD_CHANNELGROUP *channelMaster = NULL;
    FMOD_System_GetMasterChannelGroup(aud->system, &channelMaster);

    float volume = 0.f;
    FMOD_ChannelGroup_GetVolume(channelMaster, &volume);
    audioSetGlobalVolume(aud, volume + volumeAdded);
}


FMOD_SOUND* audioLoadMusic(Audio *aud, const char* filename)
{
    FMOD_SOUND *music = NULL;
    FMOD_System_CreateSound(aud->system, filename, FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &music);

    return music;
}

void audioFreeMusic(Audio* aud, FMOD_SOUND* music)
{
    FMOD_Sound_Release(music);
}


void audioPlayBackgroundMusic(Audio* aud, FMOD_SOUND* music)
{
    if(aud->backgroundMusic)
    {
        ///On arrête la musique
        FMOD_Channel_Stop(aud->backgroundMusicChannel);
    }

    aud->backgroundMusic = music;

    if(aud->backgroundMusic)
    {
        ///On relance la musique
        FMOD_System_PlaySound(aud->system, FMOD_CHANNEL_FREE, aud->backgroundMusic, 0, &aud->backgroundMusicChannel);
        FMOD_Sound_SetLoopCount(aud->backgroundMusic, -1);
    }
}


