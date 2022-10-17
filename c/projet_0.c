#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "projet_0v1.h"

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
		


void initPlateau(int nbJoueur,int **tableauDeTubes,struct Joueur **tableauDeJoueur ){
  int ecr=1;
  int lu=100;
  pid_t pid;
  
  for(int i=0;i<nbJoueur;i++){
    if (pipe(tableauDeTubes[i]) != 0) {/* pipe */
 			 fprintf(stderr, "Erreur dans pipe \n"); 
 			 exit(-1);
   	}
  }

  for(int i=0;i<nbJoueur;i++){
    pid = fork();
    if (pid>0){
                printf ("PID du PERE %d\n",getpid());
                printf ("Création JOUEUR #%d : PID %d\n",i,pid);
                wait(NULL);
    }
    else if (!pid){
              
              if(i!=0){
              			if(read(tableauDeTubes[i-1][0], &lu, sizeof(int))>=0){
                			//close(tableauDeTubes[i-1][0]);
                 			printf("je recois :%d du joueur precedent\n", lu);
              			}else{
                			fprintf(stderr, "Erreur read \n");
              			}
          		}
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
          		write(tableauDeTubes[i][1], &ecr, sizeof(int));
          		//close(tableauDeTubes[i][1]);
          		printf("j'envoie :%d au joueur suivant\n", ecr);
             printf("\n\n");
             
          		
       break;
    }else{
    perror ("Erreur à l'appel de fork()");
    }
    ecr++;
  }
}


