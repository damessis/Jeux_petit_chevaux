#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {

    

    switch (fork())
    {
    case -1:
        fprintf(stderr, "Erreur du premier fork\n");
        exit(-1);
    case 0:
      printf("pid du premier fils : %d\n", getpid());
      exit(0);
    default:
        printf("pid du pere lors de la creation du premier fils : %d\n", getppid());
        switch (fork())
        {
        case -1:
            fprintf(stderr, "Erreur du deuxieme fork\n");
            exit(-1);
        case 0:
            printf("pid du deuxieme fils : %d\n", getpid());
            exit(0);
        default:
            printf("pid du pere lors de la creation du deuxieme fils : %d\n", getppid());
            switch (fork())
            {
            case -1:
                fprintf(stderr, "Erreur du troisieme fork\n");
                exit(-1);
            case 0:
                printf("pid du troisieme fils : %d\n", getpid());
                exit(0);
            default:
                printf("pid du pere lors de la creation du troisieme fils : %d\n", getppid());
                switch (fork())
                {
                case -1:
                    fprintf(stderr, "Erreur du quatrieme fork\n");
                    exit(-1);
                case 0:
                    printf("pid du quatrieme fils : %d\n", getpid());
                    exit(0);
                default:
                    printf("pid du pere lors de la creation du quatrieme fils : %d\n", getppid());
                }
                wait(NULL);
            }
        }
    }
}