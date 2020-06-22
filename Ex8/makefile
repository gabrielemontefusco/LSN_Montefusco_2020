LIBS1:= lib1.o random.o Metropolis.o

Ex8.2.1 : Ex8.2.1.cpp random.h lib1.h Metropolis.h ${LIBS1}
	g++ -Wall -o $@ $^

Ex8.2.2 : Ex8.2.2.cpp random.h lib1.h Metropolis.h ${LIBS1}
	g++ -Wall -o $@ $^

%.o: %.cpp %.h
	g++ -Wall -c -O3 $<

clean:
	rm Ex8.2.1
	rm Ex8.2.2
	rm *.o
	rm *.0
