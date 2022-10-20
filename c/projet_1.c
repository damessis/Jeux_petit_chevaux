#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "time.h"
#include "projet_1.h"
#include <stdbool.h>


bool partieGagne=false;
pid_t pid;
pid_t pidJoueurSuivant;
int nbJoueur;

int de(int dernier_lance){
	int a;
	srand(time(NULL));
	a=(rand()+dernier_lance)%6;
  printf("Le résultat du dé est : %i\n", a+1);
return a+1;// oui on a rarement vu des des faire 0. donc +1
}


/*---------------------------------------------------------------------------------------------------------*/



void initialiser_joueur(struct Joueur tableauJoueur[],int joueur,pid_t pid){
  tableauJoueur[joueur].pid=pid;
  tableauJoueur[joueur].pion1[0]=joueur;
  tableauJoueur[joueur].pion1[1]=-8;
  tableauJoueur[joueur].pion2[0]=joueur;
  tableauJoueur[joueur].pion2[1]=-8;
}


/**
 * Retrourne le joueur avant le joueur en parametre
 * 
*/
int joueurPrecedent(int joueur, int nbJoueur) {
    int res;
    if (joueur == 0) {
        res = nbJoueur-1;
    } else {
        res = joueur-1;
    }
    return res;
}


/**
 * Avance le pion à la case suivante selon le résultat du dé
 * 
*/
void caseSuivante(int joueur, int pion, int de, Joueur* tabJoueurs, int nbJoueur) {
    int newCellule;
    int pasBouger;
    if (pion == 1) {
        newCellule = tabJoueurs[joueur].pion1[1] + de;
        if (newCellule > 13) { // pion sort de la zone
            if (tabJoueurs[joueur].pion1[0] == joueurPrecedent(joueur, nbJoueur)) { //cas où le pion est dans la zone juste avant l'arrivée
                tabJoueurs[joueur].pion1[1] = 0; // Pion sur la case d'arrivée
                tabJoueurs[joueur].pion1[0] = joueur;
            } else {
                tabJoueurs[joueur].pion1[1] = newCellule - 14; // 1e case d'une zone est la case 0
                if (tabJoueurs[joueur].pion1[0] != nbJoueur-1) {
                    tabJoueurs[joueur].pion1[0]++; 
                } else {
                    tabJoueurs[joueur].pion1[0] = 0;
                }
            }
        } else if (tabJoueurs[joueur].pion1[0] == joueur && tabJoueurs[joueur].pion1[1] == 0) { //cas où le pion1 est sur sa case d'arrivée
            if (de == 1) { //rentre dans l'escalier
                tabJoueurs[joueur].pion1[1] = -1;
            } else {
                printf("Le pion1 ne peut pas bouger !\n");
                pasBouger = 1;
            }
        } else {
            tabJoueurs[joueur].pion1[1] = newCellule;
        }
        if (pasBouger != 1) { //si le pion a bougé
            printf("Joueur %i : le pion1 a avancé : zone %i cellule %i\n", joueur, tabJoueurs[joueur].pion1[0], tabJoueurs[joueur].pion1[1]);
        }
    } else {
        newCellule = tabJoueurs[joueur].pion2[1] + de;
        if (newCellule > 13) { // pion sort de la zone
            if (tabJoueurs[joueur].pion2[0] == joueurPrecedent(joueur, nbJoueur)) { //cas où le pion est dans la zone juste avant l'arrivée
                tabJoueurs[joueur].pion2[1] = 0; // Pion sur la case d'arrivée
                tabJoueurs[joueur].pion2[0] = joueur;
            } else {
                tabJoueurs[joueur].pion2[1] = newCellule - 14; // 1e case d'une zone est la case 0
                if (tabJoueurs[joueur].pion2[0] != nbJoueur-1) {
                    tabJoueurs[joueur].pion2[0]++; 
                } else {
                    tabJoueurs[joueur].pion2[0] = 0;
                }
            }
        } else if (tabJoueurs[joueur].pion2[0] == joueur && tabJoueurs[joueur].pion2[1] == 0) { //cas où le pion2 est sur sa case d'arrivée
            if (de == 1) { //rentre dans l'escalier
                tabJoueurs[joueur].pion2[1] = -1;
            } else {
                printf("Le pion2 ne peut pas bouger !\n");
                pasBouger = 1;
            }
        } else {
            tabJoueurs[joueur].pion2[1] = newCellule;
        }
        if (pasBouger != 1) { //si le pion a bougé
            printf("Joueur %i : le pion2 a avancé : zone %i cellule %i\n", joueur, tabJoueurs[joueur].pion2[0], tabJoueurs[joueur].pion2[1]);
        }
    }
}


/**
 * Sort le pion de l'écurie
 * 
*/
void sortieEcurie(int joueur, int pion, Joueur* tabJoueurs) {
    if (pion == 1) {
        tabJoueurs[joueur].pion1[1] = 1;
        printf("Le pion1 du joueur%i est sortie de l'écurie, il est maintenant sur la case %i de la zone %i\n", joueur, tabJoueurs[joueur].pion1[1], tabJoueurs[joueur].pion1[0]);
    } else {
        tabJoueurs[joueur].pion2[1] = 1;
        printf("Le pion2 du joueur%i est sortie de l'écurie, il est maintenant sur la case %i de la zone %i\n", joueur, tabJoueurs[joueur].pion2[1], tabJoueurs[joueur].pion2[0]);
    }
}


//void caseOccupee() {}


/**
 * Phase d'avancement d'un joueur
 * 
*/
void avancerPion(int joueur, int de, Joueur* tabJoueurs, int nbJoueur) {
    char c;
    int choixPion;
    
    if (tabJoueurs[joueur].pion1[1] == 99 && tabJoueurs[joueur].pion2[1] == 99) { //cas des 2 pions dans l'écurie
        if (de == 6) { // cas où le dé = 6 donc on sort le pion1 par défault
            sortieEcurie(joueur, 1, tabJoueurs);
        } else { // cas où on ne fait rien
            printf("Le joueur%i ne peut pas avancer de pion\n", joueur);
        }
    } else if (tabJoueurs[joueur].pion2[1] == 99) { //cas où pion2 est dans l'écurie
        if (de == 6) { // cas du dé = 6
            printf("Joueur %i pion1 : zone %i cellule %i\n", joueur, tabJoueurs[joueur].pion1[0], tabJoueurs[joueur].pion1[1]);
            printf("Joueur %i pion2 dans l'écurie\n", joueur);
            printf("Joueur %i : Voulez-vous sortir votre pion2 de l'écurie ? (Si oui tapez o sinon n)\n", joueur);
            scanf("%c", &c);
            if (c == 'o') { // cas où on sort le pion2 de l'écurie
                sortieEcurie(joueur, 2, tabJoueurs);
            } else { // cas où on bouge le pion1
                caseSuivante(joueur, 1, de, tabJoueurs, nbJoueur);
            }
        } else {
            caseSuivante(joueur, 1, de, tabJoueurs, nbJoueur);
        }
    } else if (tabJoueurs[joueur].pion1[1] == 99) { //cas où pion1 est dans l'écurie
        if (de == 6) { // cas du dé = 6
            printf("Joueur %i pion1 dans l'écurie\n", joueur);
            printf("Joueur %i pion2 : zone %i cellule %i\n", joueur, tabJoueurs[joueur].pion2[0], tabJoueurs[joueur].pion2[1]);
            printf("Joueur %i : Voulez-vous sortir votre pion1 de l'écurie ? (Si oui tapez o sinon n)\n", joueur);
            scanf("%c", &c);
            if (c == 'o') { // cas où on sort le pion1 de l'écurie
                sortieEcurie(joueur, 1, tabJoueurs);
            } else { // cas où on bouge le pion2
                caseSuivante(joueur, 2, de, tabJoueurs, nbJoueur);
            }
        } else {
            caseSuivante(joueur, 2, de, tabJoueurs, nbJoueur);
        }
    } else { // cas où les 2 pions sont sur le plateau
        printf("Joueur %i pion1 : zone %i cellule %i\n", joueur, tabJoueurs[joueur].pion1[0], tabJoueurs[joueur].pion1[1]);
        printf("Joueur %i pion2 : zone %i cellule %i\n", joueur, tabJoueurs[joueur].pion2[0], tabJoueurs[joueur].pion2[1]);
        printf("Joueur %i : Quel pion voulez-vous bougez ? (Taper 1 pour pion 1 ou 2 pour pion2)\n", joueur);

        scanf("%i", &choixPion);

        if (choixPion == 1) { // cas où on bouge le pion1
            caseSuivante(joueur, 1, de, tabJoueurs, nbJoueur);
        } else { // cas où on bouge le pion2
            caseSuivante(joueur, 2, de, tabJoueurs, nbJoueur);
        }
    }
}
				



void initPlateau(int nbJoueur, struct Joueur tableauDeJoueur[], int tableauDeTubes[nbJoueur][2], int tableauDeTubes2[nbJoueur][2]){

  for(int i=0;i<nbJoueur;i++){
    pid = fork();
    if (pid>0){
                printf ("PID du PERE %d\n",getpid());
                printf ("JOUEUR #%d : PID %d\n",i,pid);
                wait(NULL);
    }else if (!pid){
              initialiser_joueur(tableauDeJoueur,i,getpid());
              printf ("Je suis le joueur %d et mon pid est: %d\n",i,tableauDeJoueur[i].pid);
       break;
    }else{
    perror ("Erreur à l'appel de fork()");
    }
  }
  
    
  
}


/*------------------------------------------------------------------------------------------------------*/

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
   while(!partieGagne){
     if(getpid()==tableauDeJoueur[0].pid){
	printf("Je suis joueur 0 mon pid est %d\n",getpid());
        if(getpid()==pidJoueurSuivant){
        	
        }else{
        
        }
     }else if(getpid()==tableauDeJoueur[1].pid){
       printf("Je suis joueur 1 mon pid est %d\n",getpid());
       if(getpid()==pidJoueurSuivant){
        	
       }else{
        
       }
     }else if(getpid()==tableauDeJoueur[2].pid){
       printf("Je suis joueur 2 mon pid est %d\n",getpid());
       if(getpid()==pidJoueurSuivant){
        	
       }else{
        
       }
     }else if(getpid()==tableauDeJoueur[3].pid){
       printf("Je suis joueur 3 mon pid est %d\n",getpid());
       if(getpid()==pidJoueurSuivant){
        	
       }else{
        
       }
     }else{
     
     }
     partieGagne=true;//on effacera ca d'ici ;c'est dans jouer qu'on doit modifier partieGagnee
  }

   
     
}
