#include <iostream>
#include <fstream>
#include "graphe.h"
#include "sommet.h"
#include <string>
#include <algorithm>
#include "arc.h"
#include <vector>

struct Donne
{
    int x, y;
};

Graphe::Graphe(std::string nom_fich1) ///focntion de lecture du premier fichier
{
    int idS, coordX, coordY;
    char nom;
    int e,s,idA;
    Arc a;
    std::ifstream fichier (nom_fich1);
    Sommet* s1;
    fichier>>m_orient; ///lecture et enregisrement de l'orientation et de l'ordre
    fichier>>m_ordre;

    for(int i=0; i<m_ordre; i++) ///enregistrement des sommets avec leurs caractéristiques (ID, Nom, Coordonnées)
    {
        fichier>>idS;
        fichier>>nom;
        fichier>>coordX;
        fichier>>coordY;
        s1=new Sommet(idS, nom, coordX, coordY);///ajout du nouveau sommet dans le vecteur de Sommet du graphe
        m_sommets.push_back(s1);
    }
    fichier>>m_nbA;///lecture à la fin du nombre d'arêtes

    for(int k=0; k<m_nbA; k++)
    {
        fichier>>idA; ///lecture procéduriale sans pondération d'abord
        fichier>>e; ///lecure des deux sommets liés à cette arête
        fichier>>s;
        a.idA=idA; ///lecture des noms, poids (initialisé à 1) et enregistrement
        a.e=e;
        a.s=s;
        a.p=0;
        m_arcs.push_back(a);
        m_sommets[e]->ajouterSucc(m_sommets[s]);///ajout de la nouvelle arête dans le vecteur d'arêtes de notre graphe

        if(!m_orient)
            m_sommets[s]->ajouterSucc(m_sommets[e]); ///si il y aune orientation, alors on ajoute le succeseur au premier sommet
    }

    for(int k=0; k<m_ordre; k++) ///procédure d'affichage (cela peut permettre de vérifier que les données sont les bonnes)
    {
        std::cout<<"sommet : "<<m_sommets[k]->getNum();
        std::cout<<"  nom : "<<m_sommets[k]->getNom();
        std::cout<<"  coord : "<<m_sommets[k]->getCoordX();
        std::cout<<" "<<m_sommets[k]->getCoordY()<<std::endl;;
    }
    std::cout<<"nombre d'aretes : "<<m_nbA<<std::endl;
    for(int u=0; u<m_nbA; u++)
    {
        std::cout<<"arete : "<<m_arcs[u].idA<<"  entree : "<<m_arcs[u].e<<"  sortie : "<<m_arcs[u].s<<"  poids : "<<m_arcs[u].p<<std::endl;
    }

}



void Graphe::lire2(std::string nom_fich2)///lecture du deuxième fichier de pondération
{
    std::ifstream fichier (nom_fich2);
    fichier>>m_nbA;
    int id,p;
    for(int i=0; i<m_nbA; i++) ///on enregistre toutes les arêtes en lisant les ID et les poids
    {
        fichier>>id;
        fichier>>p;
        for(int j=0; j<m_nbA; j++) ///on parcourt notre vecteur d'arêtes et dès qu'on retrove l'arête dont on doit charge le poids, alors on change le poids de l'arête déjà enregistrée
        {
            if(id == m_arcs[j].idA)
            {
                m_arcs[j].p = p;
            }
        }
    }

    for(int k=0; k<m_ordre; k++) ///affichage des donnéesde notre graphe avec désormais les poids qui ont été rajoutés
    {
        std::cout<<"sommet : "<<m_sommets[k]->getNum();
        std::cout<<"  nom : "<<m_sommets[k]->getNom();
        std::cout<<"  coord : "<<m_sommets[k]->getCoordX();
        std::cout<<" "<<m_sommets[k]->getCoordY()<<std::endl;;
    }
    std::cout<<"nombre d'aretes : "<<m_nbA<<std::endl;
    for(int u=0; u<m_nbA; u++)
    {
        std::cout<<"arete : "<<m_arcs[u].idA<<"  entree : "<<m_arcs[u].e<<"  sortie : "<<m_arcs[u].s<<"  poids : "<<m_arcs[u].p<<std::endl;
    }

}

void Graphe::dessinGraphe() ///fonction de dessin de divers sommets et leur arêtes
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
		position[i].y = m_sommets[i]->getCoordY() * 100 ; ///normalisation des coordonnées pour pouvoir les afficher dans l'écran (les coordonnées vont devoir être modifiées)

		if(couleur == 0)   ///différents affichages en fonction des couleurs
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
    std::cout<< m_nbA <<std::endl;

	for(int i= m_nbA - 1; i >= 0 ; i--)
	{
		if(m_orient == 0) ///dessin des arêtes si pas d'orientation (dessins de simples lignes sans sens)
        {
			dessin.addLine(position[m_arcs[i].e].x, position[m_arcs[i].e].y, position[m_arcs[i].s].x, position[m_arcs[i].s].y, "black");

			/*dessin.addLine(position[m_arcs[0].e].x, position[m_arcs[0].e].y, position[m_arcs[0].s].x, position[m_arcs[0].s].y, "black");
			dessin.addLine(position[m_arcs[1].e].x, position[m_arcs[1].e].y, position[m_arcs[1].s].x, position[m_arcs[1].s].y, "black");
			dessin.addLine(position[m_arcs[2].e].x, position[m_arcs[2].e].y, position[m_arcs[2].s].x, position[m_arcs[2].s].y, "black");
			dessin.addLine(position[m_arcs[3].e].x, position[m_arcs[3].e].y, position[m_arcs[3].s].x, position[m_arcs[3].s].y, "black");*/

			std::cout << position[m_arcs[i].e].x << "," << position[m_arcs[i].e].y  << "   " << position[m_arcs[i].s].x << "," << position[m_arcs[i].s].y << std::endl;
        }



	else ///dessin des arêtes si orientation
		{
			dessin.addLine(position[m_arcs[i].s].x, position[m_arcs[i].s].y, position[m_arcs[i].e].x, position[m_arcs[i].e].y, "black");
			//dessin.addTriangle(positionm_arcs[i].e].x, positionm_arcs[i].e].y, positionm_arcs[i].e].x, positionm_arcs[i].e].y-2
		}



		if(m_arcs[i].p != 0) ///si le poids des arêtes est différent de 0, on affiche le poids des arêtes à côté de ces dernières
			dessin.addText((position[m_arcs[i].s].x + position[m_arcs[i].e].x)/2, (position[m_arcs[i].s].y + position[m_arcs[i].e].y)/2, m_arcs[i].p, "black");


	}



}
void Graphe::degre() /// fonction permettant 'obtenir les degrés des divers sommets du graphe
	{
	    int i,j,max1,min1;
	    max1=0;min1=m_ordre;
	    j=m_sommets.size();
	    int centrDeg[j];
	    int centrDegNorm[j];
	    for(i=0;i<m_sommets.size();++i)
        { centrDeg[i]=m_sommets[i]->getdegre();


        };
        for(i=0;i<m_sommets.size();++i)
        {
            if(centrDeg[i]>max1) max1=centrDeg[i];
            if(centrDeg[i]<min1) min1=centrDeg[i];
            centrDegNorm[i]=centrDeg[i]/m_ordre;
        }
         std::cout<<"max = "<<max1<<"  min = "<<min1<<std::endl;
        for(i=0;i<m_sommets.size();++i)
        {
            std::cout<<"sommet numero"<<i<<" de degre "<<centrDeg[i]<<std::endl;
        }std::cout<<"affichage des valeurs normees\n";
        for(i=0;i<m_sommets.size();++i){
        std::cout<<"sommet numero"<<i<<" de degre "<<centrDeg[i]<<std::endl;}

	}
