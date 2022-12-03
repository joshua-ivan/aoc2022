aoc2022-01: 
	gcc -Wall -c aoc2022-01.c

test: aoc2022-01
	gcc -Wall -c aoc2022-01-test.c
	gcc -o aoc2022-01-test aoc2022-01.o aoc2022-01-test.o

main: aoc2022-01
	gcc -Wall -c aoc2022-01-main.c
	gcc -o aoc2022-01-main aoc2022-01.o aoc2022-01-main.o

clean:
	rm ./*.o
	rm aoc2022-01-test 
	rm aoc2022-01-main 

