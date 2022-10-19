#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include "projet_0v1.h"
#include <stdbool.h>


/*---------------------------------------------------------------------------------------------------------*/

bool partieGagne=false;
pid_t pid;
pid_t pidJoueurSuivant;

int de(int dernier_lance){
	int a;
	srand(time(NULL));
	a=(rand()+dernier_lance)%6;
return a+1;// oui on a rarement vu des des faire 0. donc +1
}


/*---------------------------------------------------------------------------------------------------------*/



void initialiser_joueur(struct Joueur tableauJoueur[],int joueur,pid_t pid){
  tableauJoueur[joueur].pid=pid;
  tableauJoueur[joueur].pion1[0]=joueur;
  tableauJoueur[joueur].pion1[1]=-1;
  tableauJoueur[joueur].pion2[0]=joueur;
  tableauJoueur[joueur].pion2[1]=-1;
}



/*---------------------------------------------------------------------------------------------------------*/
		


void initPlateau(int nbJoueur, struct Joueur tableauDeJoueur[], int tableauDeTubesFils[][],int tableauDeTubesPere[][]){

  for(int i=0;i<nbJoueur;i++){
    pid = fork();
    if (pid>0){
                printf ("PID du PERE %d\n",getpid());
                printf ("Création JOUEUR #%d : PID %d\n",i,pid);
                wait(NULL);
    }else if (!pid){
              initialiser_joueur(tableauDeJoueur,i,getpid());
              printf ("Je suis le joueur %d et mon pid est: %d\n",i,tableauDeJoueur[i].pid);
       break;
    }else{
    perror ("Erreur à l'appel de fork()");
    }
  }
  while(!partieGagne){
     if(getpid()==tableauDeJoueur[0].pid){
        if(getpid()==pidJoueurSuivant){
        
        }else{
        
        }
     }else if(getpid()==tableauDeJoueur[1].pid){
       if(getpid()==pidJoueurSuivant){
        
       }else{
        
       }
     }else if(getpid()==tableauDeJoueur[2].pid){
       if(getpid()==pidJoueurSuivant){
        
       }else{
        
       }
     }else if(getpid()==tableauDeJoueur[3].pid){
       if(getpid()==pidJoueurSuivant){
        
       }else{
        
       }
     }else{
     
     }
     
     
      
      //fait write dans tube 0
     }
     }
    }
    partieGagne=true;
  }
  
}


/*---------------------------------------------------------------------------------------------------------*/



int main(int argc, char *argv[]){
   int nbJoueur;
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
   int tableauDeTubesFils[nbJoueur][2];// on stocke ici les tubes qui permette aux fils de communiquer entre eux*
   struct Joueur tableauDeJoueur[nbJoueur];
   int tableauDeTubesPere[nbJoueur][2];// on stocke ici les tubes qui permette au pere d'envoyer des informations aux fils et d'en recevoir
   for(int i=0;i<nbJoueur;i++){
    if (pipe(tableauDeTubesFils[i]) != 0) {/* pipe */
 			 fprintf(stderr, "Erreur dans pipe \n"); 
 			 exit(-1);
   	}
   }
   for(int i=0;i<nbJoueur;i++){
    if (pipe(tableauDeTubesPere[i]) != 0) {/* pipe */
 			 fprintf(stderr, "Erreur dans pipe \n"); 
 			 exit(-1);
   	}
   }
   initPlateau(nbJoueur,tableauDeJoueur,tableauDeTubesFils,tableauDeTubesPere);
   
   
     
}

