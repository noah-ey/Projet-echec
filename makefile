echec : main.o echiquier.o joueur.o action.o conditions_echec.o
	gcc main.o echiquier.o joueur.o action.o conditions_echec.o -o echec

main.o : main.c declarations.h
	gcc -c main.c

echiquier.o : echiquier.c declarations.h
	gcc -c echiquier.c
	
joueur.o : joueur.c declarations.h
	gcc -c joueur.c

action.o : action.c declarations.h
	gcc -c action.c

conditions_echec.o : conditions_echec.c declarations.h
	gcc -c conditions_echec.c

clean :
	rm -f *.o echec
