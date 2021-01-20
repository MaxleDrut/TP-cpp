TestMarie: TestMarie.o Lecteur.o
	g++ -o TestMarie TestMarie.o Lecteur.o

TestMarie.o: TestMarie.cpp
	g++ -c TestMarie.cpp

Lecteur.o: Lecteur.cpp
	g++ -c Lecteur.cpp


TestMaxence: TestMaxence.o Specifications.o
	g++ -o TestMaxence TestMaxence.o Specifications.o

TestMaxence.o: TestMaxence.cpp
	g++ -c TestMaxence.cpp

Specifications.o: Specifications.cpp
	g++ -c Specifications.cpp

clear:
	rm *.o Main TestMaxence TestMarie *.h.gch
