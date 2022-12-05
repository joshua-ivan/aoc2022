aoc2022-05:
	gcc -Wall -c aoc2022-05.c

test: aoc2022-05
	gcc -Wall -c aoc2022-05-test.c
	gcc -o aoc2022-05-test aoc2022-05.o aoc2022-05-test.o

main: aoc2022-05
	gcc -Wall -c aoc2022-05-main.c
	gcc -o aoc2022-05-main aoc2022-05.o aoc2022-05-main.o

clean:
	rm ./*.o
	rm aoc2022-05-test
	rm aoc2022-05-main

