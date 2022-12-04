aoc2022-03:
	gcc -Wall -c aoc2022-03.c

test: aoc2022-03
	gcc -Wall -c aoc2022-03-test.c
	gcc -o aoc2022-03-test aoc2022-03.o aoc2022-03-test.o

main: aoc2022-03
	gcc -Wall -c aoc2022-03-main.c
	gcc -o aoc2022-03-main aoc2022-03.o aoc2022-03-main.o

clean:
	rm ./*.o
	rm aoc2022-03-test
	rm aoc2022-03-main

