aoc2022-23:
	gcc -Wall -c aoc2022-23.c

test: aoc2022-23
	gcc -Wall -c aoc2022-23-test.c
	gcc -o aoc2022-23-test aoc2022-23.o aoc2022-23-test.o
	./aoc2022-23-test

main: aoc2022-23
	gcc -Wall -c aoc2022-23-main.c
	gcc -o aoc2022-23-main aoc2022-23.o aoc2022-23-main.o
	./aoc2022-23-main

debug-test:
	gcc -g -o aoc2022-23-debug.o -Wall -c aoc2022-23.c
	gcc -g -o aoc2022-23-test-debug.o -Wall -c aoc2022-23-test.c
	gcc -g -o aoc2022-23-test-debug aoc2022-23-debug.o aoc2022-23-test-debug.o
	valgrind --leak-check=yes ./aoc2022-23-test-debug

debug-main:
	gcc -g -o aoc2022-23-debug.o -Wall -c aoc2022-23.c
	gcc -g -o aoc2022-23-main-debug.o -Wall -c aoc2022-23-main.c
	gcc -g -o aoc2022-23-main-debug aoc2022-23-debug.o aoc2022-23-main-debug.o
	valgrind --leak-check=yes ./aoc2022-23-main-debug

clean:
	rm -f ./*.o
	rm -f aoc2022-23-test
	rm -f aoc2022-23-main
	rm -f aoc2022-23-test-debug
	rm -f aoc2022-23-main-debug

