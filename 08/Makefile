aoc2022-08:
	gcc -Wall -c aoc2022-08.c

test: aoc2022-08
	gcc -Wall -c aoc2022-08-test.c
	gcc -o aoc2022-08-test aoc2022-08.o aoc2022-08-test.o

main: aoc2022-08
	gcc -Wall -c aoc2022-08-main.c
	gcc -o aoc2022-08-main aoc2022-08.o aoc2022-08-main.o

debug:
	gcc -g -o aoc2022-08-debug.o -Wall -c aoc2022-08.c
	gcc -g -o aoc2022-08-test-debug.o -Wall -c aoc2022-08-test.c
	gcc -g -o aoc2022-08-main-debug.o -Wall -c aoc2022-08-main.c
	gcc -g -o aoc2022-08-test-debug aoc2022-08-debug.o aoc2022-08-test-debug.o
	gcc -g -o aoc2022-08-main-debug aoc2022-08-debug.o aoc2022-08-main-debug.o

clean:
	rm ./*.o
	rm aoc2022-08-test
	rm aoc2022-08-main
	rm aoc2022-08-test-debug
	rm aoc2022-08-main-debug

