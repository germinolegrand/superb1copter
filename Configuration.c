#include "Configuration.h"

#include <stdio.h>

void loadConfiguration(Configuration *conf, const char* filename)
{
    FILE* file = NULL;

    file = fopen(filename, "r");

    if(file)
    {
        fscanf(file, "%d:%d:%f", &conf->windowWidth, &conf->windowHeight,
                                 &conf->audioVolume);
    }
    else
    {
        printf("Impossible d'ouvrir le fichier %s\n", filename);

        loadDefaultConfiguration(conf);
    }

    fclose(file);
}

void saveConfiguration(Configuration *conf, const char* filename)
{
    FILE *file = NULL;

    file = fopen(filename,"w"); /* Ecris ou creer le fichier si il n'existe pas */


    if(file)
    {
        fprintf(file,"%d:%d:%f", conf->windowWidth, conf->windowHeight,
                                 conf->audioVolume);
    }
    else
    {
        printf("Impossible d'ouvrir le fichier %s\n", filename);
    }

    fclose(file);
}

void loadDefaultConfiguration(Configuration* conf)
{
    printf("Chargement de la configuration par defaut.\n");

    conf->windowWidth = 800;
    conf->windowHeight = 600;

    conf->audioVolume = 1.0f;
}

