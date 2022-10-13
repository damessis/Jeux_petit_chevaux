#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
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

int main(){
  int n;
  n=4;
  for(int i=0;i<n;i++){
    creerfils();
  }
}