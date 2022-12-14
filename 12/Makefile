aoc2022-12:
	gcc -Wall -c aoc2022-12.c

test: aoc2022-12
	gcc -Wall -c aoc2022-12-test.c
	gcc -o aoc2022-12-test aoc2022-12.o aoc2022-12-test.o

main: aoc2022-12
	gcc -Wall -c aoc2022-12-main.c
	gcc -o aoc2022-12-main aoc2022-12.o aoc2022-12-main.o

debug:
	gcc -g -o aoc2022-12-debug.o -Wall -c aoc2022-12.c
	gcc -g -o aoc2022-12-test-debug.o -Wall -c aoc2022-12-test.c
	gcc -g -o aoc2022-12-main-debug.o -Wall -c aoc2022-12-main.c
	gcc -g -o aoc2022-12-test-debug aoc2022-12-debug.o aoc2022-12-test-debug.o
	gcc -g -o aoc2022-12-main-debug aoc2022-12-debug.o aoc2022-12-main-debug.o

clean:
	rm ./*.o
	rm aoc2022-12-test
	rm aoc2022-12-main
	rm aoc2022-12-test-debug
	rm aoc2022-12-main-debug

