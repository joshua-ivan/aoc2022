aoc2022-02: 
	gcc -Wall -c aoc2022-02.c

test: aoc2022-02
	gcc -Wall -c aoc2022-02-test.c
	gcc -o aoc2022-02-test aoc2022-02.o aoc2022-02-test.o

main: aoc2022-02
	gcc -Wall -c aoc2022-02-main.c
	gcc -o aoc2022-02-main aoc2022-02.o aoc2022-02-main.o

clean:
	rm ./*.o
	rm aoc2022-02-test 
	rm aoc2022-02-main 

