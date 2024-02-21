#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED
#include <vector>
#include <fstream>
#include "sommet.h"
#include <string>
#include "arc.h"
#include "svgfile.h"



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
        void lire2(std::string nom_fich2);
        /*void tri_Dj(int r, int z);
        void relachement(Arc A);*/
        ~Graphe()
        {};
        void degre();
};

#endif // GRAPHE_H_INCLUDED
