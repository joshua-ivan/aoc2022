aoc2022-09:
	gcc -Wall -c aoc2022-09.c

test: aoc2022-09
	gcc -Wall -c aoc2022-09-test.c
	gcc -o aoc2022-09-test aoc2022-09.o aoc2022-09-test.o

main: aoc2022-09
	gcc -Wall -c aoc2022-09-main.c
	gcc -o aoc2022-09-main aoc2022-09.o aoc2022-09-main.o

debug:
	gcc -g -o aoc2022-09-debug.o -Wall -c aoc2022-09.c
	gcc -g -o aoc2022-09-test-debug.o -Wall -c aoc2022-09-test.c
	gcc -g -o aoc2022-09-main-debug.o -Wall -c aoc2022-09-main.c
	gcc -g -o aoc2022-09-test-debug aoc2022-09-debug.o aoc2022-09-test-debug.o
	gcc -g -o aoc2022-09-main-debug aoc2022-09-debug.o aoc2022-09-main-debug.o

clean:
	rm ./*.o
	rm aoc2022-09-test
	rm aoc2022-09-main
	rm aoc2022-09-test-debug
	rm aoc2022-09-main-debug

