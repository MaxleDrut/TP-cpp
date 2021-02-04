/*************************************************************************
                           Analyseur -  description
                             -------------------
    début                : 22/01/21
    copyright            : (C) 2021 par DRUTEL Maxence et GUILLEVIC Marie
*************************************************************************/

//---------- Interface de la classe <Analyseur> (fichier Analyseur.cpp) ----------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système


//------------------------------------------------------ Include personnel

#include "Analyseur.h"
#include "Lecteur.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
codeAnalyse Analyseur :: ChargementLogs(Specifications * speci)
//Algorithme:
//      Pour chaque logs retourné par le Lecteur, on vérifie que les informations correspondent
//      aux les options précisées dans la commande. SI c'est le cas on
//      insert dans l'unordered_multimap logs, la requête en clé et le referer en Attribut.
{
    Lecteur * lecteur = new Lecteur();
    codeLecteur code = lecteur->OuvertureLog(speci->GetSpeci("log"));
    if(code==SUCCESS){
        string * info = RecupLecteur(lecteur->NextLine());
        bool verifSpeci; //Nous retourne si la Specification est respectée

        while(info[0]!="Fin"){
            verifSpeci=true;
            for(int i=0; i<7;i++){

                //Addresse ip
                if(speci->GetSpeci("-ip")!="\0" && speci->GetSpeci("-ip")!=info[0]){
                    verifSpeci=false;
                }

                //Heure
                if(speci->GetSpeci("-t")!="\0" &&speci->GetSpeci("-t")!=info[1]){
                    verifSpeci=false;
                }

                //Exclusion des images, des docs css et js
                if(speci->GetSpeci("-e")!="\0"){
                    verifSpeci=exclusion(info[2]);
                    if(verifSpeci){
                        verifSpeci=exclusion(info[5]);
                    }

                }

                //Status
                if(speci->GetSpeci("-err")!="\0" && stoi(info[3])==200){
                    verifSpeci=false;
                }

                //Poids en octet
                if((speci->GetSpeci("-p")!="\0" && info[4] == "-") || (speci->GetSpeci("-p")!="\0" && stoi(info[4])<stoi(speci->GetSpeci("-p")))){
                    verifSpeci=false;
                }

                //systeme d'exploitation
                if(speci->GetSpeci("-os")!="\0" && (info[6]!=speci->GetSpeci("-os"))){
                    verifSpeci=false;
                }
            }

            //Si la specification est réspectée par la ligne de log, on l'insert dans logs
            if(verifSpeci){
                logs.insert(make_pair<string,string>(move(info[2]),move(info[5])));
            }

            //On oublie pas de supprimer le tableau d'info sur la ligne de log
            delete[] info;

            //On recupère les infos sur la ligne suivante
            info = RecupLecteur(lecteur->NextLine());
        }

        //Si la commande précise qu'il faut un graph, on appelle le Grapheur qui le genere
        if(speci->GetSpeci("-g")!="\0"){
            Grapheur * graph = new Grapheur();
            graph->GenererGraph(speci->GetSpeci("-g"),logs);
            delete graph;
        }

        delete[] info;
        delete lecteur; //Delete lecteur va fermer le fichier log
        return BON;
    } else {
        delete lecteur;
        return PASBON;
    }

}//------ Fin de ChargementLogs

string * Analyseur::RecupLecteur(string * ligne)
//ALgorithme:
//     Pour chaque information de la ligne de log, on extrai l'information spécifique que l'on veut
//     traitée. On copie charactère par charactère dans la string correspondante à l'information.
{
      if(ligne[0]!="Fin"){
        string * tabInfo = new string[7];

        //Les lignes suivantes donne l'information à traitée directement (ip, erreur, poid et systeme)
        tabInfo[0]=ligne[0];
        tabInfo[3]=ligne[3];
        tabInfo[4]=ligne[4];
        tabInfo[6]=ligne[6];

        //On récupère ici seulement l'heure, sans le jour ou les minutes
        int pos=0;
        while(ligne[1][pos]!=':'){
            pos++;
        }
        pos++;
        while(ligne[1][pos]!=':'){
            tabInfo[1]+=ligne[1][pos];
            pos++;
        }

        //On récupère ici seulement l'url de la requete sans le type d'action
        pos=0;
        while(ligne[2][pos]!='/'){
            pos++;
        }
        while(ligne[2][pos]!=' '){
            tabInfo[2]+=ligne[2][pos];
            pos++;
        }

        //Récuperation de l'url de referer, en faisant attention à bien enlever la base si l'url est locale
        pos=0;
        string httpLocal = "http://intranet-if.insa-lyon.fr";
        string subLine = ligne[5].substr(pos,httpLocal.size());
        if(httpLocal==subLine){
            pos+=httpLocal.size();
        }
        while(ligne[5][pos]!='\"'){
            tabInfo[5]+=ligne[5][pos];
            pos++;
        }

        delete[] ligne;
        return tabInfo;
    }else{

        //Lorque que l'on atteint la fin du fichier on renvoie Fin
        string * tabInfo = new string[1];
        tabInfo[0]="Fin";
        delete[] ligne;
        return tabInfo;
    }

}//------- Fin de RecupLecteur

Requetes Analyseur::GenererTop10()
//Algorithme :
//      Créer d'abord une map contenant l'url des requetes en clé et le nombre de fois
//      qu'elles sont faites en valeur. Pour cela, on incrémente la valeur d'une clé si elle
//      se trouve déja dans la map.
//      Pour retourner les requetes les plus faites dans l'ordre, on créer une map de type Requetes (int,string)
//      à partir de mymap, en prenant pour clé le nombre de fois que la requête à été faite
{
    map <string,int> mymap;
    for(auto & x : logs) {
        //Si mymap est vide ou si elle ne contient pas la clé, on insert notre requete
        if(mymap.empty() || mymap.find(x.first)==mymap.end()){
            mymap.emplace(x.first,1);
        }else if(!mymap.empty() && mymap.find(x.first)!=mymap.end()){ //Si mymap n'est pas vide ou qu'elle contient déja la requête, on incrémente la valeur
            mymap[x.first]++;
        }
    }
    Requetes top10;
    for(auto & x : mymap)
    {
        top10.emplace(x.second,x.first);
    }
    return top10;
}//----- Fin de GenererTop10


void Analyseur::AfficherTop10()
//Algorithme : Aucun
{
    Requetes top10 = GenererTop10();

    //Permet, pour chaque égalité dans le nombre de hit, de classer les url dans l'ordre alphabetique
    string * tab = ordreAlphabet(top10);

    for(int i=0; i<10;i++) {
        cout<<tab[i]<<endl;
    }
    delete[] tab;

}//----- Fin de AfficherTop10


const ClasseurLogs Analyseur::GetLogs() const
//Algorithme:Aucun
{
    return logs;
}//----- Fin de GetLogs

//-------------------------------------------- Constructeurs - destructeur

Analyseur::Analyseur()
//Algorithme: Aucun
{
    #ifdef MAP
        cout << "Appel au constructeur vide de <Analyseur>" << endl;
    #endif
}//----- Fin de Analyseur

Analyseur::~Analyseur()
//Algorithme: Aucun
{
    #ifdef MAP
        cout << "Appel au destructeurde <Analyseur>" << endl;
    #endif
}//----- Fin de ~Analyseur

//----------------------------------------------------- Méthodes privées
bool Analyseur :: exclusion(string doc)
//Algorithme :
//      Parcours la string doc jusqu'à arriver au format du document. Puis on vérifie
//      si le format est un format image, css ou javascript. Dans ce cas
//      il faut exclure le document et donc la méthode renvoie faux.
{
    int pos=0;
    string format;
    const string tabFormat[] = {".png",".jpg",".gif",".css",".json",".ico",".bmp"};
    int sizeTabFormat=6;

    //Si la ressource n'est pas un document, il faut s'assurer que la boucle s'arrète en fin de ligne
    while(doc[pos]!='.' && doc[pos]!='\0'){
        pos++;
    }

    //Sinon on copie le format du doc pour le comparer par la suite
    while(doc[pos]!='\0'){
        format+=doc[pos];
        pos++;
    }

    for(int i=0; i<sizeTabFormat; i++){
        if(format==tabFormat[i]){
            return false;
        }
    }
    return true;

}//----- fin d'exclusion


string * Analyseur::ordreAlphabet(Requetes top10)
//Algorithme :
//      Parcours le top 10 jusqu'à 10 iterations. Lorsqu'il y a plusieur
//      fois des requetes avec le même nombre de hits, on sort (méthode de la stl)
//      le tableau tab qui contient les requêtes. Puis on ajoute chaque requetes
//      dans affiche.
{
    Requetes :: reverse_iterator it;
    int pos1=0;
    string * affiche = new string[10];
    string * tab;

    it=top10.rbegin();
    while(pos1<10 && it!=top10.rend()) {

        //position dans tab
        long long unsigned int pos=0;

        //tab contient les requêtes ayant le même nombre de hits
        tab = new string[top10.count(it->first)];

        //nb est le nombre de requetes ayant le même nombre de hits
        long long unsigned int nb = top10.count(it->first);

        int val=it->first;
        while(pos<nb){
            tab[pos]=it->second;
            pos++;
            ++it;
        }

        //Classe dans l'ordre alphabetique les url de tab
        sort(tab,tab+nb);
        pos=0;

        //Ajoute dans le tableau de string affiche les requetes en gardant l'ordre du nombre de hits et en classant par ordre alphabetique
        while(pos1<10 && pos<nb){
            affiche[pos1]=tab[pos] + " ("+ to_string(val)+" hits)";
            pos++;
            pos1++;
        }
        delete[] tab;
    }
    return affiche;
}
