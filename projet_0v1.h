/*un plateau est divisé en quatre zone et chaque zone a un certains nombre de cellule 
la structure position permet d'identifier de maniere unique chaque case du plateau
et nous permettra ainsi de reperer l'endroit ou se trouve un joueur;*/
struct{ /* data */
    int zone;
    int cellule
};
typedef struct Position Position;


/*la structure joueur permet de stocker les informations sur un joueur a savoir son pid et sa position*/
struct{ /* data */
    pid_t pid;
    Position* pos;
} Joueur;
typedef struct Joueur Joueur;


void creerfils();//fonction qui permet de creer un joueur


void initPlateau(int n);//fonction qui cree "n" joueur et initialise un plateau avec eux
