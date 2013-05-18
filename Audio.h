#ifndef AUDIO_H_INCLUDED
#define AUDIO_H_INCLUDED

#include <fmod.h>

#include "Configuration.h"

typedef struct Audio Audio;
struct Audio
{
    Configuration *conf;

    FMOD_SYSTEM *system;

    FMOD_SOUND *backgroundMusic;
    FMOD_CHANNEL * backgroundMusicChannel;
};

void audioInit(Audio *aud);
void audioQuit(Audio *aud);

void audioPause(Audio *aud, int paused);
void audioSetGlobalVolume(Audio *aud, float volume);
void audioChangeGlobalVolume(Audio *aud, float volumeAdded);

FMOD_SOUND* audioLoadMusic(Audio *aud, const char* filename);
void audioFreeMusic(Audio *aud, FMOD_SOUND *music);

void audioPlayBackgroundMusic(Audio *aud, FMOD_SOUND *music);

#endif // AUDIO_H_INCLUDED
