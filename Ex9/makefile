LIBS:=  random.o population.o lib1.o

Ex9.1 : Ex9.1.cpp random.h population.h lib1.h ${LIBS}
	g++ -Wall -o $@ $^

%.o: %.cpp %.h
	g++ -Wall -c -O3 $<

clean:
	rm Ex9.1
	rm *.o
