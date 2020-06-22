LIBS1:= lib1.o random.o integral.o
LIBS2:= lib1.o random.o

Ex2.1 : Ex2.1.cpp random.h lib1.h integral.h ${LIBS1}
	g++ -Wall -o $@ $^

Ex2.2 :: Ex2.2.cpp random.h lib1.h ${LIBS2}
	g++ -Wall -o $@ $^

%.o: %.cpp %.h
	g++ -Wall -c -O3 $<

clean:
	rm Ex2.1
	rm *.o
