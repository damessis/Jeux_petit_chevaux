#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "time.h"
//#include "projet_1.h"
#include <stdbool.h>




/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/


//variables globales qui sont utilise dans plus part des fonctions

bool partieGagne=false;
pid_t pid;
pid_t pidPere;
int nbJoueur;
pid_t pidJoueurSuivant;
pid_t pidJoueurCourant;
int lance=0;


/*chaque pion est detient certaines informations pour l'identifierde maniere unique*/
struct Joueur {
		pid_t pid; // le nom du joueur a qui appartient ce pion en l'occurence dans notre programme les joueur sont des processus fils du programme main 
    //chaque joueur a 2 pion et chaque pion est identifié par sa zone et sa case 
    int pion1[2];//a l'indice 0 on stocke la zone du pion et a l'indice 1 on stocke la case
    int pion2[2];
};


/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/



/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void victoire(struct Joueur *tableauDeJoueur,int nbJoueur){
  for(int i=0;i<nbJoueur;i++){
    if((tableauDeJoueur[i].pion1[0]==i && tableauDeJoueur[i].pion1[1]==-1) || (tableauDeJoueur[i].pion2[0]==i && tableauDeJoueur[i].pion2[1]==-1)){
      partieGagne=true;
      printf("Felicitations, le joueur %i a gagné\n", i);
      for(int i=0;i<nbJoueur;i++){
        kill(tableauDeJoueur[i].pid,SIGKILL);
      }
      exit(0);
    }
  }
}




/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/


//fonction qui retourne un nombre aléatoire compris entre 1 et 6, 1 et 6 inclus
int de(int dernier_lance){
	int a;
	srand(time(NULL));
	a=(rand()+dernier_lance)%6;
return a+1;// oui on a rarement vu des des faire 0. donc +1
}


int joueurPrecedent(int joueur, int nbJoueur) {
    int res;
    if (joueur == 0) {
        res = nbJoueur-1;
    } else {
        res = joueur-1;
    }
    return res;
}

void caseSuivante(int joueur, int pion, int de, struct Joueur *tabJoueurs, int nbJoueur) {
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


void sortieEcurie(int joueur, int pion, struct Joueur *tabJoueurs) {
    if (pion == 1) {
        tabJoueurs[joueur].pion1[1] = 1;
        printf("Le pion1 du joueur%i est sortie de l'écurie, il est maintenant sur la case %i de la zone %i\n", joueur, tabJoueurs[joueur].pion1[1], tabJoueurs[joueur].pion1[0]);
    } else {
        tabJoueurs[joueur].pion2[1] = 1;
        printf("Le pion2 du joueur%i est sortie de l'écurie, il est maintenant sur la case %i de la zone %i\n", joueur, tabJoueurs[joueur].pion2[1], tabJoueurs[joueur].pion2[0]);
    }
}


void avancerPion(int joueur, int de, struct Joueur *tabJoueurs, int nbJoueur) {
    char c;
    int choixPion;
    
    if (tabJoueurs[joueur].pion1[1] == -8 && tabJoueurs[joueur].pion2[1] == -8) { //cas des 2 pions dans l'écurie
        if (de == 6) { // cas où le dé = 6 donc on sort le pion1 par défault
            sortieEcurie(joueur, 1, tabJoueurs);
        } else { // cas où on ne fait rien
            printf("Le joueur%i ne peut pas avancer de pion\n", joueur);
        }
    } else if (tabJoueurs[joueur].pion2[1] == -8) { //cas où pion2 est dans l'écurie
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
    } else if (tabJoueurs[joueur].pion1[1] == -8) { //cas où pion1 est dans l'écurie
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
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/



//cette fonction permet d'afficher l'etat de vu du point de vue de n'importe quel processus
void etatPlateau(struct Joueur *tableauDeJoueur, int nbJoueur, pid_t pid){
  int j=0;
  if(getpid()==pid){
    while(j<nbJoueur && pid!=tableauDeJoueur[j].pid){
      j++;
    }
  }if(j<nbJoueur){
      if(getpid()==pid){
        printf("\n JE SUIS LE JOUEUR %d MON PID EST : %d \n",j,tableauDeJoueur[j].pid);
        printf("Voici les informations que j'ai sur le plateau\n");
        printf("\n-----------------------------------------------------------------\n");
        for(int i=0;i<nbJoueur;i++){
      		printf("joueur%d",i);
      		printf("       pid :%d\n",tableauDeJoueur[i].pid);
      		printf("       pion1 : zone %d case %d",tableauDeJoueur[i].pion1[0],tableauDeJoueur[i].pion1[1]);
      		printf("       pion2 : zone %d case %d\n",tableauDeJoueur[i].pion1[0],tableauDeJoueur[i].pion1[1]);
    		}
        printf("\n\n-----------------------------------------------------------------\n\n");
      }
  }else{
    if(getpid()==pidPere){
        printf("\n JE SUIS PROCESSUS PERE MON PID EST : %d \n",pid);
        printf("Voici les informations que j'ai sur le plateau\n");
        printf("\n\n-----------------------------------------------------------------\n\n");
        for(int i=0;i<nbJoueur;i++){
      		printf("j#%d",i);
      		printf("       pid :%d\n",tableauDeJoueur[i].pid);
      		printf("       pion1 : zone %d case %d",tableauDeJoueur[i].pion1[0],tableauDeJoueur[i].pion1[1]);
      		printf("       pion2 : zone %d case %d\n",tableauDeJoueur[i].pion1[0],tableauDeJoueur[i].pion1[1]);
    		}
        printf("\n\n-----------------------------------------------------------------\n\n");
      }
  }
}



/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/


//fonction qui permet au debut a chaque joueur de connaitre la position de chaque joueur,c'est elle qui initie la premiere communication
void initCommunication(int nbJoueur, struct Joueur *tableauDeJoueur,int tableauDeTubes2[nbJoueur+2][2]){
  if(nbJoueur=4){
    if(getpid()==pidPere){
       write(tableauDeTubes2[0][1], tableauDeJoueur, nbJoueur*sizeof(struct Joueur));
       write(tableauDeTubes2[1][1], tableauDeJoueur, nbJoueur*sizeof(struct Joueur));
       write(tableauDeTubes2[2][1], tableauDeJoueur, nbJoueur*sizeof(struct Joueur));
       write(tableauDeTubes2[3][1], tableauDeJoueur, nbJoueur*sizeof(struct Joueur));
     }
     if(getpid()==tableauDeJoueur[0].pid){
         read(tableauDeTubes2[0][0], tableauDeJoueur, nbJoueur*sizeof(struct Joueur));
     }else if(getpid()==tableauDeJoueur[1].pid){
         read(tableauDeTubes2[1][0], tableauDeJoueur, nbJoueur*sizeof(struct Joueur));
     }else if(getpid()==tableauDeJoueur[2].pid){
         read(tableauDeTubes2[2][0], tableauDeJoueur, nbJoueur*sizeof(struct Joueur));
     }else if(getpid()==tableauDeJoueur[3].pid){
         read(tableauDeTubes2[3][0], tableauDeJoueur, nbJoueur*sizeof(struct Joueur));
     }
  }else{
    if(getpid()==pidPere){
       write(tableauDeTubes2[0][1], tableauDeJoueur, nbJoueur*sizeof(struct Joueur));
       write(tableauDeTubes2[1][1], tableauDeJoueur, nbJoueur*sizeof(struct Joueur));
     }
     if(getpid()==tableauDeJoueur[0].pid){
         read(tableauDeTubes2[0][0], tableauDeJoueur, nbJoueur*sizeof(struct Joueur));
     }else if(getpid()==tableauDeJoueur[1].pid){
         read(tableauDeTubes2[1][0], tableauDeJoueur, nbJoueur*sizeof(struct Joueur));
     }
  }
}


/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/


//c'est cette fonction qui initialise le plateau avec nbJoueur avec les informations
// comme leur pid et les positions des deux pions
//prenant l'exemple du joueur 1: sachant qu'au moment de la création de joueur0 
//par le père les joueur 1,2 et 3 n'existe pas encore alors on fait appel 
//a la fontion initCommunication pour mettre les informations de chaque joueur sur le plateau au meme niveau puis on affiche le plateau de depart du point de vue de chaque joueur

void initPlateau(int nbJoueur, struct Joueur *tableauDeJoueur,int tableauDeTubes2[nbJoueur+1][2]){
  
  for(int i=0;i<nbJoueur;i++){
    pid = fork();
    if (pid>0){
              pidPere=getpid();
              printf ("PID du PERE %d\n",getpid());
    		      tableauDeJoueur[i].pid=pid;
    		      tableauDeJoueur[i].pion1[0]=i;
    	        tableauDeJoueur[i].pion1[1]=-8;
    	        tableauDeJoueur[i].pion2[0]=i;
    	        tableauDeJoueur[i].pion2[1]=-8;
              printf ("JOUEUR #%d : PID %d\n",i,pid);
    }else if (!pid){
              tableauDeJoueur[i].pid=getpid();
       break;
    }else{
    perror ("Erreur à l'appel de fork()");
    }
  }
   initCommunication(nbJoueur,tableauDeJoueur,tableauDeTubes2);
   if(getpid()==pidPere){
       pidJoueurSuivant=tableauDeJoueur[0].pid;
       etatPlateau(tableauDeJoueur, nbJoueur,pidPere);
   }
   for(int i=0;i<nbJoueur;i++){
     sleep(1);
     if(getpid()==tableauDeJoueur[i].pid){
       etatPlateau(tableauDeJoueur, nbJoueur,tableauDeJoueur[i].pid);
     }
   }
  
     
}


/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/



void jeu(int nbJoueur,struct Joueur *tableauDeJoueur,int tableauDeTubes[nbJoueur+1][2],int tableauDeTubes2[nbJoueur+2][2] ){
  if(nbJoueur==4){
    if(getpid()==pidPere){
       write(tableauDeTubes2[0][1], &pidJoueurSuivant, sizeof(pid_t));
       write(tableauDeTubes2[1][1], &pidJoueurSuivant, sizeof(pid_t));
       write(tableauDeTubes2[2][1], &pidJoueurSuivant, sizeof(pid_t));
       write(tableauDeTubes2[3][1], &pidJoueurSuivant, sizeof(pid_t));
     }
    while(!partieGagne){
       if(getpid()==tableauDeJoueur[0].pid){
          read(tableauDeTubes2[0][0], &pidJoueurCourant, sizeof(pid_t));
          if(getpid()==pidJoueurCourant){
            lance=de(lance);
            printf("Lance= %d\n",lance);
            if(lance==6){
              pidJoueurSuivant=tableauDeJoueur[0].pid;
            }else{
              pidJoueurSuivant=tableauDeJoueur[1].pid;
            }
          	avancerPion(0, lance, tableauDeJoueur,nbJoueur);
            write(tableauDeTubes[0][1], tableauDeJoueur, nbJoueur*sizeof(struct Joueur));
            write(tableauDeTubes2[4][1], &pidJoueurSuivant, sizeof(pid_t));
            write(tableauDeTubes2[5][1], tableauDeJoueur, nbJoueur*sizeof(struct Joueur));
          }else{
            sleep(1);
          	read(tableauDeTubes[3][0], tableauDeJoueur, nbJoueur*sizeof(struct Joueur));
          	etatPlateau(tableauDeJoueur, nbJoueur,tableauDeJoueur[0].pid);
          	write(tableauDeTubes[0][1], tableauDeJoueur, nbJoueur*sizeof(struct Joueur));
          }
       }
       if(getpid()==tableauDeJoueur[1].pid){
         read(tableauDeTubes2[1][0], &pidJoueurCourant, sizeof(pid_t));
         if(getpid()==pidJoueurCourant){
            lance=de(lance);
            printf("Lance= %d\n",lance);
            if(lance==6){
              pidJoueurSuivant=tableauDeJoueur[1].pid;
            }else{
              pidJoueurSuivant=tableauDeJoueur[2].pid;
            }
          	avancerPion(1, lance, tableauDeJoueur,nbJoueur);
          	write(tableauDeTubes[1][1], tableauDeJoueur, nbJoueur*sizeof(struct Joueur));
            write(tableauDeTubes2[4][1], &pidJoueurSuivant, sizeof(pid_t));
            write(tableauDeTubes2[5][1], tableauDeJoueur, nbJoueur*sizeof(struct Joueur));
         }else{
          	read(tableauDeTubes[0][0], tableauDeJoueur, nbJoueur*sizeof(struct Joueur));
          	etatPlateau(tableauDeJoueur, nbJoueur,tableauDeJoueur[1].pid);
          	write(tableauDeTubes[1][1], tableauDeJoueur, nbJoueur*sizeof(struct Joueur));
         }
       }
       if(getpid()==tableauDeJoueur[2].pid){
         read(tableauDeTubes2[2][0], &pidJoueurCourant, sizeof(pid_t));
         if(getpid()==pidJoueurCourant){
            lance=de(lance);
            printf("Lance= %d\n",lance);
            if(lance==6){
              pidJoueurSuivant=tableauDeJoueur[2].pid;
            }else{
              pidJoueurSuivant=tableauDeJoueur[3].pid;
            }
          	avancerPion(2, lance, tableauDeJoueur,nbJoueur);
          	write(tableauDeTubes[2][1], tableauDeJoueur, nbJoueur*sizeof(struct Joueur));
            write(tableauDeTubes2[4][1], &pidJoueurSuivant, sizeof(pid_t));
            write(tableauDeTubes2[5][1], tableauDeJoueur, nbJoueur*sizeof(struct Joueur));
         }else{	
          	read(tableauDeTubes[1][0], tableauDeJoueur, nbJoueur*sizeof(struct Joueur));
          	etatPlateau(tableauDeJoueur, nbJoueur,tableauDeJoueur[2].pid);
          	write(tableauDeTubes[2][1], tableauDeJoueur, nbJoueur*sizeof(struct Joueur));
          	
         }
       }
       if(getpid()==tableauDeJoueur[3].pid){
         read(tableauDeTubes2[3][0], &pidJoueurCourant, sizeof(pid_t));
         if(getpid()==pidJoueurCourant){
            lance=de(lance);
            printf("Lance= %d\n",lance);
            if(lance==6){
              pidJoueurSuivant=tableauDeJoueur[3].pid;
            }else{
              pidJoueurSuivant=tableauDeJoueur[0].pid;
            }
          	avancerPion(0, lance, tableauDeJoueur,nbJoueur);
          	write(tableauDeTubes[3][1], tableauDeJoueur, nbJoueur*sizeof(struct Joueur));
            write(tableauDeTubes2[4][1], &pidJoueurSuivant, sizeof(pid_t));
            write(tableauDeTubes2[5][1], tableauDeJoueur, nbJoueur*sizeof(struct Joueur));
         }else{	
          	read(tableauDeTubes[2][0], tableauDeJoueur, nbJoueur*sizeof(struct Joueur));
          	etatPlateau(tableauDeJoueur, nbJoueur,tableauDeJoueur[3].pid);
          	write(tableauDeTubes[3][1], tableauDeJoueur, nbJoueur*sizeof(struct Joueur));
         }
       }if(getpid()==pidPere){
         read(tableauDeTubes2[4][0], &pidJoueurSuivant, sizeof(pid_t));
         read(tableauDeTubes2[3][0], tableauDeJoueur, nbJoueur*sizeof(struct Joueur));
         victoire(tableauDeJoueur,nbJoueur);
         write(tableauDeTubes2[0][1], &pidJoueurSuivant, sizeof(pid_t));
         write(tableauDeTubes2[1][1], &pidJoueurSuivant, sizeof(pid_t));
         write(tableauDeTubes2[2][1], &pidJoueurSuivant, sizeof(pid_t));
         write(tableauDeTubes2[3][1], &pidJoueurSuivant, sizeof(pid_t));
         
       }
     partieGagne=true;//on effacera ca d'ici ;c'est dans jouer qu'on doit modifier partieGagnee
    }
    }else{
      if(getpid()==pidPere){
       write(tableauDeTubes2[0][1], &pidJoueurSuivant, sizeof(pid_t));
       write(tableauDeTubes2[1][1], &pidJoueurSuivant, sizeof(pid_t));
      }
      while(!partieGagne){
       if(getpid()==tableauDeJoueur[0].pid){
          read(tableauDeTubes2[0][0], &pidJoueurCourant, sizeof(pid_t));
          if(getpid()==pidJoueurCourant){
   	        lance=de(lance);
            printf("Lance= %d\n",lance);
            if(lance==6){
              pidJoueurSuivant=tableauDeJoueur[0].pid;
            }else{
              pidJoueurSuivant=tableauDeJoueur[1].pid;
            }
          	avancerPion(0, lance, tableauDeJoueur,nbJoueur);
            write(tableauDeTubes[0][1], tableauDeJoueur, nbJoueur*sizeof(struct Joueur));
            write(tableauDeTubes2[2][1], &pidJoueurSuivant, sizeof(pid_t));
            write(tableauDeTubes2[3][1], tableauDeJoueur, nbJoueur*sizeof(struct Joueur));
          }else{
          	read(tableauDeTubes[1][0], tableauDeJoueur, nbJoueur*sizeof(struct Joueur));
          	etatPlateau(tableauDeJoueur, nbJoueur,tableauDeJoueur[0].pid);
          	write(tableauDeTubes[0][1], tableauDeJoueur, nbJoueur*sizeof(struct Joueur));
          }
       }
       if(getpid()==tableauDeJoueur[1].pid){
         read(tableauDeTubes2[1][0], &pidJoueurCourant, sizeof(pid_t));
         if(getpid()==pidJoueurCourant){
            lance=de(lance);
            printf("Lance= %d\n",lance);
            if(lance==6){
              pidJoueurSuivant=tableauDeJoueur[1].pid;
            }else{
              pidJoueurSuivant=tableauDeJoueur[2].pid;
            }
          	avancerPion(1, lance, tableauDeJoueur,nbJoueur);
          	write(tableauDeTubes[1][1], tableauDeJoueur, nbJoueur*sizeof(struct Joueur));
            write(tableauDeTubes2[2][1], &pidJoueurSuivant, sizeof(pid_t));
            write(tableauDeTubes2[3][1], tableauDeJoueur, nbJoueur*sizeof(struct Joueur));
         }else{
          	read(tableauDeTubes[0][0], tableauDeJoueur, nbJoueur*sizeof(struct Joueur));
          	etatPlateau(tableauDeJoueur, nbJoueur,tableauDeJoueur[1].pid);
          	write(tableauDeTubes[1][1], tableauDeJoueur, nbJoueur*sizeof(struct Joueur));
         }
       }
       if(getpid()==pidPere){
         read(tableauDeTubes2[2][0], &pidJoueurSuivant, sizeof(pid_t));
         read(tableauDeTubes2[3][0], tableauDeJoueur, nbJoueur*sizeof(struct Joueur));
         victoire(tableauDeJoueur,nbJoueur);
         write(tableauDeTubes2[0][1], &pidJoueurSuivant, sizeof(pid_t));
         write(tableauDeTubes2[1][1], &pidJoueurSuivant, sizeof(pid_t));
            
       }
     
      
    }
    
  }
}

/*------------------------------------------------------------------------------------------------------*/

int main(int argc, char *argv[]){

//verification du nombre d'argument et affectation du nombre de joueur
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
   printf("nbJoueur : %d \n",nbJoueur);
   struct Joueur *tableauDeJoueur= malloc(nbJoueur*sizeof(struct Joueur));//declaration et initialisation du tableau de joueur
   
   
   //declaration des tubes de communication
   int tableauDeTubes[nbJoueur][2];// communication interprocessus fils
   int tableauDeTubes2[nbJoueur+2][2];// communication pere-fils
   
   
   //pipe des tubes de communication interprocessus fils
   for(int i=0;i<nbJoueur;i++){
    if (pipe(tableauDeTubes[i]) != 0) {/* pipe */
 			 fprintf(stderr, "Erreur dans pipe \n"); 
 			 exit(-1);
   	}
   }
   
   //pipe des tubes de communication pere fils
   for(int i=0;i<nbJoueur;i++){
    if (pipe(tableauDeTubes2[i]) != 0) {/* pipe */
 			 fprintf(stderr, "Erreur dans pipe \n"); 
 			 exit(-1);
   	}
   }
   initPlateau(nbJoueur,tableauDeJoueur,tableauDeTubes2);
   jeu(nbJoueur,tableauDeJoueur,tableauDeTubes,tableauDeTubes2);
   
   
     
}
