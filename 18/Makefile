aoc2022-18:
	gcc -Wall -c aoc2022-18.c

test: aoc2022-18
	gcc -Wall -c aoc2022-18-test.c
	gcc -o aoc2022-18-test aoc2022-18.o aoc2022-18-test.o

main: aoc2022-18
	gcc -Wall -c aoc2022-18-main.c
	gcc -o aoc2022-18-main aoc2022-18.o aoc2022-18-main.o

debug:
	gcc -g -o aoc2022-18-debug.o -Wall -c aoc2022-18.c
	gcc -g -o aoc2022-18-test-debug.o -Wall -c aoc2022-18-test.c
	gcc -g -o aoc2022-18-main-debug.o -Wall -c aoc2022-18-main.c
	gcc -g -o aoc2022-18-test-debug blocks-debug.o aoc2022-18-debug.o aoc2022-18-test-debug.o
	gcc -g -o aoc2022-18-main-debug blocks-debug.o aoc2022-18-debug.o aoc2022-18-main-debug.o

clean:
	rm ./*.o
	rm aoc2022-18-test
	rm aoc2022-18-main
	rm aoc2022-18-test-debug
	rm aoc2022-18-main-debug

