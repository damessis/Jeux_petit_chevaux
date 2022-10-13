#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "projet_0v1.h"

//fonction creerfils() qui permet de creer un joueur
void creerfils(){
  switch (fork())
    {
    case -1:
        fprintf(stderr, "Erreur du premier fork\n");
        exit(-1);
    case 0:
        printf("pid: %d   ppid: %d\n", getpid(), getppid() );
        exit(0);
    default:
      wait(NULL);
  }
}

//fonction initPlateau() qui permet de creer "n" joueur(s) et initialise un plateaux avec eux
void initPlateau(int n){
  for(int i=0;i<n;i++){
    creerfils();
  }
}
int main(){
  initPlateau(4);
}
