#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "projet_0.h"

void jouer() {

}

int main(int argc, char *argv[]){
   int nbJoueur;
   int **tableauDeTubes;
   struct Joueur **tableauDeJoueur;
   if(argc==2){
     nbJoueur=atoi(argv[1]);
     printf("%d\n",nbJoueur);
     if(nbJoueur==2){
        tableauDeTubes=createTableDeTubes(nbJoueur);
        tableauDeJoueur=createTableDeJoueur(nbJoueur);
     }else if(nbJoueur==4){
        tableauDeTubes=createTableDeTubes(nbJoueur);
        tableauDeJoueur=createTableDeJoueur(nbJoueur);
     }else{
       fprintf(stderr,"Nombre de joueur choisi incorrect Format correct.Pour une partie il faut soit '2 joueurs' soit '4 joueurs'\n");
       exit(-1);
     }
   }else{
     fprintf(stderr,"Erreur nombre d'argument incorrect Format correct <nomprogramme> <nombre de joueurs>\n");
     exit(-1);
   }
   initPlateau(nbJoueur,tableauDeTubes,tableauDeJoueur);  
}
