#include <iostream>
#include <fstream>
#include "sommet.h"
#include "graphe.h"
#include <string>

int menu()
{
    std::cout<<"souhaitez vous etudier la topologie avec ponderation ? (1 pour oui et 0 pour non) : ";
    int choix;
    std::cin>>choix;
    return choix;
}


int main()
{
    std::string nom_fich1="graphe.txt";
    std::string nom_fich2="poids.txt";
    Graphe G(nom_fich1);
    G.degre();

    if(menu()==1)
    {
        std::cout<<" "<<std::endl;
        G.lire2(nom_fich2);
    }


    G.dessinGraphe();
    G.~Graphe();

    return 0;
}
