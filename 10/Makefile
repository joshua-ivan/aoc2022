aoc2022-10:
	gcc -Wall -c aoc2022-10.c

test: aoc2022-10
	gcc -Wall -c aoc2022-10-test.c
	gcc -o aoc2022-10-test aoc2022-10.o aoc2022-10-test.o

main: aoc2022-10
	gcc -Wall -c aoc2022-10-main.c
	gcc -o aoc2022-10-main aoc2022-10.o aoc2022-10-main.o

debug:
	gcc -g -o aoc2022-10-debug.o -Wall -c aoc2022-10.c
	gcc -g -o aoc2022-10-test-debug.o -Wall -c aoc2022-10-test.c
	gcc -g -o aoc2022-10-main-debug.o -Wall -c aoc2022-10-main.c
	gcc -g -o aoc2022-10-test-debug aoc2022-10-debug.o aoc2022-10-test-debug.o
	gcc -g -o aoc2022-10-main-debug aoc2022-10-debug.o aoc2022-10-main-debug.o

clean:
	rm ./*.o
	rm aoc2022-10-test
	rm aoc2022-10-main
	rm aoc2022-10-test-debug
	rm aoc2022-10-main-debug

