TestMarie: TestMarie.o Lecteur.o Analyseur.o Specifications.o
	g++ -o TestMarie TestMarie.o Lecteur.o Analyseur.o Specifications.o

TestMarie.o: TestMarie.cpp
	g++ -c TestMarie.cpp

Lecteur.o: Lecteur.cpp
	g++ -c Lecteur.cpp

Analyseur.o: Analyseur.cpp
	g++ -c Analyseur.cpp

Specifications.o: Specifications.cpp
	g++ -c Specifications.cpp

TestMaxence: TestMaxence.o Specifications.o
	g++ -o TestMaxence TestMaxence.o Specifications.o

TestMaxence.o: TestMaxence.cpp
	g++ -c TestMaxence.cpp

Specifications.o: Specifications.cpp
	g++ -c Specifications.cpp

clear:
	rm *.o Main TestMaxence TestMarie *.h.gch
