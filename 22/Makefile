aoc2022-22:
	gcc -Wall -c aoc2022-22.c

test: aoc2022-22
	gcc -Wall -c aoc2022-22-test.c
	gcc -o aoc2022-22-test aoc2022-22.o aoc2022-22-test.o

main: aoc2022-22
	gcc -Wall -c aoc2022-22-main.c
	gcc -o aoc2022-22-main aoc2022-22.o aoc2022-22-main.o

debug:
	gcc -g -o aoc2022-22-debug.o -Wall -c aoc2022-22.c
	gcc -g -o aoc2022-22-test-debug.o -Wall -c aoc2022-22-test.c
	gcc -g -o aoc2022-22-main-debug.o -Wall -c aoc2022-22-main.c
	gcc -g -o aoc2022-22-test-debug aoc2022-22-debug.o aoc2022-22-test-debug.o
	gcc -g -o aoc2022-22-main-debug aoc2022-22-debug.o aoc2022-22-main-debug.o

clean:
	rm -f ./*.o
	rm -f aoc2022-22-test
	rm -f aoc2022-22-main
	rm -f aoc2022-22-test-debug
	rm -f aoc2022-22-main-debug

