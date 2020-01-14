server: mainserver.o networking.o storage.o
	gcc -o server mainserver.o networking.o storage.o

client: client.o networking.o
	gcc -o client client.o networking.o

client.o: client.c networking.h
	gcc -c client.c

mainserver.o: mainserver.c networking.h
	gcc -c mainserver.c

networking.o: networking.c networking.h
	gcc -c networking.c

storage.o: notes.c
	gcc -c notes.c

clean:
	rm *.o
	rm *~
