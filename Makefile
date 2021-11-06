a.out: solution.o m1.o
	gcc m1.o solution.o -o solution

m1.o: m1.c m1.h
	gcc m1.c -c

solution.o: solution.c m1.h
	gcc solution.c -c

clean:
	rm -f m1.o solution.o solution
