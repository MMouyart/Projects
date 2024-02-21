#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED
#include <vector>
class Sommet
{
    protected :
        //int m_dist;
        int m_coordX;
        float m_VectPropre;
        float m_AncienVectPropre;
        int m_coordY;
        char m_nom;
        float m_AncienIntermediarite;
        float m_AncienCentralProxim;
        float m_intermediarite;
        float m_centralProxim;
        int m_num;
        int m_Anciendegre;
        int m_degre;
        float m_AnciendegreN;
        float m_degreN;
        std::vector< Sommet*> m_successeurs;
        float centralite;


    public :
        Sommet(int num, char nom, int coordX, int coordY);
        float getCentralite();
        void setCentralite(float centralPRox, float centralInter);
        int getDegre();
        float getVectPropre();
        void setVectPropre(float i);
        float getDegreN();
        void setDegreN(float i);
        void setDegre(int deg);
        char getNom();
        int getCoordX();
        int getCoordY();
        int getNum(){return m_num;}
        const std::vector< Sommet*>& getSuccesseurs()const {return m_successeurs;}
        void setCentralProx(float prox){ m_centralProxim= prox;}
        float getCentralProx(){ return m_centralProxim;}
        void suppSuccesseur(Sommet* sommet);
        void setIntermediarite(float inter){ m_intermediarite= inter;}
        float getIntermediarite(){ return m_intermediarite;}

        void setAncienDegre(int deg){ m_Anciendegre= deg;}
        int getAncienDegre(){ return m_Anciendegre;}

        void setAncienDegreN(float deg){ m_AnciendegreN= deg;}
        float getAncienDegreN(){ return m_AnciendegreN;}

        void setAncienIntermediarite(float inter){ m_AncienIntermediarite= inter;}
        float getAncienIntermediarite(){ return m_AncienIntermediarite;}

        void setAncienCentralProx(float proxim){ m_AncienCentralProxim= proxim;}
        float getAncienCentralProx(){ return m_AncienCentralProxim;}

        void setAncienVectPropre(float vect){ m_AncienVectPropre= vect;}
        float getAncienVectPropre(){ return m_AncienVectPropre;}


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
