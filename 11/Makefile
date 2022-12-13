aoc2022-11:
	gcc -Wall -c aoc2022-11.c

test: aoc2022-11
	gcc -Wall -c aoc2022-11-test.c
	gcc -o aoc2022-11-test aoc2022-11.o aoc2022-11-test.o

main: aoc2022-11
	gcc -Wall -c aoc2022-11-main.c
	gcc -o aoc2022-11-main aoc2022-11.o aoc2022-11-main.o

debug:
	gcc -g -o aoc2022-11-debug.o -Wall -c aoc2022-11.c
	gcc -g -o aoc2022-11-test-debug.o -Wall -c aoc2022-11-test.c
	gcc -g -o aoc2022-11-main-debug.o -Wall -c aoc2022-11-main.c
	gcc -g -o aoc2022-11-test-debug aoc2022-11-debug.o aoc2022-11-test-debug.o
	gcc -g -o aoc2022-11-main-debug aoc2022-11-debug.o aoc2022-11-main-debug.o

clean:
	rm ./*.o
	rm aoc2022-11-test
	rm aoc2022-11-main
	rm aoc2022-11-test-debug
	rm aoc2022-11-main-debug

