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
    PositionPion pion1;
    PositionPion pion2;
}

Joueur* tabJoueur;
int* tubes;


void creerfils(struct Joueur *jx, int* tube,int numerofils){
	int *pinit=tube;
	int i=0;
	int k=0;
  	switch (fork())
    	{
    		case -1:
        		fprintf(stderr, "Erreur du premier fork\n");
        		exit(-1);
    		case 0:
        		printf("pid: %d   ppid: %d\n", getpid(), getppid() );
        		close(1);
        		dup(tube[numerofils][1]);
			close(0);
			if(numerofils==0){
				while(tube+1!=null){
					tube++;
				}
				dup(*tube[0]);
			tube=pinit+1;
			}else if(numerofils==3/*nbJoueur*//*longeur du tableau -1 (arguement dans le main*/){
				close(1);
                    		dup(tube[numerofils][1]);
				close(0);
                    		dup(tube[0][0]);	
			}else{
			      dup(tube[numerofils-1][0]);
			}
			
			while(i<4){
				while(k<2){
					close(tube[i][j]);
				}
			}
  			exit(0);
  		default:
      			wait(NULL);
  	}
}



void initPlateau(int nbreJoueur){

  /* Allocation de la mémoire pour le tableau de Joueur et de tubes */
  tabJoueur = (Joueur *)malloc(nbreJoueur * sizeof(Joueur));
  tubes = (int[2])malloc(nbreJoueur*sizeof(int[2]));

  for (int i = 0; i < nbreJoueur; i++) {
    tabJoueur[i][2].zone = i; // pion1 dans la zone du joueur
    tabJoueur[i][2].cellule = -1; // -1 est le cas où le pion1 est encore dans l'écurie
    tabJoueur[i][3].zone = i; // pion2 dans la zone du joueur
    tabJoueur[i][3].cellule = -1; // -1 est le cas où le pion2 est encore dans l'écurie
  }

  /* Boucle for qui crée tous les fils */
  for(int i = 0; i < n; i++){
    creerfils(tabJoueur, tubes, i);
  }
}
