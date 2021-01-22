#include <string>
#include <iostream>
using namespace std;

#include "Specifications.h"
#include "Interpreteur.h"

int main(int argc, char ** argv) {
    Interpreteur * inter = new Interpreteur();

    inter->LireCommande(argc,argv);
    Specifications * speCom = inter->GetObjSpeci();
    cout<<speCom->GetSpeci("log")<<" "<<speCom->GetSpeci("-e")<<" "<<speCom->GetSpeci("-os");
    if(speCom->GetSpeci("-err")=="") {
        cout<<"Err non renseigne"<<endl;
    }
    delete inter;
    return 0;
}
