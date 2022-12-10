#include "header.h"

/////// Opération sur Fichier

FILE* opentFile (){
    FILE *fp = fopen(DATA_PATH, "r");
    if (fp == NULL){
      fprintf(stderr, "Le fichier n'a pas pu être ouvert\n");
      exit(EXIT_FAILURE);
    }
    return fp;
}

void closeFile (FILE *fp){
    if(fclose(fp) == EOF){
        fprintf(stderr, "Erreur lors de la fermeture du flux\n");
        exit(EXIT_FAILURE);   
    }
}


/////// Créatoin de tableaux

void* allocateDynamically (size_t tabSize){
    void* tab = malloc(tabSize);
    if (tab == NULL)
    {
        fprintf(stderr, "Erreur : L'allocation dynamique a échoué");
        exit(EXIT_FAILURE);
    }
    return tab;
}


/////// Lecture du flux

Logement* readCSV(size_t* tailleTabEntrainement, size_t* tailleTabTest){
    FILE* csv = opentFile();
    Logement* logements = NULL;
    char s[256];
    unsigned int nbLogements = 0;

    while (fgets(s, 255, csv) != NULL){nbLogements++;}
    nbLogements--;
    *tailleTabEntrainement = (size_t)(0.8*nbLogements);
    *tailleTabTest = (size_t)(0.2*nbLogements)+1;
    
    logements = allocateDynamically(sizeof(Logement)*nbLogements);
    
    rewind(csv);
    fscanf(csv, "%*s");
    for (size_t i = 0; i < nbLogements; i++)
    {
        fscanf(csv,"%i,%i,%f,%f,%f,%f,%i,%i,%i", &logements[i].id, &logements[i].accommodates, &logements[i].bedrooms, &logements[i].bathrooms, &logements[i].beds, &logements[i].price, &logements[i].minimum_nights, &logements[i].maximum_nights, &logements[i].number_of_reviews);
    }

    closeFile(csv);
    return logements;
}