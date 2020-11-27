all: Main

Main : Main.o TrajetSimple.o ListeTrajets.o
	g++ -o Main Main.o TrajetSimple.o ListeTrajets.o

Main.o : Main.cpp
	g++ -c Main.cpp

TrajetSimple.o: TrajetSimple.cpp
	g++ -c TrajetSimple.cpp

ListeTrajets.o : ListeTrajets.cpp
	g++ -c ListeTrajets.cpp

clear:
	rm *.o Main *.h.gch
