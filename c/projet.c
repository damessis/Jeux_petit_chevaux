#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "projet_0.h"

int main(int argc, char *argv[]){
   if(argc!=2){
     fprintf(stderr,"Erreur nombre d'argument incorrect Format correct <nomprogramme> <nombre de joueurs>\n");
     exit(-1);
   }else{
     nbJoueur=atoi(argv[1]);
     if((nbJoueur!=2) && (nbJoueur!=4)){
        fprintf(stderr,"Nombre de joueur choisi incorrect Format correct.Pour une partie il faut soit '2 joueurs' soit '4 joueurs'\n");
        exit(-1); 
     } 
   }
   int tableauDeTubes[nbJoueur][2];// on stocke ici les tubes qui permette aux fils de communiquer entre eux*
   struct Joueur tableauDeJoueur[nbJoueur];
   int tableauDeTubes2[nbJoueur][2];// on stocke ici les tubes qui permette au pere d'envoyer des informations aux fils et d'en recevoir
   for(int i=0;i<nbJoueur;i++){
    if (pipe(tableauDeTubes[i]) != 0) {/* pipe */
 			 fprintf(stderr, "Erreur dans pipe \n"); 
 			 exit(-1);
   	}
   }
   for(int i=0;i<nbJoueur;i++){
    if (pipe(tableauDeTubes2[i]) != 0) {/* pipe */
 			 fprintf(stderr, "Erreur dans pipe \n"); 
 			 exit(-1);
   	}
   }
   initPlateau(nbJoueur,tableauDeJoueur,tableauDeTubes,tableauDeTubes2);
   
   
     
}
