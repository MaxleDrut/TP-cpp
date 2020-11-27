all: Main

Main : Main.o TrajetSimple.o
	g++ -o Main Main.o TrajetSimple.o

Main.o : Main.cpp
	g++ -c Main.cpp

TrajetSimple.o: TrajetSimple.cpp
	g++ -c TrajetSimple.cpp

clear:
	rm *.o Main *.h.gch
