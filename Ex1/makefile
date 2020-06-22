LIBS1:= lib1.o random.o

Ex1.1 : Ex1.1.cpp random.h lib1.h ${LIBS1}
	g++ -Wall -o $@ $^

Ex1.2 :: Ex1.2.cpp random.h lib1.h ${LIBS1}
	g++ -Wall -o $@ $^

Ex1.3 :: Ex1.3.cpp random.h lib1.h ${LIBS1}
		g++ -Wall -o $@ $^

%.o: %.cpp %.h
	g++ -Wall -c -O3 $<

clean:
	rm Ex1.1
	rm Ex1.2
	rm Ex1.3
	rm *.o
