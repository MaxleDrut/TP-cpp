CFLAGS =  -ansi -pedantic -Wall -std=c++11

all: analog
	
analog: analog.o Specifications.o Interpreteur.o Analyseur.o Lecteur.o Grapheur.o
	g++ -o analog analog.o Specifications.o Interpreteur.o Analyseur.o Lecteur.o Grapheur.o	
	
analog.o: analog.cpp 
	g++ -c analog.cpp $(CFLAGS)
	
TestMarie: TestMarie.o Lecteur.o Analyseur.o Specifications.o
	g++ -o TestMarie TestMarie.o Lecteur.o Analyseur.o Specifications.o

TestMarie.o: TestMarie.cpp
	g++ -c TestMarie.cpp $(CFLAGS)

Lecteur.o: Lecteur.cpp
	g++ -c Lecteur.cpp $(CFLAGS)

Analyseur.o: Analyseur.cpp
	g++ -c Analyseur.cpp $(CFLAGS)

Specifications.o: Specifications.cpp
	g++ -c Specifications.cpp $(CFLAGS)

TestMaxence: TestMaxence.o Specifications.o Interpreteur.o Analyseur.o Lecteur.o Grapheur.o
	g++ -o TestMaxence TestMaxence.o Specifications.o Interpreteur.o Analyseur.o Lecteur.o Grapheur.o

TestMaxence.o: TestMaxence.cpp
	g++ -c TestMaxence.cpp $(CFLAGS)

Interpreteur.o: Interpreteur.cpp
	g++ -c Interpreteur.cpp $(CFLAGS)

Grapheur.o: Grapheur.cpp
	g++ -c Grapheur.cpp $(CFLAGS)

clear:
	rm *.o Main TestMaxence TestMarie *.h.gch *.dot *.png
