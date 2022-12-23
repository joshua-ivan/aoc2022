aoc2022-19:
	gcc -Wall -c aoc2022-19.c

test: aoc2022-19
	gcc -Wall -c aoc2022-19-test.c
	gcc -o aoc2022-19-test aoc2022-19.o aoc2022-19-test.o

main: aoc2022-19
	gcc -Wall -c aoc2022-19-main.c
	gcc -o aoc2022-19-main aoc2022-19.o aoc2022-19-main.o

debug:
	gcc -g -o aoc2022-19-debug.o -Wall -c aoc2022-19.c
	gcc -g -o aoc2022-19-test-debug.o -Wall -c aoc2022-19-test.c
	gcc -g -o aoc2022-19-main-debug.o -Wall -c aoc2022-19-main.c
	gcc -g -o aoc2022-19-test-debug blocks-debug.o aoc2022-19-debug.o aoc2022-19-test-debug.o
	gcc -g -o aoc2022-19-main-debug blocks-debug.o aoc2022-19-debug.o aoc2022-19-main-debug.o

clean:
	rm -f ./*.o
	rm -f aoc2022-19-test
	rm -f aoc2022-19-main
	rm -f aoc2022-19-test-debug
	rm -f aoc2022-19-main-debug

