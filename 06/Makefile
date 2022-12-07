aoc2022-06:
	gcc -Wall -c aoc2022-06.c

test: aoc2022-06
	gcc -Wall -c aoc2022-06-test.c
	gcc -o aoc2022-06-test aoc2022-06.o aoc2022-06-test.o

main: aoc2022-06
	gcc -Wall -c aoc2022-06-main.c
	gcc -o aoc2022-06-main aoc2022-06.o aoc2022-06-main.o

clean:
	rm ./*.o
	rm aoc2022-06-test
	rm aoc2022-06-main

