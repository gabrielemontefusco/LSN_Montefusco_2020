LIBS:=  random.o function.o lib1.o

Ex10.1 : Ex10.1.cpp random.h function.h lib1.h ${LIBS}
	g++ -Wall -o $@ $^

%.o: %.cpp %.h
	g++ -Wall -c -O3 $<

clean:
	rm Ex10.1
	rm *.o
	rm *.0
