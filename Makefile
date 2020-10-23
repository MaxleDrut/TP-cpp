TEnsemble: TEnsemble.o Ensemble.o
	g++ -o TEnsemble TEnsemble.o Ensemble.o

TEnsemble.o: TEnsemble.cpp
	g++ -c TEnsemble.cpp

Ensemble.o: Ensemble.cpp
	g++ -c Ensemble.cpp
