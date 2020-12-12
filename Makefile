CFLAGS =  -ansi -pedantic -Wall -std=c++11
all: Main

Main : Main.o TrajetSimple.o ListeTrajets.o Maillon.o TrajetCompo.o Catalogue.o
	g++ -o Main Main.o TrajetSimple.o ListeTrajets.o Maillon.o TrajetCompo.o Catalogue.o

Test : Test.o TrajetSimple.o ListeTrajets.o Maillon.o TrajetCompo.o Catalogue.o
	g++ -o Test Test.o TrajetSimple.o ListeTrajets.o Maillon.o TrajetCompo.o Catalogue.o

Test.o : Test.cpp
	g++ -c Test.cpp

Main.o : Main.cpp
	g++ -c Main.cpp $(CFLAGS)

TrajetSimple.o: TrajetSimple.cpp
	g++ -c TrajetSimple.cpp $(CFLAGS)

ListeTrajets.o : ListeTrajets.cpp
	g++ -c ListeTrajets.cpp $(CFLAGS)

Maillon.o : Maillon.cpp
	g++ -c Maillon.cpp $(CFLAGS)

TrajetCompo.o : TrajetCompo.cpp
	g++ -c TrajetCompo.cpp $(CFLAGS)

Catalogue.o : Catalogue.cpp
	g++ -c Catalogue.cpp $(CFLAGS)

clear:
	rm *.o Main *.h.gch
