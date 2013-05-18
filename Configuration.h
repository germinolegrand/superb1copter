#ifndef CONFIGURATION_H_INCLUDED
#define CONFIGURATION_H_INCLUDED

typedef struct Configuration Configuration;
struct Configuration
{
    int windowWidth,
        windowHeight;

    float audioVolume;
};

void loadConfiguration(Configuration *conf, const char* filename);
void saveConfiguration(Configuration *conf, const char* filename);

void loadDefaultConfiguration(Configuration *conf);

#endif // CONFIGURATION_H_INCLUDED
