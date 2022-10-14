all: main

main: plateau.o main.o
        gcc plateau.o main.o -o main

main.o: main.c
        gcc -c main.c

plateau.o: plateau.c
        gcc -c plateau.c

clean :
        @echo "On efface les fichiers objets"
        -rm *.o