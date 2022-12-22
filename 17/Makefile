aoc2022-17:
	gcc -Wall -c blocks.c aoc2022-17.c

test: aoc2022-17
	gcc -Wall -c aoc2022-17-test.c
	gcc -o aoc2022-17-test blocks.o aoc2022-17.o aoc2022-17-test.o

main: aoc2022-17
	gcc -Wall -c aoc2022-17-main.c
	gcc -o aoc2022-17-main blocks.o aoc2022-17.o aoc2022-17-main.o

debug:
	gcc -g -o blocks-debug.o -Wall -c blocks.c
	gcc -g -o aoc2022-17-debug.o -Wall -c aoc2022-17.c
	gcc -g -o aoc2022-17-test-debug.o -Wall -c aoc2022-17-test.c
	gcc -g -o aoc2022-17-main-debug.o -Wall -c aoc2022-17-main.c
	gcc -g -o aoc2022-17-test-debug blocks-debug.o aoc2022-17-debug.o aoc2022-17-test-debug.o
	gcc -g -o aoc2022-17-main-debug blocks-debug.o aoc2022-17-debug.o aoc2022-17-main-debug.o

clean:
	rm ./*.o
	rm aoc2022-17-test
	rm aoc2022-17-main
	rm aoc2022-17-test-debug
	rm aoc2022-17-main-debug

