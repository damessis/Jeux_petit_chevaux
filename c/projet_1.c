 
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
 
 
int main (int argc,char ** argv){
    int nbProcessus;
    pid_t   pid;
    int i;
    /* Lecture du paramètre */
    if(argc!=2){
     fprintf(stderr,"Erreur nombre d'argument incorrect Format correct <nomprogramme> <nombre de joueurs>\n");
     exit(-1);
   }else{
        nbProcessus=atoi(argv[1]);   
        int p[nbProcessus][2];    // Place pour n paires de descripteurs (VLA)
 
        /* Indication du nombre de processus à engendrer */
        printf ("Nombre de processus à engendrer : %d\n",nbProcessus);
 
        /* Création des n tubes anonymes.             */
        /* On considère que l'appel réussit toujours. */
        for(int i=0;i<nbProcessus;i++){
            if (pipe(p[i]) != 0) {/* pipe */
 			         fprintf(stderr, "Erreur dans pipe \n"); 
 			         exit(-1);
   	        }
        }
        /* Génération des n processus fils, qui vont communiquer */
        /* entre eux. Le processus père reste en superviseur.    */
        for (i=0;i<nbProcessus;++i)
        {
            pid = fork();
 
            if (pid>0)
            {
                printf ("Création du processus fils #%d : PID %d\n",i,pid);
            }
            else if (!pid)
            {
                /*                          */
                /* ---- Processus fils ---- */
                /*                          */
 
                int ecr;     /* Descripteur d'entrée     */
                int lu;    /* Descripteur de sortie    */
                int info;   /* Donnée à  envoye        */
                int j;
                      
                /* Temporisation pour que la boucle du processus père ait   */
                /* le temps de se terminer avant de commencer le traitement */
                sleep(1);
 
                /* Récupération des descripteurs adéquats */
                ecr  = p[i][0];
                lu = p[(i+1) % nbProcessus][1];
 
                /* Fermeture des descripteurs inutiles */
                for (j=0;j<nbProcessus;++j)
                {
                    if (p[j][0] != ecr){
                      close(p[j][0]);
                    }
                    if (p[j][1] != lu){ 
                      close(p[j][1]);
                    }
                }
 
                /* Récupération et émission de notre PID */
                info = getpid();
                printf ("Processus #%d : envoie de %d\n",i,info);
                write (lu,&info,sizeof(info));
                close (lu);
 
                /* Réception de la donnée de l'autre processus */
                info = (int)getpid();
                read (ecr,&info,sizeof(info));
                printf ("Processus #%d : réception de %d\n",i,info);
                close (ecr);
 
                /* En fin de traitement, un break pour quitter la boucle */
                /* démarrée par le processus père.                       */
                break;
            }
            else perror ("Erreur à l'appel de fork()");
        }
 
        /* Si PID est non nul à l'issue de la boucle, c'est qu'on est  */
        /* toujours dans le processus père. On en profite pour faire n */
        /* wait() successifs pour attendre tous nos fils.              */
        if (pid>0)
        for (i=0;i<nbProcessus;++i) wait(NULL);
    }
 
    return 0;
}