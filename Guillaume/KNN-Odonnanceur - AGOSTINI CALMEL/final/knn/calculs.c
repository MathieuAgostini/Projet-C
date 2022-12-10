#include "header.h"

double calculDistance(float cible, float reference){
    return pow(((double)cible-(double)reference), 2);
}


void getAllDistance(Logement x, Logement* references, size_t nbLogements){
    for (size_t i = 0; i < nbLogements; i++)
    {
        testModeles(&x, &(references[i]));
    }
}

float calculPrix(size_t K, Logement* logements){
    float price = 0;
    for (size_t i = 0; i < K; i++)
    {
        price = price + logements[i].price;
    }
    return (price/K);
}