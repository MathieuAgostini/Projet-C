#include "header.h"

void testModeles(Logement* cible, Logement* reference){
    unsigned char caracteristics;
    for (unsigned char model = 0; model < NB_MODEL; model++)
    {
        caracteristics = model + 1;
        (reference->distance)[model] = 0;
        
        if (caracteristics & ACCOMMODATES){
            (reference->distance)[model] = (reference->distance)[model] + calculDistance(cible->accommodates, reference->accommodates);
        }
        if (caracteristics & BEDROOMS){
            (reference->distance)[model] = (reference->distance)[model] + calculDistance(cible->bedrooms, reference->bedrooms);
        }
        if (caracteristics & BATHROOMS){
            (reference->distance)[model] = (reference->distance)[model] + calculDistance(cible->bathrooms, reference->bathrooms);
        }
        if (caracteristics & BEDS){
            (reference->distance)[model] = (reference->distance)[model] + calculDistance(cible->beds, reference->beds);
        }
        if (caracteristics & NIGHTS){
            (reference->distance)[model] = (reference->distance)[model] + calculDistance(cible->minimum_nights, reference->minimum_nights);
            (reference->distance)[model] = (reference->distance)[model] + calculDistance(cible->maximum_nights, reference->maximum_nights);
        }
        if (caracteristics & NUMBER_OF_REVIEWS){
            (reference->distance)[model] = (reference->distance)[model] + calculDistance(cible->number_of_reviews, reference->number_of_reviews);
        }
        
        (reference->distance)[model] = sqrt((reference->distance)[model]);
    }
}

void affichageModel (size_t model){
    model++;
    if (model & ACCOMMODATES){
        printf("ACCOMMODATES\t");
    }
    if (model & BEDROOMS){
        printf("BEDROOMS\t");
    }
    if (model & BATHROOMS){
        printf("BATHROOMS\t");
    }
    if (model & BEDS){
        printf("BEDS\t");
    }
    if (model & NIGHTS){
        printf("MINIMUM & MAXIMUM NIGHTS\t");
    }
    if (model & NUMBER_OF_REVIEWS){
        printf("NUMBER OD REVIEWS\t");
    }
}
