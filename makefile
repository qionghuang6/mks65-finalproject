server: mainserver.o networking.o
	gcc -o server mainserver.o networking.o

client: client.o networking.o
	gcc -o client client.o networking.o

client.o: client.c networking.h
	gcc -c client.c

mainserver.o: mainserver.c networking.h
	gcc -c mainserver.c

networking.o: networking.c networking.h
	gcc -c networking.c

clean:
	rm *.o
	rm *~
