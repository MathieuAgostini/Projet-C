#ifndef HEADERS_H_INCLUDED
#define HEADERS_H_INCLUDED


// Librairies
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/ioctl.h>

// Defines
#define DUREE_ORDONNANCEMENT 5


// Enumeration

/**
 * @brief La valeur envoyée à ioctl associe à FIONBIO.
 * Regle le comportement de read.
 */
typedef enum{
    READ_BLOCKING_MODE, /* Regle le comportement de read pour qu'elle attende une action write sur le pipe s'il est vide ou la fermeture de tous les write descriptor des processus ayant acces au pipe.*/
    READ_NON_BLOCKING_MODE /* Regle le comportement de read pour que la fonction renvoie 0 si le pipe est vide. */
}readModes;

// Structures
struct Process;
struct ProcessList;
struct SchedulerCaracteristics;

typedef struct Process Process;
typedef struct ProcessList Scheduler;
typedef struct ProcessListCaracteristics SchedulerCaracteristics;

struct Process
{
    char name[64];
    time_t remainingTime;
    int priority;
};

struct ProcessList
{
    Process process;
    Scheduler* next;
};

struct ProcessListCaracteristics
{
    Scheduler *firstElement;
    Scheduler *lastElement;
};



    // main.c

/**
 * @brief Ajoute un processus à la file
 * 
 * 
 * @param logs flux pour l'ecriture dans le fichier qui garde en mémoire les étapes éxécutées par l'ordonnanceur
 * @param ordonnanceur pointeurs sur le premier dernier maillon de la file des processus
 * @param newProcess processus à ajouter à la file
 */
void ajoutActivite(FILE *logs, SchedulerCaracteristics *ordonnanceur, Process newProcess);


/**
 * @brief Itère step jusqu’à obtenir une file de processus vide et que le pipe est ouvert.\n
 * 
 * La première partie execute l'ordonnancement de la file jusqu'à ce que celle-ci soit vide.\n
 * La deuxième partie s'execute lorsque la liste est vide et se bloque en lecture du pipe tant qu'un nouveau processus n'est pas inscrit ou le pipe descriptor pour l'écriture n'est pas fermé par lectureNouvelleActivite.
 * 
 * @param ordonnanceur pointeurs sur le premier dernier maillon de la file des processus
 * @param readDes file descriptor pour la lecture du pipe
 * @param logs flux pour l'ecriture dans le fichier qui garde en mémoire les étapes éxécutées par l'ordonnanceur
 */
void run (SchedulerCaracteristics *ordonnanceur, int readDes, FILE* logs);


/**
 * @brief Set the Read Blocking Mode object
 * 
 * @param readDes file descriptor pour la lecture du pipe
 * @param mode 0=READ_BLOCKING_MODE, 0!=READ_NON_BLOCKING_MODE
 */
void setReadBlockingMode (int readDes,int mode);



    // step.c
    
/**
 * @brief Execute l'ordonnancement de la file de processus passée en argument
 * 
 * @param logs flux pour l'ecriture dans le fichier qui garde en mémoire les étapes éxécutées par l'ordonnanceur
 * @param ordonnanceur pointeurs sur le premier dernier maillon de la file des processus
 */
void step (FILE* logs, SchedulerCaracteristics *ordonnanceur);


/**
 * @brief Ecrit dans le fichier correspondant les l'étape en cours d'éxecution par l'ordonnanceur
 * 
 * @param terminaison si = 0 alors le processus passé en paramêtre sera terminé à ce ce tour.\n
 * @param logs flux pour l'ecriture dans le fichier qui garde en mémoire les étapes éxécutées par l'ordonnanceur
 * @param process le processus en cours d'éxecution
 * @param delay la durée pendant laquelle -process- est executé
 */
void stepLogs(int terminaison, FILE* logs, Process process, int delay);



    // childProcess.c

/**
 * @brief demande à l'utilisateur s'il souhaite ajouter un nouveau processus à la file
 * 
 * @param writeDes file descriptor pour l'écriture dans le pipe
 */
void lectureNouvelleActivite(int writeDes);


/**
 * @brief scan les propriétés saisies par l'utilisateur pour créer un nouveau processus
 * 
 * @return Process - Le nouveau processus
 */
Process caracterisationProcess();

/**
 * @brief Defini aleatoirement les caracteristiques d'un nouveau processus
 * 
 * @return Process - Le processus créé
 */
Process randomProcess();


#endif