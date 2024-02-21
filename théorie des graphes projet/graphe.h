#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED
#include <vector>
#include <fstream>
#include "sommet.h"
#include <string>
#include "arc.h"
#include "svgfile.h"
#include <stack>
#include <list>



class Graphe
{
    protected :
          int m_orient;
          std::vector<Sommet*> m_sommets;
          int m_ordre;
          int m_nbA;
          std::vector<Arc> m_arcs;



    public :
        Graphe(std::string nom_fich1);
        void dessinGraphe();
        int getOrdre();
        void matriceAdj();
        Sommet* getSommet(int i);
        void lire2(std::string nom_fich2);
        void centraliteDegre();
        void vecteurPropre();
        void centraliteProximite();
        int minDistance(int dist[], bool sptSet[]);
        void djikstra( int source, int dist[]);
        void central(std::ofstream &ofs);
        void afficher();
        int connexe(int num_s0);
        void suppArrete(int num, std::string nom_fich1, std::string nom_fich2);
        void suppLignePoids(std::string nom_fich, int ligneVrai);
        void suppLigneGraphe(std::string nom_fich, int ligneVrai);
        void intermediarite();
        void comparerIndice(std::ofstream &ofs);
        void indiceSauvegarde();
        ~Graphe()
        {
            /*for (auto s : m_sommets)
                delete s;*/
        }

};

#endif // GRAPHE_H_INCLUDED
