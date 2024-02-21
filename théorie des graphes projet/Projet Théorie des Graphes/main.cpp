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
    int v = 0;
    //std::cout << Saisir le nom du fichier :
    //std::cin >> nom_fich1
    //std::cout <<  std::endl;



    do
    {
        choix=0;
       /* std::cout<<"Entrez le nom du graphe ( JE L'AI POUR L'INSTANT PAS MIT METTEZ JUSTE UN NOMBRE AU HASARD: " ;
        std::cin>>v;
        std::cout<< std::endl;*/

        Graphe G(nom_fich1);
        G.dessinGraphe();



        while(choix!=6 && choix!=1)
        {
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
                case 2: G.afficher();
                        break;

                case 3: G.lire2(nom_fich2);
                        break;

                case 4: G.central();
                        break;


            }

            if( choix== 2 || choix== 4 )
            {
                std::cout<< "Saisissez un nombre pour continuer";
                std::cin>>v;
                std::cout<< std::endl;
            }

        }




       // G.~Graphe();

    }while(choix!=6);


    return 0;
}
