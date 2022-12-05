aoc2022-04:
	gcc -Wall -c aoc2022-04.c

test: aoc2022-04
	gcc -Wall -c aoc2022-04-test.c
	gcc -o aoc2022-04-test aoc2022-04.o aoc2022-04-test.o

main: aoc2022-04
	gcc -Wall -c aoc2022-04-main.c
	gcc -o aoc2022-04-main aoc2022-04.o aoc2022-04-main.o

clean:
	rm ./*.o
	rm aoc2022-04-test
	rm aoc2022-04-main

