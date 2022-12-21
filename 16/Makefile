aoc2022-16:
	gcc -Wall -c aoc2022-16.c

test: aoc2022-16
	gcc -Wall -c aoc2022-16-test.c
	gcc -o aoc2022-16-test aoc2022-16.o aoc2022-16-test.o

main: aoc2022-16
	gcc -Wall -c aoc2022-16-main.c
	gcc -o aoc2022-16-main aoc2022-16.o aoc2022-16-main.o

debug:
	gcc -g -o aoc2022-16-debug.o -Wall -c aoc2022-16.c
	gcc -g -o aoc2022-16-test-debug.o -Wall -c aoc2022-16-test.c
	gcc -g -o aoc2022-16-main-debug.o -Wall -c aoc2022-16-main.c
	gcc -g -o aoc2022-16-test-debug aoc2022-16-debug.o aoc2022-16-test-debug.o
	gcc -g -o aoc2022-16-main-debug aoc2022-16-debug.o aoc2022-16-main-debug.o

clean:
	rm ./*.o
	rm aoc2022-16-test
	rm aoc2022-16-main
	rm aoc2022-16-test-debug
	rm aoc2022-16-main-debug

