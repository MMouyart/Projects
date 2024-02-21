#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED
#include <vector>
class Sommet
{
    protected :
        //int m_dist;
        int m_coordX;
        int m_coordY;
        char m_nom;
        int m_num;
        std::vector<const Sommet*> m_successeurs;



    public :
        Sommet(int num, char nom, int coordX, int coordY);
        int getNum();
        char getNom();
        int getCoordX();
        int getCoordY();
        const std::vector<const Sommet*>& getSuccesseurs()const {return m_successeurs;}
        void ajouterSucc(const Sommet*s)
        {
            m_successeurs.push_back(s);
        };
        int getdegre();



        //const std::vector<const Sommet*>& getSuccesseurs()const {return m_successeurs;}

        //int getDist();
        //Sommet* getPere();
        //void setDist(int dist);
        //void setPere(Sommet* pere);

};



#endif // SOMMET_H_INCLUDED
