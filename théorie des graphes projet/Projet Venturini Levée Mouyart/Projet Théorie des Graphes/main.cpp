#include <iostream>
#include <fstream>
#include "sommet.h"
#include "graphe.h"
#include <string>
#include <cstdlib>




int main()
{
    std::string nom_fich1="graphe.txt";
    std::string nom_fich2="poids.txt";
    int choix = 0;
    int arrete = 0;
    int ponderation= 0;
    int v = 0;
    std::ofstream ofs;
    ofs.open("resultats.txt",std::ofstream::out);
    Graphe G(nom_fich1);
    G.dessinGraphe();


    do
    {
        choix=0;
     std::cout<<"Entrez le nom du graphe ('graphe.txt' mais il y en a d'autre dans le fichier 'Tous les graphes' " << std::endl;
        std::cin>>nom_fich1;
        std::cout<< std::endl;
        Graphe G(nom_fich1);
        G.dessinGraphe();


        while(choix!=6 && choix!=1 && choix!=5)
        {
            if(ponderation == 1)
                G.lire2(nom_fich2);


            if(arrete == 1)
            {
                G.indiceChargement();
            }




            system("cls");
            std::cout<<" 1. Souhaitez vous etudier un autre graphe ?  " << std::endl;
            std::cout<< std::endl;
            std::cout<<" 2. Souhaitez vous afficher le graphe ?  " << std::endl;
            std::cout<< std::endl;
            std::cout<<" 3. Souhaitez vous etudier la topologie avec ponderation ?  " << std::endl;
            std::cout<< std::endl;
            std::cout<<" 4. Souhaitez vous afficher les indices de centralite ?  " << std::endl;
            std::cout<< std::endl;
            std::cout<<" 5. Souhaitez vous supprimer des arretes ?  " << std::endl;
            std::cout<< std::endl;
            std::cout<<" 6. Souhaitez vous quittez ?  " << std::endl;
            std::cout<< std::endl;
            std::cin>>choix;
            system("cls");

            switch(choix)
            {
                case 1: ponderation=0;
                        arrete = 0;
                        break;

                case 2: std::cout<<"Le graphe obtenue : " << std::endl;
                        std::cout<< std::endl;
                        G.afficher();
                        break;

                case 3: std::cout<<"Entrez le nom du fichier ponderation" << std::endl;
                        std::cin>>nom_fich2;
                        std::cout<< std::endl;
                        arrete = 0;
                        G.lire2(nom_fich2);
                        ponderation = 1;
                        break;

                case 4: G.central(ofs);
                        if(arrete == 1)
                        {
                            std::cout<<"L'ancien graphe " << std::endl;
                            std::cout<< std::endl;
                            G.afficherAncien();
                        }
                        break;

                case 5: int num;
                        G.central(ofs);
                        system("cls");
                        G.afficher();
                        G.indiceSauvegarde();
                        std::cout<<"Indiquez le numero de l'arrete que vous voulez supprimer : ";
                        std::cin>>num;
                        G.suppArrete(num, nom_fich1, nom_fich2);
                        std::cout<<std::endl;
                        std::cout<<std::endl;
                        std::cout<<std::endl;
                        arrete = 1;
                        int v;
                        std::cout<<"Retournez au menu en rentrant 1"<<std::endl;
                        std::cin>>v;
                        break;




            }

            if( choix== 2 || choix== 4 )
            {
                std::cout<< "Saisissez un nombre pour continuer";
                std::cin>>v;
                std::cout<< std::endl;
            }

        }





    }while(choix!=6);


    return 0;
}
