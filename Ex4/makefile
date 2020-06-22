Ex4.1 : Ex4.1.cpp MolDyn_NVE.h
	g++ -Wall -o $@ $^

Ex4.2 :: Ex4.2.cpp MolDyn_NVE.h
	g++ -Wall -o $@ $^

Ex4.3 :: Ex4.3.cpp MolDyn_NVE.h
		g++ -Wall -o $@ $^

%.o: %.cpp %.h
	g++ -Wall -c -O3 $<

clean:
	rm Ex4.1
	rm Ex4.2
	rm Ex4.3
	rm *.o
