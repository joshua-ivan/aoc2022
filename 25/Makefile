aoc2022-25:
	gcc -Wall -c aoc2022-25.c

test: aoc2022-25
	gcc -Wall -c aoc2022-25-test.c
	gcc -o aoc2022-25-test aoc2022-25.o aoc2022-25-test.o
	./aoc2022-25-test

main: aoc2022-25
	gcc -Wall -c aoc2022-25-main.c
	gcc -o aoc2022-25-main aoc2022-25.o aoc2022-25-main.o
	./aoc2022-25-main

debug-test:
	gcc -g -o aoc2022-25-debug.o -Wall -c aoc2022-25.c
	gcc -g -o aoc2022-25-test-debug.o -Wall -c aoc2022-25-test.c
	gcc -g -o aoc2022-25-test-debug aoc2022-25-debug.o aoc2022-25-test-debug.o
	valgrind --leak-check=yes ./aoc2022-25-test-debug

debug-main:
	gcc -g -o aoc2022-25-debug.o -Wall -c aoc2022-25.c
	gcc -g -o aoc2022-25-main-debug.o -Wall -c aoc2022-25-main.c
	gcc -g -o aoc2022-25-main-debug aoc2022-25-debug.o aoc2022-25-main-debug.o
	valgrind --leak-check=yes ./aoc2022-25-main-debug

clean:
	rm -f ./*.o
	rm -f aoc2022-25-test
	rm -f aoc2022-25-main
	rm -f aoc2022-25-test-debug
	rm -f aoc2022-25-main-debug
