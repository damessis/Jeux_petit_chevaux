//la structure position permet de stocker la position d'un joeur sur le plateau
//un plateau est divisé en quatre zone et chaque zone a un certains nombre de cellule
typedef struct
{ /* data */
    int zone;
    int cellule;
} position;

void creerfils();//fonction qui permet de creer un joueur
void initPlateau(int n);//fonction qui cree "n" joueur et initialise un plateau avec eux
