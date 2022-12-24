aoc2022-20:
	gcc -Wall -c aoc2022-20.c

test: aoc2022-20
	gcc -Wall -c aoc2022-20-test.c
	gcc -o aoc2022-20-test aoc2022-20.o aoc2022-20-test.o

main: aoc2022-20
	gcc -Wall -c aoc2022-20-main.c
	gcc -o aoc2022-20-main aoc2022-20.o aoc2022-20-main.o

debug:
	gcc -g -o aoc2022-20-debug.o -Wall -c aoc2022-20.c
	gcc -g -o aoc2022-20-test-debug.o -Wall -c aoc2022-20-test.c
	gcc -g -o aoc2022-20-main-debug.o -Wall -c aoc2022-20-main.c
	gcc -g -o aoc2022-20-test-debug blocks-debug.o aoc2022-20-debug.o aoc2022-20-test-debug.o
	gcc -g -o aoc2022-20-main-debug blocks-debug.o aoc2022-20-debug.o aoc2022-20-main-debug.o

clean:
	rm -f ./*.o
	rm -f aoc2022-20-test
	rm -f aoc2022-20-main
	rm -f aoc2022-20-test-debug
	rm -f aoc2022-20-main-debug

