server: mainserver.o networking.o notes.o parser.o
	gcc -o server mainserver.o networking.o notes.o parser.o

client: client.o networking.o
	gcc -o client client.o networking.o

client.o: client.c networking.h
	gcc -c client.c

mainserver.o: mainserver.c networking.h
	gcc -c mainserver.c

networking.o: networking.c networking.h
	gcc -c networking.c

notes.o: notes.c
	gcc -c notes.c

parser.o: parser.c
	gcc -c parser.c

clean:
	rm *.o
	rm *~
