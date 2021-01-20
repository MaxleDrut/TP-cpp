#include <string>
#include <iostream>
using namespace std;

#include "Specifications.h"



int main(int argc, char ** argv) {

    Specifications * speci = new Specifications();
    speci->ajoutSpeci("-os","Windows");

    delete speci;
    return 0;
}
