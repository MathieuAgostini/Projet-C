/**
 * @file step.c
 * @author Guillaume CALMEL (calmelguil@cy-tech.fr)
 * @brief Contient la fonction step
 * @version 2.0
 * @date 2022-11-25
 * 
 * @copyright Copyright (c) 2022
 */
#include "header.h"


void stepLogs(int terminaison, FILE* logs, Process process, int delay){    
    if (terminaison == 0)
    {
        fprintf(logs, "Execution du processus -- %s -- pendant %d secondes. Duree de vie restante : %lu.\n", process.name, delay, process.remainingTime-delay);
    }
    else
    {
        fprintf(logs, "Terminaison du processus -- %s -- en %ld secondes.\n", process.name, process.remainingTime);
    }    
}



void step (FILE* logs, SchedulerCaracteristics *ordonnanceur){
    time_t remainingTime;
    if (ordonnanceur != NULL )
    {
        int delay = (DUREE_ORDONNANCEMENT - ordonnanceur->firstElement->process.priority);
        if ((remainingTime = ordonnanceur->firstElement->process.remainingTime - delay) > 0)
        {
            stepLogs(0, logs, ordonnanceur->firstElement->process, delay);
            ordonnanceur->firstElement->process.remainingTime = remainingTime;
            if (ordonnanceur->firstElement != ordonnanceur->lastElement)
            {
                ordonnanceur->lastElement->next = ordonnanceur->firstElement;
                ordonnanceur->lastElement = ordonnanceur->lastElement->next;
                ordonnanceur->firstElement = ordonnanceur->firstElement->next;
                ordonnanceur->lastElement->next = NULL;
            }
            sleep(delay);
        }else{
            stepLogs(1, logs, ordonnanceur->firstElement->process, delay);
            sleep(ordonnanceur->firstElement->process.remainingTime);
            Scheduler *second = ordonnanceur->firstElement->next;
            free(ordonnanceur->firstElement);
            ordonnanceur->firstElement = second;
        }
    }else{
        printf("La file des processus en attente est vide.\n");
    }
    
}