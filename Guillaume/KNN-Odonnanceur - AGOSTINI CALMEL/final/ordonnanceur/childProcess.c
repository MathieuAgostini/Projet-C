/**
 * @file childProcess.c
 * @author Guillaume CALMEL (calmelguil@cy-tech.fr)
 * @brief Regroupe l'ensemble des fonctions utiles pour l'enregistrement de nouveaux processus
 * @version 2.0
 * @date 2022-11-25
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "header.h"

void lectureNouvelleActivite(int writeDes){
    char wish;
    Process new;
    do
    {
        printf("Souhaitez-vous ajouter un processus? (r cree un processus automatiquement) [y/n/r]\t");
        do
        {
            scanf("%c", &wish);
        }while (wish != 'r' && wish != 'R' && wish != 'y' && wish != 'Y' && wish != 'n' && wish != 'N');
        
        // printf("wish: %d\n\n", wish);
        if (wish == 121 || wish == 89)
        {
            new = caracterisationProcess();
            write(writeDes, &new, sizeof(Process));
        }else if (wish == 114 || wish == 82)
        {
            new = randomProcess();
            write(writeDes, &new, sizeof(Process));
        }
        
    }while (wish != 110 /* "n" */ && wish != 78 /* "N" */);
    close(writeDes); // close writing pour l'ajout de nouveaux processus
}



Process caracterisationProcess(){
    Process newProcess;
    printf("\tQuel est le nom du nouveau Processus? : ");
    scanf("%s", newProcess.name);
    printf("\tQuel est son temps d'execution? : ");
    do{
        scanf("%ld", &newProcess.remainingTime);
    } while (newProcess.remainingTime <= 0);
    
    printf("\tQuelle est sa priorite? Elle doit être entre 0 et %d : ", DUREE_ORDONNANCEMENT-1);
    do{
        scanf("%d", &newProcess.priority);
    } while (newProcess.priority < 0 || newProcess.priority >= DUREE_ORDONNANCEMENT);
    return newProcess;
}


Process randomProcess(){
    Process process;
    process.name[0] = 'R';
    process.name[1] = 'A';
    process.name[2] = 'N';
    process.name[3] = 'D';
    process.name[4] = '_';
    for (size_t i = 5; i < 9; i++)
    {
        process.name[i] = (rand() % 10)+48;
    }
    process.name[9] = '\0';
    process.remainingTime = rand()%19 +1 ;
    process.priority = rand()%5;
    printf("Nouveau processus: %s, duree d'execution: %lu, priorite: %d\n\n", process.name, process.remainingTime, process.priority);
    return process;
}