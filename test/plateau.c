#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

/* Déclaration des tubes */
int tube01[2];//tube de communication entre le joueur 0 et le joueur 1
int tube12[2];//tube de communication entre le joueur 1 et le joueur 2
int tube23[2];//tube de communication entre le joueur 2 et le joueur 3
int tube30[2];//tube de communication entre le joueur 0 et le joueur 1
int tubeP[2];//tube de communication avec le processus père

/* Déclaration des positions des 2 pions de chaque joueur */
struct PositionPion p1j0;//position du premier pion du joueur 0
struct PositionPion p2j0;//position du deuxieme pion du joueur 0
struct PositionPion p1j1;//position du premier pion du joueur 1
struct PositionPion p2j1;//position du deuxieme pion du joueur 1
struct PositionPion p1j2;//position du premier pion du joueur 2
struct PositionPion p2j2;//position du deuxieme pion du joueur 2
struct PositionPion p1j3;//position du premier pion du joueur 3
struct PositionPion p2j3;//position du deuxieme pion du joueur 3

/* Déclarations des pid des processus fils */
int pidj0;
int pidj1;
int pidj2;
int pidj3;

/* Structure PositionPion avec comme attribut zone le numéro de la zone du joueur et cellule le numéro de la cellule dans la zone */
struct PositionPion {
    int zone;
    int cellule;
};


/* Création du plateau */
void plateau() {
    /* Définition des positions par défault */
    p1j0.zone = 0; // pion dans la zone du joueur
    p1j0.cellule = -1; // -1 est le cas où le pion est encore dans l'écurie
    p2j0.zone = 0;
    p2j0.cellule = -1;

    p1j1.zone = 1;
    p1j1.cellule = -1;
    p2j1.zone = 1;
    p2j1.cellule = -1;

    p1j2.zone = 2;
    p1j2.cellule = -1;
    p2j2.zone = 2;
    p2j2.cellule = -1;

    p1j3.zone = 3;
    p1j3.cellule = -1;
    p2j3.zone = 3;
    p2j3.cellule = -1;


    /* Création du processus fils joueur 0 + connections aux tubes*/
    switch (fork()) {
    case -1:
      fprintf(stderr, "Erreur du premier fork\n");
      exit(-1);
    case 0:
      pidj0 = getpid();
      printf("processus joueur 0 : %i\n", pidj0);
      /* Connection des tubes du processus joueur 0 + fermeture des portes qui servent à rien */
      close(1);
      dup(tube01[1]);

      close(0);
      dup(tube30[0]);

      close(tube01[0]);
      close(tube01[1]);
      close(tube12[0]);
      close(tube12[1]);
      close(tube23[0]);
      close(tube23[1]);
      close(tube30[0]);
      close(tube30[1]);
      close(tubeP[0]);
      //close(tubeP[1]) peut-être
    default:
        /* Création du processus fils joueur 1 + connections aux tubes*/
        switch (fork()) {
        case -1:
            fprintf(stderr, "Erreur du deuxième fork\n");
            exit(-1);
        case 0:
            pidj1 = getpid();
            printf("processus joueur 1 : %i\n", pidj1);
            /* Connection des tubes du processus joueur 1 + fermeture des portes qui servent à rien */
            close(1);
            dup(tube12[1]);

            close(0);
            dup(tube01[0]);

            close(tube01[0]);
            close(tube01[1]);
            close(tube12[0]);
            close(tube12[1]);
            close(tube23[0]);
            close(tube23[1]);
            close(tube30[0]);
            close(tube30[1]);
            close(tubeP[0]);
            //close(tubeP[1]) peut-être
        default:
            /* Création du processus fils joueur 2 + connections aux tubes*/
            switch (fork()) {
            case -1:
                fprintf(stderr, "Erreur du troisième fork\n");
                exit(-1);
            case 0:
                pidj2 = getpid();
                printf("processus joueur 2 : %i\n", pidj2);
                /* Connection des tubes du processus joueur 2 + fermeture des portes qui servent à rien */
                close(1);
                dup(tube23[1]);

                close(0);
                dup(tube12[0]);

                close(tube01[0]);
                close(tube01[1]);
                close(tube12[0]);
                close(tube12[1]);
                close(tube23[0]);
                close(tube23[1]);
                close(tube30[0]);
                close(tube30[1]);
                close(tubeP[0]);
                //close(tubeP[1]) peut-être
            default:
                /* Création du processus fils joueur 4 + connections aux tubes*/
                switch (fork()) {
                case -1:
                    fprintf(stderr, "Erreur du quatrième fork\n");
                    exit(-1);
                case 0:
                    pidj3 = getpid();
                    printf("processus joueur 3 : %i\n", pidj3);
                    /* Connection des tubes du processus joueur 3 + fermeture des portes qui servent à rien */
                    close(1);
                    dup(tube30[1]);

                    close(0);
                    dup(tube23[0]);

                    close(tube01[0]);
                    close(tube01[1]);
                    close(tube12[0]);
                    close(tube12[1]);
                    close(tube23[0]);
                    close(tube23[1]);
                    close(tube30[0]);
                    close(tube30[1]);
                    close(tubeP[0]);
                    //close(tubeP[1]) peut-être
                default:
                    close(0);
                    dup(tubeP[0]);

                    close(tube01[0]);
                    close(tube01[1]);
                    close(tube12[0]);
                    close(tube12[1]);
                    close(tube23[0]);
                    close(tube23[1]);
                    close(tube30[0]);
                    close(tube30[1]);
                    close(tubeP[0]);
                    close(tubeP[1]);
                }
            }
        }
    }
}