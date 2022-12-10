#include "header.h"

void randomize (Logement* logements, size_t nbLogements){
    Logement l;
    int x;
    for (size_t i = 0; i < nbLogements; i++){
        srand(time(NULL)%(rand()%1000000));
        x = rand()%nbLogements;
        l = logements[i];
        logements[i] = logements[x];
        logements[x] = l;
    }
}

void quicksort (Logement* logements, size_t nbLogements, size_t model){
    size_t left = 1, right = nbLogements-1;
    if (nbLogements > 1){
        while (left < right)
        {
            // fprintf(stderr, "+");
            if ((logements[0].distance)[model] < (logements[left].distance)[model])
            {
                // fprintf(stderr, "-");
                if ((logements[0].distance)[model] > (logements[right].distance)[model]){
                    canSwap(logements, &left, &right);
                }
            }else{
                left++;
            }

            // fprintf(stderr, "!");
            if ((logements[0].distance)[model] > (logements[right].distance)[model]){
                // fprintf(stderr, ":");
                if ((logements[0].distance)[model] < (logements[left].distance)[model] && left < right){
                    // fprintf(stderr, "8");
                    canSwap(logements, &left, &right);
                }
            }else{
                right--;
            }
        };
        if (right <= 1 && right == left)
        {
            // fprintf(stderr, "cas1:%lu\t", nbLogements-1);
            quicksort(&(logements[1]), nbLogements-1, model);
        }else if (left >= nbLogements-1 && right == left){
            // fprintf(stderr, "cas2:%lu\t", nbLogements-1);
            swap(logements, 0, nbLogements);
            quicksort(logements, nbLogements-1, model);
        }else if ((logements[0].distance)[model] > (logements[right].distance)[model])
        {
            swapPivot(logements, nbLogements, right, model);
        }
        else
        {
            swapPivot(logements, nbLogements, right-1, model);
        }
        
    } 
}

void canSwap (Logement* logements, size_t *left, size_t *right){
    swap(logements, *right, *left);
    (*left)++;
    (*right)--;
}

void swapPivot (Logement* logements, size_t nbLogements, size_t indexPivot, size_t model){
    size_t nbElements = indexPivot + 1;
    swap(logements, 0, indexPivot);
    quicksort(logements, nbElements, model);
    quicksort(&(logements[nbElements]), nbLogements-nbElements, model);
}

void swap (Logement* logements, size_t first, size_t second){
    Logement l;
    l = logements[second];
    logements[second] = logements[first];
    logements[first] = l;
}