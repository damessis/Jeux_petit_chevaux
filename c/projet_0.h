/*un plateau est divisé en quatre zone et chaque zone a un certains nombre de cellule 
la structure position permet d'identifier de maniere unique chaque case du plateau
et nous permettra ainsi de reperer l'endroit ou se trouve un joueur;*/
#ifndef PROJET_0
#define PROJET_0

/*------------------------------------------------------------------------------------------------------------------*/
void creerfils(struct Joueur **tableauDeJoueur, int **tableauDeTubes, int n, int nbJoueur );//fonction qui permet de creer un joueur

/*------------------------------------------------------------------------------------------------------------------*/
void initPlateau(int n, int **tableauDeTubes,struct Joueur **tableauDeJoueur );//fonction qui cree "n" joueur et initialise un plateau avec eux

/*------------------------------------------------------------------------------------------------------------------*/
int **createTableDeTubes(int nbJoueur);//permet de stocker tous les tubes en fonction du nombre de joueur et de pouvoir y acceder par reference

/*------------------------------------------------------------------------------------------------------------------*/
void detruireLesTubes(int **tableauDeTubes);//cette fonction nous permettra de detruire tous les tubes une fois qu'on en aura plus besoin et ainsi eviter d'occuper inutilement de la memoire

/*------------------------------------------------------------------------------------------------------------------*/
struct Joueur **createTableDeJoueur(int nbJoueur);//cette fonction nous permet de stocker les informations de tous les joueur;

/*------------------------------------------------------------------------------------------------------------------*/
void detruireLesJoueur( struct Joueur **tableauDeJoueur);//cette fonction nous permet en fin de parti de nous debarasser des informatiosn sur les joueur en meme temps que nous les tuons;
#endif
