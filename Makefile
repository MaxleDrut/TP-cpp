all: Main

Main : Main.o TrajetSimple.o ListeTrajets.o Maillon.o TrajetCompo.o Catalogue.o
	g++ -o Main Main.o TrajetSimple.o ListeTrajets.o Maillon.o TrajetCompo.o Catalogue.o

Main.o : Main.cpp
	g++ -c Main.cpp

TrajetSimple.o: TrajetSimple.cpp
	g++ -c TrajetSimple.cpp

ListeTrajets.o : ListeTrajets.cpp
	g++ -c ListeTrajets.cpp

Maillon.o : Maillon.cpp
	g++ -c Maillon.cpp

TrajetCompo.o : TrajetCompo.cpp
	g++ -c TrajetCompo.cpp

Catalogue.o : Catalogue.cpp
	g++ -c Catalogue.cpp

clear:
	rm *.o Main *.h.gch
