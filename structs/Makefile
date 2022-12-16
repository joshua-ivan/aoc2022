coords:
	gcc -Wall -c coords.c

test: coords
	gcc -Wall -c coords-test.c
	gcc -o coords-test coords.o coords-test.o

clean:
	rm ./*.o
	rm coords-test

