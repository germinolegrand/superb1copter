#include "Configuration.h"

void saveconf()
{
    FILE *file;

    file = fopen("Config.txt","w"); /* Ecris ou creer le fichier si il n'existe pas */


    if (file != NULL)
    {
        fprintf(file,"%s","800:600:32:1");
    }
    else
    {
        // On affiche un message d'erreur si on veut
        printf("Impossible d'ouvrir le fichier test.txt");
    }

fclose(file);
}


void loadconf()
{
    int resolution[3] = {0};
    int son = {0};
    FILE* fichier = NULL;

    fichier = fopen("Config.txt", "r");

    fscanf(fichier, "%d:%d:%d:%d", &resolution[0], &resolution[1], &resolution[2],&son);
    fclose(fichier);
}
