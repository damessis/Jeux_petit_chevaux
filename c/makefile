all: projet

projet: projet.o
	gcc projet.o -o projet

projet_1: projet_1.o
	gcc projet_1.o -o projet_1

projet_0: projet_0.o
	gcc projet_0.o -o projet_0

projet.o: projet.c 
	gcc -c projet.c

projet_1.o: projet_1.c
	gcc -c projet_1.c

projet_0.o: projet_0.c
	gcc -c projet_0.c

clean :
	@echo "On efface les fichiers objets"
	-rm *.o

