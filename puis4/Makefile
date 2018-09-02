all: damier.o jeu.o
	gcc damier.o jeu.o -o puissance4
	./puissance4

damier.o: damier.c damier.h
	gcc -c damier.c -o damier.o

jeu.o: jeu.c 
	gcc -c jeu.c -o jeu.o

clean:
	rm *.o puissance4
