/**
 * @file main.c
 * @author Guillaume CALMEL (calmelguil@cy-tech.fr)
 * @brief Regroupe les fonctions main, run et ajoutActivite qui initient le programme
 * @version 2.0
 * @date 2022-11-25
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "header.h"


void ajoutActivite(FILE *logs, SchedulerCaracteristics *ordonnanceur, Process newProcess){
    Scheduler *new = malloc(sizeof(Scheduler));
    if (new == NULL)
    {
        fprintf(stderr, "Erreur: Creation d'un nouveau maillon a ordonnanceur.");
        exit(EXIT_FAILURE);
    }
    fprintf(logs, "~~~ Insertion du processus -- %s -- dans la file. Duree de vie : %lu. Priorite : %d.\n", newProcess.name, newProcess.remainingTime, newProcess.priority);
    new->process = newProcess;
    new->next = NULL;
    if (ordonnanceur->firstElement == NULL)
    {
        ordonnanceur->firstElement = new;
        ordonnanceur->lastElement = ordonnanceur->firstElement;
    }else{
        ordonnanceur->lastElement->next = new;
        ordonnanceur->lastElement = new;
    }
}



void setReadBlockingMode (int readDes,int mode){
    if (ioctl(readDes, FIONBIO, &mode) == -1)
    {
        fprintf(stderr, "ERREUR: Failed to set FIONBIO=%d (read blocking mode).\n", mode);
        exit(EXIT_FAILURE);
    }
}



void run (SchedulerCaracteristics *ordonnanceur, int readDes, FILE* logs){
    Process newProcess;
    char tmp = 0;
    ssize_t nBytesRead;
    
    setReadBlockingMode(readDes, READ_NON_BLOCKING_MODE);
    while (ordonnanceur->firstElement != NULL){
        step(logs, ordonnanceur);
        if ((nBytesRead = read(readDes, &newProcess, sizeof(Process))) == sizeof(Process)){
            ajoutActivite(logs, ordonnanceur, newProcess);
            read(readDes, &tmp, sizeof(char));  
        }else if (nBytesRead != -1 && nBytesRead != 0){
            fprintf(stderr, "ERREUR: Read1 failed. nBytes = %ld\n", nBytesRead);
            exit(EXIT_FAILURE);
        }
    }
    printf("\nLa liste de processus est vide.\n");


    setReadBlockingMode(readDes, READ_BLOCKING_MODE);
    if ((nBytesRead = read(readDes, &newProcess, sizeof(Process))) == sizeof(Process)){
        fprintf(logs, "\n\tRelance de l'ordonnanceur.\n\n");
        ajoutActivite(logs, ordonnanceur, newProcess);
        run(ordonnanceur, readDes, logs);
    }else if(nBytesRead != 0)
    {
        fprintf(stderr, "ERREUR: Read2 failed. nBytes = %ld\n", nBytesRead);
        exit(EXIT_FAILURE);
    }
    close(readDes);
}


int main(int argc, char const *argv[])
{
    SchedulerCaracteristics ordonnanceur;
    int pipedes[2];
    FILE *logs = fopen("./OrdonnanceurLogs.txt", "a");

    if (logs == NULL)
    {
        fprintf(stderr, "Erreur: Ouverture du fichier OrdonnanceurLogs.txt.\n");
        exit(EXIT_FAILURE);
    }

    if (pipe(pipedes) != 0)
    {
        fprintf(stderr, "Erreur: Creation du pipe.\n");
        exit(EXIT_FAILURE);
    }

    
    if (fork() == 0)
    {
        fprintf(logs,"Ordonnanceur %ld:\n\n", time(NULL));
        ajoutActivite(logs, &ordonnanceur, caracterisationProcess());
        write(pipedes[1], "c", sizeof(char));
        close(pipedes[1]); // close writing pour l'ordonnanceur
        run(&ordonnanceur, pipedes[0], logs);
        fprintf(logs,"______________________________________________________\n\n");
        printf("\nOrdonnanceur: Sucessfully terminated\n\n");
        fclose(logs);
    }
    else{
        char controle;
        read(pipedes[0], &controle, sizeof(char)); // Attend qu'une nouvelle activite soit créée
        close(pipedes[0]); // close reading pour l'ajout des nouveaux processus
        lectureNouvelleActivite(pipedes[1]);
    }
    return 0;
}
