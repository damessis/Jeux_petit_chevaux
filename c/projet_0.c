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




