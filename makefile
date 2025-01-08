echec : main.o jeu.o
	gcc main.o jeu.o -o echec

main.o : main.c declarations.h
	gcc -c main.c

jeu.o : jeu.c declarations.h
	gcc -c jeu.c

clean :
	rm -f *.o echec
