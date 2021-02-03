CFLAGS =  -ansi -pedantic -Wall -std=c++11

all: analog

analog: analog.o Specifications.o Interpreteur.o Analyseur.o Lecteur.o Grapheur.o
	g++ -o analog analog.o Specifications.o Interpreteur.o Analyseur.o Lecteur.o Grapheur.o

analog.o: analog.cpp
	g++ -c analog.cpp $(CFLAGS)

Lecteur.o: Lecteur.cpp
	g++ -c Lecteur.cpp $(CFLAGS)

Analyseur.o: Analyseur.cpp
	g++ -c Analyseur.cpp $(CFLAGS)

Specifications.o: Specifications.cpp
	g++ -c Specifications.cpp $(CFLAGS)

Interpreteur.o: Interpreteur.cpp
	g++ -c Interpreteur.cpp $(CFLAGS)

Grapheur.o: Grapheur.cpp
	g++ -c Grapheur.cpp $(CFLAGS)

clear:
	rm *.o *.h.gch *.dot *.png analog
