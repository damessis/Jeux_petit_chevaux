#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "projet_0v1.h"

int nbreJoueur;

struct PositionPion {
    int zone;
    int cellule;
};

struct Joueur {
    int pid;
    struct PositionPion *pion1;
    struct PositionPion *pion2;
}

Joueur* tabJoueur;
int* tubes;
/*---------------------------------------------------------------------------------------------------------*/

struct Joueur **createTableDeJoueur(int nbJoueur){
  struct Joueur **tableauDeJoueur =(struct Joueur **)malloc(nbJoueur*sizeof(struct Joueur *));
  struct Joueur *joueur=(struct Joueur *)malloc(nbJoueur*sizeof(struct Joueur));
  struct Position *position1=(struct Position *)malloc(nbJoueur*sizeof(struct Position));
 struct Position *position2=(struct Position *)malloc(nbJoueur*sizeof(struct Position));
  for(int i = 0 ; i < nbJoueur ; i++){
		tableauDeJoueur[i] = &joueur[i];
	}
  for(int i = 0 ; i < nbJoueur ; i++){
    tableauDeJoueur[i][0].pion1 = &position1[i];
    tableauDeJoueur[i][0].pion2 = &position2[i];
  }
  return tableauDeJoueur;
}

/*---------------------------------------------------------------------------------------------------------*/


void detruireLesJoueur( struct Joueur **tableauDeJoueur){
	free(tableauDeJoueur[0]);
	free(tableauDeJoueur);
}


/*---------------------------------------------------------------------------------------------------------*/


int **createTableDeTubes(int nbJoueur){
  int **tableauDeTubes=(int **)malloc(sizeof(int*)*nbJoueur);
  int *tubes = (int *)malloc(sizeof(int)*nbJoueur*2);
  for(int i = 0 ; i < nbJoueur ; i++){
		tableauDeTubes[i] = &tubes[i*2];
	}
	return tableauDeTubes;
}

/*---------------------------------------------------------------------------------------------------------*/


void detruireLesTubes(int **tableauDeTubes){
	free(tableauDeTubes[0]);
	free(tableauDeTubes);
}

/*---------------------------------------------------------------------------------------------------------*/


void creerfils(struct Joueur **tableauDeJoueur, int **tableauDeTubes,int n,int nbJoueur){
    	switch (fork()){
    		case -1:
        		fprintf(stderr, "Erreur du premier fork\n");
        		exit(-1);
    		case 0:
          		printf("n %d\n",i);
          		(tableauDeJoueur[i][0]).pid=getpid();
          		(tableauDeJoueur[i][0]).pion1->zone=i;
          		(tableauDeJoueur[i][0]).pion1->cellule=0;
			(tableauDeJoueur[i][0]).pion2->zone=i;
          		(tableauDeJoueur[i][0]).pion2->cellule=0;
          		printf("pid du joueur courant: %d\n", tableauDeJoueur[i]->pid);
          		printf("position initiale premier pion du joueur courant zone: %d\n", tableauDeJoueur[i][0].pion1->zone);
          		printf("position initiale premier pion du joueur courant cellule: %d\n", tableauDeJoueur[i][0].pion1->cellule);
			printf("position initiale deuxieme pion du joueur courant zone: %d\n", tableauDeJoueur[i][0].pion1->zone);
          		printf("position initiale deuxieme pion du joueur courant cellule: %d\n", tableauDeJoueur[i][0].pion1->cellule);
          		printf("pid: %d   ppid: %d\n", getpid(), getppid() );
          		if (pipe(tableauDeTubes[i]) != 0) {/* pipe */
              			fprintf(stderr, "Erreur dans pipe \n"); 
              			exit(-1);
          		}
            		write(tableauDeTubes[i][1], &ecr, sizeof(int));
            		close(tableauDeTubes[i][1]);
            		printf("j'envoie :%d au joueur suivant\n", ecr);
          		if(i!=0){
              			if(read(tableauDeTubes[i-1][0], &lu, sizeof(int))>0){
                			close(tableauDeTubes[i-1][0]);
                 			printf("je recois :%d du joueur precedent\n", lu);
              			}else{
                			fprintf(stderr, "Erreur read \n");
              			}
          		}
          		if(i==nbJoueur-1){
            			if(read(tableauDeTubes[nbJoueur-1][0], &lu, sizeof(int))>0){
                			close(tableauDeTubes[nbJoueur-1][0]);
                 			printf("je recois :%d du joueur precedent\n", lu);
              			}else{
                			fprintf(stderr, "Erreur read \n");
              			}
          		}  
  			default:
            			printf("\n\n");
      				while (wait(NULL)!=-1);
 
  	}
  			
}

void initPlateau(int nbJoueur,int **tableauDeTubes,struct Joueur **tableauDeJoueur ){
  /* Boucle for qui crée tous les fils */
  for(int i = 0; i < n; i++){
    creerfils(tableauDeJoueur, tableauDeTubes,i,nbJoueur);
  }
}

