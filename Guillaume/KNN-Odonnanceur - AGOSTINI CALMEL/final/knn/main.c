#include "header.h"


int main(int argc, char const *argv[])
{
    size_t tailleTabEntrainement = 0, tailleTabTest = 0, K;
    Logement *tabEntrainement = readCSV(&tailleTabEntrainement, &tailleTabTest), *tabTest = &(tabEntrainement[tailleTabEntrainement]);
    printf("\n");
    printf("Les données du fichier ont été extraites et placées dans le tableau tabEntrainement et tabTest.\n\n");

    float *modelsPrice[NB_MODEL];
    double *mae[NB_MODEL];
    maeOptimal optimal;

    fprintf(stderr, "NBLogements: %lu, tailleTabEntrainement: %lu, tailleTabTest: %lu\n\n",tailleTabEntrainement+tailleTabTest, tailleTabEntrainement, tailleTabTest);
        
    randomize(tabEntrainement, tailleTabEntrainement);
    
    printf("Le tableau d'entrainement viens d'être trié.\n\n");

    for (size_t i = 0; i < NB_MODEL; i++){modelsPrice[i] = (float*)allocateDynamically(sizeof(float)*tailleTabTest);}
    for (size_t i = 0; i < NB_MODEL; i++){mae[i] = (double*)allocateDynamically(sizeof(double)*(tailleTabEntrainement-1));}
    
    for ( K = 0; K < tailleTabEntrainement-1; K++)
    {
        for (size_t i = 0; i < tailleTabTest; i++)
        {
            getAllDistance(tabTest[i], tabEntrainement, tailleTabEntrainement); // récupère les distances pour tous les modèles testés pour un élément de tabEntrainement
            for (size_t model = 0; model < NB_MODEL; model++)
            {
                quicksort(tabEntrainement, tailleTabEntrainement-1, model);
                modelsPrice[model][i] = calculPrix(K+1, tabEntrainement); // calcul le prix du logement étudié pour chaque modèles
            }
        }
        
        for (size_t model = 0; model < NB_MODEL; model++)
        {
            mae[model][K] = 0;
            for (size_t i = 0; i < tailleTabEntrainement; i++)
            {                
                mae[model][K] = mae[model][K] + fabs((double)(tabEntrainement[i].price - modelsPrice[model][i]));
            }
            mae[model][K] = mae[model][K]/tailleTabEntrainement;
        }

        if (K==0) {printf("* Nous commencons le traitement des données, le calcul des distances et du MAE\n\n");}
        if (K==tailleTabEntrainement/2) {printf("   * Nous sommes à la moitié du traitement des données, du calcul des distances et du MAE\n\n");}
    }
    optimal.model = 0;
    optimal.K = 0;
    for (size_t model = 0; model < NB_MODEL; model++)
    {
        for (size_t K = 0; K < tailleTabEntrainement-1; K++)
        {
            if(mae[model][K] < mae[optimal.model][optimal.K]){
                optimal.K = K;
                optimal.model = model;
            }
        }
    }
    printf("Le modele le plus efficace est le modele %lu : ", optimal.model);
    affichageModel(optimal.model);
    printf("\nPour un K égal à %lu.\n", optimal.K);
        
    for (size_t i = 0; i < NB_MODEL; i++){free(modelsPrice[i]);}
    for (size_t i = 0; i < NB_MODEL; i++){free(mae[i]);}
    free(tabEntrainement);
    return 0;
}