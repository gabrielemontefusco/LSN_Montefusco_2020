LIBS1:= lib1.o random.o Metropolis.o

Ex5 : Ex5.cpp random.h lib1.h Metropolis.h ${LIBS1}
	g++ -Wall -o $@ $^

%.o: %.cpp %.h
	g++ -Wall -c -O3 $<

clean:
	rm Ex5
	rm *.o
