#include <iostream>
#include <fstream>
#include "graphe.h"
#include "sommet.h"
#include <string>
#include <algorithm>
#include <math.h>
#include "arc.h"
#include <vector>
#include <list>
#include <stack>

struct Donne
{
    int x, y;
};

Graphe::Graphe(std::string nom_fich1)
{
    int idS, coordX, coordY;
    char nom;
    int e,s,idA;
    Arc a;
    std::ifstream fichier (nom_fich1);
    Sommet* s1;
    fichier>>m_orient;
    fichier>>m_ordre;

    for(int i=0; i<m_ordre; i++)
    {
        fichier>>idS;
        fichier>>nom;
        fichier>>coordX;
        fichier>>coordY;
        s1=new Sommet(idS, nom, coordX, coordY);
        m_sommets.push_back(s1);
    }

    fichier>>m_nbA;

    for(int k=0; k<m_nbA; k++)
    {
        fichier>>idA;
        fichier>>e;
        fichier>>s;
        a.idA=idA;
        a.e=e;
        a.p=1;
        a.s=s;
        m_arcs.push_back(a);
        m_sommets[e]->ajouterSucc(m_sommets[s]);

        if(!m_orient)
            m_sommets[s]->ajouterSucc(m_sommets[e]);
    }
}




void Graphe::lire2(std::string nom_fich2)
{
    std::ifstream fichier (nom_fich2);
    fichier>>m_nbA;
    int id,p;
    for(int i=0; i<m_nbA; i++)
    {
        fichier>>id;
        fichier>>p;
        for(int j=0; j<m_nbA; j++)
        {
            if(id == m_arcs[j].idA)
            {
                m_arcs[j].p = p;
            }
        }
    }
}




void Graphe::dessinGraphe()
{
    Svgfile dessin;

	Donne position[m_ordre];
    int couleur;

    for(int i=0 ; i < m_ordre ; i++)
	{
	    couleur = 0;
		for(auto succ : m_sommets[i]->getSuccesseurs())
			couleur++;

		position[i].x = m_sommets[i]->getCoordX() * 100 ;
		position[i].y = m_sommets[i]->getCoordY() * 100 ;

		if(couleur == 0)
			dessin.addDisk(position[i].x,  position[i].y, 7, "black");

		else if(couleur == 1)
			dessin.addDisk(position[i].x,  position[i].y, 7, "blue");

		else if(couleur == 2)
			dessin.addDisk(position[i].x,  position[i].y, 7, "red");

		else if(couleur == 3)
			dessin.addDisk(position[i].x,  position[i].y, 7, "green");

		else if(couleur == 4)
			dessin.addDisk(position[i].x,  position[i].y, 7, "orange");

		else if(couleur == 5)
			dessin.addDisk(position[i].x,  position[i].y, 7, "yellow");

		else if(couleur == 6)
			dessin.addDisk(position[i].x,  position[i].y, 7, "cyan");

		else
			dessin.addDisk(position[i].x, position[i].y, 7, "purple");
	}


	for(int i= m_nbA - 1; i >= 0 ; i--)
	{
		if(m_orient == 0)
        {
			dessin.addLine(position[m_arcs[i].e].x, position[m_arcs[i].e].y, position[m_arcs[i].s].x, position[m_arcs[i].s].y, "black");
        }



	else
		{
			dessin.addLine(position[m_arcs[i].s].x, position[m_arcs[i].s].y, position[m_arcs[i].e].x, position[m_arcs[i].e].y, "black");
			///Mettre le triangle
		}



		if(m_arcs[i].p != 0)
			dessin.addText((position[m_arcs[i].s].x + position[m_arcs[i].e].x)/2, (position[m_arcs[i].s].y + position[m_arcs[i].e].y)/2, m_arcs[i].p, "black");


	}


}


///détermine si le graphe est connexe, recoit le sommet de départ pour le BFS et renvoit 1 si le graphe est connexe est 0 sinon
int Graphe::connexe(int num_s0)
{
    /// déclaration de la file
    std::list<int> file;

    /// pour le marquage
    std::vector<int> couleurs((int)m_sommets.size(),0);//0 c'est non visité

    ///pour noter les prédécesseurs : on note les numéros des prédécesseurs (on pourrait stocker des pointeurs sur ...)
    std::vector<int> preds((int)m_sommets.size(),-1);

    ///étape initiale : on enfile et on marque le sommet initial
    couleurs[num_s0]=1;
    file.push_back(num_s0);

    ///tant que la file n'est pas vide
    while(!file.empty())
    {
        ///on défile le prochain sommet
        num_s0 = file.front(); ///Pas sur pour le num_S0
       // std::cout << num_s0 ; ///Pas l'afficehr ici car ne tient pas compte des sommets marqué
        file.pop_front();



        ///pour chaque successeur du sommet défilé
        for(auto succ : m_sommets[num_s0]->getSuccesseurs())


        {

                 if( couleurs[succ->getNum()] != 1)  ///s'il n'est pas marqué
                 {

                    couleurs[succ->getNum()] = 1;  ///on le marque
                    preds[succ->getNum()]=num_s0;   ///on note son prédecesseur (=le sommet défilé)
                    /// preds[succ->getNum()]=num_s0;
                    file.push_back(succ->getNum());  ///on le met dans la file
               }
        }

    }

    int compteur = 1;
    for(int i=0; i<m_sommets.size(); i++)
    {
        for(int j=0; j<preds.size(); j++)
        {
            if(preds[j] == m_sommets[i]->getNum())
            {
                compteur++;
                std::cout<<compteur<<std::endl;
            }
        }
    }
    if(compteur == m_sommets.size())
    {
        return 1;
    }
    else
    {
        return 0;
    }

}


void Graphe::centraliteDegre()
{

    double somme=0,moyenne=0,var=0,EcType=0,Somsq=0;

    for(int i=0 ; i < m_ordre ; i++)

    {

        m_sommets[i]->setDegre(0) ;

       for( auto succ :  m_sommets[i]->getSuccesseurs())

        {

            m_sommets[i]->setDegre(m_sommets[i]->getDegre()+1);
            m_sommets[i]->setDegre(m_sommets[i]->getDegre()/m_ordre);
            m_sommets[i]->setcentralite(m_sommets[i]->getDegre()*0.20);

        }



        somme=somme+m_sommets[i]->getDegre(); Somsq=Somsq+m_sommets[i]->getDegre()*m_sommets[i]->getDegre();

        std::cout<<"sommet numero "<<m_sommets[i]->getNom()<<" centralite de degre = "<<m_sommets[i]->getDegre()<<std::endl;

    }

    moyenne=somme/m_ordre; Somsq=Somsq/m_ordre;

    var=Somsq-moyenne*moyenne; EcType=sqrt(var);

    EcType=1-EcType;
    for(int i =0; i<m_ordre;++i)

        {
            m_sommets[i]->setcentralite(m_sommets[i]->getcentralite()*(EcType));

}
}


void Graphe::vecteurPropre()
{
    float deltaLambda= 1;
    float Lambda=0;
    float stokage=0;
    float degre[m_ordre];
    float degreAjouter[m_ordre];
    double moyenne=0,somme=0,Somsq=0,var=0,EcType=0;

    for(int i=0 ; i < m_ordre ; i++)
    {

        degre[i] = 1;
        degreAjouter[i]=0;

    }

    while((Lambda - 0.00001 )>  deltaLambda ||( Lambda + 0.00001) < deltaLambda ) ///Tant que Lambda varie de 0.00001 près
    {
       deltaLambda =Lambda;
        for(int i=0 ; i < m_ordre ; i++)
        {
            degreAjouter[i]=0;
            stokage=0;
        }

        for(int i=0 ; i < m_ordre ; i++)
        {
            for( int j=0 ; j < m_nbA ; j++)
            {
                if( i == m_arcs[j].e)
                    degreAjouter[i] = degre[m_arcs[j].s] +  degreAjouter[i];

                if(!m_orient)
                    if( i == m_arcs[j].s)
                        degreAjouter[i] = degre[m_arcs[j].e] + degreAjouter[i];
            }
        }


        for(int i=0 ; i < m_ordre ; i++)
        {
            stokage = degreAjouter[i]*degreAjouter[i] + stokage;
        }
        Lambda=sqrt(stokage);


        for(int i=0 ; i < m_ordre ; i++)
        {
            degre[i] = degreAjouter[i] / Lambda;
        }
    }

   for(int i=0 ; i < m_ordre ; i++)
   {

       m_sommets[i]->setVectPropre(degre[i]);somme=somme+m_sommets[i]->getVectPropre();
       m_sommets[i]->setcentralite(m_sommets[i]->getVectPropre()*0.5);
       Somsq=Somsq+(m_sommets[i]->getVectPropre()*m_sommets[i]->getVectPropre());
       std::cout<<"sommet "<<m_sommets[i]->getNom()<<" vecteur propre "<<m_sommets[i]->getVectPropre()<<std::endl;

   }
  /* for(double i=0;i<m_arcs.size();++i)

   {
       Arcsomme=Arcsomme+m_arcs[i]->p;
   }

Arcmoyenne=Arcsomme/i;*/

    moyenne=somme/m_ordre; Somsq=Somsq/m_ordre;



    var=Somsq-moyenne*moyenne; EcType=sqrt(var);
}





int Graphe::minDistance(int dist[], bool sptSet[])
{

    int minDistance = INT_MAX, min_index;

    for (int i = 0; i < m_ordre; i++)
        if (sptSet[i] == false && dist[i] <= minDistance)
            minDistance = dist[i], min_index = i;

    return min_index;
}





void Graphe::djikstra( int source)
{
    int matrice[m_ordre][m_ordre];
    int prox=0;

   // for(int i=0; i<m_nbA; i++)
      //  m_arcs[i].p=1;

    for(int i=0 ; i < m_ordre ; i++)
        for( int j=0 ; j < m_ordre ; j++)
            matrice[i][j]=0;


    for( int j=0 ; j < m_nbA ; j++)
    {
            matrice[m_arcs[j].e][m_arcs[j].s] =  m_arcs[j].p;

            if(!m_orient)
                matrice[m_arcs[j].s][m_arcs[j].e] =  m_arcs[j].p;
    }
    ///NOUS AVONS PRIS SUR INTERNET 20 LIGNES DE CODES POUR REALISER CE CALCUL DE CENTRALITE, BIEN ENTENDU LA SOURCE EST EXPLICITEE DANS LE RENDU
    int dist[m_ordre];
    bool sptSet[m_ordre];

    for (int i = 0; i < m_ordre; i++)
        dist[i] = INT_MAX, sptSet[i] = false;

    dist[source] = 0;

    for (int j = 0; j < m_ordre - 1; j++)
    {
        int u = minDistance(dist, sptSet);
        sptSet[u] = true;
        for (int i = 0; i < m_ordre; i++)
            if(!sptSet[i] && matrice[u][i] && dist[u] != INT_MAX && dist[u] + matrice[u][i] < dist[i])
                dist[i] = dist[u] + matrice[u][i];
    }


    for(int i=0; i < m_ordre ; i++)
    {
        prox = dist[i] + prox;
    }

     m_sommets[source]->setCentralProx((float)1/prox) ;
     m_sommets[source]->setCentralProx((m_sommets[source]->getCentralProx())*(m_ordre-1));
     std::cout<<"sommet "<<m_sommets[source]->getNom()<<" indice de proximite = "<<m_sommets[source]->getCentralProx()<<std::endl<<std::endl;
     m_sommets[source]->setcentralite(0.7*m_sommets[source]->getCentralProx());
}





void Graphe::afficher()
{

    std::cout<<"nombre de sommet : "<<m_ordre<<std::endl;
    for(int k=0; k<m_ordre; k++)
    {
        std::cout<<"Sommet : "<<m_sommets[k]->getNum();
        std::cout<<"   Nom : "<<m_sommets[k]->getNom();
        std::cout<<"   Coord : "<<m_sommets[k]->getCoordX();
        std::cout<<" "<<m_sommets[k]->getCoordY();
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
    std::cout<<"nombre d'aretes : "<<m_nbA<<std::endl;

    for(int u=0; u<m_nbA; u++)
    {
        std::cout<<"arete : "<<m_arcs[u].idA<<"  entree : "<<m_arcs[u].e<<"  sortie : "<<m_arcs[u].s<<"  poids : "<<m_arcs[u].p<<std::endl;
    }
}






void Graphe::central()
{
    centraliteDegre();
    vecteurPropre();
    for(int i=0; i<m_ordre;i++)
        djikstra(i);


    std::cout<<"Sommet       Degre            VectPropre            Proximite normalise" << std::endl;
    for(int k=0; k<m_ordre;k++)
    {
m_sommets[k]->centrallitefinal();
        std::cout<<m_sommets[k]->getNum() << "           " <<m_sommets[k]->getDegre()<<"             ";
        std::cout<< "            "<< m_sommets[k]->getVectPropre() ;
        std::cout<< "      "<< m_sommets[k]->getCentralProx()  << std::endl;


    } for(int k=0; k<m_ordre;k++)
    { std::cout<<"centralite finale pour le sommet "<<m_sommets[k]->getNom()<<" = "<<m_sommets[k]->getcentralite()<<std::endl;
    }

}


