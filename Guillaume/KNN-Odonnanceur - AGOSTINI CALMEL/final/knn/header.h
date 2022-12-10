#ifndef HEADERS_H_INCLUDED
#define HEADERS_H_INCLUDED

// librairies
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


// define
#define DATA_PATH "data/bis.csv"
// #define DATA_PATH "data/airbnb_donnees_propres.csv"
#define NB_MODEL 63 // 2^6 - 1, le nombre de combinaisons possible pour une étude de 6 caracteristiques moins la combinaison nulle

// énumerations
enum flags {
    ACCOMMODATES = 0x01,
    BEDROOMS = 0x02,
    BATHROOMS = 0x04,
    BEDS = 0x08,
    NIGHTS = 0x10,
    NUMBER_OF_REVIEWS = 0x20
};

// structures
struct Logement;

typedef struct caracteristiquesLogement Logement;
typedef struct maeOptimal maeOptimal;

/**
 * @brief Logement défini par les caracteristiques: id, accommodates, bedrooms, bathrooms, beds, price, minimum_nights, maximum_nights, number_of_reviews
 */
struct caracteristiquesLogement{
    unsigned int id;
    unsigned int accommodates;
    float bedrooms;
    float bathrooms;
    float beds;
    float price;
    unsigned int minimum_nights;
    unsigned int maximum_nights;
    unsigned int number_of_reviews;
    double distance[NB_MODEL];// Tableau de double contenant la distance par rapport à un élement de type Logement pour chaque modele existant
};

/**
 * @brief Combinaison du modele et du nombre d'éléments à étudier
 * 
 */
struct maeOptimal
{
    size_t model;
    size_t K;
};


// lectureCSV.c
FILE* openFile ();
void closeFile (FILE *fp);
void* allocateDynamically (size_t tabSize);

/**
 * @brief Récupère les données d'un fichier CSV et renvoie un tableau de type Logement
 * 
 * @param tailleTabEntrainement Le nombre d'éléments du tableau tabEntrainement
 * @param tailleTabTest Le nombre d'éléments du tableau tabTest
 * @return Logement* - Le tableau de logement de taille tailleTabTest + tailleTabEntrainement
 */
Logement* readCSV(size_t* tailleTabEntrainement, size_t* tailleTabTest);


// calculPrix.c
double calculDistance(float cible, float reference);

/**
 * @brief recupere la distance entre x et tous les éléments de references pour chaque modeles
 * 
 * @param x Le logement dont on recherche le prix
 * @param references Le tableau de logement qui servent de references
 * @param nbLogements la taille du tableau references
 */
void getAllDistance(Logement x, Logement* references, size_t nbLogements);

/**
 * @brief Calcul la moyenne des K logements de plus petite distance
 * 
 * @param K Le nombre de logements à prendre en compte
 * @param logements Le tableau de logements
 * @return float - Le prix estimé
 */
float calculPrix(size_t K, Logement* logements);


// testModeles.c

/**
 * @brief Calcul la distance entre reference et cible pour chaque modele possible
 * 
 * @param cible Le logement dont on cherche le prix
 * @param reference Le logement de reference
 */
void testModeles(Logement* cible, Logement* reference);

/**
 * @brief Affiche les caracteristiques étudiés par le modele envoyé en parametre
 * 
 * @param model Le numero du modele a transcrire
 */
void affichageModel (size_t model);


// tri.c

/**
 * @brief randomize le tableau envoyé en paramêtre
 * 
 * @param logements Le tableau de logements à randomiser
 * @param nbLogements La taille du tableau logements
 */
void randomize (Logement* logements, size_t nbLogements);

/**
 * @brief Tri rapide d'un tableau de structure Logement par rapport à la distance
 * 
 * @param logements Le tableau de logements à trier
 * @param nbLogements La taille du tableau logements
 * @param model L'index du tableau de distance, correspond au modele étudié
 */
void quicksort (Logement* logements, size_t nbLogements, size_t model);

/**
 * @brief Interverti deux éléments du tableau de type Logement reçu en paramêtre
 * 
 * @param logements Le tableau de logements
 * @param first L'index du premier élement à intervertir
 * @param second L'index du deuxieme élement à intervertir
 */
void swap (Logement* logements, size_t first, size_t second);

/**
 * @brief Déplace le pivot à l'index indexPivot puis divise le tableau autour du pivot et lance recursivement un quicksort sur les deux éléments obtenus
 * 
 * @param logements Le tableau de logements après une iteration de quicksort
 * @param nbLogements La taille du tableau logements
 * @param indexPivot L'index ou doit être placé le pivot
 * @param model L'index du tableau de distance, correspond au modele étudié
 */
void swapPivot (Logement* logements, size_t nbLogements, size_t indexPivot, size_t model);

void canSwap (Logement* logements, size_t *left, size_t *right);

#endif