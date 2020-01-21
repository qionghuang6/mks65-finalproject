server: mainserver.o networking.o parser.o
	gcc -o server mainserver.o networking.o parser.o

client: client.o networking.o play.o
	gcc -o client client.o networking.o play.o

tst: test.o parser.o
	gcc -o tst test.o parser.o

client.o: client.c networking.h
	gcc -c client.c

mainserver.o: mainserver.c networking.h
	gcc -c mainserver.c

networking.o: networking.c networking.h
	gcc -c networking.c

play.o: play.c play.h
	gcc -c play.c

test.o: test.c
	gcc -c test.c

parser.o: parser.c parser.h
	gcc -c parser.c

clean:
	rm *.o
	rm *~
