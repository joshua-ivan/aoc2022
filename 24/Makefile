aoc2022-24:
	gcc -Wall -c aoc2022-24.c

test: aoc2022-24
	gcc -Wall -c aoc2022-24-test.c
	gcc -o aoc2022-24-test aoc2022-24.o aoc2022-24-test.o
	./aoc2022-24-test

main: aoc2022-24
	gcc -Wall -c aoc2022-24-main.c
	gcc -o aoc2022-24-main aoc2022-24.o aoc2022-24-main.o
	./aoc2022-24-main

debug-test:
	gcc -g -o aoc2022-24-debug.o -Wall -c aoc2022-24.c
	gcc -g -o aoc2022-24-test-debug.o -Wall -c aoc2022-24-test.c
	gcc -g -o aoc2022-24-test-debug aoc2022-24-debug.o aoc2022-24-test-debug.o
	valgrind --leak-check=yes ./aoc2022-24-test-debug

debug-main:
	gcc -g -o aoc2022-24-debug.o -Wall -c aoc2022-24.c
	gcc -g -o aoc2022-24-main-debug.o -Wall -c aoc2022-24-main.c
	gcc -g -o aoc2022-24-main-debug aoc2022-24-debug.o aoc2022-24-main-debug.o
	valgrind --leak-check=yes ./aoc2022-24-main-debug

clean:
	rm -f ./*.o
	rm -f aoc2022-24-test
	rm -f aoc2022-24-main
	rm -f aoc2022-24-test-debug
	rm -f aoc2022-24-main-debug

