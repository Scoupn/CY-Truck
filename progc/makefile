all: exec

hello.o: hello.c
	gcc -o hello.o -c hello.c

autre.o: autre.c
	gcc -o autre.o -c autre.c

arbre.o: arbre.c autre.h
	gcc -o arbre.o -c arbre.c


exec: hello.o arbre.o autre.o
	gcc hello.o arbre.o autre.o -o exec

clean:
	rm -f *.o
	rm -f exec

