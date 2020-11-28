all: Main

Main : Main.o TrajetSimple.o ListeTrajets.o Maillon.o
	g++ -o Main Main.o TrajetSimple.o ListeTrajets.o Maillon.o

Main.o : Main.cpp
	g++ -c Main.cpp

TrajetSimple.o: TrajetSimple.cpp
	g++ -c TrajetSimple.cpp

ListeTrajets.o : ListeTrajets.cpp
	g++ -c ListeTrajets.cpp

Maillon.o : Maillon.cpp
	g++ -c Maillon.cpp

clear:
	rm *.o Main *.h.gch
