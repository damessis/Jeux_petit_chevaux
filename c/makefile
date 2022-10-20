all:projet_1

projet_1:projet_1.o
	gcc projet_1.o -o projet_1

projet_1.o : projet_1.c projet_1.h
	gcc -c projet_1.c

clean :
	@echo "On efface les fichiers objets"
	-rm *.o
