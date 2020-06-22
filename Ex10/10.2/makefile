LIBS:=  random.o population.o lib1.o

Ex10.2 : Ex10.2.cpp random.h population.h lib1.h ${LIBS}
	mpicxx -Wall -o $@ $^

%.o: %.cpp %.h
	g++ -Wall -c -O3 $<

clean:
	rm Ex10.2
	rm *.o
	rm *.0
