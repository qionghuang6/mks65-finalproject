server: mainserver.o networking.o parser.o
	gcc -o server mainserver.o networking.o parser.o

client: client.o networking.o
	gcc -o client client.o networking.o

tst: test.o parser.o
	gcc -o tst test.o parser.o

client.o: client.c networking.h
	gcc -c client.c

mainserver.o: mainserver.c networking.h
	gcc -c mainserver.c

networking.o: networking.c networking.h
	gcc -c networking.c

test.o: test.c
	gcc -c test.c

parser.o: parser.c
	gcc -c parser.c

clean:
	rm *.o
	rm *~
