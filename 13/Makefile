aoc2022-13:
	gcc -Wall -c aoc2022-13.c

test: aoc2022-13
	gcc -Wall -c aoc2022-13-test.c
	gcc -o aoc2022-13-test aoc2022-13.o aoc2022-13-test.o

main: aoc2022-13
	gcc -Wall -c aoc2022-13-main.c
	gcc -o aoc2022-13-main aoc2022-13.o aoc2022-13-main.o

debug:
	gcc -g -o aoc2022-13-debug.o -Wall -c aoc2022-13.c
	gcc -g -o aoc2022-13-test-debug.o -Wall -c aoc2022-13-test.c
	gcc -g -o aoc2022-13-main-debug.o -Wall -c aoc2022-13-main.c
	gcc -g -o aoc2022-13-test-debug aoc2022-13-debug.o aoc2022-13-test-debug.o
	gcc -g -o aoc2022-13-main-debug aoc2022-13-debug.o aoc2022-13-main-debug.o

clean:
	rm ./*.o
	rm aoc2022-13-test
	rm aoc2022-13-main
	rm aoc2022-13-test-debug
	rm aoc2022-13-main-debug

