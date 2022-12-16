aoc2022-15:
	gcc -Wall -c aoc2022-15.c

test: aoc2022-15
	gcc -Wall -c aoc2022-15-test.c
	gcc -o aoc2022-15-test ../structs/coords.o aoc2022-15.o aoc2022-15-test.o

main: aoc2022-15
	gcc -Wall -c aoc2022-15-main.c
	gcc -o aoc2022-15-main ../structs/coords.o aoc2022-15.o aoc2022-15-main.o

debug:
	gcc -g -o aoc2022-15-debug.o -Wall -c aoc2022-15.c
	gcc -g -o aoc2022-15-test-debug.o -Wall -c aoc2022-15-test.c
	gcc -g -o aoc2022-15-main-debug.o -Wall -c aoc2022-15-main.c
	gcc -g -o aoc2022-15-test-debug aoc2022-15-debug.o aoc2022-15-test-debug.o
	gcc -g -o aoc2022-15-main-debug aoc2022-15-debug.o aoc2022-15-main-debug.o

clean:
	rm ./*.o
	rm aoc2022-15-test
	rm aoc2022-15-main
	rm aoc2022-15-test-debug
	rm aoc2022-15-main-debug

