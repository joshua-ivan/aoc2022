aoc2022-07:
	gcc -Wall -c aoc2022-07.c

test: aoc2022-07
	gcc -Wall -c aoc2022-07-test.c
	gcc -o aoc2022-07-test aoc2022-07.o aoc2022-07-test.o

main: aoc2022-07
	gcc -Wall -c aoc2022-07-main.c
	gcc -o aoc2022-07-main aoc2022-07.o aoc2022-07-main.o

debug:
	gcc -g -o aoc2022-07-debug.o -Wall -c aoc2022-07.c
	gcc -g -o aoc2022-07-test-debug.o -Wall -c aoc2022-07-test.c
	gcc -g -o aoc2022-07-main-debug.o -Wall -c aoc2022-07-main.c
	gcc -g -o aoc2022-07-test-debug aoc2022-07-debug.o aoc2022-07-test-debug.o
	gcc -g -o aoc2022-07-main-debug aoc2022-07-debug.o aoc2022-07-main-debug.o

clean:
	rm ./*.o
	rm aoc2022-07-test
	rm aoc2022-07-test-debug
	rm aoc2022-07-main
	rm aoc2022-07-main-debug

