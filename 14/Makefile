aoc2022-14:
	gcc -Wall -c aoc2022-14.c

test: aoc2022-14
	gcc -Wall -c aoc2022-14-test.c
	gcc -o aoc2022-14-test ../structs/coords.o aoc2022-14.o aoc2022-14-test.o

main: aoc2022-14
	gcc -Wall -c aoc2022-14-main.c
	gcc -o aoc2022-14-main ../structs/coords.o aoc2022-14.o aoc2022-14-main.o

debug:
	gcc -g -o aoc2022-14-debug.o -Wall -c aoc2022-14.c
	gcc -g -o aoc2022-14-test-debug.o -Wall -c aoc2022-14-test.c
	gcc -g -o aoc2022-14-main-debug.o -Wall -c aoc2022-14-main.c
	gcc -g -o aoc2022-14-test-debug aoc2022-14-debug.o aoc2022-14-test-debug.o
	gcc -g -o aoc2022-14-main-debug aoc2022-14-debug.o aoc2022-14-main-debug.o

clean:
	rm ./*.o
	rm aoc2022-14-test
	rm aoc2022-14-main
	rm aoc2022-14-test-debug
	rm aoc2022-14-main-debug

