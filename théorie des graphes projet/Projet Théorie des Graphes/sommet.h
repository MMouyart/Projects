#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED
#include <vector>
class Sommet
{
    protected :
        //int m_dist;
        int m_coordX;
        double m_VectPropre;
        int m_coordY;
        char m_nom;
        float m_centralProxim;
        int m_num;
        double m_degre;
        double m_degreN;
        std::vector< Sommet*> m_successeurs;
        double m_fiabilite;
        double m_centralite;


    public :
        Sommet(int num, char nom, int coordX, int coordY);

        double getDegre();
        double setcentralite(double cent);
        double getcentralite ();
        double getVectPropre();
        void setVectPropre(double i);
        double getDegreN();
        void setDegreN(double i);
        void setDegre(double deg);
        char getNom();
        int getCoordX();
        int getCoordY();
        int getNum(){return m_num;}
        const std::vector< Sommet*>& getSuccesseurs()const {return m_successeurs;}
        void setCentralProx(float prox){ m_centralProxim= prox;}
        float getCentralProx(){ return m_centralProxim;}
        void centrallitefinal();














        void ajouterSucc( Sommet*s)
        {
            m_successeurs.push_back(s);
        }


        //const std::vector<const Sommet*>& getSuccesseurs()const {return m_successeurs;}

        //int getDist();
        //Sommet* getPere();
        //void setDist(int dist);
        //void setPere(Sommet* pere);

};



#endif // SOMMET_H_INCLUDED
