#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

typedef struct
{
    /* data */
    int zone;
    int case;
}position;

void jouer(){

}

int main() 
{
    int f01[2];
    int f12[2];
    int f23[2];
    int f34[2];
    int fp[2];
    position pj1;
    position pj2;
    position pj3;
    position pj4;
    switch (fork())
    {
    case -1:
        fprintf(stderr, "Erreur du premier fork\n");
        exit(-1);
    case 0:

    default:
        switch (fork())
        {
        case -1:
            fprintf(stderr, "Erreur du deuxieme fork\n");
            exit(-1);
        case 0:
            fprintf(stderr, "Erreur de fork\n");
            exit(-1);

        default:
        }
        switch (fork())
            {
            case -1:
                fprintf(stderr, "Erreur du troisieme fork\n");
                exit(-1);
            case 0:
                fprintf(stderr, "Erreur de fork\n");
                exit(-1);

            default:
        }
        switch (fork())
                {
                case -1:
                    fprintf(stderr, "Erreur du quatrieme fork\n");
                    exit(-1);
                case 0:
                    fprintf(stderr, "Erreur de fork\n");
                    exit(-1);

                default:
        }
        wait(NULL)
    }
}