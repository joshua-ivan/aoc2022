aoc2022-21:
	gcc -Wall -c aoc2022-21.c

test: aoc2022-21
	gcc -Wall -c aoc2022-21-test.c
	gcc -o aoc2022-21-test aoc2022-21.o aoc2022-21-test.o

main: aoc2022-21
	gcc -Wall -c aoc2022-21-main.c
	gcc -o aoc2022-21-main aoc2022-21.o aoc2022-21-main.o

debug:
	gcc -g -o aoc2022-21-debug.o -Wall -c aoc2022-21.c
	gcc -g -o aoc2022-21-test-debug.o -Wall -c aoc2022-21-test.c
	gcc -g -o aoc2022-21-main-debug.o -Wall -c aoc2022-21-main.c
	gcc -g -o aoc2022-21-test-debug aoc2022-21-debug.o aoc2022-21-test-debug.o
	gcc -g -o aoc2022-21-main-debug aoc2022-21-debug.o aoc2022-21-main-debug.o

clean:
	rm -f ./*.o
	rm -f aoc2022-21-test
	rm -f aoc2022-21-main
	rm -f aoc2022-21-test-debug
	rm -f aoc2022-21-main-debug

