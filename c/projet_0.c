/**
 * @author OUCHANE Souleymen
 * @author DAMESSI Samuel
 * Première étape du projet permettant de créer N processus fils du processus initial
*/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>


/**
 * Créer N processus fils
 * @param int nbJoueur
*/
void creerNprocessus(int nbJoueur){
  int pid;
  for(int i=0;i<nbJoueur;i++){
    pid = fork();
    if (pid>0){
              printf ("Je suis le pere mon pid est %d\n",getpid());
              wait(NULL);
    }else if (!pid){
              printf ("Je suis le processus %d et mon pere est %d\n",getpid(),getppid());
              break;
    }else{
    perror ("Erreur à l'appel de fork()");
    }
  }
}



int main(int argc, char *argv[]){
    int nbJoueur;
    if(argc!=2){
     fprintf(stderr,"Erreur nombre d'argument incorrect Format correct <nomprogramme> <nombre de joueurs>\n");
     exit(-1);
    }else{
     nbJoueur=atoi(argv[1]);
    }
    printf ("Vous vouliez creer %d fils,les voici\n",nbJoueur);
    creerNprocessus(nbJoueur);
}