LIBS1:= lib1.o random.o 

Ex3.1 : Ex3.1.cpp random.h lib1.h ${LIBS1}
	g++ -Wall -o $@ $^

%.o: %.cpp %.h
	g++ -Wall -c -O3 $<

clean:
	rm Ex3.1
	rm *.o
